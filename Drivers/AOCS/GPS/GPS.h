/**
 * @file GPS.h
 * @brief GPS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * GPS�C���^�[�t�F�[�X���W���[���́AAxelSpace��AXELNAV-1�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g�A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.10.18
 */

#ifndef	GPS_INCLUDE_
#define	GPS_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @brief UTC���i�[���邽�߂̍\���̂ł��B
 */
typedef struct {
	unsigned char year;	/**< @public @brief �N(����̉�2��)(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char month;	/**< @public @brief ��(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char day;	/**< @public @brief ��(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char hour;	/**< @public @brief ����(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char min;	/**< @public @brief ��(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char sec;	/**< @public @brief �b(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
} UTC_STRUCT;


/**
 * @class GPS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief GPS�̏����i�[����\���̂ł��B
 * 
 * GPS1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  GPS_init() �ɂ�菉�������Ďg�p���܂��B
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Super�N���X�̍\����*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422�N���X�̍\����*/
	int					latitude;	/**< @public @brief �ܓx(��܂͕��̐��ŕ\��)(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	int					longitude;	/**< @public @brief �o�x(���o�͕��̐��ŕ\��)(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned int		altitude;	/**< @public @brief ���x(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	long long			vector_x;	/**< @public @brief �ʒu�x�N�g��x(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	long long			vector_y;	/**< @public @brief �ʒu�x�N�g��y(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	long long			vector_z;	/**< @public @brief �ʒu�x�N�g��z(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned short		speed;	/**< @public @brief ���x(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned short		direction;	/**< @public @brief ����(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned short		pdop;	/**< @public @brief PDOP(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	UTC_STRUCT			utc;	/**< @public @brief UTC*/
	unsigned char		alive_sat;	/**< @public @brief ����ȉq����(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		visible_sat;	/**< @public @brief ���q����(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		delay_time;	/**< @public @brief ���ʒx������(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	unsigned char		pps;	/**< @public @brief PPS�␳(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
	union{
		unsigned char		byte;
		struct{
			unsigned : 2; /**< @public @brief ����bit(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
			unsigned csf_flag : 1; /**< @public @brief CSF�t���O(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
			unsigned two_sat_positioning_flag : 1; /**< @public @brief 2�q�����ʃt���O(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
			unsigned : 1; /**< @public @brief ����bit(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
			unsigned three_dim_positioning_flag : 1; /**< @public @brief 3D���ʃt���O(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
			unsigned two_dim_positioning_flag : 1; /**< @public @brief 2D���ʃt���O(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
			unsigned positioning_status : 1; /**< @public @brief ���ʃX�e�[�^�X(AXELNAV-1���[�U�[�Y�}�j���A���Q��)*/
		} bit;
	} status1;	/**< @public @brief �e��X�e�[�^�X(AXELNAV-1���[�U�[�Y�}�j���A���Q��, 97�o�C�g��)*/
}	GPS_STRUCT;


int GPS_init(GPS_STRUCT *my_gps, unsigned char ch);
int GPS_cycle(GPS_STRUCT *my_gps);
int GPS_rec(GPS_STRUCT *my_gps);
int GPS_debug_message(GPS_STRUCT* my_gps);
int GPS_Conf(GPS_STRUCT *my_gps);

#endif // GPS_INCLUDE_
