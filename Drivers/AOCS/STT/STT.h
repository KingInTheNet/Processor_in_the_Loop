/**
 * @file STT.h
 * @brief STT�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * STT�C���^�[�t�F�[�X���W���[���́AAxelSpace��AXELSTAR-2�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g�A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.11.01
 */

#ifndef	STT_INCLUDE_
#define	STT_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../../IF_Wrapper/DC.h"
#include "../../Super/Driver_Super.h"


/**
 * @brief �P�����o�����i�[���邽�߂̍\���̂ł��B
 */
typedef struct {
	unsigned int	hipparcos_id;	/**< @public @brief Hipparcos ID(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	unsigned int	luminance;	/**< @public @brief �P�x(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	double			tan_azimuth;	/**< @public @brief tan���ʊp(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	double			tan_elevation;	/**< @public @brief tan�p(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
} STAR_INFO_STRUCT;


/**
 * @class STT_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @extends DC_CONFIG_STRUCT
 * @brief STT�̏����i�[����\���̂ł��B
 * 
 * STT1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  STT_init() �ɂ�菉�������Ďg�p���܂��B
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Super�N���X�̍\����*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422�N���X�̍\����*/
	DC_CONFIG_STRUCT	dc_config;	/**< @private @brief DC�N���X�̍\����*/
	unsigned short		capture_id; /**< @public @brief �B�e���ƂɃC���N�������g�����J�E���^(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	union{
		unsigned char		byte[2];
		struct{
			unsigned complexity : 8; /**< @public @brief �v�Z�̕��G��(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
			unsigned : 2; /**< @public @brief ����bit(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
			unsigned master_data : 1; /**< @public @brief �}�X�^�̃f�[�^(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
			unsigned slave_data : 1; /**< @public @brief �X���[�u�̃f�[�^(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
			unsigned status : 4; /**< @public @brief �X�e�[�^�X(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
		} bit;
	} integration_state; /**< @public @brief �p�������X�e�[�^�X(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	double				attitude[4]; /**< @public @brief �������ꂽ����p��(quaternion)(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	double				error_covariance_matrix[3][3]; /**< @public @brief �������ꂽ�덷�����U�s��(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	float				master_imager_temperature; /**< @public @brief �}�X�^�̃C���[�W�Z���T���x(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		master_detected_star_count; /**< @public @brief �}�X�^�̌��o�P����(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	STAR_INFO_STRUCT	master_star_info[6]; /**< @public @brief �}�X�^�̌��o�P�����(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	union{
		unsigned char		byte[4];
		struct{
			unsigned : 12; /**< @public @brief ����bit(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
			unsigned reliability : 8; /**< @public @brief �o�͎p���̌v�Z�̐M���x(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
			unsigned nearness : 7; /**< @public @brief �ߎ��p������́u�߂��v(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
			unsigned algorithm : 1; /**< @public @brief �p������Ɏg�p�����A���S���Y��(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
			unsigned status : 4; /**< @public @brief �X�e�[�^�X(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
		} bit;
	} master_estimation_status; /**< @public @brief �}�X�^�̎p������X�e�[�^�X(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
}	STT_STRUCT;

/**
 * @brief �P�����o���(Get Detected Star Info �R�}���h�p)���i�[���邽�߂̍\���̂ł��B
 */
typedef struct {
	unsigned char	read_star_count;	/**< @public @brief �ǂݏo������(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	unsigned short	index;	/**< @public @brief ���̉�ʓ�index(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	unsigned char	flag;	/**< @public @brief ���̏�ԃt���O(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	unsigned int	hipparcos_id;	/**< @public @brief ����Hipparcos ID(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	unsigned short	area;	/**< @public @brief ���̖ʐ�(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	unsigned int	luminance;	/**< @public @brief ���̋P�x(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	double			tan_azimuth;	/**< @public @brief ����tan���ʊp(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	double			tan_elevation;	/**< @public @brief ����tan�p(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
} GET_DETECTED_STAR_INFO_COMMAND_STRUCT;

/**
 * @brief �p������X�e�[�^�X(Get Estimation Status �R�}���h�p)���i�[���邽�߂̍\���̂ł��B
 */
typedef union{
	unsigned char		byte[4];
	struct{
		unsigned : 12; /**< @public @brief ����bit*/
		unsigned confidence : 8; /**< @public @brief �v�Z�̐M���x(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
		unsigned nearness : 7; /**< @public @brief �ݒ肵���ߎ��p������́u�߂��v��\���w�W(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
		unsigned algorithm : 1; /**< @public @brief �p������Ɏg�p�����A���S���Y��(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
		unsigned status : 4; /**< @public @brief �X�e�[�^�X(AXELSTAR-2���[�U�[�Y�}�j���A���Q��)*/
	} bit;
} GET_ESTIMATION_STATUS_UNION;


int STT_init(STT_STRUCT *my_stt, unsigned char ch, unsigned short up_enable_bit);
int STT_cycle(STT_STRUCT *my_stt);
int STT_rec(STT_STRUCT *my_stt);
int STT_debug_message(STT_STRUCT* my_stt);
int STT_auto_mode(STT_STRUCT *my_stt);
int STT_stop(STT_STRUCT* my_stt);
int STT_Up_Enable_Power_Down(STT_STRUCT *my_stt);
int STT_Up_Enable_Idle(STT_STRUCT *my_stt);
int STT_Get_Temperature(STT_STRUCT *my_stt, float *image_sensor_board, float *fpga, float *image_sensor);
int STT_Change_Power_State_Capture(STT_STRUCT *my_stt);
int STT_Change_Power_State_Idle(STT_STRUCT *my_stt);
int STT_Get_Power_State(STT_STRUCT *my_stt, unsigned char *state);
int STT_Get_Exposure_Time(STT_STRUCT *my_stt, unsigned short *get_time);
int STT_Set_Exposure_Time(STT_STRUCT *my_stt, unsigned short *get_time, unsigned short set_time);
int STT_System_Reset(STT_STRUCT *my_stt);
int STT_Capture_Only(STT_STRUCT *my_stt);
int STT_PostProc_Only(STT_STRUCT *my_stt);
int STT_Capture_And_PostProc(STT_STRUCT *my_stt);
int STT_Get_Detected_Star_Count(STT_STRUCT *my_stt, unsigned char *star_count);
int STT_Get_Detected_Star_Info(STT_STRUCT *my_stt, unsigned short read_index, unsigned char count, GET_DETECTED_STAR_INFO_COMMAND_STRUCT *info_data, unsigned int size);
int STT_Set_Approximate_Attitude(STT_STRUCT *my_stt, double quaternion1, double quaternion2, double quaternion3, double quaternion4);
int STT_Get_Estimation_Status(STT_STRUCT *my_stt, GET_ESTIMATION_STATUS_UNION *st_data);
int STT_Get_Attitude(STT_STRUCT *my_stt, double *quaternion1, double *quaternion2, double *quaternion3, double *quaternion4);
int STT_Get_Error_Covariance_Matrix(STT_STRUCT *my_stt, double *ecm00, double *ecm01, double *ecm02, double *ecm11, double *ecm12, double *ecm22);
int STT_Change_Output_Mode(STT_STRUCT *my_stt, unsigned char *state);
int STT_Get_SEU_Error_Correction_Count(STT_STRUCT *my_stt, unsigned short *seu_error_count);
int STT_Get_Error(STT_STRUCT *my_stt, unsigned char *error);
int STT_Clear_Error(STT_STRUCT *my_stt, unsigned char *error);
int STT_Get_Output_Interval(STT_STRUCT *my_stt, unsigned char *interval);
int STT_Set_Output_Interval(STT_STRUCT *my_stt, unsigned char set_interval, unsigned char *interval);
int STT_Start_Output(STT_STRUCT *my_stt);
int STT_Stop_Output(STT_STRUCT *my_stt);

#endif // STT_INCLUDE_
