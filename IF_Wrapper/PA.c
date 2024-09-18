/**
 * @file PA.c
 * @brief PA(PassiveAnalog)ラッパーのクラスです。(AOBC用)
 * 
 * PA(PassiveAnalog)ラッパーは、
 * PAのインターフェースを実現し、
 * PAポートの初期化、電流値取得を行う、
 * PAラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @author 小林 宗太郎
 * @date 2013.10.24
 */

/* インクルードファイル宣言 */
#include "t_services.h"        		/* TOPPERS用ヘッダファイル              */
#include "../source/mw_header.h"	/* ミドルウェア用ヘッダファイル         */
#include "IF_Board_Number.h"

#include "PA.h"

#define PA_TIMECODE		((unsigned int)1)		/**< @brief ミドルウエアへの設定(取得周期)を定義します。*/

/* 変数定義 */
static unsigned int		pa_rx_trigger;			/**< @brief ミドルウエアからのデータ(イベントトリガカウント値)を格納する変数です。*/
static int				pa_get_data[16];		/**< @brief 最後に取得したデータを格納する変数です。*/
static unsigned char	pa_next_get_ch_group;	/**< @brief 次にデータを取得するチャンネル群を指示する変数です。*/

//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof PA_CONFIG_STRUCT
 * @protected
 * @brief PA_CONFIG構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * @note PAラッパーのクラスを使用する時は起動時に必ず実施してください。
 * @warning この関数を実行する前にPA_CONFIG構造体内の設定値を設定しておく必要があります。
 * @param void *my_pa_v : 初期化するPA_CONFIG構造体へのポインタ
 * @return 0 : 正常終了
 * @return -100番台 : 異常終了(詳細は+100をして M_AP_nobc_pa_ctrl() の戻り値を参照)
 * @return -200番台 : 異常終了(詳細は+200をして M_AP_nobc_selectTempCh() の戻り値を参照)
 */
int	PA_init(void *my_pa_v){
    PA_CONFIG_STRUCT *my_pa = (PA_CONFIG_STRUCT *)my_pa_v;
    int                 i_ret = 0;
	
	
	pa_get_data[0] = 0;
	pa_get_data[1] = 0;
	pa_get_data[2] = 0;
	pa_get_data[3] = 0;
	pa_get_data[4] = 0;
	pa_get_data[5] = 0;
	pa_get_data[6] = 0;
	pa_get_data[7] = 0;
	pa_get_data[8] = 0;
	pa_get_data[9] = 0;
	pa_get_data[10] = 0;
	pa_get_data[11] = 0;
	pa_get_data[12] = 0;
	pa_get_data[13] = 0;
	pa_get_data[14] = 0;
	pa_get_data[15] = 0;
	
	if((i_ret = M_AP_nobc_pa_ctrl(d_IF_BORD1, PA_TIMECODE)) != 0){	// Error
		return (i_ret - 100);
	}
	
	pa_next_get_ch_group = 0;		// 0～7ch
	
	if((i_ret = M_AP_nobc_selectTempCh(d_IF_BORD1, pa_next_get_ch_group)) != 0){	// 0～7chに切替
		return (i_ret - 200);
	}
	
	
	return (i_ret);
}

//***************************************************
//	Middlewear RX
//***************************************************
/**
 * @brief PAポートの電流値を取得します。
 * @param unsigned char call_counter : 呼び出し回数指定
 * @return 0 : 正常終了
 * @return -1000番台,-3000番台 : 異常終了(詳細は+1000して M_AP_nobc_pa_getVal() の戻り値を参照)
 * @return -2000番台,-4000番台 : 異常終了(詳細は+2000して M_AP_nobc_selectTempCh() の戻り値を参照)
 */
int		PA_Middlewear_RX(unsigned char call_counter){
    int					i_ret = 0;
	
	
	call_counter %= 200;	// 1sec周期
	
	//////// 受信処理 ////////
	if((call_counter % 200) == 47){	// 1000msecに1回,位相は47の時
		if(pa_next_get_ch_group == 0){	// 0～7ch
			// 0～7ch取得
			if((i_ret = M_AP_nobc_pa_getVal(d_IF_BORD1, 0x000000FF, &pa_rx_trigger, (unsigned int *)(&pa_get_data[0]))) != 0){	// Error
				return (-1000 - i_ret);
			}
			pa_next_get_ch_group = 1;	// 次は8～15ch切り替え
		}
	}
	
	//////// 切り替え処理 ////////
	if((call_counter % 200) == 87){	// 1000msecに1回,位相は87の時
		if(pa_next_get_ch_group == 1){
			if((i_ret = M_AP_nobc_selectTempCh(d_IF_BORD1, 1)) != 0){	// 8～15chに切替
				pa_next_get_ch_group = 0;	// 次も0～7ch受信
				return (-2000 - i_ret);
			}
			pa_next_get_ch_group = 2;	// 次は8～15ch受信
		}
	}
	
	//////// 受信処理 ////////
	if((call_counter % 200) == 147){	// 1000msecに1回,位相は147の時
		if(pa_next_get_ch_group == 2){	// 0～7ch
			if((i_ret = M_AP_nobc_pa_getVal(d_IF_BORD1, 0x000000FF, &pa_rx_trigger, (unsigned int *)(&pa_get_data[8]))) != 0){	// Error
				return (-3000 - i_ret);
			}
			pa_next_get_ch_group = 3;	// 次は0～7ch切り替え
		}
	}
	
	//////// 切り替え処理 ////////
	if((call_counter % 200) == 187){	// 1000msecに1回,位相は187の時
		if(pa_next_get_ch_group == 3){
			if((i_ret = M_AP_nobc_selectTempCh(d_IF_BORD1, 0)) != 0){	// 0～7chに切替
				pa_next_get_ch_group = 2;	// 次も8～15ch受信
				return (-4000 - i_ret);
			}
			pa_next_get_ch_group = 0;	// 次は0～7ch受信
		}
	}
	
	
	return (i_ret);
}

//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof PA_CONFIG_STRUCT
 * @protected
 * @brief PA_CONFIG構造体にて指定されたポートの電流値を取得します。
 * @note 取得電流値はポート1から順にポート8まで指定ポートのデータのみが詰めて出力されます。
 * @param void *my_pa_v : 対象とするPA_CONFIG構造体へのポインタ
 * @param void *data_v : 電流値格納先へのポインタ
 * @param int *count : 電流値格納先のデータサイズ
 * @note 取得した電流値は、指定アドレスから short(2バイト)x取得指定したポート数 分のデータ(A/D変換値)となりますので、そのバイト数以上の領域を確保してください。
 * @return -100 : 電流値格納先データサイズ不足
 * @return 上記以外 : 電流値有効データ数(電流値取得完了 正常終了)
 */
int		PA_RX(void *my_pa_v, void *data_v, int count){
	PA_CONFIG_STRUCT	*my_pa = (PA_CONFIG_STRUCT *)my_pa_v;
	short				*data = (short *)data_v;
    int					i_ret = 0;
	int					data_cnt = 0;
	int					i, j;
	
	
	for(i = 0; i < 16 * sizeof(my_pa->ch); i++){
		if((((my_pa->ch) >> i) & 0x01) == 1){
			data_cnt += sizeof(short);
		}
	}
	
	if(count < data_cnt){
		return (-100);
	}
	
	j = 0;
	for(i = 0; i < 8 * sizeof(my_pa->ch); i++){
		if((((my_pa->ch) >> i) & 0x01) == 1){
			data[j] = (short)pa_get_data[i];
			j++;
		}
	}
	
	
	return (data_cnt);
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof PA_CONFIG_STRUCT
 * @protected
 * @brief PAにおいて「送信」にあたるものはないので、何もしないダミーの関数です。
 * @param void *my_pa_v : 対象とするPA_CONFIG構造体へのポインタ
 * @param void *data_v : 送信データ格納先へのポインタ
 * @param int *count : 送信データサイズ
 * @return 0 : 正常終了
 */
int		PA_TX(void *my_pa_v, void *data_v, int count){
	PA_CONFIG_STRUCT *my_pa = (PA_CONFIG_STRUCT *)my_pa_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
	
	return	(i_ret);
}
