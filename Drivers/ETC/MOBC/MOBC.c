/**
 * @file MOBC.c
 * @brief MOBCとのインターフェースモジュール群です。
 * 
 * MOBCインターフェースモジュールは、MHI社MOBCとのインターフェースを実現し、
 * データ取得・コマンド送信を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.11.01
 */

#include "utility.h"	// Printf()使用時には必要

#include "MOBC.h"

//#define	MOBC_DEBUG


//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof MOBC_STRUCT
 * @public
 * @brief MOBC構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * @note MOBCインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param MOBC_STRUCT *my_mobc : 初期化するMOBC構造体へのポインタ
 * @param unsigned char ch : MOBCが接続されているUARTポート番号
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は RS422_init() の戻り値を参照)
 */
int MOBC_init(MOBC_STRUCT *my_mobc, unsigned char ch){
	int		i_ret;
	unsigned char	init_data[4] = {0x55, 0xAA, 0x55, 0xAA};
	
	my_mobc->rs422_config.ch = ch;
	my_mobc->rs422_config.baudrate = 115200;
	my_mobc->rs422_config.stop_bit = 1;
	
	if((i_ret = RS422_init(&(my_mobc->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	// 初期化後に何かデータを送信しないと相手先で「フレーミングエラー」が出っ放しになるため入れた
	MOBC_RS422_Data_Send(my_mobc, init_data, sizeof(init_data));
	
	return(0);
}

/**
 * @memberof MOBC_STRUCT
 * @public
 * @brief MOBCへRS422データを送信します
 * 
 * RS422_TX() を呼び出してデータを送信します。
 * @param MOBC_STRUCT *my_mobc : 対象とするMOBC構造体へのポインタ
 * @param void *data_v : 送信データ格納先へのポインタ
 * @param int *count : 送信データサイズ
 * @return 0 : 正常終了
 * @return 上記以外 : 異常終了(詳細は RS422_TX() の戻り値を参照)
 */
int MOBC_RS422_Data_Send(MOBC_STRUCT *my_mobc, void *data_v, int size){
	int		i_ret;	/**< @brief 戻り値格納*/
	
	if((i_ret = RS422_TX(&my_mobc->rs422_config, data_v, size)) != 0){
		return (i_ret);
	}
	
	return (0);
}

/**
 * @memberof MOBC_STRUCT
 * @public
 * @brief MOBCからRS422データを受信します
 * 
 * RS422_RX() を呼び出してデータを受信します。
 * @param MOBC_STRUCT *my_mobc : 対象とするMOBC構造体へのポインタ
 * @param void *data_v : 受信データ格納先へのポインタ
 * @param int *count : 受信データ格納先のデータサイズ
 * @return 0 : 受信データなし
 * @return 正数 : 受信データバイト数
 * @return 上記以外 : 異常終了(詳細は RS422_RX() の戻り値を参照)
 * @note 戻り値の「受信データバイト数」は、実際に受信したデータバイト数を一番近い4の倍数に切り上げた値となる(ミドルウエアの仕様のため)
 */
int MOBC_RS422_Data_Receive(MOBC_STRUCT *my_mobc, void *data_v, int size){
	int		i_ret;	/**< @brief 戻り値格納*/
	
	if((i_ret = RS422_RX(&my_mobc->rs422_config, data_v, size)) < 0){
		return (i_ret);
	}
	
	return (i_ret);
}

//*****************************************************************************
//	内部モジュール
//*****************************************************************************
