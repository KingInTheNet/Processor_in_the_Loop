/**
 * @file DC.c
 * @brief DC(Discrete)ラッパーのクラスです。(AOBC用)
 * 
 * DC(Discrete)ラッパーは、
 * DCのインターフェースを実現し、
 * DCポートの初期化、DC信号入出力を行う、
 * DCラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @author 小林 宗太郎
 * @date 2013.06.20
 */

/* インクルードファイル宣言 */
#include "t_services.h"        		/* TOPPERS用ヘッダファイル              */
#include "../source/mw_header.h"	/* ミドルウェア用ヘッダファイル         */
#include "IF_Board_Number.h"

#include "DC.h"

#define DC_TIMECODE		((unsigned int)1)		/**< @brief ミドルウエアへの設定(取得周期)を定義します。*/

/* 変数定義 */
// ※下記の2変数はアドレス値が4の倍数となるようなメモリ上にアサインされないと M_AP_nobc_lvttl_getInVal() が正常動作しないらしい。
//   よって、各変数の定義の順番に注意すること。
static unsigned int	dc_in_tmp;	/**< @brief ミドルウエアからの入力値データを一時格納する変数です。*/
static unsigned int	dc_rx_trigger;	/**< @brief ミドルウエアからのデータ(イベントトリガカウント値)を格納する変数です。*/

static unsigned short	dc_curent_val_out = 0x0000;	/**< @brief 現在の出力値データを格納する変数です。*/
static unsigned short	dc_current_val_in;		/**< @brief 最後に取得した入力値を格納する変数です。*/

unsigned short dc_val_out;	/**< @public @brief 最新のDC出力値データを格納する変数です(テレメトリ用)。*/
unsigned short dc_val_in;	/**< @public @brief 最新のDC入力値データを格納する変数です(テレメトリ用)。*/


//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof DC_CONFIG_STRUCT
 * @protected
 * @brief DC_CONFIG構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * @note 初期化時に、DC_CONFIG構造体内の設定値で設定したポートのみ、信号値が"0"になります(設定してないポートは前の状態のままです)。
 * @note DCラッパーのクラスを使用する時は起動時に必ず実施してください。
 * @warning この関数を実行する前にDC_CONFIG構造体内の設定値を設定しておく必要があります。
 * @param void *my_dc_v : 初期化するDC_CONFIG構造体へのポインタ
 * @return 0 : 正常終了
 * @return -100番台 : 異常終了(詳細は+100をして M_AP_nobc_lvttl_ctrl() の戻り値を参照)
 * @return -200番台 : 異常終了(詳細は+200をして M_AP_nobc_lvttl_setOutVal() の戻り値を参照)
 */
int		DC_init(void *my_dc_v){
	DC_CONFIG_STRUCT *my_dc = (DC_CONFIG_STRUCT *)my_dc_v;
	int				i_ret;
	int				i;
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_out); i++){
		if((((my_dc->ch_out) >> i) & 0x0001) == 1){
			dc_curent_val_out &= (~(1 << i));
		}
	}
	
	if((i_ret = M_AP_nobc_lvttl_ctrl(d_IF_BORD1, DC_TIMECODE)) != 0){	// Error
		return (i_ret - 100);
	}
	
	if((i_ret = M_AP_nobc_lvttl_setOutVal(d_IF_BORD1, dc_curent_val_out)) != 0){	// Error
		return (i_ret - 200);
	}
	
	return (i_ret);
}

//***************************************************
//	Middlewear RX
//***************************************************
/**
 * @brief DC信号値を取得します。
 * @param unsigned char call_counter : 呼び出し回数指定
 * @note 取得したDC信号値は、指定アドレスから 取得指定したポート数バイト 分のデータとなりますので、そのバイト数以上の領域を確保してください。
 * @return 0 : 正常終了
 * @return -1000番台 : 異常終了(詳細は+1000して M_AP_nobc_lvttl_getInVal() の戻り値を参照)
 */
int		DC_Middlewear_RX(unsigned char call_counter){
	int				i_ret = 0;
	call_counter %= 200;	// 1sec周期
	
	//////// 受信処理 ////////
	if((call_counter % 200) == 87){	// 1000msecに1回,位相は87の時
		if((i_ret = M_AP_nobc_lvttl_getInVal(d_IF_BORD1, &dc_rx_trigger, &dc_in_tmp)) != 0){	// Error
			return (-1000 - i_ret);
		}
	}
	
	dc_current_val_in = (unsigned short)dc_in_tmp;
	dc_val_in = (unsigned short)dc_in_tmp;
	
	
	return (i_ret);
}

//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof DC_CONFIG_STRUCT
 * @protected
 * @brief DC_CONFIG構造体にて指定されたポートのDC信号値を取得します。
 * @note 取得DC信号値はポート1から順にポート16まで指定したポートのデータのみが詰めて出力されます。
 * @param void *my_dc_v : 対象とするDC_CONFIG構造体へのポインタ
 * @param void *data_v : DC信号値格納先へのポインタ
 * @param int *count : DC信号値格納先のデータサイズ
 * @note 取得したDC信号値は、指定アドレスから 取得指定したポート数バイト 分のデータとなりますので、そのバイト数以上の領域を確保してください。
 * @return -100 : DC信号値格納先データサイズ不足
 * @return 上記以外 : DC信号値有効データ数(DC信号値取得完了 正常終了)
 */
int		DC_RX(void *my_dc_v, void *data_v, int count){
	DC_CONFIG_STRUCT *my_dc = (DC_CONFIG_STRUCT *)my_dc_v;
	unsigned char *data = (unsigned char *)data_v;
	int				i_ret = 0;
	int				data_cnt = 0;
	int				i, j = 0;
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_in); i++){
		if((((my_dc->ch_in) >> i) & 0x0001) == 1){
			data_cnt++;
		}
	}
	
	if(count < data_cnt){
		return (-100);
	}
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_in); i++){
		if((((my_dc->ch_in) >> i) & 0x0001) == 1){
			*(data + j) = (unsigned char)((dc_current_val_in >> i) & 0x00000001);
			j++;
		}
	}
	
	return (data_cnt);
}

//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof DC_CONFIG_STRUCT
 * @protected
 * @brief DC_CONFIG構造体にて指定されたポートのDC信号値を出力します。
 * @note 出力するDC信号値はポート1から順にポート16まで指定したポートのデータのみを詰め、"0"か"1"で指定します。
 * @note 出力を指定しなかったポートの出力値は前の状態のままです。
 * @param void *my_dc_v : 対象とするDC_CONFIG構造体へのポインタ
 * @param void *data_v : DC信号値格納先へのポインタ
 * @param int *count : DC信号値格納先のデータサイズ
 * @note 出力するDC信号値は、指定アドレスから 出力指定したポート数バイト 分のデータとなりますので、そのバイト数以上の領域を確保してください。
 * @return 0 : DC信号値有効データ数(DC信号値取得完了 正常終了)
 * @return -100 : DC信号値格納先データサイズ不足
 * @return -200番台 : 異常終了(詳細は+200をして M_AP_nobc_lvttl_setOutVal() の戻り値を参照)
 */
int		DC_TX(void *my_dc_v, void *data_v, int count){
	DC_CONFIG_STRUCT *my_dc = (DC_CONFIG_STRUCT *)my_dc_v;
	unsigned char *data = (unsigned char *)data_v;
	int				i_ret = 0;
	int				data_cnt = 0;
	int				i, j = 0;
	
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_out); i++){
		if((((my_dc->ch_out) >> i) & 0x0001) == 1){
			data_cnt++;
		}
	}
	
	if(count < data_cnt){
		return (-100);
	}
	
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_out); i++){
		if((((my_dc->ch_out) >> i) & 0x0001) == 1){
			if((data[j] & 0x01) == 0){
				dc_curent_val_out &= (~(1 << i));
			}else if((data[j] & 0x01) == 1){
				dc_curent_val_out |= (1 << i);
			}
			j++;
		}
	}
	
	
	if((i_ret = M_AP_nobc_lvttl_setOutVal(d_IF_BORD1, (unsigned int)dc_curent_val_out)) != 0){	// Error
		return (i_ret - 200);
	}
	
	dc_val_out = dc_curent_val_out;
	
	return (i_ret);
}
