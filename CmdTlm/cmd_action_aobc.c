#include <itron.h>
#include "utility.h"
#include "kernel_id.h"

#include "../Equipment_Instance.h"

#include "../interval/aocs-interval.h"
#include "../AOCS_Process/AOCS_Process.h"
#include "cmd_analyze_aobc.h"

#include "cmd_action_aobc.h"

unsigned short rw1_current_gain, rw2_current_gain, rw3_current_gain, rw4_current_gain;
unsigned short rw1_current_integ_gain, rw2_current_integ_gain, rw3_current_integ_gain, rw4_current_integ_gain;
unsigned short rw1_current_limit, rw2_current_limit, rw3_current_limit, rw4_current_limit;
unsigned short rw1_temperature_gain, rw2_temperature_gain, rw3_temperature_gain, rw4_temperature_gain;
unsigned short rw1_temperature_offset, rw2_temperature_offset, rw3_temperature_offset, rw4_temperature_offset;
unsigned short rw1_system_config, rw2_system_config, rw3_system_config, rw4_system_config;
float stt1_image_sensor_board;
float stt1_fpga;
float stt1_image_sensor;
unsigned char stt1_power_state;
unsigned short stt1_get_time;
unsigned short stt1_set_time;
unsigned char stt1_star_count;
GET_DETECTED_STAR_INFO_COMMAND_STRUCT stt1_info_data[64];
double stt1_quaternion1;
double stt1_quaternion2;
double stt1_quaternion3;
double stt1_quaternion4;
GET_ESTIMATION_STATUS_UNION stt1_st_data;
double stt1_ecm00;
double stt1_ecm01;
double stt1_ecm02;
double stt1_ecm11;
double stt1_ecm12;
double stt1_ecm22;
unsigned char stt1_output_mode;
unsigned short stt1_seu_error_count;
unsigned char stt1_error;
unsigned char stt1_interval;


int		CMD_MTQ(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	
	Printf("CMD_MTQ %02X %02X\n", param1, param2);

	if(param1 == 0x01){				// MTQ 1
		if(param2 == 0x00){			//	OFF
			Printf("MTQ1 OFF\n");
			CmdSend_PowerOff(MTQ_X_OFF);
		}else if(param2 == 0x01){		//	CW
			Printf("MTQ1 CW ON\n");
			CmdSend_PowerOn(MTQ_X_PLUS);
		}else if(param2 == 0x02){		//	CCW
			Printf("MTQ1 CCW ON\n");
			CmdSend_PowerOn(MTQ_X_MINUS);
		}else{
			Printf("MTQ1 ERROR\n");
			return(-1);
		}
	}else if(param1 == 0x02){			// MTQ 2
		if(param2 == 0x00){			//	OFF
			Printf("MTQ2 OFF\n");
			CmdSend_PowerOff(MTQ_Y_OFF);
		}else if(param2 == 0x01){		//	CW
			Printf("MTQ2 CW ON\n");
			CmdSend_PowerOn(MTQ_Y_PLUS);
		}else if(param2 == 0x02){		//	CCW
			Printf("MTQ2 CCW ON\n");
			CmdSend_PowerOn(MTQ_Y_MINUS);
		}else{
			Printf("MTQ2 ERROR\n");
			return(-1);
		}
	}else if(param1 == 0x03){			// MTQ 3
		if(param2 == 0x00){			//	OFF
			Printf("MTQ3 OFF\n");
			CmdSend_PowerOff(MTQ_Z_OFF);
		}else if(param2 == 0x01){		//	CW
			Printf("MTQ3 CW ON\n");
			CmdSend_PowerOn(MTQ_Z_PLUS);
		}else if(param2 == 0x02){		//	CCW
			Printf("MTQ3 CCW ON\n");
			CmdSend_PowerOn(MTQ_Z_MINUS);
		}else{
			Printf("MTQ3 ERROR\n");
			return(-1);
		}
	}else{
		Printf("No such a MTQ\n");
		return(-2);
	}
		
	return CMD_ERROR_NONE;
}

int		CMD_RW(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3 = packet->data[CMD_POSITION_PARAM+2];
	unsigned char param4 = packet->data[CMD_POSITION_PARAM+3];
	unsigned char param5 = packet->data[CMD_POSITION_PARAM+4];
	unsigned char param6 = packet->data[CMD_POSITION_PARAM+5];

	unsigned short	local_param1;
	unsigned short	local_param2;

	local_param1 = param3;
	local_param1 <<= 8;
	local_param1 &= 0xff00;
	local_param1 |= param4;

	local_param2 = param5;
	local_param2 <<= 8;
	local_param2 &= 0xff00;
	local_param2 |= param6;

	Printf("CMD_RW %02X %02X %02X %02X %02X %02X\n", param1, param2, param3, param4, param5, param6);
	Printf("local_param1 %04X\n", local_param1);
	Printf("local_param2 %04X\n", local_param2);
	if(param1 == 0x01){		// RW1
		Printf("RW1\n");
		RW_tx_comm(&rw1, param2, local_param1, local_param2);
	}else if(param1 == 0x02){	// RW2
		Printf("RW2\n");
		RW_tx_comm(&rw2, param2, local_param1, local_param2);
	}else if(param1 == 0x03){	// RW3
		Printf("RW3\n");
		RW_tx_comm(&rw3, param2, local_param1, local_param2);
	}else if(param1 == 0x04){	// RW4
		Printf("RW4\n");
		RW_tx_comm(&rw4, param2, local_param1, local_param2);
	}else{
		Printf("No such a RW\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_RW_PARAMETER_REQUEST1(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_RW_PARAMETER_REQUEST1 %02X\n", param1);
	if(param1 == 0x01){		// RW1
		Printf("RW1\n");
		RW_Parameter_Request1(&rw1, &rw1_current_gain, &rw1_current_integ_gain, &rw1_current_limit);
		Printf("current_gain %04X\n", rw1_current_gain);
		Printf("current_integ_gain %04X\n", rw1_current_integ_gain);
		Printf("current_limit %04\n", rw1_current_limit);
	}else if(param1 == 0x02){	// RW2
		Printf("RW2\n");
		RW_Parameter_Request1(&rw2, &rw2_current_gain, &rw2_current_integ_gain, &rw2_current_limit);
		Printf("current_gain %04X\n", rw2_current_gain);
		Printf("current_integ_gain %04X\n", rw2_current_integ_gain);
		Printf("current_limit %04\n", rw2_current_limit);
	}else if(param1 == 0x03){	// RW3
		Printf("RW3\n");
		RW_Parameter_Request1(&rw3, &rw3_current_gain, &rw3_current_integ_gain, &rw3_current_limit);
		Printf("current_gain %04X\n", rw3_current_gain);
		Printf("current_integ_gain %04X\n", rw3_current_integ_gain);
		Printf("current_limit %04\n", rw3_current_limit);
	}else if(param1 == 0x04){	// RW4
		Printf("RW4\n");
		RW_Parameter_Request1(&rw4, &rw4_current_gain, &rw4_current_integ_gain, &rw4_current_limit);
		Printf("current_gain %04X\n", rw4_current_gain);
		Printf("current_integ_gain %04X\n", rw4_current_integ_gain);
		Printf("current_limit %04\n", rw4_current_limit);
	}else{
		Printf("No such a RW\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_RW_PARAMETER_REQUEST2(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_RW_PARAMETER_REQUEST2 %02X\n", param1);
	if(param1 == 0x01){		// RW1
		Printf("RW1\n");
		RW_Parameter_Request2(&rw1, &rw1_temperature_gain, &rw1_temperature_offset, &rw1_system_config);
		Printf("temperature_gain %04X\n", rw1_temperature_gain);
		Printf("temperature_offset %04X\n", rw1_temperature_offset);
		Printf("system_config %04X\n", rw1_system_config);
	}else if(param1 == 0x02){	// RW2
		Printf("RW2\n");
		RW_Parameter_Request2(&rw2, &rw2_temperature_gain, &rw2_temperature_offset, &rw2_system_config);
		Printf("temperature_gain %04X\n", rw2_temperature_gain);
		Printf("temperature_offset %04X\n", rw2_temperature_offset);
		Printf("system_config %04X\n", rw2_system_config);
	}else if(param1 == 0x03){	// RW3
		Printf("RW3\n");
		RW_Parameter_Request2(&rw3, &rw3_temperature_gain, &rw3_temperature_offset, &rw3_system_config);
		Printf("temperature_gain %04X\n", rw3_temperature_gain);
		Printf("temperature_offset %04X\n", rw3_temperature_offset);
		Printf("system_config %04X\n", rw3_system_config);
	}else if(param1 == 0x04){	// RW4
		Printf("RW4\n");
		RW_Parameter_Request2(&rw4, &rw4_temperature_gain, &rw4_temperature_offset, &rw4_system_config);
		Printf("temperature_gain %04X\n", rw4_temperature_gain);
		Printf("temperature_offset %04X\n", rw4_temperature_offset);
		Printf("system_config %04X\n", rw4_system_config);
	}else{
		Printf("No such a RW\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_RW_PARAMETER_CONFIG1(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3 = packet->data[CMD_POSITION_PARAM+2];
	unsigned char param4 = packet->data[CMD_POSITION_PARAM+3];
	unsigned char param5 = packet->data[CMD_POSITION_PARAM+4];
	unsigned char param6 = packet->data[CMD_POSITION_PARAM+5];
	unsigned char param7 = packet->data[CMD_POSITION_PARAM+6];

	unsigned short	local_param1;
	unsigned short	local_param2;
	unsigned short	local_param3;

	local_param1 = param2;
	local_param1 <<= 8;
	local_param1 &= 0xff00;
	local_param1 |= param3;
	
	local_param2 = param4;
	local_param2 <<= 8;
	local_param2 &= 0xff00;
	local_param2 |= param5;

	local_param3 = param6;
	local_param3 <<= 8;
	local_param3 &= 0xff00;
	local_param3 |= param7;

	Printf("CMD_RW_PARAMETER_CONFIG1 %02X %02X %02X %02X %02X %02X %02X\n", param1, param2, param3, param4, param5, param6, param7);
	Printf("local_param1 %04X\n", local_param1);
	Printf("local_param2 %04X\n", local_param2);
	Printf("local_param3 %04X\n", local_param3);
	if(param1 == 0x01){		// RW1
		Printf("RW1\n");
		RW_Parameter_Config1(&rw1, local_param1, local_param2, local_param3);
	}else if(param1 == 0x02){	// RW2
		Printf("RW2\n");
		RW_Parameter_Config1(&rw2, local_param1, local_param2, local_param3);
	}else if(param1 == 0x03){	// RW3
		Printf("RW3\n");
		RW_Parameter_Config1(&rw3, local_param1, local_param2, local_param3);
	}else if(param1 == 0x04){	// RW4
		Printf("RW4\n");
		RW_Parameter_Config1(&rw4, local_param1, local_param2, local_param3);
	}else{
		Printf("No such a RW\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_RW_PARAMETER_CONFIG2(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3 = packet->data[CMD_POSITION_PARAM+2];
	unsigned char param4 = packet->data[CMD_POSITION_PARAM+3];
	unsigned char param5 = packet->data[CMD_POSITION_PARAM+4];
	unsigned char param6 = packet->data[CMD_POSITION_PARAM+5];
	unsigned char param7 = packet->data[CMD_POSITION_PARAM+6];

	unsigned short	local_param1;
	unsigned short	local_param2;
	unsigned short	local_param3;

	local_param1 = param2;
	local_param1 <<= 8;
	local_param1 &= 0xff00;
	local_param1 |= param3;
	
	local_param2 = param4;
	local_param2 <<= 8;
	local_param2 &= 0xff00;
	local_param2 |= param5;

	local_param3 = param6;
	local_param3 <<= 8;
	local_param3 &= 0xff00;
	local_param3 |= param7;

	Printf("CMD_RW_PARAMETER_CONFIG2 %02X %02X %02X %02X %02X %02X %02X\n", param1, param2, param3, param4, param5, param6, param7);
	Printf("local_param1 %04X\n", local_param1);
	Printf("local_param2 %04X\n", local_param2);
	Printf("local_param3 %04X\n", local_param3);
	if(param1 == 0x01){		// RW1
		Printf("RW1\n");
		RW_Parameter_Config2(&rw1, local_param1, local_param2, local_param3);
	}else if(param1 == 0x02){	// RW2
		Printf("RW2\n");
		RW_Parameter_Config2(&rw2, local_param1, local_param2, local_param3);
	}else if(param1 == 0x03){	// RW3
		Printf("RW3\n");
		RW_Parameter_Config2(&rw3, local_param1, local_param2, local_param3);
	}else if(param1 == 0x04){	// RW4
		Printf("RW4\n");
		RW_Parameter_Config2(&rw4, local_param1, local_param2, local_param3);
	}else{
		Printf("No such a RW\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_NSAS_GAIN(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3 = packet->data[CMD_POSITION_PARAM+2];

	Printf("CMD_NSAS_GAIN %02X %02X %02X\n", param1, param2, param3);
	if(param1 == 0x01){		// NSAS1
		Printf("NSAS1\n");
		NSAS_gain(&nsas1, param2, param3);
	}else if(param1 == 0x02){	// NSAS2
		Printf("NSAS2\n");
		NSAS_gain(&nsas2, param2, param3);
	}else if(param1 == 0x03){	// NSAS3
		Printf("NSAS3\n");
		NSAS_gain(&nsas3, param2, param3);
	}else{
		Printf("No such a NSAS\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_RCS_INITIALIZE_COMMAND(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_RCS_INITIALIZE_COMMAND %02X\n", param1);
	if(param1 == 0x01){	// RCS1
		Printf("RCS1\n");
		RCS_initialize_command(&rcs1);
	}else{
		Printf("No such a RCS\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_RCS_INJECTION_PREPARATION(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	
	Printf("CMD_RCS_INJECTION_PREPARATION %02X %02X\n", param1, param2);
	if(param1 == 0x01){	// RCS1
		Printf("RCS1\n");
		RCS_injection_preparation(&rcs1, param2);
	}else{
		Printf("No such a RCS\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_RCS_INJECTION_START(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	
	Printf("CMD_RCS_INJECTION_START %02X %02X\n", param1, param2);
	if(param1 == 0x01){	// RCS1
		Printf("RCS1\n");
		RCS_injection_start(&rcs1, param2);
	}else{
		Printf("No such a RCS\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_RCS_INJECTION_STOP(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_RCS_INJECTION_STOP %02X\n", param1);
	if(param1 == 0x01){	// RCS1
		Printf("RCS1\n");
		RCS_injection_stop(&rcs1);
	}else{
		Printf("No such a RCS\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_ENABLE_CONTROL(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];

	Printf("CMD_STT_ENABLE_CONTROL %02X %02X\n", param1, param2);
	if(param1 == 0x01){ // STT1
		Printf("STT1\n");
		if(param2 == 0x00){
			Printf("DISABLE\n");
			STT_Up_Enable_Power_Down(&stt1);
		}
		if(param2 == 0x01){
			Printf("ENABLE\n");
			STT_Up_Enable_Idle(&stt1);
		}
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}


int		CMD_STT_AUTO_MODE(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_STT_AUTO_MODE %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_auto_mode(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_STOP(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_STT_STOP %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_stop(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_TEMPERATURE(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_GET_TEMPERATURE %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_Temperature(&stt1, &stt1_image_sensor_board, &stt1_fpga, &stt1_image_sensor);
		Printf("image_sensor_board %08X\n", stt1_image_sensor_board);
		Printf("fpga %08X\n", stt1_fpga);
		Printf("image_sensor %08X\n", stt1_image_sensor);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_CHANGE_POWER_STATE_CAPTURE(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_STT_CHANGE_POWER_STATE_CAPTURE %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Change_Power_State_Capture(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_CHANGE_POWER_STATE_IDLE(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_STT_CHANGE_POWER_STATE_IDLE %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Change_Power_State_Idle(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_POWER_STATE(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_GET_POWER_STATE %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_Power_State(&stt1, &stt1_power_state);
		Printf("stt1_power_state: %02X\n", stt1_power_state);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_EXPOSURE_TIME(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_GET_EXPOSURE_TIME %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_Exposure_Time(&stt1, &stt1_get_time);
		Printf("get_time %04X\n", stt1_get_time);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_SET_EXPOSURE_TIME(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3 = packet->data[CMD_POSITION_PARAM+2];
	
	*(((unsigned char*)&stt1_set_time) + 0) = param2;
	*(((unsigned char*)&stt1_set_time) + 1) = param3;

	Printf("CMD_STT_SET_EXPOSURE_TIME %02X %02X %02X\n", param1, param2, param3);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Set_Exposure_Time(&stt1, &stt1_get_time, stt1_set_time);
		Printf("stt1_get_time: %04X\n");
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_SYSTEM_RESET(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_STT_SYSTEM_RESET %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_System_Reset(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_CAPTURE_ONLY(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_STT_CAPTURE_ONLY %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Capture_Only(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_POSTPROC_ONLY(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_STT_POSTPROC_ONLY %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_PostProc_Only(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_CAPTURE_AND_POSTPROC(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_STT_CAPTURE_AND_POSTPROC %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Capture_And_PostProc(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_DETECTED_STAR_COUNT(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	
	Printf("CMD_STT_GET_DETECTED_STAR_COUNT %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_Detected_Star_Count(&stt1, &stt1_star_count);
		Printf("star_count %02X\n", stt1_star_count);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_DETECTED_STAR_INFO(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3 = packet->data[CMD_POSITION_PARAM+2];
	unsigned char param4 = packet->data[CMD_POSITION_PARAM+3];
	unsigned short read_index;
	unsigned char count;
	unsigned int size = sizeof(stt1_info_data);
	
	*(((unsigned char*)&read_index) + 0) = param2;
	*(((unsigned char*)&read_index) + 1) = param3;
	count = param4;
	
	Printf("CMD_STT_GET_DETECTED_STAR_INFO %02X %02X %02X %02X\n", param1, param2, param3, param4);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_Detected_Star_Info(&stt1, read_index, count, &(stt1_info_data[0]), size);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_SET_APPROXIMATE_ATTITUDE(const HUPacket* packet)
{
	unsigned char param1  = packet->data[CMD_POSITION_PARAM];
	unsigned char param2  = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3  = packet->data[CMD_POSITION_PARAM+2];
	unsigned char param4  = packet->data[CMD_POSITION_PARAM+3];
	unsigned char param5  = packet->data[CMD_POSITION_PARAM+4];
	unsigned char param6  = packet->data[CMD_POSITION_PARAM+5];
	unsigned char param7  = packet->data[CMD_POSITION_PARAM+6];
	unsigned char param8  = packet->data[CMD_POSITION_PARAM+7];
	unsigned char param9  = packet->data[CMD_POSITION_PARAM+8];
	unsigned char param10 = packet->data[CMD_POSITION_PARAM+9];
	unsigned char param11 = packet->data[CMD_POSITION_PARAM+10];
	unsigned char param12 = packet->data[CMD_POSITION_PARAM+11];
	unsigned char param13 = packet->data[CMD_POSITION_PARAM+12];
	unsigned char param14 = packet->data[CMD_POSITION_PARAM+13];
	unsigned char param15 = packet->data[CMD_POSITION_PARAM+14];
	unsigned char param16 = packet->data[CMD_POSITION_PARAM+15];
	unsigned char param17 = packet->data[CMD_POSITION_PARAM+16];
	unsigned char param18 = packet->data[CMD_POSITION_PARAM+17];
	unsigned char param19 = packet->data[CMD_POSITION_PARAM+18];
	unsigned char param20 = packet->data[CMD_POSITION_PARAM+19];
	unsigned char param21 = packet->data[CMD_POSITION_PARAM+20];
	unsigned char param22 = packet->data[CMD_POSITION_PARAM+21];
	unsigned char param23 = packet->data[CMD_POSITION_PARAM+22];
	unsigned char param24 = packet->data[CMD_POSITION_PARAM+23];
	unsigned char param25 = packet->data[CMD_POSITION_PARAM+24];
	unsigned char param26 = packet->data[CMD_POSITION_PARAM+25];
	unsigned char param27 = packet->data[CMD_POSITION_PARAM+26];
	unsigned char param28 = packet->data[CMD_POSITION_PARAM+27];
	unsigned char param29 = packet->data[CMD_POSITION_PARAM+28];
	unsigned char param30 = packet->data[CMD_POSITION_PARAM+29];
	unsigned char param31 = packet->data[CMD_POSITION_PARAM+30];
	unsigned char param32 = packet->data[CMD_POSITION_PARAM+31];
	unsigned char param33 = packet->data[CMD_POSITION_PARAM+32];
	
	*(((unsigned char*)&stt1_quaternion1) + 0) = param2;
	*(((unsigned char*)&stt1_quaternion1) + 1) = param3;
	*(((unsigned char*)&stt1_quaternion1) + 2) = param4;
	*(((unsigned char*)&stt1_quaternion1) + 3) = param5;
	*(((unsigned char*)&stt1_quaternion1) + 4) = param6;
	*(((unsigned char*)&stt1_quaternion1) + 5) = param7;
	*(((unsigned char*)&stt1_quaternion1) + 6) = param8;
	*(((unsigned char*)&stt1_quaternion1) + 7) = param9;
		
	*(((unsigned char*)&stt1_quaternion2) + 0) = param10;
	*(((unsigned char*)&stt1_quaternion2) + 1) = param11;
	*(((unsigned char*)&stt1_quaternion2) + 2) = param12;
	*(((unsigned char*)&stt1_quaternion2) + 3) = param13;
	*(((unsigned char*)&stt1_quaternion2) + 4) = param14;
	*(((unsigned char*)&stt1_quaternion2) + 5) = param15;
	*(((unsigned char*)&stt1_quaternion2) + 6) = param16;
	*(((unsigned char*)&stt1_quaternion2) + 7) = param17;
		
	*(((unsigned char*)&stt1_quaternion3) + 0) = param18;
	*(((unsigned char*)&stt1_quaternion3) + 1) = param19;
	*(((unsigned char*)&stt1_quaternion3) + 2) = param20;
	*(((unsigned char*)&stt1_quaternion3) + 3) = param21;
	*(((unsigned char*)&stt1_quaternion3) + 4) = param22;
	*(((unsigned char*)&stt1_quaternion3) + 5) = param23;
	*(((unsigned char*)&stt1_quaternion3) + 6) = param24;
	*(((unsigned char*)&stt1_quaternion3) + 7) = param25;
		
	*(((unsigned char*)&stt1_quaternion4) + 0) = param26;
	*(((unsigned char*)&stt1_quaternion4) + 1) = param27;
	*(((unsigned char*)&stt1_quaternion4) + 2) = param28;
	*(((unsigned char*)&stt1_quaternion4) + 3) = param29;
	*(((unsigned char*)&stt1_quaternion4) + 4) = param30;
	*(((unsigned char*)&stt1_quaternion4) + 5) = param31;
	*(((unsigned char*)&stt1_quaternion4) + 6) = param32;
	*(((unsigned char*)&stt1_quaternion4) + 7) = param33;
	
	Printf("CMD_STT_SET_APPROXIMATE_ATTITUDE %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", param1, param2, param3, param4, param5, param6, param7, param8, param9, param10, param11, param12, param13, param14, param15, param16, param17, param18, param19, param20, param21, param22, param23, param24, param25, param26, param27, param28, param29, param30, param31, param32, param33);
	Printf("quaternion1 %16X\n", stt1_quaternion1);
	Printf("quaternion2 %16X\n", stt1_quaternion2);
	Printf("quaternion3 %16X\n", stt1_quaternion3);
	Printf("quaternion4 %16X\n", stt1_quaternion4);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Set_Approximate_Attitude(&stt1, stt1_quaternion1, stt1_quaternion2, stt1_quaternion3, stt1_quaternion4);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_ESTIMATION_STATUS(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_GET_ESTIMATION_STATUS %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("sTT1\n");
		STT_Get_Estimation_Status(&stt1, &stt1_st_data);
		Printf("st_data.byte[0] %02X\n", stt1_st_data.byte[0]);
		Printf("st_data.byte[1] %02X\n", stt1_st_data.byte[1]);
		Printf("st_data.byte[2] %02X\n", stt1_st_data.byte[2]);
		Printf("st_data.byte[3] %02X\n", stt1_st_data.byte[3]);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_ATTITUDE(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_GET_ATTITUDE %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_Attitude(&stt1, &stt1_quaternion1, &stt1_quaternion2, &stt1_quaternion3, &stt1_quaternion4);
		Printf("quaternion1 %16X\n", stt1_quaternion1);
		Printf("quaternion2 %16X\n", stt1_quaternion2);
		Printf("quaternion3 %16X\n", stt1_quaternion3);
		Printf("quaternion4 %16X\n", stt1_quaternion4);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}
	
	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_COVARIANCE_MATRIX(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_GET_COVARIANCE_MATRIX %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_Error_Covariance_Matrix(&stt1, &stt1_ecm00, &stt1_ecm01, &stt1_ecm02, &stt1_ecm11, &stt1_ecm12, &stt1_ecm22);
		Printf("ecm00 %16X\n", stt1_ecm00);
		Printf("ecm01 %16X\n", stt1_ecm01);
		Printf("ecm02 %16X\n", stt1_ecm02);
		Printf("ecm11 %16X\n", stt1_ecm11);
		Printf("ecm12 %16X\n", stt1_ecm12);
		Printf("ecm22 %16X\n", stt1_ecm22);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_CHANGE_OUTPUT_MODE(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_CHANGE_OUTPUT_MODE %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Change_Output_Mode(&stt1, &stt1_output_mode);
		Printf("stt1_output_mode: %02X\n", stt1_output_mode);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_SEU_ERROR_CORRECTION_COUNT(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_GET_SEU_ERROR_CORRECTION_COUNT %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_SEU_Error_Correction_Count(&stt1, &stt1_seu_error_count);
		Printf("seu_error_count %04X\n", stt1_seu_error_count);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}
	Printf("seu_error_count %04X\n", stt1_seu_error_count);

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_ERROR(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_GET_ERROR %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_Error(&stt1, &stt1_error);
		Printf("error %02X\n", stt1_error);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_CLEAR_ERROR(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_CLEAR_ERROR %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Clear_Error(&stt1, &stt1_error);
		Printf("error %02X\n", stt1_error);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_GET_OUTPUT_INTERVAL(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_GET_OUTPUT_INTERVAL %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Get_Output_Interval(&stt1, &stt1_interval);
		Printf("interval %02X\n", stt1_interval);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_SET_OUTPUT_INTERVAL(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	unsigned char set_interval = param2;

	Printf("CMD_STT_SET_OUTPUT_INTERVAL %02X %02X\n", param1, param2);
	Printf("set_interval %02X\n", set_interval);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Set_Output_Interval(&stt1, set_interval, &stt1_interval);
		Printf("interval %02X\n", stt1_interval);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_START_OUTPUT(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_START_OUTPUT %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Start_Output(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_STT_STOP_OUTPUT(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	Printf("CMD_STT_STOP_OUTPUT %02X\n", param1);
	if(param1 == 0x01){	// STT1
		Printf("STT1\n");
		STT_Stop_Output(&stt1);
	}else{
		Printf("No such a STT\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_MIPS_HVPS(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	unsigned char param2 = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3 = packet->data[CMD_POSITION_PARAM+2];
	unsigned char param4 = packet->data[CMD_POSITION_PARAM+3];
		
	Printf("CMD_MIPS_HVPS %02X %02X %02X %02X\n", param1, param2, param3, param4);
	if(param1 == 0x01){	// MIPS1
		Printf("MIPS1\n");
		////MIPSドライバ更新に伴い、いったんコメントアウト 2013/11/14 小林
		////MIPS_command1(&mips1, param2, param3, param4);
	}else{
		Printf("No such a MIPS\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_MIPS_TV_TIMER(const HUPacket* packet)
{
	unsigned char param1  = packet->data[CMD_POSITION_PARAM];
	unsigned char param2  = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3  = packet->data[CMD_POSITION_PARAM+2];
	unsigned char param4  = packet->data[CMD_POSITION_PARAM+3];
	unsigned char param5  = packet->data[CMD_POSITION_PARAM+4];
	unsigned char param6  = packet->data[CMD_POSITION_PARAM+5];
	unsigned char param7  = packet->data[CMD_POSITION_PARAM+6];
	unsigned char param8  = packet->data[CMD_POSITION_PARAM+7];
	unsigned char param9  = packet->data[CMD_POSITION_PARAM+8];
	unsigned char param10 = packet->data[CMD_POSITION_PARAM+9];
	unsigned int MIPS_timer_start, MIPS_timer_stop;
	
	*(((unsigned char*)&MIPS_timer_start) + 0) = param3;
	*(((unsigned char*)&MIPS_timer_start) + 1) = param4;
	*(((unsigned char*)&MIPS_timer_start) + 2) = param5;
	*(((unsigned char*)&MIPS_timer_start) + 3) = param6;

	*(((unsigned char*)&MIPS_timer_stop) + 0) = param7;
	*(((unsigned char*)&MIPS_timer_stop) + 1) = param8;
	*(((unsigned char*)&MIPS_timer_stop) + 2) = param9;
	*(((unsigned char*)&MIPS_timer_stop) + 3) = param10;
		
	Printf("CMD_MIPS_TV_TIMER %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", param1, param2, param3, param4, param5, param6, param7, param8, param9, param10);
	Printf("MIPS_timer_start %08X\n", MIPS_timer_start);
	Printf("MIPS_timer_stop %08X\n", MIPS_timer_stop);
	if(param1 == 0x01){	// MIPS1
		Printf("MIPS1\n");
		////MIPSドライバ更新に伴い、いったんコメントアウト 2013/11/14 小林
		////MIPS_command2(&mips1, param2, MIPS_timer_start, MIPS_timer_stop);
	}else{
		Printf("No such a MIPS\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_MIPS_TV(const HUPacket* packet)
{
	unsigned char param1  = packet->data[CMD_POSITION_PARAM];
	unsigned char param2  = packet->data[CMD_POSITION_PARAM+1];
			
	Printf("CMD_MIPS_TV %02X %02X\n", param1, param2);
	if(param1 == 0x01){	// MIPS1
		Printf("MIPS1\n");
		////MIPSドライバ更新に伴い、いったんコメントアウト 2013/11/14 小林
		////MIPS_command3(&mips1, param2);
	}else{
		Printf("No such a MIPS\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_MIPS_RV(const HUPacket* packet)
{
	unsigned char param1  = packet->data[CMD_POSITION_PARAM];
	unsigned char param2  = packet->data[CMD_POSITION_PARAM+1];
	unsigned char param3  = packet->data[CMD_POSITION_PARAM+2];
	unsigned char param4  = packet->data[CMD_POSITION_PARAM+3];
	unsigned char param5  = packet->data[CMD_POSITION_PARAM+4];
	unsigned short MIPS_vlt;

	*(((unsigned char*)&MIPS_vlt) + 0) = param4;
	*(((unsigned char*)&MIPS_vlt) + 1) = param5;

	Printf("CMD_MIPS_RV %02X %02X %02X %02X %02X\n", param1, param2, param3, param4, param5);
	Printf("MIPS_vlt %04X\n", MIPS_vlt);
	if(param1 == 0x01){	// MIPS1
		Printf("MIPS1\n");
		////MIPSドライバ更新に伴い、いったんコメントアウト 2013/11/14 小林
		////MIPS_command4(&mips1, param2, param3, MIPS_vlt);
	}else{
		Printf("No such a MIPS\n");
		return(-1);
	}

	return CMD_ERROR_NONE;
}

int		CMD_SET_CONT_GAIN(const HUPacket* packet)
{
	*(((unsigned char*)&AOCS_gain_P[0]) + 0) = packet->data[CMD_POSITION_PARAM + 0];
	*(((unsigned char*)&AOCS_gain_P[0]) + 1) = packet->data[CMD_POSITION_PARAM + 1];
	*(((unsigned char*)&AOCS_gain_P[0]) + 2) = packet->data[CMD_POSITION_PARAM + 2];
	*(((unsigned char*)&AOCS_gain_P[0]) + 3) = packet->data[CMD_POSITION_PARAM + 3];
	*(((unsigned char*)&AOCS_gain_P[0]) + 4) = packet->data[CMD_POSITION_PARAM + 4];
	*(((unsigned char*)&AOCS_gain_P[0]) + 5) = packet->data[CMD_POSITION_PARAM + 5];
	*(((unsigned char*)&AOCS_gain_P[0]) + 6) = packet->data[CMD_POSITION_PARAM + 6];
	*(((unsigned char*)&AOCS_gain_P[0]) + 7) = packet->data[CMD_POSITION_PARAM + 7];

	*(((unsigned char*)&AOCS_gain_P[1]) + 0) = packet->data[CMD_POSITION_PARAM + 8];
	*(((unsigned char*)&AOCS_gain_P[1]) + 1) = packet->data[CMD_POSITION_PARAM + 9];
	*(((unsigned char*)&AOCS_gain_P[1]) + 2) = packet->data[CMD_POSITION_PARAM + 10];
	*(((unsigned char*)&AOCS_gain_P[1]) + 3) = packet->data[CMD_POSITION_PARAM + 11];
	*(((unsigned char*)&AOCS_gain_P[1]) + 4) = packet->data[CMD_POSITION_PARAM + 12];
	*(((unsigned char*)&AOCS_gain_P[1]) + 5) = packet->data[CMD_POSITION_PARAM + 13];
	*(((unsigned char*)&AOCS_gain_P[1]) + 6) = packet->data[CMD_POSITION_PARAM + 14];
	*(((unsigned char*)&AOCS_gain_P[1]) + 7) = packet->data[CMD_POSITION_PARAM + 15];

	*(((unsigned char*)&AOCS_gain_P[2]) + 0) = packet->data[CMD_POSITION_PARAM + 16];
	*(((unsigned char*)&AOCS_gain_P[2]) + 1) = packet->data[CMD_POSITION_PARAM + 17];
	*(((unsigned char*)&AOCS_gain_P[2]) + 2) = packet->data[CMD_POSITION_PARAM + 18];
	*(((unsigned char*)&AOCS_gain_P[2]) + 3) = packet->data[CMD_POSITION_PARAM + 19];
	*(((unsigned char*)&AOCS_gain_P[2]) + 4) = packet->data[CMD_POSITION_PARAM + 20];
	*(((unsigned char*)&AOCS_gain_P[2]) + 5) = packet->data[CMD_POSITION_PARAM + 21];
	*(((unsigned char*)&AOCS_gain_P[2]) + 6) = packet->data[CMD_POSITION_PARAM + 22];
	*(((unsigned char*)&AOCS_gain_P[2]) + 7) = packet->data[CMD_POSITION_PARAM + 23];

	*(((unsigned char*)&AOCS_gain_D[0]) + 0) = packet->data[CMD_POSITION_PARAM + 24];
	*(((unsigned char*)&AOCS_gain_D[0]) + 1) = packet->data[CMD_POSITION_PARAM + 25];
	*(((unsigned char*)&AOCS_gain_D[0]) + 2) = packet->data[CMD_POSITION_PARAM + 26];
	*(((unsigned char*)&AOCS_gain_D[0]) + 3) = packet->data[CMD_POSITION_PARAM + 27];
	*(((unsigned char*)&AOCS_gain_D[0]) + 4) = packet->data[CMD_POSITION_PARAM + 28];
	*(((unsigned char*)&AOCS_gain_D[0]) + 5) = packet->data[CMD_POSITION_PARAM + 29];
	*(((unsigned char*)&AOCS_gain_D[0]) + 6) = packet->data[CMD_POSITION_PARAM + 30];
	*(((unsigned char*)&AOCS_gain_D[0]) + 7) = packet->data[CMD_POSITION_PARAM + 31];

	*(((unsigned char*)&AOCS_gain_D[1]) + 0) = packet->data[CMD_POSITION_PARAM + 32];
	*(((unsigned char*)&AOCS_gain_D[1]) + 1) = packet->data[CMD_POSITION_PARAM + 33];
	*(((unsigned char*)&AOCS_gain_D[1]) + 2) = packet->data[CMD_POSITION_PARAM + 34];
	*(((unsigned char*)&AOCS_gain_D[1]) + 3) = packet->data[CMD_POSITION_PARAM + 35];
	*(((unsigned char*)&AOCS_gain_D[1]) + 4) = packet->data[CMD_POSITION_PARAM + 36];
	*(((unsigned char*)&AOCS_gain_D[1]) + 5) = packet->data[CMD_POSITION_PARAM + 37];
	*(((unsigned char*)&AOCS_gain_D[1]) + 6) = packet->data[CMD_POSITION_PARAM + 38];
	*(((unsigned char*)&AOCS_gain_D[1]) + 7) = packet->data[CMD_POSITION_PARAM + 39];

	*(((unsigned char*)&AOCS_gain_D[2]) + 0) = packet->data[CMD_POSITION_PARAM + 40];
	*(((unsigned char*)&AOCS_gain_D[2]) + 1) = packet->data[CMD_POSITION_PARAM + 41];
	*(((unsigned char*)&AOCS_gain_D[2]) + 2) = packet->data[CMD_POSITION_PARAM + 42];
	*(((unsigned char*)&AOCS_gain_D[2]) + 3) = packet->data[CMD_POSITION_PARAM + 43];
	*(((unsigned char*)&AOCS_gain_D[2]) + 4) = packet->data[CMD_POSITION_PARAM + 44];
	*(((unsigned char*)&AOCS_gain_D[2]) + 5) = packet->data[CMD_POSITION_PARAM + 45];
	*(((unsigned char*)&AOCS_gain_D[2]) + 6) = packet->data[CMD_POSITION_PARAM + 46];
	*(((unsigned char*)&AOCS_gain_D[2]) + 7) = packet->data[CMD_POSITION_PARAM + 47];

	return CMD_ERROR_NONE;

}

int		CMD_SET_INERTIA(const HUPacket* packet)
{

	*(((unsigned char*)&AOCS_inertia[0][0]) + 0) = packet->data[CMD_POSITION_PARAM + 0];
	*(((unsigned char*)&AOCS_inertia[0][0]) + 1) = packet->data[CMD_POSITION_PARAM + 1];
	*(((unsigned char*)&AOCS_inertia[0][0]) + 2) = packet->data[CMD_POSITION_PARAM + 2];
	*(((unsigned char*)&AOCS_inertia[0][0]) + 3) = packet->data[CMD_POSITION_PARAM + 3];
	*(((unsigned char*)&AOCS_inertia[0][0]) + 4) = packet->data[CMD_POSITION_PARAM + 4];
	*(((unsigned char*)&AOCS_inertia[0][0]) + 5) = packet->data[CMD_POSITION_PARAM + 5];
	*(((unsigned char*)&AOCS_inertia[0][0]) + 6) = packet->data[CMD_POSITION_PARAM + 6];
	*(((unsigned char*)&AOCS_inertia[0][0]) + 7) = packet->data[CMD_POSITION_PARAM + 7];

	*(((unsigned char*)&AOCS_inertia[0][1]) + 0) = packet->data[CMD_POSITION_PARAM + 8];
	*(((unsigned char*)&AOCS_inertia[0][1]) + 1) = packet->data[CMD_POSITION_PARAM + 9];
	*(((unsigned char*)&AOCS_inertia[0][1]) + 2) = packet->data[CMD_POSITION_PARAM + 10];
	*(((unsigned char*)&AOCS_inertia[0][1]) + 3) = packet->data[CMD_POSITION_PARAM + 11];
	*(((unsigned char*)&AOCS_inertia[0][1]) + 4) = packet->data[CMD_POSITION_PARAM + 12];
	*(((unsigned char*)&AOCS_inertia[0][1]) + 5) = packet->data[CMD_POSITION_PARAM + 13];
	*(((unsigned char*)&AOCS_inertia[0][1]) + 6) = packet->data[CMD_POSITION_PARAM + 14];
	*(((unsigned char*)&AOCS_inertia[0][1]) + 7) = packet->data[CMD_POSITION_PARAM + 15];

	*(((unsigned char*)&AOCS_inertia[0][2]) + 0) = packet->data[CMD_POSITION_PARAM + 16];
	*(((unsigned char*)&AOCS_inertia[0][2]) + 1) = packet->data[CMD_POSITION_PARAM + 17];
	*(((unsigned char*)&AOCS_inertia[0][2]) + 2) = packet->data[CMD_POSITION_PARAM + 18];
	*(((unsigned char*)&AOCS_inertia[0][2]) + 3) = packet->data[CMD_POSITION_PARAM + 19];
	*(((unsigned char*)&AOCS_inertia[0][2]) + 4) = packet->data[CMD_POSITION_PARAM + 20];
	*(((unsigned char*)&AOCS_inertia[0][2]) + 5) = packet->data[CMD_POSITION_PARAM + 21];
	*(((unsigned char*)&AOCS_inertia[0][2]) + 6) = packet->data[CMD_POSITION_PARAM + 22];
	*(((unsigned char*)&AOCS_inertia[0][2]) + 7) = packet->data[CMD_POSITION_PARAM + 23];

	*(((unsigned char*)&AOCS_inertia[1][1]) + 0) = packet->data[CMD_POSITION_PARAM + 24];
	*(((unsigned char*)&AOCS_inertia[1][1]) + 1) = packet->data[CMD_POSITION_PARAM + 25];
	*(((unsigned char*)&AOCS_inertia[1][1]) + 2) = packet->data[CMD_POSITION_PARAM + 26];
	*(((unsigned char*)&AOCS_inertia[1][1]) + 3) = packet->data[CMD_POSITION_PARAM + 27];
	*(((unsigned char*)&AOCS_inertia[1][1]) + 4) = packet->data[CMD_POSITION_PARAM + 28];
	*(((unsigned char*)&AOCS_inertia[1][1]) + 5) = packet->data[CMD_POSITION_PARAM + 29];
	*(((unsigned char*)&AOCS_inertia[1][1]) + 6) = packet->data[CMD_POSITION_PARAM + 30];
	*(((unsigned char*)&AOCS_inertia[1][1]) + 7) = packet->data[CMD_POSITION_PARAM + 31];

	*(((unsigned char*)&AOCS_inertia[1][2]) + 0) = packet->data[CMD_POSITION_PARAM + 32];
	*(((unsigned char*)&AOCS_inertia[1][2]) + 1) = packet->data[CMD_POSITION_PARAM + 33];
	*(((unsigned char*)&AOCS_inertia[1][2]) + 2) = packet->data[CMD_POSITION_PARAM + 34];
	*(((unsigned char*)&AOCS_inertia[1][2]) + 3) = packet->data[CMD_POSITION_PARAM + 35];
	*(((unsigned char*)&AOCS_inertia[1][2]) + 4) = packet->data[CMD_POSITION_PARAM + 36];
	*(((unsigned char*)&AOCS_inertia[1][2]) + 5) = packet->data[CMD_POSITION_PARAM + 37];
	*(((unsigned char*)&AOCS_inertia[1][2]) + 6) = packet->data[CMD_POSITION_PARAM + 38];
	*(((unsigned char*)&AOCS_inertia[1][2]) + 7) = packet->data[CMD_POSITION_PARAM + 39];

	*(((unsigned char*)&AOCS_inertia[2][2]) + 0) = packet->data[CMD_POSITION_PARAM + 40];
	*(((unsigned char*)&AOCS_inertia[2][2]) + 1) = packet->data[CMD_POSITION_PARAM + 41];
	*(((unsigned char*)&AOCS_inertia[2][2]) + 2) = packet->data[CMD_POSITION_PARAM + 42];
	*(((unsigned char*)&AOCS_inertia[2][2]) + 3) = packet->data[CMD_POSITION_PARAM + 43];
	*(((unsigned char*)&AOCS_inertia[2][2]) + 4) = packet->data[CMD_POSITION_PARAM + 44];
	*(((unsigned char*)&AOCS_inertia[2][2]) + 5) = packet->data[CMD_POSITION_PARAM + 45];
	*(((unsigned char*)&AOCS_inertia[2][2]) + 6) = packet->data[CMD_POSITION_PARAM + 46];
	*(((unsigned char*)&AOCS_inertia[2][2]) + 7) = packet->data[CMD_POSITION_PARAM + 47];

	AOCS_inertia[1][0] = AOCS_inertia[0][1];
	AOCS_inertia[2][0] = AOCS_inertia[0][2];
	AOCS_inertia[2][1] = AOCS_inertia[1][2];

	return CMD_ERROR_NONE;

}

int		CMD_SET_SPIN_PARAM(const HUPacket* packet)
{

	*(((unsigned char*)&AOCS_spin_wt_b[0]) + 0) = packet->data[CMD_POSITION_PARAM + 0];
	*(((unsigned char*)&AOCS_spin_wt_b[0]) + 1) = packet->data[CMD_POSITION_PARAM + 1];
	*(((unsigned char*)&AOCS_spin_wt_b[0]) + 2) = packet->data[CMD_POSITION_PARAM + 2];
	*(((unsigned char*)&AOCS_spin_wt_b[0]) + 3) = packet->data[CMD_POSITION_PARAM + 3];
	*(((unsigned char*)&AOCS_spin_wt_b[0]) + 4) = packet->data[CMD_POSITION_PARAM + 4];
	*(((unsigned char*)&AOCS_spin_wt_b[0]) + 5) = packet->data[CMD_POSITION_PARAM + 5];
	*(((unsigned char*)&AOCS_spin_wt_b[0]) + 6) = packet->data[CMD_POSITION_PARAM + 6];
	*(((unsigned char*)&AOCS_spin_wt_b[0]) + 7) = packet->data[CMD_POSITION_PARAM + 7];

	*(((unsigned char*)&AOCS_spin_wt_b[1]) + 0) = packet->data[CMD_POSITION_PARAM + 8];
	*(((unsigned char*)&AOCS_spin_wt_b[1]) + 1) = packet->data[CMD_POSITION_PARAM + 9];
	*(((unsigned char*)&AOCS_spin_wt_b[1]) + 2) = packet->data[CMD_POSITION_PARAM + 10];
	*(((unsigned char*)&AOCS_spin_wt_b[1]) + 3) = packet->data[CMD_POSITION_PARAM + 11];
	*(((unsigned char*)&AOCS_spin_wt_b[1]) + 4) = packet->data[CMD_POSITION_PARAM + 12];
	*(((unsigned char*)&AOCS_spin_wt_b[1]) + 5) = packet->data[CMD_POSITION_PARAM + 13];
	*(((unsigned char*)&AOCS_spin_wt_b[1]) + 6) = packet->data[CMD_POSITION_PARAM + 14];
	*(((unsigned char*)&AOCS_spin_wt_b[1]) + 7) = packet->data[CMD_POSITION_PARAM + 15];

	*(((unsigned char*)&AOCS_spin_wt_b[2]) + 0) = packet->data[CMD_POSITION_PARAM + 16];
	*(((unsigned char*)&AOCS_spin_wt_b[2]) + 1) = packet->data[CMD_POSITION_PARAM + 17];
	*(((unsigned char*)&AOCS_spin_wt_b[2]) + 2) = packet->data[CMD_POSITION_PARAM + 18];
	*(((unsigned char*)&AOCS_spin_wt_b[2]) + 3) = packet->data[CMD_POSITION_PARAM + 19];
	*(((unsigned char*)&AOCS_spin_wt_b[2]) + 4) = packet->data[CMD_POSITION_PARAM + 20];
	*(((unsigned char*)&AOCS_spin_wt_b[2]) + 5) = packet->data[CMD_POSITION_PARAM + 21];
	*(((unsigned char*)&AOCS_spin_wt_b[2]) + 6) = packet->data[CMD_POSITION_PARAM + 22];
	*(((unsigned char*)&AOCS_spin_wt_b[2]) + 7) = packet->data[CMD_POSITION_PARAM + 23];

	*(((unsigned char*)&AOCS_spin_wt_thresh) + 0) = packet->data[CMD_POSITION_PARAM + 24];
	*(((unsigned char*)&AOCS_spin_wt_thresh) + 1) = packet->data[CMD_POSITION_PARAM + 25];
	*(((unsigned char*)&AOCS_spin_wt_thresh) + 2) = packet->data[CMD_POSITION_PARAM + 26];
	*(((unsigned char*)&AOCS_spin_wt_thresh) + 3) = packet->data[CMD_POSITION_PARAM + 27];
	*(((unsigned char*)&AOCS_spin_wt_thresh) + 4) = packet->data[CMD_POSITION_PARAM + 28];
	*(((unsigned char*)&AOCS_spin_wt_thresh) + 5) = packet->data[CMD_POSITION_PARAM + 29];
	*(((unsigned char*)&AOCS_spin_wt_thresh) + 6) = packet->data[CMD_POSITION_PARAM + 30];
	*(((unsigned char*)&AOCS_spin_wt_thresh) + 7) = packet->data[CMD_POSITION_PARAM + 31];

	*(((unsigned char*)&AOCS_spin_offset) + 0) = packet->data[CMD_POSITION_PARAM + 32];
	*(((unsigned char*)&AOCS_spin_offset) + 1) = packet->data[CMD_POSITION_PARAM + 33];
	*(((unsigned char*)&AOCS_spin_offset) + 2) = packet->data[CMD_POSITION_PARAM + 34];
	*(((unsigned char*)&AOCS_spin_offset) + 3) = packet->data[CMD_POSITION_PARAM + 35];
	*(((unsigned char*)&AOCS_spin_offset) + 4) = packet->data[CMD_POSITION_PARAM + 36];
	*(((unsigned char*)&AOCS_spin_offset) + 5) = packet->data[CMD_POSITION_PARAM + 37];
	*(((unsigned char*)&AOCS_spin_offset) + 6) = packet->data[CMD_POSITION_PARAM + 38];
	*(((unsigned char*)&AOCS_spin_offset) + 7) = packet->data[CMD_POSITION_PARAM + 39];

	*(((unsigned char*)&AOCS_MTQ_max_count) + 0) = packet->data[CMD_POSITION_PARAM + 40];
	*(((unsigned char*)&AOCS_MTQ_max_count) + 1) = packet->data[CMD_POSITION_PARAM + 41];

	*(((unsigned char*)&AOCS_MTQ_start_count) + 0) = packet->data[CMD_POSITION_PARAM + 42];
	*(((unsigned char*)&AOCS_MTQ_start_count) + 1) = packet->data[CMD_POSITION_PARAM + 43];

	*(((unsigned char*)&AOCS_MTQ_stop_count) + 0) = packet->data[CMD_POSITION_PARAM + 44];
	*(((unsigned char*)&AOCS_MTQ_stop_count) + 1) = packet->data[CMD_POSITION_PARAM + 45];

	return CMD_ERROR_NONE;

}

int		CMD_SET_RW_PARAM(const HUPacket* packet)
{

	*(((unsigned char*)&RW_R) + 0) = packet->data[CMD_POSITION_PARAM + 0];
	*(((unsigned char*)&RW_R) + 1) = packet->data[CMD_POSITION_PARAM + 1];
	*(((unsigned char*)&RW_R) + 2) = packet->data[CMD_POSITION_PARAM + 2];
	*(((unsigned char*)&RW_R) + 3) = packet->data[CMD_POSITION_PARAM + 3];
	*(((unsigned char*)&RW_R) + 4) = packet->data[CMD_POSITION_PARAM + 4];
	*(((unsigned char*)&RW_R) + 5) = packet->data[CMD_POSITION_PARAM + 5];
	*(((unsigned char*)&RW_R) + 6) = packet->data[CMD_POSITION_PARAM + 6];
	*(((unsigned char*)&RW_R) + 7) = packet->data[CMD_POSITION_PARAM + 7];

	*(((unsigned char*)&RW_J) + 0) = packet->data[CMD_POSITION_PARAM + 8];
	*(((unsigned char*)&RW_J) + 1) = packet->data[CMD_POSITION_PARAM + 9];
	*(((unsigned char*)&RW_J) + 2) = packet->data[CMD_POSITION_PARAM + 10];
	*(((unsigned char*)&RW_J) + 3) = packet->data[CMD_POSITION_PARAM + 11];
	*(((unsigned char*)&RW_J) + 4) = packet->data[CMD_POSITION_PARAM + 12];
	*(((unsigned char*)&RW_J) + 5) = packet->data[CMD_POSITION_PARAM + 13];
	*(((unsigned char*)&RW_J) + 6) = packet->data[CMD_POSITION_PARAM + 14];
	*(((unsigned char*)&RW_J) + 7) = packet->data[CMD_POSITION_PARAM + 15];

	*(((unsigned char*)&RW_kE) + 0) = packet->data[CMD_POSITION_PARAM + 16];
	*(((unsigned char*)&RW_kE) + 1) = packet->data[CMD_POSITION_PARAM + 17];
	*(((unsigned char*)&RW_kE) + 2) = packet->data[CMD_POSITION_PARAM + 18];
	*(((unsigned char*)&RW_kE) + 3) = packet->data[CMD_POSITION_PARAM + 19];
	*(((unsigned char*)&RW_kE) + 4) = packet->data[CMD_POSITION_PARAM + 20];
	*(((unsigned char*)&RW_kE) + 5) = packet->data[CMD_POSITION_PARAM + 21];
	*(((unsigned char*)&RW_kE) + 6) = packet->data[CMD_POSITION_PARAM + 22];
	*(((unsigned char*)&RW_kE) + 7) = packet->data[CMD_POSITION_PARAM + 23];

	*(((unsigned char*)&RW_kT) + 0) = packet->data[CMD_POSITION_PARAM + 24];
	*(((unsigned char*)&RW_kT) + 1) = packet->data[CMD_POSITION_PARAM + 25];
	*(((unsigned char*)&RW_kT) + 2) = packet->data[CMD_POSITION_PARAM + 26];
	*(((unsigned char*)&RW_kT) + 3) = packet->data[CMD_POSITION_PARAM + 27];
	*(((unsigned char*)&RW_kT) + 4) = packet->data[CMD_POSITION_PARAM + 28];
	*(((unsigned char*)&RW_kT) + 5) = packet->data[CMD_POSITION_PARAM + 29];
	*(((unsigned char*)&RW_kT) + 6) = packet->data[CMD_POSITION_PARAM + 30];
	*(((unsigned char*)&RW_kT) + 7) = packet->data[CMD_POSITION_PARAM + 31];

	*(((unsigned char*)&RW_tau) + 0) = packet->data[CMD_POSITION_PARAM + 32];
	*(((unsigned char*)&RW_tau) + 1) = packet->data[CMD_POSITION_PARAM + 33];
	*(((unsigned char*)&RW_tau) + 2) = packet->data[CMD_POSITION_PARAM + 34];
	*(((unsigned char*)&RW_tau) + 3) = packet->data[CMD_POSITION_PARAM + 35];
	*(((unsigned char*)&RW_tau) + 4) = packet->data[CMD_POSITION_PARAM + 36];
	*(((unsigned char*)&RW_tau) + 5) = packet->data[CMD_POSITION_PARAM + 37];
	*(((unsigned char*)&RW_tau) + 6) = packet->data[CMD_POSITION_PARAM + 38];
	*(((unsigned char*)&RW_tau) + 7) = packet->data[CMD_POSITION_PARAM + 39];

	return CMD_ERROR_NONE;

}

int		CMD_SET_RW_LIMIT(const HUPacket* packet)
{

	*(((unsigned char*)&RW_V_limit) + 0) = packet->data[CMD_POSITION_PARAM + 0];
	*(((unsigned char*)&RW_V_limit) + 1) = packet->data[CMD_POSITION_PARAM + 1];
	*(((unsigned char*)&RW_V_limit) + 2) = packet->data[CMD_POSITION_PARAM + 2];
	*(((unsigned char*)&RW_V_limit) + 3) = packet->data[CMD_POSITION_PARAM + 3];
	*(((unsigned char*)&RW_V_limit) + 4) = packet->data[CMD_POSITION_PARAM + 4];
	*(((unsigned char*)&RW_V_limit) + 5) = packet->data[CMD_POSITION_PARAM + 5];
	*(((unsigned char*)&RW_V_limit) + 6) = packet->data[CMD_POSITION_PARAM + 6];
	*(((unsigned char*)&RW_V_limit) + 7) = packet->data[CMD_POSITION_PARAM + 7];

	*(((unsigned char*)&RW_Integ_V_limit) + 0) = packet->data[CMD_POSITION_PARAM + 8];
	*(((unsigned char*)&RW_Integ_V_limit) + 1) = packet->data[CMD_POSITION_PARAM + 9];
	*(((unsigned char*)&RW_Integ_V_limit) + 2) = packet->data[CMD_POSITION_PARAM + 10];
	*(((unsigned char*)&RW_Integ_V_limit) + 3) = packet->data[CMD_POSITION_PARAM + 11];
	*(((unsigned char*)&RW_Integ_V_limit) + 4) = packet->data[CMD_POSITION_PARAM + 12];
	*(((unsigned char*)&RW_Integ_V_limit) + 5) = packet->data[CMD_POSITION_PARAM + 13];
	*(((unsigned char*)&RW_Integ_V_limit) + 6) = packet->data[CMD_POSITION_PARAM + 14];
	*(((unsigned char*)&RW_Integ_V_limit) + 7) = packet->data[CMD_POSITION_PARAM + 15];

	*(((unsigned char*)&RW_rate_limit) + 0) = packet->data[CMD_POSITION_PARAM + 16];
	*(((unsigned char*)&RW_rate_limit) + 1) = packet->data[CMD_POSITION_PARAM + 17];
	*(((unsigned char*)&RW_rate_limit) + 2) = packet->data[CMD_POSITION_PARAM + 18];
	*(((unsigned char*)&RW_rate_limit) + 3) = packet->data[CMD_POSITION_PARAM + 19];
	*(((unsigned char*)&RW_rate_limit) + 4) = packet->data[CMD_POSITION_PARAM + 20];
	*(((unsigned char*)&RW_rate_limit) + 5) = packet->data[CMD_POSITION_PARAM + 21];
	*(((unsigned char*)&RW_rate_limit) + 6) = packet->data[CMD_POSITION_PARAM + 22];
	*(((unsigned char*)&RW_rate_limit) + 7) = packet->data[CMD_POSITION_PARAM + 23];

	if(RW_V_limit > 28.0){
		RW_V_limit = 28.0;
	}

	if(RW_Integ_V_limit > 28.0){
		RW_Integ_V_limit = 28.0;
	}
	if(RW_rate_limit > 10000.0){
		RW_Integ_V_limit = 10000.0;
	}

	return CMD_ERROR_NONE;

}

int		CMD_SET_DCM(const HUPacket* packet)
{

	unsigned char param1 = packet->data[CMD_POSITION_PARAM];
	double q[4]; // q0は正で規格化する

	*(((unsigned char*)&q[1]) + 0) = packet->data[CMD_POSITION_PARAM + 1];
	*(((unsigned char*)&q[1]) + 1) = packet->data[CMD_POSITION_PARAM + 2];
	*(((unsigned char*)&q[1]) + 2) = packet->data[CMD_POSITION_PARAM + 3];
	*(((unsigned char*)&q[1]) + 3) = packet->data[CMD_POSITION_PARAM + 4];
	*(((unsigned char*)&q[1]) + 4) = packet->data[CMD_POSITION_PARAM + 5];
	*(((unsigned char*)&q[1]) + 5) = packet->data[CMD_POSITION_PARAM + 6];
	*(((unsigned char*)&q[1]) + 6) = packet->data[CMD_POSITION_PARAM + 7];
	*(((unsigned char*)&q[1]) + 7) = packet->data[CMD_POSITION_PARAM + 8];

	*(((unsigned char*)&q[2]) + 0) = packet->data[CMD_POSITION_PARAM + 9];
	*(((unsigned char*)&q[2]) + 1) = packet->data[CMD_POSITION_PARAM + 10];
	*(((unsigned char*)&q[2]) + 2) = packet->data[CMD_POSITION_PARAM + 11];
	*(((unsigned char*)&q[2]) + 3) = packet->data[CMD_POSITION_PARAM + 12];
	*(((unsigned char*)&q[2]) + 4) = packet->data[CMD_POSITION_PARAM + 13];
	*(((unsigned char*)&q[2]) + 5) = packet->data[CMD_POSITION_PARAM + 14];
	*(((unsigned char*)&q[2]) + 6) = packet->data[CMD_POSITION_PARAM + 15];
	*(((unsigned char*)&q[2]) + 7) = packet->data[CMD_POSITION_PARAM + 16];

	*(((unsigned char*)&q[3]) + 0) = packet->data[CMD_POSITION_PARAM + 17];
	*(((unsigned char*)&q[3]) + 1) = packet->data[CMD_POSITION_PARAM + 18];
	*(((unsigned char*)&q[3]) + 2) = packet->data[CMD_POSITION_PARAM + 19];
	*(((unsigned char*)&q[3]) + 3) = packet->data[CMD_POSITION_PARAM + 20];
	*(((unsigned char*)&q[3]) + 4) = packet->data[CMD_POSITION_PARAM + 21];
	*(((unsigned char*)&q[3]) + 5) = packet->data[CMD_POSITION_PARAM + 22];
	*(((unsigned char*)&q[3]) + 6) = packet->data[CMD_POSITION_PARAM + 23];
	*(((unsigned char*)&q[3]) + 7) = packet->data[CMD_POSITION_PARAM + 24];

	q[0] = 1.0 - q[1] * q[1] - q[2] * q[2] - q[3] * q[3]; // q[0]^2
	if(q[0] < 0.0){
		return -1;
	}

	q[0] = sqrt(q[0]); // q[0]^2の平方根を取る
  
	switch(param1){
		case 0:
			GAS_c2b_quat[0] = q[0];
			GAS_c2b_quat[1] = q[1];
			GAS_c2b_quat[2] = q[2];
			GAS_c2b_quat[3] = q[3];
			Quat2DCM(GAS_c2b_quat, GAS_c2b_DCM);
			break;
		case 1:
			GYRO_c2b_quat[0] = q[0];
			GYRO_c2b_quat[1] = q[1];
			GYRO_c2b_quat[2] = q[2];
			GYRO_c2b_quat[3] = q[3];
			Quat2DCM(GYRO_c2b_quat, GYRO_c2b_DCM);
			break;
		case 2:
			NSAS1_c2b_quat[0] = q[0];
			NSAS1_c2b_quat[1] = q[1];
			NSAS1_c2b_quat[2] = q[2];
			NSAS1_c2b_quat[3] = q[3];
			Quat2DCM(NSAS1_c2b_quat, NSAS1_c2b_DCM);
			break;
		case 3:
			NSAS2_c2b_quat[0] = q[0];
			NSAS2_c2b_quat[1] = q[1];
			NSAS2_c2b_quat[2] = q[2];
			NSAS2_c2b_quat[3] = q[3];
			Quat2DCM(NSAS2_c2b_quat, NSAS2_c2b_DCM);
			break;
		case 4:
			NSAS3_c2b_quat[0] = q[0];
			NSAS3_c2b_quat[1] = q[1];
			NSAS3_c2b_quat[2] = q[2];
			NSAS3_c2b_quat[3] = q[3];
			Quat2DCM(NSAS3_c2b_quat, NSAS3_c2b_DCM);
			break;
		case 5:
			STT_c2b_quat[0] = q[0];
			STT_c2b_quat[1] = q[1];
			STT_c2b_quat[2] = q[2];
			STT_c2b_quat[3] = q[3];
			Quat2DCM(STT_c2b_quat, STT_c2b_DCM);
			break;
		default:
			break;
	}

	return CMD_ERROR_NONE;

}

int		CMD_SET_MTQ_POL(const HUPacket* packet)
{

	MTQ1_c2b = packet->data[CMD_POSITION_PARAM + 0];
	MTQ2_c2b = packet->data[CMD_POSITION_PARAM + 1];
	MTQ3_c2b = packet->data[CMD_POSITION_PARAM + 2];

	return CMD_ERROR_NONE;

}

int		CMD_SET_SKEW_PARAM(const HUPacket* packet)
{

	*(((unsigned char*)&skew_alpha) + 0) = packet->data[CMD_POSITION_PARAM + 0];
	*(((unsigned char*)&skew_alpha) + 1) = packet->data[CMD_POSITION_PARAM + 1];
	*(((unsigned char*)&skew_alpha) + 2) = packet->data[CMD_POSITION_PARAM + 2];
	*(((unsigned char*)&skew_alpha) + 3) = packet->data[CMD_POSITION_PARAM + 3];
	*(((unsigned char*)&skew_alpha) + 4) = packet->data[CMD_POSITION_PARAM + 4];
	*(((unsigned char*)&skew_alpha) + 5) = packet->data[CMD_POSITION_PARAM + 5];
	*(((unsigned char*)&skew_alpha) + 6) = packet->data[CMD_POSITION_PARAM + 6];
	*(((unsigned char*)&skew_alpha) + 7) = packet->data[CMD_POSITION_PARAM + 7];

	*(((unsigned char*)&skew_beta) + 0) = packet->data[CMD_POSITION_PARAM + 8];
	*(((unsigned char*)&skew_beta) + 1) = packet->data[CMD_POSITION_PARAM + 9];
	*(((unsigned char*)&skew_beta) + 2) = packet->data[CMD_POSITION_PARAM + 10];
	*(((unsigned char*)&skew_beta) + 3) = packet->data[CMD_POSITION_PARAM + 11];
	*(((unsigned char*)&skew_beta) + 4) = packet->data[CMD_POSITION_PARAM + 12];
	*(((unsigned char*)&skew_beta) + 5) = packet->data[CMD_POSITION_PARAM + 13];
	*(((unsigned char*)&skew_beta) + 6) = packet->data[CMD_POSITION_PARAM + 14];
	*(((unsigned char*)&skew_beta) + 7) = packet->data[CMD_POSITION_PARAM + 15];

	set_skew_param();

	return CMD_ERROR_NONE;

}

int		CMD_SET_D_MATRIX(const HUPacket* packet)
{

	unsigned char n = packet->data[CMD_POSITION_PARAM];

	*(((unsigned char*)&three_one_skew_D[n][0][0]) + 0) = packet->data[CMD_POSITION_PARAM + 1];
	*(((unsigned char*)&three_one_skew_D[n][0][0]) + 1) = packet->data[CMD_POSITION_PARAM + 2];
	*(((unsigned char*)&three_one_skew_D[n][0][0]) + 2) = packet->data[CMD_POSITION_PARAM + 3];
	*(((unsigned char*)&three_one_skew_D[n][0][0]) + 3) = packet->data[CMD_POSITION_PARAM + 4];
	*(((unsigned char*)&three_one_skew_D[n][0][0]) + 4) = packet->data[CMD_POSITION_PARAM + 5];
	*(((unsigned char*)&three_one_skew_D[n][0][0]) + 5) = packet->data[CMD_POSITION_PARAM + 6];
	*(((unsigned char*)&three_one_skew_D[n][0][0]) + 6) = packet->data[CMD_POSITION_PARAM + 7];
	*(((unsigned char*)&three_one_skew_D[n][0][0]) + 7) = packet->data[CMD_POSITION_PARAM + 8];

	*(((unsigned char*)&three_one_skew_D[n][0][1]) + 0) = packet->data[CMD_POSITION_PARAM + 9];
	*(((unsigned char*)&three_one_skew_D[n][0][1]) + 1) = packet->data[CMD_POSITION_PARAM + 10];
	*(((unsigned char*)&three_one_skew_D[n][0][1]) + 2) = packet->data[CMD_POSITION_PARAM + 11];
	*(((unsigned char*)&three_one_skew_D[n][0][1]) + 3) = packet->data[CMD_POSITION_PARAM + 12];
	*(((unsigned char*)&three_one_skew_D[n][0][1]) + 4) = packet->data[CMD_POSITION_PARAM + 13];
	*(((unsigned char*)&three_one_skew_D[n][0][1]) + 5) = packet->data[CMD_POSITION_PARAM + 14];
	*(((unsigned char*)&three_one_skew_D[n][0][1]) + 6) = packet->data[CMD_POSITION_PARAM + 15];
	*(((unsigned char*)&three_one_skew_D[n][0][1]) + 7) = packet->data[CMD_POSITION_PARAM + 16];

	*(((unsigned char*)&three_one_skew_D[n][0][2]) + 0) = packet->data[CMD_POSITION_PARAM + 17];
	*(((unsigned char*)&three_one_skew_D[n][0][2]) + 1) = packet->data[CMD_POSITION_PARAM + 18];
	*(((unsigned char*)&three_one_skew_D[n][0][2]) + 2) = packet->data[CMD_POSITION_PARAM + 19];
	*(((unsigned char*)&three_one_skew_D[n][0][2]) + 3) = packet->data[CMD_POSITION_PARAM + 20];
	*(((unsigned char*)&three_one_skew_D[n][0][2]) + 4) = packet->data[CMD_POSITION_PARAM + 21];
	*(((unsigned char*)&three_one_skew_D[n][0][2]) + 5) = packet->data[CMD_POSITION_PARAM + 22];
	*(((unsigned char*)&three_one_skew_D[n][0][2]) + 6) = packet->data[CMD_POSITION_PARAM + 23];
	*(((unsigned char*)&three_one_skew_D[n][0][2]) + 7) = packet->data[CMD_POSITION_PARAM + 24];

	*(((unsigned char*)&three_one_skew_D[n][1][0]) + 0) = packet->data[CMD_POSITION_PARAM + 25];
	*(((unsigned char*)&three_one_skew_D[n][1][0]) + 1) = packet->data[CMD_POSITION_PARAM + 26];
	*(((unsigned char*)&three_one_skew_D[n][1][0]) + 2) = packet->data[CMD_POSITION_PARAM + 27];
	*(((unsigned char*)&three_one_skew_D[n][1][0]) + 3) = packet->data[CMD_POSITION_PARAM + 28];
	*(((unsigned char*)&three_one_skew_D[n][1][0]) + 4) = packet->data[CMD_POSITION_PARAM + 29];
	*(((unsigned char*)&three_one_skew_D[n][1][0]) + 5) = packet->data[CMD_POSITION_PARAM + 30];
	*(((unsigned char*)&three_one_skew_D[n][1][0]) + 6) = packet->data[CMD_POSITION_PARAM + 31];
	*(((unsigned char*)&three_one_skew_D[n][1][0]) + 7) = packet->data[CMD_POSITION_PARAM + 32];

	*(((unsigned char*)&three_one_skew_D[n][1][1]) + 0) = packet->data[CMD_POSITION_PARAM + 33];
	*(((unsigned char*)&three_one_skew_D[n][1][1]) + 1) = packet->data[CMD_POSITION_PARAM + 34];
	*(((unsigned char*)&three_one_skew_D[n][1][1]) + 2) = packet->data[CMD_POSITION_PARAM + 35];
	*(((unsigned char*)&three_one_skew_D[n][1][1]) + 3) = packet->data[CMD_POSITION_PARAM + 36];
	*(((unsigned char*)&three_one_skew_D[n][1][1]) + 4) = packet->data[CMD_POSITION_PARAM + 37];
	*(((unsigned char*)&three_one_skew_D[n][1][1]) + 5) = packet->data[CMD_POSITION_PARAM + 38];
	*(((unsigned char*)&three_one_skew_D[n][1][1]) + 6) = packet->data[CMD_POSITION_PARAM + 39];
	*(((unsigned char*)&three_one_skew_D[n][1][1]) + 7) = packet->data[CMD_POSITION_PARAM + 40];

	*(((unsigned char*)&three_one_skew_D[n][1][2]) + 0) = packet->data[CMD_POSITION_PARAM + 41];
	*(((unsigned char*)&three_one_skew_D[n][1][2]) + 1) = packet->data[CMD_POSITION_PARAM + 42];
	*(((unsigned char*)&three_one_skew_D[n][1][2]) + 2) = packet->data[CMD_POSITION_PARAM + 43];
	*(((unsigned char*)&three_one_skew_D[n][1][2]) + 3) = packet->data[CMD_POSITION_PARAM + 44];
	*(((unsigned char*)&three_one_skew_D[n][1][2]) + 4) = packet->data[CMD_POSITION_PARAM + 45];
	*(((unsigned char*)&three_one_skew_D[n][1][2]) + 5) = packet->data[CMD_POSITION_PARAM + 46];
	*(((unsigned char*)&three_one_skew_D[n][1][2]) + 6) = packet->data[CMD_POSITION_PARAM + 47];
	*(((unsigned char*)&three_one_skew_D[n][1][2]) + 7) = packet->data[CMD_POSITION_PARAM + 48];

	*(((unsigned char*)&three_one_skew_D[n][2][0]) + 0) = packet->data[CMD_POSITION_PARAM + 49];
	*(((unsigned char*)&three_one_skew_D[n][2][0]) + 1) = packet->data[CMD_POSITION_PARAM + 50];
	*(((unsigned char*)&three_one_skew_D[n][2][0]) + 2) = packet->data[CMD_POSITION_PARAM + 51];
	*(((unsigned char*)&three_one_skew_D[n][2][0]) + 3) = packet->data[CMD_POSITION_PARAM + 52];
	*(((unsigned char*)&three_one_skew_D[n][2][0]) + 4) = packet->data[CMD_POSITION_PARAM + 53];
	*(((unsigned char*)&three_one_skew_D[n][2][0]) + 5) = packet->data[CMD_POSITION_PARAM + 54];
	*(((unsigned char*)&three_one_skew_D[n][2][0]) + 6) = packet->data[CMD_POSITION_PARAM + 55];
	*(((unsigned char*)&three_one_skew_D[n][2][0]) + 7) = packet->data[CMD_POSITION_PARAM + 56];

	*(((unsigned char*)&three_one_skew_D[n][2][1]) + 0) = packet->data[CMD_POSITION_PARAM + 57];
	*(((unsigned char*)&three_one_skew_D[n][2][1]) + 1) = packet->data[CMD_POSITION_PARAM + 58];
	*(((unsigned char*)&three_one_skew_D[n][2][1]) + 2) = packet->data[CMD_POSITION_PARAM + 59];
	*(((unsigned char*)&three_one_skew_D[n][2][1]) + 3) = packet->data[CMD_POSITION_PARAM + 60];
	*(((unsigned char*)&three_one_skew_D[n][2][1]) + 4) = packet->data[CMD_POSITION_PARAM + 61];
	*(((unsigned char*)&three_one_skew_D[n][2][1]) + 5) = packet->data[CMD_POSITION_PARAM + 62];
	*(((unsigned char*)&three_one_skew_D[n][2][1]) + 6) = packet->data[CMD_POSITION_PARAM + 63];
	*(((unsigned char*)&three_one_skew_D[n][2][1]) + 7) = packet->data[CMD_POSITION_PARAM + 64];

	*(((unsigned char*)&three_one_skew_D[n][2][2]) + 0) = packet->data[CMD_POSITION_PARAM + 65];
	*(((unsigned char*)&three_one_skew_D[n][2][2]) + 1) = packet->data[CMD_POSITION_PARAM + 66];
	*(((unsigned char*)&three_one_skew_D[n][2][2]) + 2) = packet->data[CMD_POSITION_PARAM + 67];
	*(((unsigned char*)&three_one_skew_D[n][2][2]) + 3) = packet->data[CMD_POSITION_PARAM + 68];
	*(((unsigned char*)&three_one_skew_D[n][2][2]) + 4) = packet->data[CMD_POSITION_PARAM + 69];
	*(((unsigned char*)&three_one_skew_D[n][2][2]) + 5) = packet->data[CMD_POSITION_PARAM + 70];
	*(((unsigned char*)&three_one_skew_D[n][2][2]) + 6) = packet->data[CMD_POSITION_PARAM + 71];
	*(((unsigned char*)&three_one_skew_D[n][2][2]) + 7) = packet->data[CMD_POSITION_PARAM + 72];

	*(((unsigned char*)&three_one_skew_D[n][3][0]) + 0) = packet->data[CMD_POSITION_PARAM + 73];
	*(((unsigned char*)&three_one_skew_D[n][3][0]) + 1) = packet->data[CMD_POSITION_PARAM + 74];
	*(((unsigned char*)&three_one_skew_D[n][3][0]) + 2) = packet->data[CMD_POSITION_PARAM + 75];
	*(((unsigned char*)&three_one_skew_D[n][3][0]) + 3) = packet->data[CMD_POSITION_PARAM + 76];
	*(((unsigned char*)&three_one_skew_D[n][3][0]) + 4) = packet->data[CMD_POSITION_PARAM + 77];
	*(((unsigned char*)&three_one_skew_D[n][3][0]) + 5) = packet->data[CMD_POSITION_PARAM + 78];
	*(((unsigned char*)&three_one_skew_D[n][3][0]) + 6) = packet->data[CMD_POSITION_PARAM + 79];
	*(((unsigned char*)&three_one_skew_D[n][3][0]) + 7) = packet->data[CMD_POSITION_PARAM + 80];

	*(((unsigned char*)&three_one_skew_D[n][3][1]) + 0) = packet->data[CMD_POSITION_PARAM + 81];
	*(((unsigned char*)&three_one_skew_D[n][3][1]) + 1) = packet->data[CMD_POSITION_PARAM + 82];
	*(((unsigned char*)&three_one_skew_D[n][3][1]) + 2) = packet->data[CMD_POSITION_PARAM + 83];
	*(((unsigned char*)&three_one_skew_D[n][3][1]) + 3) = packet->data[CMD_POSITION_PARAM + 84];
	*(((unsigned char*)&three_one_skew_D[n][3][1]) + 4) = packet->data[CMD_POSITION_PARAM + 85];
	*(((unsigned char*)&three_one_skew_D[n][3][1]) + 5) = packet->data[CMD_POSITION_PARAM + 86];
	*(((unsigned char*)&three_one_skew_D[n][3][1]) + 6) = packet->data[CMD_POSITION_PARAM + 87];
	*(((unsigned char*)&three_one_skew_D[n][3][1]) + 7) = packet->data[CMD_POSITION_PARAM + 88];

	*(((unsigned char*)&three_one_skew_D[n][3][2]) + 0) = packet->data[CMD_POSITION_PARAM + 89];
	*(((unsigned char*)&three_one_skew_D[n][3][2]) + 1) = packet->data[CMD_POSITION_PARAM + 90];
	*(((unsigned char*)&three_one_skew_D[n][3][2]) + 2) = packet->data[CMD_POSITION_PARAM + 91];
	*(((unsigned char*)&three_one_skew_D[n][3][2]) + 3) = packet->data[CMD_POSITION_PARAM + 92];
	*(((unsigned char*)&three_one_skew_D[n][3][2]) + 4) = packet->data[CMD_POSITION_PARAM + 93];
	*(((unsigned char*)&three_one_skew_D[n][3][2]) + 5) = packet->data[CMD_POSITION_PARAM + 94];
	*(((unsigned char*)&three_one_skew_D[n][3][2]) + 6) = packet->data[CMD_POSITION_PARAM + 95];
	*(((unsigned char*)&three_one_skew_D[n][3][2]) + 7) = packet->data[CMD_POSITION_PARAM + 96];

	return CMD_ERROR_NONE;

}
int		CMD_TASK(const HUPacket* packet)
{
	unsigned char param1 = packet->data[CMD_POSITION_PARAM];

	if(param1 & TASK_ID_MASK1_NSAS){	// NSAS
		debug_nsas_flg = 1;
	}else{
		debug_nsas_flg = 0;
	}

	if(param1 & TASK_ID_MASK1_GAS){		// GAS
		debug_gas_flg = 1;
	}else{
		debug_gas_flg = 0;
	}

	if(param1 & TASK_ID_MASK1_GPS){		// GPS
		debug_gps_flg = 1;
	}else{
		debug_gps_flg = 0;
	}

	if(param1 & TASK_ID_MASK1_GYRO){	// GYRO
		debug_gyro_flg = 1;
	}else{
		debug_gyro_flg = 0;
	}

	if(param1 & TASK_ID_MASK1_STT){		// STT
		debug_stt_flg = 1;
	}else{
		debug_stt_flg = 0;
	}

	if(param1 & TASK_ID_MASK2_RW){		// RW
		debug_rw_flg = 1;
	}else{
		debug_rw_flg = 0;
	}

	return CMD_ERROR_NONE;	
}

enum AOCS_MODE { NON_CONTROL, SUN_SPIN, ROUGH_SUN_POINTING, ROUGH_EARTH_POINTING, FINE_EARTH_POINTING, FINE_SUN_POINTING };

int		CMD_AOCS_MODE(const HUPacket* packet)
{
	AOCS_mode = packet->data[CMD_POSITION_PARAM];
  switch(AOCS_mode)
  {
  case NON_CONTROL:
	Printf("Non Control Mode\n");
	break;
  case SUN_SPIN:
    Printf("Sun Spin Mode\n");
    //switch_to_sun_spin();
    break;
  case ROUGH_SUN_POINTING:
    Printf("Rough Sun Pointing Mode\n");
    //switch_to_sun_pointing();
    break;
  case ROUGH_EARTH_POINTING:
    Printf("Rough Earth Pointing Mode\n");
    //switch_to_rough_earth_pointing();
    break;
  case FINE_EARTH_POINTING:
    Printf("Fine Earth Pointing Mode\n");
    //switch_to_fine_earth_pointing();
    break;
  case FINE_SUN_POINTING:
	Printf("Fine Sun Pointing Mode\n");
	break;
  default:
    Printf("Err: Unknown mode\n");
    break;
  }
	return CMD_ERROR_NONE;
}


void switch_to_sun_spin(void)
{
/*
  turn_on_all_nsas();
  CmdSend_PowerOn(GYRO);
*/
  CmdSend_PowerOn(GAS);
/*
  CmdSend_PowerOff(STT);
  CmdSend_PowerOff(GPSR);
  turn_off_all_rw();
*/
}

void switch_to_sun_pointing(void)
{
  turn_on_all_nsas();
  CmdSend_PowerOn(GYRO);
  CmdSend_PowerOn(GAS);
  turn_on_all_rw();

  CmdSend_PowerOff(STT);
  CmdSend_PowerOff(GPSR);
}

void switch_to_rough_earth_pointing(void)
{
  switch_to_sun_pointing();
}

void switch_to_fine_earth_pointing(void)
{
  CmdSend_PowerOn(STT);
  CmdSend_PowerOn(GPSR);
  CmdSend_PowerOn(GYRO);
  turn_on_all_rw();

  turn_off_all_nsas();
  CmdSend_PowerOff(GAS);
}

void turn_on_all_rw(void)
{
  CmdSend_PowerOn(RW1_ON);
  CmdSend_PowerOn(RW2_ON);
  CmdSend_PowerOn(RW3_ON);
}

void turn_off_all_rw(void)
{
  CmdSend_PowerOff(RW1_OFF);
  CmdSend_PowerOff(RW2_OFF);
  CmdSend_PowerOff(RW3_OFF);
}

void turn_on_all_nsas(void)
{
  CmdSend_PowerOn(NSAS1);
  CmdSend_PowerOn(NSAS2);
  CmdSend_PowerOn(NSAS3);
}

void turn_off_all_nsas(void)
{
  CmdSend_PowerOff(NSAS1);
  CmdSend_PowerOff(NSAS2);
  CmdSend_PowerOff(NSAS3);
}
