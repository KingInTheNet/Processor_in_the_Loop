/**
 * @file AA.c
 * @brief AA(ActiveAnalog)���b�p�[�̃N���X�ł��B
 * 
 * AA(ActiveAnalog)���b�p�[�́A
 * AA�̃C���^�[�t�F�[�X���������A
 * AA�|�[�g�̏������A�d���l�擾���s���A
 * AA���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @author ���� �@���Y
 * @date 2013.04.06
 */

/* �C���N���[�h�t�@�C���錾 */

#include "t_services.h"        		/* TOPPERS�p�w�b�_�t�@�C��              */
#include "../source/mw_header.h"	/* �~�h���E�F�A�p�w�b�_�t�@�C��         */
#include "IF_Board_Number.h"
#include "utility.h"

#include "AA.h"

#define AA_TIMECODE		((unsigned int)1)		/**< @brief �~�h���E�G�A�ւ̐ݒ�(�擾����)���`���܂��B*/

/* �ϐ���` */
static unsigned int		aa_rx_trigger;		/**< @brief �~�h���E�G�A����̃f�[�^(�C�x���g�g���K�J�E���g�l)���i�[����ϐ��ł��B*/
static unsigned long	aa_last_get_time;	/**< @brief �f�[�^���Ō�Ɏ擾�����������i�[����ϐ��ł��B*/
static int				aa_get_data[8];		/**< @brief �Ō�Ɏ擾�����f�[�^���i�[����ϐ��ł��B*/

//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof AA_CONFIG_STRUCT
 * @protected
 * @brief AA_CONFIG�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * @note AA���b�p�[�̃N���X���g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @warning ���̊֐������s����O��AA_CONFIG�\���̓��̐ݒ�l��ݒ肵�Ă����K�v������܂��B
 * @param void *my_aa_v : ����������AA_CONFIG�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� M_AP_nobc_aa_ctrl() �̖߂�l���Q��)
 */
int	AA_init(void *my_aa_v){
    AA_CONFIG_STRUCT *my_aa = (AA_CONFIG_STRUCT *)my_aa_v;
    int                 i_ret = 0;
	
	
	if((i_ret = M_AP_nobc_aa_ctrl(d_IF_BORD1, AA_TIMECODE)) != 0){	// Error
		return (i_ret - 100);
	}
	
	aa_last_get_time = 0;
	aa_get_data[0] = 0;
	aa_get_data[1] = 0;
	aa_get_data[2] = 0;
	aa_get_data[3] = 0;
	aa_get_data[4] = 0;
	aa_get_data[5] = 0;
	aa_get_data[6] = 0;
	aa_get_data[7] = 0;
	
	
	return (i_ret);
}


//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof AA_CONFIG_STRUCT
 * @protected
 * @brief AA_CONFIG�\���̂ɂĎw�肳�ꂽ�|�[�g�̓d���l���擾���܂��B
 * @note �擾�d���l�̓|�[�g1���珇�Ƀ|�[�g8�܂Ŏw��|�[�g�̃f�[�^�݂̂��l�߂ďo�͂���܂��B
 * @param void *my_aa_v : �ΏۂƂ���AA_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : �d���l�i�[��ւ̃|�C���^
 * @param int *count : �d���l�i�[��̃f�[�^�T�C�Y
 * @note �擾�����d���l�́A�w��A�h���X���� short(2�o�C�g)x�擾�w�肵���|�[�g�� ���̃f�[�^(A/D�ϊ��l)�ƂȂ�܂��̂ŁA���̃o�C�g���ȏ�̗̈���m�ۂ��Ă��������B
 * @return -100 : �d���l�i�[��f�[�^�T�C�Y�s��
 * @return -200 : �^�C���A�E�g( M_AP_nobc_aa_getStat() �ŃR�P�Ă���)
 * @return -300�ԑ� : �ُ�I��(�ڍׂ�+300������ M_AP_nobc_aa_getVal() �̖߂�l���Q��)
 * @return ��L�ȊO : �d���l�L���f�[�^��(�d���l�擾���� ����I��)
 */
int		AA_RX(void *my_aa_v, void *data_v, int count){
	AA_CONFIG_STRUCT	*my_aa = (AA_CONFIG_STRUCT *)my_aa_v;
	short				*data = (short *)data_v;
	int					i_ret = 0;
	int					loop = 1;
	unsigned long		start_time;
	int					data_cnt = 0;
	int					i, j;
	
	
	for(i = 0; i < 8 * sizeof(my_aa->ch); i++){
		if((((my_aa->ch) >> i) & 0x01) == 1){
			data_cnt += sizeof(short);
		}
	}
	
	if(count < data_cnt){
		return (-100);
	}
	
	
	if(((my_time() - aa_last_get_time) >= 50) || ((my_time() - aa_last_get_time) < 0)){
		/*
		loop = 1;
		start_time = my_time();
		while(loop){
			if(M_AP_nobc_aa_getStat(d_IF_BORD1) == 0){
				loop = 0;
			}
			if(((my_time() - start_time) > 100) || ((my_time() - start_time) < 0)){
				return (-200);
			}
			tslp_tsk(10);
		}
		*/
		
		if((i_ret = M_AP_nobc_aa_getVal(d_IF_BORD1, 0x000000FF, &aa_rx_trigger, (unsigned int *)aa_get_data)) != 0){	// Error
			return (i_ret - 300);
		}
		aa_last_get_time = my_time();
	}
	
	
	j = 0;
	for(i = 0; i < 8 * sizeof(my_aa->ch); i++){
		if((((my_aa->ch) >> i) & 0x01) == 1){
			data[j] = (short)aa_get_data[i];
			j++;
		}
	}
	
	return (data_cnt);
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof AA_CONFIG_STRUCT
 * @protected
 * @brief AA�ɂ����āu���M�v�ɂ�������̂͂Ȃ��̂ŁA�������Ȃ��_�~�[�̊֐��ł��B
 * @param void *my_aa_v : �ΏۂƂ���AA_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : ���M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ���M�f�[�^�T�C�Y
 * @return 0 : ����I��
 */
int		AA_TX(void *my_aa_v, void *data_v, int count){
	AA_CONFIG_STRUCT *my_aa = (AA_CONFIG_STRUCT *)my_aa_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
	
	return	(i_ret);
}
