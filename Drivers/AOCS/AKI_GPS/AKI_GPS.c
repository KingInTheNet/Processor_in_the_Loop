/**
 * @file AKI_GPS.c
 * @brief �H��GPS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * AKI_GPS�C���^�[�t�F�[�X���W���[���́A�H��GPS�Ƃ̃C���^�[�t�F�[�X���������A
 * �f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.10.04
 */

#include <stdlib.h>
#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "AKI_GPS.h"

//#define	AKI_GPS_DEBUG


int				AKI_GPS_Data_Conv(AKI_GPS_STRUCT *my_aki_gps);


#define AKI_GPS_RX_FRAME_SIZE			-1	/**< @brief ��M�t���[���̒���*/

static unsigned char	aki_gps_rx_header[7] = {'$', 'G', 'P', 'G', 'G', 'A', ','};	/**< @brief ��M�t���[���̃w�b�_*/
static unsigned char	aki_gps_rx_footer[2] = {0x0D, 0x0A};	/**< @brief ��M�t���[���̃t�b�^*/

//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof AKI_GPS_STRUCT
 * @public
 * @brief AKI_GPS�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA AKI_GPS_STRUCT.driver_super �ɒ����M���̃w�b�_,�t�b�^,�t���[���T�C�Y���L�^���܂��B
 * @note AKI_GPS�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param AKI_GPS_STRUCT *my_aki_gps : ����������AKI_GPS�\���̂ւ̃|�C���^
 * @param unsigned char ch : AKI_GPS���ڑ�����Ă���UART�|�[�g�ԍ�
 * @return 0 : ����I��
 * @return 100�ԑ� : �ُ�I��(�ڍׂ� DRIVER_Super_init() �̖߂�l���Q��)
 * @return 1000�ԑ� : �ُ�I��(�ڍׂ� AKI_GPS_Conf() �̖߂�l���Q��)
 */
int		AKI_GPS_init(AKI_GPS_STRUCT* my_aki_gps, unsigned char ch){
    int		i_ret;
	
	my_aki_gps->rs422_config.ch = ch;
	my_aki_gps->rs422_config.baudrate = 9600;
	my_aki_gps->rs422_config.stop_bit = 1;
	
	my_aki_gps->driver_super.inter_face = RS422;
	
	my_aki_gps->driver_super.periodic_config.rx_header_size = sizeof(aki_gps_rx_header);
	my_aki_gps->driver_super.periodic_config.rx_header = aki_gps_rx_header;
	
	my_aki_gps->driver_super.periodic_config.rx_footer_size = sizeof(aki_gps_rx_footer);
		my_aki_gps->driver_super.periodic_config.rx_footer = aki_gps_rx_footer;
	
	my_aki_gps->driver_super.periodic_config.rx_frame_size = AKI_GPS_RX_FRAME_SIZE;
	
	my_aki_gps->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_aki_gps->driver_super), &(my_aki_gps->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	return(0);
}

/**
 * @memberof AKI_GPS_STRUCT
 * @public
 * @brief AKI_GPS�ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * 
 * �{AKI_GPS�͒���R�}���h���M���s�v�Ȃ̂ŁA���̊֐��͎��s���Ă������N���܂���
 * @param AKI_GPS_STRUCT *my_aki_gps : �ΏۂƂ���AKI_GPS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_cycle() �̖߂�l���Q��)
 */
int		AKI_GPS_cycle(AKI_GPS_STRUCT* my_aki_gps){
	int		i_ret;
	
		#ifdef	AKI_GPS_DEBUG
			Printf("AKI_GPS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_aki_gps->driver_super), &(my_aki_gps->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof AKI_GPS_STRUCT
 * @public
 * @brief AKI_GPS����̃f�[�^�p�P�b�g���Ď����A��M�������e�� AKI_GPS_STRUCT �Ɋi�[���܂��B
 * 
 * AKI_GPS�̃f�[�^�o�͎����ł���A1�b��葁�������Œ���I�Ɏ��s���Ă��������B
 * @note �f�[�^�p�P�b�g�ɂ��Ă� DRIVER_Super_rec() ���g�p���ăt���[���������Ƃ�A
 * �t���[���������Ƃꂽ�ꍇ�Ɏ�M���e�� AKI_GPS_STRUCT �Ɋi�[���܂��B
 * @param AKI_GPS_STRUCT *my_aki_gps : �ΏۂƂ���AKI_GPS�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		AKI_GPS_rec(AKI_GPS_STRUCT* my_aki_gps){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_aki_gps->driver_super), &(my_aki_gps->rs422_config));
	if(i_ret == 1){
			#ifdef	AKI_GPS_DEBUG
				Printf("AKI_GPS: *** Frame ***\n");
			#endif
		AKI_GPS_Data_Conv(my_aki_gps);
	}
	
	return(i_ret);
}

/**
 * @memberof AKI_GPS_STRUCT
 * @public
 * @brief AKI_GPS�\���̂̃f�[�^���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param AKI_GPS_STRUCT *my_gps : �ΏۂƂ���AKI_GPS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		AKI_GPS_debug_message(AKI_GPS_STRUCT* my_aki_gps){
	Printf("UTC:%lf ", my_aki_gps->utc);
	Printf("Latitude:%lf ", my_aki_gps->latitude);
	Printf("Longitude:%lf ", my_aki_gps->longitude);
	Printf("Position_fix:%d ", my_aki_gps->p_fix);
	Printf("Visible_sat:%d ", my_aki_gps->visible_sat);
	Printf("HDOP:%f ", my_aki_gps->hdop);
	Printf("Antenna_height:%lf ", my_aki_gps->antenna_height);
	Printf("Geoidal_height:%lf ", my_aki_gps->geoidal_height);
	
	DRIVER_Super_debug_message(&(my_aki_gps->driver_super));
	
	
	return(0);
}

//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof AKI_GPS_STRUCT
 * @private
 * @brief �t���[���f�[�^��AKI_GPS�\���̂̃f�[�^���e�ɕϊ����܂��B
 * 
 * �H�w�l�ϊ����K�v�ȏꍇ�͂����ɏ������݂܂��B
 * @param AKI_GPS_STRUCT *my_aki_gps : �ΏۂƂ���AKI_GPS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		AKI_GPS_Data_Conv(AKI_GPS_STRUCT *my_aki_gps){
	/** @brief �t���[���f�[�^�̃w�b�_�����I�t�Z�b�g�����|�C���^*/
	unsigned char *aki_gps_rx_data = my_aki_gps->driver_super.periodic_rx_frame + sizeof(aki_gps_rx_header);
	
	int i;
	int	counter = 0;
	char	aki_gps_tmp[24];
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->utc = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->latitude = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	if(aki_gps_rx_data[counter] == 'S'){
		my_aki_gps->latitude = -(my_aki_gps->latitude);
	}
	counter++;
	counter++;
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->longitude = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	if(aki_gps_rx_data[counter] == 'W'){
		my_aki_gps->longitude = -(my_aki_gps->latitude);
	}
	counter++;
	counter++;
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->p_fix = atoi(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->visible_sat = atoi(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->hdop = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->antenna_height = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	// �]����'M'������
		counter++;
		counter++;
	
	for(i = 0; i < sizeof(aki_gps_tmp); i++){
		if(aki_gps_rx_data[counter] == ','){
			aki_gps_tmp[i] = 0x00;
			counter++;
			my_aki_gps->geoidal_height = atof(aki_gps_tmp);
			break;
		}
		aki_gps_tmp[i] = aki_gps_rx_data[counter];
		counter++;
	}
	
	return(0);
}
