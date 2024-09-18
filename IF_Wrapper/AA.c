/**
 * @file AA.c
 * @brief AA(ActiveAnalog)ラッパーのクラスです。
 * 
 * AA(ActiveAnalog)ラッパーは、
 * AAのインターフェースを実現し、
 * AAポートの初期化、電圧値取得を行う、
 * AAラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @author 小林 宗太郎
 * @date 2013.04.06
 */

/* インクルードファイル宣言 */

#include "t_services.h"        		/* TOPPERS用ヘッダファイル              */
#include "../source/mw_header.h"	/* ミドルウェア用ヘッダファイル         */
#include "IF_Board_Number.h"
#include "utility.h"

#include "AA.h"

#define AA_TIMECODE		((unsigned int)1)		/**< @brief ミドルウエアへの設定(取得周期)を定義します。*/

/* 変数定義 */
static unsigned int		aa_rx_trigger;		/**< @brief ミドルウエアからのデータ(イベントトリガカウント値)を格納する変数です。*/
static unsigned long	aa_last_get_time;	/**< @brief データを最後に取得した時刻を格納する変数です。*/
static int				aa_get_data[8];		/**< @brief 最後に取得したデータを格納する変数です。*/

//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof AA_CONFIG_STRUCT
 * @protected
 * @brief AA_CONFIG構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * @note AAラッパーのクラスを使用する時は起動時に必ず実施してください。
 * @warning この関数を実行する前にAA_CONFIG構造体内の設定値を設定しておく必要があります。
 * @param void *my_aa_v : 初期化するAA_CONFIG構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は M_AP_nobc_aa_ctrl() の戻り値を参照)
 */
int	AA_init(void *my_aa_v){
    AA_CONFIG_STRUCT *my_aa = (AA_CONFIG_STRUCT *)my_aa_v;
    int                 i_ret = 0;
	
	
	if((i_ret = M_AP_nobc_aa_ctrl(d_IF_BORD1, AA_TIMECODE)) != 0){	// Error
		return (i_ret - 100);
	}
	
	aa_last_get_time = 0;
	aa_get_data[0] = 0;
	aa_get_data[1] = 0;
	aa_get_data[2] = 0;
	aa_get_data[3] = 0;
	aa_get_data[4] = 0;
	aa_get_data[5] = 0;
	aa_get_data[6] = 0;
	aa_get_data[7] = 0;
	
	
	return (i_ret);
}


//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof AA_CONFIG_STRUCT
 * @protected
 * @brief AA_CONFIG構造体にて指定されたポートの電圧値を取得します。
 * @note 取得電圧値はポート1から順にポート8まで指定ポートのデータのみが詰めて出力されます。
 * @param void *my_aa_v : 対象とするAA_CONFIG構造体へのポインタ
 * @param void *data_v : 電圧値格納先へのポインタ
 * @param int *count : 電圧値格納先のデータサイズ
 * @note 取得した電圧値は、指定アドレスから short(2バイト)x取得指定したポート数 分のデータ(A/D変換値)となりますので、そのバイト数以上の領域を確保してください。
 * @return -100 : 電圧値格納先データサイズ不足
 * @return -200 : タイムアウト( M_AP_nobc_aa_getStat() でコケている)
 * @return -300番台 : 異常終了(詳細は+300をして M_AP_nobc_aa_getVal() の戻り値を参照)
 * @return 上記以外 : 電圧値有効データ数(電圧値取得完了 正常終了)
 */
int		AA_RX(void *my_aa_v, void *data_v, int count){
	AA_CONFIG_STRUCT	*my_aa = (AA_CONFIG_STRUCT *)my_aa_v;
	short				*data = (short *)data_v;
	int					i_ret = 0;
	int					loop = 1;
	unsigned long		start_time;
	int					data_cnt = 0;
	int					i, j;
	
	
	for(i = 0; i < 8 * sizeof(my_aa->ch); i++){
		if((((my_aa->ch) >> i) & 0x01) == 1){
			data_cnt += sizeof(short);
		}
	}
	
	if(count < data_cnt){
		return (-100);
	}
	
	
	if(((my_time() - aa_last_get_time) >= 50) || ((my_time() - aa_last_get_time) < 0)){
		/*
		loop = 1;
		start_time = my_time();
		while(loop){
			if(M_AP_nobc_aa_getStat(d_IF_BORD1) == 0){
				loop = 0;
			}
			if(((my_time() - start_time) > 100) || ((my_time() - start_time) < 0)){
				return (-200);
			}
			tslp_tsk(10);
		}
		*/
		
		if((i_ret = M_AP_nobc_aa_getVal(d_IF_BORD1, 0x000000FF, &aa_rx_trigger, (unsigned int *)aa_get_data)) != 0){	// Error
			return (i_ret - 300);
		}
		aa_last_get_time = my_time();
	}
	
	
	j = 0;
	for(i = 0; i < 8 * sizeof(my_aa->ch); i++){
		if((((my_aa->ch) >> i) & 0x01) == 1){
			data[j] = (short)aa_get_data[i];
			j++;
		}
	}
	
	return (data_cnt);
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof AA_CONFIG_STRUCT
 * @protected
 * @brief AAにおいて「送信」にあたるものはないので、何もしないダミーの関数です。
 * @param void *my_aa_v : 対象とするAA_CONFIG構造体へのポインタ
 * @param void *data_v : 送信データ格納先へのポインタ
 * @param int *count : 送信データサイズ
 * @return 0 : 正常終了
 */
int		AA_TX(void *my_aa_v, void *data_v, int count){
	AA_CONFIG_STRUCT *my_aa = (AA_CONFIG_STRUCT *)my_aa_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
	
	return	(i_ret);
}
