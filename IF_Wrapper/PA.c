/**
 * @file PA.c
 * @brief PA(PassiveAnalog)���b�p�[�̃N���X�ł��B(AOBC�p)
 * 
 * PA(PassiveAnalog)���b�p�[�́A
 * PA�̃C���^�[�t�F�[�X���������A
 * PA�|�[�g�̏������A�d���l�擾���s���A
 * PA���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @author ���� �@���Y
 * @date 2013.10.24
 */

/* �C���N���[�h�t�@�C���錾 */
#include "t_services.h"        		/* TOPPERS�p�w�b�_�t�@�C��              */
#include "../source/mw_header.h"	/* �~�h���E�F�A�p�w�b�_�t�@�C��         */
#include "IF_Board_Number.h"

#include "PA.h"

#define PA_TIMECODE		((unsigned int)1)		/**< @brief �~�h���E�G�A�ւ̐ݒ�(�擾����)���`���܂��B*/

/* �ϐ���` */
static unsigned int		pa_rx_trigger;			/**< @brief �~�h���E�G�A����̃f�[�^(�C�x���g�g���K�J�E���g�l)���i�[����ϐ��ł��B*/
static int				pa_get_data[16];		/**< @brief �Ō�Ɏ擾�����f�[�^���i�[����ϐ��ł��B*/
static unsigned char	pa_next_get_ch_group;	/**< @brief ���Ƀf�[�^���擾����`�����l���Q���w������ϐ��ł��B*/

//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof PA_CONFIG_STRUCT
 * @protected
 * @brief PA_CONFIG�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * @note PA���b�p�[�̃N���X���g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @warning ���̊֐������s����O��PA_CONFIG�\���̓��̐ݒ�l��ݒ肵�Ă����K�v������܂��B
 * @param void *my_pa_v : ����������PA_CONFIG�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return -100�ԑ� : �ُ�I��(�ڍׂ�+100������ M_AP_nobc_pa_ctrl() �̖߂�l���Q��)
 * @return -200�ԑ� : �ُ�I��(�ڍׂ�+200������ M_AP_nobc_selectTempCh() �̖߂�l���Q��)
 */
int	PA_init(void *my_pa_v){
    PA_CONFIG_STRUCT *my_pa = (PA_CONFIG_STRUCT *)my_pa_v;
    int                 i_ret = 0;
	
	
	pa_get_data[0] = 0;
	pa_get_data[1] = 0;
	pa_get_data[2] = 0;
	pa_get_data[3] = 0;
	pa_get_data[4] = 0;
	pa_get_data[5] = 0;
	pa_get_data[6] = 0;
	pa_get_data[7] = 0;
	pa_get_data[8] = 0;
	pa_get_data[9] = 0;
	pa_get_data[10] = 0;
	pa_get_data[11] = 0;
	pa_get_data[12] = 0;
	pa_get_data[13] = 0;
	pa_get_data[14] = 0;
	pa_get_data[15] = 0;
	
	if((i_ret = M_AP_nobc_pa_ctrl(d_IF_BORD1, PA_TIMECODE)) != 0){	// Error
		return (i_ret - 100);
	}
	
	pa_next_get_ch_group = 0;		// 0�`7ch
	
	if((i_ret = M_AP_nobc_selectTempCh(d_IF_BORD1, pa_next_get_ch_group)) != 0){	// 0�`7ch�ɐؑ�
		return (i_ret - 200);
	}
	
	
	return (i_ret);
}

//***************************************************
//	Middlewear RX
//***************************************************
/**
 * @brief PA�|�[�g�̓d���l���擾���܂��B
 * @param unsigned char call_counter : �Ăяo���񐔎w��
 * @return 0 : ����I��
 * @return -1000�ԑ�,-3000�ԑ� : �ُ�I��(�ڍׂ�+1000���� M_AP_nobc_pa_getVal() �̖߂�l���Q��)
 * @return -2000�ԑ�,-4000�ԑ� : �ُ�I��(�ڍׂ�+2000���� M_AP_nobc_selectTempCh() �̖߂�l���Q��)
 */
int		PA_Middlewear_RX(unsigned char call_counter){
    int					i_ret = 0;
	
	
	call_counter %= 200;	// 1sec����
	
	//////// ��M���� ////////
	if((call_counter % 200) == 47){	// 1000msec��1��,�ʑ���47�̎�
		if(pa_next_get_ch_group == 0){	// 0�`7ch
			// 0�`7ch�擾
			if((i_ret = M_AP_nobc_pa_getVal(d_IF_BORD1, 0x000000FF, &pa_rx_trigger, (unsigned int *)(&pa_get_data[0]))) != 0){	// Error
				return (-1000 - i_ret);
			}
			pa_next_get_ch_group = 1;	// ����8�`15ch�؂�ւ�
		}
	}
	
	//////// �؂�ւ����� ////////
	if((call_counter % 200) == 87){	// 1000msec��1��,�ʑ���87�̎�
		if(pa_next_get_ch_group == 1){
			if((i_ret = M_AP_nobc_selectTempCh(d_IF_BORD1, 1)) != 0){	// 8�`15ch�ɐؑ�
				pa_next_get_ch_group = 0;	// ����0�`7ch��M
				return (-2000 - i_ret);
			}
			pa_next_get_ch_group = 2;	// ����8�`15ch��M
		}
	}
	
	//////// ��M���� ////////
	if((call_counter % 200) == 147){	// 1000msec��1��,�ʑ���147�̎�
		if(pa_next_get_ch_group == 2){	// 0�`7ch
			if((i_ret = M_AP_nobc_pa_getVal(d_IF_BORD1, 0x000000FF, &pa_rx_trigger, (unsigned int *)(&pa_get_data[8]))) != 0){	// Error
				return (-3000 - i_ret);
			}
			pa_next_get_ch_group = 3;	// ����0�`7ch�؂�ւ�
		}
	}
	
	//////// �؂�ւ����� ////////
	if((call_counter % 200) == 187){	// 1000msec��1��,�ʑ���187�̎�
		if(pa_next_get_ch_group == 3){
			if((i_ret = M_AP_nobc_selectTempCh(d_IF_BORD1, 0)) != 0){	// 0�`7ch�ɐؑ�
				pa_next_get_ch_group = 2;	// ����8�`15ch��M
				return (-4000 - i_ret);
			}
			pa_next_get_ch_group = 0;	// ����0�`7ch��M
		}
	}
	
	
	return (i_ret);
}

//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof PA_CONFIG_STRUCT
 * @protected
 * @brief PA_CONFIG�\���̂ɂĎw�肳�ꂽ�|�[�g�̓d���l���擾���܂��B
 * @note �擾�d���l�̓|�[�g1���珇�Ƀ|�[�g8�܂Ŏw��|�[�g�̃f�[�^�݂̂��l�߂ďo�͂���܂��B
 * @param void *my_pa_v : �ΏۂƂ���PA_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : �d���l�i�[��ւ̃|�C���^
 * @param int *count : �d���l�i�[��̃f�[�^�T�C�Y
 * @note �擾�����d���l�́A�w��A�h���X���� short(2�o�C�g)x�擾�w�肵���|�[�g�� ���̃f�[�^(A/D�ϊ��l)�ƂȂ�܂��̂ŁA���̃o�C�g���ȏ�̗̈���m�ۂ��Ă��������B
 * @return -100 : �d���l�i�[��f�[�^�T�C�Y�s��
 * @return ��L�ȊO : �d���l�L���f�[�^��(�d���l�擾���� ����I��)
 */
int		PA_RX(void *my_pa_v, void *data_v, int count){
	PA_CONFIG_STRUCT	*my_pa = (PA_CONFIG_STRUCT *)my_pa_v;
	short				*data = (short *)data_v;
    int					i_ret = 0;
	int					data_cnt = 0;
	int					i, j;
	
	
	for(i = 0; i < 16 * sizeof(my_pa->ch); i++){
		if((((my_pa->ch) >> i) & 0x01) == 1){
			data_cnt += sizeof(short);
		}
	}
	
	if(count < data_cnt){
		return (-100);
	}
	
	j = 0;
	for(i = 0; i < 8 * sizeof(my_pa->ch); i++){
		if((((my_pa->ch) >> i) & 0x01) == 1){
			data[j] = (short)pa_get_data[i];
			j++;
		}
	}
	
	
	return (data_cnt);
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof PA_CONFIG_STRUCT
 * @protected
 * @brief PA�ɂ����āu���M�v�ɂ�������̂͂Ȃ��̂ŁA�������Ȃ��_�~�[�̊֐��ł��B
 * @param void *my_pa_v : �ΏۂƂ���PA_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : ���M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ���M�f�[�^�T�C�Y
 * @return 0 : ����I��
 */
int		PA_TX(void *my_pa_v, void *data_v, int count){
	PA_CONFIG_STRUCT *my_pa = (PA_CONFIG_STRUCT *)my_pa_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
	
	return	(i_ret);
}
