/**
 * @file RW.h
 * @brief RW�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * RW�C���^�[�t�F�[�X���W���[���́A�����쐸�@�������TS4431�Ƃ̃C���^�[�t�F�[�X���������A
 * �f�[�^�擾�E�R�}���h���M���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.09.17
 */

#ifndef	RW_INCLUDE_
#define	RW_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @brief RW�̃R�}���h���M�w�ߒl���i�[���邽�߂̍\���̂ł��B
 */
typedef	struct {
	unsigned char	mess_no;	/**< @public @brief ���b�Z�[�WNo.(RW�ʐM�d�l���Q��)*/
	union{
		unsigned char		byte;
		struct{
			unsigned : 5; /**< @public @brief ����bit(RW�ʐM�d�l���Q��)*/
			unsigned open_close_loop : 1; /**< @public @brief �I�[�v��/�N���[�Y���[�v(RW�ʐM�d�l���Q��)*/
			unsigned torque_output_direction : 1; /**< @public @brief �g���N�o�͕���(RW�ʐM�d�l���Q��)*/
			unsigned motor_drive : 1; /**< @public @brief ���[�^�쓮(RW�ʐM�d�l���Q��)*/
		} bit;
	} comm1; /**< @public @brief �R�}���h1(RW�ʐM�d�l���Q��)*/
	unsigned short	comm2;	/**< @public @brief �R�}���h2(�d���l(�w�ߐ��l))*/
	unsigned short	comm3;	/**< @public @brief �R�}���h3(RW�ʐM�d�l���Q��)*/
}	RW_TX_COMM_STRUCT;


/**
 * @brief RW�̎�M�X�e�[�^�X���i�[���邽�߂̍\���̂ł��B
 */
typedef	struct {
	unsigned char	mess_no;	/**< @public @brief ���b�Z�[�WNo.(RW�ʐM�d�l���Q��)*/
	union{
		unsigned char		byte;
		struct{
			unsigned : 5; /**< @public @brief ����bit(RW�ʐM�d�l���Q��)*/
			unsigned rotation_direction : 1; /**< @public @brief ���[�^��]����(RW�ʐM�d�l���Q��)*/
			unsigned torque_output_direction : 1; /**< @public @brief �g���N�o�͕���(RW�ʐM�d�l���Q��)*/
			unsigned motor_drive : 1; /**< @public @brief ���[�^�쓮(RW�ʐM�d�l���Q��)*/
		} bit;
	} sts1;	/**< @public @brief �X�e�[�^�X1(RW�ʐM�d�l���Q��)*/
	union{
		unsigned char		byte;
		struct{
			unsigned : 2; /**< @public @brief ����bit(RW�ʐM�d�l���Q��)*/
			unsigned overcurrent: 1; /**< @public @brief �ߓd���ُ�(RW�ʐM�d�l���Q��)*/
			unsigned sensor_failed : 1; /**< @public @brief �Z���T�ُ�(RW�ʐM�d�l���Q��)*/
			unsigned overvoltage : 1; /**< @public @brief �ߓd���ُ�(RW�ʐM�d�l���Q��)*/
			unsigned command_failed : 1; /**< @public @brief �R�}���h�͈͊O(RW�ʐM�d�l���Q��)*/
			unsigned bcc_failed : 1; /**< @public @brief BCC�ُ�(RW�ʐM�d�l���Q��)*/
			unsigned command_nothing : 1; /**< @public @brief �R�}���h����(RW�ʐM�d�l���Q��)*/
		} bit;
	} sts2;	/**< @public @brief �X�e�[�^�X2(RW�ʐM�d�l���Q��)*/
	unsigned short	sts3;	/**< @public @brief �X�e�[�^�X3(RW�ʐM�d�l���Q��)*/
	short			sts4;	/**< @public @brief �X�e�[�^�X4(RW�ʐM�d�l���Q��)*/
	short			sts5;	/**< @public @brief �X�e�[�^�X5(RW�ʐM�d�l���Q��)*/
}	RW_RX_STS_STRUCT;


/**
 * @class RW_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief RW�̏����i�[����\���̂ł��B
 * 
 * RW1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  RW_init() �ɂ�菉�������Ďg�p���܂��B
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Super�N���X�̍\����*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422�N���X�̍\����*/
	RW_TX_COMM_STRUCT	rw_tx_comm;	/**< @public @brief �R�}���h���M�w�ߒl�i�[�p�\����*/
	RW_RX_STS_STRUCT	rw_rx_sts;	/**< @public @brief ��M�X�e�[�^�X�i�[�p�\����*/
	unsigned char		param_req_mess_no;	/**< @private @brief �p�����[�^�v���p���b�Z�[�W�i���o�[*/
	unsigned char		param_cfg_mess_no;	/**< @private @brief �p�����[�^�ݒ�p���b�Z�[�W�i���o�[*/
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
