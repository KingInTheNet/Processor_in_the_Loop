/**
 * @file AD590.c
 * @brief AD590�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * AD590�C���^�[�t�F�[�X���W���[���́AAnalog Devices��AD590�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2013.10.24
 */

#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "AD590.h"

//#define	AD590_DEBUG


int		AD590_Data_Conv(AD590_STRUCT *my_ad590);

#define AD590_RX_FRAME_SIZE		(2 * AD590_NUMBER)	/**< @brief ��M�t���[���̒���(2�o�C�g x �|�[�g��)*/

//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof AD590_STRUCT
 * @public
 * @brief AD590�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA AD590_STRUCT.driver_super �ɒ����M���̃w�b�_,�t�b�^,�t���[���T�C�Y�A����R�}���h���s���̏����L�^���܂��B
 * @note AD590�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param AD590_STRUCT *my_ad590 : ����������AD590�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 100�ԑ� : �ُ�I��(�ڍׂ� DRIVER_Super_init() �̖߂�l���Q��)
 */
int		AD590_init(AD590_STRUCT *my_ad590){
	int		i;
	int		i_ret;
	
	my_ad590->pa_config.ch = (0x00000001 << AD590_NUMBER) - 1;
	
	my_ad590->driver_super.inter_face = PA;
	
	my_ad590->driver_super.periodic_config.rx_header_size = 0;
	
	my_ad590->driver_super.periodic_config.rx_footer_size = 0;
	
	my_ad590->driver_super.periodic_config.rx_frame_size = AD590_RX_FRAME_SIZE;
	
	my_ad590->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_ad590->driver_super), &(my_ad590->pa_config))) != 0){	// Error
		return(i_ret);
	}
	
	return(i_ret);
}

/**
 * @memberof AD590_STRUCT
 * @public
 * @brief AD590�ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * 
 * �{AD590�͒���R�}���h���M���s�v�Ȃ̂ŁA���̊֐��͎��s���Ă������N���܂���
 * @param AD590_STRUCT *my_ad590 : �ΏۂƂ���AD590�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_cycle() �̖߂�l���Q��)
 */
int		AD590_cycle(AD590_STRUCT* my_ad590){
	int		i_ret;
	
		#ifdef	AD590_DEBUG
			Printf("AD590: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_ad590->driver_super), &(my_ad590->pa_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof AD590_STRUCT
 * @public
 * @brief AD590����̓d���l���擾���A���̒l�����x[��]�ɕϊ��� AD590_STRUCT �Ɋi�[���܂��B
 * 
 * ���䑤�ŕK�v�Ƃ�������Œ���I�Ɏ��s���Ă��������B
 * @param AD590_STRUCT *my_ad590 : �ΏۂƂ���AD590�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		AD590_rec(AD590_STRUCT* my_ad590){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_ad590->driver_super), &(my_ad590->pa_config));
	if(i_ret == 1){
			#ifdef	AD590_DEBUG
				Printf("AD590: *** Frame ***\n");
			#endif
		AD590_Data_Conv(my_ad590);
	}
	
	return(i_ret);
}

/**
 * @memberof AD590_STRUCT
 * @public
 * @brief AD590�\���̂̃f�[�^���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param AD590_STRUCT *my_ad590 : �ΏۂƂ���AD590�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		AD590_debug_message(AD590_STRUCT* my_ad590){
	Printf("CH00:%d  ", my_ad590->tempe[0]);
	Printf("CH01:%d  ", my_ad590->tempe[1]);
	Printf("CH02:%d  ", my_ad590->tempe[2]);
	Printf("CH03:%d  ", my_ad590->tempe[3]);
	Printf("\n");
	Printf("CH04:%d  ", my_ad590->tempe[4]);
	Printf("CH05:%d  ", my_ad590->tempe[5]);
	Printf("CH06:%d  ", my_ad590->tempe[6]);
	Printf("CH07:%d  ", my_ad590->tempe[7]);
	Printf("\n");
	Printf("CH08:%d  ", my_ad590->tempe[8]);
	Printf("CH09:%d  ", my_ad590->tempe[9]);
	Printf("CH10:%d  ", my_ad590->tempe[10]);
	Printf("CH11:%d  ", my_ad590->tempe[11]);
	Printf("\n");
	Printf("CH12:%d  ", my_ad590->tempe[12]);
	Printf("CH13:%d  ", my_ad590->tempe[13]);
	Printf("CH14:%d  ", my_ad590->tempe[14]);
	Printf("CH15:%d  ", my_ad590->tempe[15]);
	
	//DRIVER_Super_debug_message(&(my_ad590->driver_super));
	
	
	return(0);
}

//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof AD590_STRUCT
 * @private
 * @brief �t���[���f�[�^��AD590�\���̂̃f�[�^���e�ɕϊ����܂��B
 * 
 * �H�w�l�ϊ����K�v�ȏꍇ�͂����ɏ������݂܂��B
 * @param AD590_STRUCT *my_ad590 : �ΏۂƂ���AD590�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		AD590_Data_Conv(AD590_STRUCT *my_ad590){
	/** @brief �t���[���f�[�^�̃w�b�_�����I�t�Z�b�g�����|�C���^*/
	short *ad590_rx_data = (short *)(my_ad590->driver_super.periodic_rx_frame + 0);
	int	i;
	
	
	for(i = 0; i < AD590_NUMBER; i++){
		my_ad590->tempe[i] = *(ad590_rx_data + i);
	}
	
	
	return (0);
}
