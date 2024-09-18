/**
 * @file RS422.c
 * @brief RS422(UART)通信ラッパーのクラスです。(AOBC用)
 * 
 * RS422(UART)通信ラッパーは、
 * RS422のインターフェースを実現し、
 * RS422ポートの初期化、データ送信、データ受信を行う、
 * RS422通信ラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @note RS422(UART)のチャンネルはch0～21あり、今回はそのうちch0～16の計16chが外部へ出ています。
 * @author 小林 宗太郎
 * @date 2013.08.07
 */

/* インクルードファイル宣言 */
#include "t_services.h"        		/* TOPPERS用ヘッダファイル              */
#include "kernel_id.h"
#include "../source/mw_header.h"	/* ミドルウェア用ヘッダファイル         */
#include "IF_Board_Number.h"

#include "RS422.h"

#define UART_RING_SIZE 1024
#define UART_DOUBLE_SIZE 512

/* 変数定義 */
M_T_COM_REF_BUFF    t_sendData[16];						/**< @brief 送信データ情報設定用*/
unsigned char		doub_send[16][2][UART_DOUBLE_SIZE];	/**< @brief 送信データ用ダブルバッファ*/
int					doub_send_num[16][2];				/**< @brief 送信データ用ダブルバッファ使用量*/
unsigned char		doub_send_new[16];					/**< @brief 最新のデータの入った送信データダブルバッファ番号*/

M_T_COM_SET_BUFF    t_rcvBuff[16];						/**< @brief 受信データ情報設定用*/
unsigned char		temp_rcv[16][UART_RING_SIZE];		/**< @brief 受信データ用一時バッファ*/
unsigned int		ret_count[16];						/**< @brief 受信データのバイト数格納用*/
unsigned int 		error[16];							/**< @brief データ受信時のエラーステータス格納用*/
unsigned char		ring_rcv[16][UART_RING_SIZE];		/**< @brief 受信データ用リングバッファ*/
int					ring_rcv_head[16];					/**< @brief 受信データ用リングバッファ先頭場所*/
int					ring_rcv_foot[16];					/**< @brief 受信データ用リングバッファ終端場所*/
int					ring_rcv_num[16];					/**< @brief 受信データ用リングバッファ使用量*/


typedef struct{
	int	from;
	int	to;
}BankChMap;
#define RS422_BANK_NUM (5)
static const BankChMap	bcmap_[RS422_BANK_NUM] = {{0, 1}, {2, 3}, {4, 11}, {12, 13}, {14, 15}};


//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof RS422_CONFIG_STRUCT
 * @protected
 * @brief RS422_CONFIG構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * @note RS422通信ラッパーのクラスを使用する時は起動時に必ず実施してください。
 * @warning この関数を実行する前にRS422_CONFIG構造体内の設定値を設定しておく必要があります。
 * @param void *my_rs422_v : 初期化するRS422_CONFIG構造体へのポインタ
 * @return 0 : 正常終了
 * @return -100 : UARTチャンネル番号不正
 * @return -200 : ボーレート設定値不正
 * @return -300 : ストップビット値不正
 * @return -400番台 : 異常終了(詳細は+400をして M_AP_nobc_uart_ctrl() の戻り値を参照)
 * @return -500番台 : 異常終了(詳細は+500をして M_AP_nobc_uart_sndTrigger() の戻り値を参照)
 */
int	RS422_init(void *my_rs422_v){
	RS422_CONFIG_STRUCT	*my_rs422 = (RS422_CONFIG_STRUCT *)my_rs422_v;
	int					i_ret = 0;
	unsigned int		rate;
	unsigned char		stop;
	
	
	if((my_rs422->ch < 0) || (my_rs422->ch > 15)){
		return (-100);
	}
	
	
	M_AP_set_SetBuffInfo(&t_rcvBuff[my_rs422->ch], temp_rcv[my_rs422->ch], UART_RING_SIZE, &ret_count[my_rs422->ch]);
	
	doub_send_num[my_rs422->ch][0] = 0;
	doub_send_num[my_rs422->ch][1] = 0;
	doub_send_new[my_rs422->ch] = 0;
	ring_rcv_head[my_rs422->ch] = 0;
	ring_rcv_foot[my_rs422->ch] = 0;
	ring_rcv_num[my_rs422->ch] = 0;
	
	
	if(my_rs422->baudrate == 4800){
		rate = M_d_SIO_BPS_4800;
	}else if(my_rs422->baudrate == 9600){
		rate = M_d_SIO_BPS_9600;
	}else if(my_rs422->baudrate == 14400){
		rate = M_d_SIO_BPS_14400;
	}else if(my_rs422->baudrate == 19200){
		rate = M_d_SIO_BPS_19200;
	}else if(my_rs422->baudrate == 38400){
		rate = M_d_SIO_BPS_38400;
	}else if(my_rs422->baudrate == 57600){
		rate = M_d_SIO_BPS_57600;
	}else if(my_rs422->baudrate == 115200){
		rate = M_d_SIO_BPS_115200;
	}else{
		return (-200);
	}
	
	//データ長8、パリティなし、ストップビット長1 → "8"
	//データ長8、パリティなし、ストップビット長2 → "0"
	if(my_rs422->stop_bit == 1){
		stop = 8;
	}else if(my_rs422->stop_bit == 2){
		stop = 0;
	}else{
		return (-300);
	}
	
	
	/********************************************************/
	/* ポート設定						                    */
	/********************************************************/
	/*  環境設定 通信レート、データ長,パリティ,ストップビット  */
	////if((my_rs422->ch >= 0) && (my_rs422->ch <= 7)){
		i_ret = M_AP_nobc_uart_ctrl( d_IF_BORD1, my_rs422->ch, rate, stop, 7, 0 );
		if(i_ret != 0){
			return (-400 + i_ret);
		}
	////}else if((my_rs422->ch >= 8) && (my_rs422->ch <= 15)){
	////	i_ret = M_AP_nobc_uart_ctrl( d_IF_BORD1, (my_rs422->ch + 4), rate, stop, 7, 0 );
	////	if(i_ret != 0){
	////		return (-400 + i_ret);
	////	}
	////}
	/********************************************************/
	/* 送信設定						                       */
	/* データ格納後、即送信したい場合                       */
	/********************************************************/
	/*  即DMA実施設定       */
	////if((my_rs422->ch >= 0) && (my_rs422->ch <= 7)){
		i_ret = M_AP_nobc_uart_sndTrigger( d_IF_BORD1, my_rs422->ch, M_d_SIO_SEND_TRG_SET );
		if(i_ret != 0){
			return (-500 + i_ret);
		}
	////}else if((my_rs422->ch >= 8) && (my_rs422->ch <= 15)){
	////	i_ret = M_AP_nobc_uart_sndTrigger( d_IF_BORD1, (my_rs422->ch + 4), M_d_SIO_SEND_TRG_SET );
	////	if(i_ret != 0){
	////		return (-500 + i_ret);
	////	}
	////}
	return (i_ret);
}


int		RS422_RX_wai_sem(int	ch){
	switch(ch){
		case 0:
			wai_sem(RS422_RX_00_SEM);
		break;
		
		case 1:
			wai_sem(RS422_RX_01_SEM);
		break;
		
		case 2:
			wai_sem(RS422_RX_02_SEM);
		break;
		
		case 3:
			wai_sem(RS422_RX_03_SEM);
		break;
		
		case 4:
			wai_sem(RS422_RX_04_SEM);
		break;
		
		case 5:
			wai_sem(RS422_RX_05_SEM);
		break;
		
		case 6:
			wai_sem(RS422_RX_06_SEM);
		break;
		
		case 7:
			wai_sem(RS422_RX_07_SEM);
		break;
		
		case 8:
			wai_sem(RS422_RX_08_SEM);
		break;
		
		case 9:
			wai_sem(RS422_RX_09_SEM);
		break;
		
		case 10:
			wai_sem(RS422_RX_10_SEM);
		break;
		
		case 11:
			wai_sem(RS422_RX_11_SEM);
		break;
		
		case 12:
			wai_sem(RS422_RX_12_SEM);
		break;
		
		case 13:
			wai_sem(RS422_RX_13_SEM);
		break;
		
		case 14:
			wai_sem(RS422_RX_14_SEM);
		break;
		
		case 15:
			wai_sem(RS422_RX_15_SEM);
		break;
		
		default:
			return (-1);
		break;
	}
	
	return (0);
}

int		RS422_RX_sig_sem(int	ch){
	switch(ch){
		case 0:
			sig_sem(RS422_RX_00_SEM);
		break;
		
		case 1:
			sig_sem(RS422_RX_01_SEM);
		break;
		
		case 2:
			sig_sem(RS422_RX_02_SEM);
		break;
		
		case 3:
			sig_sem(RS422_RX_03_SEM);
		break;
		
		case 4:
			sig_sem(RS422_RX_04_SEM);
		break;
		
		case 5:
			sig_sem(RS422_RX_05_SEM);
		break;
		
		case 6:
			sig_sem(RS422_RX_06_SEM);
		break;
		
		case 7:
			sig_sem(RS422_RX_07_SEM);
		break;
		
		case 8:
			sig_sem(RS422_RX_08_SEM);
		break;
		
		case 9:
			sig_sem(RS422_RX_09_SEM);
		break;
		
		case 10:
			sig_sem(RS422_RX_10_SEM);
		break;
		
		case 11:
			sig_sem(RS422_RX_11_SEM);
		break;
		
		case 12:
			sig_sem(RS422_RX_12_SEM);
		break;
		
		case 13:
			sig_sem(RS422_RX_13_SEM);
		break;
		
		case 14:
			sig_sem(RS422_RX_14_SEM);
		break;
		
		case 15:
			sig_sem(RS422_RX_15_SEM);
		break;
		
		default:
			return (-1);
		break;
	}
	
	return (0);
}


int		RS422_TX_bank(int bank_id){
	int i;
	int i_ret = 0;
	
	
	for(i = bcmap_[bank_id].from; i <= bcmap_[bank_id].to; i++){
		if((doub_send_num[i][0] == 0) && (doub_send_num[i][1] == 0)){
			// 送信ダブルバッファが両方とも空の時
			M_AP_set_RefBuffInfo(&(t_sendData[i]), &(doub_send[i][doub_send_new[i]]), doub_send_num[i][doub_send_new[i]]);
			doub_send_num[i][doub_send_new[i]] = 0;
		}else if((doub_send_num[i][0] != 0) && (doub_send_num[i][1] != 0)){
			// 送信ダブルバッファが両方とも使用している時
			M_AP_set_RefBuffInfo(&(t_sendData[i]), &(doub_send[i][(doub_send_new[i])^1]), doub_send_num[i][(doub_send_new[i])^1]);
			doub_send_num[i][(doub_send_new[i])^1] = 0;
		}else{
			// 送信ダブルバッファを片方だけ使用している時
			M_AP_set_RefBuffInfo(&(t_sendData[i]), &(doub_send[i][doub_send_new[i]]), doub_send_num[i][doub_send_new[i]]);
			doub_send_num[i][doub_send_new[i]] = 0;
		}
	}
	
	i_ret = M_AP_nobc_uart_SndDataBank(d_IF_BORD1, bank_id, &t_sendData[bcmap_[bank_id].from]);
	if(i_ret != 0){
		return (i_ret - 1000);
	}
	
	return (i_ret);
}

int		RS422_RX_bank(int bank_id){
	int i, j;
	int i_ret = 0;
	int full_flg = 0;
	
	
	/*
	for(i = bcmap_[bank_id].from; i <= bcmap_[bank_id].to; i++){
		// 格納リングバッファがいっぱいの時
		if(ring_rcv_num[i] == UART_RING_SIZE){
			return (-2000 - i);
		}
	}
	*/
	
	i_ret = M_AP_nobc_uart_getRcvDataBank(d_IF_BORD1, bank_id, &error[bcmap_[bank_id].from], &t_rcvBuff[bcmap_[bank_id].from]);
	if((i_ret != 0) && (i_ret != -100)){	// 「通信エラー」以外のエラーの時
		return (i_ret - 3000);
	}else{	// 「通信エラー」もしくは「正常終了」の時
		for(i = bcmap_[bank_id].from; i <= bcmap_[bank_id].to; i++){
			if(error[i] == 0){
				for(j = 0; j < ret_count[i]; j++){
					// 格納リングバッファがいっぱいの時
					if(ring_rcv_num[i] == UART_RING_SIZE){
						full_flg++;
						break;
					}
					
					if(ring_rcv_foot[i] == UART_RING_SIZE){
						ring_rcv_foot[i] = 0;
					}
					ring_rcv[i][ring_rcv_foot[i]] = temp_rcv[i][j];
					ring_rcv_foot[i]++;
					// たった一行だけだが、どうも排他制御しておかないとring_rcv_num[]の値がずれることがある
					RS422_RX_wai_sem(i);
					ring_rcv_num[i]++;
					RS422_RX_sig_sem(i);
				}
			}
		}
	}
	
	if(i_ret == -100){	// 「通信エラー」の時
		if(full_flg != 0){	// かつ、格納リングバッファがいっぱいの時
			return (i_ret - 3000 - 2000);
		}else{	// 「通信エラー」のみの時
			return (i_ret - 3000);
		}
	}else{	// 「正常終了」の時
		if(full_flg != 0){	// かつ、格納リングバッファがいっぱいの時
			return (i_ret - 2000);
		}
	}
	
	return (i_ret);
}


//***************************************************
//	Middlewear TRX
//***************************************************
/**
 * @brief RS422のデータを送信リングバッファより送信し、受信したデータを受信リングバッファに格納します。
 * @param unsigned char call_counter : 呼び出し回数指定
 * @return 0 : 正常終了
 * @return -?1000番台 : 異常終了(詳細は+1000して M_AP_nobc_uart_SndDataBank() の戻り値を参照)
 * @return -?2000番台 : どこかのCHの受信バッファがいっぱい
 * @return -?3000番台 : 異常終了(詳細は+3000して M_AP_nobc_uart_GetRcvDataBank() の戻り値を参照)
 * @note 「?」は異常の発生したBank番号
 * @note 必ず5msecおきに呼ぶこと
 */
int		RS422_Middlewear_TRX(unsigned char call_counter){
	int		i_ret = 0;
	
	
	call_counter %= 200;	// 1sec周期
	
	//////// 送信処理 ////////
	if((call_counter % 10) == 1){	// 50msecに1回,位相は1の時
		// Bank0の送信処理を行う
		i_ret = RS422_TX_bank(0);
		if(i_ret != 0){
			return (i_ret - 0);
		}
	}
	
	if((call_counter % 100) == 17){	// 500msecに1回,位相は17の時
		// Bank1の送信処理を行う
		i_ret = RS422_TX_bank(1);
		if(i_ret != 0){
			return (i_ret - 10000);
		}
	}
	
	if((call_counter % 10) == 3){	// 50msecに1回,位相は3の時
		// Bank2の送信処理を行う
		i_ret = RS422_TX_bank(2);
		if(i_ret != 0){
			return (i_ret - 20000);
		}
	}
	
	if((call_counter % 100) == 27){	// 500msecに1回,位相は27の時
		// Bank3の送信処理を行う
		i_ret = RS422_TX_bank(3);
		if(i_ret != 0){
			return (i_ret - 30000);
		}
	}
	
	if((call_counter % 100) == 37){	// 500msecに1回,位相は37の時
		// Bank4の送信処理を行う
		i_ret = RS422_TX_bank(4);
		if(i_ret != 0){
			return (i_ret - 40000);
		}
	}
	
	
	
	
	//////// 受信処理 ////////
	if((call_counter % 20) == 5){	// 100msecに1回,位相は5の時
		// Bank0の受信処理を行う
		i_ret = RS422_RX_bank(0);
		if(i_ret != 0){
			return (i_ret - 0);
		}
	}
	
	if((call_counter % 100) == 57){	// 500msecに1回,位相は57の時
		// Bank1の受信処理を行う
		i_ret = RS422_RX_bank(1);
		if(i_ret != 0){
			return (i_ret - 10000);
		}
	}
	
	if((call_counter % 8) == 0){	// 40msecに1回,位相は0の時
		// Bank2の受信処理を行う
		i_ret = RS422_RX_bank(2);
		if(i_ret != 0){
			return (i_ret - 20000);
		}
	}
	
	if((call_counter % 100) == 67){	// 500msecに1回,位相は67の時
		// Bank3の受信処理を行う
		i_ret = RS422_RX_bank(3);
		if(i_ret != 0){
			return (i_ret - 30000);
		}
	}
	
	if((call_counter % 100) == 77){	// 500msecに1回,位相は77の時
		// Bank4の受信処理を行う
		i_ret = RS422_RX_bank(4);
		if(i_ret != 0){
			return (i_ret - 40000);
		}
	}
	
	
	return(i_ret);
}


//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof RS422_CONFIG_STRUCT
 * @protected
 * @brief RS422_CONFIG構造体にて指定されたchからデータを受信します。
 * @param void *my_rs422_v : 対象とするRS422_CONFIG構造体へのポインタ
 * @param void *data_v : 受信データ格納先へのポインタ
 * @param int *count : 受信データ格納先のデータサイズ
 * @return 0 : 受信データなし
 * @return 0以外 : 受信データバイト数
 * @note 戻り値の「受信データバイト数」は、実際に受信したデータバイト数を一番近い4の倍数に切り上げた値となる(ミドルウエアの仕様のため)
 */
int		RS422_RX(void *my_rs422_v, void *data_v, int count){
	RS422_CONFIG_STRUCT	*my_rs422 = (RS422_CONFIG_STRUCT *)my_rs422_v;
	unsigned char	*data = (unsigned char *)data_v;
	int				i_ret = 0;
	int				i;
	
	
	if(ring_rcv_num[my_rs422->ch] == 0){	// 格納リングバッファが空の時(何も受信してない時)
		return (i_ret);
	}
	
	for(i = 0; 0 < ring_rcv_num[my_rs422->ch]; i++){
		if((count - i) <= 0){
			return (i);
		}
		
		if(ring_rcv_head[my_rs422->ch] == UART_RING_SIZE){
			ring_rcv_head[my_rs422->ch] = 0;
		}
		
		data[i] = ring_rcv[my_rs422->ch][ring_rcv_head[my_rs422->ch]];
		ring_rcv_head[my_rs422->ch]++;
		// たった一行だけだが、どうも排他制御しておかないとring_rcv_num[]の値がずれることがある
		RS422_RX_wai_sem((int)(my_rs422->ch));
		ring_rcv_num[my_rs422->ch]--;
		RS422_RX_sig_sem((int)(my_rs422->ch));
	}
	
	
	return (i);
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof RS422_CONFIG_STRUCT
 * @protected
 * @brief RS422_CONFIG構造体にて指定されたchへデータを送信します。
 * @param void *my_rs422_v : 対象とするRS422_CONFIG構造体へのポインタ
 * @param void *data_v : 送信データ格納先へのポインタ
 * @param int *count : 送信データサイズ
 * @return 0 : 正常終了
 * @return -1 : 送信データサイズが大きすぎる
 * @return -2 : 送信バッファがいっぱい
 */
int		RS422_TX(void *my_rs422_v, void *data_v, int count){
	RS422_CONFIG_STRUCT	*my_rs422 = (RS422_CONFIG_STRUCT *)my_rs422_v;
	unsigned char	*data = (unsigned char *)data_v;
	int		i_ret = 0;
	int		i;
	unsigned char	page;
	
	if((my_rs422->ch >= 4) && (my_rs422->ch <= 11)){	//Bank2
		if(count > 128){
			return (-1);
		}
	}else{
		if(count > 512){
			return (-1);
		}
	}
	
	if((doub_send_num[my_rs422->ch][0] != 0) && (doub_send_num[my_rs422->ch][1] != 0)){	// 送信ダブルバッファが両方とも使用している時
		return (-2);
	}
	
	if((doub_send_num[my_rs422->ch][0] == 0) && (doub_send_num[my_rs422->ch][1] == 0)){	// 送信ダブルバッファが両方とも空の時
		for(i = 0; i < count; i++){
			doub_send[my_rs422->ch][0][i] = data[i];
		}
		doub_send_new[my_rs422->ch] = 0;
		doub_send_num[my_rs422->ch][0] = count;
	}else{	// 送信ダブルバッファを片方だけ使用している時
		page = doub_send_new[my_rs422->ch] ^ 1;
		for(i = 0; i < count; i++){
			doub_send[my_rs422->ch][page][i] = data[i];
		}
		doub_send_new[my_rs422->ch] = page;
		doub_send_num[my_rs422->ch][page] = count;
	}
	
	return (i_ret);
}
