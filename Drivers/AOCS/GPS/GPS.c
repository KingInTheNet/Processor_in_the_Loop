/**
 * @file GPS.c
 * @brief GPS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * GPS�C���^�[�t�F�[�X���W���[���́AAxelSpace��AXELNAV-1�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g�A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.10.18
 */

#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "GPS.h"

//#define	GPS_DEBUG


int				GPS_Data_Conv(GPS_STRUCT *my_gps);
void			seven2eight(void* bef, void* aft, int size_bef, int size_aft, char sig_flag);
unsigned int	psmod(unsigned int xp, unsigned int xq);
long long		utc(unsigned char year_c, unsigned char mon, unsigned char day, unsigned char time, unsigned char min, unsigned char sec);


#define GPS_CONF_FRAME_SIZE	21	/**< @brief �o�̓f�[�^�ݒ�R�}���h�̒���*/
static unsigned int		gps_dummy1;
static unsigned char	gps_conf_cmd_data_standard_default[GPS_CONF_FRAME_SIZE] = 
{0xC6,									// �w�b�_
 0x00, 0x00, 0x00, 0x00,				// ����ܓx-������
 0x00, 0x00, 0x00, 0x00,				// ����o�x-������
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// UTC-������
 0x00, 0x00, 0x00,						// ��]�ȉ~�̍�-������
 0x00,									// N/A
 0x00,									// (bit0)�R�[���h�X�^�[�g-���Ȃ�,
 										// (bit1)������-���Ȃ�,
 										// (bit2�`4)���͒l�g�p-���Ȃ�,
 										// (bit5)�}�X�^�[���Z�b�g-���Ȃ�,
 										// (bit6)�R�}���h�^�C�v-�W���R�}���h
 0xDA};									// �^�[�~�l�[�^
  /**< @brief �o�̓f�[�^�ݒ�R�}���h(�W��)*/
 
#define	GPS_CONF_STANDARD_CMD	gps_conf_cmd_data_standard_default	/**< @brief �o�̓f�[�^�ݒ�R�}���h(�W��)*/

static unsigned int	gps_dummy2;
static unsigned char	gps_conf_cmd_data_expansion_default[GPS_CONF_FRAME_SIZE + 3] = 
{0x00, 0x00, 0x00,	// �u�w�b�_�v�̃A�h���X��4�̔{���ɂ��邽�߂̃I�t�Z�b�g��
 0xC6,			// �w�b�_
 0x01,			// ���ʃ��[�h-3D
 0x01,			// �p�}�X�N�p�x-1
 0x00,			// �d���w�E�Η����̒n��p�␳�؂�ւ��t���O-�␳�Ȃ�
 0x40,			// PDOP������~�b�g-128(�ݒ�l=64)
 0x02,			// ���������x��-��
 0x00,			// ���ʍ��W�n-WGS-84
 0x00,			// �g�p�֎~�q���@�̉q���ԍ�-�g�p�֎~���Ȃ�
 0x00,			// �g�p�֎~�q���A�̉q���ԍ�-�g�p�֎~���Ȃ�
 0x00,			// �g�p�֎~�q���B�̉q���ԍ�-�g�p�֎~���Ȃ�
 0x00,			// �g�p�֎~�q���C�̉q���ԍ�-�g�p�֎~���Ȃ�
 0x00,			// �g�p�֎~�q���D�̉q���ԍ�-�g�p�֎~���Ȃ�
 0x00,			// �g�p�֎~�q���E�̉q���ԍ�-�g�p�֎~���Ȃ�
 0x00,			// �o�̓t�H�[�}�b�g-�W���o��
 0x00,			// �G�t�F�����X�o�͂���q���ԍ�-������
 0x00,			// �R�[���h�X�^�[�g�v��-���Ȃ�
 0x00,			// DGPS���ʗv��-���Ȃ�
 0x00, 0x00,	// N/A
 0x40,			// (bit6)�R�}���h�^�C�v-�g���R�}���h
 0xDA};			// �^�[�~�l�[�^
  /**< @brief �o�̓f�[�^�ݒ�R�}���h(�g��)*/

#define	GPS_CONF_EXPANSION_CMD	gps_conf_cmd_data_expansion_default + 3	/**< @brief �o�̓f�[�^�ݒ�R�}���h(�g��)*/


//#define GPS_RX_FRAME_SIZE			225
#define GPS_RX_FRAME_SIZE			99	/**< @brief ��M�t���[���̒���*/

static unsigned char	gps_rx_header[1] = {0xC6};	/**< @brief ��M�t���[���̃w�b�_*/
static unsigned char	gps_rx_footer[1] = {0xDA};	/**< @brief ��M�t���[���̃t�b�^*/

//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPS�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA GPS_STRUCT.driver_super �ɒ����M���̃w�b�_,�t�b�^,�t���[���T�C�Y�A����R�}���h���s���̏����L�^���܂��B
 * �܂��A�������Ɠ����ɁAGPS�ɑ΂��ďo�͂��u�W���o�́v�݂̂ɂ���悤�ɃR�}���h�𔭍s���܂��B
 * @note GPS�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param GPS_STRUCT *my_gps : ����������GPS�\���̂ւ̃|�C���^
 * @param unsigned char ch : GPS���ڑ�����Ă���UART�|�[�g�ԍ�
 * @return 0 : ����I��
 * @return 100�ԑ� : �ُ�I��(�ڍׂ� DRIVER_Super_init() �̖߂�l���Q��)
 * @return 1000�ԑ� : �ُ�I��(�ڍׂ� GPS_Conf() �̖߂�l���Q��)
 */
int		GPS_init(GPS_STRUCT* my_gps, unsigned char ch){
    int		i_ret;
	
	my_gps->rs422_config.ch = ch;
	my_gps->rs422_config.baudrate = 4800;
	my_gps->rs422_config.stop_bit = 2;
	
	my_gps->driver_super.inter_face = RS422;
	
	my_gps->driver_super.periodic_config.rx_header_size = sizeof(gps_rx_header);
	my_gps->driver_super.periodic_config.rx_header = gps_rx_header;
	
	my_gps->driver_super.periodic_config.rx_footer_size = sizeof(gps_rx_footer);
	my_gps->driver_super.periodic_config.rx_footer = gps_rx_footer;
	
	my_gps->driver_super.periodic_config.rx_frame_size = GPS_RX_FRAME_SIZE;
	
	my_gps->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_gps->driver_super), &(my_gps->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	/*
	pif((i_ret = GPS_Conf(my_gps)) != 0){	// Error
		return(i_ret);
	}
	*/
	
	return(0);
}

/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPS�ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * 
 * �{GPS�͒���R�}���h���M���s�v�Ȃ̂ŁA���̊֐��͎��s���Ă������N���܂���
 * @param GPS_STRUCT *my_gps : �ΏۂƂ���GPS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_cycle() �̖߂�l���Q��)
 */
int		GPS_cycle(GPS_STRUCT* my_gps){
	int		i_ret;
	
		#ifdef	GPS_DEBUG
			Printf("GPS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_gps->driver_super), &(my_gps->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPS����̃f�[�^�p�P�b�g���Ď����A��M�������e�� GPS_STRUCT �Ɋi�[���܂��B
 * 
 * GPS�̃f�[�^�o�͎����ł���A1�b��葁�������Œ���I�Ɏ��s���Ă��������B
 * @note �f�[�^�p�P�b�g�ɂ��Ă� DRIVER_Super_rec() ���g�p���ăt���[���������Ƃ�A
 * �t���[���������Ƃꂽ�ꍇ�Ɏ�M���e�� GPS_STRUCT �Ɋi�[���܂��B
 * @param GPS_STRUCT *my_gps : �ΏۂƂ���GPS�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		GPS_rec(GPS_STRUCT* my_gps){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_gps->driver_super), &(my_gps->rs422_config));
	if(i_ret == 1){
			#ifdef	GPS_DEBUG
				Printf("GPS: *** Frame ***\n");
			#endif
		GPS_Data_Conv(my_gps);
	}
	
	return(i_ret);
}

/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPS�\���̂̃f�[�^���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param GPS_STRUCT *my_gas : �ΏۂƂ���GPS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		GPS_debug_message(GPS_STRUCT* my_gps){
	Printf("X:%lld ", my_gps->vector_x);
	Printf("Y:%lld ", my_gps->vector_y);
	Printf("Z:%lld ", my_gps->vector_z);
	//Printf("PDOP:%d ", my_gps->pdop);
	Printf("UTC:");
	Printf("20%02d/", my_gps->utc.year);
	Printf("%02d/", my_gps->utc.month);
	Printf("%02d ", my_gps->utc.day);
	Printf("%02d:", my_gps->utc.hour);
	Printf("%02d:", my_gps->utc.min);
	Printf("%02d ", my_gps->utc.sec);
	//Printf("aSat:%d ", my_gps->alive_sat);
	Printf("vSat:%d ", my_gps->visible_sat);
	//Printf("Delay:%d ", my_gps->delay_time);
	//Printf("PPS:%d ", my_gps->pps);
	//Printf("Sts1:%d ", my_gps->status1.byte);
	
	DRIVER_Super_debug_message(&(my_gps->driver_super));
	
	
	return(0);
}

/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPS�o�̓f�[�^�ݒ�R�}���h���s�֐��ł��B
 * 
 * �o�̓f�[�^�ݒ�R�}���h(�W��)�𔭍s���A����1�b��ɏo�̓f�[�^�ݒ�R�}���h(�g��)�𔭍s���܂��B
 * @note aosc_super�ɔ����R�}���h���s���ƁA���̃R�}���h�ɑ΂��郌�X�|���X��M���̏����������݁A
 *  DRIVER_Super_conf()�����s���Ă��܂��B
 * @param GPS_STRUCT *my_gps : �ΏۂƂ���GPS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 1000�ԑ� : �o�̓f�[�^�ݒ�R�}���h(�W��)���s���łُ̈�I��(�ڍׂ�-1000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 2000�ԑ� : �o�̓f�[�^�ݒ�R�}���h(�g��)���s���łُ̈�I��(�ڍׂ�-2000������ DRIVER_Super_conf() �̖߂�l���Q��)
 */
int		GPS_Conf(GPS_STRUCT *my_gps){
	int		i_ret;	/**< @brief DRIVER_Super_conf()�̖߂�l�i�[*/
	
	my_gps->driver_super.non_periodic_config.rx_frame_size = 0;
	
	my_gps->driver_super.non_periodic_config.tx_frame_size = GPS_CONF_FRAME_SIZE;
	my_gps->driver_super.non_periodic_config.tx_frame = GPS_CONF_STANDARD_CMD;
	if((i_ret = DRIVER_Super_conf(&(my_gps->driver_super), &(my_gps->rs422_config))) != 1){	// Error
			#ifdef	GPS_DEBUG
				Printf("GPS: +++ Error Config Cmd 1 +++\n");
			#endif
		return (1000 + i_ret);
	}
	MilliSleep(1000);	//1sec wait
	
	my_gps->driver_super.non_periodic_config.tx_frame_size = GPS_CONF_FRAME_SIZE;
	my_gps->driver_super.non_periodic_config.tx_frame = GPS_CONF_EXPANSION_CMD;
	if((i_ret = DRIVER_Super_conf(&(my_gps->driver_super), &(my_gps->rs422_config))) != 1){	// Error
			#ifdef	GPS_DEBUG
				Printf("GPS: +++ Error Config Cmd 2 +++\n");
			#endif
		return (2000 + i_ret);
	}
	//MilliSleep(1000);	//1sec wait
	
	return(0);
}

//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof GPS_STRUCT
 * @private
 * @brief �t���[���f�[�^��GPS�\���̂̃f�[�^���e�ɕϊ����܂��B
 * 
 * �H�w�l�ϊ����K�v�ȏꍇ�͂����ɏ������݂܂��B
 * @param GPS_STRUCT *my_gps : �ΏۂƂ���GPS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		GPS_Data_Conv(GPS_STRUCT *my_gps){
	/** @brief �t���[���f�[�^�̃w�b�_�����I�t�Z�b�g�����|�C���^*/
	unsigned char *gps_rx_data = my_gps->driver_super.periodic_rx_frame + sizeof(gps_rx_header);
	
	seven2eight(gps_rx_data + 0, &(my_gps->latitude), 4, sizeof(my_gps->latitude), 1);
	seven2eight(gps_rx_data + 4, &(my_gps->longitude), 4, sizeof(my_gps->longitude), 1);
	seven2eight(gps_rx_data + 8, &(my_gps->altitude), 3, sizeof(my_gps->altitude), 0);
	
	seven2eight(gps_rx_data + 11, &(my_gps->vector_x), 6, sizeof(my_gps->vector_x), 1);
	seven2eight(gps_rx_data + 17, &(my_gps->vector_y), 6, sizeof(my_gps->vector_y), 1);
	seven2eight(gps_rx_data + 23, &(my_gps->vector_z), 6, sizeof(my_gps->vector_z), 1);
	
	seven2eight(gps_rx_data + 29, &(my_gps->speed), 2, sizeof(my_gps->speed), 0);
	seven2eight(gps_rx_data + 31, &(my_gps->direction), 2, sizeof(my_gps->direction), 0);
	
	seven2eight(gps_rx_data + 33, &(my_gps->pdop), 2, sizeof(my_gps->pdop), 0);
	
	seven2eight(gps_rx_data + 35, &(my_gps->utc.year), 1, sizeof(my_gps->utc.year), 0);
	seven2eight(gps_rx_data + 36, &(my_gps->utc.month), 1, sizeof(my_gps->utc.month), 0);
	seven2eight(gps_rx_data + 37, &(my_gps->utc.day), 1, sizeof(my_gps->utc.day), 0);
	seven2eight(gps_rx_data + 38, &(my_gps->utc.hour), 1, sizeof(my_gps->utc.hour), 0);
	seven2eight(gps_rx_data + 39, &(my_gps->utc.min), 1, sizeof(my_gps->utc.min), 0);
	seven2eight(gps_rx_data + 40, &(my_gps->utc.sec), 1, sizeof(my_gps->utc.sec), 0);
	
	seven2eight(gps_rx_data + 41, &(my_gps->alive_sat), 1, sizeof(my_gps->alive_sat), 0);
	
	seven2eight(gps_rx_data + 42, &(my_gps->visible_sat), 1, sizeof(my_gps->visible_sat), 0);
	
	seven2eight(gps_rx_data + 43, &(my_gps->delay_time), 1, sizeof(my_gps->delay_time), 0);
	
	seven2eight(gps_rx_data + 44, &(my_gps->pps), 1, sizeof(my_gps->pps), 0);
	
	seven2eight(gps_rx_data + 95, &(my_gps->status1.byte), 1, sizeof(my_gps->status1.byte), 0);
	
	return(0);
}

/**
 * @memberof GPS_STRUCT
 * @private
 * @brief 7�r�b�g�`��(AXELNAV-1���[�U�[�Y�}�j���A���Q��)��8�r�b�g�`���ɕϊ����܂��B
 * @note �r�b�O�G���f�B�A�����Ŏ��s�̂���
 * @param void *bef : �ϊ��O�̃f�[�^
 * @param void *aft : �ϊ���̃f�[�^�i�[��
 * @param int size_bef : �ϊ��O�̃f�[�^�T�C�Y
 * @param int size_aft : �ϊ���̃f�[�^�i�[��T�C�Y
 * @param char sig_flag : �ϊ��f�[�^�������t�����ǂ���
 * @return �Ȃ�
 */
void	seven2eight(void* bef, void* aft, int size_bef, int size_aft, char sig_flag){
#define S2E_TMP 8
	
	unsigned char* before = (unsigned char*)bef;	// �擾���A�h���X
	unsigned char* after = (unsigned char*)aft;		// �i�[��A�h���X
	unsigned char tmp[S2E_TMP * 8 + 1];		// tmp[0]�͎g�p���Ȃ�, bool�㐔��Ƃ��Ďg�p
	unsigned char sig_data;					// �����̃f�[�^
	int i, j, cnt;
	int i_offset;
	
	size_bef = size_bef - 1;	// �o�C�g�T�C�Y�l��1�`8�ł͎g�p���Â炢�̂�0�`7�ɕύX
	size_aft = size_aft - 1;	// �o�C�g�T�C�Y�l��1�`8�ł͎g�p���Â炢�̂�0�`7�ɕύX
	
	// �擾������tmp[]��LSByte,LSBit����i�[(�e�o�C�g��MSBit�͖����f�[�^�Ȃ̂ŃX�L�b�v)
	cnt = S2E_TMP * 8;
	for(i = size_bef; i >= 0; i--){		// LSByet��菇�Ɏ擾���̃o�C�g�T�C�Y���Ń��[�v
		for(j = 0; j < 7; j++){				// LSBit��菇��7�r�b�g�������i�[
			tmp[cnt] = *(before + i);			// �Ώۃo�C�g���܂邲�ƃR�s�[
			tmp[cnt] &= (1 << j);				// �Ώۃo�C�g���̑Ώۃr�b�g�ȊO�Ƀ}�X�N����
			tmp[cnt] >>= j;						// �Ώۃr�b�g�̒l��char�^��bool�㐔�l��
			cnt--;								// 						�Ȃ�悤�ɃV�t�g
		}
	}
	// signed�t���O������Ύ擾����MSByte,MSBit-1�̒l�Ő����𔻒f���Asig_data��
	// signed�t���O���Ȃ���΂��̂܂�
	// ���̌�i�[��T�C�Y�ɍ����悤��tmp[]�̒l���i�[���𖄂߂�
	if(sig_flag != 0){		// ����signed�t���O�������Ă����
		cnt++;
		sig_data = tmp[cnt];
			//tmp[((S2E_TMP - size_aft) * 8) - 7] = sig_data;
		if(sig_data == 0){		// ���̏ꍇ
			for(cnt--; cnt > 0; cnt--){
				tmp[cnt] = 0;		// �l���i�[����0�Ŗ��߂�
			}
		}else{					// ���̏ꍇ
			for(cnt--; cnt > 0; cnt--){
				tmp[cnt] = 1;		// �l���i�[����1�Ŗ��߂�
			}
		}
	}else{					// ����signed�t���O���Ȃ����
		for(; cnt > 0; cnt--){
			tmp[cnt] = 0;		// �l���i�[����0�Ŗ��߂�
		}
	}
	
	// �i�[��̏�����
	for(i = 0; i <= size_aft; i++){
		*(after + i) = 0;
	}
	
	// �i�[��փf�[�^���i�[
	for(i = 0; i <= size_aft; i++){
		i_offset = i + (S2E_TMP - (size_aft + 1));
		for(j = 1; j <= 8; j++){
			*(after + i) |= (tmp[(i_offset * 8) + j] << (8 - j));	//�r�b�O�G���f�B�A����
			//*(after + (size_aft - i)) |= (tmp[(i_offset * 8) + j] << (8 - j));	//���g���G���f�B�A����
		}
	}
	
	return;
}

/**
 * @memberof GPS_STRUCT
 * @private
 * @brief ���̐��̏��Z���̗]����v�Z���܂��B
 * @note UTC�Z�o���Ɏg�p���܂�
 * @param unsigned int xp : �����鐔(����)
 * @param unsigned int xq : ���鐔(1�ȏ�̐���)
 * @return �]��
 */
unsigned int psmod(unsigned int xp, unsigned int xq){
	if(xp < 0){
		return ((xp % xq) + xq) % xq;
	}else{
		return (xp % xq);
	}
}//xq��1�ȏ�̐����Axp�𐮐��Ƃ���B

/**
 * @memberof GPS_STRUCT
 * @private
 * @brief UTC���v�Z���܂��B
 * @param unsigned char year_c : �N(��2��)
 * @param unsigned char mon : ��
 * @param unsigned char day : ��
 * @param unsigned char time : ��
 * @param unsigned char min : ��
 * @param unsigned char sec : �b
 * @return UTC
 */
long long utc(unsigned char year_c, unsigned char mon, unsigned char day, unsigned char time, unsigned char min, unsigned char sec){
	long long x;	/**< @brief UTC*/
	unsigned int year = 2000 + (unsigned int)year_c;	/**< @brief �N*/
	
	x = 31556952 * (year - 1970 - (psmod((year - 1970), 400)));
	year = 1970 + psmod((year - 1970), 400);
	while(year != 1970){
		if((psmod(year, 4) == 0 && psmod(year, 100) != 0) || psmod(year, 400) == 0){
			x += 31622400;
		}else{
			x += 31536000;
		}
		year -= 1;
	}
	switch((int)mon){
		case 12:
			day += 30;
		case 11:
			day += 31;
		case 10:
			day += 30;
		case 9:
			day += 31;
		case 8:
			day += 31;
		case 7:
			day += 30;
		case 6:
			day += 31;
		case 5:
			day += 30;
		case 4:
			day += 31;
		case 3:
			day += 28;
		case 2:
			day += 31;
			break;
		default:
			break;
	}
	x += (day - 1) * 86400 + time * 3600 + min * 60 + sec;
	
	return (x);
}
