/**
 * @file MIPS.c
 * @brief MIPSとのインターフェースモジュール群です。
 * 
 * MIPS(イオンエンジン)インターフェースモジュールは、ジュピターコーポレーション社MIPSとのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2014.01.17
 */

#include "utility.h"	// Printf()使用時には必要

#include "../../../../Port_Config.h"		//デバッグモードの時には必要

#include "../../../Data_Processing/ascii_conv.h"

#include "MIPS.h"

//#define	MIPS_DEBUG


int		MIPS_Data_Conv(MIPS_STRUCT *my_mips);
void	MIPS_header_insert(MIPS_STRUCT *my_mips);


static unsigned int		mips_dummy;
static union{
	unsigned char	inte[128];
	struct{
		unsigned char	stx[2];
		unsigned char	length[2];
		unsigned char	time[16];
		unsigned char	cmd_count[2];
		unsigned char	cmd_id[1];
		unsigned char	param_and_etx[128 - (2+2+16+2+1)];
	}split;
} mips_tx_frame = {0x80, 0x80, 								// STX
					'0', '0', 									// Length(ヘッダ・フッタ・Lenを除いた数らしい)
					'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 	// Time
					'0', '0', 									// CMD_Count
					'0', 										// CMD_ID
					0x00, 										// PARAM_and_ETX
					};	/**< @brief 送信フレーム*/


static unsigned char	mips_header[2] = {0x80, 0x80};	/**< @brief フレームのヘッダ*/
static unsigned char	mips_footer[2] = {0x81, 0x81};	/**< @brief フレームのフッタ*/

//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief MIPS構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、 MIPS_STRUCT.driver_super に定期受信部のヘッダ,フッタ,フレームサイズ、定期コマンド発行部の情報を記録します。
 * また、初期化と同時に、MIPSに対して出力を「標準出力」のみにするようにコマンドを発行します。
 * @note MIPSインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param MIPS_STRUCT *my_mips : 初期化するMIPS構造体へのポインタ
 * @param unsigned char ch : MIPSが接続されているUARTポート番号
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_init() の戻り値を参照)
 */
int		MIPS_init(MIPS_STRUCT *my_mips, unsigned char ch){
    int		i_ret;
	
	my_mips->rs422_config.ch = ch;
	my_mips->rs422_config.baudrate = 38400;
	my_mips->rs422_config.stop_bit = 1;
	
	my_mips->driver_super.inter_face = RS422;
	
	my_mips->driver_super.periodic_config.rx_header_size = sizeof(mips_header);
	my_mips->driver_super.periodic_config.rx_header = mips_header;
	
	my_mips->driver_super.periodic_config.rx_footer_size = sizeof(mips_footer);
	my_mips->driver_super.periodic_config.rx_footer = mips_footer;
	
	my_mips->driver_super.periodic_config.rx_frame_size = -1;	// 可変長
	my_mips->driver_super.periodic_config.rx_framelength_place = 0;	// フレームサイズデータ無し
	
	my_mips->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_mips->driver_super), &(my_mips->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	return(0);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief MIPS試験用のデバッグモードです。
 * 
 * デバッグコンソール上でMIPSからのステータスを表示したり、MIPSに対しコマンドを送信したりします。
 * @param なし
 * @return なし
 */
void Debug_MIPS(void){
	extern MIPS_STRUCT	mips1;
	u_char				c;
	unsigned int	end_flg = 0;
	int				cnt = 0;
	int				debug_mips_loop = 1;
	int				i_ret;
	unsigned int	tmp = 0;
	unsigned int	param1_tmp, param2_tmp, param3_tmp, param4_tmp;
	unsigned long long	ll_tmp;
	unsigned char	cmd_7_data[48];
	int				i;
	for(i = 0; i < sizeof(cmd_7_data); i++){
		cmd_7_data[i] = i;
	}
	
	//	Channel Setting
	Printf("MIPS Test \n");
	while(!end_flg){
		Printf("  Which channel (0-15) ?\n");
		ScanfUIntD( &tmp );
		if(tmp < 0 || tmp > 15){
			Printf("Illegal Ch Number\n");
		}else{
			end_flg = 1;
		}
	}
	end_flg = 0;
	
	i_ret = MIPS_init(&mips1, (unsigned char)tmp);
	if(i_ret != 0){
		Printf("MIPS Init Error (%d)\n", i_ret);
		return;
	}
	
	Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
	Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
	Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
	Printf("=============  q:Quit  ========================================\n");
	while(debug_mips_loop){
		MilliSleep(5);
		
		i_ret = MIPS_rec(&(mips1));
		if(i_ret == 1){
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
			
			Printf("TLM_Count:%d\n", mips1.tlm_count);
			Printf("TLM_Time:%ld\n", mips1.time);
			
			Printf("MCU_Status:0x%01X\n", mips1.mips_status.bit.mcu);
			
			if(mips1.hvps_status.bit.aps == 0){
				Printf("APS:OFF  ");
			}else if(mips1.hvps_status.bit.aps == 1){
				Printf("APS:ON   ");
			}
			if(mips1.hvps_status.bit.nps == 0){
				Printf("NPS:OFF  ");
			}else if(mips1.hvps_status.bit.nps == 1){
				Printf("NPS:ON   ");
			}
			if(mips1.hvps_status.bit.sps == 0){
				Printf("SPS:OFF  ");
			}else if(mips1.hvps_status.bit.sps == 1){
				Printf("SPS:ON   ");
			}
			if(mips1.hvps_status.bit.indicator == 0){
				Printf("INDICATOR:OFF");
			}else if(mips1.hvps_status.bit.indicator == 1){
				Printf("INDICATOR:ON ");
			}
			Printf("\n");
			
			if(mips1.valve_status.bit.mps == 0){
				Printf("MPS:OFF  ");
			}else if(mips1.valve_status.bit.mps == 1){
				Printf("MPS:ON   ");
			}
			if(mips1.valve_status.bit.bv == 0){
				Printf("BV:OFF   ");
			}else if(mips1.valve_status.bit.bv == 1){
				Printf("BV:ON    ");
			}
			if(mips1.valve_status.bit.rv == 0){
				Printf("RV:OFF   ");
			}else if(mips1.valve_status.bit.rv == 1){
				Printf("RV:ON    ");
			}
			if(mips1.valve_status.bit.tv == 0){
				Printf("TV:OFF   ");
			}else if(mips1.valve_status.bit.tv == 1){
				Printf("TV:ON    ");
			}
			Printf("\n");
			
			Printf("AD00:%5.3f  ", ((float)mips1.ad00) * (5.0 / 0x1000));
			Printf("AD01:%5.3f  ", ((float)mips1.ad01) * (5.0 / 0x1000));
			Printf("AD02:%5.3f  ", ((float)mips1.ad02) * (5.0 / 0x1000));
			Printf("AD03:%5.3f\n", ((float)mips1.ad03) * (5.0 / 0x1000));
			Printf("AD04:%5.3f  ", ((float)mips1.ad04) * (5.0 / 0x1000));
			Printf("AD05:%5.3f  ", ((float)mips1.ad05) * (5.0 / 0x1000));
			Printf("AD06:%5.3f  ", ((float)mips1.ad06) * (5.0 / 0x1000));
			Printf("AD07:%5.3f\n", ((float)mips1.ad07) * (5.0 / 0x1000));
			Printf("AD08:%5.3f  ", ((float)mips1.ad08) * (5.0 / 0x1000));
			Printf("AD09:%5.3f  ", ((float)mips1.ad09) * (5.0 / 0x1000));
			Printf("AD10:%5.3f  ", ((float)mips1.ad10) * (5.0 / 0x1000));
			Printf("AD11:%5.3f\n", ((float)mips1.ad11) * (5.0 / 0x1000));
			Printf("AD12:%5.3f  ", ((float)mips1.ad12) * (5.0 / 0x1000));
			Printf("AD13:%5.3f  ", ((float)mips1.ad13) * (5.0 / 0x1000));
			Printf("AD14:%5.3f  ", ((float)mips1.ad14) * (5.0 / 0x1000));
			Printf("AD15:%5.3f[V]\n", ((float)mips1.ad15) * (5.0 / 0x1000));
			
			Printf("Total_Current:0x%08X\n", mips1.total_current);
			
			
			Printf("Start_Time: %ld\n", mips1.start_time);
			Printf("Stop_Time: %ld\n", mips1.stop_time);
			Printf("LPS_Select: 0x%01X\n", mips1.lps_select);
			Printf("RV_Cont: 0x%03X\n", mips1.rv_cont);
			Printf("LP_Max: 0x%03X\n", mips1.lp_max);
			Printf("RV_Time: 0x%02X\n", mips1.rv_time);
			Printf("LP_Ready_Time: 0x%02X\n", mips1.lp_ready_time);
			Printf("MPS_On_Stb_Time: 0x%02X\n", mips1.mps_on_stb_time);
			Printf("TV_Open_Stb_Time: 0x%02X\n", mips1.tv_open_stb_time);
			Printf("HVPS_On_Ion: 0x%01X\n", mips1.hvps_on_ion);
			Printf("Ion_Check_Time: 0x%02X\n", mips1.ion_check_time);
			Printf("Ion_Count_Limit: 0x%01X\n", mips1.ion_count_limit);
			Printf("MPS_Temp_Max: 0x%03X\n", mips1.mps_temp_max);
			Printf("HVPS_Temp_Max: 0x%03X\n", mips1.hvps_temp_max);
			Printf("LPS_Check_Time: 0x%02X\n", mips1.lps_check_time);
			Printf("HVPS_On_Time1: 0x%02X\n", mips1.hvps_on_time1);
			Printf("HVPS_On_Time2: 0x%02X\n", mips1.hvps_on_time2);
			Printf("HVPS_On_Order: 0x%01X\n", mips1.hvps_on_order);
			Printf("NPS_Voltage_Ref: 0x%03X\n", mips1.nps_voltage_ref);
			Printf("APS_Current_Ref: 0x%03X\n", mips1.aps_current_ref);
			Printf("APS_Voltage_Ref: 0x%03X\n", mips1.aps_voltage_ref);
			Printf("SPS_Current_Ref: 0x%03X\n", mips1.sps_current_ref);
			Printf("MIPS_On_Count: 0x%01X\n", mips1.mips_on_count);
			Printf("MIPS_On_Count_Limit: 0x%01X\n", mips1.mips_on_count_limit);
			Printf("MIPS_Auto: 0x%01X\n", mips1.mips_auto);
		}
		
		if(cnt == 0){
			MIPS_cycle(&(mips1));
		}
		cnt++;
		cnt %= 1000;
		
		c = CheckChar();
		if(c == '1'){
			Printf("  Power_ON/OFF Select (BIN)\n");
			Printf("  bit3:INDICATOR bit2:APS  bit1:NPS  bit0:SPS\n");
			Printf(" -> ");
			ScanfUIntB( &tmp );
			param1_tmp = ((tmp >> 0) & 0x00000001);
			param2_tmp = ((tmp >> 1) & 0x00000001);
			param3_tmp = ((tmp >> 2) & 0x00000001);
			param4_tmp = ((tmp >> 3) & 0x00000001);
			
			Printf("Send %d\n", MIPS_command1(&mips1, (unsigned char)param1_tmp, (unsigned char)param2_tmp, (unsigned char)param3_tmp, (unsigned char)param4_tmp));
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
		}else if(c == '2'){
			Printf("  MPS_ON/OFF Select (0:OFF 1:ON)\n");
			Printf(" -> ");
			ScanfUIntD( &tmp );
			param1_tmp = tmp;
			Printf("Send %d\n", MIPS_command2(&mips1, (unsigned char)param1_tmp));
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
		}else if(c == '3'){
			Printf("  TV_ON/OFF Select (0:OFF 1:ON)\n");
			Printf(" -> ");
			ScanfUIntD( &tmp );
			param1_tmp = tmp;
			Printf("Send %d\n", MIPS_command3(&mips1, (unsigned char)param1_tmp));
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
		}else if(c == '4'){
			Printf("  RV_ON/OFF/AUTO Select (0:OFF 1:ON 2:AUTO)\n");
			Printf(" -> ");
			ScanfUIntD( &tmp );
			param1_tmp = tmp;
			Printf("  Rvauto_Open_Time (DEC:0-255)\n");
			Printf(" -> ");
			ScanfUIntD( &tmp );
			param2_tmp = tmp;
			Printf("  REF_Voltage (HEX:0x0000-0x0FFF)\n");
			Printf(" -> ");
			ScanfUInt( &tmp );
			param3_tmp = tmp;
			Printf("Send %d\n", MIPS_command4(&mips1, (unsigned char)param1_tmp, (unsigned char)param2_tmp, (unsigned short)param3_tmp));
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
		}else if(c == '5'){
			Printf("  BV_ON/OFF Select (0:OFF 1:ON)\n");
			Printf(" -> ");
			ScanfUIntD( &tmp );
			param1_tmp = tmp;
			Printf("Send %d\n", MIPS_command5(&mips1, (unsigned char)param1_tmp));
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
		}else if(c == '6'){
			Printf("  Param_Change_Addr (HEX:0x00-0xFF)\n");
			Printf(" -> ");
			ScanfUInt( &tmp );
			param1_tmp = tmp;
			Printf("  Param_Change_Data_Hi-4byte (HEX:0x00000000-0xFFFFFFFF)\n");
			Printf(" -> ");
			ScanfUInt( &tmp );
			param2_tmp = tmp;
			Printf("  Param_Change_Data_Lo-4byte (HEX:0x00000000-0xFFFFFFFF)\n");
			Printf(" -> ");
			ScanfUInt( &tmp );
			param3_tmp = tmp;
			ll_tmp = 0;
			ll_tmp |= ((unsigned long long)param2_tmp) << 32;
			ll_tmp |= ((unsigned long long)param3_tmp) << 0;
			Printf("Send %d\n", MIPS_command6(&mips1, (unsigned char)param1_tmp, ll_tmp));
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
		}else if(c == '7'){
			Printf("MIPS_command7 has not been implemented in the DebugMode...\n");
				////Printf("0x00-0x30 Data Send %d\n", MIPS_command7(&mips1, cmd_7_data));
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
		}else if(c == '8'){
			Printf("Send %d\n", MIPS_command8(&mips1));
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
		}else if(c == '9'){
			Printf("Send %d\n", MIPS_command9(&mips1));
			Printf("\n");
			Printf("============  1:Command1    2:Command2    3:Command3  =========\n");
			Printf("============  4:Command4    5:Command5    6:Command6  =========\n");
			Printf("============  7:Command7    8:Command8    9:Command9  =========\n");
			Printf("=============  q:Quit  ========================================\n");
		}else if(c == 'q' || c == 'Q'){
			debug_mips_loop = 0;
		}
	}
	
	
	return;
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief MIPSに対して定期コマンドを送信します。
 *
 * 本MIPSは定期コマンド送信が不要なので、この関数は実行しても何も起きません
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_cycle() の戻り値を参照)
 */
int		MIPS_cycle(MIPS_STRUCT *my_mips){
	int		i_ret;
	
		#ifdef	MIPS_DEBUG
			Printf("MIPS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_mips->driver_super), &(my_mips->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief MIPSからのデータパケットを監視し、受信した内容を MIPS_STRUCT に格納します。
 * 
 * 定期コマンド送信周期より早い周期で定期的に実行してください。
 * @note データパケットについては DRIVER_Super_rec() を使用してフレーム同期をとり、
 * フレーム同期がとれた場合に受信内容を MIPS_STRUCT に格納します。
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 上記以外 : データが受信されなかった等(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
int		MIPS_rec(MIPS_STRUCT *my_mips){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret == 1){
			#ifdef	MIPS_DEBUG
				Printf("MIPS: *** Frame ***\n");
			#endif
			MIPS_Data_Conv(my_mips);
	}
	
	return(i_ret);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief MIPS構造体のデータをデバッグコンソール上に表示します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		MIPS_debug_message(MIPS_STRUCT* my_mips){
	Printf("TLM_Count: %d  ", my_mips->tlm_count);
	Printf("TLM_Time: %ld  ", my_mips->time);
	
	DRIVER_Super_debug_message(&(my_mips->driver_super));
	
	
	return(0);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief コマンド1(HVPS)をMIPSへ送信します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @param unsigned char sps : HVPS-SPS_ON/OFF(0:OFF 1:ON)
 * @param unsigned char nps : HVPS-NPS_ON/OFF(0:OFF 1:ON)
 * @param unsigned char aps : HVPS-APS_ON/OFF(0:OFF 1:ON)
 * @param unsigned char indicator : HVPS-INDICATOR_ON/OFF(0:OFF 1:ON)
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		MIPS_command1(MIPS_STRUCT *my_mips, unsigned char sps, unsigned char nps, unsigned char aps, unsigned char indicator){
	int				i_ret;
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	
	
	//存在しない引数の排除
	if((sps != 0) && (sps != 1)){
		sps = 0;
	}
	if((nps != 0) && (nps != 1)){
		nps = 0;
	}
	if((aps != 0) && (aps != 1)){
		aps = 0;
	}
	if((indicator != 0) && (indicator != 1)){
		indicator = 0;
	}
	
	
	MIPS_header_insert(my_mips);
	
	
	//Cmd_ID
	mips_tx_frame.split.cmd_id[0] = '1';	//HVPS
	
	
	//Param1
	char_tmp = 0x00;
	char_tmp |= (sps << 0);
	char_tmp |= (nps << 1);
	char_tmp |= (aps << 2);
	char_tmp |= (indicator << 3);
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[0] = p_tmp[1];
	//mips_tx_frame.split.param_and_etx[1] = p_tmp[1];
	
	
	//ETX
	mips_tx_frame.split.param_and_etx[1] = 0x81;
	mips_tx_frame.split.param_and_etx[2] = 0x81;
	
	
	my_mips->driver_super.non_periodic_config.tx_frame_size = 26;	//HVPS
	
	//Length
	char_tmp = my_mips->driver_super.non_periodic_config.tx_frame_size - 2 - 2 - 2;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.length[0] = p_tmp[0];
	mips_tx_frame.split.length[1] = p_tmp[1];
	
	
	my_mips->driver_super.non_periodic_config.tx_frame = mips_tx_frame.inte;
	
	my_mips->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief コマンド2(MPS)をMIPSへ送信します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @param unsigned char onoff : MPS_ON/OFF(0:OFF 1:ON)
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		MIPS_command2(MIPS_STRUCT *my_mips, unsigned char onoff){
	int				i_ret;
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	
	
	//存在しない引数の排除
	if((onoff != 0) && (onoff != 1)){
		onoff = 0;
	}
	
	
	MIPS_header_insert(my_mips);
	
	
	//Cmd_ID
	mips_tx_frame.split.cmd_id[0] = '2';	//MPS
	
	
	//Param1
	char_tmp = 0x00;
	char_tmp |= (onoff << 0);
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[0] = p_tmp[1];
	//mips_tx_frame.split.param_and_etx[1] = p_tmp[1];
	
	
	//ETX
	mips_tx_frame.split.param_and_etx[1] = 0x81;
	mips_tx_frame.split.param_and_etx[2] = 0x81;
	
	
	my_mips->driver_super.non_periodic_config.tx_frame_size = 26;	//MPS
	
	//Length
	char_tmp = my_mips->driver_super.non_periodic_config.tx_frame_size - 2 - 2 - 2;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.length[0] = p_tmp[0];
	mips_tx_frame.split.length[1] = p_tmp[1];
	
	
	my_mips->driver_super.non_periodic_config.tx_frame = mips_tx_frame.inte;
	
	my_mips->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief コマンド3(TV)をMIPSへ送信します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @param unsigned char onoff : TV_ON/OFF(0:OFF 1:ON)
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		MIPS_command3(MIPS_STRUCT *my_mips, unsigned char onoff){
	int				i_ret;
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	
	
	//存在しない引数の排除
	if((onoff != 0) && (onoff != 1)){
		onoff = 0;
	}
	
	
	MIPS_header_insert(my_mips);
	
	
	//Cmd_ID
	mips_tx_frame.split.cmd_id[0] = '3';	//TV
	
	
	//Param1
	char_tmp = 0x00;
	char_tmp |= (onoff << 0);
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[0] = p_tmp[1];
	//mips_tx_frame.split.param_and_etx[1] = p_tmp[1];
	
	
	//ETX
	mips_tx_frame.split.param_and_etx[1] = 0x81;
	mips_tx_frame.split.param_and_etx[2] = 0x81;
	
	
	my_mips->driver_super.non_periodic_config.tx_frame_size = 26;	//TV
	
	//Length
	char_tmp = my_mips->driver_super.non_periodic_config.tx_frame_size - 2 - 2 - 2;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.length[0] = p_tmp[0];
	mips_tx_frame.split.length[1] = p_tmp[1];
	
	
	my_mips->driver_super.non_periodic_config.tx_frame = mips_tx_frame.inte;
	
	my_mips->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief コマンド4(RV)をMIPSへ送信します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @param unsigned char onoff : RV開閉_ON/OFF/AUTO(0:OFF 1:ON 2:AUTO)
 * @param unsigned char time : RVauto解放Time(0x00～0xFF)
 * @param unsigned short vlt : REF電圧(0x0000～0x0FFF)
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		MIPS_command4(MIPS_STRUCT *my_mips, unsigned char onoff, unsigned char time, unsigned short vlt){
	int				i_ret;
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	
	
	//存在しない引数の排除
	if((onoff != 0) && (onoff != 1) && (onoff != 2)){
		onoff = 0;
	}
	if(vlt > 0x0FFF){
		vlt = 0x0FFF;
	}
	
	
	MIPS_header_insert(my_mips);
	
	
	//Cmd_ID
	mips_tx_frame.split.cmd_id[0] = '4';	//RV
	
	
	//Param1
	char_tmp = 0x00;
	char_tmp |= (onoff << 0);
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[0] = p_tmp[1];
	//mips_tx_frame.split.param_and_etx[1] = p_tmp[1];
	
	
	//Param2
	char_tmp = time;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[1] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[2] = p_tmp[1];
	
	
	//Param3
	short_tmp = vlt;
	p_tmp = (unsigned char *)&short_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[3] = p_tmp[1];
	//mips_tx_frame.split.param_and_etx[4] = p_tmp[1];
	
	p_tmp = (unsigned char *)&short_tmp;
	ret_ascii = hex2ascii(p_tmp[1]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[4] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[5] = p_tmp[1];
	
	
	//ETX
	mips_tx_frame.split.param_and_etx[6] = 0x81;
	mips_tx_frame.split.param_and_etx[7] = 0x81;
	
	
	my_mips->driver_super.non_periodic_config.tx_frame_size = 31;	//RV
	
	//Length
	char_tmp = my_mips->driver_super.non_periodic_config.tx_frame_size - 2 - 2 - 2;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.length[0] = p_tmp[0];
	mips_tx_frame.split.length[1] = p_tmp[1];
	
	
	my_mips->driver_super.non_periodic_config.tx_frame = mips_tx_frame.inte;
	
	my_mips->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief コマンド5(BV)をMIPSへ送信します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @param unsigned char onoff : BV_ON/OFF(0:OFF 1:ON)
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		MIPS_command5(MIPS_STRUCT *my_mips, unsigned char onoff){
	int				i_ret;
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	
	
	//存在しない引数の排除
	if((onoff != 0) && (onoff != 1)){
		onoff = 0;
	}
	
	
	MIPS_header_insert(my_mips);
	
	
	//Cmd_ID
	mips_tx_frame.split.cmd_id[0] = '5';	//BV
	
	
	//Param1
	char_tmp = 0x00;
	char_tmp |= (onoff << 0);
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[0] = p_tmp[1];
	//mips_tx_frame.split.param_and_etx[1] = p_tmp[1];
	
	
	//ETX
	mips_tx_frame.split.param_and_etx[1] = 0x81;
	mips_tx_frame.split.param_and_etx[2] = 0x81;
	
	
	my_mips->driver_super.non_periodic_config.tx_frame_size = 26;	//BV
	
	//Length
	char_tmp = my_mips->driver_super.non_periodic_config.tx_frame_size - 2 - 2 - 2;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.length[0] = p_tmp[0];
	mips_tx_frame.split.length[1] = p_tmp[1];
	
	
	my_mips->driver_super.non_periodic_config.tx_frame = mips_tx_frame.inte;
	
	my_mips->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief コマンド6(パラメータ設定)をMIPSへ送信します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @param unsigned char address : 変更箇所指定(0x00～0xFF)
 * @param unsigned long long val : 変更値(0x0000000000000000～0xFFFFFFFFFFFFFFFF)
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		MIPS_command6(MIPS_STRUCT *my_mips, unsigned char address, unsigned long long val){
	int				i_ret;
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	
	
	MIPS_header_insert(my_mips);
	
	
	//Cmd_ID
	mips_tx_frame.split.cmd_id[0] = '6';	//パラメータ設定
	
	
	//Param1
	char_tmp = address;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[0] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[1] = p_tmp[1];
	
	
	//Param2(可変長)
	ll_tmp = val;
	p_tmp = (unsigned char *)&ll_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[2] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[3] = p_tmp[1];
	
	p_tmp = (unsigned char *)&ll_tmp;
	ret_ascii = hex2ascii(p_tmp[1]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[4] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[5] = p_tmp[1];
	
	p_tmp = (unsigned char *)&ll_tmp;
	ret_ascii = hex2ascii(p_tmp[2]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[6] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[7] = p_tmp[1];
	
	p_tmp = (unsigned char *)&ll_tmp;
	ret_ascii = hex2ascii(p_tmp[3]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[8] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[9] = p_tmp[1];
	
	p_tmp = (unsigned char *)&ll_tmp;
	ret_ascii = hex2ascii(p_tmp[4]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[10] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[11] = p_tmp[1];
	
	p_tmp = (unsigned char *)&ll_tmp;
	ret_ascii = hex2ascii(p_tmp[5]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[12] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[13] = p_tmp[1];
	
	p_tmp = (unsigned char *)&ll_tmp;
	ret_ascii = hex2ascii(p_tmp[6]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[14] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[15] = p_tmp[1];
	
	p_tmp = (unsigned char *)&ll_tmp;
	ret_ascii = hex2ascii(p_tmp[7]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[16] = p_tmp[0];
	mips_tx_frame.split.param_and_etx[17] = p_tmp[1];
	
	if((ll_tmp >= 0x0000000000000000) && (ll_tmp <= 0x000000000000000F)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[3] = 0x81;
		mips_tx_frame.split.param_and_etx[4] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 28;
	}else if((ll_tmp >= 0x0000000000000010) && (ll_tmp <= 0x00000000000000FF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[4] = 0x81;
		mips_tx_frame.split.param_and_etx[5] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 29;
	}else if((ll_tmp >= 0x0000000000000100) && (ll_tmp <= 0x0000000000000FFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[5] = 0x81;
		mips_tx_frame.split.param_and_etx[6] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 30;
	}else if((ll_tmp >= 0x0000000000001000) && (ll_tmp <= 0x000000000000FFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[6] = 0x81;
		mips_tx_frame.split.param_and_etx[7] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 31;
	}else if((ll_tmp >= 0x0000000000010000) && (ll_tmp <= 0x00000000000FFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[7] = 0x81;
		mips_tx_frame.split.param_and_etx[8] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 32;
	}else if((ll_tmp >= 0x0000000000100000) && (ll_tmp <= 0x0000000000FFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[8] = 0x81;
		mips_tx_frame.split.param_and_etx[9] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 33;
	}else if((ll_tmp >= 0x0000000001000000) && (ll_tmp <= 0x000000000FFFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[11];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[8] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[9] = 0x81;
		mips_tx_frame.split.param_and_etx[10] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 34;
	}else if((ll_tmp >= 0x0000000001000000) && (ll_tmp <= 0x00000000FFFFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[10];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[11];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[8] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[9] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[10] = 0x81;
		mips_tx_frame.split.param_and_etx[11] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 35;
	}else if((ll_tmp >= 0x0000000100000000) && (ll_tmp <= 0x0000000FFFFFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[9];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[10];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[11];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[8] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[9] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[10] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[11] = 0x81;
		mips_tx_frame.split.param_and_etx[12] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 36;
	}else if((ll_tmp >= 0x0000001000000000) && (ll_tmp <= 0x000000FFFFFFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[8];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[9];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[10];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[11];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[8] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[9] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[10] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[11] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[12] = 0x81;
		mips_tx_frame.split.param_and_etx[13] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 37;
	}else if((ll_tmp >= 0x0000010000000000) && (ll_tmp <= 0x00000FFFFFFFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[7];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[8];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[9];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[10];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[11];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[8] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[9] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[10] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[11] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[12] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[13] = 0x81;
		mips_tx_frame.split.param_and_etx[14] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 38;
	}else if((ll_tmp >= 0x0000100000000000) && (ll_tmp <= 0x0000FFFFFFFFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[6];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[7];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[8];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[9];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[10];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[11];
		mips_tx_frame.split.param_and_etx[8] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[9] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[10] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[11] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[12] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[13] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[14] = 0x81;
		mips_tx_frame.split.param_and_etx[15] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 39;
	}else if((ll_tmp >= 0x0001000000000000) && (ll_tmp <= 0x000FFFFFFFFFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[5];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[6];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[7];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[8];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[9];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[10];
		mips_tx_frame.split.param_and_etx[8] = mips_tx_frame.split.param_and_etx[11];
		mips_tx_frame.split.param_and_etx[9] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[10] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[11] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[12] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[13] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[14] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[15] = 0x81;
		mips_tx_frame.split.param_and_etx[16] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 40;
	}else if((ll_tmp >= 0x0010000000000000) && (ll_tmp <= 0x00FFFFFFFFFFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[4];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[5];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[6];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[7];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[8];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[9];
		mips_tx_frame.split.param_and_etx[8] = mips_tx_frame.split.param_and_etx[10];
		mips_tx_frame.split.param_and_etx[9] = mips_tx_frame.split.param_and_etx[11];
		mips_tx_frame.split.param_and_etx[10] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[11] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[12] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[13] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[14] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[15] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[16] = 0x81;
		mips_tx_frame.split.param_and_etx[17] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 41;
	}else if((ll_tmp >= 0x0100000000000000) && (ll_tmp <= 0x0FFFFFFFFFFFFFFF)){
		mips_tx_frame.split.param_and_etx[2] = mips_tx_frame.split.param_and_etx[3];
		mips_tx_frame.split.param_and_etx[3] = mips_tx_frame.split.param_and_etx[4];
		mips_tx_frame.split.param_and_etx[4] = mips_tx_frame.split.param_and_etx[5];
		mips_tx_frame.split.param_and_etx[5] = mips_tx_frame.split.param_and_etx[6];
		mips_tx_frame.split.param_and_etx[6] = mips_tx_frame.split.param_and_etx[7];
		mips_tx_frame.split.param_and_etx[7] = mips_tx_frame.split.param_and_etx[8];
		mips_tx_frame.split.param_and_etx[8] = mips_tx_frame.split.param_and_etx[9];
		mips_tx_frame.split.param_and_etx[9] = mips_tx_frame.split.param_and_etx[10];
		mips_tx_frame.split.param_and_etx[10] = mips_tx_frame.split.param_and_etx[11];
		mips_tx_frame.split.param_and_etx[11] = mips_tx_frame.split.param_and_etx[12];
		mips_tx_frame.split.param_and_etx[12] = mips_tx_frame.split.param_and_etx[13];
		mips_tx_frame.split.param_and_etx[13] = mips_tx_frame.split.param_and_etx[14];
		mips_tx_frame.split.param_and_etx[14] = mips_tx_frame.split.param_and_etx[15];
		mips_tx_frame.split.param_and_etx[15] = mips_tx_frame.split.param_and_etx[16];
		mips_tx_frame.split.param_and_etx[16] = mips_tx_frame.split.param_and_etx[17];
		
		//ETX
		mips_tx_frame.split.param_and_etx[17] = 0x81;
		mips_tx_frame.split.param_and_etx[18] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 42;
	}else if((ll_tmp >= 0x1000000000000000) && (ll_tmp <= 0xFFFFFFFFFFFFFFFF)){
		//ETX
		mips_tx_frame.split.param_and_etx[18] = 0x81;
		mips_tx_frame.split.param_and_etx[19] = 0x81;
		my_mips->driver_super.non_periodic_config.tx_frame_size = 43;
	}
	
	
	//Length
	char_tmp = my_mips->driver_super.non_periodic_config.tx_frame_size - 2 - 2 - 2;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.length[0] = p_tmp[0];
	mips_tx_frame.split.length[1] = p_tmp[1];
	
	
	my_mips->driver_super.non_periodic_config.tx_frame = mips_tx_frame.inte;
	
	my_mips->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief コマンド7(パラメータ設定ブロック)をMIPSへ送信します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @param unsigned char *data : データ(48バイト分(実際に関係するのは47バイトと4bit分))
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		MIPS_command7(MIPS_STRUCT *my_mips, unsigned char *data){
	int				i_ret;
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	int i;
	
	
	MIPS_header_insert(my_mips);
	
	
	//Cmd_ID
	mips_tx_frame.split.cmd_id[0] = '7';	//パラメータ設定ブロック
	
	
	//Param1
	char_tmp = data[0];
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.param_and_etx[0 + 0] = p_tmp[1];
	//mips_tx_frame.split.param_and_etx[0 + 1] = p_tmp[1];
	for(i = 1; i < 48; i++){
		char_tmp = data[i];
		p_tmp = (unsigned char *)&char_tmp;
		ret_ascii = hex2ascii(p_tmp[0]);
		p_tmp = (unsigned char *)&ret_ascii;
		mips_tx_frame.split.param_and_etx[(i * 2) + -1] = p_tmp[0];
		mips_tx_frame.split.param_and_etx[(i * 2) + 0] = p_tmp[1];
	}
	
	
	//ETX
	mips_tx_frame.split.param_and_etx[(i * 2) + -1] = 0x81;
	mips_tx_frame.split.param_and_etx[(i * 2) + 0] = 0x81;
	
	
	my_mips->driver_super.non_periodic_config.tx_frame_size = 120;	//パラメータ設定ブロック
	
	//Length
	char_tmp = my_mips->driver_super.non_periodic_config.tx_frame_size - 2 - 2 - 2;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.length[0] = p_tmp[0];
	mips_tx_frame.split.length[1] = p_tmp[1];
	
	
	my_mips->driver_super.non_periodic_config.tx_frame = mips_tx_frame.inte;
	
	my_mips->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief コマンド8(自動噴射開始)をMIPSへ送信します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		MIPS_command8(MIPS_STRUCT *my_mips){
	int				i_ret;
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	
	
	MIPS_header_insert(my_mips);
	
	
	//Cmd_ID
	mips_tx_frame.split.cmd_id[0] = '8';	//自動噴射開始
	
	
	//ETX
	mips_tx_frame.split.param_and_etx[0] = 0x81;
	mips_tx_frame.split.param_and_etx[1] = 0x81;
	
	
	my_mips->driver_super.non_periodic_config.tx_frame_size = 25;	//自動噴射開始
	
	//Length
	char_tmp = my_mips->driver_super.non_periodic_config.tx_frame_size - 2 - 2 - 2;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.length[0] = p_tmp[0];
	mips_tx_frame.split.length[1] = p_tmp[1];
	
	
	my_mips->driver_super.non_periodic_config.tx_frame = mips_tx_frame.inte;
	
	my_mips->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof MIPS_STRUCT
 * @public
 * @brief コマンド9(自動噴射停止)をMIPSへ送信します。
 * 
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @return 1 : 正常終了
 * @return 1以外 : 異常終了(詳細は DRIVER_Super_conf() の戻り値を参照)
 */
int		MIPS_command9(MIPS_STRUCT *my_mips){
	int				i_ret;
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	
	
	MIPS_header_insert(my_mips);
	
	
	//Cmd_ID
	mips_tx_frame.split.cmd_id[0] = '9';	//自動噴射停止
	
	
	//ETX
	mips_tx_frame.split.param_and_etx[0] = 0x81;
	mips_tx_frame.split.param_and_etx[1] = 0x81;
	
	
	my_mips->driver_super.non_periodic_config.tx_frame_size = 25;	//自動噴射停止
	
	//Length
	char_tmp = my_mips->driver_super.non_periodic_config.tx_frame_size - 2 - 2 - 2;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.length[0] = p_tmp[0];
	mips_tx_frame.split.length[1] = p_tmp[1];
	
	
	my_mips->driver_super.non_periodic_config.tx_frame = mips_tx_frame.inte;
	
	my_mips->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_mips->driver_super), &(my_mips->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof MIPS_STRUCT
 * @private
 * @brief フレームデータをMIPS構造体のデータ内容に変換します。
 * 
 * 工学値変換が必要な場合はここに書き込みます。
 * @param MIPS_STRUCT *my_mips : 対象とするMIPS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		MIPS_Data_Conv(MIPS_STRUCT* my_mips){
	/** @brief フレームデータのヘッダ分をオフセットしたポインタ*/
	unsigned char *mips_rx_data = my_mips->driver_super.periodic_rx_frame + sizeof(mips_header) + 2/*Len*/;
	unsigned short	short_tmp;
	
	
	my_mips->tlm_count = 0x00;
	short_tmp = 0;
	short_tmp |= (mips_rx_data[1] << 8);
	short_tmp |= (mips_rx_data[2] << 0);
	my_mips->tlm_count |= (ascii2hex(short_tmp) << 0);
	
	my_mips->time = 0x0000000000000000;
	short_tmp = 0;
	short_tmp |= (mips_rx_data[3] << 8);
	short_tmp |= (mips_rx_data[4] << 0);
	my_mips->time |= (ascii2hex(short_tmp) << 56);
	short_tmp = 0;
	short_tmp |= (mips_rx_data[5] << 8);
	short_tmp |= (mips_rx_data[6] << 0);
	my_mips->time |= (ascii2hex(short_tmp) << 48);
	short_tmp = 0;
	short_tmp |= (mips_rx_data[7] << 8);
	short_tmp |= (mips_rx_data[8] << 0);
	my_mips->time |= (ascii2hex(short_tmp) << 40);
	short_tmp = 0;
	short_tmp |= (mips_rx_data[9] << 8);
	short_tmp |= (mips_rx_data[10] << 0);
	my_mips->time |= (ascii2hex(short_tmp) << 32);
	short_tmp = 0;
	short_tmp |= (mips_rx_data[11] << 8);
	short_tmp |= (mips_rx_data[12] << 0);
	my_mips->time |= (ascii2hex(short_tmp) << 24);
	short_tmp = 0;
	short_tmp |= (mips_rx_data[13] << 8);
	short_tmp |= (mips_rx_data[14] << 0);
	my_mips->time |= (ascii2hex(short_tmp) << 16);
	short_tmp = 0;
	short_tmp |= (mips_rx_data[15] << 8);
	short_tmp |= (mips_rx_data[16] << 0);
	my_mips->time |= (ascii2hex(short_tmp) << 8);
	short_tmp = 0;
	short_tmp |= (mips_rx_data[17] << 8);
	short_tmp |= (mips_rx_data[18] << 0);
	my_mips->time |= (ascii2hex(short_tmp) << 0);
	
	if(mips_rx_data[0] == '1'){	// テレメデータ
		my_mips->mips_status.byte = mips_rx_data[19] - '0';
		
		my_mips->hvps_status.byte = mips_rx_data[20] - '0';
		
		my_mips->valve_status.byte = mips_rx_data[21] - '0';
		
		my_mips->ad00 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[22] << 0);
		my_mips->ad00 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[23] << 8);
		short_tmp |= (mips_rx_data[24] << 0);
		my_mips->ad00 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad01 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[25] << 0);
		my_mips->ad01 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[26] << 8);
		short_tmp |= (mips_rx_data[27] << 0);
		my_mips->ad01 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad02 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[28] << 0);
		my_mips->ad02 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[29] << 8);
		short_tmp |= (mips_rx_data[30] << 0);
		my_mips->ad02 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad03 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[31] << 0);
		my_mips->ad03 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[32] << 8);
		short_tmp |= (mips_rx_data[33] << 0);
		my_mips->ad03 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad04 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[34] << 0);
		my_mips->ad04 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[35] << 8);
		short_tmp |= (mips_rx_data[36] << 0);
		my_mips->ad04 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad05 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[37] << 0);
		my_mips->ad05 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[38] << 8);
		short_tmp |= (mips_rx_data[39] << 0);
		my_mips->ad05 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad06 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[40] << 0);
		my_mips->ad06 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[41] << 8);
		short_tmp |= (mips_rx_data[42] << 0);
		my_mips->ad06 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad07 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[43] << 0);
		my_mips->ad07 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[44] << 8);
		short_tmp |= (mips_rx_data[45] << 0);
		my_mips->ad07 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad08 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[46] << 0);
		my_mips->ad08 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[47] << 8);
		short_tmp |= (mips_rx_data[48] << 0);
		my_mips->ad08 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad09 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[49] << 0);
		my_mips->ad09 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[50] << 8);
		short_tmp |= (mips_rx_data[51] << 0);
		my_mips->ad09 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad10 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[52] << 0);
		my_mips->ad10 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[53] << 8);
		short_tmp |= (mips_rx_data[54] << 0);
		my_mips->ad10 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad11 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[55] << 0);
		my_mips->ad11 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[56] << 8);
		short_tmp |= (mips_rx_data[57] << 0);
		my_mips->ad11 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad12 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[58] << 0);
		my_mips->ad12 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[59] << 8);
		short_tmp |= (mips_rx_data[60] << 0);
		my_mips->ad12 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad13 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[61] << 0);
		my_mips->ad13 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[62] << 8);
		short_tmp |= (mips_rx_data[63] << 0);
		my_mips->ad13 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad14 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[64] << 0);
		my_mips->ad14 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[65] << 8);
		short_tmp |= (mips_rx_data[66] << 0);
		my_mips->ad14 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ad15 = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[67] << 0);
		my_mips->ad15 |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[68] << 8);
		short_tmp |= (mips_rx_data[69] << 0);
		my_mips->ad15 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->total_current = 0x00000000;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[70] << 8);
		short_tmp |= (mips_rx_data[71] << 0);
		my_mips->total_current |= (ascii2hex(short_tmp) << 24);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[72] << 8);
		short_tmp |= (mips_rx_data[73] << 0);
		my_mips->total_current |= (ascii2hex(short_tmp) << 16);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[74] << 8);
		short_tmp |= (mips_rx_data[75] << 0);
		my_mips->total_current |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[76] << 8);
		short_tmp |= (mips_rx_data[77] << 0);
		my_mips->total_current |= (ascii2hex(short_tmp) << 0);
	}
	
	if(mips_rx_data[0] == '3'){	// パラメータ
		my_mips->start_time = 0x0000000000000000;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[19] << 8);
		short_tmp |= (mips_rx_data[20] << 0);
		my_mips->start_time |= (ascii2hex(short_tmp) << 56);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[21] << 8);
		short_tmp |= (mips_rx_data[22] << 0);
		my_mips->start_time |= (ascii2hex(short_tmp) << 48);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[23] << 8);
		short_tmp |= (mips_rx_data[24] << 0);
		my_mips->start_time |= (ascii2hex(short_tmp) << 40);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[25] << 8);
		short_tmp |= (mips_rx_data[26] << 0);
		my_mips->start_time |= (ascii2hex(short_tmp) << 32);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[27] << 8);
		short_tmp |= (mips_rx_data[28] << 0);
		my_mips->start_time |= (ascii2hex(short_tmp) << 24);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[29] << 8);
		short_tmp |= (mips_rx_data[30] << 0);
		my_mips->start_time |= (ascii2hex(short_tmp) << 16);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[31] << 8);
		short_tmp |= (mips_rx_data[32] << 0);
		my_mips->start_time |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[33] << 8);
		short_tmp |= (mips_rx_data[34] << 0);
		my_mips->start_time |= (ascii2hex(short_tmp) << 0);
		
		my_mips->stop_time = 0x0000000000000000;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[35] << 8);
		short_tmp |= (mips_rx_data[36] << 0);
		my_mips->stop_time |= (ascii2hex(short_tmp) << 56);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[37] << 8);
		short_tmp |= (mips_rx_data[38] << 0);
		my_mips->stop_time |= (ascii2hex(short_tmp) << 48);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[39] << 8);
		short_tmp |= (mips_rx_data[40] << 0);
		my_mips->stop_time |= (ascii2hex(short_tmp) << 40);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[41] << 8);
		short_tmp |= (mips_rx_data[42] << 0);
		my_mips->stop_time |= (ascii2hex(short_tmp) << 32);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[43] << 8);
		short_tmp |= (mips_rx_data[44] << 0);
		my_mips->stop_time |= (ascii2hex(short_tmp) << 24);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[45] << 8);
		short_tmp |= (mips_rx_data[46] << 0);
		my_mips->stop_time |= (ascii2hex(short_tmp) << 16);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[47] << 8);
		short_tmp |= (mips_rx_data[48] << 0);
		my_mips->stop_time |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[49] << 8);
		short_tmp |= (mips_rx_data[50] << 0);
		my_mips->stop_time |= (ascii2hex(short_tmp) << 0);
		
		my_mips->lps_select = mips_rx_data[51] - '0';
		
		my_mips->rv_cont = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[52] << 0);
		my_mips->rv_cont |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[53] << 8);
		short_tmp |= (mips_rx_data[54] << 0);
		my_mips->rv_cont |= (ascii2hex(short_tmp) << 0);
		
		my_mips->lp_max = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[55] << 0);
		my_mips->lp_max |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[56] << 8);
		short_tmp |= (mips_rx_data[57] << 0);
		my_mips->lp_max |= (ascii2hex(short_tmp) << 0);
		
		my_mips->rv_time = 0x00;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[58] << 8);
		short_tmp |= (mips_rx_data[59] << 0);
		my_mips->rv_time |= (ascii2hex(short_tmp) << 0);
		
		my_mips->lp_ready_time = 0x00;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[60] << 8);
		short_tmp |= (mips_rx_data[61] << 0);
		my_mips->lp_ready_time |= (ascii2hex(short_tmp) << 0);
		
		my_mips->mps_on_stb_time = 0x00;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[62] << 8);
		short_tmp |= (mips_rx_data[63] << 0);
		my_mips->mps_on_stb_time |= (ascii2hex(short_tmp) << 0);
		
		my_mips->tv_open_stb_time = 0x00;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[64] << 8);
		short_tmp |= (mips_rx_data[65] << 0);
		my_mips->tv_open_stb_time |= (ascii2hex(short_tmp) << 0);
		
		my_mips->hvps_on_ion = mips_rx_data[66] - '0';
		
		my_mips->ion_check_time = 0x00;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[67] << 8);
		short_tmp |= (mips_rx_data[68] << 0);
		my_mips->ion_check_time |= (ascii2hex(short_tmp) << 0);
		
		my_mips->ion_count_limit = mips_rx_data[69] - '0';
		
		my_mips->mps_temp_max = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[70] << 0);
		my_mips->mps_temp_max |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[71] << 8);
		short_tmp |= (mips_rx_data[72] << 0);
		my_mips->mps_temp_max |= (ascii2hex(short_tmp) << 0);
		
		my_mips->hvps_temp_max = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[73] << 0);
		my_mips->hvps_temp_max |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[74] << 8);
		short_tmp |= (mips_rx_data[75] << 0);
		my_mips->hvps_temp_max |= (ascii2hex(short_tmp) << 0);
		
		my_mips->lps_check_time = 0x00;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[76] << 8);
		short_tmp |= (mips_rx_data[77] << 0);
		my_mips->lps_check_time |= (ascii2hex(short_tmp) << 0);
		
		my_mips->hvps_on_time1 = 0x00;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[78] << 8);
		short_tmp |= (mips_rx_data[79] << 0);
		my_mips->hvps_on_time1 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->hvps_on_time2 = 0x00;
		short_tmp = 0;
		short_tmp |= (mips_rx_data[80] << 8);
		short_tmp |= (mips_rx_data[81] << 0);
		my_mips->hvps_on_time2 |= (ascii2hex(short_tmp) << 0);
		
		my_mips->hvps_on_order = mips_rx_data[82] - '0';
		
		my_mips->nps_voltage_ref = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[83] << 0);
		my_mips->nps_voltage_ref |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[84] << 8);
		short_tmp |= (mips_rx_data[85] << 0);
		my_mips->nps_voltage_ref |= (ascii2hex(short_tmp) << 0);
		
		my_mips->aps_current_ref = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[86] << 0);
		my_mips->aps_current_ref |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[87] << 8);
		short_tmp |= (mips_rx_data[88] << 0);
		my_mips->aps_current_ref |= (ascii2hex(short_tmp) << 0);
		
		my_mips->aps_voltage_ref = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[89] << 0);
		my_mips->aps_voltage_ref |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[90] << 8);
		short_tmp |= (mips_rx_data[91] << 0);
		my_mips->aps_voltage_ref |= (ascii2hex(short_tmp) << 0);
		
		my_mips->sps_current_ref = 0x0000;
		short_tmp = 0;
		short_tmp |= (0x00 << 8);
		short_tmp |= (mips_rx_data[92] << 0);
		my_mips->sps_current_ref |= (ascii2hex(short_tmp) << 8);
		short_tmp = 0;
		short_tmp |= (mips_rx_data[93] << 8);
		short_tmp |= (mips_rx_data[94] << 0);
		my_mips->sps_current_ref |= (ascii2hex(short_tmp) << 0);
		
		my_mips->mips_on_count = mips_rx_data[95] - '0';
		
		my_mips->mips_on_count_limit = mips_rx_data[96] - '0';
		
		my_mips->mips_auto = mips_rx_data[97] - '0';
	}
	
	
	return (0);
}

void MIPS_header_insert(MIPS_STRUCT *my_mips){
	unsigned short	ret_ascii;
	unsigned char	char_tmp;
	unsigned short	short_tmp;
	unsigned int	int_tmp;
	unsigned long long	ll_tmp;
	unsigned char	*p_tmp;
	
	
	//Time
	mips_tx_frame.split.time[0] = '0';
	mips_tx_frame.split.time[1] = '0';
	mips_tx_frame.split.time[2] = '0';
	mips_tx_frame.split.time[3] = '0';
	mips_tx_frame.split.time[4] = '0';
	mips_tx_frame.split.time[5] = '0';
	mips_tx_frame.split.time[6] = '0';
	mips_tx_frame.split.time[7] = '0';
	int_tmp = my_time();
	p_tmp = (unsigned char *)&int_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.time[8] = p_tmp[0];
	mips_tx_frame.split.time[9] = p_tmp[1];
	
	p_tmp = (unsigned char *)&int_tmp;
	ret_ascii = hex2ascii(p_tmp[1]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.time[10] = p_tmp[0];
	mips_tx_frame.split.time[11] = p_tmp[1];
	
	p_tmp = (unsigned char *)&int_tmp;
	ret_ascii = hex2ascii(p_tmp[2]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.time[12] = p_tmp[0];
	mips_tx_frame.split.time[13] = p_tmp[1];
	
	p_tmp = (unsigned char *)&int_tmp;
	ret_ascii = hex2ascii(p_tmp[3]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.time[14] = p_tmp[0];
	mips_tx_frame.split.time[15] = p_tmp[1];
	
	
	//Cmd_cnt
	my_mips->cmd_count++;
	char_tmp = my_mips->cmd_count;
	p_tmp = (unsigned char *)&char_tmp;
	ret_ascii = hex2ascii(p_tmp[0]);
	p_tmp = (unsigned char *)&ret_ascii;
	mips_tx_frame.split.cmd_count[0] = p_tmp[0];
	mips_tx_frame.split.cmd_count[1] = p_tmp[1];
	
	return;
}
