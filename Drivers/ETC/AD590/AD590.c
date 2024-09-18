/**
 * @file AD590.c
 * @brief AD590とのインターフェースモジュール群です。
 * 
 * AD590インターフェースモジュールは、Analog Devices社AD590とのインターフェースを実現し、
 * 初期化、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2013.10.24
 */

#include "utility.h"	// Printf()使用時には必要

#include "AD590.h"

//#define	AD590_DEBUG


int		AD590_Data_Conv(AD590_STRUCT *my_ad590);

#define AD590_RX_FRAME_SIZE		(2 * AD590_NUMBER)	/**< @brief 受信フレームの長さ(2バイト x ポート数)*/

//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof AD590_STRUCT
 * @public
 * @brief AD590構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、 AD590_STRUCT.driver_super に定期受信部のヘッダ,フッタ,フレームサイズ、定期コマンド発行部の情報を記録します。
 * @note AD590インターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param AD590_STRUCT *my_ad590 : 初期化するAD590構造体へのポインタ
 * @return 0 : 正常終了
 * @return 100番台 : 異常終了(詳細は DRIVER_Super_init() の戻り値を参照)
 */
int		AD590_init(AD590_STRUCT *my_ad590){
	int		i;
	int		i_ret;
	
	my_ad590->pa_config.ch = (0x00000001 << AD590_NUMBER) - 1;
	
	my_ad590->driver_super.inter_face = PA;
	
	my_ad590->driver_super.periodic_config.rx_header_size = 0;
	
	my_ad590->driver_super.periodic_config.rx_footer_size = 0;
	
	my_ad590->driver_super.periodic_config.rx_frame_size = AD590_RX_FRAME_SIZE;
	
	my_ad590->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_ad590->driver_super), &(my_ad590->pa_config))) != 0){	// Error
		return(i_ret);
	}
	
	return(i_ret);
}

/**
 * @memberof AD590_STRUCT
 * @public
 * @brief AD590に対して定期コマンドを送信します。
 * 
 * 本AD590は定期コマンド送信が不要なので、この関数は実行しても何も起きません
 * @param AD590_STRUCT *my_ad590 : 対象とするAD590構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_cycle() の戻り値を参照)
 */
int		AD590_cycle(AD590_STRUCT* my_ad590){
	int		i_ret;
	
		#ifdef	AD590_DEBUG
			Printf("AD590: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_ad590->driver_super), &(my_ad590->pa_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof AD590_STRUCT
 * @public
 * @brief AD590からの電流値を取得し、その値を温度[℃]に変換し AD590_STRUCT に格納します。
 * 
 * 制御側で必要とする周期で定期的に実行してください。
 * @param AD590_STRUCT *my_ad590 : 対象とするAD590構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 1以外 : データが受信されなかった等(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
int		AD590_rec(AD590_STRUCT* my_ad590){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_ad590->driver_super), &(my_ad590->pa_config));
	if(i_ret == 1){
			#ifdef	AD590_DEBUG
				Printf("AD590: *** Frame ***\n");
			#endif
		AD590_Data_Conv(my_ad590);
	}
	
	return(i_ret);
}

/**
 * @memberof AD590_STRUCT
 * @public
 * @brief AD590構造体のデータをデバッグコンソール上に表示します。
 * 
 * @param AD590_STRUCT *my_ad590 : 対象とするAD590構造体へのポインタ
 * @return 0 : 正常終了
 */
int		AD590_debug_message(AD590_STRUCT* my_ad590){
	Printf("CH00:%d  ", my_ad590->tempe[0]);
	Printf("CH01:%d  ", my_ad590->tempe[1]);
	Printf("CH02:%d  ", my_ad590->tempe[2]);
	Printf("CH03:%d  ", my_ad590->tempe[3]);
	Printf("\n");
	Printf("CH04:%d  ", my_ad590->tempe[4]);
	Printf("CH05:%d  ", my_ad590->tempe[5]);
	Printf("CH06:%d  ", my_ad590->tempe[6]);
	Printf("CH07:%d  ", my_ad590->tempe[7]);
	Printf("\n");
	Printf("CH08:%d  ", my_ad590->tempe[8]);
	Printf("CH09:%d  ", my_ad590->tempe[9]);
	Printf("CH10:%d  ", my_ad590->tempe[10]);
	Printf("CH11:%d  ", my_ad590->tempe[11]);
	Printf("\n");
	Printf("CH12:%d  ", my_ad590->tempe[12]);
	Printf("CH13:%d  ", my_ad590->tempe[13]);
	Printf("CH14:%d  ", my_ad590->tempe[14]);
	Printf("CH15:%d  ", my_ad590->tempe[15]);
	
	//DRIVER_Super_debug_message(&(my_ad590->driver_super));
	
	
	return(0);
}

//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof AD590_STRUCT
 * @private
 * @brief フレームデータをAD590構造体のデータ内容に変換します。
 * 
 * 工学値変換が必要な場合はここに書き込みます。
 * @param AD590_STRUCT *my_ad590 : 対象とするAD590構造体へのポインタ
 * @return 0 : 正常終了
 */
int		AD590_Data_Conv(AD590_STRUCT *my_ad590){
	/** @brief フレームデータのヘッダ分をオフセットしたポインタ*/
	short *ad590_rx_data = (short *)(my_ad590->driver_super.periodic_rx_frame + 0);
	int	i;
	
	
	for(i = 0; i < AD590_NUMBER; i++){
		my_ad590->tempe[i] = *(ad590_rx_data + i);
	}
	
	
	return (0);
}
