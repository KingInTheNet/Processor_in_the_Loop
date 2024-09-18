/**
 * @file MIPS.h
 * @brief MIPS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * MIPS(�C�I���G���W��)�C���^�[�t�F�[�X���W���[���́A�W���s�^�[�R�[�|���[�V������MIPS�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g�A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
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
 * @brief MIPS�̏����i�[����\���̂ł��B
 * 
 * MIPS1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  MIPS_init() �ɂ�菉�������Ďg�p���܂��B
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Super�N���X�̍\����*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422�N���X�̍\����*/
	
	unsigned char		tlm_count;	/**< @public @brief MIPS�����TLM�J�E���^���*/
	unsigned long long	time;	/**< @public @brief MIPS����̎������*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned : 4; /**< @public @brief ����bit*/
			unsigned mcu : 4; /**< @public @brief MCU���bit*/
		} bit;
	} mips_status; /**< @public @brief MIPS�̏��*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned : 4; /**< @public @brief ����bit*/
			unsigned indicator : 1; /**< @public @brief INDICATOR��ONOFF���bit(0:OFF, 1:ON)*/
			unsigned aps : 1; /**< @public @brief APS��ONOFF���bit(0:OFF, 1:ON)*/
			unsigned nps : 1; /**< @public @brief NPS��ONOFF���bit(0:OFF, 1:ON)*/
			unsigned sps : 1; /**< @public @brief SPS��ONOFF���bit(0:OFF, 1:ON)*/
		} bit;
	} hvps_status; /**< @public @brief HVPS��ONOFF���*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned : 4; /**< @public @brief ����bit*/
			unsigned mps : 1; /**< @public @brief MPS��ONOFF���bit(0:OFF, 1:ON)*/
			unsigned bv : 1; /**< @public @brief BV��ONOFF���bit(0:OFF, 1:ON)*/
			unsigned rv : 1; /**< @public @brief RV��ONOFF���bit(0:OFF, 1:ON)*/
			unsigned tv : 1; /**< @public @brief TV��ONOFF���bit(0:OFF, 1:ON)*/
		} bit;
	} valve_status; /**< @public @brief VALVE��ONOFF���*/
	
	unsigned short		ad00;	/**< @public @brief MPS�d�͏o�̓��j�^(0�`5V)*/
	unsigned short		ad01;	/**< @public @brief MPS���x���j�^(0�`5V)*/
	unsigned short		ad02;	/**< @public @brief SPS-V�o�̓��j�^(0�`5V)*/
	unsigned short		ad03;	/**< @public @brief SPS-I�o�̓��j�^(0�`5V)*/
	unsigned short		ad04;	/**< @public @brief NPS-V�o�̓��j�^(0�`5V)*/
	unsigned short		ad05;	/**< @public @brief NPS-I�o�̓��j�^(0�`5V)*/
	unsigned short		ad06;	/**< @public @brief APS-V�o�̓��j�^(0�`5V)*/
	unsigned short		ad07;	/**< @public @brief APS-I�o�̓��j�^(0�`5V)*/
	unsigned short		ad08;	/**< @public @brief HVPS���x���j�^(0�`5V)*/
	unsigned short		ad09;	/**< @public @brief LPS���̓Z���T�o�̓��j�^1(0�`5V)*/
	unsigned short		ad10;	/**< @public @brief LPS���̓Z���T�o�̓��j�^2(0�`5V)*/
	unsigned short		ad11;	/**< @public @brief HPS���̓Z���T�o�̓��j�^(0�`5V)*/
	unsigned short		ad12;	/**< @public @brief MCU��㉷�x���j�^(0�`5V)*/
	unsigned short		ad13;	/**< @public @brief �ሳ�^���N���x���j�^(0�`5V)*/
	unsigned short		ad14;	/**< @public @brief �����^���N���x���j�^(0�`5V)*/
	unsigned short		ad15;	/**< @public @brief ITU���x���j�^(0�`5V)*/
	
	unsigned int		total_current;	/**< @public @brief �d���ϕ��l*/
	
	unsigned long long	start_time;	/**< @public @brief ���ˊJ�n����*/
	unsigned long long	stop_time;	/**< @public @brief �������˒�~����*/
	unsigned char		lps_select;	/**< @public @brief �ሳ�Z���T�ؑ�*/
	unsigned short		rv_cont;	/**< @public @brief RV�Q�ƒl*/
	unsigned short		lp_max;		/**< @public @brief �ሳ�ő刳��*/
	unsigned char		rv_time;	/**< @public @brief RV�������*/
	unsigned char		lp_ready_time;	/**< @public @brief �ሳ���ҋ@����*/
	unsigned char		mps_on_stb_time;	/**< @public @brief MPS�I����������*/
	unsigned char		tv_open_stb_time;	/**< @public @brief TV�J����������*/
	unsigned char		hvps_on_ion;	/**< @public @brief ���Ύ�HVPS���p*/
	unsigned char		ion_check_time;	/**< @public @brief ���Ίm�F����*/
	unsigned char		ion_count_limit;	/**< @public @brief ���Ύ��s�񐔐���*/
	unsigned short		mps_temp_max;	/**< @public @brief MPS�ő剷�x*/
	unsigned short		hvps_temp_max;	/**< @public @brief HVPS�ő剷�x*/
	unsigned char		lps_check_time;	/**< @public @brief �ሳ�m�F����*/
	unsigned char		hvps_on_time1;	/**< @public @brief HVPS�g�p�J�n����1*/
	unsigned char		hvps_on_time2;	/**< @public @brief HVPS�g�p�J�n����2*/
	unsigned char		hvps_on_order;	/**< @public @brief HVPS�g�p����*/
	unsigned short		nps_voltage_ref;	/**< @public @brief NPS�d���Q�ƒl*/
	unsigned short		aps_current_ref;	/**< @public @brief APS�d���Q�ƒl*/
	unsigned short		aps_voltage_ref;	/**< @public @brief APS�d���Q�ƒl*/
	unsigned short		sps_current_ref;	/**< @public @brief SPS�d���Q�ƒl*/
	unsigned char		mips_on_count;	/**< @public @brief MIPS�N����*/
	unsigned char		mips_on_count_limit;	/**< @public @brief MIPS�N��������*/
	unsigned char		mips_auto;	/**< @public @brief ��������*/
	
	
	
	unsigned char		cmd_count;	/**< @private @brief MIPS�ւ�CMD�J�E���^*/
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
