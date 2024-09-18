/**
 * @file AD590.h
 * @brief AD590�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * AD590�C���^�[�t�F�[�X���W���[���́AAnalog Devices��AD590�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2013.10.24
 */

#ifndef AD590_INCLUDE_
#define AD590_INCLUDE_


#define		AD590_NUMBER	16

#include "../../../IF_Wrapper/PA.h"
#include "../../Super/Driver_Super.h"



/**
 * @class AD590_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends PA_CONFIG_STRUCT
 * @brief AD590�̏����i�[����\���̂ł��B
 * 
 *  AD590_init() �ɂ�菉�������Ďg�p���܂��B
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Super�N���X�̍\����*/
	PA_CONFIG_STRUCT	pa_config;	/**< @private @brief PA�N���X�̍\����*/
	short					tempe[AD590_NUMBER];	/**< @public @brief AD590�̉��xA/D�l*/
}	AD590_STRUCT;


int AD590_init(AD590_STRUCT *my_ad590);
int AD590_cycle(AD590_STRUCT *my_ad590);
int AD590_rec(AD590_STRUCT *my_ad590);
int AD590_debug_message(AD590_STRUCT* my_ad590);

#endif // AD590_INCLUDE_
