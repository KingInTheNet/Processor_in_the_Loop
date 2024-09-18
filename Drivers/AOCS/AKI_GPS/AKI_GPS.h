/**
 * @file AKI_GPS.h
 * @brief �H��GPS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * AKI_GPS�C���^�[�t�F�[�X���W���[���́A�H��GPS�Ƃ̃C���^�[�t�F�[�X���������A
 * �f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.10.04
 */

#ifndef	AKI_GPS_INCLUDE_
#define	AKI_GPS_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../Super/Driver_Super.h"


/**
 * @class AKI_GPS_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief �H��GPS�̏����i�[����\���̂ł��B
 * 
 * AKI_GPS1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  AKI_GPS_init() �ɂ�菉�������Ďg�p���܂��B
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_SUPER�N���X�̍\����*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422�N���X�̍\����*/
	double			utc;			/**< @public @brief UTC*/
	double 			latitude;		/**< @public @brief �ܓx*/
	double 			longitude;		/**< @public @brief �o�x*/
	unsigned char	p_fix;			/**< @public @brief Position fix*/
	unsigned char	visible_sat;	/**< @public @brief ���q����*/
	double			hdop;			/**< @public @brief Horizontal dilution of precision*/
	double			antenna_height;	/**< @public @brief Antenna height above/below mean sea level*/
	double			geoidal_height;	/**< @public @brief Geoidal height,*/
}	AKI_GPS_STRUCT;


int AKI_GPS_init(AKI_GPS_STRUCT *my_aki_gps, unsigned char ch);
int AKI_GPS_cycle(AKI_GPS_STRUCT *my_aki_gps);
int AKI_GPS_rec(AKI_GPS_STRUCT *my_aki_gps);
int AKI_GPS_debug_message(AKI_GPS_STRUCT* my_aki_gps);

#endif // AKI_GPS_INCLUDE_
