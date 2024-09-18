/**
 * @file MOBC.c
 * @brief MOBC�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * MOBC�C���^�[�t�F�[�X���W���[���́AMHI��MOBC�Ƃ̃C���^�[�t�F�[�X���������A
 * �f�[�^�擾�E�R�}���h���M���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.11.01
 */

#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "MOBC.h"

//#define	MOBC_DEBUG


//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof MOBC_STRUCT
 * @public
 * @brief MOBC�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * @note MOBC�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param MOBC_STRUCT *my_mobc : ����������MOBC�\���̂ւ̃|�C���^
 * @param unsigned char ch : MOBC���ڑ�����Ă���UART�|�[�g�ԍ�
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� RS422_init() �̖߂�l���Q��)
 */
int MOBC_init(MOBC_STRUCT *my_mobc, unsigned char ch){
	int		i_ret;
	unsigned char	init_data[4] = {0x55, 0xAA, 0x55, 0xAA};
	
	my_mobc->rs422_config.ch = ch;
	my_mobc->rs422_config.baudrate = 115200;
	my_mobc->rs422_config.stop_bit = 1;
	
	if((i_ret = RS422_init(&(my_mobc->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	// ��������ɉ����f�[�^�𑗐M���Ȃ��Ƒ����Łu�t���[�~���O�G���[�v���o�������ɂȂ邽�ߓ��ꂽ
	MOBC_RS422_Data_Send(my_mobc, init_data, sizeof(init_data));
	
	return(0);
}

/**
 * @memberof MOBC_STRUCT
 * @public
 * @brief MOBC��RS422�f�[�^�𑗐M���܂�
 * 
 * RS422_TX() ���Ăяo���ăf�[�^�𑗐M���܂��B
 * @param MOBC_STRUCT *my_mobc : �ΏۂƂ���MOBC�\���̂ւ̃|�C���^
 * @param void *data_v : ���M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ���M�f�[�^�T�C�Y
 * @return 0 : ����I��
 * @return ��L�ȊO : �ُ�I��(�ڍׂ� RS422_TX() �̖߂�l���Q��)
 */
int MOBC_RS422_Data_Send(MOBC_STRUCT *my_mobc, void *data_v, int size){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	
	if((i_ret = RS422_TX(&my_mobc->rs422_config, data_v, size)) != 0){
		return (i_ret);
	}
	
	return (0);
}

/**
 * @memberof MOBC_STRUCT
 * @public
 * @brief MOBC����RS422�f�[�^����M���܂�
 * 
 * RS422_RX() ���Ăяo���ăf�[�^����M���܂��B
 * @param MOBC_STRUCT *my_mobc : �ΏۂƂ���MOBC�\���̂ւ̃|�C���^
 * @param void *data_v : ��M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ��M�f�[�^�i�[��̃f�[�^�T�C�Y
 * @return 0 : ��M�f�[�^�Ȃ�
 * @return ���� : ��M�f�[�^�o�C�g��
 * @return ��L�ȊO : �ُ�I��(�ڍׂ� RS422_RX() �̖߂�l���Q��)
 * @note �߂�l�́u��M�f�[�^�o�C�g���v�́A���ۂɎ�M�����f�[�^�o�C�g������ԋ߂�4�̔{���ɐ؂�グ���l�ƂȂ�(�~�h���E�G�A�̎d�l�̂���)
 */
int MOBC_RS422_Data_Receive(MOBC_STRUCT *my_mobc, void *data_v, int size){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	
	if((i_ret = RS422_RX(&my_mobc->rs422_config, data_v, size)) < 0){
		return (i_ret);
	}
	
	return (i_ret);
}

//*****************************************************************************
//	�������W���[��
//*****************************************************************************
