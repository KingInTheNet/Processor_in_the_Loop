/**
 * @file GYRO.h
 * @brief GYROとのインターフェースモジュール群です。
 * 
 * GYROインターフェースモジュールは、多摩川精機株式会社FOG IRU TA7584とのインターフェースを実現し、
 * データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2013.10.03
 */

#ifndef	GYRO_INCLUDE_
#define	GYRO_INCLUDE_


#include "../../../IF_Wrapper/AA.h"
#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @class GYRO_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @extends AA_CONFIG_STRUCT
 * @brief GYROの情報を格納する構造体です。
 * 
 * GYRO1台に対して、1つのグローバルインスタンスとして定義します。
 *  GYRO_init() により初期化して使用します。
 */
// AAをfloatではなくshortで取得するように変更した by kkamiya 2013/11/15
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Superクラスの構造体*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422クラスの構造体*/
	AA_CONFIG_STRUCT	aa_config;	/**< @private @brief RS422クラスの構造体*/
	unsigned int		counter;	/**< @public @brief GYROからのカウンタ(MEMS/IRUユーザーズマニュアル参照)*/
	union{
		unsigned char		byte[2];
		struct{
			unsigned error : 1; /**< @public @brief エラー(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned : 3; /**< @public @brief 無効bit(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned action_mode : 4; /**< @public @brief 動作モード(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned angular_vel_detection_range_x : 1;	 /**< @public @brief x軸角速度検出範囲(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned angular_vel_detection_range_y : 1;	 /**< @public @brief y軸角速度検出範囲(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned angular_vel_detection_range_z : 1;	 /**< @public @brief z軸角速度検出範囲(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned : 1;	/**< @public @brief 無効bit(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned abnormality_x : 1;	/**< @public @brief x軸FOG異常(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned abnormality_y : 1;	/**< @public @brief y軸FOG異常(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned abnormality_z : 1;	/**< @public @brief z軸FOG異常(MEMS/IRUユーザーズマニュアル参照)*/
			unsigned abnormality_tempe : 1;	/**< @public @brief 温度センサ異常(MEMS/IRUユーザーズマニュアル参照)*/
		} bit;
	} status;	/**< @public @brief ステータス(MEMS/IRUユーザーズマニュアル参照)*/
	int				del_x;	/**< @public @brief 角速度x(MEMS/IRUユーザーズマニュアル参照)*/
	int				del_y;	/**< @public @brief 角速度y(MEMS/IRUユーザーズマニュアル参照)*/
	int				del_z;	/**< @public @brief 角速度z(MEMS/IRUユーザーズマニュアル参照)*/
	short				current_x;	/**< @public @brief x軸SLD電流(MEMS/IRUユーザーズマニュアル参照)*/
	short				current_y;	/**< @public @brief y軸SLD電流(MEMS/IRUユーザーズマニュアル参照)*/
	short				current_z;	/**< @public @brief z軸SLD電流(MEMS/IRUユーザーズマニュアル参照)*/
	short				tempe;	/**< @public @brief 温度(MEMS/IRUユーザーズマニュアル参照)*/
	short				del_x_aa;	/**< @public @brief 角速度x(AA端子で取得された電圧値)*/
	short				del_y_aa;	/**< @public @brief 角速度y(AA端子で取得された電圧値)*/
	short				del_z_aa;	/**< @public @brief 角速度z(AA端子で取得された電圧値)*/
}	GYRO_STRUCT;


int GYRO_init(GYRO_STRUCT* my_gyro, unsigned char ch, unsigned char aa_ch_x, unsigned char aa_ch_y, unsigned char aa_ch_z);
int GYRO_rec(GYRO_STRUCT *my_gyro);
int GYRO_cycle(GYRO_STRUCT *my_gyro);
int GYRO_debug_message(GYRO_STRUCT* my_gyro);

#endif // GYRO_INCLUDE_
