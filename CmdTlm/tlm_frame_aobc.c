#include "../source/mw_header.h"
#include "utility.h"

#include <stddef.h> // for NULL

#include "../Equipment_Instance.h"

#include "../Data_Processing/CRC.h"
#include "../AOCS_Process/AOCS_Process.h"
#include "../interval/aocs-interval.h"
#include "cmd_analyze_aobc.h"
#include "cmd_action_aobc.h"

#define _TLM_FRAME_MAIN

#include "tlm_frame_aobc.h"

void TlmCmd_init_code_den(void);

int		TlmCmd_init(void)
{
	int i;
	
	for(i = 0; i < 0xFF; i++){
		tlm_packet_ptr[i] = NULL;
	}
	
	TlmCmd_init_code_den();
	
	return(0);
}

void TlmHeader(unsigned char id)
{	
	unsigned long	now_time  = my_time();
	
	// TLM ID
	TLM_ID = id;
	// Telemetry Count
	TlmCount[id]++;
	TlmCount[id] &= 0xFF;
	// Make Telemetry Packet 
	TlmPacket[TLM_POSITION_STX1]			= TLM_STX;
	TlmPacket[TLM_POSITION_STX2]			= TLM_STX;
	TlmPacket[TLM_POSITION_DISCRIMINATE]	= TLMCMD_TLM;
	TlmPacket[TLM_POSITION_TLM_MODE]		= TLM_ID;
	TlmPacket[TLM_POSITION_TLM_COUNT]		= TlmCount[id];
	TlmPacket[TLM_POSITION_TLM_TIME + 0]	= (unsigned char)((now_time >> 24) & 0xff);
	TlmPacket[TLM_POSITION_TLM_TIME + 1]	= (unsigned char)((now_time >> 16) & 0xff);
	TlmPacket[TLM_POSITION_TLM_TIME + 2]	= (unsigned char)((now_time >> 8) & 0xff);
	TlmPacket[TLM_POSITION_TLM_TIME + 3]	= (unsigned char)(now_time & 0xff);
	TlmPacket[TLM_POSITION_CMD_CODE]		= (unsigned char)(CmdCode & 0xff);
	TlmPacket[TLM_POSITION_CMD_STAT]		= (unsigned char)(CmdSts & 0xFF);	
	TlmPacket[TLM_POSITION_CMD_ERR_STAT]	= (unsigned char)(CmdErrorSts & 0xFF);
	TlmPacket[TLM_POSITION_CMD_COUNT]		= (unsigned char)(CmdCount & 0xff);
}

void	TlmFooter(int	ofs)
{
	unsigned int	ret_crc;
	
	TlmPacket[TLM_POSITION_LENGTH]		= (unsigned char)((TLM_BYTE_COUNT + ofs - 7) & 0xff);	// Packet Size - STX*2 - ETX*2 - CRC*2 - LENGTH	
		
	ret_crc = crc(&(TlmPacket[TLM_POSITION_DISCRIMINATE]), TLM_BYTE_COUNT + ofs - 7);
	TlmPacket[TLM_POSITION_CRC_H + ofs] = (unsigned char)((ret_crc >> 8) & 0xFF);	// CRC H
	TlmPacket[TLM_POSITION_CRC_L + ofs] = (unsigned char)((ret_crc >> 0) & 0xFF);	// CRC L
	TlmPacket[TLM_POSITION_ETX1 + ofs] = TLM_ETX;
	TlmPacket[TLM_POSITION_ETX2 + ofs] = TLM_ETX;
}

void TlmSend(int ofs)
{
	int		i;
	
	
	//	Send
	MOBC_RS422_Data_Send(&mobc1, TlmPacket, TLM_BYTE_COUNT+ofs);
	
	////Printf("TLM: ");
	////for(i = 0; i < TLM_BYTE_COUNT+ofs; i++){
	////	Printf(" %2X",TlmPacket[i]);
	////}
	////Printf("\n");
}


int		TlmPacket_combining(unsigned char tlm_id, int (*TlmDataSet_p)(void)){
	int		ofs;
	
	if(TlmDataSet_p == NULL){
		Printf("Tlm Data Set Function Pointer Error\n");
		return(-2);
	}
	
	TlmHeader(tlm_id);
	if((ofs = (*TlmDataSet_p)()) < 0)
	{
		Printf("Tlm Data Set Error\n");
		return(-1);
	}
	TlmFooter(ofs);
	return (ofs);
}


int		MakeTlmPacket(TLM_MODE_AOBC_ENUM	mode)
{
	static	unsigned char		times;
	static	TLM_MODE_AOBC_ENUM		last_mode;
	unsigned char	tlm_id;
	int		(*TlmDataSet_p)(void);
	
	TlmDataSet_p = NULL;
	
	if(mode == last_mode){
		times++;
	}else{
		times = 0;
		last_mode = mode;
	}


/*
This pattern is a "separator".
This should not be changed.
This should not be used in other places.
*/
//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##




	switch(mode){
		case TLM_MODE_SAFE:
			if(times == 2-1){
				tlm_id = TLM_AOBC_40_ID;
				TlmDataSet_p = TLM_AOBC_40;
			}else if(times == 4-1){
				tlm_id = TLM_AOBC_41_ID;
				TlmDataSet_p = TLM_AOBC_41;
			}else if(times == 6-1){
				tlm_id = TLM_AOBC_42_ID;
				TlmDataSet_p = TLM_AOBC_42;
			}else if(times == 8-1){
				tlm_id = TLM_AOBC_43_ID;
				TlmDataSet_p = TLM_AOBC_43;
			}else if(times == 10-1){
				tlm_id = TLM_AOBC_44_ID;
				TlmDataSet_p = TLM_AOBC_44;
			}else if(times == 12-1){
				tlm_id = TLM_AOBC_45_ID;
				TlmDataSet_p = TLM_AOBC_45;
			}else if(times == 14-1){
				tlm_id = TLM_AOBC_201_ID;
				TlmDataSet_p = TLM_AOBC_201;
			}else if(times == 16-1){
				tlm_id = TLM_AOBC_202_ID;
				TlmDataSet_p = TLM_AOBC_202;
			}else if(times == 20-1){
				times = -1;
				return (0);
			}else{
				// Data Packet Do Not Make
				return (0);
			}
		break;
		
		case TLM_MODE_SUNSHINE:
			if(times == 2-1){
				tlm_id = TLM_AOBC_40_ID;
				TlmDataSet_p = TLM_AOBC_40;
			}else if(times == 4-1){
				tlm_id = TLM_AOBC_41_ID;
				TlmDataSet_p = TLM_AOBC_41;
			}else if(times == 6-1){
				tlm_id = TLM_AOBC_42_ID;
				TlmDataSet_p = TLM_AOBC_42;
			}else if(times == 8-1){
				tlm_id = TLM_AOBC_43_ID;
				TlmDataSet_p = TLM_AOBC_43;
			}else if(times == 10-1){
				tlm_id = TLM_AOBC_44_ID;
				TlmDataSet_p = TLM_AOBC_44;
			}else if(times == 12-1){
				tlm_id = TLM_AOBC_45_ID;
				TlmDataSet_p = TLM_AOBC_45;
			}else if(times == 14-1){
				tlm_id = TLM_AOBC_201_ID;
				TlmDataSet_p = TLM_AOBC_201;
			}else if(times == 16-1){
				tlm_id = TLM_AOBC_202_ID;
				TlmDataSet_p = TLM_AOBC_202;
			}else if(times == 20-1){
				times = -1;
				return (0);
			}else{
				// Data Packet Do Not Make
				return (0);
			}
		break;
		
		case TLM_MODE_SUNSHADE:
			if(times == 2-1){
				tlm_id = TLM_AOBC_40_ID;
				TlmDataSet_p = TLM_AOBC_40;
			}else if(times == 4-1){
				tlm_id = TLM_AOBC_41_ID;
				TlmDataSet_p = TLM_AOBC_41;
			}else if(times == 6-1){
				tlm_id = TLM_AOBC_42_ID;
				TlmDataSet_p = TLM_AOBC_42;
			}else if(times == 8-1){
				tlm_id = TLM_AOBC_43_ID;
				TlmDataSet_p = TLM_AOBC_43;
			}else if(times == 10-1){
				tlm_id = TLM_AOBC_44_ID;
				TlmDataSet_p = TLM_AOBC_44;
			}else if(times == 12-1){
				tlm_id = TLM_AOBC_45_ID;
				TlmDataSet_p = TLM_AOBC_45;
			}else if(times == 14-1){
				tlm_id = TLM_AOBC_201_ID;
				TlmDataSet_p = TLM_AOBC_201;
			}else if(times == 16-1){
				tlm_id = TLM_AOBC_202_ID;
				TlmDataSet_p = TLM_AOBC_202;
			}else if(times == 20-1){
				times = -1;
				return (0);
			}else{
				// Data Packet Do Not Make
				return (0);
			}
		break;
		
		case TLM_MODE_ALL:
			if(times == 2-1){
				tlm_id = TLM_AOBC_40_ID;
				TlmDataSet_p = TLM_AOBC_40;
			}else if(times == 4-1){
				tlm_id = TLM_AOBC_41_ID;
				TlmDataSet_p = TLM_AOBC_41;
			}else if(times == 6-1){
				tlm_id = TLM_AOBC_42_ID;
				TlmDataSet_p = TLM_AOBC_42;
			}else if(times == 8-1){
				tlm_id = TLM_AOBC_43_ID;
				TlmDataSet_p = TLM_AOBC_43;
			}else if(times == 10-1){
				tlm_id = TLM_AOBC_44_ID;
				TlmDataSet_p = TLM_AOBC_44;
			}else if(times == 12-1){
				tlm_id = TLM_AOBC_45_ID;
				TlmDataSet_p = TLM_AOBC_45;
			}else if(times == 14-1){
				tlm_id = TLM_AOBC_201_ID;
				TlmDataSet_p = TLM_AOBC_201;
			}else if(times == 16-1){
				tlm_id = TLM_AOBC_202_ID;
				TlmDataSet_p = TLM_AOBC_202;
			}else if(times == 20-1){
				times = -1;
				return (0);
			}else{
				// Data Packet Do Not Make
				return (0);
			}
		break;
		
		default:
			// Data Packet Do Not Make
			return (0);
		break;
	}
	
	// Data Packet Combining
	return (TlmPacket_combining(tlm_id, TlmDataSet_p));
}


void TlmCmd_init_code_den(void){ 
	tlm_packet_ptr[ 40 ] = TLM_AOBC_40 ;
	tlm_packet_ptr[ 41 ] = TLM_AOBC_41 ;
	tlm_packet_ptr[ 42 ] = TLM_AOBC_42 ;
	tlm_packet_ptr[ 43 ] = TLM_AOBC_43 ;
	tlm_packet_ptr[ 44 ] = TLM_AOBC_44 ;
	tlm_packet_ptr[ 45 ] = TLM_AOBC_45 ;
	tlm_packet_ptr[ 201 ] = TLM_AOBC_201 ;
	tlm_packet_ptr[ 202 ] = TLM_AOBC_202 ;
	return;
}


int TLM_AOBC_40(void){
	unsigned char	*p;
	
	TlmPacket[TLM_POSITION_MAIN + 0] = (unsigned char)( AOCS_mode  & 0xFF);  //	姿勢制御モードを表す。
	p = (unsigned char *)&( AOCS_qd[1] );	//	決定姿勢の四元数1(ノーマライズされている＆０成分は常に正）
	TlmPacket[TLM_POSITION_MAIN + 9 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_qd[2] );	//	決定姿勢の四元数2
	TlmPacket[TLM_POSITION_MAIN + 17 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 17 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 17 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 17 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 17 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 17 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 17 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 17 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_qd[3] );	//	決定姿勢の四元数3
	TlmPacket[TLM_POSITION_MAIN + 25 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 25 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 25 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 25 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 25 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 25 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 25 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 25 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_failure_flag );	//	姿勢制御系機器の故障フラグ
	TlmPacket[TLM_POSITION_MAIN + 33 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 33 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 35] = (unsigned char)( nsas1.error  & 0xFF);  //	NSAS1 エラー
	TlmPacket[TLM_POSITION_MAIN + 36] = (unsigned char)( nsas1.id  & 0xFF);  //	NSAS1 固有ID
	TlmPacket[TLM_POSITION_MAIN + 37] = (unsigned char)( nsas1.gain_flag  & 0xFF);  //	NSAS1ゲインフラグ
	TlmPacket[TLM_POSITION_MAIN + 38] = (unsigned char)( nsas1.sun_flag  & 0xFF);  //	NSAS1 サンフラグ
	TlmPacket[TLM_POSITION_MAIN + 39] = (unsigned char)( nsas1.gain  & 0xFF);  //	NSAS1 ゲイン
	TlmPacket[TLM_POSITION_MAIN + 40] = (unsigned char)( nsas1.tempe  & 0xFF);  //	NSAS1 温度
	TlmPacket[TLM_POSITION_MAIN + 41] = (unsigned char)( nsas1.x  & 0xFF);  //	NSAS1 角度のx成分
	TlmPacket[TLM_POSITION_MAIN + 42] = (unsigned char)( nsas1.y  & 0xFF);  //	NSAS1 角度のy成分
	p = (unsigned char *)&( nsas1.driver_super.update_time );	//	NSAS１データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 43 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 47] = (unsigned char)( nsas2.error  & 0xFF);  //	NSAS2 エラー
	TlmPacket[TLM_POSITION_MAIN + 48] = (unsigned char)( nsas2.id  & 0xFF);  //	NSAS2 固有ID
	TlmPacket[TLM_POSITION_MAIN + 49] = (unsigned char)( nsas2.gain_flag  & 0xFF);  //	NSAS2ゲインフラグ
	TlmPacket[TLM_POSITION_MAIN + 50] = (unsigned char)( nsas2.sun_flag  & 0xFF);  //	NSAS2 サンフラグ
	TlmPacket[TLM_POSITION_MAIN + 51] = (unsigned char)( nsas2.gain  & 0xFF);  //	NSAS2 ゲイン
	TlmPacket[TLM_POSITION_MAIN + 52] = (unsigned char)( nsas2.tempe  & 0xFF);  //	NSAS2 温度
	TlmPacket[TLM_POSITION_MAIN + 53] = (unsigned char)( nsas2.x  & 0xFF);  //	NSAS2 角度のx成分
	TlmPacket[TLM_POSITION_MAIN + 54] = (unsigned char)( nsas2.y  & 0xFF);  //	NSAS2 角度のy成分
	p = (unsigned char *)&( nsas2.driver_super.update_time );	//	NSAS2データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 55 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 59] = (unsigned char)( nsas3.error  & 0xFF);  //	NSAS3 エラー
	TlmPacket[TLM_POSITION_MAIN + 60] = (unsigned char)( nsas3.id  & 0xFF);  //	NSAS3 固有ID
	TlmPacket[TLM_POSITION_MAIN + 61] = (unsigned char)( nsas3.gain_flag  & 0xFF);  //	NSAS3ゲインフラグ
	TlmPacket[TLM_POSITION_MAIN + 62] = (unsigned char)( nsas3.sun_flag  & 0xFF);  //	NSAS3 サンフラグ
	TlmPacket[TLM_POSITION_MAIN + 63] = (unsigned char)( nsas3.gain  & 0xFF);  //	NSAS3 ゲイン
	TlmPacket[TLM_POSITION_MAIN + 64] = (unsigned char)( nsas3.tempe  & 0xFF);  //	NSAS3 温度
	TlmPacket[TLM_POSITION_MAIN + 65] = (unsigned char)( nsas3.x  & 0xFF);  //	NSAS3 角度のx成分
	TlmPacket[TLM_POSITION_MAIN + 66] = (unsigned char)( nsas3.y  & 0xFF);  //	NSAS3 角度のy成分
	p = (unsigned char *)&( nsas3.driver_super.update_time );	//	NSAS3データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 67 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gas1.x );	//	GAS-X軸信号の電圧値
	TlmPacket[TLM_POSITION_MAIN + 71 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 71 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gas1.y );	//	GAS-Y軸信号の電圧値
	TlmPacket[TLM_POSITION_MAIN + 73 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gas1.z );	//	GAS-Z軸信号の電圧値
	TlmPacket[TLM_POSITION_MAIN + 75 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 75 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gas1.ref );	//	GASのReference信号の電圧値
	TlmPacket[TLM_POSITION_MAIN + 77 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 77 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gas1.driver_super.update_time );	//	gasデータパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 79 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 83] = (unsigned char)( gyro1.counter  & 0xFF);  //	GYRO1のカウンタ出力値
	p = (unsigned char *)&( gyro1.status.byte[0] );	//	GYRO1のステータス出力値
	TlmPacket[TLM_POSITION_MAIN + 84 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 84 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.del_x );	//	GYRO1 x方向の角速度
	TlmPacket[TLM_POSITION_MAIN + 86 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 86 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 86 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 86 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.del_y );	//	GYRO1 y方向の角速度
	TlmPacket[TLM_POSITION_MAIN + 90 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 90 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 90 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 90 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.del_z );	//	GYRO1 z方向の角速度
	TlmPacket[TLM_POSITION_MAIN + 94 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 94 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 94 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 94 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.current_x );	//	GYRO1 x軸SLD電流
	TlmPacket[TLM_POSITION_MAIN + 98 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 98 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.current_y );	//	GYRO1 y軸SLD電流
	TlmPacket[TLM_POSITION_MAIN + 100 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 100 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.current_z );	//	GYRO1 z軸SLD電流
	TlmPacket[TLM_POSITION_MAIN + 102 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 102 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.tempe );	//	GYRO1温度
	TlmPacket[TLM_POSITION_MAIN + 104 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.driver_super.update_time );	//	gyro1データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 106 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 106 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 106 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 106 + 3] = (unsigned char)(*p);	p++;
	return(  110 );
 }



int TLM_AOBC_41(void){
	unsigned char	*p;
	
	TlmPacket[TLM_POSITION_MAIN + 0] = (unsigned char)( rw1.rw_rx_sts.mess_no  & 0xFF);  //	RW1のメッセージ番号
	TlmPacket[TLM_POSITION_MAIN + 1] = (unsigned char)( rw1.rw_rx_sts.sts1.byte  & 0xFF);  //	RW1のステータス1
	TlmPacket[TLM_POSITION_MAIN + 2] = (unsigned char)( rw1.rw_rx_sts.sts2.byte  & 0xFF);  //	RW1のステータス2

	p = (unsigned char *)&( rw1.rw_rx_sts.sts3 );	//	RW1のステータス3
	TlmPacket[TLM_POSITION_MAIN + 3 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 3 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1.rw_rx_sts.sts4 );	//	RW1のステータス4
	TlmPacket[TLM_POSITION_MAIN + 5 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 5 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1.rw_rx_sts.sts5 );	//	RW1のステータス５
	TlmPacket[TLM_POSITION_MAIN + 7 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 7 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1.driver_super.update_time );	//	RW1データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 9 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 9 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 13] = (unsigned char)( rw1.rw_tx_comm.mess_no  & 0xFF);  //	メッセージ#(送り手)
	TlmPacket[TLM_POSITION_MAIN + 14] = (unsigned char)( rw1.rw_tx_comm.comm1.byte  & 0xFF);  //	コマンド
	p = (unsigned char *)&( rw1.rw_tx_comm.comm2 );	//	電圧
	TlmPacket[TLM_POSITION_MAIN + 15 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 15 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 17] = (unsigned char)( rw2.rw_rx_sts.mess_no  & 0xFF);  //	RW2のメッセージ番号
	TlmPacket[TLM_POSITION_MAIN + 18] = (unsigned char)( rw2.rw_rx_sts.sts1.byte  & 0xFF);  //	RW2のステータス1
	TlmPacket[TLM_POSITION_MAIN + 19] = (unsigned char)( rw2.rw_rx_sts.sts2.byte  & 0xFF);  //	RW2のステータス2
	p = (unsigned char *)&( rw2.rw_rx_sts.sts3 );	//	RW2のステータス3
	TlmPacket[TLM_POSITION_MAIN + 20 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 20 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw2.rw_rx_sts.sts4 );	//	RW2のステータス4
	TlmPacket[TLM_POSITION_MAIN + 22 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 22 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw2.rw_rx_sts.sts5 );	//	RW2のステータス５
	TlmPacket[TLM_POSITION_MAIN + 24 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw2.driver_super.update_time );	//	RW2データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 26 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 30] = (unsigned char)( rw2.rw_tx_comm.mess_no  & 0xFF);  //	メッセージ#(送り手)
	TlmPacket[TLM_POSITION_MAIN + 31] = (unsigned char)( rw2.rw_tx_comm.comm1.byte  & 0xFF);  //	コマンド
	p = (unsigned char *)&( rw2.rw_tx_comm.comm2 );	//	電圧
	TlmPacket[TLM_POSITION_MAIN + 32 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 34] = (unsigned char)( rw3.rw_rx_sts.mess_no  & 0xFF);  //	RW3のメッセージ番号
	TlmPacket[TLM_POSITION_MAIN + 35] = (unsigned char)( rw3.rw_rx_sts.sts1.byte  & 0xFF);  //	RW3のステータス1
	TlmPacket[TLM_POSITION_MAIN + 36] = (unsigned char)( rw3.rw_rx_sts.sts2.byte  & 0xFF);  //	RW3のステータス2
	p = (unsigned char *)&( rw3.rw_rx_sts.sts3 );	//	RW3のステータス3
	TlmPacket[TLM_POSITION_MAIN + 37 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 37 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw3.rw_rx_sts.sts4 );	//	RW3のステータス4
	TlmPacket[TLM_POSITION_MAIN + 39 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 39 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw3.rw_rx_sts.sts5 );	//	RW3のステータス５
	TlmPacket[TLM_POSITION_MAIN + 41 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 41 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw3.driver_super.update_time );	//	RW3データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 43 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 47] = (unsigned char)( rw3.rw_tx_comm.mess_no  & 0xFF);  //	メッセージ#(送り手)
	TlmPacket[TLM_POSITION_MAIN + 48] = (unsigned char)( rw3.rw_tx_comm.comm1.byte  & 0xFF);  //	コマンド
	p = (unsigned char *)&( rw3.rw_tx_comm.comm2 );	//	電圧
	TlmPacket[TLM_POSITION_MAIN + 49 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 49 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 51] = (unsigned char)( rw4.rw_rx_sts.mess_no  & 0xFF);  //	RW4のメッセージ番号
	TlmPacket[TLM_POSITION_MAIN + 52] = (unsigned char)( rw4.rw_rx_sts.sts1.byte  & 0xFF);  //	RW4のステータス1
	TlmPacket[TLM_POSITION_MAIN + 53] = (unsigned char)( rw4.rw_rx_sts.sts2.byte  & 0xFF);  //	RW4のステータス2
	p = (unsigned char *)&( rw4.rw_rx_sts.sts3 );	//	RW4のステータス3
	TlmPacket[TLM_POSITION_MAIN + 54 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 54 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw4.rw_rx_sts.sts4 );	//	RW4のステータス4
	TlmPacket[TLM_POSITION_MAIN + 56 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 56 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw4.rw_rx_sts.sts5 );	//	RW4のステータス５
	TlmPacket[TLM_POSITION_MAIN + 58 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 58 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw4.driver_super.update_time );	//	RW4データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 60 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 64] = (unsigned char)( rw4.rw_tx_comm.mess_no  & 0xFF);  //	メッセージ#(送り手)
	TlmPacket[TLM_POSITION_MAIN + 65] = (unsigned char)( rw4.rw_tx_comm.comm1.byte  & 0xFF);  //	コマンド
	p = (unsigned char *)&( rw4.rw_tx_comm.comm2 );	//	電圧
	TlmPacket[TLM_POSITION_MAIN + 66 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 66 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 68] = (unsigned char)( gps1.status1.byte  & 0xFF);  //	GPS1のｽﾃｰﾀｽ1
	p = (unsigned char *)&( gps1.latitude );	//	GPS1の緯度
	TlmPacket[TLM_POSITION_MAIN + 69 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 69 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 69 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 69 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.longitude );	//	GPS1の経度
	TlmPacket[TLM_POSITION_MAIN + 73 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.altitude );	//	GPS1の高度
	TlmPacket[TLM_POSITION_MAIN + 77 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 77 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 77 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 77 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.vector_x );	//	GPS1X方向の出力値
	TlmPacket[TLM_POSITION_MAIN + 81 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.vector_y );	//	GPS1Y方向の出力値
	TlmPacket[TLM_POSITION_MAIN + 89 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.vector_z );	//	GPS1Z方向の出力値
	TlmPacket[TLM_POSITION_MAIN + 97 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.pdop );	//	GPS1のPDOP
	TlmPacket[TLM_POSITION_MAIN + 105 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 105 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 107] = (unsigned char)( gps1.utc.year  & 0xFF);  //	GPS1のUTCの年（西暦の下二桁）
	TlmPacket[TLM_POSITION_MAIN + 108] = (unsigned char)( gps1.utc.month  & 0xFF);  //	GPS1のUTCの月
	TlmPacket[TLM_POSITION_MAIN + 109] = (unsigned char)( gps1.utc.day  & 0xFF);  //	GPS1のUTCの日
	TlmPacket[TLM_POSITION_MAIN + 110] = (unsigned char)( gps1.utc.hour  & 0xFF);  //	GPS1のUTCの時
	TlmPacket[TLM_POSITION_MAIN + 111] = (unsigned char)( gps1.utc.min  & 0xFF);  //	GPS1のUTCの分
	TlmPacket[TLM_POSITION_MAIN + 112] = (unsigned char)( gps1.utc.sec  & 0xFF);  //	GPS1のUTCの秒
	TlmPacket[TLM_POSITION_MAIN + 113] = (unsigned char)( gps1.alive_sat  & 0xFF);  //	GPS1の正常な衛星数
	TlmPacket[TLM_POSITION_MAIN + 114] = (unsigned char)( gps1.visible_sat  & 0xFF);  //	GPS1の可視衛星数
	TlmPacket[TLM_POSITION_MAIN + 115] = (unsigned char)( gps1.delay_time  & 0xFF);  //	GPS1の測位遅延時間
	TlmPacket[TLM_POSITION_MAIN + 116] = (unsigned char)( gps1.pps  & 0xFF);  //	GPS1のPPS補正
	p = (unsigned char *)&( gps1.driver_super.update_time );	//	GPS1データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 117 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 117 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 117 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 117 + 3] = (unsigned char)(*p);	p++;
	return(  121 );
 }



int TLM_AOBC_42(void){
	unsigned char	*p;
	
	p = (unsigned char *)&( stt1.driver_super.update_time );	//	STT1データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 0 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_imager_temperature );	//	STT1のマスタイメージセンサ温度
	TlmPacket[TLM_POSITION_MAIN + 4 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.capture_id );	//	STT1の1撮影ごとにインクリメントされるカウンタ
	TlmPacket[TLM_POSITION_MAIN + 8 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.attitude[0] );	//	STT1の四元数1
	TlmPacket[TLM_POSITION_MAIN + 10 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 10 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 10 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 10 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 10 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 10 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 10 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 10 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.attitude[1] );	//	STT1の四元数2
	TlmPacket[TLM_POSITION_MAIN + 18 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.attitude[2] );	//	STT1の四元数3
	TlmPacket[TLM_POSITION_MAIN + 26 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.attitude[3] );	//	STT1の四元数4
	TlmPacket[TLM_POSITION_MAIN + 34 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 34 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 34 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 34 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 34 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 34 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 34 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 34 + 7] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 42] = (unsigned char)( stt1.driver_super.rx_count  & 0xFF);  //	STT1のデータパケット受信回数
	p = (unsigned char *)&( stt1.error_covariance_matrix[0][0]  );	//	STT1の誤差共分散1
	TlmPacket[TLM_POSITION_MAIN + 43 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 43 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[0][1] );	//	STT1の誤差共分散2
	TlmPacket[TLM_POSITION_MAIN + 51 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 51 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 51 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 51 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 51 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 51 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 51 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 51 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[0][2] );	//	STT1の誤差共分散3
	TlmPacket[TLM_POSITION_MAIN + 59 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 59 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 59 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 59 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 59 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 59 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 59 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 59 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[1][0]  );	//	STT1の誤差共分散4
	TlmPacket[TLM_POSITION_MAIN + 67 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 67 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[1][1] );	//	STT1の誤差共分散5
	TlmPacket[TLM_POSITION_MAIN + 75 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 75 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 75 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 75 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 75 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 75 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 75 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 75 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[1][2] );	//	STT1の誤差共分散6
	TlmPacket[TLM_POSITION_MAIN + 83 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 83 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 83 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 83 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 83 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 83 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 83 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 83 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[2][0]  );	//	STT1の誤差共分散7
	TlmPacket[TLM_POSITION_MAIN + 91 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 91 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 91 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 91 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 91 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 91 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 91 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 91 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[2][1] );	//	STT1の誤差共分散8
	TlmPacket[TLM_POSITION_MAIN + 99 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 99 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 99 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 99 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 99 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 99 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 99 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 99 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[2][2] );	//	STT1の誤差共分散9
	TlmPacket[TLM_POSITION_MAIN + 107 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 107 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 107 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 107 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 107 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 107 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 107 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 107 + 7] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 115] = (unsigned char)( stt1.master_detected_star_count  & 0xFF);  //	マスタの検出恒星数
	p = (unsigned char *)&( stt1.master_estimation_status );	//	マスタの姿勢推定ステータス
	TlmPacket[TLM_POSITION_MAIN + 116 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 116 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 116 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 116 + 3] = (unsigned char)(*p);	p++;
	return(  120 );
 }



int TLM_AOBC_43(void){
	unsigned char	*p;
	
	p = (unsigned char *)&( stt1.master_star_info[0].hipparcos_id );	//	マスタの検出恒星情報１: Hipparcos ID
	TlmPacket[TLM_POSITION_MAIN + 0 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[0].luminance );	//	マスタの検出恒星情報１: Luminance
	TlmPacket[TLM_POSITION_MAIN + 4 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[0].tan_azimuth );	//	マスタの検出恒星情報１: tan_azimuth
	TlmPacket[TLM_POSITION_MAIN + 8 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[0].tan_elevation );	//	マスタの検出恒星情報１: tan_elevation
	TlmPacket[TLM_POSITION_MAIN + 16 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[1].hipparcos_id );	//	マスタの検出恒星情報2: Hipparcos ID
	TlmPacket[TLM_POSITION_MAIN + 24 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[1].luminance );	//	マスタの検出恒星情報2: Luminance
	TlmPacket[TLM_POSITION_MAIN + 28 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[1].tan_azimuth );	//	マスタの検出恒星情報2: tan_azimuth
	TlmPacket[TLM_POSITION_MAIN + 32 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[1].tan_elevation );	//	マスタの検出恒星情報2: tan_elevation
	TlmPacket[TLM_POSITION_MAIN + 40 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[2].hipparcos_id );	//	マスタの検出恒星情報3: Hipparcos ID
	TlmPacket[TLM_POSITION_MAIN + 48 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 48 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 48 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 48 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[2].luminance );	//	マスタの検出恒星情報3: Luminance
	TlmPacket[TLM_POSITION_MAIN + 52 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[2].tan_azimuth );	//	マスタの検出恒星情報3: tan_azimuth
	TlmPacket[TLM_POSITION_MAIN + 56 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 56 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 56 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 56 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 56 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 56 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 56 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 56 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[2].tan_elevation );	//	マスタの検出恒星情報3: tan_elevation
	TlmPacket[TLM_POSITION_MAIN + 64 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 64 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 64 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 64 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 64 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 64 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 64 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 64 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[3].hipparcos_id );	//	マスタの検出恒星情報4: Hipparcos ID
	TlmPacket[TLM_POSITION_MAIN + 72 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 72 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 72 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 72 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[3].luminance );	//	マスタの検出恒星情報4: Luminance
	TlmPacket[TLM_POSITION_MAIN + 76 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[3].tan_azimuth );	//	マスタの検出恒星情報4: tan_azimuth
	TlmPacket[TLM_POSITION_MAIN + 80 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 80 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 80 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 80 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 80 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 80 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 80 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 80 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[3].tan_elevation );	//	マスタの検出恒星情報4: tan_elevation
	TlmPacket[TLM_POSITION_MAIN + 88 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 88 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 88 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 88 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 88 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 88 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 88 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 88 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[4].hipparcos_id );	//	マスタの検出恒星情報5: Hipparcos ID
	TlmPacket[TLM_POSITION_MAIN + 96 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[4].luminance );	//	マスタの検出恒星情報5: Luminance
	TlmPacket[TLM_POSITION_MAIN + 100 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 100 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 100 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 100 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[4].tan_azimuth );	//	マスタの検出恒星情報5: tan_azimuth
	TlmPacket[TLM_POSITION_MAIN + 104 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[4].tan_elevation );	//	マスタの検出恒星情報5: tan_elevation
	TlmPacket[TLM_POSITION_MAIN + 112 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[5].hipparcos_id );	//	マスタの検出恒星情報6: Hipparcos ID
	TlmPacket[TLM_POSITION_MAIN + 120 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[5].luminance );	//	マスタの検出恒星情報6: Luminance
	TlmPacket[TLM_POSITION_MAIN + 124 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 124 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 124 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 124 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[5].tan_azimuth );	//	マスタの検出恒星情報6: tan_azimuth
	TlmPacket[TLM_POSITION_MAIN + 128 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.master_star_info[5].tan_elevation );	//	マスタの検出恒星情報6: tan_elevation
	TlmPacket[TLM_POSITION_MAIN + 136 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 7] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 144] = (unsigned char)( rcs1.flag.byte  & 0xFF);  //	フラグ内容 
	TlmPacket[TLM_POSITION_MAIN + 145] = (unsigned char)( rcs1.status.byte  & 0xFF);  //	ステータス情報
	TlmPacket[TLM_POSITION_MAIN + 146] = (unsigned char)( rcs1.last_cmd  & 0xFF);  //	直前のコマンドを格納する．
	TlmPacket[TLM_POSITION_MAIN + 147] = (unsigned char)( rcs1.ack  & 0xFF);  //	各種ACK又はエラー番号を格納する．
	TlmPacket[TLM_POSITION_MAIN + 148] = (unsigned char)( rcs1.tt0  & 0xFF);  //	タンク基準温度（上位）
	TlmPacket[TLM_POSITION_MAIN + 149] = (unsigned char)( rcs1.tt0  & 0xFF);  //	タンク基準温度（下位）．TT0_H*16+TT0_L=タンク基準温度
	TlmPacket[TLM_POSITION_MAIN + 150] = (unsigned char)( rcs1.tt1  & 0xFF);  //	タンク相対温度（上位）
	TlmPacket[TLM_POSITION_MAIN + 151] = (unsigned char)( rcs1.tt1  & 0xFF);  //	タンク相対温度（下位）．TT1_H*16+TT1_L=タンク相対温度
	TlmPacket[TLM_POSITION_MAIN + 152] = (unsigned char)( rcs1.tc0  & 0xFF);  //	スラスタ内基準温度（上位）
	TlmPacket[TLM_POSITION_MAIN + 153] = (unsigned char)( rcs1.tc0  & 0xFF);  //	スラスタ内基基準温度（下位）．TC0_H*256+TC0_L=スラスタ内基基準温度
	TlmPacket[TLM_POSITION_MAIN + 154] = (unsigned char)( rcs1.tc1  & 0xFF);  //	スラスタ内基相対温度（上位）
	TlmPacket[TLM_POSITION_MAIN + 155] = (unsigned char)( rcs1.tc1  & 0xFF);  //	スラスタ内基相対温度（下位）．TC1_H*256+TC1_L=スラスタ内基相対温度
	TlmPacket[TLM_POSITION_MAIN + 156] = (unsigned char)( rcs1.pt  & 0xFF);  //	タンク内圧（上位）
	TlmPacket[TLM_POSITION_MAIN + 157] = (unsigned char)( rcs1.pt  & 0xFF);  //	タンク内圧（下位）．PT_H*256+PT_L=タンク内圧
	TlmPacket[TLM_POSITION_MAIN + 158] = (unsigned char)( rcs1.pc  & 0xFF);  //	スラスタ内圧（上位）
	TlmPacket[TLM_POSITION_MAIN + 159] = (unsigned char)( rcs1.pc  & 0xFF);  //	スラスタ内圧（下位）．PC_H*256+PC_L=スラスタ内圧
	TlmPacket[TLM_POSITION_MAIN + 160] = (unsigned char)( rcs1.i_pt  & 0xFF);  //	圧力計PT電流（上位）
	TlmPacket[TLM_POSITION_MAIN + 161] = (unsigned char)( rcs1.i_pt  & 0xFF);  //	圧力計PT電流（下位）．I-PT_H*256+I-PT_L=圧力計PT電流
	TlmPacket[TLM_POSITION_MAIN + 162] = (unsigned char)( rcs1.i_pc  & 0xFF);  //	圧力計PC電流（上位）
	TlmPacket[TLM_POSITION_MAIN + 163] = (unsigned char)( rcs1.i_pc  & 0xFF);  //	圧力計PC電流（下位）．I-PC_H*256+I-PC_L=圧力計PC電流
	p = (unsigned char *)&( rcs1.driver_super.update_time );	//	RCSデータパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 164 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 164 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 164 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 164 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( dc_val_in );	//	AOCSのDC INの状態
	TlmPacket[TLM_POSITION_MAIN + 168 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 168 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( dc_val_out );	//	AOCSのDC OUTの状態
	TlmPacket[TLM_POSITION_MAIN + 170 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 170 + 1] = (unsigned char)(*p);	p++;
	return(  172 );
 }



int TLM_AOBC_44(void){
	unsigned char	*p;
	
	p = (unsigned char *)&( ad590.tempe[0] );	//	AD590_16（AOBC付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 0 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[1] );	//	AD590_17（RW1付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 2 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 2 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[2] );	//	AD590_18（RW1付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 4 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[3] );	//	AD590_19（RW1付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 6 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 6 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[4] );	//	AD590_20（RW1付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 8 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[5] );	//	AD590_21（MTQ_X付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 10 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 10 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[6] );	//	AD590_22（GAS付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 12 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 12 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[7] );	//	AD590_23（STT1付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 14 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 14 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[8] );	//	AD590_24（FOG付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 16 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[9] );	//	AD590_25（GPS-R付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 18 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[10] );	//	AD590_26（RCS付近）の状態
	TlmPacket[TLM_POSITION_MAIN + 20 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 20 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[11] );	//	AD590_27　N/A
	TlmPacket[TLM_POSITION_MAIN + 22 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 22 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[12] );	//	AD590_28　N/A
	TlmPacket[TLM_POSITION_MAIN + 24 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[13] );	//	AD590_29　N/A
	TlmPacket[TLM_POSITION_MAIN + 26 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[14] );	//	AD590_30　N/A
	TlmPacket[TLM_POSITION_MAIN + 28 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( ad590.tempe[15] );	//	AD590_31　N/A
	TlmPacket[TLM_POSITION_MAIN + 30 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 30 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32] = (unsigned char)( AOCS_MTQ  & 0xFF);  //	MTQ設定値
	p = (unsigned char *)&( AOCS_qt[1] );	//	目標クオータニオン2
	TlmPacket[TLM_POSITION_MAIN + 33 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 33 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 33 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 33 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 33 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 33 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 33 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 33 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_qt[2] );	//	目標クオータニオン3
	TlmPacket[TLM_POSITION_MAIN + 41 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 41 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 41 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 41 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 41 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 41 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 41 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 41 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_qt[3] );	//	目標クオータニオン4
	TlmPacket[TLM_POSITION_MAIN + 49 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 49 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 49 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 49 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 49 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 49 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 49 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 49 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wt[0] );	//	目標角速度X
	TlmPacket[TLM_POSITION_MAIN + 57 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 57 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 57 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 57 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 57 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 57 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 57 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 57 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wt[1] );	//	目標角速度Y
	TlmPacket[TLM_POSITION_MAIN + 65 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 65 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 65 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 65 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 65 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 65 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 65 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 65 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wt[2] );	//	目標角速度Z
	TlmPacket[TLM_POSITION_MAIN + 73 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 73 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wd[0] );	//	決定角速度X
	TlmPacket[TLM_POSITION_MAIN + 81 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 81 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wd[1] );	//	決定角速度Y
	TlmPacket[TLM_POSITION_MAIN + 89 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 89 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wd[2] );	//	決定角速度Z
	TlmPacket[TLM_POSITION_MAIN + 97 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 97 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_R[0] );	//	軌道情報 R_x
	TlmPacket[TLM_POSITION_MAIN + 105 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 105 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 105 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 105 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 105 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 105 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 105 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 105 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_R[1] );	//	軌道情報 R_y
	TlmPacket[TLM_POSITION_MAIN + 113 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 113 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 113 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 113 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 113 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 113 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 113 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 113 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_R[2] );	//	軌道情報 R_z
	TlmPacket[TLM_POSITION_MAIN + 121 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 121 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 121 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 121 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 121 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 121 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 121 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 121 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_V[0] );	//	軌道情報 V_x
	TlmPacket[TLM_POSITION_MAIN + 129 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 129 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 129 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 129 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 129 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 129 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 129 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 129 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_V[1] );	//	軌道情報 V_y
	TlmPacket[TLM_POSITION_MAIN + 137 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 137 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 137 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 137 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 137 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 137 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 137 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 137 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_V[2] );	//	軌道情報 V_z
	TlmPacket[TLM_POSITION_MAIN + 145 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 145 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 145 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 145 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 145 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 145 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 145 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 145 + 7] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 153] = (unsigned char)( AOCS_RW_dist  & 0xFF);  //	RW分配則状況
	return(  154 );
 }



int TLM_AOBC_45(void){
	unsigned char	*p;
	
	p = (unsigned char *)&( AOCS_SUN_dir[0] );	//	太陽方向計算値f
	TlmPacket[TLM_POSITION_MAIN + 0 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_SUN_dir[1] );	//	太陽方向計算値q
	TlmPacket[TLM_POSITION_MAIN + 8 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_SUN_dir[2] );	//	太陽方向計算値y
	TlmPacket[TLM_POSITION_MAIN + 16 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_GEOMAG_dir[0] );	//	地磁気ベクトル計算値X
	TlmPacket[TLM_POSITION_MAIN + 24 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 24 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_GEOMAG_dir[1] );	//	地磁気ベクトル計算値Y
	TlmPacket[TLM_POSITION_MAIN + 32 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 32 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_GEOMAG_dir[2] );	//	地磁気ベクトル計算値Z
	TlmPacket[TLM_POSITION_MAIN + 40 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 40 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_gain );	//	RW1電流ゲイン
	TlmPacket[TLM_POSITION_MAIN + 48 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 48 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_integ_gain );	//	RW1電流積分ゲイン
	TlmPacket[TLM_POSITION_MAIN + 50 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 50 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_limit );	//	RW1電流制限値
	TlmPacket[TLM_POSITION_MAIN + 52 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_temperature_gain );	//	RW1温度ゲイン
	TlmPacket[TLM_POSITION_MAIN + 54 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 54 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_temperature_offset );	//	RW1温度オフセット
	TlmPacket[TLM_POSITION_MAIN + 56 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 56 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_system_config );	//	RW1システム設定
	TlmPacket[TLM_POSITION_MAIN + 58 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 58 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_gain );	//	RW1電流ゲイン
	TlmPacket[TLM_POSITION_MAIN + 60 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_integ_gain );	//	RW1電流積分ゲイン
	TlmPacket[TLM_POSITION_MAIN + 62 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 62 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_limit );	//	RW1電流制限値
	TlmPacket[TLM_POSITION_MAIN + 64 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 64 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_temperature_gain );	//	RW1温度ゲイン
	TlmPacket[TLM_POSITION_MAIN + 66 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 66 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_temperature_offset );	//	RW1温度オフセット
	TlmPacket[TLM_POSITION_MAIN + 68 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 68 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_system_config );	//	RW1システム設定
	TlmPacket[TLM_POSITION_MAIN + 70 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 70 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_gain );	//	RW1電流ゲイン
	TlmPacket[TLM_POSITION_MAIN + 72 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 72 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_integ_gain );	//	RW1電流積分ゲイン
	TlmPacket[TLM_POSITION_MAIN + 74 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 74 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_limit );	//	RW1電流制限値
	TlmPacket[TLM_POSITION_MAIN + 76 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_temperature_gain );	//	RW1温度ゲイン
	TlmPacket[TLM_POSITION_MAIN + 78 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 78 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_temperature_offset );	//	RW1温度オフセット
	TlmPacket[TLM_POSITION_MAIN + 80 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 80 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_system_config );	//	RW1システム設定
	TlmPacket[TLM_POSITION_MAIN + 82 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 82 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_gain );	//	RW1電流ゲイン
	TlmPacket[TLM_POSITION_MAIN + 84 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 84 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_integ_gain );	//	RW1電流積分ゲイン
	TlmPacket[TLM_POSITION_MAIN + 86 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 86 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_current_limit );	//	RW1電流制限値
	TlmPacket[TLM_POSITION_MAIN + 88 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 88 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_temperature_gain );	//	RW1温度ゲイン
	TlmPacket[TLM_POSITION_MAIN + 90 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 90 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_temperature_offset );	//	RW1温度オフセット
	TlmPacket[TLM_POSITION_MAIN + 92 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 92 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( rw1_system_config );	//	RW1システム設定
	TlmPacket[TLM_POSITION_MAIN + 94 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 94 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_cont_trq[0] );	//	モード毎の制御量の計算値X
	TlmPacket[TLM_POSITION_MAIN + 96 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 96 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_cont_trq[1] );	//	モード毎の制御量の計算値Y
	TlmPacket[TLM_POSITION_MAIN + 104 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 104 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_cont_trq[2] );	//	モード毎の制御量の計算値Z
	TlmPacket[TLM_POSITION_MAIN + 112 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 112 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_gain_P[0] );	//	AOCS PD制御 Pゲイン等の設定値
	TlmPacket[TLM_POSITION_MAIN + 120 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 120 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_gain_D[0] );	//	AOCS PD制御 Dゲイン等の設定値
	TlmPacket[TLM_POSITION_MAIN + 128 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 128 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1_image_sensor_board );	//	イメージセンサ基板温度
	TlmPacket[TLM_POSITION_MAIN + 136 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 136 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1_fpga );	//	FPGA温度
	TlmPacket[TLM_POSITION_MAIN + 140 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 140 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 140 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 140 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1_get_time );	//	現在の露光時間
	TlmPacket[TLM_POSITION_MAIN + 145 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 145 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1_seu_error_count );	//	SEU エラー自動修正回数
	TlmPacket[TLM_POSITION_MAIN + 148 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 148 + 1] = (unsigned char)(*p);	p++;
	return(  150 );
 }



int TLM_AOBC_201(void){
	unsigned char	*p;
	
	p = (unsigned char *)&( gyro1.del_x );	//	GYRO1 x方向の角速度
	TlmPacket[TLM_POSITION_MAIN + 0 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.del_y );	//	GYRO1 y方向の角速度
	TlmPacket[TLM_POSITION_MAIN + 4 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.del_z );	//	GYRO1 z方向の角速度
	TlmPacket[TLM_POSITION_MAIN + 8 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 8 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.driver_super.update_time );	//	gyro1データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 12 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 12 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 12 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 12 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gyro1.status.byte[0] );	//	GYRO1のステータス出力値
	TlmPacket[TLM_POSITION_MAIN + 16 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 16 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.driver_super.update_time );	//	STT1データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 18 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 18 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_STT1_cap_cmd_snd_time );	//	撮影のコマンドを送った時刻
	TlmPacket[TLM_POSITION_MAIN + 22 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 22 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 22 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 22 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.capture_id );	//	STT1の1撮影ごとにインクリメントされるカウンタ
	TlmPacket[TLM_POSITION_MAIN + 26 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 26 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.attitude[0] );	//	STT1の四元数1
	TlmPacket[TLM_POSITION_MAIN + 28 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 28 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.attitude[1] );	//	STT1の四元数2
	TlmPacket[TLM_POSITION_MAIN + 36 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 36 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 36 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 36 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 36 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 36 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 36 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 36 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.attitude[2] );	//	STT1の四元数3
	TlmPacket[TLM_POSITION_MAIN + 44 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 44 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 44 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 44 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 44 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 44 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 44 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 44 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[0][0]  );	//	STT1の誤差共分散1
	TlmPacket[TLM_POSITION_MAIN + 52 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 52 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[0][1] );	//	STT1の誤差共分散2
	TlmPacket[TLM_POSITION_MAIN + 60 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 60 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[0][2] );	//	STT1の誤差共分散3
	TlmPacket[TLM_POSITION_MAIN + 68 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 68 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 68 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 68 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 68 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 68 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 68 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 68 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[1][1] );	//	STT1の誤差共分散5
	TlmPacket[TLM_POSITION_MAIN + 76 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 76 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[1][2] );	//	STT1の誤差共分散6
	TlmPacket[TLM_POSITION_MAIN + 84 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 84 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 84 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 84 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 84 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 84 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 84 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 84 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( stt1.error_covariance_matrix[2][2] );	//	STT1の誤差共分散9
	TlmPacket[TLM_POSITION_MAIN + 92 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 92 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 92 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 92 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 92 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 92 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 92 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 92 + 7] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 100] = (unsigned char)( stt1.master_detected_star_count  & 0xFF);  //	マスタの検出恒星数
	p = (unsigned char *)&( stt1.master_estimation_status );	//	マスタの姿勢推定ステータス
	TlmPacket[TLM_POSITION_MAIN + 101 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 101 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 101 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 101 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 105] = (unsigned char)( gps1.status1.byte  & 0xFF);  //	GPS1のｽﾃｰﾀｽ1
	p = (unsigned char *)&( gps1.latitude );	//	GPS1の緯度
	TlmPacket[TLM_POSITION_MAIN + 106 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 106 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 106 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 106 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.longitude );	//	GPS1の経度
	TlmPacket[TLM_POSITION_MAIN + 110 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 110 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 110 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 110 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.altitude );	//	GPS1の高度
	TlmPacket[TLM_POSITION_MAIN + 114 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 114 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 114 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 114 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.vector_x );	//	GPS1X方向の出力値
	TlmPacket[TLM_POSITION_MAIN + 118 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 118 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 118 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 118 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 118 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 118 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 118 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 118 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.vector_y );	//	GPS1Y方向の出力値
	TlmPacket[TLM_POSITION_MAIN + 126 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 126 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 126 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 126 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 126 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 126 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 126 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 126 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.vector_z );	//	GPS1Z方向の出力値
	TlmPacket[TLM_POSITION_MAIN + 134 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 134 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 134 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 134 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 134 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 134 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 134 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 134 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( gps1.pdop );	//	GPS1のPDOP
	TlmPacket[TLM_POSITION_MAIN + 142 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 142 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 144] = (unsigned char)( gps1.utc.year  & 0xFF);  //	GPS1のUTCの年（西暦の下二桁）
	TlmPacket[TLM_POSITION_MAIN + 145] = (unsigned char)( gps1.utc.month  & 0xFF);  //	GPS1のUTCの月
	TlmPacket[TLM_POSITION_MAIN + 146] = (unsigned char)( gps1.utc.day  & 0xFF);  //	GPS1のUTCの日
	TlmPacket[TLM_POSITION_MAIN + 147] = (unsigned char)( gps1.utc.hour  & 0xFF);  //	GPS1のUTCの時
	TlmPacket[TLM_POSITION_MAIN + 148] = (unsigned char)( gps1.utc.min  & 0xFF);  //	GPS1のUTCの分
	TlmPacket[TLM_POSITION_MAIN + 149] = (unsigned char)( gps1.utc.sec  & 0xFF);  //	GPS1のUTCの秒
	TlmPacket[TLM_POSITION_MAIN + 150] = (unsigned char)( gps1.alive_sat  & 0xFF);  //	GPS1の正常な衛星数
	TlmPacket[TLM_POSITION_MAIN + 151] = (unsigned char)( gps1.visible_sat  & 0xFF);  //	GPS1の可視衛星数
	TlmPacket[TLM_POSITION_MAIN + 152] = (unsigned char)( gps1.delay_time  & 0xFF);  //	GPS1の測位遅延時間
	TlmPacket[TLM_POSITION_MAIN + 153] = (unsigned char)( gps1.pps  & 0xFF);  //	GPS1のPPS補正
	p = (unsigned char *)&( gps1.driver_super.update_time );	//	GPS1データパケット受信時刻
	TlmPacket[TLM_POSITION_MAIN + 154 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 154 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 154 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 154 + 3] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_R_WGS84[0] );	//	起動情報 R_x (WGS84)
	TlmPacket[TLM_POSITION_MAIN + 158 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 158 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 158 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 158 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 158 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 158 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 158 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 158 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_R_WGS84[1] );	//	起動情報 R_y (WGS84)
	TlmPacket[TLM_POSITION_MAIN + 166 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 166 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 166 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 166 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 166 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 166 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 166 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 166 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_R_WGS84[2] );	//	起動情報 R_z (WGS84)
	TlmPacket[TLM_POSITION_MAIN + 174 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 174 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 174 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 174 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 174 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 174 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 174 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 174 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_det_time );	//	生成時刻
	TlmPacket[TLM_POSITION_MAIN + 182 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 182 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 182 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 182 + 3] = (unsigned char)(*p);	p++;
	return(  186 );
 }



int TLM_AOBC_202(void){
	unsigned char	*p;
	
	p = (unsigned char *)&( AOCS_det_time );	//	生成時刻
	TlmPacket[TLM_POSITION_MAIN + 0 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 0 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 4] = (unsigned char)( AOCS_mode  & 0xFF);  //	姿勢制御モードを表す。
	p = (unsigned char *)&( AOCS_qd[1] );	//	決定姿勢の四元数1(ノーマライズされている＆０成分は常に正）
	TlmPacket[TLM_POSITION_MAIN + 5 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 5 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 5 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 5 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 5 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 5 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 5 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 5 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_qd[2] );	//	決定姿勢の四元数2
	TlmPacket[TLM_POSITION_MAIN + 13 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 13 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 13 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 13 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 13 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 13 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 13 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 13 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_qd[3] );	//	決定姿勢の四元数3
	TlmPacket[TLM_POSITION_MAIN + 21 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 21 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 21 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 21 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 21 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 21 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 21 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 21 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_failure_flag );	//	姿勢制御系機器の故障フラグ
	TlmPacket[TLM_POSITION_MAIN + 29 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 29 + 1] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_qt[1] );	//	目標クオータニオン2
	TlmPacket[TLM_POSITION_MAIN + 31 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 31 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 31 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 31 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 31 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 31 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 31 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 31 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_qt[2] );	//	目標クオータニオン3
	TlmPacket[TLM_POSITION_MAIN + 39 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 39 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 39 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 39 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 39 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 39 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 39 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 39 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_qt[3] );	//	目標クオータニオン4
	TlmPacket[TLM_POSITION_MAIN + 47 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 47 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 47 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 47 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 47 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 47 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 47 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 47 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wt[0] );	//	目標角速度X
	TlmPacket[TLM_POSITION_MAIN + 55 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 55 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wt[1] );	//	目標角速度Y
	TlmPacket[TLM_POSITION_MAIN + 63 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 63 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 63 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 63 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 63 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 63 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 63 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 63 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wt[2] );	//	目標角速度Z
	TlmPacket[TLM_POSITION_MAIN + 71 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 71 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 71 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 71 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 71 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 71 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 71 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 71 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wd[0] );	//	決定角速度X
	TlmPacket[TLM_POSITION_MAIN + 79 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 79 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wd[1] );	//	決定角速度Y
	TlmPacket[TLM_POSITION_MAIN + 87 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 87 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 87 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 87 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 87 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 87 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 87 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 87 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_wd[2] );	//	決定角速度Z
	TlmPacket[TLM_POSITION_MAIN + 95 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 95 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 95 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 95 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 95 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 95 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 95 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 95 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_R[0] );	//	軌道情報 R_x
	TlmPacket[TLM_POSITION_MAIN + 103 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 103 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 103 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 103 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 103 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 103 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 103 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 103 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_R[1] );	//	軌道情報 R_y
	TlmPacket[TLM_POSITION_MAIN + 111 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 111 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 111 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 111 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 111 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 111 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 111 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 111 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_R[2] );	//	軌道情報 R_z
	TlmPacket[TLM_POSITION_MAIN + 119 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 119 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 119 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 119 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 119 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 119 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 119 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 119 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_V[0] );	//	軌道情報 V_x
	TlmPacket[TLM_POSITION_MAIN + 127 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 127 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 127 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 127 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 127 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 127 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 127 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 127 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_V[1] );	//	軌道情報 V_y
	TlmPacket[TLM_POSITION_MAIN + 135 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 135 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 135 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 135 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 135 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 135 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 135 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 135 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_orb_V[2] );	//	軌道情報 V_z
	TlmPacket[TLM_POSITION_MAIN + 143 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 143 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 143 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 143 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 143 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 143 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 143 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 143 + 7] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 151] = (unsigned char)( AOCS_RW_dist  & 0xFF);  //	RW分配則状況
	p = (unsigned char *)&( AOCS_cont_trq[0] );	//	モード毎の制御量の計算値X
	TlmPacket[TLM_POSITION_MAIN + 152 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 152 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 152 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 152 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 152 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 152 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 152 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 152 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_cont_trq[1] );	//	モード毎の制御量の計算値Y
	TlmPacket[TLM_POSITION_MAIN + 160 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 160 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 160 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 160 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 160 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 160 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 160 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 160 + 7] = (unsigned char)(*p);	p++;
	p = (unsigned char *)&( AOCS_cont_trq[2] );	//	モード毎の制御量の計算値Z
	TlmPacket[TLM_POSITION_MAIN + 168 + 0] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 168 + 1] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 168 + 2] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 168 + 3] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 168 + 4] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 168 + 5] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 168 + 6] = (unsigned char)(*p);	p++;
	TlmPacket[TLM_POSITION_MAIN + 168 + 7] = (unsigned char)(*p);	p++;
	return(  176 );
 }

