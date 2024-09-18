#ifndef	CMD_ACTION_AOBC_INCLUDE_
#define	CMD_ACTION_AOBC_INCLUDE_

//tentative
#include "HodoUniPacket_simple_tentative.h"

#define		MTQ_ID_MASK1			0x01
#define		MTQ_ID_MASK2			0x02
#define		MTQ_ID_MASK3			0x04

#define		TASK_ID_MASK1_NSAS			0x01
#define		TASK_ID_MASK1_GAS			0x02
#define		TASK_ID_MASK1_GPS			0x04
#define		TASK_ID_MASK1_GYRO			0x08
#define		TASK_ID_MASK1_STT			0x10
#define		TASK_ID_MASK2_RW			0x20


// ‚±‚Ì’è?”ŒQ‚ÍMOBC‚Æ“¯Šú‚ð‚Æ‚é•K—v‚ª‚ ‚é?B
// •Ï?X‚Ì?Û‚É‚Í’?ˆÓ‚·‚é‚±‚Æ?B
enum { STT, DEMO_B, GYRO, X_TX, SAP_HRM,
		DCDC_SNS, DCDC_MTQ, DCDC_RW, 
		GPSR, NSAS1, NSAS2, NSAS3,
        NSAS4, NSAS5, NSAS6, GAS, RESERVE, 
		MTQ_X_PLUS, MTQ_X_MINUS, MTQ_X_OFF, 
		MTQ_Y_PLUS, MTQ_Y_MINUS, MTQ_Y_OFF, 
		MTQ_Z_PLUS, MTQ_Z_MINUS, MTQ_Z_OFF, 
		RW1_ON, RW1_SAFE, RW1_OFF, 
		RW2_ON, RW2_SAFE, RW2_OFF, 
		RW3_ON, RW3_SAFE, RW3_OFF, 
		RW4_ON, RW4_SAFE, RW4_OFF, 
		HTR3, HTR4, HTR5, HTR6, HTR7};


int		CMD_MTQ(const HUPacket* packet);
int		CMD_RW(const HUPacket* packet);
int		CMD_RW_PARAMETER_REQUEST1(const HUPacket* packet);
int		CMD_RW_PARAMETER_REQUEST2(const HUPacket* packet);
int		CMD_RW_PARAMETER_CONFIG1(const HUPacket* packet);
int		CMD_RW_PARAMETER_CONFIG2(const HUPacket* packet);
int		CMD_NSAS_GAIN(const HUPacket* packet);
int		CMD_RCS_INITIALIZE_COMMAND(const HUPacket* packet);
int		CMD_RCS_INJECTION_PREPARATION(const HUPacket* packet);
int		CMD_RCS_INJECTION_START(const HUPacket* packet);
int		CMD_RCS_INJECTION_STOP(const HUPacket* packet);
int		CMD_STT_ENABLE_CONTROL(const HUPacket* packet);
int		CMD_STT_AUTO_MODE(const HUPacket* packet);
int		CMD_STT_STOP(const HUPacket* packet);
int		CMD_STT_GET_TEMPERATURE(const HUPacket* packet);
int		CMD_STT_CHANGE_POWER_STATE_CAPTURE(const HUPacket* packet);
int		CMD_STT_CHANGE_POWER_STATE_IDLE(const HUPacket* packet);
int		CMD_STT_GET_POWER_STATE(const HUPacket* packet);
int		CMD_STT_GET_EXPOSURE_TIME(const HUPacket* packet);
int		CMD_STT_SET_EXPOSURE_TIME(const HUPacket* packet);
int		CMD_STT_SYSTEM_RESET(const HUPacket* packet);
int		CMD_STT_CAPTURE_ONLY(const HUPacket* packet);
int		CMD_STT_POSTPROC_ONLY(const HUPacket* packet);
int		CMD_STT_CAPTURE_AND_POSTPROC(const HUPacket* packet);
int		CMD_STT_GET_DETECTED_STAR_COUNT(const HUPacket* packet);
int		CMD_STT_GET_DETECTED_STAR_INFO(const HUPacket* packet);
int		CMD_STT_SET_APPROXIMATE_ATTITUDE(const HUPacket* packet);
int		CMD_STT_GET_ESTIMATION_STATUS(const HUPacket* packet);
int		CMD_STT_GET_ATTITUDE(const HUPacket* packet);
int		CMD_STT_GET_COVARIANCE_MATRIX(const HUPacket* packet);
int		CMD_STT_CHANGE_OUTPUT_MODE(const HUPacket* packet);
int		CMD_STT_GET_SEU_ERROR_CORRECTION_COUNT(const HUPacket* packet);
int		CMD_STT_GET_ERROR(const HUPacket* packet);
int		CMD_STT_CLEAR_ERROR(const HUPacket* packet);
int		CMD_STT_GET_OUTPUT_INTERVAL(const HUPacket* packet);
int		CMD_STT_SET_OUTPUT_INTERVAL(const HUPacket* packet);
int		CMD_STT_START_OUTPUT(const HUPacket* packet);
int		CMD_STT_STOP_OUTPUT(const HUPacket* packet);
int		CMD_MIPS_HVPS(const HUPacket* packet);
int		CMD_MIPS_TV_TIMER(const HUPacket* packet);
int		CMD_MIPS_TV(const HUPacket* packet);
int		CMD_MIPS_RV(const HUPacket* packet);

int		CMD_SET_CONT_GAIN(const HUPacket* packet);
int		CMD_SET_INERTIA(const HUPacket* packet);
int		CMD_SET_SPIN_PARAM(const HUPacket* packet);
int		CMD_SET_RW_PARAM(const HUPacket* packet);
int		CMD_SET_RW_LIMIT(const HUPacket* packet);
int		CMD_SET_DCM(const HUPacket* packet);
int		CMD_SET_MTQ_POL(const HUPacket* packet);
int		CMD_SET_SKEW_PARAM(const HUPacket* packet);
int		CMD_SET_D_MATRIX(const HUPacket* packet);

int		CMD_TASK(const HUPacket* packet);
int		CMD_AOCS_MODE(const HUPacket* packet);

void switch_to_sun_spin(void);
void switch_to_sun_pointing(void);
void switch_to_rough_earth_pointing(void);
void switch_to_fine_earth_pointing(void);

void turn_on_all_rw(void);
void turn_off_all_rw(void);
void turn_on_all_nsas(void);
void turn_off_all_nsas(void);


extern	unsigned short rw1_current_gain, rw2_current_gain, rw3_current_gain, rw4_current_gain;
extern	unsigned short rw1_current_integ_gain, rw2_current_integ_gain, rw3_current_integ_gain, rw4_current_integ_gain;
extern	unsigned short rw1_current_limit, rw2_current_limit, rw3_current_limit, rw4_current_limit;
extern	unsigned short rw1_temperature_gain, rw2_temperature_gain, rw3_temperature_gain, rw4_temperature_gain;
extern	unsigned short rw1_temperature_offset, rw2_temperature_offset, rw3_temperature_offset, rw4_temperature_offset;
extern	unsigned short rw1_system_config, rw2_system_config, rw3_system_config, rw4_system_config;
extern	float stt1_image_sensor_board;
extern	float stt1_fpga;
extern	float stt1_image_sensor;
extern	unsigned char stt1_power_state;
extern	unsigned short stt1_get_time;
extern	unsigned short stt1_set_time;
extern	unsigned char stt1_star_count;
extern	GET_DETECTED_STAR_INFO_COMMAND_STRUCT stt1_info_data[64];
extern	double stt1_quaternion1;
extern	double stt1_quaternion2;
extern	double stt1_quaternion3;
extern	double stt1_quaternion4;
extern	GET_ESTIMATION_STATUS_UNION stt1_st_data;
extern	double stt1_ecm00;
extern	double stt1_ecm01;
extern	double stt1_ecm02;
extern	double stt1_ecm11;
extern	double stt1_ecm12;
extern	double stt1_ecm22;
extern	unsigned char stt1_output_mode;
extern	unsigned short stt1_seu_error_count;
extern	unsigned char stt1_error;
extern	unsigned char stt1_interval;

#endif // CMD_ACTION_AOBC_INCLUDE_
