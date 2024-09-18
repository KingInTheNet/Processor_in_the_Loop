/**
 * @file GAS.h
 * @brief GASとのインターフェースモジュール群です。
 * 
 * GASインターフェースモジュールは、テラテクニカ社TGA-330とのインターフェースを実現し、
 * 初期化、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.08.24
 */

#ifndef	GAS_INCLUDE_
#define	GAS_INCLUDE_


#include "../../../IF_Wrapper/AA.h"
#include "../../Super/Driver_Super.h"


/**
 * @class GAS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends AA_CONFIG_STRUCT
 * @brief GASの情報を格納する構造体です。
 * 
 * GAS1台に対して、1つのグローバルインスタンスとして定義します。
 *  GAS_init() により初期化して使用します。
 */
// AAをfloatではなくshortで取得するように変更した by kkamiya 2013/11/15
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Superクラスの構造体*/
	AA_CONFIG_STRUCT	aa_config;	/**< @private @brief AAクラスの構造体*/
	short					x;	/**< @public @brief X軸信号の電圧出力値*/
	short					y;	/**< @public @brief Y軸信号の電圧出力値*/
	short					z;	/**< @public @brief Z軸信号の電圧出力値*/
	short					ref;	/**< @public @brief Reference信号の電圧出力値*/
	
	short					cycle_sum_x;	/**< @private @brief X軸信号の電圧出力値加算用変数*/
	short					cycle_sum_y;	/**< @private @brief Y軸信号の電圧出力値加算用変数*/
	short					cycle_sum_z;	/**< @private @brief Z軸信号の電圧出力値加算用変数*/
	short					cycle_sum_ref;	/**< @private @brief Reference信号の電圧出力値加算用変数*/
	int						cycle_cnt;	/**< @private @brief 取得周期カウンタ*/
}	GAS_STRUCT;


int GAS_init(GAS_STRUCT *my_gas, unsigned int ch_x, unsigned int ch_y, unsigned int ch_z, unsigned int ch_ref);
int GAS_cycle(GAS_STRUCT *my_gas);
int GAS_rec(GAS_STRUCT *my_gas);
int GAS_debug_message(GAS_STRUCT* my_gas);

#endif // GAS_INCLUDE_
