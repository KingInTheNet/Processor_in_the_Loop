/**
 * @file STT.c
 * @brief STTとのインターフェースモジュール群です。
 * 
 * STTインターフェースモジュールは、AxelSpace社AXELSTAR-2とのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.11.01
 */

#include "utility.h"	// Printf()使用時には必要

#include "STT.h"

//#define	STT_DEBUG


int				STT_Data_Conv(STT_STRUCT *my_stt);

#define STT_RX_FRAME_SIZE			241	/**< @brief 受信フレームの長さ(オートモード時)*/
//#define STT_RX_FRAME_SIZE			242	/**< @brief 受信フレームの長さ(オートモード時)*/

static unsigned char	stt_rx_header[4] = {'s', 't', '2', 'z'};	/**< @brief 受信フレームのヘッダ(オートモード時)*/

//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、 STT_STRUCT.driver_super に定期受信部のヘッダ,フッタ,フレームサイズ、定期コマンド発行部の情報を記録します。
 * @note STTインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param STT_STRUCT *my_stt : 初期化するSTT構造体へのポインタ
 * @param unsigned char ch : STTが接続されているUARTポート番号
 * @param unsigned short up_enable_bit : STTの「UP-ENABLE」ピンが接続されているDCポート番号
 * @return 0 : 正常終了
 * @return 100番台 : 異常終了(詳細は DRIVER_Super_init() の戻り値を参照)
 * @return 100000番台 : 異常終了(詳細は-100000して DC_init() の戻り値を参照)
 */
int		STT_init(STT_STRUCT* my_stt, unsigned char ch, unsigned short up_enable_bit){
    int		i_ret;
	
	my_stt->dc_config.ch_out = up_enable_bit;
	
	my_stt->rs422_config.ch = ch;
	my_stt->rs422_config.baudrate = 115200;
	my_stt->rs422_config.stop_bit = 1;
	
	my_stt->driver_super.inter_face = RS422;
	
	my_stt->driver_super.periodic_config.rx_header_size = sizeof(stt_rx_header);
	my_stt->driver_super.periodic_config.rx_header = stt_rx_header;
	
	my_stt->driver_super.periodic_config.rx_footer_size = 0;
	
	my_stt->driver_super.periodic_config.rx_frame_size = STT_RX_FRAME_SIZE;
	
	my_stt->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_stt->driver_super), &(my_stt->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	if((i_ret = DC_init(&(my_stt->dc_config))) != 0){
		return (100000 + i_ret);
	}
	
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTに対して定期コマンドを送信します。
 * 
 * 本STTは定期コマンド送信が不要なので、この関数は実行しても何も起きません
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_cycle() の戻り値を参照)
 */
int		STT_cycle(STT_STRUCT* my_stt){
	int		i_ret;
	
		#ifdef	STT_DEBUG
			Printf("STT: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_stt->driver_super), &(my_stt->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTからのデータパケットを監視し、受信した内容を STT_STRUCT に格納します。
 * 
 * STTのデータ出力周期である、1秒より早い周期で定期的に実行してください。
 * @note データパケットについては DRIVER_Super_rec() を使用してフレーム同期をとり、
 * フレーム同期がとれた場合に受信内容を STT_STRUCT に格納します。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 1以外 : データが受信されなかった等(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
int		STT_rec(STT_STRUCT* my_stt){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_stt->driver_super), &(my_stt->rs422_config));
	if(i_ret == 1){
			#ifdef	STT_DEBUG
				Printf("STT: *** Frame ***\n");
			#endif
		STT_Data_Conv(my_stt);
	}
	
	return(i_ret);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT構造体のデータをデバッグコンソール上に表示します。
 * 
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 */
int		STT_debug_message(STT_STRUCT* my_stt){
	Printf("Capt_ID:%u ", (unsigned int)my_stt->capture_id);
	Printf("Tempe:%f ", my_stt->master_imager_temperature);
	Printf("Quat[0]:%f ", my_stt->attitude[0]);
	Printf("Quat[1]:%f ", my_stt->attitude[1]);
	Printf("Quat[2]:%f ", my_stt->attitude[2]);
	Printf("Quat[3]:%f ", my_stt->attitude[3]);
	
	DRIVER_Super_debug_message(&(my_stt->driver_super));
	
	
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTを「オートモード」へ移行させる処理をする関数です。
 * 
 *  STT_Up_Enable_Idle() により、DC信号の「UP-ENABLE」ピンを"HIGH"にして「Idle State」に移行させ、
 * 「Get/Change Power State」コマンドを発行して「Capture State」に移行させ、
 * 「Change Output Mode」コマンドを発行して出力モードを変更させ、
 * 「Start/Stop Output」コマンドを発行して撮影を開始します。
 * @note aosc_superに非定期コマンド発行部と、そのコマンドに対するレスポンス受信部の情報を書き込み、
 *  DRIVER_Super_conf()を実行しています。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 1000番台 : STT_Up_Enable_Power_Down() での異常終了(詳細は-1000をして STT_Up_Enable_Power_Down() の戻り値を参照)
 * @return 2000番台 : STT_Up_Enable_Idle() での異常終了(詳細は-2000をして STT_Up_Enable_Idle() の戻り値を参照)
 * @return 3000番台 : STT_Change_Power_State_Capture() での異常終了(詳細は-3000をして STT_Change_Power_State_Capture() の戻り値を参照)
 * @return 4000番台 : STT_Change_Output_Mode() (1回目)での異常終了(詳細は-4000をして STT_Change_Output_Mode() の戻り値を参照)
 * @return 5000番台 : STT_Change_Output_Mode() (2回目)での異常終了(詳細は-5000をして STT_Change_Output_Mode() の戻り値を参照)
 * @return 6000番台 : STT_Start_Output() での異常終了(詳細は-6000をして STT_Start_Output() の戻り値を参照)
 */
int		STT_auto_mode(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	state = 0x00;
	
	i_ret = STT_Change_Output_Mode(my_stt, &state);
	if(i_ret != 0){	// Error
		
	}else if(state != 'm'){
		MilliSleep(100);	//100msec wait
		i_ret = STT_Change_Output_Mode(my_stt, &state);
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Change_Power_State_Idle(my_stt)) != 0){	// Error
		
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Up_Enable_Power_Down(my_stt)) != 0){
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Up_Enable_Power_Down +++\n");
			#endif
		return (1000 + i_ret);
	}
	MilliSleep(1000);	//1sec wait
	
	if((i_ret = STT_Up_Enable_Idle(my_stt)) != 0){
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Up_Enable_Idle +++\n");
			#endif
		return (2000 + i_ret);
	}
	MilliSleep(5000);	//5sec wait
	
	if((i_ret = STT_Change_Power_State_Capture(my_stt)) != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Power_State_Capture +++\n");
			#endif
		return (3000 + i_ret);
	}
	MilliSleep(100);	//100msec wait
	
	i_ret = STT_Change_Output_Mode(my_stt, &state);
	if(i_ret != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Output_Mode(2-1) +++\n");
			#endif
		return (4000 + i_ret);
	}else if((state != 'a') && (state != 'b')){
		MilliSleep(100);	//100msec wait
		i_ret = STT_Change_Output_Mode(my_stt, &state);
		if((state != 'a') && (state != 'b')){
				#ifdef	STT_DEBUG
					Printf("STT: +++ STT_Change_Output_Mode(2-2) +++\n");
				#endif
			return (5000 + i_ret);
		}
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Start_Output(my_stt)) != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Start_Output +++\n");
			#endif
		return (6000 + i_ret);
	}
	
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTを電源OFFできる状態にします。
 * 
 * 「Change Output Mode」コマンドを発行して出力モードを変更させ、
 * 「Get/Change Power State」コマンドを発行して「Idle State」に移行させ、
 *  STT_Up_Enable_Power_Down() により、DC信号の「UP-ENABLE」ピンを"LOW"にして、「Power-Down State」に移行させます。
 * @note aosc_superに非定期コマンド発行部と、そのコマンドに対するレスポンス受信部の情報を書き込み、
 *  DRIVER_Super_conf()を実行しています。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 1000番台 : STT_Change_Output_Mode() での異常終了(詳細は-1000をして STT_Change_Output_Mode() の戻り値を参照)
 * @return 2000番台 : STT_Change_Output_Mode() での異常終了(詳細は-2000をして STT_Change_Output_Mode() の戻り値を参照)
 * @return 3000番台 : STT_Change_Power_State_Capture() での異常終了(詳細は-3000をして STT_Change_Power_State_Capture() の戻り値を参照)
 * @return 4000番台 : STT_Up_Enable_Power_Down() での異常終了(詳細は-4000をして STT_Up_Enable_Power_Down() の戻り値を参照)
 */
int		STT_stop(STT_STRUCT* my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	dc_tx = 0;
	unsigned char	state = 0x00;
	
	i_ret = STT_Change_Output_Mode(my_stt, &state);
	if(i_ret != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Output_Mode +++\n");
			#endif
		return (1000 + i_ret);
	}else if(state != 'm'){
		i_ret = STT_Change_Output_Mode(my_stt, &state);
		MilliSleep(100);	//100msec wait
	}
	
	if(state != 'm'){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Output_Mode +++\n");
			#endif
		return (2000 + i_ret);
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Change_Power_State_Idle(my_stt)) != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Power_State_Idle +++\n");
			#endif
		return (3000 + i_ret);
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Up_Enable_Power_Down(my_stt)) != 0){
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Up_Enable_Power_Down +++\n");
			#endif
		return (4000 + i_ret);
	}
	
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへの「UP-ENABLE」ピンを"LOW"にして「Power-Down State」に移行する関数です。
 * 
 * DC信号の「UP-ENABLE」ピンを"LOW"にして「Power-Down State」に移行させます。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 上記以外 : DC_TX() での異常終了(詳細は DC_TX() の戻り値を参照)
 */
int		STT_Up_Enable_Power_Down(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	dc_tx = 0;
	
	
	if((i_ret = DC_TX(&(my_stt->dc_config), &dc_tx, sizeof(dc_tx))) != 0){
		return (i_ret);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへの「UP-ENABLE」ピンを"HIGH"にして「Idle State」に移行する関数です。
 * 
 * DC信号の「UP-ENABLE」ピンを"HIGH"にして「Idle State」に移行させます。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 上記以外 : DC_TX() での異常終了(詳細は DC_TX() の戻り値を参照)
 */
int		STT_Up_Enable_Idle(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	dc_tx = 1;
	
	
	if((i_ret = DC_TX(&(my_stt->dc_config), &dc_tx, sizeof(dc_tx))) != 0){
		return (i_ret);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get Temperature」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param float *image_sensor_board : イメージセンサ基板温度格納先へのポインタ
 * @param float *fpga : FPGA温度格納先へのポインタ
 * @param float *image_sensor : イメージセンサ温度格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_Temperature(STT_STRUCT *my_stt, float *image_sensor_board, float *fpga, float *image_sensor){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[4] = {'s', 't', '2', 0x02};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x02};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+12;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)image_sensor_board) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)image_sensor_board) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	*(((unsigned char *)image_sensor_board) + 2) = my_stt->driver_super.non_periodic_rx_frame[7];
	*(((unsigned char *)image_sensor_board) + 3) = my_stt->driver_super.non_periodic_rx_frame[8];
	
	*(((unsigned char *)fpga) + 0) = my_stt->driver_super.non_periodic_rx_frame[9];
	*(((unsigned char *)fpga) + 1) = my_stt->driver_super.non_periodic_rx_frame[10];
	*(((unsigned char *)fpga) + 2) = my_stt->driver_super.non_periodic_rx_frame[11];
	*(((unsigned char *)fpga) + 3) = my_stt->driver_super.non_periodic_rx_frame[12];
	
	*(((unsigned char *)image_sensor) + 0) = my_stt->driver_super.non_periodic_rx_frame[13];
	*(((unsigned char *)image_sensor) + 1) = my_stt->driver_super.non_periodic_rx_frame[14];
	*(((unsigned char *)image_sensor) + 2) = my_stt->driver_super.non_periodic_rx_frame[15];
	*(((unsigned char *)image_sensor) + 3) = my_stt->driver_super.non_periodic_rx_frame[16];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get/Change Power State - Capture State」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 * @return 30000番台 : 「Capture State」ではない。もしくは変な値が返ってきた。(詳細は-30000をして戻り値を参照)
 */
int		STT_Change_Power_State_Capture(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x03, 'c'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x03};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[5] != 'c'){
		return (30000 + my_stt->driver_super.non_periodic_rx_frame[5]);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get/Change Power State - Idle State」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 * @return 30000番台 : 「Idle State」ではない。もしくは変な値が返ってきた。(詳細は-30000をして戻り値を参照)
 */
int		STT_Change_Power_State_Idle(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x03, 'i'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x03};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[5] != 'i'){
		return (30000 + my_stt->driver_super.non_periodic_rx_frame[5]);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get Power State」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned char *state : 現在の電源状態格納先へのポインタ(格納値はAXELSTAR-2ユーザーズマニュアルの「Get/Change Power State」コマンドを参照)
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 * @return 30000番台 : 変な値が返ってきた。(詳細は-30000をして戻り値を参照)
 */
int		STT_Get_Power_State(STT_STRUCT *my_stt, unsigned char *state){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x03, 'g'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x03};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*state = my_stt->driver_super.non_periodic_rx_frame[5];
	
	if((*state != 'c') || (*state != 'i')){
		
		return (30000 + *state);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get Exposure Time」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned short *get_time : 現在の露光時間格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_Exposure_Time(STT_STRUCT *my_stt, unsigned short *get_time){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x06, 'g'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x06};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+2;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)get_time) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)get_time) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Set Exposure Time」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned short *get_time : 現在の露光時間格納先へのポインタ
 * @param unsigned short set_time : 設定する露光時間
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Set_Exposure_Time(STT_STRUCT *my_stt, unsigned short *get_time, unsigned short set_time){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[7] = {'s', 't', '2', 0x06, 's', 0x00, 0x00};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x06};
	
	tx[5] = *(((unsigned char*)&set_time) + 0);
	tx[6] = *(((unsigned char*)&set_time) + 1);
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+2;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)get_time) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)get_time) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「System Reset」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 */
int		STT_System_Reset(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[4] = {'s', 't', '2', 0x12};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Capture/PostProc - Capture Only」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Capture_Only(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x13, 'c'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x13};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Capture/PostProc - PostProc Only」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_PostProc_Only(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x13, 'p'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x13};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Capture/PostProc - Capture+PostProc」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Capture_And_PostProc(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x13, 'a'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x13};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get Detected Star Count」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned char *star_count : イメージセンサ基板温度格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_Detected_Star_Count(STT_STRUCT *my_stt, unsigned char *star_count){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[4] = {'s', 't', '2', 0x18};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x18};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+2;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)star_count) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)star_count) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get Detected Star Info」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned short read_index : 読み出しを開始する星のindex
 * @param unsigned char count : 読み出す星数
 * @param GET_DETECTED_STAR_INFO_COMMAND_STRUCT *info_data : 星の情報データ構造体の配列の格納先へのポインタ
 * @param unsigned int size : 星の情報データ構造体の配列の格納先のサイズ(上記第三引数をsizeof()してください)
 * @return 0 : 正常終了
 * @return 10000 : 第2引数エラー(64以下でない)
 * @return 10001 : データ格納先サイズ不足
 * @return 20000番台 : DRIVER_Super_conf() での異常終了(詳細は-20000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 30000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-30000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_Detected_Star_Info(STT_STRUCT *my_stt, unsigned short read_index, unsigned char count, GET_DETECTED_STAR_INFO_COMMAND_STRUCT *info_data, unsigned int size){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[7] = {'s', 't', '2', 0x19, 0x00, 0x00, 0x00};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x19};
	int		info_data_cnt;
	int		data_cnt;
	
	if(count > 64){
		return (10000);
	}
	
	if((count * sizeof(GET_DETECTED_STAR_INFO_COMMAND_STRUCT)) > size){
		return (10001);
	}
	
	tx[4] = *(((unsigned char*)&read_index) + 0);
	tx[5] = *(((unsigned char*)&read_index) + 1);
	tx[6] = *(((unsigned char*)&count) + 0);
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+(count * sizeof(GET_DETECTED_STAR_INFO_COMMAND_STRUCT));
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (20000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (30000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	data_cnt = 5;
	for(info_data_cnt = 0; info_data_cnt < count; info_data_cnt++){
		*(((unsigned char *)info_data->read_star_count) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->index) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->index) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->flag) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->hipparcos_id) + 0) = 0x00;
		*(((unsigned char *)info_data->hipparcos_id) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->hipparcos_id) + 2) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->hipparcos_id) + 3) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->area) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->area) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->luminance) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->luminance) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->luminance) + 2) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->luminance) + 3) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 2) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 3) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 4) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 5) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 6) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 7) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 2) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 3) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 4) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 5) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 6) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 7) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		
		info_data++;
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Set Approximate Attitude」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param double quaternion1 : Quaternion1
 * @param double quaternion2 : Quaternion2
 * @param double quaternion3 : Quaternion3
 * @param double quaternion4 : Quaternion4
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Set_Approximate_Attitude(STT_STRUCT *my_stt, double quaternion1, double quaternion2, double quaternion3, double quaternion4){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[36] = {'s', 't', '2', 0x1A,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x1A};
	
	double	*quaternion_p = (double *)(tx + 4);
	
	
	*quaternion_p = quaternion1;
	quaternion_p++;
	*quaternion_p = quaternion2;
	quaternion_p++;
	*quaternion_p = quaternion3;
	quaternion_p++;
	*quaternion_p = quaternion4;
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+0;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get Estimation Status」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param GET_ESTIMATION_STATUS_UNION *st_data : 姿勢推定ステータスデータ格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_Estimation_Status(STT_STRUCT *my_stt, GET_ESTIMATION_STATUS_UNION *st_data){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[4] = {'s', 't', '2', 0x1B};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x1B};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+4;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)st_data->byte) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)st_data->byte) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	*(((unsigned char *)st_data->byte) + 2) = my_stt->driver_super.non_periodic_rx_frame[7];
	*(((unsigned char *)st_data->byte) + 3) = my_stt->driver_super.non_periodic_rx_frame[8];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get Attitude」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param double *quaternion1 : Quaternion1格納先へのポインタ
 * @param double *quaternion2 : Quaternion2格納先へのポインタ
 * @param double *quaternion3 : Quaternion3格納先へのポインタ
 * @param double *quaternion4 : Quaternion4格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_Attitude(STT_STRUCT *my_stt, double *quaternion1, double *quaternion2, double *quaternion3, double *quaternion4){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[4] = {'s', 't', '2', 0x1D};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x1D};
	
	unsigned char	*quaternion_p;
	int		data_cnt;
	int		i;
	
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5 + (4 * sizeof(double));
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	data_cnt = 5;
	
	quaternion_p = (unsigned char*)quaternion1;
	for(i = 0; i < sizeof(double); i++){
		*quaternion_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	quaternion_p++;	data_cnt++;
	}
	
	quaternion_p = (unsigned char*)quaternion2;
	for(i = 0; i < sizeof(double); i++){
		*quaternion_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	quaternion_p++;	data_cnt++;
	}
	
	quaternion_p = (unsigned char*)quaternion3;
	for(i = 0; i < sizeof(double); i++){
		*quaternion_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	quaternion_p++;	data_cnt++;
	}
	
	quaternion_p = (unsigned char*)quaternion4;
	for(i = 0; i < sizeof(double); i++){
		*quaternion_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	quaternion_p++;	data_cnt++;
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get Error Covariance Matrix」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param double *ecm00 : error_covariance_matrix00格納先へのポインタ
 * @param double *ecm01 : error_covariance_matrix01格納先へのポインタ
 * @param double *ecm02 : error_covariance_matrix02格納先へのポインタ
 * @param double *ecm11 : error_covariance_matrix11格納先へのポインタ
 * @param double *ecm12 : error_covariance_matrix12格納先へのポインタ
 * @param double *ecm22 : error_covariance_matrix22格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_Error_Covariance_Matrix(STT_STRUCT *my_stt, double *ecm00, double *ecm01, double *ecm02, double *ecm11, double *ecm12, double *ecm22){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[4] = {'s', 't', '2', 0x1F};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x1F};
	
	unsigned char	*ecm_p;
	int		data_cnt;
	int		i;
	
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5 + (6 * sizeof(double));
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	data_cnt = 5;
	
	ecm_p = (unsigned char*)ecm00;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm01;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm02;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm11;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm12;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm22;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Change Output Mode」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned char *state : 現在の出力モード格納先へのポインタ(格納値はAXELSTAR-2ユーザーズマニュアルの「Change Output Mode」コマンドを参照)
 * @return '0' : 正常終了(詳細はAXELSTAR-2ユーザーズマニュアルの「Change Output Mode」コマンドを参照)
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 * @return 30000番台 : 変な値が返ってきた(-30000をして戻り値を参照)
 */
int		STT_Change_Output_Mode(STT_STRUCT *my_stt, unsigned char *state){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[4] = {'s', 't', '2', 0x21};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x21};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*state = my_stt->driver_super.non_periodic_rx_frame[5];
	
	if(*state != 'a' && *state != 'b' && *state != 'm'){
		return (30000 + *state);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get SEU Error Correction Count」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned short *seu_error_count : SEUエラー自動修正カウント値格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_SEU_Error_Correction_Count(STT_STRUCT *my_stt, unsigned short *seu_error_count){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[4] = {'s', 't', '2', 0x26};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x26};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+2;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)seu_error_count) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)seu_error_count) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get/Clear Error - Get Error」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned char *error : エラー状態値格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_Error(STT_STRUCT *my_stt, unsigned char *error){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x27, 'g'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x27};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)error) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get/Clear Error - Clear Error」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned char *error : エラー状態値格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Clear_Error(STT_STRUCT *my_stt, unsigned char *error){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x27, 'c'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x27};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)error) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get/Set Output Interval - Get Output Interval」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned char *interval : 出力周期取得値格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Get_Output_Interval(STT_STRUCT *my_stt, unsigned char *interval){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[6] = {'s', 't', '2', 0x28, 'g', 0x00};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x28};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)interval) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Get/Set Output Interval - Set Output Interval」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @param unsigned char set_interval : 出力周期設定値
 * @param unsigned char *interval : 出力周期取得値格納先へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 20000番台 : STT内でのエラー(コマンド送受信自体はOK)(詳細は-20000をしてAXELSTAR-2ユーザーズマニュアルの表8.4を参照)
 */
int		STT_Set_Output_Interval(STT_STRUCT *my_stt, unsigned char set_interval, unsigned char *interval){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[6] = {'s', 't', '2', 0x28, 's', 0x00};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x28};
	
	tx[5] = set_interval;
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)interval) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Start Output」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 */
int		STT_Start_Output(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x2B, 1};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STTへ「Stop Output」コマンドを発行する関数です。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 * @return 10000番台 : DRIVER_Super_conf() での異常終了(詳細は-10000をして DRIVER_Super_conf() の戻り値を参照)
 */
int		STT_Stop_Output(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief 戻り値格納*/
	unsigned char	tx[5] = {'s', 't', '2', 0x2B, 0};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	return (0);
}


//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof STT_STRUCT
 * @private
 * @brief フレームデータをSTT構造体のデータ内容に変換します。
 * 
 * 工学値変換が必要な場合はここに書き込みます。
 * @param STT_STRUCT *my_stt : 対象とするSTT構造体へのポインタ
 * @return 0 : 正常終了
 */
int		STT_Data_Conv(STT_STRUCT *my_stt){
	/** @brief フレームデータのヘッダ分をオフセットしたポインタ*/
	unsigned char *stt_rx_data = my_stt->driver_super.periodic_rx_frame + sizeof(stt_rx_header);
	
	*((unsigned char *)(&(my_stt->capture_id)) + 0) = *(stt_rx_data + 0);
	*((unsigned char *)(&(my_stt->capture_id)) + 1) = *(stt_rx_data + 1);
	
	*((unsigned char *)(&(my_stt->integration_state.byte)) + 0) = *(stt_rx_data + 2);
	*((unsigned char *)(&(my_stt->integration_state.byte)) + 1) = *(stt_rx_data + 3);
	
	*((unsigned char *)(&(my_stt->attitude[0])) + 0) = *(stt_rx_data + 4);
	*((unsigned char *)(&(my_stt->attitude[0])) + 1) = *(stt_rx_data + 5);
	*((unsigned char *)(&(my_stt->attitude[0])) + 2) = *(stt_rx_data + 6);
	*((unsigned char *)(&(my_stt->attitude[0])) + 3) = *(stt_rx_data + 7);
	*((unsigned char *)(&(my_stt->attitude[0])) + 4) = *(stt_rx_data + 8);
	*((unsigned char *)(&(my_stt->attitude[0])) + 5) = *(stt_rx_data + 9);
	*((unsigned char *)(&(my_stt->attitude[0])) + 6) = *(stt_rx_data + 10);
	*((unsigned char *)(&(my_stt->attitude[0])) + 7) = *(stt_rx_data + 11);
	
	*((unsigned char *)(&(my_stt->attitude[1])) + 0) = *(stt_rx_data + 12);
	*((unsigned char *)(&(my_stt->attitude[1])) + 1) = *(stt_rx_data + 13);
	*((unsigned char *)(&(my_stt->attitude[1])) + 2) = *(stt_rx_data + 14);
	*((unsigned char *)(&(my_stt->attitude[1])) + 3) = *(stt_rx_data + 15);
	*((unsigned char *)(&(my_stt->attitude[1])) + 4) = *(stt_rx_data + 16);
	*((unsigned char *)(&(my_stt->attitude[1])) + 5) = *(stt_rx_data + 17);
	*((unsigned char *)(&(my_stt->attitude[1])) + 6) = *(stt_rx_data + 18);
	*((unsigned char *)(&(my_stt->attitude[1])) + 7) = *(stt_rx_data + 19);
	
	*((unsigned char *)(&(my_stt->attitude[2])) + 0) = *(stt_rx_data + 20);
	*((unsigned char *)(&(my_stt->attitude[2])) + 1) = *(stt_rx_data + 21);
	*((unsigned char *)(&(my_stt->attitude[2])) + 2) = *(stt_rx_data + 22);
	*((unsigned char *)(&(my_stt->attitude[2])) + 3) = *(stt_rx_data + 23);
	*((unsigned char *)(&(my_stt->attitude[2])) + 4) = *(stt_rx_data + 24);
	*((unsigned char *)(&(my_stt->attitude[2])) + 5) = *(stt_rx_data + 25);
	*((unsigned char *)(&(my_stt->attitude[2])) + 6) = *(stt_rx_data + 26);
	*((unsigned char *)(&(my_stt->attitude[2])) + 7) = *(stt_rx_data + 27);
	
	*((unsigned char *)(&(my_stt->attitude[3])) + 0) = *(stt_rx_data + 28);
	*((unsigned char *)(&(my_stt->attitude[3])) + 1) = *(stt_rx_data + 29);
	*((unsigned char *)(&(my_stt->attitude[3])) + 2) = *(stt_rx_data + 30);
	*((unsigned char *)(&(my_stt->attitude[3])) + 3) = *(stt_rx_data + 31);
	*((unsigned char *)(&(my_stt->attitude[3])) + 4) = *(stt_rx_data + 32);
	*((unsigned char *)(&(my_stt->attitude[3])) + 5) = *(stt_rx_data + 33);
	*((unsigned char *)(&(my_stt->attitude[3])) + 6) = *(stt_rx_data + 34);
	*((unsigned char *)(&(my_stt->attitude[3])) + 7) = *(stt_rx_data + 35);
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 0) = *(stt_rx_data + 36);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 1) = *(stt_rx_data + 37);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 2) = *(stt_rx_data + 38);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 3) = *(stt_rx_data + 39);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 4) = *(stt_rx_data + 40);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 5) = *(stt_rx_data + 41);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 6) = *(stt_rx_data + 42);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 7) = *(stt_rx_data + 43);
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 0) = *(stt_rx_data + 44);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 1) = *(stt_rx_data + 45);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 2) = *(stt_rx_data + 46);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 3) = *(stt_rx_data + 47);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 4) = *(stt_rx_data + 48);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 5) = *(stt_rx_data + 49);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 6) = *(stt_rx_data + 50);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 7) = *(stt_rx_data + 51);
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 0) = *(stt_rx_data + 52);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 1) = *(stt_rx_data + 53);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 2) = *(stt_rx_data + 54);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 3) = *(stt_rx_data + 55);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 4) = *(stt_rx_data + 56);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 5) = *(stt_rx_data + 57);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 6) = *(stt_rx_data + 58);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 7) = *(stt_rx_data + 59);
	
	my_stt->error_covariance_matrix[1][0] = my_stt->error_covariance_matrix[0][1];
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 0) = *(stt_rx_data + 60);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 1) = *(stt_rx_data + 61);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 2) = *(stt_rx_data + 62);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 3) = *(stt_rx_data + 63);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 4) = *(stt_rx_data + 64);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 5) = *(stt_rx_data + 65);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 6) = *(stt_rx_data + 66);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 7) = *(stt_rx_data + 67);
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 0) = *(stt_rx_data + 68);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 1) = *(stt_rx_data + 69);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 2) = *(stt_rx_data + 70);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 3) = *(stt_rx_data + 71);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 4) = *(stt_rx_data + 72);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 5) = *(stt_rx_data + 73);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 6) = *(stt_rx_data + 74);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 7) = *(stt_rx_data + 75);
	
	my_stt->error_covariance_matrix[2][0] = my_stt->error_covariance_matrix[0][2];
	
	my_stt->error_covariance_matrix[2][1] = my_stt->error_covariance_matrix[1][2];
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 0) = *(stt_rx_data + 76);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 1) = *(stt_rx_data + 77);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 2) = *(stt_rx_data + 78);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 3) = *(stt_rx_data + 79);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 4) = *(stt_rx_data + 80);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 5) = *(stt_rx_data + 81);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 6) = *(stt_rx_data + 82);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 7) = *(stt_rx_data + 83);
	
	*((unsigned char *)(&(my_stt->master_imager_temperature)) + 0) = *(stt_rx_data + 84);
	*((unsigned char *)(&(my_stt->master_imager_temperature)) + 1) = *(stt_rx_data + 85);
	*((unsigned char *)(&(my_stt->master_imager_temperature)) + 2) = *(stt_rx_data + 86);
	*((unsigned char *)(&(my_stt->master_imager_temperature)) + 3) = *(stt_rx_data + 87);
	
	*((unsigned char *)(&(my_stt->master_detected_star_count)) + 0) = *(stt_rx_data + 88);
	//*((unsigned char *)(&(my_stt->master_detected_star_count)) + 1) = *(stt_rx_data + 89);
	
	if(my_stt->master_detected_star_count > 0){
		*((unsigned char *)(&(my_stt->master_star_info[0].hipparcos_id)) + 0) = *(stt_rx_data + 89);
		*((unsigned char *)(&(my_stt->master_star_info[0].hipparcos_id)) + 1) = *(stt_rx_data + 90);
		*((unsigned char *)(&(my_stt->master_star_info[0].hipparcos_id)) + 2) = *(stt_rx_data + 91);
		*((unsigned char *)(&(my_stt->master_star_info[0].hipparcos_id)) + 3) = *(stt_rx_data + 92);
		
		*((unsigned char *)(&(my_stt->master_star_info[0].luminance)) + 0) = *(stt_rx_data + 93);
		*((unsigned char *)(&(my_stt->master_star_info[0].luminance)) + 1) = *(stt_rx_data + 94);
		*((unsigned char *)(&(my_stt->master_star_info[0].luminance)) + 2) = *(stt_rx_data + 95);
		*((unsigned char *)(&(my_stt->master_star_info[0].luminance)) + 3) = *(stt_rx_data + 96);
		
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 0) = *(stt_rx_data + 97);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 1) = *(stt_rx_data + 98);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 2) = *(stt_rx_data + 99);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 3) = *(stt_rx_data + 100);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 4) = *(stt_rx_data + 101);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 5) = *(stt_rx_data + 102);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 6) = *(stt_rx_data + 103);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 7) = *(stt_rx_data + 104);
		
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 0) = *(stt_rx_data + 105);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 1) = *(stt_rx_data + 106);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 2) = *(stt_rx_data + 107);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 3) = *(stt_rx_data + 108);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 4) = *(stt_rx_data + 109);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 5) = *(stt_rx_data + 110);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 6) = *(stt_rx_data + 111);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 7) = *(stt_rx_data + 112);
	}else{
		my_stt->master_star_info[0].hipparcos_id = 0;
		my_stt->master_star_info[0].luminance = 0;
		my_stt->master_star_info[0].tan_azimuth = 0;
		my_stt->master_star_info[0].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 1){
		*((unsigned char *)(&(my_stt->master_star_info[1].hipparcos_id)) + 0) = *(stt_rx_data + 113);
		*((unsigned char *)(&(my_stt->master_star_info[1].hipparcos_id)) + 1) = *(stt_rx_data + 114);
		*((unsigned char *)(&(my_stt->master_star_info[1].hipparcos_id)) + 2) = *(stt_rx_data + 115);
		*((unsigned char *)(&(my_stt->master_star_info[1].hipparcos_id)) + 3) = *(stt_rx_data + 116);
		
		*((unsigned char *)(&(my_stt->master_star_info[1].luminance)) + 0) = *(stt_rx_data + 117);
		*((unsigned char *)(&(my_stt->master_star_info[1].luminance)) + 1) = *(stt_rx_data + 118);
		*((unsigned char *)(&(my_stt->master_star_info[1].luminance)) + 2) = *(stt_rx_data + 119);
		*((unsigned char *)(&(my_stt->master_star_info[1].luminance)) + 3) = *(stt_rx_data + 120);
		
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 0) = *(stt_rx_data + 121);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 1) = *(stt_rx_data + 122);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 2) = *(stt_rx_data + 123);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 3) = *(stt_rx_data + 124);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 4) = *(stt_rx_data + 125);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 5) = *(stt_rx_data + 126);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 6) = *(stt_rx_data + 127);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 7) = *(stt_rx_data + 128);
		
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 0) = *(stt_rx_data + 129);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 1) = *(stt_rx_data + 130);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 2) = *(stt_rx_data + 131);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 3) = *(stt_rx_data + 132);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 4) = *(stt_rx_data + 133);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 5) = *(stt_rx_data + 134);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 6) = *(stt_rx_data + 135);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 7) = *(stt_rx_data + 136);
	}else{
		my_stt->master_star_info[1].hipparcos_id = 0;
		my_stt->master_star_info[1].luminance = 0;
		my_stt->master_star_info[1].tan_azimuth = 0;
		my_stt->master_star_info[1].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 2){
		*((unsigned char *)(&(my_stt->master_star_info[2].hipparcos_id)) + 0) = *(stt_rx_data + 137);
		*((unsigned char *)(&(my_stt->master_star_info[2].hipparcos_id)) + 1) = *(stt_rx_data + 138);
		*((unsigned char *)(&(my_stt->master_star_info[2].hipparcos_id)) + 2) = *(stt_rx_data + 139);
		*((unsigned char *)(&(my_stt->master_star_info[2].hipparcos_id)) + 3) = *(stt_rx_data + 140);
		
		*((unsigned char *)(&(my_stt->master_star_info[2].luminance)) + 0) = *(stt_rx_data + 141);
		*((unsigned char *)(&(my_stt->master_star_info[2].luminance)) + 1) = *(stt_rx_data + 142);
		*((unsigned char *)(&(my_stt->master_star_info[2].luminance)) + 2) = *(stt_rx_data + 143);
		*((unsigned char *)(&(my_stt->master_star_info[2].luminance)) + 3) = *(stt_rx_data + 144);
		
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 0) = *(stt_rx_data + 145);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 1) = *(stt_rx_data + 146);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 2) = *(stt_rx_data + 147);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 3) = *(stt_rx_data + 148);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 4) = *(stt_rx_data + 149);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 5) = *(stt_rx_data + 150);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 6) = *(stt_rx_data + 151);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 7) = *(stt_rx_data + 152);
		
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 0) = *(stt_rx_data + 153);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 1) = *(stt_rx_data + 154);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 2) = *(stt_rx_data + 155);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 3) = *(stt_rx_data + 156);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 4) = *(stt_rx_data + 157);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 5) = *(stt_rx_data + 158);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 6) = *(stt_rx_data + 159);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 7) = *(stt_rx_data + 160);
	}else{
		my_stt->master_star_info[2].hipparcos_id = 0;
		my_stt->master_star_info[2].luminance = 0;
		my_stt->master_star_info[2].tan_azimuth = 0;
		my_stt->master_star_info[2].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 3){
		*((unsigned char *)(&(my_stt->master_star_info[3].hipparcos_id)) + 0) = *(stt_rx_data + 161);
		*((unsigned char *)(&(my_stt->master_star_info[3].hipparcos_id)) + 1) = *(stt_rx_data + 162);
		*((unsigned char *)(&(my_stt->master_star_info[3].hipparcos_id)) + 2) = *(stt_rx_data + 163);
		*((unsigned char *)(&(my_stt->master_star_info[3].hipparcos_id)) + 3) = *(stt_rx_data + 164);
		
		*((unsigned char *)(&(my_stt->master_star_info[3].luminance)) + 0) = *(stt_rx_data + 165);
		*((unsigned char *)(&(my_stt->master_star_info[3].luminance)) + 1) = *(stt_rx_data + 166);
		*((unsigned char *)(&(my_stt->master_star_info[3].luminance)) + 2) = *(stt_rx_data + 167);
		*((unsigned char *)(&(my_stt->master_star_info[3].luminance)) + 3) = *(stt_rx_data + 168);
		
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 0) = *(stt_rx_data + 169);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 1) = *(stt_rx_data + 170);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 2) = *(stt_rx_data + 171);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 3) = *(stt_rx_data + 172);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 4) = *(stt_rx_data + 173);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 5) = *(stt_rx_data + 174);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 6) = *(stt_rx_data + 175);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 7) = *(stt_rx_data + 176);
		
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 0) = *(stt_rx_data + 177);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 1) = *(stt_rx_data + 178);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 2) = *(stt_rx_data + 179);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 3) = *(stt_rx_data + 180);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 4) = *(stt_rx_data + 181);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 5) = *(stt_rx_data + 182);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 6) = *(stt_rx_data + 183);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 7) = *(stt_rx_data + 184);
	}else{
		my_stt->master_star_info[3].hipparcos_id = 0;
		my_stt->master_star_info[3].luminance = 0;
		my_stt->master_star_info[3].tan_azimuth = 0;
		my_stt->master_star_info[3].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 4){
		*((unsigned char *)(&(my_stt->master_star_info[4].hipparcos_id)) + 0) = *(stt_rx_data + 185);
		*((unsigned char *)(&(my_stt->master_star_info[4].hipparcos_id)) + 1) = *(stt_rx_data + 186);
		*((unsigned char *)(&(my_stt->master_star_info[4].hipparcos_id)) + 2) = *(stt_rx_data + 187);
		*((unsigned char *)(&(my_stt->master_star_info[4].hipparcos_id)) + 3) = *(stt_rx_data + 188);
		
		*((unsigned char *)(&(my_stt->master_star_info[4].luminance)) + 0) = *(stt_rx_data + 189);
		*((unsigned char *)(&(my_stt->master_star_info[4].luminance)) + 1) = *(stt_rx_data + 190);
		*((unsigned char *)(&(my_stt->master_star_info[4].luminance)) + 2) = *(stt_rx_data + 191);
		*((unsigned char *)(&(my_stt->master_star_info[4].luminance)) + 3) = *(stt_rx_data + 192);
		
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 0) = *(stt_rx_data + 193);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 1) = *(stt_rx_data + 194);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 2) = *(stt_rx_data + 195);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 3) = *(stt_rx_data + 196);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 4) = *(stt_rx_data + 197);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 5) = *(stt_rx_data + 198);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 6) = *(stt_rx_data + 199);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 7) = *(stt_rx_data + 200);
		
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 0) = *(stt_rx_data + 201);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 1) = *(stt_rx_data + 202);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 2) = *(stt_rx_data + 203);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 3) = *(stt_rx_data + 204);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 4) = *(stt_rx_data + 205);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 5) = *(stt_rx_data + 206);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 6) = *(stt_rx_data + 207);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 7) = *(stt_rx_data + 208);
	}else{
		my_stt->master_star_info[4].hipparcos_id = 0;
		my_stt->master_star_info[4].luminance = 0;
		my_stt->master_star_info[4].tan_azimuth = 0;
		my_stt->master_star_info[4].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 5){
		*((unsigned char *)(&(my_stt->master_star_info[5].hipparcos_id)) + 0) = *(stt_rx_data + 209);
		*((unsigned char *)(&(my_stt->master_star_info[5].hipparcos_id)) + 1) = *(stt_rx_data + 210);
		*((unsigned char *)(&(my_stt->master_star_info[5].hipparcos_id)) + 2) = *(stt_rx_data + 211);
		*((unsigned char *)(&(my_stt->master_star_info[5].hipparcos_id)) + 3) = *(stt_rx_data + 212);
		
		*((unsigned char *)(&(my_stt->master_star_info[5].luminance)) + 0) = *(stt_rx_data + 213);
		*((unsigned char *)(&(my_stt->master_star_info[5].luminance)) + 1) = *(stt_rx_data + 214);
		*((unsigned char *)(&(my_stt->master_star_info[5].luminance)) + 2) = *(stt_rx_data + 215);
		*((unsigned char *)(&(my_stt->master_star_info[5].luminance)) + 3) = *(stt_rx_data + 216);
		
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 0) = *(stt_rx_data + 217);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 1) = *(stt_rx_data + 218);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 2) = *(stt_rx_data + 219);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 3) = *(stt_rx_data + 220);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 4) = *(stt_rx_data + 221);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 5) = *(stt_rx_data + 222);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 6) = *(stt_rx_data + 223);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 7) = *(stt_rx_data + 224);
		
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 0) = *(stt_rx_data + 225);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 1) = *(stt_rx_data + 226);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 2) = *(stt_rx_data + 227);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 3) = *(stt_rx_data + 228);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 4) = *(stt_rx_data + 229);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 5) = *(stt_rx_data + 230);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 6) = *(stt_rx_data + 231);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 7) = *(stt_rx_data + 232);
	}else{
		my_stt->master_star_info[5].hipparcos_id = 0;
		my_stt->master_star_info[5].luminance = 0;
		my_stt->master_star_info[5].tan_azimuth = 0;
		my_stt->master_star_info[5].tan_elevation = 0;
	}
	
	*((unsigned char *)(&(my_stt->master_estimation_status.byte)) + 0) = *(stt_rx_data + 233);
	*((unsigned char *)(&(my_stt->master_estimation_status.byte)) + 1) = *(stt_rx_data + 234);
	*((unsigned char *)(&(my_stt->master_estimation_status.byte)) + 2) = *(stt_rx_data + 235);
	*((unsigned char *)(&(my_stt->master_estimation_status.byte)) + 3) = *(stt_rx_data + 236);
	
	return(0);
}
