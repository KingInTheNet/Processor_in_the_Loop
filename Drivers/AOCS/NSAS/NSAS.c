/**
 * @file NSAS.c
 * @brief NSASとのインターフェースモジュール群です。
 * 
 * NSASインターフェースモジュールは、AxelSpace社AxelSunとのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2013.03.09
 */

#include "utility.h"	// Printf()使用時には必要

#include "../../../../Port_Config.h"		//デバッグモードには必要

#include "NSAS.h"

//#define	NSAS_DEBUG


int		NSAS_Data_Conv(NSAS_STRUCT *my_nsas);

static unsigned int		nsas_dummy1;
static unsigned char	nsas_cmd_data_req_angle[3] = {0xC2, 0x00, 0x0D};	/**< @brief 角度出力データリクエストコマンド*/
static unsigned int		nsas_dummy2;
static unsigned char	nsas_cmd_data_req[3] = {0xC2, 0x01, 0x0D};	/**< @brief ベクトル出力データリクエストコマンド*/

/** @brief 角度出力データパケットについて、フレームの長さを定義(旧)*/
#define	NSAS_RX_FRAME_SIZE_ANGLE_OLD		23	// HEADER 2 + ERROR CODE 1 + PACKET DATA 18 + FOOTER 2 = 23
/** @brief 角度出力データパケットについて、フレームの長さを定義(新)*/
#define	NSAS_RX_FRAME_SIZE_ANGLE_NEW		13	// HEADER 2 + ERROR CODE 1 + PACKET DATA 8 + FOOTER 2 = 13
/** @brief ベクトル出力データパケットについて、フレームの長さを定義*/
#define	NSAS_RX_FRAME_SIZE_VECTOR		27	// HEADER 2 + ERROR CODE 1 + PACKET DATA 22 + FOOTER 2 = 27

static unsigned char	nsas_rx_header[2] = {0x02, 0xC2};	/**< @brief 受信フレームのヘッダ*/
static unsigned char	nsas_rx_footer[2] = {0x0D, 0x0A};	/**< @brief 受信フレームのフッタ*/

//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSAS構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、 NSAS_STRUCT.driver_super に定期受信部のヘッダ,フッタ,フレームサイズ、定期コマンド発行部の情報を記録します。
 * また、初期化と同時に、NSASに対して出力を「標準出力」のみにするようにコマンドを発行します。
 * @note NSASインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param NSAS_STRUCT *my_nsas : 初期化するNSAS構造体へのポインタ
 * @param unsigned char ch : NSASが接続されているUARTポート番号
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_init() の戻り値を参照)
 */
int		NSAS_init(NSAS_STRUCT *my_nsas, unsigned char ch){
    int		i_ret;
	
	
	//if(ch == NSAS1_CH){	//新版
		my_nsas->rs422_config.ch = ch;
		my_nsas->rs422_config.baudrate = 38400;
		my_nsas->rs422_config.stop_bit = 1;
		
		my_nsas->driver_super.inter_face = RS422;
		
		my_nsas->driver_super.periodic_config.rx_header_size = sizeof(nsas_rx_header);
		my_nsas->driver_super.periodic_config.rx_header = nsas_rx_header;
		
		my_nsas->driver_super.periodic_config.rx_footer_size = sizeof(nsas_rx_footer);
		my_nsas->driver_super.periodic_config.rx_footer = nsas_rx_footer;
		
		my_nsas->driver_super.periodic_config.rx_frame_size = NSAS_RX_FRAME_SIZE_ANGLE_NEW;
		
		my_nsas->driver_super.periodic_config.tx_frame_size = sizeof(nsas_cmd_data_req_angle);
		my_nsas->driver_super.periodic_config.tx_frame = nsas_cmd_data_req_angle;
		
		if((i_ret = DRIVER_Super_init(&(my_nsas->driver_super), &(my_nsas->rs422_config))) != 0){	// Error
			return(i_ret);
		}
	/*}else{	//旧版
		my_nsas->rs422_config.ch = ch;
		my_nsas->rs422_config.baudrate = 38400;
		my_nsas->rs422_config.stop_bit = 1;
		
		my_nsas->driver_super.inter_face = RS422;
		
		my_nsas->driver_super.periodic_config.rx_header_size = sizeof(nsas_rx_header);
		my_nsas->driver_super.periodic_config.rx_header = nsas_rx_header;
		
		my_nsas->driver_super.periodic_config.rx_footer_size = sizeof(nsas_rx_footer);
		my_nsas->driver_super.periodic_config.rx_footer = nsas_rx_footer;
		
		my_nsas->driver_super.periodic_config.rx_frame_size = NSAS_RX_FRAME_SIZE_ANGLE_OLD;
		
		my_nsas->driver_super.periodic_config.tx_frame_size = sizeof(nsas_cmd_data_req_angle);
		my_nsas->driver_super.periodic_config.tx_frame = nsas_cmd_data_req_angle;
		
		if((i_ret = DRIVER_Super_init(&(my_nsas->driver_super), &(my_nsas->rs422_config))) != 0){	// Error
			return(i_ret);
		}
	}
	*/
	
	
	return(0);
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSAS試験用のデバッグモードです。
 * 
 * デバッグコンソール上で、NSASに対しゲイン設定コマンドを送信します。
 * @param なし
 * @return なし
 */
void		Debug_NSAS_gain_set(void){
	extern NSAS_STRUCT	nsas1, nsas2, nsas3;
	NSAS_STRUCT			*nsasx_p;
	int				i_ret;
	unsigned int	end_flg = 0;
	unsigned int	tmp = 0;
	unsigned char	ch = 0;
	unsigned char	ope = 0;
	unsigned char	gain = 0;
	int				ret = 0;
	
	while(1){
		Printf("\nNSAS Gain Set \n");
		while(!end_flg){
			Printf("  Which NSAS (1-3)?    99:end\n");
			ScanfUIntD( &tmp );
			if(tmp == 99){
				return;
			}
			if(tmp < 1 || tmp > 3){
				Printf("Illegal NSAS Number\n");
			}else{
				end_flg = 1;
			}
		}
		end_flg = 0;
		
		switch(tmp){
			case 1:
				nsasx_p = &nsas1;
				ch = NSAS1_CH;
			break;
			
			case 2:
				nsasx_p = &nsas2;
				ch = NSAS2_CH;
			break;
			
			case 3:
				nsasx_p = &nsas3;
				ch = NSAS3_CH;
			break;
			
			default:
			break;
		}
		
		i_ret = NSAS_init(nsasx_p, ch);
		if(i_ret != 0){
			Printf("NSAS Init Error (%d)\n", i_ret);
			return;
		}
		
		while(!end_flg){
			Printf(" Gain Control?  0:OFF 1:ON\n");
			ScanfUIntD( &tmp );
			if(tmp == 0 || tmp == 1){
				ope = (unsigned char)tmp;
				end_flg = 1;
			}
		}
		end_flg = 0;
		
		while(!end_flg){
			Printf(" Gain? (0-255)\n");
			ScanfUIntD( &tmp );
			if(tmp >= 0 || tmp <= 255){
				gain = (unsigned char)tmp;
				end_flg = 1;
			}
		}
		end_flg = 0;
		
		ret = NSAS_gain(nsasx_p, ope, gain);
		if(ret == 0){
			Printf("Time Out\n");
		}else if(ret == 202){
			Printf("NSAS Rx OK - Data Error\n");
		}else if(ret == 201){
			Printf("NSAS Rx OK - Set Gain Error\n");
		}else if(ret < 0){
			Printf("Rx Data Error ");
			if(ret < -300){
				Printf("in %d byte (Footer)\n", (-ret) - 300);
			}else{
				Printf("in %d byte (Header)\n", (-ret) - 100);
			}
		}else if(ret == 1){
			Printf("Done\n");
		}else{
			Printf("?\n");
		}
	}
	return;
	
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSASに対して定期コマンドを送信します。
 * @param NSAS_STRUCT *my_nsas : 対象とするNSAS構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_cycle() の戻り値を参照)
 */
int		NSAS_cycle(NSAS_STRUCT *my_nsas){
	int		i_ret;
	
		#ifdef	NSAS_DEBUG
			Printf("NSAS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_nsas->driver_super), &(my_nsas->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSASからのデータパケットを監視し、受信した内容を NSAS_STRUCT に格納します。
 * 
 * 定期コマンド送信周期より早い周期で定期的に実行してください。
 * @note データパケットについては DRIVER_Super_rec() を使用してフレーム同期をとり、
 * フレーム同期がとれた場合に受信内容を NSAS_STRUCT に格納します。
 * @param NSAS_STRUCT *my_nsas : 対象とするNSAS構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 1以外 : データが受信されなかった等(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
int		NSAS_rec(NSAS_STRUCT *my_nsas){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_nsas->driver_super), &(my_nsas->rs422_config));
	if(i_ret == 1){
			#ifdef	NSAS_DEBUG
				Printf("NSAS: *** Frame ***\n");
			#endif
		NSAS_Data_Conv(my_nsas);
	}
	
	return(i_ret);
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSAS構造体のデータをデバッグコンソール上に表示します。
 * 
 * @param NSAS_STRUCT *my_nsas : 対象とするNSAS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		NSAS_debug_message(NSAS_STRUCT* my_nsas){
	Printf("X:%u ", my_nsas->x);
	Printf("Y:%u ", my_nsas->y);
	//Printf("Z:%f ", my_nsas->z);
		Printf("ID:%u ", (unsigned int)my_nsas->id);
		Printf("GF:%u ", (unsigned int)my_nsas->gain_flag);
		Printf("SF:%u ", (unsigned int)my_nsas->sun_flag);
		Printf("Ga:%u ", (unsigned int)my_nsas->gain);
		Printf("Te:%u ", my_nsas->tempe);
	
	DRIVER_Super_debug_message(&(my_nsas->driver_super));
	
	
	return(0);
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSASへゲイン設定コマンドを送信し、それに対するレスポンスの可否をリターンします。
 * 
 * @note aosc_superに非定期コマンド発行部と、そのコマンドに対するレスポンス受信部の情報を書き込み、
 *  DRIVER_Super_conf() を実行しています。
 * @param NSAS_STRUCT *my_nsas : 対象とするNSAS構造体へのポインタ
 * @param unsigned char ope : ゲインコントロールモードのON/OFF(ON:1  OFF:0)
 * @param unsigned char gain : 設定するゲインの値
 * @return 1 : レスポンス正常
 * @return 1000 : 第二引数のエラー(0か1以外を入れた場合)
 * @return 2001 : レスポンス自体は正常だが、ゲインの設定に失敗
 * @return 2002 : レスポンスのフレーム同期は正常だが、データが意味不明
 * @return 上記以外 : レスポンス異常(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
int		NSAS_gain(NSAS_STRUCT *my_nsas, unsigned char ope, unsigned char gain){
	int	ret;
	unsigned char	nsas_cmd_gain[4] = {0xD1, 0x4D, 0x00, 0x0D};
	unsigned char	nsas_cmd_gain_rx_header[2] = {0x02, 0xD1};
	unsigned char	nsas_cmd_gain_rx_footer[2] = {0x0D, 0x0A};
	
	if(ope == 0){
		nsas_cmd_gain[1] = 0x4D;
	}else if(ope == 1){
		nsas_cmd_gain[1] = 0x41;
	}else{
		return (1000);
	}
	
	nsas_cmd_gain[2] = gain;
	
	my_nsas->driver_super.non_periodic_config.tx_frame_size = sizeof(nsas_cmd_gain);
	my_nsas->driver_super.non_periodic_config.tx_frame = nsas_cmd_gain;
	
	my_nsas->driver_super.non_periodic_config.rx_header_size = sizeof(nsas_cmd_gain_rx_header);
	my_nsas->driver_super.non_periodic_config.rx_header = nsas_cmd_gain_rx_header;
	
	my_nsas->driver_super.non_periodic_config.rx_footer_size = sizeof(nsas_cmd_gain_rx_footer);
	my_nsas->driver_super.non_periodic_config.rx_footer = nsas_cmd_gain_rx_footer;
	
	my_nsas->driver_super.non_periodic_config.rx_frame_size = 7;
	
	ret = DRIVER_Super_conf(&(my_nsas->driver_super), &(my_nsas->rs422_config));
	
	if(ret == 1){
		if((my_nsas->driver_super.non_periodic_rx_frame[2]) == 0x00){
			return (1);
		}else if((my_nsas->driver_super.non_periodic_rx_frame[2]) == 0x01){
			return (2001);
		}else{
			return (2002);
		}
	}
	
	return (ret);
}


//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof NSAS_STRUCT
 * @private
 * @brief フレームデータをNSAS構造体のデータ内容に変換します。
 * 
 * 工学値変換が必要な場合はここに書き込みます。
 * @param NSAS_STRUCT *my_nsas : 対象とするNSAS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		NSAS_Data_Conv(NSAS_STRUCT* my_nsas){
	/** @brief フレームデータのヘッダ分をオフセットしたポインタ*/
	unsigned char *nsas_rx_data = my_nsas->driver_super.periodic_rx_frame + sizeof(nsas_rx_header);
	
	
	//if(my_nsas->rs422_config.ch == NSAS1_CH){	//新版
		my_nsas->error = *(nsas_rx_data + 0);
		my_nsas->id = *(nsas_rx_data + 1);
		//ココ(nsas_rx_data + 2)には必ずゼロが来るので取得しない
		my_nsas->gain_flag = *(nsas_rx_data + 3);
		my_nsas->sun_flag = *(nsas_rx_data + 4);
		my_nsas->gain = *(nsas_rx_data + 5);
		//my_nsas->tempe = ((28.0+85.0) / (0xFF) * nsas_rx_data[6]) - 28.0;
		//my_nsas->x = ((55.0+55.0) / (0xFF) * nsas_rx_data[7]) - 55.0;
		//my_nsas->y = ((55.0+55.0) / (0xFF) * nsas_rx_data[8]) - 55.0;
		my_nsas->tempe = nsas_rx_data[6];
		my_nsas->x = nsas_rx_data[7];
		my_nsas->y = nsas_rx_data[8];
	/*}else{	//旧版
		my_nsas->error = *(nsas_rx_data + 0);
		
		//ココ(nsas_rx_data + 1)にはなぜか余分な1バイトが送信されてくるらしい?
		
		my_nsas->id = *(nsas_rx_data + 2);
		
		//ココ(nsas_rx_data + 3)には必ずゼロが来るので取得しない
		
		my_nsas->gain_flag = *(nsas_rx_data + 4);
		
		my_nsas->sun_flag = *(nsas_rx_data + 5);
		
		my_nsas->gain = *(nsas_rx_data + 6);
		
		*((unsigned char*)(&(my_nsas->tempe)) + 0) = *(nsas_rx_data + 7);
		*((unsigned char*)(&(my_nsas->tempe)) + 1) = *(nsas_rx_data + 8);
		*((unsigned char*)(&(my_nsas->tempe)) + 2) = *(nsas_rx_data + 9);
		*((unsigned char*)(&(my_nsas->tempe)) + 3) = *(nsas_rx_data + 10);
		
		*((unsigned char*)(&(my_nsas->x)) + 0) = *(nsas_rx_data + 11);
		*((unsigned char*)(&(my_nsas->x)) + 1) = *(nsas_rx_data + 12);
		*((unsigned char*)(&(my_nsas->x)) + 2) = *(nsas_rx_data + 13);
		*((unsigned char*)(&(my_nsas->x)) + 3) = *(nsas_rx_data + 14);
		
		*((unsigned char*)(&(my_nsas->y)) + 0) = *(nsas_rx_data + 15);
		*((unsigned char*)(&(my_nsas->y)) + 1) = *(nsas_rx_data + 16);
		*((unsigned char*)(&(my_nsas->y)) + 2) = *(nsas_rx_data + 17);
		*((unsigned char*)(&(my_nsas->y)) + 3) = *(nsas_rx_data + 18);
	}
	*/
	
	
	return (0);
}
