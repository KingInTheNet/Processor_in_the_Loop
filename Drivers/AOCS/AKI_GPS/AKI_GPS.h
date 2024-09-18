/**
 * @file AKI_GPS.h
 * @brief 秋月GPSとのインターフェースモジュール群です。
 * 
 * AKI_GPSインターフェースモジュールは、秋月GPSとのインターフェースを実現し、
 * データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.10.04
 */

#ifndef	AKI_GPS_INCLUDE_
#define	AKI_GPS_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @class AKI_GPS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief 秋月GPSの情報を格納する構造体です。
 * 
 * AKI_GPS1台に対して、1つのグローバルインスタンスとして定義します。
 *  AKI_GPS_init() により初期化して使用します。
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_SUPERクラスの構造体*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422クラスの構造体*/
	double			utc;			/**< @public @brief UTC*/
	double 			latitude;		/**< @public @brief 緯度*/
	double 			longitude;		/**< @public @brief 経度*/
	unsigned char	p_fix;			/**< @public @brief Position fix*/
	unsigned char	visible_sat;	/**< @public @brief 可視衛星数*/
	double			hdop;			/**< @public @brief Horizontal dilution of precision*/
	double			antenna_height;	/**< @public @brief Antenna height above/below mean sea level*/
	double			geoidal_height;	/**< @public @brief Geoidal height,*/
}	AKI_GPS_STRUCT;


int AKI_GPS_init(AKI_GPS_STRUCT *my_aki_gps, unsigned char ch);
int AKI_GPS_cycle(AKI_GPS_STRUCT *my_aki_gps);
int AKI_GPS_rec(AKI_GPS_STRUCT *my_aki_gps);
int AKI_GPS_debug_message(AKI_GPS_STRUCT* my_aki_gps);

#endif // AKI_GPS_INCLUDE_
