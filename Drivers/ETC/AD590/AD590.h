/**
 * @file AD590.h
 * @brief AD590とのインターフェースモジュール群です。
 * 
 * AD590インターフェースモジュールは、Analog Devices社AD590とのインターフェースを実現し、
 * 初期化、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2013.10.24
 */

#ifndef AD590_INCLUDE_
#define AD590_INCLUDE_


#define		AD590_NUMBER	16

#include "../../../IF_Wrapper/PA.h"
#include "../../Super/Driver_Super.h"



/**
 * @class AD590_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends PA_CONFIG_STRUCT
 * @brief AD590の情報を格納する構造体です。
 * 
 *  AD590_init() により初期化して使用します。
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Superクラスの構造体*/
	PA_CONFIG_STRUCT	pa_config;	/**< @private @brief PAクラスの構造体*/
	short					tempe[AD590_NUMBER];	/**< @public @brief AD590の温度A/D値*/
}	AD590_STRUCT;


int AD590_init(AD590_STRUCT *my_ad590);
int AD590_cycle(AD590_STRUCT *my_ad590);
int AD590_rec(AD590_STRUCT *my_ad590);
int AD590_debug_message(AD590_STRUCT* my_ad590);

#endif // AD590_INCLUDE_
