/**
 * @file DC.c
 * @brief DC(Discrete)���b�p�[�̃N���X�ł��B(AOBC�p)
 * 
 * DC(Discrete)���b�p�[�́A
 * DC�̃C���^�[�t�F�[�X���������A
 * DC�|�[�g�̏������ADC�M�����o�͂��s���A
 * DC���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @author ���� �@���Y
 * @date 2013.06.20
 */

/* �C���N���[�h�t�@�C���錾 */
#include "t_services.h"        		/* TOPPERS�p�w�b�_�t�@�C��              */
#include "../source/mw_header.h"	/* �~�h���E�F�A�p�w�b�_�t�@�C��         */
#include "IF_Board_Number.h"

#include "DC.h"

#define DC_TIMECODE		((unsigned int)1)		/**< @brief �~�h���E�G�A�ւ̐ݒ�(�擾����)���`���܂��B*/

/* �ϐ���` */
// �����L��2�ϐ��̓A�h���X�l��4�̔{���ƂȂ�悤�ȃ�������ɃA�T�C������Ȃ��� M_AP_nobc_lvttl_getInVal() �����퓮�삵�Ȃ��炵���B
//   ����āA�e�ϐ��̒�`�̏��Ԃɒ��ӂ��邱�ƁB
static unsigned int	dc_in_tmp;	/**< @brief �~�h���E�G�A����̓��͒l�f�[�^���ꎞ�i�[����ϐ��ł��B*/
static unsigned int	dc_rx_trigger;	/**< @brief �~�h���E�G�A����̃f�[�^(�C�x���g�g���K�J�E���g�l)���i�[����ϐ��ł��B*/

static unsigned short	dc_curent_val_out = 0x0000;	/**< @brief ���݂̏o�͒l�f�[�^���i�[����ϐ��ł��B*/
static unsigned short	dc_current_val_in;		/**< @brief �Ō�Ɏ擾�������͒l���i�[����ϐ��ł��B*/

unsigned short dc_val_out;	/**< @public @brief �ŐV��DC�o�͒l�f�[�^���i�[����ϐ��ł�(�e�����g���p)�B*/
unsigned short dc_val_in;	/**< @public @brief �ŐV��DC���͒l�f�[�^���i�[����ϐ��ł�(�e�����g���p)�B*/


//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof DC_CONFIG_STRUCT
 * @protected
 * @brief DC_CONFIG�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * @note ���������ɁADC_CONFIG�\���̓��̐ݒ�l�Őݒ肵���|�[�g�̂݁A�M���l��"0"�ɂȂ�܂�(�ݒ肵�ĂȂ��|�[�g�͑O�̏�Ԃ̂܂܂ł�)�B
 * @note DC���b�p�[�̃N���X���g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @warning ���̊֐������s����O��DC_CONFIG�\���̓��̐ݒ�l��ݒ肵�Ă����K�v������܂��B
 * @param void *my_dc_v : ����������DC_CONFIG�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return -100�ԑ� : �ُ�I��(�ڍׂ�+100������ M_AP_nobc_lvttl_ctrl() �̖߂�l���Q��)
 * @return -200�ԑ� : �ُ�I��(�ڍׂ�+200������ M_AP_nobc_lvttl_setOutVal() �̖߂�l���Q��)
 */
int		DC_init(void *my_dc_v){
	DC_CONFIG_STRUCT *my_dc = (DC_CONFIG_STRUCT *)my_dc_v;
	int				i_ret;
	int				i;
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_out); i++){
		if((((my_dc->ch_out) >> i) & 0x0001) == 1){
			dc_curent_val_out &= (~(1 << i));
		}
	}
	
	if((i_ret = M_AP_nobc_lvttl_ctrl(d_IF_BORD1, DC_TIMECODE)) != 0){	// Error
		return (i_ret - 100);
	}
	
	if((i_ret = M_AP_nobc_lvttl_setOutVal(d_IF_BORD1, dc_curent_val_out)) != 0){	// Error
		return (i_ret - 200);
	}
	
	return (i_ret);
}

//***************************************************
//	Middlewear RX
//***************************************************
/**
 * @brief DC�M���l���擾���܂��B
 * @param unsigned char call_counter : �Ăяo���񐔎w��
 * @note �擾����DC�M���l�́A�w��A�h���X���� �擾�w�肵���|�[�g���o�C�g ���̃f�[�^�ƂȂ�܂��̂ŁA���̃o�C�g���ȏ�̗̈���m�ۂ��Ă��������B
 * @return 0 : ����I��
 * @return -1000�ԑ� : �ُ�I��(�ڍׂ�+1000���� M_AP_nobc_lvttl_getInVal() �̖߂�l���Q��)
 */
int		DC_Middlewear_RX(unsigned char call_counter){
	int				i_ret = 0;
	call_counter %= 200;	// 1sec����
	
	//////// ��M���� ////////
	if((call_counter % 200) == 87){	// 1000msec��1��,�ʑ���87�̎�
		if((i_ret = M_AP_nobc_lvttl_getInVal(d_IF_BORD1, &dc_rx_trigger, &dc_in_tmp)) != 0){	// Error
			return (-1000 - i_ret);
		}
	}
	
	dc_current_val_in = (unsigned short)dc_in_tmp;
	dc_val_in = (unsigned short)dc_in_tmp;
	
	
	return (i_ret);
}

//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof DC_CONFIG_STRUCT
 * @protected
 * @brief DC_CONFIG�\���̂ɂĎw�肳�ꂽ�|�[�g��DC�M���l���擾���܂��B
 * @note �擾DC�M���l�̓|�[�g1���珇�Ƀ|�[�g16�܂Ŏw�肵���|�[�g�̃f�[�^�݂̂��l�߂ďo�͂���܂��B
 * @param void *my_dc_v : �ΏۂƂ���DC_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : DC�M���l�i�[��ւ̃|�C���^
 * @param int *count : DC�M���l�i�[��̃f�[�^�T�C�Y
 * @note �擾����DC�M���l�́A�w��A�h���X���� �擾�w�肵���|�[�g���o�C�g ���̃f�[�^�ƂȂ�܂��̂ŁA���̃o�C�g���ȏ�̗̈���m�ۂ��Ă��������B
 * @return -100 : DC�M���l�i�[��f�[�^�T�C�Y�s��
 * @return ��L�ȊO : DC�M���l�L���f�[�^��(DC�M���l�擾���� ����I��)
 */
int		DC_RX(void *my_dc_v, void *data_v, int count){
	DC_CONFIG_STRUCT *my_dc = (DC_CONFIG_STRUCT *)my_dc_v;
	unsigned char *data = (unsigned char *)data_v;
	int				i_ret = 0;
	int				data_cnt = 0;
	int				i, j = 0;
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_in); i++){
		if((((my_dc->ch_in) >> i) & 0x0001) == 1){
			data_cnt++;
		}
	}
	
	if(count < data_cnt){
		return (-100);
	}
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_in); i++){
		if((((my_dc->ch_in) >> i) & 0x0001) == 1){
			*(data + j) = (unsigned char)((dc_current_val_in >> i) & 0x00000001);
			j++;
		}
	}
	
	return (data_cnt);
}

//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof DC_CONFIG_STRUCT
 * @protected
 * @brief DC_CONFIG�\���̂ɂĎw�肳�ꂽ�|�[�g��DC�M���l���o�͂��܂��B
 * @note �o�͂���DC�M���l�̓|�[�g1���珇�Ƀ|�[�g16�܂Ŏw�肵���|�[�g�̃f�[�^�݂̂��l�߁A"0"��"1"�Ŏw�肵�܂��B
 * @note �o�͂��w�肵�Ȃ������|�[�g�̏o�͒l�͑O�̏�Ԃ̂܂܂ł��B
 * @param void *my_dc_v : �ΏۂƂ���DC_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : DC�M���l�i�[��ւ̃|�C���^
 * @param int *count : DC�M���l�i�[��̃f�[�^�T�C�Y
 * @note �o�͂���DC�M���l�́A�w��A�h���X���� �o�͎w�肵���|�[�g���o�C�g ���̃f�[�^�ƂȂ�܂��̂ŁA���̃o�C�g���ȏ�̗̈���m�ۂ��Ă��������B
 * @return 0 : DC�M���l�L���f�[�^��(DC�M���l�擾���� ����I��)
 * @return -100 : DC�M���l�i�[��f�[�^�T�C�Y�s��
 * @return -200�ԑ� : �ُ�I��(�ڍׂ�+200������ M_AP_nobc_lvttl_setOutVal() �̖߂�l���Q��)
 */
int		DC_TX(void *my_dc_v, void *data_v, int count){
	DC_CONFIG_STRUCT *my_dc = (DC_CONFIG_STRUCT *)my_dc_v;
	unsigned char *data = (unsigned char *)data_v;
	int				i_ret = 0;
	int				data_cnt = 0;
	int				i, j = 0;
	
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_out); i++){
		if((((my_dc->ch_out) >> i) & 0x0001) == 1){
			data_cnt++;
		}
	}
	
	if(count < data_cnt){
		return (-100);
	}
	
	
	for(i = 0; i < 8 * sizeof(my_dc->ch_out); i++){
		if((((my_dc->ch_out) >> i) & 0x0001) == 1){
			if((data[j] & 0x01) == 0){
				dc_curent_val_out &= (~(1 << i));
			}else if((data[j] & 0x01) == 1){
				dc_curent_val_out |= (1 << i);
			}
			j++;
		}
	}
	
	
	if((i_ret = M_AP_nobc_lvttl_setOutVal(d_IF_BORD1, (unsigned int)dc_curent_val_out)) != 0){	// Error
		return (i_ret - 200);
	}
	
	dc_val_out = dc_curent_val_out;
	
	return (i_ret);
}
