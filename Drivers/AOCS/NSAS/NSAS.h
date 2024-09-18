/**
 * @file NSAS.h
 * @brief NSAS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * NSAS�C���^�[�t�F�[�X���W���[���́AAxelSpace��AxelSun�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g�A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.08.24
 */

#ifndef	MSAS_INCLUDE_
#define	MSAS_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @class NSAS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief NSAS�̏����i�[����\���̂ł��B
 * 
 * NSAS1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  NSAS_init() �ɂ�菉�������Ďg�p���܂��B
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Super�N���X�̍\����*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422�N���X�̍\����*/
	unsigned char		error;	/**< @public @brief Error Code(AXELSUN-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		id;	/**< @public @brief �ŗLID(AXELSUN-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		gain_flag;	/**< @public @brief �Q�C���R���g���[�����[�h��ON/OFF(AXELSUN-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		sun_flag;	/**< @public @brief ���z�����˔���(AXELSUN-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		gain;	/**< @public @brief �Q�C��(AXELSUN-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		tempe;	/**< @public @brief ���x(AXELSUN-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		x;	/**< @public @brief �p�xx(AXELSUN-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		y;	/**< @public @brief �p�xy(AXELSUN-1���[�U�[�Y�}�j���A���Q��)*/
}	NSAS_STRUCT;


int NSAS_init(NSAS_STRUCT *my_nsas, unsigned char ch);
void Debug_NSAS_gain_set(void);
int NSAS_cycle(NSAS_STRUCT *my_nsas);
int NSAS_rec(NSAS_STRUCT *my_nsas);
int NSAS_debug_message(NSAS_STRUCT* my_nsas);
int NSAS_gain(NSAS_STRUCT *my_nsas, unsigned char ope, unsigned char gain);

#endif // MSAS_INCLUDE_
