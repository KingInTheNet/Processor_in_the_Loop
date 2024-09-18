/**
 * @file RCS.c
 * @brief RCSとのインターフェースモジュール群です。
 * 
 * RCSインターフェースモジュールは、首都大RCSとのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.10.06
 */

#include "utility.h"	// Printf()使用時には必要

#include "../../../../Port_Config.h"		//デバッグモードの時には必要

#include "RCS.h"

//#define	RCS_DEBUG


int		RCS_Data_Conv(RCS_STRUCT *my_rcs);


#define RCS_RX_FRAME_SIZE			26	/**< @brief 受信フレームの長さ*/
#define RCS_TX_FRAME_SIZE			8	/**< @brief 送信フレームの長さ*/

static unsigned int		rcs_dummy1;
static unsigned char	rcs_tx_frame[RCS_TX_FRAME_SIZE];	/**< @brief 送信フレーム(汎用)*/
static unsigned int		rcs_dummy2;
static unsigned char	rcs_tx_frame_periodic[RCS_TX_FRAME_SIZE] = {0x80, 0x80, 0x01, 0x00, 0x10, 0x00, 0x81, 0x81};	/**< @brief 送信フレーム(定期送信(テレメ要求)用)*/

static unsigned char	rcs_header[2] = {0x80, 0x80};	/**< @brief フレームのヘッダ*/
static unsigned char	rcs_footer[2] = {0x81, 0x81};	/**< @brief フレームのフッタ*/

//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCS構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、 RCS_STRUCT.driver_super に定期受信部のヘッダ,フッタ,フレームサイズ、定期コマンド発行部の情報を記録します。
 * また、初期化と同時に、RCSに対して出力を「標準出力」のみにするようにコマンドを発行します。
 * @note RCSインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param RCS_STRUCT *my_rcs : 初期化するRCS構造体へのポインタ
 * @param unsigned char ch : RCSが接続されているUARTポート番号
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_init() の戻り値を参照)
 */
int		RCS_init(RCS_STRUCT *my_rcs, unsigned char ch){
    int		i_ret;
	
	my_rcs->rs422_config.ch = ch;
	my_rcs->rs422_config.baudrate = 38400;
	my_rcs->rs422_config.stop_bit = 1;
	
	my_rcs->driver_super.inter_face = RS422;
	
	my_rcs->driver_super.periodic_config.rx_header_size = sizeof(rcs_header);
	my_rcs->driver_super.periodic_config.rx_header = rcs_header;
	
	my_rcs->driver_super.periodic_config.rx_footer_size = sizeof(rcs_footer);
	my_rcs->driver_super.periodic_config.rx_footer = rcs_footer;
	
	my_rcs->driver_super.periodic_config.rx_frame_size = RCS_RX_FRAME_SIZE;
	
	my_rcs->driver_super.periodic_config.tx_frame_size = sizeof(rcs_tx_frame_periodic);
	my_rcs->driver_super.periodic_config.tx_frame = rcs_tx_frame_periodic;
	
	if((i_ret = DRIVER_Super_init(&(my_rcs->driver_super), &(my_rcs->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	return(0);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCS試験用のデバッグモードです。
 * 
 * デバッグコンソール上でRCSからのステータスを表示したり、RCSに対しコマンドを送信したりします。
 * @param なし
 * @return なし
 */
void Debug_RCS(void){
	extern RCS_STRUCT	rcs1;
	u_char				c;
	unsigned int	end_flg = 0;
	int				cnt = 0;
	int				debug_rcs_loop = 1;
	int				i_ret;
	unsigned int	tmp = 0;
	
	//	Channel Setting
	Printf("RCS Test \n");
	while(!end_flg){
		Printf("  Which channel (0-15) ?\n");
		ScanfUIntD( &tmp );
		if(tmp < 0 || tmp > 15){
			Printf("Illegal Ch Number\n");
		}else{
			end_flg = 1;
		}
	}
	end_flg = 0;
	
	i_ret = RCS_init(&rcs1, (unsigned char)tmp);
	if(i_ret != 0){
		Printf("RCS Init Error (%d)\n", i_ret);
		return;
	}
	
	Printf("============  1:Init     2:Preparation  =========\n");
	Printf("============  4:Start    8:Stop  ================\n");
	Printf("=============  q:Quit  ==========================\n");
	while(debug_rcs_loop){
		MilliSleep(5);
		
		i_ret = RCS_rec(&(rcs1));
		if(i_ret == 1){
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
			
			if(rcs1.flag.bit.vo_au == 0){
				Printf("VO-AU_flag:Close        ");
			}else if(rcs1.flag.bit.vo_au == 1){
				Printf("VO-AU_flag:Open_Wait    ");
			}else if(rcs1.flag.bit.vo_au == 2){
				Printf("VO-AU_flag:Opening      ");
			}else if(rcs1.flag.bit.vo_au == 3){
				Printf("VO-AU_flag:Open         ");
			}
			if(rcs1.flag.bit.vo_ad == 0){
				Printf("VO-AD_flag:Close        ");
			}else if(rcs1.flag.bit.vo_ad == 1){
				Printf("VO-AD_flag:Open_Wait    ");
			}else if(rcs1.flag.bit.vo_ad == 2){
				Printf("VO-AD_flag:Opening      ");
			}else if(rcs1.flag.bit.vo_ad == 3){
				Printf("VO-AD_flag:Open         ");
			}
			Printf("\n");
			if(rcs1.flag.bit.vo_bu == 0){
				Printf("VO-BU_flag:Close        ");
			}else if(rcs1.flag.bit.vo_bu == 1){
				Printf("VO-BU_flag:Open_Wait    ");
			}else if(rcs1.flag.bit.vo_bu == 2){
				Printf("VO-BU_flag:Opening      ");
			}else if(rcs1.flag.bit.vo_bu == 3){
				Printf("VO-BU_flag:Open         ");
			}
			if(rcs1.flag.bit.vo_bd == 0){
				Printf("VO-BD_flag:Close        ");
			}else if(rcs1.flag.bit.vo_bd == 1){
				Printf("VO-BD_flag:Open_Wait    ");
			}else if(rcs1.flag.bit.vo_bd == 2){
				Printf("VO-BD_flag:Opening      ");
			}else if(rcs1.flag.bit.vo_bd == 3){
				Printf("VO-BD_flag:Open         ");
			}
			Printf("\n");
			
			if(rcs1.status.bit.vo_au == 0){
				Printf("VO-AU_pin:Close    ");
			}else if(rcs1.status.bit.vo_au == 1){
				Printf("VO-AU_pin:Open     ");
			}
			if(rcs1.status.bit.vo_ad == 0){
				Printf("VO-AD_pin:Close    ");
			}else if(rcs1.status.bit.vo_ad == 1){
				Printf("VO-AD_pin:Open     ");
			}
			if(rcs1.status.bit.vo_bu == 0){
				Printf("VO-BU_pin:Close    ");
			}else if(rcs1.status.bit.vo_bu == 1){
				Printf("VO-BU_pin:Open     ");
			}
			if(rcs1.status.bit.vo_bd == 0){
				Printf("VO-BD_pin:Close    ");
			}else if(rcs1.status.bit.vo_bd == 1){
				Printf("VO-BD_pin:Open     ");
			}
			Printf("\n");
			if(rcs1.status.bit.flag_12v == 0){
				Printf("12V_flag:OFF    ");
			}else if(rcs1.status.bit.flag_12v == 1){
				Printf("12V_flag:ON     ");
			}
			if(rcs1.status.bit.pin_12v == 0){
				Printf("12V_pin:OFF    ");
			}else if(rcs1.status.bit.pin_12v == 1){
				Printf("12V_pin:ON     ");
			}
			Printf("Mode:L%d", rcs1.status.bit.mode);
			Printf("\n");
			
			if(rcs1.last_cmd == 0x01){
				Printf("LastCmd:Init           ");
			}else if(rcs1.last_cmd == 0x02){
				Printf("LastCmd:Preparation    ");
			}else if(rcs1.last_cmd == 0x04){
				Printf("LastCmd:Start          ");
			}else if(rcs1.last_cmd == 0x08){
				Printf("LastCmd:Stop           ");
			}else if(rcs1.last_cmd == 0x10){
				Printf("LastCmd:Tlm_Req        ");
			}else{
				Printf("LastCmd:?              ");
			}
			Printf("Ack:0x%02X", rcs1.ack);
			Printf("\n");
			
			Printf("Tank_reference_tempe:%5d         ", rcs1.tt0);
			Printf("Tank_relative_tempe:%5d", rcs1.tt1);
			Printf("\n");
			
			Printf("Thruster_reference_tempe:%5d     ", rcs1.tc0);
			Printf("Thruster_relative_tempe:%5d", rcs1.tc1);
			Printf("\n");
			
			Printf("Tank_pressure:%5d                ", rcs1.pt);
			Printf("Thruster_pressure:%5d", rcs1.pc);
			Printf("\n");
			
			Printf("Pressure gauge_PT_current:%5d    ", rcs1.i_pt);
			Printf("Pressure gauge_PC_current:%5d", rcs1.i_pc);
			Printf("\n");
			
		}
		
		if(cnt == 0){
			RCS_cycle(&(rcs1));
		}
		cnt++;
		cnt %= 1000;
		
		c = CheckChar();
		if(c == '1'){
			Printf("Send %d\n", RCS_initialize_command(&rcs1));
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
		}else if(c == '2'){
			Printf("  Valve Select (DEC)        Quit : >255\n");
			Printf(" -> ");
			ScanfUIntD( &tmp );
			if(tmp <= 0xFF){
				Printf("Send %d\n", RCS_injection_preparation(&rcs1, (unsigned char)tmp));
			}
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
		}else if(c == '4'){
			Printf("  Injection Time (DEC)        Quit : >255\n");
			Printf(" -> ");
			ScanfUIntD( &tmp );
			if(tmp <= 0xFF){
				Printf("Send %d\n", RCS_injection_start(&rcs1, (unsigned char)tmp));
			}
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
		}else if(c == '8'){
			Printf("Send %d\n", RCS_injection_stop(&rcs1));
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
		}else if(c == 'q' || c == 'Q'){
			debug_rcs_loop = 0;
		}
	}
	
	
	return;
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCSに対して定期コマンドを送信します。
 * @param RCS_STRUCT *my_rcs : 対象とするRCS構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_cycle() の戻り値を参照)
 */
int		RCS_cycle(RCS_STRUCT *my_rcs){
	int		i_ret;
	
		#ifdef	RCS_DEBUG
			Printf("RCS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_rcs->driver_super), &(my_rcs->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCSからのデータパケットを監視し、受信した内容を RCS_STRUCT に格納します。
 * 
 * 定期コマンド送信周期より早い周期で定期的に実行してください。
 * @note データパケットについては DRIVER_Super_rec() を使用してフレーム同期をとり、
 * フレーム同期がとれた場合に受信内容を RCS_STRUCT に格納します。
 * @param RCS_STRUCT *my_rcs : 対象とするRCS構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 1以外 : データが受信されなかった等(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
int		RCS_rec(RCS_STRUCT *my_rcs){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret == 1){
			#ifdef	RCS_DEBUG
				Printf("RCS: *** Frame ***\n");
			#endif
		RCS_Data_Conv(my_rcs);
	}
	
	return(i_ret);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCS構造体のデータをデバッグコンソール上に表示します。
 * 
 * @param RCS_STRUCT *my_rcs : 対象とするRCS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		RCS_debug_message(RCS_STRUCT* my_rcs){
	Printf("Mode: L%u  ", my_rcs->status.bit.mode);
	if(my_rcs->last_cmd == 0x01){
		Printf("LastCmd: Init  ");
	}else if(my_rcs->last_cmd == 0x02){
		Printf("LastCmd: Preparation  ");
	}else if(my_rcs->last_cmd == 0x04){
		Printf("LastCmd: Start  ");
	}else if(my_rcs->last_cmd == 0x08){
		Printf("LastCmd: Stop  ");
	}else if(my_rcs->last_cmd == 0x10){
		Printf("LastCmd: Tlm_Req  ");
	}else{
		Printf("LastCmd: ?  ");
	}
	
	DRIVER_Super_debug_message(&(my_rcs->driver_super));
	
	
	return(0);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCSの起動と初期設定を行うコマンドをRCSへ送信します。
 * 
 * @param RCS_STRUCT *my_rcs : 対象とするRCS構造体へのポインタ
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		RCS_initialize_command(RCS_STRUCT *my_rcs){
	int				i_ret;
	unsigned char	*p_tmp;
	
	
	p_tmp = (unsigned char *)rcs_header;
	rcs_tx_frame[0] = *(p_tmp + 0);
	rcs_tx_frame[1] = *(p_tmp + 1);
	
	rcs_tx_frame[2] = 0x01;	// パケット長(固定値)
	rcs_tx_frame[3] = 0x00;	// コンポID(固定値)
	rcs_tx_frame[4] = 0x01;	// コマンドHEX(初期化)
	rcs_tx_frame[5] = 0x00;	// コマンド引数(ダミー)
	
	p_tmp = (unsigned char *)rcs_footer;
	rcs_tx_frame[6] = *(p_tmp + 0);
	rcs_tx_frame[7] = *(p_tmp + 1);
	
	
	my_rcs->driver_super.non_periodic_config.tx_frame_size = RCS_TX_FRAME_SIZE;
	my_rcs->driver_super.non_periodic_config.tx_frame = rcs_tx_frame;
	
	my_rcs->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief 噴射準備コマンドをRCSへ送信します。
 * 
 * @param RCS_STRUCT *my_rcs : 対象とするRCS構造体へのポインタ
 * @param unsigned char valve : バルブ選択
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		RCS_injection_preparation(RCS_STRUCT *my_rcs, unsigned char valve){
	int				i_ret;
	unsigned char	*p_tmp;
	
	
	p_tmp = (unsigned char *)rcs_header;
	rcs_tx_frame[0] = *(p_tmp + 0);
	rcs_tx_frame[1] = *(p_tmp + 1);
	
	rcs_tx_frame[2] = 0x01;	// パケット長(固定値)
	rcs_tx_frame[3] = 0x00;	// コンポID(固定値)
	rcs_tx_frame[4] = 0x02;	// コマンドHEX(噴射準備)
	rcs_tx_frame[5] = valve;	// コマンド引数(バルブ選択)
	
	p_tmp = (unsigned char *)rcs_footer;
	rcs_tx_frame[6] = *(p_tmp + 0);
	rcs_tx_frame[7] = *(p_tmp + 1);
	
	
	my_rcs->driver_super.non_periodic_config.tx_frame_size = RCS_TX_FRAME_SIZE;
	my_rcs->driver_super.non_periodic_config.tx_frame = rcs_tx_frame;
	
	my_rcs->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief 噴射開始コマンドをRCSへ送信します。
 * 
 * @param RCS_STRUCT *my_rcs : 対象とするRCS構造体へのポインタ
 * @param unsigned char second : 噴射秒数
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		RCS_injection_start(RCS_STRUCT *my_rcs, unsigned char second){
	int				i_ret;
	unsigned char	*p_tmp;
	
	
	p_tmp = (unsigned char *)rcs_header;
	rcs_tx_frame[0] = *(p_tmp + 0);
	rcs_tx_frame[1] = *(p_tmp + 1);
	
	rcs_tx_frame[2] = 0x01;	// パケット長(固定値)
	rcs_tx_frame[3] = 0x00;	// コンポID(固定値)
	rcs_tx_frame[4] = 0x04;	// コマンドHEX(噴射開始)
	rcs_tx_frame[5] = second;	// コマンド引数(噴射秒数)
	
	p_tmp = (unsigned char *)rcs_footer;
	rcs_tx_frame[6] = *(p_tmp + 0);
	rcs_tx_frame[7] = *(p_tmp + 1);
	
	
	my_rcs->driver_super.non_periodic_config.tx_frame_size = RCS_TX_FRAME_SIZE;
	my_rcs->driver_super.non_periodic_config.tx_frame = rcs_tx_frame;
	
	my_rcs->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief 噴射停止コマンドをRCSへ送信します。
 * 
 * @param RCS_STRUCT *my_rcs : 対象とするRCS構造体へのポインタ
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		RCS_injection_stop(RCS_STRUCT *my_rcs){
	int				i_ret;
	unsigned char	*p_tmp;
	
	
	p_tmp = (unsigned char *)rcs_header;
	rcs_tx_frame[0] = *(p_tmp + 0);
	rcs_tx_frame[1] = *(p_tmp + 1);
	
	rcs_tx_frame[2] = 0x01;	// パケット長(固定値)
	rcs_tx_frame[3] = 0x00;	// コンポID(固定値)
	rcs_tx_frame[4] = 0x08;	// コマンドHEX(噴射停止)
	rcs_tx_frame[5] = 0x00;	// コマンド引数(ダミー)
	
	p_tmp = (unsigned char *)rcs_footer;
	rcs_tx_frame[6] = *(p_tmp + 0);
	rcs_tx_frame[7] = *(p_tmp + 1);
	
	
	my_rcs->driver_super.non_periodic_config.tx_frame_size = RCS_TX_FRAME_SIZE;
	my_rcs->driver_super.non_periodic_config.tx_frame = rcs_tx_frame;
	
	my_rcs->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}


//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof RCS_STRUCT
 * @private
 * @brief フレームデータをRCS構造体のデータ内容に変換します。
 * 
 * 工学値変換が必要な場合はここに書き込みます。
 * @param RCS_STRUCT *my_rcs : 対象とするRCS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		RCS_Data_Conv(RCS_STRUCT* my_rcs){
	/** @brief フレームデータのヘッダ分をオフセットしたポインタ*/
	unsigned char *rcs_rx_data = my_rcs->driver_super.periodic_rx_frame + sizeof(rcs_header);
	
	// パケット長(固定値) = *(rcs_rx_data + 0);
	// コンポID(固定値) = *(rcs_rx_data + 1);
	
	my_rcs->flag.byte = *(rcs_rx_data + 2);
	my_rcs->status.byte = *(rcs_rx_data + 3);
	
	my_rcs->last_cmd = *(rcs_rx_data + 4);
	my_rcs->ack = *(rcs_rx_data + 5);
	
	my_rcs->tt0 = ((*(rcs_rx_data + 6)) * 16) + (*(rcs_rx_data + 7));
	my_rcs->tt1 = ((*(rcs_rx_data + 8)) * 16) + (*(rcs_rx_data + 9));
	my_rcs->tc0 = ((*(rcs_rx_data + 10)) * 256) + (*(rcs_rx_data + 11));
	my_rcs->tc1 = ((*(rcs_rx_data + 12)) * 256) + (*(rcs_rx_data + 13));
	my_rcs->pt = ((*(rcs_rx_data + 14)) * 256) + (*(rcs_rx_data + 15));
	my_rcs->pc = ((*(rcs_rx_data + 16)) * 256) + (*(rcs_rx_data + 17));
	my_rcs->i_pt = ((*(rcs_rx_data + 18)) * 256) + (*(rcs_rx_data + 19));
	my_rcs->i_pc = ((*(rcs_rx_data + 20)) * 256) + (*(rcs_rx_data + 21));
	
	return (0);
}
