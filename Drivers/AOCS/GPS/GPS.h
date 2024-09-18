/**
 * @file GPS.h
 * @brief GPSとのインターフェースモジュール群です。
 * 
 * GPSインターフェースモジュールは、AxelSpace社AXELNAV-1とのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.10.18
 */

#ifndef	GPS_INCLUDE_
#define	GPS_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @brief UTCを格納するための構造体です。
 */
typedef struct {
	unsigned char year;	/**< @public @brief 年(西暦の下2桁)(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned char month;	/**< @public @brief 月(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned char day;	/**< @public @brief 日(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned char hour;	/**< @public @brief 時間(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned char min;	/**< @public @brief 分(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned char sec;	/**< @public @brief 秒(AXELNAV-1ユーザーズマニュアル参照)*/
} UTC_STRUCT;


/**
 * @class GPS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief GPSの情報を格納する構造体です。
 * 
 * GPS1台に対して、1つのグローバルインスタンスとして定義します。
 *  GPS_init() により初期化して使用します。
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Superクラスの構造体*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422クラスの構造体*/
	int					latitude;	/**< @public @brief 緯度(南緯は負の数で表現)(AXELNAV-1ユーザーズマニュアル参照)*/
	int					longitude;	/**< @public @brief 経度(西経は負の数で表現)(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned int		altitude;	/**< @public @brief 高度(AXELNAV-1ユーザーズマニュアル参照)*/
	long long			vector_x;	/**< @public @brief 位置ベクトルx(AXELNAV-1ユーザーズマニュアル参照)*/
	long long			vector_y;	/**< @public @brief 位置ベクトルy(AXELNAV-1ユーザーズマニュアル参照)*/
	long long			vector_z;	/**< @public @brief 位置ベクトルz(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned short		speed;	/**< @public @brief 速度(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned short		direction;	/**< @public @brief 方位(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned short		pdop;	/**< @public @brief PDOP(AXELNAV-1ユーザーズマニュアル参照)*/
	UTC_STRUCT			utc;	/**< @public @brief UTC*/
	unsigned char		alive_sat;	/**< @public @brief 正常な衛星数(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned char		visible_sat;	/**< @public @brief 可視衛星数(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned char		delay_time;	/**< @public @brief 測位遅延時間(AXELNAV-1ユーザーズマニュアル参照)*/
	unsigned char		pps;	/**< @public @brief PPS補正(AXELNAV-1ユーザーズマニュアル参照)*/
	union{
		unsigned char		byte;
		struct{
			unsigned : 2; /**< @public @brief 無効bit(AXELNAV-1ユーザーズマニュアル参照)*/
			unsigned csf_flag : 1; /**< @public @brief CSFフラグ(AXELNAV-1ユーザーズマニュアル参照)*/
			unsigned two_sat_positioning_flag : 1; /**< @public @brief 2衛星測位フラグ(AXELNAV-1ユーザーズマニュアル参照)*/
			unsigned : 1; /**< @public @brief 無効bit(AXELNAV-1ユーザーズマニュアル参照)*/
			unsigned three_dim_positioning_flag : 1; /**< @public @brief 3D測位フラグ(AXELNAV-1ユーザーズマニュアル参照)*/
			unsigned two_dim_positioning_flag : 1; /**< @public @brief 2D測位フラグ(AXELNAV-1ユーザーズマニュアル参照)*/
			unsigned positioning_status : 1; /**< @public @brief 測位ステータス(AXELNAV-1ユーザーズマニュアル参照)*/
		} bit;
	} status1;	/**< @public @brief 各種ステータス(AXELNAV-1ユーザーズマニュアル参照, 97バイト目)*/
}	GPS_STRUCT;


int GPS_init(GPS_STRUCT *my_gps, unsigned char ch);
int GPS_cycle(GPS_STRUCT *my_gps);
int GPS_rec(GPS_STRUCT *my_gps);
int GPS_debug_message(GPS_STRUCT* my_gps);
int GPS_Conf(GPS_STRUCT *my_gps);

#endif // GPS_INCLUDE_
