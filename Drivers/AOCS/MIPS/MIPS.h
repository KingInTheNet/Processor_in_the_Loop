/**
 * @file MIPS.h
 * @brief MIPSとのインターフェースモジュール群です。
 * 
 * MIPS(イオンエンジン)インターフェースモジュールは、ジュピターコーポレーション社MIPSとのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2014.01.17
 */

#ifndef	MIPS_INCLUDE_
#define	MIPS_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @class MIPS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief MIPSの情報を格納する構造体です。
 * 
 * MIPS1台に対して、1つのグローバルインスタンスとして定義します。
 *  MIPS_init() により初期化して使用します。
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Superクラスの構造体*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422クラスの構造体*/
	
	unsigned char		tlm_count;	/**< @public @brief MIPSからのTLMカウンタ情報*/
	unsigned long long	time;	/**< @public @brief MIPSからの時刻情報*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned : 4; /**< @public @brief 無効bit*/
			unsigned mcu : 4; /**< @public @brief MCU状態bit*/
		} bit;
	} mips_status; /**< @public @brief MIPSの情報*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned : 4; /**< @public @brief 無効bit*/
			unsigned indicator : 1; /**< @public @brief INDICATORのONOFF状態bit(0:OFF, 1:ON)*/
			unsigned aps : 1; /**< @public @brief APSのONOFF状態bit(0:OFF, 1:ON)*/
			unsigned nps : 1; /**< @public @brief NPSのONOFF状態bit(0:OFF, 1:ON)*/
			unsigned sps : 1; /**< @public @brief SPSのONOFF状態bit(0:OFF, 1:ON)*/
		} bit;
	} hvps_status; /**< @public @brief HVPSのONOFF情報*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned : 4; /**< @public @brief 無効bit*/
			unsigned mps : 1; /**< @public @brief MPSのONOFF状態bit(0:OFF, 1:ON)*/
			unsigned bv : 1; /**< @public @brief BVのONOFF状態bit(0:OFF, 1:ON)*/
			unsigned rv : 1; /**< @public @brief RVのONOFF状態bit(0:OFF, 1:ON)*/
			unsigned tv : 1; /**< @public @brief TVのONOFF状態bit(0:OFF, 1:ON)*/
		} bit;
	} valve_status; /**< @public @brief VALVEのONOFF情報*/
	
	unsigned short		ad00;	/**< @public @brief MPS電力出力モニタ(0～5V)*/
	unsigned short		ad01;	/**< @public @brief MPS温度モニタ(0～5V)*/
	unsigned short		ad02;	/**< @public @brief SPS-V出力モニタ(0～5V)*/
	unsigned short		ad03;	/**< @public @brief SPS-I出力モニタ(0～5V)*/
	unsigned short		ad04;	/**< @public @brief NPS-V出力モニタ(0～5V)*/
	unsigned short		ad05;	/**< @public @brief NPS-I出力モニタ(0～5V)*/
	unsigned short		ad06;	/**< @public @brief APS-V出力モニタ(0～5V)*/
	unsigned short		ad07;	/**< @public @brief APS-I出力モニタ(0～5V)*/
	unsigned short		ad08;	/**< @public @brief HVPS温度モニタ(0～5V)*/
	unsigned short		ad09;	/**< @public @brief LPS圧力センサ出力モニタ1(0～5V)*/
	unsigned short		ad10;	/**< @public @brief LPS圧力センサ出力モニタ2(0～5V)*/
	unsigned short		ad11;	/**< @public @brief HPS圧力センサ出力モニタ(0～5V)*/
	unsigned short		ad12;	/**< @public @brief MCU基板上温度モニタ(0～5V)*/
	unsigned short		ad13;	/**< @public @brief 低圧タンク温度モニタ(0～5V)*/
	unsigned short		ad14;	/**< @public @brief 高圧タンク温度モニタ(0～5V)*/
	unsigned short		ad15;	/**< @public @brief ITU温度モニタ(0～5V)*/
	
	unsigned int		total_current;	/**< @public @brief 電流積分値*/
	
	unsigned long long	start_time;	/**< @public @brief 噴射開始時刻*/
	unsigned long long	stop_time;	/**< @public @brief 自動噴射停止時刻*/
	unsigned char		lps_select;	/**< @public @brief 低圧センサ切替*/
	unsigned short		rv_cont;	/**< @public @brief RV参照値*/
	unsigned short		lp_max;		/**< @public @brief 低圧最大圧力*/
	unsigned char		rv_time;	/**< @public @brief RV解放時間*/
	unsigned char		lp_ready_time;	/**< @public @brief 低圧側待機時間*/
	unsigned char		mps_on_stb_time;	/**< @public @brief MPSオン準備時間*/
	unsigned char		tv_open_stb_time;	/**< @public @brief TV開放準備時間*/
	unsigned char		hvps_on_ion;	/**< @public @brief 着火時HVPS利用*/
	unsigned char		ion_check_time;	/**< @public @brief 着火確認時間*/
	unsigned char		ion_count_limit;	/**< @public @brief 着火試行回数制限*/
	unsigned short		mps_temp_max;	/**< @public @brief MPS最大温度*/
	unsigned short		hvps_temp_max;	/**< @public @brief HVPS最大温度*/
	unsigned char		lps_check_time;	/**< @public @brief 低圧確認時間*/
	unsigned char		hvps_on_time1;	/**< @public @brief HVPS使用開始時間1*/
	unsigned char		hvps_on_time2;	/**< @public @brief HVPS使用開始時間2*/
	unsigned char		hvps_on_order;	/**< @public @brief HVPS使用順序*/
	unsigned short		nps_voltage_ref;	/**< @public @brief NPS電圧参照値*/
	unsigned short		aps_current_ref;	/**< @public @brief APS電流参照値*/
	unsigned short		aps_voltage_ref;	/**< @public @brief APS電圧参照値*/
	unsigned short		sps_current_ref;	/**< @public @brief SPS電流参照値*/
	unsigned char		mips_on_count;	/**< @public @brief MIPS起動回数*/
	unsigned char		mips_on_count_limit;	/**< @public @brief MIPS起動制限回数*/
	unsigned char		mips_auto;	/**< @public @brief 自動噴射*/
	
	
	
	unsigned char		cmd_count;	/**< @private @brief MIPSへのCMDカウンタ*/
}	MIPS_STRUCT;


int MIPS_init(MIPS_STRUCT *my_mips, unsigned char ch);
void Debug_MIPS_gain_set(void);
int MIPS_cycle(MIPS_STRUCT *my_mips);
int MIPS_rec(MIPS_STRUCT *my_mips);
int MIPS_debug_message(MIPS_STRUCT* my_mips);
int MIPS_command1(MIPS_STRUCT *my_mips, unsigned char sps, unsigned char nps, unsigned char aps, unsigned char indicator);
int MIPS_command2(MIPS_STRUCT *my_mips, unsigned char onoff);
int MIPS_command3(MIPS_STRUCT *my_mips, unsigned char onoff);
int MIPS_command4(MIPS_STRUCT *my_mips, unsigned char onoff, unsigned char time, unsigned short vlt);
int MIPS_command5(MIPS_STRUCT *my_mips, unsigned char onoff);
int MIPS_command6(MIPS_STRUCT *my_mips, unsigned char address, unsigned long long val);
int MIPS_command7(MIPS_STRUCT *my_mips, unsigned char *data);
int MIPS_command8(MIPS_STRUCT *my_mips);
int MIPS_command9(MIPS_STRUCT *my_mips);

#endif // MIPS_INCLUDE_
