/**
 * @file GYRO.c
 * @brief GYROとのインターフェースモジュール群です。
 * 
 * GYROインターフェースモジュールは、多摩川精機株式会社FOG IRU TA7584とのインターフェースを実現し、
 * データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2013.10.03
 */

#include "utility.h"	// Printf()使用時には必要

#include "../../../Data_Processing/endian_conv.h"
#include "../../../Data_Processing/exor.h"
#include "../../../Data_Processing/ascii_conv.h"

#include "GYRO.h"

//#define	GYRO_DEBUG


int				GYRO_Data_Conv(GYRO_STRUCT *my_gyro);

#define GYRO_RX_FRAME_SIZE			42	/**< @brief 受信フレームの長さ*/

static unsigned char	gyro_rx_header[11] = {'$', 'T', 'S', 'C', ',', 'B', 'I', 'N', ',', 0x1C, 0x00};	/**< @brief 受信フレームのヘッダ*/
static unsigned char	gyro_rx_footer[2] = {0x0D, 0x0A};	/**< @brief 受信フレームのフッタ*/

//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof GYRO_STRUCT
 * @public
 * @brief GYRO構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、 GYRO_STRUCT.driver_super に定期受信部のヘッダ,フッタ,フレームサイズ、定期コマンド発行部の情報を記録します。
 * @note GYROインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param GYRO_STRUCT *my_gyro : 初期化するGYRO構造体へのポインタ
 * @param unsigned char ch : GYROが接続されているUARTポート番号
 * @return 0 : 正常終了
 * @return 100000番台 : 異常終了(詳細は-100000して AA_init() の戻り値を参照)
 * @return 200000 : 異常終了(DRIVER_Super_init() と AA_init() の両方でエラー発生)
 * @return 上記以外 : 異常終了(詳細は DRIVER_Super_init() の戻り値を参照)
 */
int		GYRO_init(GYRO_STRUCT* my_gyro, unsigned char ch, unsigned char aa_ch_x, unsigned char aa_ch_y, unsigned char aa_ch_z){
    int		i_ret, i_ret2;
	
	my_gyro->rs422_config.ch = ch;
	my_gyro->rs422_config.baudrate = 115200;
	my_gyro->rs422_config.stop_bit = 1;
	
	my_gyro->driver_super.inter_face = RS422;
	
	my_gyro->driver_super.periodic_config.rx_header_size = sizeof(gyro_rx_header);
	my_gyro->driver_super.periodic_config.rx_header = gyro_rx_header;
	
	my_gyro->driver_super.periodic_config.rx_footer_size = sizeof(gyro_rx_footer);
	my_gyro->driver_super.periodic_config.rx_footer = gyro_rx_footer;
	
	my_gyro->driver_super.periodic_config.rx_frame_size = GYRO_RX_FRAME_SIZE;
	
	my_gyro->driver_super.periodic_config.tx_frame_size = 0;
	
	i_ret = DRIVER_Super_init(&(my_gyro->driver_super), &(my_gyro->rs422_config));
	
	
	my_gyro->aa_config.ch = 0;
	my_gyro->aa_config.ch |= (1 << aa_ch_x);
	my_gyro->aa_config.ch |= (1 << aa_ch_y);
	my_gyro->aa_config.ch |= (1 << aa_ch_z);
	
	i_ret2 = AA_init(&(my_gyro->aa_config));
	
	if((i_ret != 0) && (i_ret2 != 0)){
		return(200000);
	}
	
	if(i_ret2 != 0){
		return(100000 + i_ret2);
	}
	
	
	return(i_ret);
}

/**
 * @memberof GYRO_STRUCT
 * @public
 * @brief GYROに対して定期コマンドを送信します。
 * 
 * 本GYROは定期コマンド送信が不要なので、この関数は実行しても何も起きません
 * @param GYRO_STRUCT *my_gyro : 対象とするGYRO構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_cycle() の戻り値を参照)
 */
int		GYRO_cycle(GYRO_STRUCT *my_gyro){
	int		i_ret;
	
		#ifdef	GYRO_DEBUG
			Printf("GYRO: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_gyro->driver_super), &(my_gyro->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof GYRO_STRUCT
 * @public
 * @brief GYROからのデータパケットを監視し、受信した内容を GYRO_STRUCT に格納します。
 * 
 * GYROのデータ出力周期である、20Hzより早い周期で定期的に実行してください。
 * @note データパケットについては DRIVER_Super_rec() を使用してフレーム同期をとり、
 * フレーム同期がとれた場合に受信内容を GYRO_STRUCT に格納します。
 * @param GYRO_STRUCT *my_gyro : 対象とするGYRO構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 1以外 : データが受信されなかった等(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
// AAをfloatではなくshortで取得するように変更した by kkamiya 2013/11/15
int		GYRO_rec(GYRO_STRUCT* my_gyro){
	int		i_ret, i_ret2;
	short	vlt[3];
	
	i_ret = DRIVER_Super_rec(&(my_gyro->driver_super), &(my_gyro->rs422_config));
	if(i_ret == 1){
			#ifdef	GYRO_DEBUG
				Printf("GYRO: *** Frame ***\n");
			#endif
		GYRO_Data_Conv(my_gyro);
	}
	
	AA_RX(&(my_gyro->aa_config), vlt, sizeof(vlt));
	my_gyro->del_x_aa = vlt[0];
	my_gyro->del_y_aa = vlt[1];
	my_gyro->del_z_aa = vlt[2];
	
	return(i_ret);
}

/**
 * @memberof GYRO_STRUCT
 * @public
 * @brief GYRO構造体のデータをデバッグコンソール上に表示します。
 * 
 * @param GYRO_STRUCT *my_gyro : 対象とするGYRO構造体へのポインタ
 * @return 0 : 正常終了
 */
int		GYRO_debug_message(GYRO_STRUCT* my_gyro){
	Printf("Count:%d ", my_gyro->counter);
	Printf("Sts:0x%02X%02X ", my_gyro->status.byte[0], my_gyro->status.byte[1]);
	Printf("DelX:%d ", my_gyro->del_x);
	Printf("DelY:%d ", my_gyro->del_y);
	Printf("DelZ:%d ", my_gyro->del_z);
	//Printf("CurX:%d ", my_gyro->current_x);
	//Printf("CurY:%d ", my_gyro->current_y);
	//Printf("CurZ:%d ", my_gyro->current_z);
	Printf("Tempe:%d ", my_gyro->tempe);
	Printf("DelX_AA:%d ", my_gyro->del_x_aa);
	Printf("DelY_AA:%d ", my_gyro->del_y_aa);
	Printf("DelZ_AA:%d ", my_gyro->del_z_aa);
	
	DRIVER_Super_debug_message(&(my_gyro->driver_super));
	
	
	return(0);
}

//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof GYRO_STRUCT
 * @private
 * @brief フレームデータをGYRO構造体のデータ内容に変換します。
 * 
 * 受信したデータはBCCのチェックを行い、正しかった場合にのみGYRO構造体に格納します。
 * 工学値変換が必要な場合はここに書き込みます。
 * @note BCCの算出は exor() を使用して行っています。
 * @note BCCのアスキーコードの変換は ascii2hex() を使用して行っています。
 * @note エンディアンの変換は endian_conv() を使用して行っています。
 * @param GYRO_STRUCT *my_rw : 対象とするGYRO構造体へのポインタ
 * @return 0 : 正常終了
 * @return 1 : BCCエラー
 */
int		GYRO_Data_Conv(GYRO_STRUCT *my_gyro){
	/** @brief フレームデータのヘッダ分をオフセットしたポインタ*/
	unsigned char	*gyro_rx_data = my_gyro->driver_super.periodic_rx_frame + sizeof(gyro_rx_header);
	int				gyro_conv_tmp_i;
	short			gyro_conv_tmp_s;
	
	gyro_conv_tmp_s = 0x0000;
	gyro_conv_tmp_s |= (gyro_rx_data[27] << 8);
	gyro_conv_tmp_s |= (gyro_rx_data[28] << 0);
	if(ascii2hex((unsigned short)gyro_conv_tmp_s) != exor(&(my_gyro->driver_super.periodic_rx_frame[1]), 36)){
			#ifdef	GYRO_DEBUG
				Printf("GYRO: *** BCC Error ***\n");
			#endif
		return (1);
	}
	
	endian_conv((gyro_rx_data + 0), &(my_gyro->counter), sizeof(my_gyro->counter));
	endian_conv((gyro_rx_data + 4), &(my_gyro->status.byte), sizeof(my_gyro->status.byte));
	
	endian_conv((gyro_rx_data + 6), &gyro_conv_tmp_i, sizeof(gyro_conv_tmp_i));
	//my_gyro->del_x = gyro_conv_tmp_i * (10.0 / 0x80000000);
	my_gyro->del_x = gyro_conv_tmp_i;
	
	endian_conv((gyro_rx_data + 10), &gyro_conv_tmp_i, sizeof(gyro_conv_tmp_i));
	//my_gyro->del_y = gyro_conv_tmp_i * (10.0 / 0x80000000);
	my_gyro->del_y = gyro_conv_tmp_i;
	
	endian_conv((gyro_rx_data + 14), &gyro_conv_tmp_i, sizeof(gyro_conv_tmp_i));
	//my_gyro->del_z = gyro_conv_tmp_i * (10.0 / 0x80000000);
	my_gyro->del_z = gyro_conv_tmp_i;
	
	endian_conv((gyro_rx_data + 18), &gyro_conv_tmp_s, sizeof(gyro_conv_tmp_s));
	//my_gyro->current_x = gyro_conv_tmp_s * (5000.0 / 0x8000);
	my_gyro->current_x = gyro_conv_tmp_s;
	
	endian_conv((gyro_rx_data + 20), &gyro_conv_tmp_s, sizeof(gyro_conv_tmp_s));
	//my_gyro->current_y = gyro_conv_tmp_s * (5000.0 / 0x8000);
	my_gyro->current_y = gyro_conv_tmp_s;
	
	endian_conv((gyro_rx_data + 22), &gyro_conv_tmp_s, sizeof(gyro_conv_tmp_s));
	//my_gyro->current_z = gyro_conv_tmp_s * (5000.0 / 0x8000);
	my_gyro->current_z = gyro_conv_tmp_s;
	
	endian_conv((gyro_rx_data + 24), &gyro_conv_tmp_s, sizeof(gyro_conv_tmp_s));
	//my_gyro->tempe = gyro_conv_tmp_s * (100.0 / 0x8000);
	my_gyro->tempe = gyro_conv_tmp_s;
	
	return (0);
}
