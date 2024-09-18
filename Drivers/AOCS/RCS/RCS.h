/**
 * @file RCS.h
 * @brief RCS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * RCS�C���^�[�t�F�[�X���W���[���́A��s��RCS�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g�A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
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
 * @brief RCS�̏����i�[����\���̂ł��B
 * 
 * RCS1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  RCS_init() �ɂ�菉�������Ďg�p���܂��B
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Super�N���X�̍\����*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422�N���X�̍\����*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned vo_au : 2; /**< @public @brief VO-AU�t���O���e(0:Close, 1:Open_Action, 2:Open)*/
			unsigned vo_ad : 2; /**< @public @brief VO-AD�t���O���e(0:Close, 1:Open_Action, 2:Open)*/
			unsigned vo_bu : 2; /**< @public @brief VO-BU�t���O���e(0:Close, 1:Open_Action, 2:Open)*/
			unsigned vo_bd : 2; /**< @public @brief VO-BD�t���O���e(0:Close, 1:Open_Action, 2:Open)*/
		} bit;
	} flag; /**< @public @brief �t���O���e*/
	
	union{
		unsigned char	byte;
		struct{
			unsigned vo_au : 1; /**< @public @brief VO-AU�s�����(0:Close, 1:Open)*/
			unsigned vo_ad : 1; /**< @public @brief VO-AD�s�����(0:Close, 1:Open)*/
			unsigned vo_bu : 1; /**< @public @brief VO-BU�s�����(0:Close, 1:Open)*/
			unsigned vo_bd : 1; /**< @public @brief VO-BD�s�����(0:Close, 1:Open)*/
			unsigned flag_12v : 1; /**< @public @brief 12V�n�t���O���e(0:OFF, 1:ON)*/
			unsigned pin_12v : 1; /**< @public @brief 12V�n�s�����(0:OFF, 1:ON)*/
			unsigned mode : 2; /**< @public @brief ���[�h(0�`3:L0�`L3)*/
		} bit;
	} status; /**< @public @brief �X�e�[�^�X���*/
	
	unsigned char		last_cmd;	/**< @public @brief ���O�̃R�}���h���i�[����*/
	unsigned char		ack;	/**< @public @brief �e��ACK���̓G���[�ԍ����i�[����*/
	
	unsigned short		tt0;	/**< @public @brief �^���N����x*/
	unsigned short		tt1;	/**< @public @brief �^���N���Ή��x*/
	unsigned short		tc0;	/**< @public @brief �X���X�^������x*/
	unsigned short		tc1;	/**< @public @brief �X���X�^�����Ή��x*/
	unsigned short		pt;		/**< @public @brief �^���N����*/
	unsigned short		pc;		/**< @public @brief �X���X�^����*/
	unsigned short		i_pt;	/**< @public @brief ���͌vPT�d��*/
	unsigned short		i_pc;	/**< @public @brief ���͌vPC�d��*/
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
