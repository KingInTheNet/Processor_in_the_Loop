/**
 * @file RCS.h
 * @brief RCSとのインターフェースモジュール群です。
 * 
 * RCSインターフェースモジュールは、首都大RCSとのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.10.06
 */

#ifndef	RCS_INCLUDE_
#define	RCS_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @class RCS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief RCSの情報を格納する構造体です。
 * 
 * RCS1台に対して、1つのグローバルインスタンスとして定義します。
 *  RCS_init() により初期化して使用します。
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Superクラスの構造体*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422クラスの構造体*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned vo_au : 2; /**< @public @brief VO-AUフラグ内容(0:Close, 1:Open_Action, 2:Open)*/
			unsigned vo_ad : 2; /**< @public @brief VO-ADフラグ内容(0:Close, 1:Open_Action, 2:Open)*/
			unsigned vo_bu : 2; /**< @public @brief VO-BUフラグ内容(0:Close, 1:Open_Action, 2:Open)*/
			unsigned vo_bd : 2; /**< @public @brief VO-BDフラグ内容(0:Close, 1:Open_Action, 2:Open)*/
		} bit;
	} flag; /**< @public @brief フラグ内容*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned vo_au : 1; /**< @public @brief VO-AUピン状態(0:Close, 1:Open)*/
			unsigned vo_ad : 1; /**< @public @brief VO-ADピン状態(0:Close, 1:Open)*/
			unsigned vo_bu : 1; /**< @public @brief VO-BUピン状態(0:Close, 1:Open)*/
			unsigned vo_bd : 1; /**< @public @brief VO-BDピン状態(0:Close, 1:Open)*/
			unsigned flag_12v : 1; /**< @public @brief 12V系フラグ内容(0:OFF, 1:ON)*/
			unsigned pin_12v : 1; /**< @public @brief 12V系ピン状態(0:OFF, 1:ON)*/
			unsigned mode : 2; /**< @public @brief モード(0～3:L0～L3)*/
		} bit;
	} status; /**< @public @brief ステータス情報*/
	
	unsigned char		last_cmd;	/**< @public @brief 直前のコマンドを格納する*/
	unsigned char		ack;	/**< @public @brief 各種ACK又はエラー番号を格納する*/
	
	unsigned short		tt0;	/**< @public @brief タンク基準温度*/
	unsigned short		tt1;	/**< @public @brief タンク相対温度*/
	unsigned short		tc0;	/**< @public @brief スラスタ内基準温度*/
	unsigned short		tc1;	/**< @public @brief スラスタ内相対温度*/
	unsigned short		pt;		/**< @public @brief タンク内圧*/
	unsigned short		pc;		/**< @public @brief スラスタ内圧*/
	unsigned short		i_pt;	/**< @public @brief 圧力計PT電流*/
	unsigned short		i_pc;	/**< @public @brief 圧力計PC電流*/
}	RCS_STRUCT;


int RCS_init(RCS_STRUCT *my_rcs, unsigned char ch);
void Debug_RCS_gain_set(void);
int RCS_cycle(RCS_STRUCT *my_rcs);
int RCS_rec(RCS_STRUCT *my_rcs);
int RCS_debug_message(RCS_STRUCT* my_rcs);
int RCS_initialize_command(RCS_STRUCT *my_rcs);
int RCS_injection_preparation(RCS_STRUCT *my_rcs, unsigned char valve);
int RCS_injection_start(RCS_STRUCT *my_rcs, unsigned char second);
int RCS_injection_stop(RCS_STRUCT *my_rcs);

#endif // RCS_INCLUDE_
