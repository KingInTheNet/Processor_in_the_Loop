/**
 * @file CCSDS.c
 * @brief CCSDS�ʐM���b�p�[�̃N���X�ł��B(AOBC�p �ʏ��荞��Ver)
 * 
 * CCSDS�ʐM���b�p�[�́A
 * CCSDS�̃C���^�[�t�F�[�X���������A
 * CCSDS�|�[�g�̏������A�f�[�^���M�A�f�[�^��M���s���A
 * CCSDS�ʐM���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @author ���� �@���Y
 * @date 2013.06.13
 */

/* �C���N���[�h�t�@�C���錾 */
#include "t_services.h"        		/* TOPPERS�p�w�b�_�t�@�C��              */
#include "../source/mw_header.h"	/* �~�h���E�F�A�p�w�b�_�t�@�C��         */
#include "IF_Board_Number.h"

#include "CCSDS.h"

/* �ϐ���` */
/**
 * @brief CCSDS�|�[�g�̃f�[�^���M�A�f�[�^��M�̍ۂɕK�v�ƂȂ�A�~�h���E�G�A�̐ݒ�����i�[����\���̂ł��B
 */

M_T_COM_REF_BUFF    fill_vcdu_t_buf;	/**< @brief FILL_VCDU���M�f�[�^���ݒ�p*/
M_T_COM_REF_BUFF    hk_vcdu_t_buf;		/**< @brief HK_VCDU���M�f�[�^���ݒ�p*/
M_T_COM_REF_BUFF    ms_vcdu_t_buf;		/**< @brief MS_VCDU���M�f�[�^���ݒ�p*/
M_T_COM_SET_BUFF    ccsds_rcvBuff;	/**< @brief ��M�f�[�^���ݒ�p*/

unsigned int	ccsds_dummy1;
unsigned char	ccsds_fill_vcdu[220] = {0x00, };
unsigned int	ccsds_dummy2;
unsigned char	ccsds_ms_send_buf[220];


//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof CCSDS_CONFIG_STRUCT
 * @protected
 * @brief CCSDS_CONFIG�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * @note CCSDS�ʐM���b�p�[�̃N���X���g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @warning ���̊֐������s����O��CCSDS_CONFIG�\���̓��̐ݒ�l��ݒ肵�Ă����K�v������܂��B
 * @param void *my_ccsds_v : ����������CCSDS_CONFIG�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return -100 : �r�b�g���[�g�ݒ�l�s��
 * @return -200�ԑ� : �ُ�I��(�ڍׂ�+200������ M_AP_nobc_ccsds_sndCtrl() �̖߂�l���Q��)
 * @return -300�ԑ� : �ُ�I��(�ڍׂ�+300������ M_AP_nobc_ccsds_ctrl() �̖߂�l���Q��)
 * @return -400�ԑ� : �ُ�I��(�ڍׂ�+400������ M_AP_nobc_ccsds_setOutPort() �̖߂�l���Q��)
 * @return -500�ԑ� : �ُ�I��(�ڍׂ�+500������ M_AP_nobc_ccsds_setFillData() �̖߂�l���Q��)
 * @return -600�ԑ� : �ُ�I��(�ڍׂ�+600������ M_AP_nobc_ccsds_sndCtrl() �̖߂�l���Q��)
 */
int	CCSDS_init(void *my_ccsds_v){
    CCSDS_CONFIG_STRUCT *my_ccsds = (CCSDS_CONFIG_STRUCT *)my_ccsds_v;
    int                 i_ret = 0;
	unsigned int		rate;
	
	if(my_ccsds->bitrate == 2500){
		rate = M_d_SIO_BPS_2500K;
	}else if(my_ccsds->bitrate == 1250){
		rate = M_d_SIO_BPS_1250K;
	}else if(my_ccsds->bitrate == 1000){
		rate = M_d_SIO_BPS_1000K;
	}else if(my_ccsds->bitrate == 625){
		rate = M_d_SIO_BPS_625K;
	}else if(my_ccsds->bitrate == 64){
		rate = M_d_SIO_BPS_64K;
	}else if(my_ccsds->bitrate == 32){
		rate = M_d_SIO_BPS_32K;
	}else if(my_ccsds->bitrate == 16){
		rate = M_d_SIO_BPS_16K;
	}else if(my_ccsds->bitrate == 8){
		rate = M_d_SIO_BPS_8K;
	}else if(my_ccsds->bitrate == 4){
		rate = M_d_SIO_BPS_4K;
	}else{
		return (-100);
	}
	
	/********************************************************/
	/* ���M��~							                    */
	/********************************************************/
	i_ret = M_AP_nobc_ccsds_sndCtrl( d_IF_BORD1, 0 );
	if(i_ret != 0){
		return (-200 + i_ret);
	}
	
	if(my_ccsds->onoff == 0){
		return (i_ret);
	}
	
		tslp_tsk(1000);	//1sec wait
	
	/********************************************************/
	/* �|�[�g�ݒ�						                    */
	/********************************************************/
	i_ret = M_AP_nobc_ccsds_ctrl( d_IF_BORD1, rate, 220 );
	if(i_ret != 0){
		return (-300 + i_ret);
	}
	
	/********************************************************/
	/* �o�̓|�[�g�I��					                    */
	/********************************************************/
	i_ret = M_AP_nobc_ccsds_setOutPort( d_IF_BORD1, 0 );
	if(i_ret != 0){
		return (-400 + i_ret);
	}
	
	/********************************************************/
	/* FILL_VCDU�ݒ�					                    */
	/********************************************************/
	fill_vcdu_t_buf.vp_add = (void *)ccsds_fill_vcdu;
	fill_vcdu_t_buf.ui_dataSize = sizeof(ccsds_fill_vcdu);
	i_ret = M_AP_nobc_ccsds_setFillData( d_IF_BORD1, fill_vcdu_t_buf );
	if(i_ret != 0){
		return (-500 + i_ret);
	}
	
	/********************************************************/
	/* ���M�J�n							                    */
	/********************************************************/
	i_ret = M_AP_nobc_ccsds_sndCtrl( d_IF_BORD1, 1 );
	if(i_ret != 0){
		return (-600 + i_ret);
	}
	
	return (i_ret);
}


//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof CCSDS_CONFIG_STRUCT
 * @protected
 * @brief CCSDS_CONFIG�\���̂ɂĎw�肳�ꂽch����f�[�^����M���܂��B
 * @param void *my_ccsds_v : �ΏۂƂ���CCSDS_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : ��M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ��M�f�[�^�i�[��̃f�[�^�T�C�Y
 * @return 0 : ��M�f�[�^�Ȃ�
 * @return ���� : ��M�f�[�^�o�C�g��
 * @return -100�ԑ� : �ُ�I��(�ڍׂ�-100���� M_AP_nobc_ccsds_getRcvData() �̃G���[�X�e�[�^�X�̒l���Q��)
 * @return ��L�ȊO : �ُ�I��(�ڍׂ� M_AP_nobc_ccsds_getRcvData() �̖߂�l���Q��)
 * @note �߂�l�́u��M�f�[�^�o�C�g���v�́A���ۂɎ�M�����f�[�^�o�C�g������ԋ߂�4�̔{���ɐ؂�グ���l�ƂȂ�(�~�h���E�G�A�̎d�l�̂���)
 */
int		CCSDS_RX(void *my_ccsds_v, void *data_v, int count){
	CCSDS_CONFIG_STRUCT *my_ccsds = (CCSDS_CONFIG_STRUCT *)my_ccsds_v;
	unsigned char *data = (unsigned char *)data_v;
    int				i_ret = 0;
	unsigned int	ret_count;
    unsigned int 	error;
	
	ccsds_rcvBuff.ui_bufSize = count;
    ccsds_rcvBuff.vp_add = (void*)data;
    ccsds_rcvBuff.uip_dataSize = &ret_count;
	
	i_ret = M_AP_nobc_ccsds_getRcvData( d_IF_BORD1, &error, ccsds_rcvBuff );
	if(i_ret < 0){
		if(i_ret == -100){
			i_ret -= error;
		}
		return (i_ret);
	}
	
	return	ret_count;
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof CCSDS_CONFIG_STRUCT
 * @protected
 * @brief CCSDS_CONFIG�\���̂ɂĎw�肳�ꂽch�փf�[�^�𑗐M���܂��B
 * @param void *my_ccsds_v : �ΏۂƂ���CCSDS_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : ���M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ���M�f�[�^�T�C�Y
 * @return 0 : ����I��
 * @return -100 : ���M�f�[�^�o�C�g���I�[�o�[
 * @return ��L�ȊO : �ُ�I��(�ڍׂ� M_AP_nobc_ccsds_sndHkVcdu() �̖߂�l���Q��)
 */
int		CCSDS_TX(void *my_ccsds_v, void *data_v, int count){
	CCSDS_CONFIG_STRUCT *my_ccsds = (CCSDS_CONFIG_STRUCT *)my_ccsds_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
    int		i;
	
	if(count > sizeof(ccsds_ms_send_buf)){
		return (-100);
	}
	
	for(i = 0; i < count; i++){
		ccsds_ms_send_buf[i] = data[i];
	}
	for(; i < sizeof(ccsds_ms_send_buf); i++){
		ccsds_ms_send_buf[i] = 0x00;
	}
	
	/*i_ret += */M_AP_set_RefBuffInfo(&ms_vcdu_t_buf, ccsds_ms_send_buf, sizeof(ccsds_ms_send_buf));
	
	i_ret += M_AP_nobc_ccsds_sndMsVcdu( d_IF_BORD1, ms_vcdu_t_buf );
	
	/////*i_ret += */M_AP_set_RefBuffInfo(&hk_vcdu_t_buf, data, (unsigned int)count);
	////
	////i_ret += M_AP_nobc_ccsds_sndHkVcdu( d_IF_BORD1, hk_vcdu_t_buf );
	
	return (i_ret);
}
