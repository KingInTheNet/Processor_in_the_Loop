/**
 * @file AKI_GPS.c
 * @brief 秋月GPSとのインターフェースモジュール群です。
 * 
 * AKI_GPSインターフェースモジュールは、秋月GPSとのインターフェースを実現し、
 * データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.10.04
 */

#include <stdlib.h>
#include "utility.h"	// Printf()使用時には必要

#include "AKI_GPS.h"

//#define	AKI_GPS_DEBUG


int				AKI_GPS_Data_Conv(AKI_GPS_STRUCT *my_aki_gps);


#define AKI_GPS_RX_FRAME_SIZE			-1	/**< @brief 受信フレームの長さ*/

static unsigned char	aki_gps_rx_header[7] = {'$', 'G', 'P', 'G', 'G', 'A', ','};	/**< @brief 受信フレームのヘッダ*/
static unsigned char	aki_gps_rx_footer[2] = {0x0D, 0x0A};	/**< @brief 受信フレームのフッタ*/

//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof AKI_GPS_STRUCT
 * @public
 * @brief AKI_GPS構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、 AKI_GPS_STRUCT.driver_super に定期受信部のヘッダ,フッタ,フレームサイズを記録します。
 * @note AKI_GPSインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param AKI_GPS_STRUCT *my_aki_gps : 初期化するAKI_GPS構造体へのポインタ
 * @param unsigned char ch : AKI_GPSが接続されているUARTポート番号
 * @return 0 : 正常終了
 * @return 100番台 : 異常終了(詳細は DRIVER_Super_init() の戻り値を参照)
 * @return 1000番台 : 異常終了(詳細は AKI_GPS_Conf() の戻り値を参照)
 */
int		AKI_GPS_init(AKI_GPS_STRUCT* my_aki_gps, unsigned char ch){
    int		i_ret;
	
	my_aki_gps->rs422_config.ch = ch;
	my_aki_gps->rs422_config.baudrate = 9600;
	my_aki_gps->rs422_config.stop_bit = 1;
	
	my_aki_gps->driver_super.inter_face = RS422;
	
	my_aki_gps->driver_super.periodic_config.rx_header_size = sizeof(aki_gps_rx_header);
	my_aki_gps->driver_super.periodic_config.rx_header = aki_gps_rx_header;
	
	my_aki_gps->driver_super.periodic_config.rx_footer_size = sizeof(aki_gps_rx_footer);
		my_aki_gps->driver_super.periodic_config.rx_footer = aki_gps_rx_footer;
	
	my_aki_gps->driver_super.periodic_config.rx_frame_size = AKI_GPS_RX_FRAME_SIZE;
	
	my_aki_gps->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_aki_gps->driver_super), &(my_aki_gps->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	return(0);
}

/**
 * @memberof AKI_GPS_STRUCT
 * @public
 * @brief AKI_GPSに対して定期コマンドを送信します。
 * 
 * 本AKI_GPSは定期コマンド送信が不要なので、この関数は実行しても何も起きません
 * @param AKI_GPS_STRUCT *my_aki_gps : 対象とするAKI_GPS構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_cycle() の戻り値を参照)
 */
int		AKI_GPS_cycle(AKI_GPS_STRUCT* my_aki_gps){
	int		i_ret;
	
		#ifdef	AKI_GPS_DEBUG
			Printf("AKI_GPS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_aki_gps->driver_super), &(my_aki_gps->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof AKI_GPS_STRUCT
 * @public
 * @brief AKI_GPSからのデータパケットを監視し、受信した内容を AKI_GPS_STRUCT に格納します。
 * 
 * AKI_GPSのデータ出力周期である、1秒より早い周期で定期的に実行してください。
 * @note データパケットについては DRIVER_Super_rec() を使用してフレーム同期をとり、
 * フレーム同期がとれた場合に受信内容を AKI_GPS_STRUCT に格納します。
 * @param AKI_GPS_STRUCT *my_aki_gps : 対象とするAKI_GPS構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 1以外 : データが受信されなかった等(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
int		AKI_GPS_rec(AKI_GPS_STRUCT* my_aki_gps){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_aki_gps->driver_super), &(my_aki_gps->rs422_config));
	if(i_ret == 1){
			#ifdef	AKI_GPS_DEBUG
				Printf("AKI_GPS: *** Frame ***\n");
			#endif
		AKI_GPS_Data_Conv(my_aki_gps);
	}
	
	return(i_ret);
}

/**
 * @memberof AKI_GPS_STRUCT
 * @public
 * @brief AKI_GPS構造体のデータをデバッグコンソール上に表示します。
 * 
 * @param AKI_GPS_STRUCT *my_gps : 対象とするAKI_GPS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		AKI_GPS_debug_message(AKI_GPS_STRUCT* my_aki_gps){
	Printf("UTC:%lf ", my_aki_gps->utc);
	Printf("Latitude:%lf ", my_aki_gps->latitude);
	Printf("Longitude:%lf ", my_aki_gps->longitude);
	Printf("Position_fix:%d ", my_aki_gps->p_fix);
	Printf("Visible_sat:%d ", my_aki_gps->visible_sat);
	Printf("HDOP:%f ", my_aki_gps->hdop);
	Printf("Antenna_height:%lf ", my_aki_gps->antenna_height);
	Printf("Geoidal_height:%lf ", my_aki_gps->geoidal_height);
	
	DRIVER_Super_debug_message(&(my_aki_gps->driver_super));
	
	
	return(0);
}

//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof AKI_GPS_STRUCT
 * @private
 * @brief フレームデータをAKI_GPS構造体のデータ内容に変換します。
 * 
 * 工学値変換が必要な場合はここに書き込みます。
 * @param AKI_GPS_STRUCT *my_aki_gps : 対象とするAKI_GPS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		AKI_GPS_Data_Conv(AKI_GPS_STRUCT *my_aki_gps){
	/** @brief フレームデータのヘッダ分をオフセットしたポインタ*/
	unsigned char *aki_gps_rx_data = my_aki_gps->driver_super.periodic_rx_frame + sizeof(aki_gps_rx_header);
	
	int i;
	int	counter = 0;
	char	aki_gps_tmp[24];
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->utc = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->latitude = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	if(aki_gps_rx_data[counter] == 'S'){
		my_aki_gps->latitude = -(my_aki_gps->latitude);
	}
	counter++;
	counter++;
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->longitude = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	if(aki_gps_rx_data[counter] == 'W'){
		my_aki_gps->longitude = -(my_aki_gps->latitude);
	}
	counter++;
	counter++;
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->p_fix = atoi(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->visible_sat = atoi(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->hdop = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->antenna_height = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	// 余分な'M'を除去
		counter++;
		counter++;
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->geoidal_height = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	return(0);
}
