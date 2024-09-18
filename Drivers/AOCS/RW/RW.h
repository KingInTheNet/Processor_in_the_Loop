/**
 * @file RW.h
 * @brief RWとのインターフェースモジュール群です。
 * 
 * RWインターフェースモジュールは、多摩川精機株式会社TS4431とのインターフェースを実現し、
 * データ取得・コマンド送信を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.09.17
 */

#ifndef	RW_INCLUDE_
#define	RW_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @brief RWのコマンド送信指令値を格納するための構造体です。
 */
typedef	struct {
	unsigned char	mess_no;	/**< @public @brief メッセージNo.(RW通信仕様書参照)*/
	union{
		unsigned char		byte;
		struct{
			unsigned : 5; /**< @public @brief 無効bit(RW通信仕様書参照)*/
			unsigned open_close_loop : 1; /**< @public @brief オープン/クローズループ(RW通信仕様書参照)*/
			unsigned torque_output_direction : 1; /**< @public @brief トルク出力方向(RW通信仕様書参照)*/
			unsigned motor_drive : 1; /**< @public @brief モータ駆動(RW通信仕様書参照)*/
		} bit;
	} comm1; /**< @public @brief コマンド1(RW通信仕様書参照)*/
	unsigned short	comm2;	/**< @public @brief コマンド2(電圧値(指令生値))*/
	unsigned short	comm3;	/**< @public @brief コマンド3(RW通信仕様書参照)*/
}	RW_TX_COMM_STRUCT;


/**
 * @brief RWの受信ステータスを格納するための構造体です。
 */
typedef	struct {
	unsigned char	mess_no;	/**< @public @brief メッセージNo.(RW通信仕様書参照)*/
	union{
		unsigned char		byte;
		struct{
			unsigned : 5; /**< @public @brief 無効bit(RW通信仕様書参照)*/
			unsigned rotation_direction : 1; /**< @public @brief モータ回転方向(RW通信仕様書参照)*/
			unsigned torque_output_direction : 1; /**< @public @brief トルク出力方向(RW通信仕様書参照)*/
			unsigned motor_drive : 1; /**< @public @brief モータ駆動(RW通信仕様書参照)*/
		} bit;
	} sts1;	/**< @public @brief ステータス1(RW通信仕様書参照)*/
	union{
		unsigned char		byte;
		struct{
			unsigned : 2; /**< @public @brief 無効bit(RW通信仕様書参照)*/
			unsigned overcurrent: 1; /**< @public @brief 過電圧異常(RW通信仕様書参照)*/
			unsigned sensor_failed : 1; /**< @public @brief センサ異常(RW通信仕様書参照)*/
			unsigned overvoltage : 1; /**< @public @brief 過電圧異常(RW通信仕様書参照)*/
			unsigned command_failed : 1; /**< @public @brief コマンド範囲外(RW通信仕様書参照)*/
			unsigned bcc_failed : 1; /**< @public @brief BCC異常(RW通信仕様書参照)*/
			unsigned command_nothing : 1; /**< @public @brief コマンド無し(RW通信仕様書参照)*/
		} bit;
	} sts2;	/**< @public @brief ステータス2(RW通信仕様書参照)*/
	unsigned short	sts3;	/**< @public @brief ステータス3(RW通信仕様書参照)*/
	short			sts4;	/**< @public @brief ステータス4(RW通信仕様書参照)*/
	short			sts5;	/**< @public @brief ステータス5(RW通信仕様書参照)*/
}	RW_RX_STS_STRUCT;


/**
 * @class RW_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief RWの情報を格納する構造体です。
 * 
 * RW1台に対して、1つのグローバルインスタンスとして定義します。
 *  RW_init() により初期化して使用します。
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Superクラスの構造体*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422クラスの構造体*/
	RW_TX_COMM_STRUCT	rw_tx_comm;	/**< @public @brief コマンド送信指令値格納用構造体*/
	RW_RX_STS_STRUCT	rw_rx_sts;	/**< @public @brief 受信ステータス格納用構造体*/
	unsigned char		param_req_mess_no;	/**< @private @brief パラメータ要求用メッセージナンバー*/
	unsigned char		param_cfg_mess_no;	/**< @private @brief パラメータ設定用メッセージナンバー*/
}	RW_STRUCT;


int RW_init(RW_STRUCT* my_rw, unsigned char ch);
void Debug_RW(void);
int RW_tx_comm(RW_STRUCT *my_rw, unsigned char Comm1, unsigned short Comm2, unsigned short Comm3);
int RW_cycle(RW_STRUCT* my_rw);
int RW_rec(RW_STRUCT* my_rw);
int RW_debug_message(RW_STRUCT* my_rw);
int RW_Parameter_Request1(RW_STRUCT *my_rw, unsigned short *current_gain, unsigned short *current_integ_gain, unsigned short *current_limit);
int RW_Parameter_Request2(RW_STRUCT *my_rw, unsigned short *temperature_gain, unsigned short *temperature_offset, unsigned short *system_config);
int RW_Parameter_Config1(RW_STRUCT *my_rw, unsigned short current_gain, unsigned short current_integ_gain, unsigned short current_limit);
int RW_Parameter_Config2(RW_STRUCT *my_rw, unsigned short temperature_gain, unsigned short temperature_offset, unsigned short system_config);

#endif // RW_INCLUDE_
