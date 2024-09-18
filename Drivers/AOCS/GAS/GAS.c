/**
 * @file GAS.c
 * @brief GAS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * GAS�C���^�[�t�F�[�X���W���[���́A�e���e�N�j�J��TGA-330�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.08.24
 */

#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "GAS.h"

//#define	GAS_DEBUG


int		GAS_Data_Conv(GAS_STRUCT *my_gas);

#define GAS_RX_FRAME_SIZE		8	/**< @brief ��M�t���[���̒���(2�o�C�g x 4�|�[�g = 8�o�C�g)*/
//#define GAS_RX_FRAME_SIZE		16	/**< @brief ��M�t���[���̒���(4�o�C�g x 4�|�[�g = 16�o�C�g)*/

//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof GAS_STRUCT
 * @public
 * @brief GAS�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA GAS_STRUCT.driver_super �ɒ����M���̃w�b�_,�t�b�^,�t���[���T�C�Y�A����R�}���h���s���̏����L�^���܂��B
 * @note GAS�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param GAS_STRUCT *my_gas : ����������GAS�\���̂ւ̃|�C���^
 * @param unsigned int ch_x : X���̐����ڑ�����Ă���AA�̃|�[�g
 * @param unsigned int ch_y : Y���̐����ڑ�����Ă���AA�̃|�[�g
 * @param unsigned int ch_z : Z���̐����ڑ�����Ă���AA�̃|�[�g
 * @param unsigned int ch_ref : Reference�̐����ڑ�����Ă���AA�̃|�[�g
 * @return 0 : ����I��
 * @return 100�ԑ� : �ُ�I��(�ڍׂ� DRIVER_Super_init() �̖߂�l���Q��)
 */
int		GAS_init(GAS_STRUCT *my_gas, unsigned int ch_x, unsigned int ch_y, unsigned int ch_z, unsigned int ch_ref){
	int		i_ret;
	
	my_gas->aa_config.ch = 0;
	my_gas->aa_config.ch |= (1 << ch_x);
	my_gas->aa_config.ch |= (1 << ch_y);
	my_gas->aa_config.ch |= (1 << ch_z);
	my_gas->aa_config.ch |= (1 << ch_ref);
	
	my_gas->driver_super.inter_face = AA;
	
	my_gas->driver_super.periodic_config.rx_header_size = 0;
	
	my_gas->driver_super.periodic_config.rx_footer_size = 0;
	
	my_gas->driver_super.periodic_config.rx_frame_size = GAS_RX_FRAME_SIZE;
	
	my_gas->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_gas->driver_super), &(my_gas->aa_config))) != 0){	// Error
		return(i_ret);
	}
	
	my_gas->cycle_sum_x = 0;
	my_gas->cycle_sum_y = 0;
	my_gas->cycle_sum_z = 0;
	my_gas->cycle_sum_ref = 0;
	my_gas->cycle_cnt = 0;
	
	return(i_ret);
}

/**
 * @memberof GAS_STRUCT
 * @public
 * @brief GAS�ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * 
 * �{GAS�͒���R�}���h���M���s�v�Ȃ̂ŁA���̊֐��͎��s���Ă������N���܂���
 * @param GAS_STRUCT *my_gas : �ΏۂƂ���GAS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_cycle() �̖߂�l���Q��)
 */
int		GAS_cycle(GAS_STRUCT* my_gas){
	int		i_ret;
	
		#ifdef	GAS_DEBUG
			Printf("GAS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_gas->driver_super), &(my_gas->aa_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof GAS_STRUCT
 * @public
 * @brief GAS����̓d���l���擾���A����AD�ϊ��l�� GAS_STRUCT �Ɋi�[���܂��B
 * 
 * ���䑤�ŕK�v�Ƃ�������Œ���I�Ɏ��s���Ă��������B
 * @param GAS_STRUCT *my_gas : �ΏۂƂ���GAS�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		GAS_rec(GAS_STRUCT* my_gas){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_gas->driver_super), &(my_gas->aa_config));
	if(i_ret == 1){
			#ifdef	GAS_DEBUG
				Printf("GAS: *** Frame ***\n");
			#endif
		GAS_Data_Conv(my_gas);
	}
	
	return(i_ret);
}

/**
 * @memberof GAS_STRUCT
 * @public
 * @brief GAS�\���̂̃f�[�^���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param GAS_STRUCT *my_gas : �ΏۂƂ���GAS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		GAS_debug_message(GAS_STRUCT* my_gas){
	Printf("X:%d ", my_gas->x);
	Printf("Y:%d ", my_gas->y);
	Printf("Z:%d ", my_gas->z);
	Printf("REF:%d ", my_gas->ref);
	
	DRIVER_Super_debug_message(&(my_gas->driver_super));
	
	
	return(0);
}

//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof GAS_STRUCT
 * @private
 * @brief �t���[���f�[�^��GAS�\���̂̃f�[�^���e�ɕϊ����܂��B
 * 
 * �H�w�l�ϊ����K�v�ȏꍇ�͂����ɏ������݂܂��B
 * @param GAS_STRUCT *my_gas : �ΏۂƂ���GAS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
// AA��float�ł͂Ȃ�short�Ŏ擾����悤�ɕύX���� by kkamiya 2013/11/15
int		GAS_Data_Conv(GAS_STRUCT *my_gas){
	/** @brief �t���[���f�[�^�̃w�b�_�����I�t�Z�b�g�����|�C���^*/
	short *gas_rx_data = (short *)(my_gas->driver_super.periodic_rx_frame + 0);
	
	my_gas->ref = *(gas_rx_data + 0);
	my_gas->x = *(gas_rx_data + 1);
	my_gas->y = *(gas_rx_data + 2);
	my_gas->z = *(gas_rx_data + 3);
	/*
	my_gas->cycle_sum_ref += *(gas_rx_data + 0);
	my_gas->cycle_sum_x += *(gas_rx_data + 1);
	my_gas->cycle_sum_y += *(gas_rx_data + 2);
	my_gas->cycle_sum_z += *(gas_rx_data + 3);
	
	my_gas->cycle_cnt++;
	if(my_gas->cycle_cnt == 10){
		my_gas->x = my_gas->cycle_sum_x / 10;
		my_gas->y = my_gas->cycle_sum_y / 10;
		my_gas->z = my_gas->cycle_sum_z / 10;
		my_gas->ref = my_gas->cycle_sum_ref / 10;
		
		my_gas->cycle_sum_x = 0;
		my_gas->cycle_sum_y = 0;
		my_gas->cycle_sum_z = 0;
		my_gas->cycle_sum_ref = 0;
		my_gas->cycle_cnt = 0;
	}
	*/
	return (0);
}
