/**
 * @file MOBC.h
 * @brief MOBC�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * MOBC�C���^�[�t�F�[�X���W���[���́AMHI��MOBC�Ƃ̃C���^�[�t�F�[�X���������A
 * �f�[�^�擾�E�R�}���h���M���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.11.01
 */

#ifndef	MOBC_INCLUDE_
#define	MOBC_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"


/**
 * @class MOBC_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief MOBC�̏����i�[����\���̂ł��B
 * 
 * MOBC1��ɑ΂��āA1�̃O���[�o���C���X�^���X�Ƃ��Ē�`���܂��B
 *  MOBC_init() �ɂ�菉�������Ďg�p���܂��B
 */
typedef	struct {
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422�N���X�̍\����*/
}	MOBC_STRUCT;


int MOBC_init(MOBC_STRUCT *my_mobc, unsigned char ch);
int MOBC_RS422_Data_Send(MOBC_STRUCT *my_mobc, void *data_v, int size);
int MOBC_RS422_Data_Receive(MOBC_STRUCT *my_mobc, void *data_v, int size);

#endif // MOBC_INCLUDE_
