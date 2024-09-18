/**
 * @file GAS.h
 * @brief GAS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * GAS�C���^�[�t�F�[�X���W���[���́A�e���e�N�j�J��TGA-330�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.08.24
 */

#ifndef	GAS_INCLUDE_
#define	GAS_INCLUDE_


#include "../../../IF_Wrapper/AA.h"
#include "../../Super/Driver_Super.h"


/**
 * @class GAS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends AA_CONFIG_STRUCT
 * @brief GAS�̏����i�[����\���̂ł��B
 * 
 * GAS1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  GAS_init() �ɂ�菉�������Ďg�p���܂��B
 */
// AA��float�ł͂Ȃ�short�Ŏ擾����悤�ɕύX���� by kkamiya 2013/11/15
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Super�N���X�̍\����*/
	AA_CONFIG_STRUCT	aa_config;	/**< @private @brief AA�N���X�̍\����*/
	short					x;	/**< @public @brief X���M���̓d���o�͒l*/
	short					y;	/**< @public @brief Y���M���̓d���o�͒l*/
	short					z;	/**< @public @brief Z���M���̓d���o�͒l*/
	short					ref;	/**< @public @brief Reference�M���̓d���o�͒l*/
	
	short					cycle_sum_x;	/**< @private @brief X���M���̓d���o�͒l���Z�p�ϐ�*/
	short					cycle_sum_y;	/**< @private @brief Y���M���̓d���o�͒l���Z�p�ϐ�*/
	short					cycle_sum_z;	/**< @private @brief Z���M���̓d���o�͒l���Z�p�ϐ�*/
	short					cycle_sum_ref;	/**< @private @brief Reference�M���̓d���o�͒l���Z�p�ϐ�*/
	int						cycle_cnt;	/**< @private @brief �擾�����J�E���^*/
}	GAS_STRUCT;


int GAS_init(GAS_STRUCT *my_gas, unsigned int ch_x, unsigned int ch_y, unsigned int ch_z, unsigned int ch_ref);
int GAS_cycle(GAS_STRUCT *my_gas);
int GAS_rec(GAS_STRUCT *my_gas);
int GAS_debug_message(GAS_STRUCT* my_gas);

#endif // GAS_INCLUDE_
