/**
 * @file RS422.c
 * @brief RS422(UART)�ʐM���b�p�[�̃N���X�ł��B(AOBC�p)
 * 
 * RS422(UART)�ʐM���b�p�[�́A
 * RS422�̃C���^�[�t�F�[�X���������A
 * RS422�|�[�g�̏������A�f�[�^���M�A�f�[�^��M���s���A
 * RS422�ʐM���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @note RS422(UART)�̃`�����l����ch0�`21����A����͂��̂���ch0�`16�̌v16ch���O���֏o�Ă��܂��B
 * @author ���� �@���Y
 * @date 2013.08.07
 */

/* �C���N���[�h�t�@�C���錾 */
#include "t_services.h"        		/* TOPPERS�p�w�b�_�t�@�C��              */
#include "kernel_id.h"
#include "../source/mw_header.h"	/* �~�h���E�F�A�p�w�b�_�t�@�C��         */
#include "IF_Board_Number.h"

#include "RS422.h"

#define UART_RING_SIZE 1024
#define UART_DOUBLE_SIZE 512

/* �ϐ���` */
M_T_COM_REF_BUFF    t_sendData[16];						/**< @brief ���M�f�[�^���ݒ�p*/
unsigned char		doub_send[16][2][UART_DOUBLE_SIZE];	/**< @brief ���M�f�[�^�p�_�u���o�b�t�@*/
int					doub_send_num[16][2];				/**< @brief ���M�f�[�^�p�_�u���o�b�t�@�g�p��*/
unsigned char		doub_send_new[16];					/**< @brief �ŐV�̃f�[�^�̓��������M�f�[�^�_�u���o�b�t�@�ԍ�*/

M_T_COM_SET_BUFF    t_rcvBuff[16];						/**< @brief ��M�f�[�^���ݒ�p*/
unsigned char		temp_rcv[16][UART_RING_SIZE];		/**< @brief ��M�f�[�^�p�ꎞ�o�b�t�@*/
unsigned int		ret_count[16];						/**< @brief ��M�f�[�^�̃o�C�g���i�[�p*/
unsigned int 		error[16];							/**< @brief �f�[�^��M���̃G���[�X�e�[�^�X�i�[�p*/
unsigned char		ring_rcv[16][UART_RING_SIZE];		/**< @brief ��M�f�[�^�p�����O�o�b�t�@*/
int					ring_rcv_head[16];					/**< @brief ��M�f�[�^�p�����O�o�b�t�@�擪�ꏊ*/
int					ring_rcv_foot[16];					/**< @brief ��M�f�[�^�p�����O�o�b�t�@�I�[�ꏊ*/
int					ring_rcv_num[16];					/**< @brief ��M�f�[�^�p�����O�o�b�t�@�g�p��*/


typedef struct{
	int	from;
	int	to;
}BankChMap;
#define RS422_BANK_NUM (5)
static const BankChMap	bcmap_[RS422_BANK_NUM] = {{0, 1}, {2, 3}, {4, 11}, {12, 13}, {14, 15}};


//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof RS422_CONFIG_STRUCT
 * @protected
 * @brief RS422_CONFIG�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * @note RS422�ʐM���b�p�[�̃N���X���g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @warning ���̊֐������s����O��RS422_CONFIG�\���̓��̐ݒ�l��ݒ肵�Ă����K�v������܂��B
 * @param void *my_rs422_v : ����������RS422_CONFIG�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return -100 : UART�`�����l���ԍ��s��
 * @return -200 : �{�[���[�g�ݒ�l�s��
 * @return -300 : �X�g�b�v�r�b�g�l�s��
 * @return -400�ԑ� : �ُ�I��(�ڍׂ�+400������ M_AP_nobc_uart_ctrl() �̖߂�l���Q��)
 * @return -500�ԑ� : �ُ�I��(�ڍׂ�+500������ M_AP_nobc_uart_sndTrigger() �̖߂�l���Q��)
 */
int	RS422_init(void *my_rs422_v){
	RS422_CONFIG_STRUCT	*my_rs422 = (RS422_CONFIG_STRUCT *)my_rs422_v;
	int					i_ret = 0;
	unsigned int		rate;
	unsigned char		stop;
	
	
	if((my_rs422->ch < 0) || (my_rs422->ch > 15)){
		return (-100);
	}
	
	
	M_AP_set_SetBuffInfo(&t_rcvBuff[my_rs422->ch], temp_rcv[my_rs422->ch], UART_RING_SIZE, &ret_count[my_rs422->ch]);
	
	doub_send_num[my_rs422->ch][0] = 0;
	doub_send_num[my_rs422->ch][1] = 0;
	doub_send_new[my_rs422->ch] = 0;
	ring_rcv_head[my_rs422->ch] = 0;
	ring_rcv_foot[my_rs422->ch] = 0;
	ring_rcv_num[my_rs422->ch] = 0;
	
	
	if(my_rs422->baudrate == 4800){
		rate = M_d_SIO_BPS_4800;
	}else if(my_rs422->baudrate == 9600){
		rate = M_d_SIO_BPS_9600;
	}else if(my_rs422->baudrate == 14400){
		rate = M_d_SIO_BPS_14400;
	}else if(my_rs422->baudrate == 19200){
		rate = M_d_SIO_BPS_19200;
	}else if(my_rs422->baudrate == 38400){
		rate = M_d_SIO_BPS_38400;
	}else if(my_rs422->baudrate == 57600){
		rate = M_d_SIO_BPS_57600;
	}else if(my_rs422->baudrate == 115200){
		rate = M_d_SIO_BPS_115200;
	}else{
		return (-200);
	}
	
	//�f�[�^��8�A�p���e�B�Ȃ��A�X�g�b�v�r�b�g��1 �� "8"
	//�f�[�^��8�A�p���e�B�Ȃ��A�X�g�b�v�r�b�g��2 �� "0"
	if(my_rs422->stop_bit == 1){
		stop = 8;
	}else if(my_rs422->stop_bit == 2){
		stop = 0;
	}else{
		return (-300);
	}
	
	
	/********************************************************/
	/* �|�[�g�ݒ�						                    */
	/********************************************************/
	/*  ���ݒ� �ʐM���[�g�A�f�[�^��,�p���e�B,�X�g�b�v�r�b�g  */
	////if((my_rs422->ch >= 0) && (my_rs422->ch <= 7)){
		i_ret = M_AP_nobc_uart_ctrl( d_IF_BORD1, my_rs422->ch, rate, stop, 7, 0 );
		if(i_ret != 0){
			return (-400 + i_ret);
		}
	////}else if((my_rs422->ch >= 8) && (my_rs422->ch <= 15)){
	////	i_ret = M_AP_nobc_uart_ctrl( d_IF_BORD1, (my_rs422->ch + 4), rate, stop, 7, 0 );
	////	if(i_ret != 0){
	////		return (-400 + i_ret);
	////	}
	////}
	/********************************************************/
	/* ���M�ݒ�						                       */
	/* �f�[�^�i�[��A�����M�������ꍇ                       */
	/********************************************************/
	/*  ��DMA���{�ݒ�       */
	////if((my_rs422->ch >= 0) && (my_rs422->ch <= 7)){
		i_ret = M_AP_nobc_uart_sndTrigger( d_IF_BORD1, my_rs422->ch, M_d_SIO_SEND_TRG_SET );
		if(i_ret != 0){
			return (-500 + i_ret);
		}
	////}else if((my_rs422->ch >= 8) && (my_rs422->ch <= 15)){
	////	i_ret = M_AP_nobc_uart_sndTrigger( d_IF_BORD1, (my_rs422->ch + 4), M_d_SIO_SEND_TRG_SET );
	////	if(i_ret != 0){
	////		return (-500 + i_ret);
	////	}
	////}
	return (i_ret);
}


int		RS422_RX_wai_sem(int	ch){
	switch(ch){
		case 0:
			wai_sem(RS422_RX_00_SEM);
		break;
		
		case 1:
			wai_sem(RS422_RX_01_SEM);
		break;
		
		case 2:
			wai_sem(RS422_RX_02_SEM);
		break;
		
		case 3:
			wai_sem(RS422_RX_03_SEM);
		break;
		
		case 4:
			wai_sem(RS422_RX_04_SEM);
		break;
		
		case 5:
			wai_sem(RS422_RX_05_SEM);
		break;
		
		case 6:
			wai_sem(RS422_RX_06_SEM);
		break;
		
		case 7:
			wai_sem(RS422_RX_07_SEM);
		break;
		
		case 8:
			wai_sem(RS422_RX_08_SEM);
		break;
		
		case 9:
			wai_sem(RS422_RX_09_SEM);
		break;
		
		case 10:
			wai_sem(RS422_RX_10_SEM);
		break;
		
		case 11:
			wai_sem(RS422_RX_11_SEM);
		break;
		
		case 12:
			wai_sem(RS422_RX_12_SEM);
		break;
		
		case 13:
			wai_sem(RS422_RX_13_SEM);
		break;
		
		case 14:
			wai_sem(RS422_RX_14_SEM);
		break;
		
		case 15:
			wai_sem(RS422_RX_15_SEM);
		break;
		
		default:
			return (-1);
		break;
	}
	
	return (0);
}

int		RS422_RX_sig_sem(int	ch){
	switch(ch){
		case 0:
			sig_sem(RS422_RX_00_SEM);
		break;
		
		case 1:
			sig_sem(RS422_RX_01_SEM);
		break;
		
		case 2:
			sig_sem(RS422_RX_02_SEM);
		break;
		
		case 3:
			sig_sem(RS422_RX_03_SEM);
		break;
		
		case 4:
			sig_sem(RS422_RX_04_SEM);
		break;
		
		case 5:
			sig_sem(RS422_RX_05_SEM);
		break;
		
		case 6:
			sig_sem(RS422_RX_06_SEM);
		break;
		
		case 7:
			sig_sem(RS422_RX_07_SEM);
		break;
		
		case 8:
			sig_sem(RS422_RX_08_SEM);
		break;
		
		case 9:
			sig_sem(RS422_RX_09_SEM);
		break;
		
		case 10:
			sig_sem(RS422_RX_10_SEM);
		break;
		
		case 11:
			sig_sem(RS422_RX_11_SEM);
		break;
		
		case 12:
			sig_sem(RS422_RX_12_SEM);
		break;
		
		case 13:
			sig_sem(RS422_RX_13_SEM);
		break;
		
		case 14:
			sig_sem(RS422_RX_14_SEM);
		break;
		
		case 15:
			sig_sem(RS422_RX_15_SEM);
		break;
		
		default:
			return (-1);
		break;
	}
	
	return (0);
}


int		RS422_TX_bank(int bank_id){
	int i;
	int i_ret = 0;
	
	
	for(i = bcmap_[bank_id].from; i <= bcmap_[bank_id].to; i++){
		if((doub_send_num[i][0] == 0) && (doub_send_num[i][1] == 0)){
			// ���M�_�u���o�b�t�@�������Ƃ���̎�
			M_AP_set_RefBuffInfo(&(t_sendData[i]), &(doub_send[i][doub_send_new[i]]), doub_send_num[i][doub_send_new[i]]);
			doub_send_num[i][doub_send_new[i]] = 0;
		}else if((doub_send_num[i][0] != 0) && (doub_send_num[i][1] != 0)){
			// ���M�_�u���o�b�t�@�������Ƃ��g�p���Ă��鎞
			M_AP_set_RefBuffInfo(&(t_sendData[i]), &(doub_send[i][(doub_send_new[i])^1]), doub_send_num[i][(doub_send_new[i])^1]);
			doub_send_num[i][(doub_send_new[i])^1] = 0;
		}else{
			// ���M�_�u���o�b�t�@��Е������g�p���Ă��鎞
			M_AP_set_RefBuffInfo(&(t_sendData[i]), &(doub_send[i][doub_send_new[i]]), doub_send_num[i][doub_send_new[i]]);
			doub_send_num[i][doub_send_new[i]] = 0;
		}
	}
	
	i_ret = M_AP_nobc_uart_SndDataBank(d_IF_BORD1, bank_id, &t_sendData[bcmap_[bank_id].from]);
	if(i_ret != 0){
		return (i_ret - 1000);
	}
	
	return (i_ret);
}

int		RS422_RX_bank(int bank_id){
	int i, j;
	int i_ret = 0;
	int full_flg = 0;
	
	
	/*
	for(i = bcmap_[bank_id].from; i <= bcmap_[bank_id].to; i++){
		// �i�[�����O�o�b�t�@�������ς��̎�
		if(ring_rcv_num[i] == UART_RING_SIZE){
			return (-2000 - i);
		}
	}
	*/
	
	i_ret = M_AP_nobc_uart_getRcvDataBank(d_IF_BORD1, bank_id, &error[bcmap_[bank_id].from], &t_rcvBuff[bcmap_[bank_id].from]);
	if((i_ret != 0) && (i_ret != -100)){	// �u�ʐM�G���[�v�ȊO�̃G���[�̎�
		return (i_ret - 3000);
	}else{	// �u�ʐM�G���[�v�������́u����I���v�̎�
		for(i = bcmap_[bank_id].from; i <= bcmap_[bank_id].to; i++){
			if(error[i] == 0){
				for(j = 0; j < ret_count[i]; j++){
					// �i�[�����O�o�b�t�@�������ς��̎�
					if(ring_rcv_num[i] == UART_RING_SIZE){
						full_flg++;
						break;
					}
					
					if(ring_rcv_foot[i] == UART_RING_SIZE){
						ring_rcv_foot[i] = 0;
					}
					ring_rcv[i][ring_rcv_foot[i]] = temp_rcv[i][j];
					ring_rcv_foot[i]++;
					// ��������s���������A�ǂ����r�����䂵�Ă����Ȃ���ring_rcv_num[]�̒l������邱�Ƃ�����
					RS422_RX_wai_sem(i);
					ring_rcv_num[i]++;
					RS422_RX_sig_sem(i);
				}
			}
		}
	}
	
	if(i_ret == -100){	// �u�ʐM�G���[�v�̎�
		if(full_flg != 0){	// ���A�i�[�����O�o�b�t�@�������ς��̎�
			return (i_ret - 3000 - 2000);
		}else{	// �u�ʐM�G���[�v�݂̂̎�
			return (i_ret - 3000);
		}
	}else{	// �u����I���v�̎�
		if(full_flg != 0){	// ���A�i�[�����O�o�b�t�@�������ς��̎�
			return (i_ret - 2000);
		}
	}
	
	return (i_ret);
}


//***************************************************
//	Middlewear TRX
//***************************************************
/**
 * @brief RS422�̃f�[�^�𑗐M�����O�o�b�t�@��著�M���A��M�����f�[�^����M�����O�o�b�t�@�Ɋi�[���܂��B
 * @param unsigned char call_counter : �Ăяo���񐔎w��
 * @return 0 : ����I��
 * @return -?1000�ԑ� : �ُ�I��(�ڍׂ�+1000���� M_AP_nobc_uart_SndDataBank() �̖߂�l���Q��)
 * @return -?2000�ԑ� : �ǂ�����CH�̎�M�o�b�t�@�������ς�
 * @return -?3000�ԑ� : �ُ�I��(�ڍׂ�+3000���� M_AP_nobc_uart_GetRcvDataBank() �̖߂�l���Q��)
 * @note �u?�v�ُ͈�̔�������Bank�ԍ�
 * @note �K��5msec�����ɌĂԂ���
 */
int		RS422_Middlewear_TRX(unsigned char call_counter){
	int		i_ret = 0;
	
	
	call_counter %= 200;	// 1sec����
	
	//////// ���M���� ////////
	if((call_counter % 10) == 1){	// 50msec��1��,�ʑ���1�̎�
		// Bank0�̑��M�������s��
		i_ret = RS422_TX_bank(0);
		if(i_ret != 0){
			return (i_ret - 0);
		}
	}
	
	if((call_counter % 100) == 17){	// 500msec��1��,�ʑ���17�̎�
		// Bank1�̑��M�������s��
		i_ret = RS422_TX_bank(1);
		if(i_ret != 0){
			return (i_ret - 10000);
		}
	}
	
	if((call_counter % 10) == 3){	// 50msec��1��,�ʑ���3�̎�
		// Bank2�̑��M�������s��
		i_ret = RS422_TX_bank(2);
		if(i_ret != 0){
			return (i_ret - 20000);
		}
	}
	
	if((call_counter % 100) == 27){	// 500msec��1��,�ʑ���27�̎�
		// Bank3�̑��M�������s��
		i_ret = RS422_TX_bank(3);
		if(i_ret != 0){
			return (i_ret - 30000);
		}
	}
	
	if((call_counter % 100) == 37){	// 500msec��1��,�ʑ���37�̎�
		// Bank4�̑��M�������s��
		i_ret = RS422_TX_bank(4);
		if(i_ret != 0){
			return (i_ret - 40000);
		}
	}
	
	
	
	
	//////// ��M���� ////////
	if((call_counter % 20) == 5){	// 100msec��1��,�ʑ���5�̎�
		// Bank0�̎�M�������s��
		i_ret = RS422_RX_bank(0);
		if(i_ret != 0){
			return (i_ret - 0);
		}
	}
	
	if((call_counter % 100) == 57){	// 500msec��1��,�ʑ���57�̎�
		// Bank1�̎�M�������s��
		i_ret = RS422_RX_bank(1);
		if(i_ret != 0){
			return (i_ret - 10000);
		}
	}
	
	if((call_counter % 8) == 0){	// 40msec��1��,�ʑ���0�̎�
		// Bank2�̎�M�������s��
		i_ret = RS422_RX_bank(2);
		if(i_ret != 0){
			return (i_ret - 20000);
		}
	}
	
	if((call_counter % 100) == 67){	// 500msec��1��,�ʑ���67�̎�
		// Bank3�̎�M�������s��
		i_ret = RS422_RX_bank(3);
		if(i_ret != 0){
			return (i_ret - 30000);
		}
	}
	
	if((call_counter % 100) == 77){	// 500msec��1��,�ʑ���77�̎�
		// Bank4�̎�M�������s��
		i_ret = RS422_RX_bank(4);
		if(i_ret != 0){
			return (i_ret - 40000);
		}
	}
	
	
	return(i_ret);
}


//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof RS422_CONFIG_STRUCT
 * @protected
 * @brief RS422_CONFIG�\���̂ɂĎw�肳�ꂽch����f�[�^����M���܂��B
 * @param void *my_rs422_v : �ΏۂƂ���RS422_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : ��M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ��M�f�[�^�i�[��̃f�[�^�T�C�Y
 * @return 0 : ��M�f�[�^�Ȃ�
 * @return 0�ȊO : ��M�f�[�^�o�C�g��
 * @note �߂�l�́u��M�f�[�^�o�C�g���v�́A���ۂɎ�M�����f�[�^�o�C�g������ԋ߂�4�̔{���ɐ؂�グ���l�ƂȂ�(�~�h���E�G�A�̎d�l�̂���)
 */
int		RS422_RX(void *my_rs422_v, void *data_v, int count){
	RS422_CONFIG_STRUCT	*my_rs422 = (RS422_CONFIG_STRUCT *)my_rs422_v;
	unsigned char	*data = (unsigned char *)data_v;
	int				i_ret = 0;
	int				i;
	
	
	if(ring_rcv_num[my_rs422->ch] == 0){	// �i�[�����O�o�b�t�@����̎�(������M���ĂȂ���)
		return (i_ret);
	}
	
	for(i = 0; 0 < ring_rcv_num[my_rs422->ch]; i++){
		if((count - i) <= 0){
			return (i);
		}
		
		if(ring_rcv_head[my_rs422->ch] == UART_RING_SIZE){
			ring_rcv_head[my_rs422->ch] = 0;
		}
		
		data[i] = ring_rcv[my_rs422->ch][ring_rcv_head[my_rs422->ch]];
		ring_rcv_head[my_rs422->ch]++;
		// ��������s���������A�ǂ����r�����䂵�Ă����Ȃ���ring_rcv_num[]�̒l������邱�Ƃ�����
		RS422_RX_wai_sem((int)(my_rs422->ch));
		ring_rcv_num[my_rs422->ch]--;
		RS422_RX_sig_sem((int)(my_rs422->ch));
	}
	
	
	return (i);
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof RS422_CONFIG_STRUCT
 * @protected
 * @brief RS422_CONFIG�\���̂ɂĎw�肳�ꂽch�փf�[�^�𑗐M���܂��B
 * @param void *my_rs422_v : �ΏۂƂ���RS422_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : ���M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ���M�f�[�^�T�C�Y
 * @return 0 : ����I��
 * @return -1 : ���M�f�[�^�T�C�Y���傫������
 * @return -2 : ���M�o�b�t�@�������ς�
 */
int		RS422_TX(void *my_rs422_v, void *data_v, int count){
	RS422_CONFIG_STRUCT	*my_rs422 = (RS422_CONFIG_STRUCT *)my_rs422_v;
	unsigned char	*data = (unsigned char *)data_v;
	int		i_ret = 0;
	int		i;
	unsigned char	page;
	
	if((my_rs422->ch >= 4) && (my_rs422->ch <= 11)){	//Bank2
		if(count > 128){
			return (-1);
		}
	}else{
		if(count > 512){
			return (-1);
		}
	}
	
	if((doub_send_num[my_rs422->ch][0] != 0) && (doub_send_num[my_rs422->ch][1] != 0)){	// ���M�_�u���o�b�t�@�������Ƃ��g�p���Ă��鎞
		return (-2);
	}
	
	if((doub_send_num[my_rs422->ch][0] == 0) && (doub_send_num[my_rs422->ch][1] == 0)){	// ���M�_�u���o�b�t�@�������Ƃ���̎�
		for(i = 0; i < count; i++){
			doub_send[my_rs422->ch][0][i] = data[i];
		}
		doub_send_new[my_rs422->ch] = 0;
		doub_send_num[my_rs422->ch][0] = count;
	}else{	// ���M�_�u���o�b�t�@��Е������g�p���Ă��鎞
		page = doub_send_new[my_rs422->ch] ^ 1;
		for(i = 0; i < count; i++){
			doub_send[my_rs422->ch][page][i] = data[i];
		}
		doub_send_new[my_rs422->ch] = page;
		doub_send_num[my_rs422->ch][page] = count;
	}
	
	return (i_ret);
}
