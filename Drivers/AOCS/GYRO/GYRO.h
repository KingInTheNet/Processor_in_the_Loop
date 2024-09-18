/**
 * @file GYRO.h
 * @brief GYRO�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * GYRO�C���^�[�t�F�[�X���W���[���́A�����쐸�@�������FOG IRU TA7584�Ƃ̃C���^�[�t�F�[�X���������A
 * �f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2013.10.03
 */

#ifndef	GYRO_INCLUDE_
#define	GYRO_INCLUDE_


#include "../../../IF_Wrapper/AA.h"
#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @class GYRO_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @extends AA_CONFIG_STRUCT
 * @brief GYRO�̏����i�[����\���̂ł��B
 * 
 * GYRO1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  GYRO_init() �ɂ�菉�������Ďg�p���܂��B
 */
// AA��float�ł͂Ȃ�short�Ŏ擾����悤�ɕύX���� by kkamiya 2013/11/15
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Super�N���X�̍\����*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422�N���X�̍\����*/
	AA_CONFIG_STRUCT	aa_config;	/**< @private @brief RS422�N���X�̍\����*/
	unsigned int		counter;	/**< @public @brief GYRO����̃J�E���^(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
	union{
		unsigned char		byte[2];
		struct{
			unsigned error : 1; /**< @public @brief �G���[(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned : 3; /**< @public @brief ����bit(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned action_mode : 4; /**< @public @brief ���샂�[�h(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned angular_vel_detection_range_x : 1;	 /**< @public @brief x���p���x���o�͈�(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned angular_vel_detection_range_y : 1;	 /**< @public @brief y���p���x���o�͈�(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned angular_vel_detection_range_z : 1;	 /**< @public @brief z���p���x���o�͈�(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned : 1;	/**< @public @brief ����bit(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned abnormality_x : 1;	/**< @public @brief x��FOG�ُ�(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned abnormality_y : 1;	/**< @public @brief y��FOG�ُ�(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned abnormality_z : 1;	/**< @public @brief z��FOG�ُ�(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
			unsigned abnormality_tempe : 1;	/**< @public @brief ���x�Z���T�ُ�(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
		} bit;
	} status;	/**< @public @brief �X�e�[�^�X(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
	int				del_x;	/**< @public @brief �p���xx(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
	int				del_y;	/**< @public @brief �p���xy(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
	int				del_z;	/**< @public @brief �p���xz(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
	short				current_x;	/**< @public @brief x��SLD�d��(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
	short				current_y;	/**< @public @brief y��SLD�d��(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
	short				current_z;	/**< @public @brief z��SLD�d��(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
	short				tempe;	/**< @public @brief ���x(MEMS/IRU���[�U�[�Y�}�j���A���Q��)*/
	short				del_x_aa;	/**< @public @brief �p���xx(AA�[�q�Ŏ擾���ꂽ�d���l)*/
	short				del_y_aa;	/**< @public @brief �p���xy(AA�[�q�Ŏ擾���ꂽ�d���l)*/
	short				del_z_aa;	/**< @public @brief �p���xz(AA�[�q�Ŏ擾���ꂽ�d���l)*/
}	GYRO_STRUCT;


int GYRO_init(GYRO_STRUCT* my_gyro, unsigned char ch, unsigned char aa_ch_x, unsigned char aa_ch_y, unsigned char aa_ch_z);
int GYRO_rec(GYRO_STRUCT *my_gyro);
int GYRO_cycle(GYRO_STRUCT *my_gyro);
int GYRO_debug_message(GYRO_STRUCT* my_gyro);

#endif // GYRO_INCLUDE_
