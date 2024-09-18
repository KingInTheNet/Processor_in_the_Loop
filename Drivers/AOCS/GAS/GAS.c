/**
 * @file GAS.c
 * @brief GASとのインターフェースモジュール群です。
 * 
 * GASインターフェースモジュールは、テラテクニカ社TGA-330とのインターフェースを実現し、
 * 初期化、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.08.24
 */

#include "utility.h"	// Printf()使用時には必要

#include "GAS.h"

//#define	GAS_DEBUG


int		GAS_Data_Conv(GAS_STRUCT *my_gas);

#define GAS_RX_FRAME_SIZE		8	/**< @brief 受信フレームの長さ(2バイト x 4ポート = 8バイト)*/
//#define GAS_RX_FRAME_SIZE		16	/**< @brief 受信フレームの長さ(4バイト x 4ポート = 16バイト)*/

//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof GAS_STRUCT
 * @public
 * @brief GAS構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、 GAS_STRUCT.driver_super に定期受信部のヘッダ,フッタ,フレームサイズ、定期コマンド発行部の情報を記録します。
 * @note GASインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param GAS_STRUCT *my_gas : 初期化するGAS構造体へのポインタ
 * @param unsigned int ch_x : X軸の線が接続されているAAのポート
 * @param unsigned int ch_y : Y軸の線が接続されているAAのポート
 * @param unsigned int ch_z : Z軸の線が接続されているAAのポート
 * @param unsigned int ch_ref : Referenceの線が接続されているAAのポート
 * @return 0 : 正常終了
 * @return 100番台 : 異常終了(詳細は DRIVER_Super_init() の戻り値を参照)
 */
int		GAS_init(GAS_STRUCT *my_gas, unsigned int ch_x, unsigned int ch_y, unsigned int ch_z, unsigned int ch_ref){
	int		i_ret;
	
	my_gas->aa_config.ch = 0;
	my_gas->aa_config.ch |= (1 << ch_x);
	my_gas->aa_config.ch |= (1 << ch_y);
	my_gas->aa_config.ch |= (1 << ch_z);
	my_gas->aa_config.ch |= (1 << ch_ref);
	
	my_gas->driver_super.inter_face = AA;
	
	my_gas->driver_super.periodic_config.rx_header_size = 0;
	
	my_gas->driver_super.periodic_config.rx_footer_size = 0;
	
	my_gas->driver_super.periodic_config.rx_frame_size = GAS_RX_FRAME_SIZE;
	
	my_gas->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_gas->driver_super), &(my_gas->aa_config))) != 0){	// Error
		return(i_ret);
	}
	
	my_gas->cycle_sum_x = 0;
	my_gas->cycle_sum_y = 0;
	my_gas->cycle_sum_z = 0;
	my_gas->cycle_sum_ref = 0;
	my_gas->cycle_cnt = 0;
	
	return(i_ret);
}

/**
 * @memberof GAS_STRUCT
 * @public
 * @brief GASに対して定期コマンドを送信します。
 * 
 * 本GASは定期コマンド送信が不要なので、この関数は実行しても何も起きません
 * @param GAS_STRUCT *my_gas : 対象とするGAS構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_cycle() の戻り値を参照)
 */
int		GAS_cycle(GAS_STRUCT* my_gas){
	int		i_ret;
	
		#ifdef	GAS_DEBUG
			Printf("GAS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_gas->driver_super), &(my_gas->aa_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof GAS_STRUCT
 * @public
 * @brief GASからの電圧値を取得し、そのAD変換値を GAS_STRUCT に格納します。
 * 
 * 制御側で必要とする周期で定期的に実行してください。
 * @param GAS_STRUCT *my_gas : 対象とするGAS構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 1以外 : データが受信されなかった等(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
int		GAS_rec(GAS_STRUCT* my_gas){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_gas->driver_super), &(my_gas->aa_config));
	if(i_ret == 1){
			#ifdef	GAS_DEBUG
				Printf("GAS: *** Frame ***\n");
			#endif
		GAS_Data_Conv(my_gas);
	}
	
	return(i_ret);
}

/**
 * @memberof GAS_STRUCT
 * @public
 * @brief GAS構造体のデータをデバッグコンソール上に表示します。
 * 
 * @param GAS_STRUCT *my_gas : 対象とするGAS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		GAS_debug_message(GAS_STRUCT* my_gas){
	Printf("X:%d ", my_gas->x);
	Printf("Y:%d ", my_gas->y);
	Printf("Z:%d ", my_gas->z);
	Printf("REF:%d ", my_gas->ref);
	
	DRIVER_Super_debug_message(&(my_gas->driver_super));
	
	
	return(0);
}

//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof GAS_STRUCT
 * @private
 * @brief フレームデータをGAS構造体のデータ内容に変換します。
 * 
 * 工学値変換が必要な場合はここに書き込みます。
 * @param GAS_STRUCT *my_gas : 対象とするGAS構造体へのポインタ
 * @return 0 : 正常終了
 */
// AAをfloatではなくshortで取得するように変更した by kkamiya 2013/11/15
int		GAS_Data_Conv(GAS_STRUCT *my_gas){
	/** @brief フレームデータのヘッダ分をオフセットしたポインタ*/
	short *gas_rx_data = (short *)(my_gas->driver_super.periodic_rx_frame + 0);
	
	my_gas->ref = *(gas_rx_data + 0);
	my_gas->x = *(gas_rx_data + 1);
	my_gas->y = *(gas_rx_data + 2);
	my_gas->z = *(gas_rx_data + 3);
	/*
	my_gas->cycle_sum_ref += *(gas_rx_data + 0);
	my_gas->cycle_sum_x += *(gas_rx_data + 1);
	my_gas->cycle_sum_y += *(gas_rx_data + 2);
	my_gas->cycle_sum_z += *(gas_rx_data + 3);
	
	my_gas->cycle_cnt++;
	if(my_gas->cycle_cnt == 10){
		my_gas->x = my_gas->cycle_sum_x / 10;
		my_gas->y = my_gas->cycle_sum_y / 10;
		my_gas->z = my_gas->cycle_sum_z / 10;
		my_gas->ref = my_gas->cycle_sum_ref / 10;
		
		my_gas->cycle_sum_x = 0;
		my_gas->cycle_sum_y = 0;
		my_gas->cycle_sum_z = 0;
		my_gas->cycle_sum_ref = 0;
		my_gas->cycle_cnt = 0;
	}
	*/
	return (0);
}
