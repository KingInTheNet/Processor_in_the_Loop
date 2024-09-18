/**
 * @file SPWIRE.c
 * @brief SPWIRE(スペースワイヤ)通信ラッパーのクラスです。
 * 
 * SPWIRE(スペースワイヤ)通信ラッパーは、
 * SPWIREのインターフェースを実現し、
 * SPWIREポートの初期化、データ送信、データ受信を行う、
 * SPWIRE通信ラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @note SPWIRE(スペースワイヤ)のルーティングは複数考えられますが、
 * 今回は接続相手機器がSOBC(EM)のCPUボード(J111～J114ポート)同士で接続した場合の経路にのみ対応しています。
 * また、データのやりとりもCPUボード上のメモリマップ上にのみ限定されています(ディスティネーションキー固定:0x24)。
 * @warning J111,J112ポートはIFボード向けにAPIで使用されていたりするので、なるべく手を出さない方が良い。
 * また、今回J111ポートにはIFボードが接続されているはずなので、その設定で本クラスを使用しないはず。
 * @author 小林 宗太郎
 * @date 2013.04.19
 */

/* インクルードファイル宣言 */
#include <string.h>
#include "t_services.h"        		/* TOPPERS用ヘッダファイル              */
#include "../source/mw_header.h"	/* ミドルウェア用ヘッダファイル         */
#include "IF_Board_Number.h"

#include "SPWIRE.h"

/* 変数定義 */
static M_T_RMAP_PKT_ATTR	rmap_cfg[4][4];	/**< @brief ミドルウエアの設定情報を格納する構造体の変数(4×4通りポート分)です。*/
static unsigned char		rmap_buf[0xFFF];	/**< @brief バッファ*/

//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof SPWIRE_CONFIG_STRUCT
 * @protected
 * @brief SPWIRE_CONFIG構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * @note SPWIRE通信ラッパーのクラスを使用する時は起動時に必ず実施してください。
 * @warning この関数を実行する前にSPWIRE_CONFIG構造体内の設定値を設定しておく必要があります。
 * @param void *my_spwire_v : 初期化するSPWIRE_CONFIG構造体へのポインタ
 * @return 0 : 正常終了
 * @return -100 : 自身のポート番号値不正
 * @return -200 : 相手のポート番号値不正
 */
int	SPWIRE_init(void *my_spwire_v){
    SPWIRE_CONFIG_STRUCT *my_spwire = (SPWIRE_CONFIG_STRUCT *)my_spwire_v;
    int				i_ret = 0;
	unsigned char	own = my_spwire->own_port;
	unsigned char	tar = my_spwire->target_port;
	unsigned int	addr = my_spwire->reg_addr;
	
	
	if((own < 1) || (own > 4)){
		return (-100);
	}
	
	if((tar < 1) || (tar > 4)){
		return (-200);
	}
	
	
	/********************************************************/
	/* ポート設定						                    */
	/********************************************************/
	rmap_cfg[own][tar].ui_destLogAdd = 0x42;
	rmap_cfg[own][tar].ui_srcLogAdd = 0x42;
	rmap_cfg[own][tar].ui_ackMode = 1;
	rmap_cfg[own][tar].ui_incAddMode = 1;
	rmap_cfg[own][tar].ui_destKey = 0x24;
	rmap_cfg[own][tar].ui_exAdd = 0;
	
	
	// 経路設定
	rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000000;
	rmap_cfg[own][tar].t_destPathAdd.ui_add[1] = 0x00000000;
	rmap_cfg[own][tar].t_destPathAdd.ui_add[2] = 0x00000000;
	rmap_cfg[own][tar].t_destPathAdd.ui_addNum = 1;
	rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000000;
	rmap_cfg[own][tar].t_srcPathAdd.ui_add[1] = 0x00000000;
	rmap_cfg[own][tar].t_srcPathAdd.ui_add[2] = 0x00000000;
	rmap_cfg[own][tar].t_srcPathAdd.ui_addNum = 1;
	if(own == 1){
		if(tar == 1){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000105;
		}else if(tar == 2){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00010105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00030305;
		}else if(tar == 3){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000205;
		}else{
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00010105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00030205;
		}
	}else if(own == 2){
		if(tar == 1){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00030305;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00010105;
		}else if(tar == 2){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x03030105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x03030105;
		}else if(tar == 3){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00030305;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00020105;
		}else{
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x03030105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x03020105;
		}
	}else if(own == 3){
		if(tar == 1){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000205;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000105;
		}else if(tar == 2){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00020105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00030305;
		}else if(tar == 3){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000205;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000205;
		}else{
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00020105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00030205;
		}
	}else{
		if(tar == 1){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00030205;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00010105;
		}else if(tar == 2){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x03020105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x03030105;
		}else if(tar == 3){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00030205;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00020105;
		}else{
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x03020105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x03020105;
		}
	}
	
	
	// いちおう初期化
	rmap_cfg[own][tar].ui_RdWrMode = 0;
	rmap_cfg[own][tar].ui_verifyMode = 0;
	rmap_cfg[own][tar].ui_accessAdd = 0x00000000;
	rmap_cfg[own][tar].ui_dataLen = 0;
	
	return (0);
}


//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof SPWIRE_CONFIG_STRUCT
 * @protected
 * @brief SPWIRE_CONFIG構造体にて指定されたchからデータを受信します。
 * @note 通信相手に対して4バイトバウンダリアクセスになるように細工してある
 * @param void *my_spwire_v : 対象とするSPWIRE_CONFIG構造体へのポインタ
 * @param void *data_v : 受信データ格納先へのポインタ
 * @param int *count : 受信データ格納先のデータサイズ
 * @return 0 : 受信データなし
 * @return -100 : 受信するデータサイズが大きすぎる(0xFFF以上)
 * @return -200番台 : 異常終了(詳細は+200をして M_AP_nobc_sendRmapPacket() の戻り値を参照)
 * @return 上記以外 : 受信データバイト数(正常終了)
 */
int		SPWIRE_RX(void *my_spwire_v, void *data_v, int count){
	SPWIRE_CONFIG_STRUCT *my_spwire = (SPWIRE_CONFIG_STRUCT *)my_spwire_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
	unsigned char	own = my_spwire->own_port;
	unsigned char	tar = my_spwire->target_port;
	unsigned int	addr = my_spwire->reg_addr;
	unsigned char	addr_mod = addr % 4;
	unsigned char	cnt_mod = ((4 - (count + addr_mod) % 4) % 4);
	
	
	if(count <= 0){
		return (0);
	}
	
	if(count > sizeof(rmap_buf)){
		return (-100);
	}
	
	rmap_cfg[own][tar].ui_RdWrMode = 0;		// Read
	rmap_cfg[own][tar].ui_verifyMode = 0;
	rmap_cfg[own][tar].ui_accessAdd = addr - addr_mod;
	rmap_cfg[own][tar].ui_dataLen = count + addr_mod + cnt_mod;
	i_ret = M_AP_nobc_sendRmapPacket(rmap_cfg[own][tar] , rmap_buf);
	if(i_ret != 0){
		return (-200 + i_ret);
	}
	
	memcpy(data, (rmap_buf + addr_mod), count);
	
	
	return (count);
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof SPWIRE_CONFIG_STRUCT
 * @protected
 * @brief SPWIRE_CONFIG構造体にて指定されたchへデータを送信します。
 * @note 通信相手に対して4バイトバウンダリアクセスになるように細工してある
 * @param void *my_spwire_v : 対象とするSPWIRE_CONFIG構造体へのポインタ
 * @param void *data_v : 送信データ格納先へのポインタ
 * @param int *count : 送信データサイズ
 * @return 0 : 正常終了
 * @return -100 : 送信するデータサイズが大きすぎる(0xFFF以上)
 * @return -200番台 : 異常終了(リード時)(詳細は+200をして M_AP_nobc_sendRmapPacket() の戻り値を参照)
 * @return -300番台 : 異常終了(ライト時)(詳細は+300をして M_AP_nobc_sendRmapPacket() の戻り値を参照)
 */
int		SPWIRE_TX(void *my_spwire_v, void *data_v, int count){
	SPWIRE_CONFIG_STRUCT *my_spwire = (SPWIRE_CONFIG_STRUCT *)my_spwire_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
	unsigned char	own = my_spwire->own_port;
	unsigned char	tar = my_spwire->target_port;
	unsigned int	addr = my_spwire->reg_addr;
	unsigned char	addr_mod = addr % 4;
	unsigned char	cnt_mod = ((4 - (count + addr_mod) % 4) % 4);
	
	
	if(count <= 0){
		return (0);
	}
	
	if(count > sizeof(rmap_buf)){
		return (-100);
	}
	
	rmap_cfg[own][tar].ui_RdWrMode = 0;		// Read
	rmap_cfg[own][tar].ui_verifyMode = 0;
	rmap_cfg[own][tar].ui_accessAdd = addr - addr_mod;
	rmap_cfg[own][tar].ui_dataLen = count + addr_mod + cnt_mod;
	i_ret = M_AP_nobc_sendRmapPacket(rmap_cfg[own][tar] , rmap_buf);
	if(i_ret != 0){
		return (-200 + i_ret);
	}
	
	memcpy((rmap_buf + addr_mod), data, count);
	
	rmap_cfg[own][tar].ui_RdWrMode = 1;		// Write
	rmap_cfg[own][tar].ui_verifyMode = 1;
	rmap_cfg[own][tar].ui_accessAdd = addr - addr_mod;
	rmap_cfg[own][tar].ui_dataLen = count + addr_mod + cnt_mod;
	i_ret = M_AP_nobc_sendRmapPacket(rmap_cfg[own][tar] , rmap_buf);
	if(i_ret != 0){
		return (-300 + i_ret);
	}
	
	
	return (0);
}
