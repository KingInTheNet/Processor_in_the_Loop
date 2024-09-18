/**
 * @file NSAS.h
 * @brief NSASとのインターフェースモジュール群です。
 * 
 * NSASインターフェースモジュールは、AxelSpace社AxelSunとのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.08.24
 */

#ifndef	MSAS_INCLUDE_
#define	MSAS_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @class NSAS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief NSASの情報を格納する構造体です。
 * 
 * NSAS1台に対して、1つのグローバルインスタンスとして定義します。
 *  NSAS_init() により初期化して使用します。
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Superクラスの構造体*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422クラスの構造体*/
	unsigned char		error;	/**< @public @brief Error Code(AXELSUN-1ユーザーズマニュアル参照)*/
	unsigned char		id;	/**< @public @brief 固有ID(AXELSUN-1ユーザーズマニュアル参照)*/
	unsigned char		gain_flag;	/**< @public @brief ゲインコントロールモードのON/OFF(AXELSUN-1ユーザーズマニュアル参照)*/
	unsigned char		sun_flag;	/**< @public @brief 太陽光入射判定(AXELSUN-1ユーザーズマニュアル参照)*/
	unsigned char		gain;	/**< @public @brief ゲイン(AXELSUN-1ユーザーズマニュアル参照)*/
	unsigned char		tempe;	/**< @public @brief 温度(AXELSUN-1ユーザーズマニュアル参照)*/
	unsigned char		x;	/**< @public @brief 角度x(AXELSUN-1ユーザーズマニュアル参照)*/
	unsigned char		y;	/**< @public @brief 角度y(AXELSUN-1ユーザーズマニュアル参照)*/
}	NSAS_STRUCT;


int NSAS_init(NSAS_STRUCT *my_nsas, unsigned char ch);
void Debug_NSAS_gain_set(void);
int NSAS_cycle(NSAS_STRUCT *my_nsas);
int NSAS_rec(NSAS_STRUCT *my_nsas);
int NSAS_debug_message(NSAS_STRUCT* my_nsas);
int NSAS_gain(NSAS_STRUCT *my_nsas, unsigned char ope, unsigned char gain);

#endif // MSAS_INCLUDE_
