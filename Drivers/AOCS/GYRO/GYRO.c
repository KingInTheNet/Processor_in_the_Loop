/**
 * @file GYRO.c
 * @brief GYRO�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * GYRO�C���^�[�t�F�[�X���W���[���́A�����쐸�@�������FOG IRU TA7584�Ƃ̃C���^�[�t�F�[�X���������A
 * �f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2013.10.03
 */

#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "../../../Data_Processing/endian_conv.h"
#include "../../../Data_Processing/exor.h"
#include "../../../Data_Processing/ascii_conv.h"

#include "GYRO.h"

//#define	GYRO_DEBUG


int				GYRO_Data_Conv(GYRO_STRUCT *my_gyro);

#define GYRO_RX_FRAME_SIZE			42	/**< @brief ��M�t���[���̒���*/

static unsigned char	gyro_rx_header[11] = {'$', 'T', 'S', 'C', ',', 'B', 'I', 'N', ',', 0x1C, 0x00};	/**< @brief ��M�t���[���̃w�b�_*/
static unsigned char	gyro_rx_footer[2] = {0x0D, 0x0A};	/**< @brief ��M�t���[���̃t�b�^*/

//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof GYRO_STRUCT
 * @public
 * @brief GYRO�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA GYRO_STRUCT.driver_super �ɒ����M���̃w�b�_,�t�b�^,�t���[���T�C�Y�A����R�}���h���s���̏����L�^���܂��B
 * @note GYRO�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param GYRO_STRUCT *my_gyro : ����������GYRO�\���̂ւ̃|�C���^
 * @param unsigned char ch : GYRO���ڑ�����Ă���UART�|�[�g�ԍ�
 * @return 0 : ����I��
 * @return 100000�ԑ� : �ُ�I��(�ڍׂ�-100000���� AA_init() �̖߂�l���Q��)
 * @return 200000 : �ُ�I��(DRIVER_Super_init() �� AA_init() �̗����ŃG���[����)
 * @return ��L�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_init() �̖߂�l���Q��)
 */
int		GYRO_init(GYRO_STRUCT* my_gyro, unsigned char ch, unsigned char aa_ch_x, unsigned char aa_ch_y, unsigned char aa_ch_z){
    int		i_ret, i_ret2;
	
	my_gyro->rs422_config.ch = ch;
	my_gyro->rs422_config.baudrate = 115200;
	my_gyro->rs422_config.stop_bit = 1;
	
	my_gyro->driver_super.inter_face = RS422;
	
	my_gyro->driver_super.periodic_config.rx_header_size = sizeof(gyro_rx_header);
	my_gyro->driver_super.periodic_config.rx_header = gyro_rx_header;
	
	my_gyro->driver_super.periodic_config.rx_footer_size = sizeof(gyro_rx_footer);
	my_gyro->driver_super.periodic_config.rx_footer = gyro_rx_footer;
	
	my_gyro->driver_super.periodic_config.rx_frame_size = GYRO_RX_FRAME_SIZE;
	
	my_gyro->driver_super.periodic_config.tx_frame_size = 0;
	
	i_ret = DRIVER_Super_init(&(my_gyro->driver_super), &(my_gyro->rs422_config));
	
	
	my_gyro->aa_config.ch = 0;
	my_gyro->aa_config.ch |= (1 << aa_ch_x);
	my_gyro->aa_config.ch |= (1 << aa_ch_y);
	my_gyro->aa_config.ch |= (1 << aa_ch_z);
	
	i_ret2 = AA_init(&(my_gyro->aa_config));
	
	if((i_ret != 0) && (i_ret2 != 0)){
		return(200000);
	}
	
	if(i_ret2 != 0){
		return(100000 + i_ret2);
	}
	
	
	return(i_ret);
}

/**
 * @memberof GYRO_STRUCT
 * @public
 * @brief GYRO�ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * 
 * �{GYRO�͒���R�}���h���M���s�v�Ȃ̂ŁA���̊֐��͎��s���Ă������N���܂���
 * @param GYRO_STRUCT *my_gyro : �ΏۂƂ���GYRO�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_cycle() �̖߂�l���Q��)
 */
int		GYRO_cycle(GYRO_STRUCT *my_gyro){
	int		i_ret;
	
		#ifdef	GYRO_DEBUG
			Printf("GYRO: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_gyro->driver_super), &(my_gyro->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof GYRO_STRUCT
 * @public
 * @brief GYRO����̃f�[�^�p�P�b�g���Ď����A��M�������e�� GYRO_STRUCT �Ɋi�[���܂��B
 * 
 * GYRO�̃f�[�^�o�͎����ł���A20Hz��葁�������Œ���I�Ɏ��s���Ă��������B
 * @note �f�[�^�p�P�b�g�ɂ��Ă� DRIVER_Super_rec() ���g�p���ăt���[���������Ƃ�A
 * �t���[���������Ƃꂽ�ꍇ�Ɏ�M���e�� GYRO_STRUCT �Ɋi�[���܂��B
 * @param GYRO_STRUCT *my_gyro : �ΏۂƂ���GYRO�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
// AA��float�ł͂Ȃ�short�Ŏ擾����悤�ɕύX���� by kkamiya 2013/11/15
int		GYRO_rec(GYRO_STRUCT* my_gyro){
	int		i_ret, i_ret2;
	short	vlt[3];
	
	i_ret = DRIVER_Super_rec(&(my_gyro->driver_super), &(my_gyro->rs422_config));
	if(i_ret == 1){
			#ifdef	GYRO_DEBUG
				Printf("GYRO: *** Frame ***\n");
			#endif
		GYRO_Data_Conv(my_gyro);
	}
	
	AA_RX(&(my_gyro->aa_config), vlt, sizeof(vlt));
	my_gyro->del_x_aa = vlt[0];
	my_gyro->del_y_aa = vlt[1];
	my_gyro->del_z_aa = vlt[2];
	
	return(i_ret);
}

/**
 * @memberof GYRO_STRUCT
 * @public
 * @brief GYRO�\���̂̃f�[�^���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param GYRO_STRUCT *my_gyro : �ΏۂƂ���GYRO�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		GYRO_debug_message(GYRO_STRUCT* my_gyro){
	Printf("Count:%d ", my_gyro->counter);
	Printf("Sts:0x%02X%02X ", my_gyro->status.byte[0], my_gyro->status.byte[1]);
	Printf("DelX:%d ", my_gyro->del_x);
	Printf("DelY:%d ", my_gyro->del_y);
	Printf("DelZ:%d ", my_gyro->del_z);
	//Printf("CurX:%d ", my_gyro->current_x);
	//Printf("CurY:%d ", my_gyro->current_y);
	//Printf("CurZ:%d ", my_gyro->current_z);
	Printf("Tempe:%d ", my_gyro->tempe);
	Printf("DelX_AA:%d ", my_gyro->del_x_aa);
	Printf("DelY_AA:%d ", my_gyro->del_y_aa);
	Printf("DelZ_AA:%d ", my_gyro->del_z_aa);
	
	DRIVER_Super_debug_message(&(my_gyro->driver_super));
	
	
	return(0);
}

//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof GYRO_STRUCT
 * @private
 * @brief �t���[���f�[�^��GYRO�\���̂̃f�[�^���e�ɕϊ����܂��B
 * 
 * ��M�����f�[�^��BCC�̃`�F�b�N���s���A�����������ꍇ�ɂ̂�GYRO�\���̂Ɋi�[���܂��B
 * �H�w�l�ϊ����K�v�ȏꍇ�͂����ɏ������݂܂��B
 * @note BCC�̎Z�o�� exor() ���g�p���čs���Ă��܂��B
 * @note BCC�̃A�X�L�[�R�[�h�̕ϊ��� ascii2hex() ���g�p���čs���Ă��܂��B
 * @note �G���f�B�A���̕ϊ��� endian_conv() ���g�p���čs���Ă��܂��B
 * @param GYRO_STRUCT *my_rw : �ΏۂƂ���GYRO�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 1 : BCC�G���[
 */
int		GYRO_Data_Conv(GYRO_STRUCT *my_gyro){
	/** @brief �t���[���f�[�^�̃w�b�_�����I�t�Z�b�g�����|�C���^*/
	unsigned char	*gyro_rx_data = my_gyro->driver_super.periodic_rx_frame + sizeof(gyro_rx_header);
	int				gyro_conv_tmp_i;
	short			gyro_conv_tmp_s;
	
	gyro_conv_tmp_s = 0x0000;
	gyro_conv_tmp_s |= (gyro_rx_data[27] << 8);
	gyro_conv_tmp_s |= (gyro_rx_data[28] << 0);
	if(ascii2hex((unsigned short)gyro_conv_tmp_s) != exor(&(my_gyro->driver_super.periodic_rx_frame[1]), 36)){
			#ifdef	GYRO_DEBUG
				Printf("GYRO: *** BCC Error ***\n");
			#endif
		return (1);
	}
	
	endian_conv((gyro_rx_data + 0), &(my_gyro->counter), sizeof(my_gyro->counter));
	endian_conv((gyro_rx_data + 4), &(my_gyro->status.byte), sizeof(my_gyro->status.byte));
	
	endian_conv((gyro_rx_data + 6), &gyro_conv_tmp_i, sizeof(gyro_conv_tmp_i));
	//my_gyro->del_x = gyro_conv_tmp_i * (10.0 / 0x80000000);
	my_gyro->del_x = gyro_conv_tmp_i;
	
	endian_conv((gyro_rx_data + 10), &gyro_conv_tmp_i, sizeof(gyro_conv_tmp_i));
	//my_gyro->del_y = gyro_conv_tmp_i * (10.0 / 0x80000000);
	my_gyro->del_y = gyro_conv_tmp_i;
	
	endian_conv((gyro_rx_data + 14), &gyro_conv_tmp_i, sizeof(gyro_conv_tmp_i));
	//my_gyro->del_z = gyro_conv_tmp_i * (10.0 / 0x80000000);
	my_gyro->del_z = gyro_conv_tmp_i;
	
	endian_conv((gyro_rx_data + 18), &gyro_conv_tmp_s, sizeof(gyro_conv_tmp_s));
	//my_gyro->current_x = gyro_conv_tmp_s * (5000.0 / 0x8000);
	my_gyro->current_x = gyro_conv_tmp_s;
	
	endian_conv((gyro_rx_data + 20), &gyro_conv_tmp_s, sizeof(gyro_conv_tmp_s));
	//my_gyro->current_y = gyro_conv_tmp_s * (5000.0 / 0x8000);
	my_gyro->current_y = gyro_conv_tmp_s;
	
	endian_conv((gyro_rx_data + 22), &gyro_conv_tmp_s, sizeof(gyro_conv_tmp_s));
	//my_gyro->current_z = gyro_conv_tmp_s * (5000.0 / 0x8000);
	my_gyro->current_z = gyro_conv_tmp_s;
	
	endian_conv((gyro_rx_data + 24), &gyro_conv_tmp_s, sizeof(gyro_conv_tmp_s));
	//my_gyro->tempe = gyro_conv_tmp_s * (100.0 / 0x8000);
	my_gyro->tempe = gyro_conv_tmp_s;
	
	return (0);
}
