/**
 * @file CCSDS.c
 * @brief CCSDS通信ラッパーのクラスです。(AOBC用 通常取り込みVer)
 * 
 * CCSDS通信ラッパーは、
 * CCSDSのインターフェースを実現し、
 * CCSDSポートの初期化、データ送信、データ受信を行う、
 * CCSDS通信ラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @author 小林 宗太郎
 * @date 2013.06.13
 */

/* インクルードファイル宣言 */
#include "t_services.h"        		/* TOPPERS用ヘッダファイル              */
#include "../source/mw_header.h"	/* ミドルウェア用ヘッダファイル         */
#include "IF_Board_Number.h"

#include "CCSDS.h"

/* 変数定義 */
/**
 * @brief CCSDSポートのデータ送信、データ受信の際に必要となる、ミドルウエアの設定情報を格納する構造体です。
 */

M_T_COM_REF_BUFF    fill_vcdu_t_buf;	/**< @brief FILL_VCDU送信データ情報設定用*/
M_T_COM_REF_BUFF    hk_vcdu_t_buf;		/**< @brief HK_VCDU送信データ情報設定用*/
M_T_COM_REF_BUFF    ms_vcdu_t_buf;		/**< @brief MS_VCDU送信データ情報設定用*/
M_T_COM_SET_BUFF    ccsds_rcvBuff;	/**< @brief 受信データ情報設定用*/

unsigned int	ccsds_dummy1;
unsigned char	ccsds_fill_vcdu[220] = {0x00, };
unsigned int	ccsds_dummy2;
unsigned char	ccsds_ms_send_buf[220];


//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof CCSDS_CONFIG_STRUCT
 * @protected
 * @brief CCSDS_CONFIG構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * @note CCSDS通信ラッパーのクラスを使用する時は起動時に必ず実施してください。
 * @warning この関数を実行する前にCCSDS_CONFIG構造体内の設定値を設定しておく必要があります。
 * @param void *my_ccsds_v : 初期化するCCSDS_CONFIG構造体へのポインタ
 * @return 0 : 正常終了
 * @return -100 : ビットレート設定値不正
 * @return -200番台 : 異常終了(詳細は+200をして M_AP_nobc_ccsds_sndCtrl() の戻り値を参照)
 * @return -300番台 : 異常終了(詳細は+300をして M_AP_nobc_ccsds_ctrl() の戻り値を参照)
 * @return -400番台 : 異常終了(詳細は+400をして M_AP_nobc_ccsds_setOutPort() の戻り値を参照)
 * @return -500番台 : 異常終了(詳細は+500をして M_AP_nobc_ccsds_setFillData() の戻り値を参照)
 * @return -600番台 : 異常終了(詳細は+600をして M_AP_nobc_ccsds_sndCtrl() の戻り値を参照)
 */
int	CCSDS_init(void *my_ccsds_v){
    CCSDS_CONFIG_STRUCT *my_ccsds = (CCSDS_CONFIG_STRUCT *)my_ccsds_v;
    int                 i_ret = 0;
	unsigned int		rate;
	
	if(my_ccsds->bitrate == 2500){
		rate = M_d_SIO_BPS_2500K;
	}else if(my_ccsds->bitrate == 1250){
		rate = M_d_SIO_BPS_1250K;
	}else if(my_ccsds->bitrate == 1000){
		rate = M_d_SIO_BPS_1000K;
	}else if(my_ccsds->bitrate == 625){
		rate = M_d_SIO_BPS_625K;
	}else if(my_ccsds->bitrate == 64){
		rate = M_d_SIO_BPS_64K;
	}else if(my_ccsds->bitrate == 32){
		rate = M_d_SIO_BPS_32K;
	}else if(my_ccsds->bitrate == 16){
		rate = M_d_SIO_BPS_16K;
	}else if(my_ccsds->bitrate == 8){
		rate = M_d_SIO_BPS_8K;
	}else if(my_ccsds->bitrate == 4){
		rate = M_d_SIO_BPS_4K;
	}else{
		return (-100);
	}
	
	/********************************************************/
	/* 送信停止							                    */
	/********************************************************/
	i_ret = M_AP_nobc_ccsds_sndCtrl( d_IF_BORD1, 0 );
	if(i_ret != 0){
		return (-200 + i_ret);
	}
	
	if(my_ccsds->onoff == 0){
		return (i_ret);
	}
	
		tslp_tsk(1000);	//1sec wait
	
	/********************************************************/
	/* ポート設定						                    */
	/********************************************************/
	i_ret = M_AP_nobc_ccsds_ctrl( d_IF_BORD1, rate, 220 );
	if(i_ret != 0){
		return (-300 + i_ret);
	}
	
	/********************************************************/
	/* 出力ポート選択					                    */
	/********************************************************/
	i_ret = M_AP_nobc_ccsds_setOutPort( d_IF_BORD1, 0 );
	if(i_ret != 0){
		return (-400 + i_ret);
	}
	
	/********************************************************/
	/* FILL_VCDU設定					                    */
	/********************************************************/
	fill_vcdu_t_buf.vp_add = (void *)ccsds_fill_vcdu;
	fill_vcdu_t_buf.ui_dataSize = sizeof(ccsds_fill_vcdu);
	i_ret = M_AP_nobc_ccsds_setFillData( d_IF_BORD1, fill_vcdu_t_buf );
	if(i_ret != 0){
		return (-500 + i_ret);
	}
	
	/********************************************************/
	/* 送信開始							                    */
	/********************************************************/
	i_ret = M_AP_nobc_ccsds_sndCtrl( d_IF_BORD1, 1 );
	if(i_ret != 0){
		return (-600 + i_ret);
	}
	
	return (i_ret);
}


//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof CCSDS_CONFIG_STRUCT
 * @protected
 * @brief CCSDS_CONFIG構造体にて指定されたchからデータを受信します。
 * @param void *my_ccsds_v : 対象とするCCSDS_CONFIG構造体へのポインタ
 * @param void *data_v : 受信データ格納先へのポインタ
 * @param int *count : 受信データ格納先のデータサイズ
 * @return 0 : 受信データなし
 * @return 正数 : 受信データバイト数
 * @return -100番台 : 異常終了(詳細は-100して M_AP_nobc_ccsds_getRcvData() のエラーステータスの値を参照)
 * @return 上記以外 : 異常終了(詳細は M_AP_nobc_ccsds_getRcvData() の戻り値を参照)
 * @note 戻り値の「受信データバイト数」は、実際に受信したデータバイト数を一番近い4の倍数に切り上げた値となる(ミドルウエアの仕様のため)
 */
int		CCSDS_RX(void *my_ccsds_v, void *data_v, int count){
	CCSDS_CONFIG_STRUCT *my_ccsds = (CCSDS_CONFIG_STRUCT *)my_ccsds_v;
	unsigned char *data = (unsigned char *)data_v;
    int				i_ret = 0;
	unsigned int	ret_count;
    unsigned int 	error;
	
	ccsds_rcvBuff.ui_bufSize = count;
    ccsds_rcvBuff.vp_add = (void*)data;
    ccsds_rcvBuff.uip_dataSize = &ret_count;
	
	i_ret = M_AP_nobc_ccsds_getRcvData( d_IF_BORD1, &error, ccsds_rcvBuff );
	if(i_ret < 0){
		if(i_ret == -100){
			i_ret -= error;
		}
		return (i_ret);
	}
	
	return	ret_count;
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof CCSDS_CONFIG_STRUCT
 * @protected
 * @brief CCSDS_CONFIG構造体にて指定されたchへデータを送信します。
 * @param void *my_ccsds_v : 対象とするCCSDS_CONFIG構造体へのポインタ
 * @param void *data_v : 送信データ格納先へのポインタ
 * @param int *count : 送信データサイズ
 * @return 0 : 正常終了
 * @return -100 : 送信データバイト数オーバー
 * @return 上記以外 : 異常終了(詳細は M_AP_nobc_ccsds_sndHkVcdu() の戻り値を参照)
 */
int		CCSDS_TX(void *my_ccsds_v, void *data_v, int count){
	CCSDS_CONFIG_STRUCT *my_ccsds = (CCSDS_CONFIG_STRUCT *)my_ccsds_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
    int		i;
	
	if(count > sizeof(ccsds_ms_send_buf)){
		return (-100);
	}
	
	for(i = 0; i < count; i++){
		ccsds_ms_send_buf[i] = data[i];
	}
	for(; i < sizeof(ccsds_ms_send_buf); i++){
		ccsds_ms_send_buf[i] = 0x00;
	}
	
	/*i_ret += */M_AP_set_RefBuffInfo(&ms_vcdu_t_buf, ccsds_ms_send_buf, sizeof(ccsds_ms_send_buf));
	
	i_ret += M_AP_nobc_ccsds_sndMsVcdu( d_IF_BORD1, ms_vcdu_t_buf );
	
	/////*i_ret += */M_AP_set_RefBuffInfo(&hk_vcdu_t_buf, data, (unsigned int)count);
	////
	////i_ret += M_AP_nobc_ccsds_sndHkVcdu( d_IF_BORD1, hk_vcdu_t_buf );
	
	return (i_ret);
}
