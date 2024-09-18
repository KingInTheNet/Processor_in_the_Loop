/**
 * @file Driver_Super.c
 * @brief �e����Z���T�E�A�N�`���G�[�^���Ƃ̃C���^�[�t�F�[�X���W���[���Q�̃X�[�p�[�N���X�ł��B
 * 
 * Driver_Super�C���^�[�t�F�[�X���W���[���́A
 * �e����Z���T�E�A�N�`���G�[�^���Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g(���)�A�f�[�^�擾(���)�A�����ݒ�R�}���h�E���X�|���X��M���s���A
 * ���W���[���Q�̃X�[�p�[�N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @date 2013.06.29
 */

#include "utility.h"

#include "Driver_Super.h"

//#define	DRIVER_SUPER_DEBUG

int		DRIVER_SUPER_TX(DRIVER_SUPER_STRUCT *my_super, DRIVER_SUPER_CONFIG_STRUCT *config, void *if_config);
int		DRIVER_SUPER_RX(DRIVER_SUPER_STRUCT *my_super, DRIVER_SUPER_CONFIG_STRUCT *config, void *if_config, unsigned char *frame);
int		DRIVER_SUPER_Analyze(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame);
int		DRIVER_SUPER_Analyze_variable(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame);
int		DRIVER_SUPER_Analyze_variable_not_fsd(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame);


//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief DRIVER_SUPER�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA�\���̓��̏��������K�v�ȕϐ������������܂��B
 * @note Driver_Super�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param DRIVER_SUPER_STRUCT *my_super : ����������DRIVER_SUPER�\���̂ւ̃|�C���^
 * @param void *if_config : �g�p����IF�̐ݒ�l�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� �Ώ�IF_init() �̖߂�l���Q��)
 */
int		DRIVER_Super_init(DRIVER_SUPER_STRUCT *my_super, void *if_config){
    int				i_ret = 0;
	
	if((i_ret = (*IF_init[my_super->inter_face])(if_config)) != 0){	// Error
		return(i_ret);
	}
	
	my_super->tx_count = 0;
	my_super->rx_count = 0;
	my_super->update_flg = 0;
	my_super->cmd_time = 0;
	my_super->update_time = 0;
	
	my_super->periodic_config.rx_frame_count = 0;
	
	// rx_frame_size������(�σf�[�^�o�C�g��)�̎�
	if(my_super->periodic_config.rx_frame_size < 0){
		// �������Ȃ�
	}else{
		my_super->periodic_config.rx_except_footer_size
		 = my_super->periodic_config.rx_frame_size - my_super->periodic_config.rx_footer_size;
	}
	return (0);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief �p����̋@��ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * @note ���̊֐������s����x�� DRIVER_SUPER_STRUCT.update_flg , DRIVER_SUPER_STRUCT.tx_count ���C���N�������g���A
 *  DRIVER_SUPER_STRUCT.cmd_time �Ɏ��s����OBC�������i�[���܂��B
 * @warning ���̊֐������s����O��DRIVER_SUPER�\���̓��̒���R�}���h���M�֌W�̐ݒ�l��ݒ肵�Ă����K�v������܂��B
 * @param DRIVER_SUPER_STRUCT *my_super : �ΏۂƂ���DRIVER_SUPER�\���̂ւ̃|�C���^
 * @param void *if_config : �g�p����IF�̐ݒ�l�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_SUPER_TX() �̖߂�l���Q��)
 */
int		DRIVER_Super_cycle(DRIVER_SUPER_STRUCT *my_super, void *if_config){
	my_super->update_flg++;
	my_super->tx_count++;
	my_super->cmd_time = my_time();
		#ifdef	DRIVER_SUPER_DEBUG
			Printf("DRIVER_SUPER: *** DATA Req. ***\n");
		#endif
	return(DRIVER_SUPER_TX(my_super, &(my_super->periodic_config), if_config));
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief �p����̋@��������M�f�[�^����M���܂��B
 * 
 * �p����̋@��̃f�[�^�o�͎�����葁�������Œ���I�Ɏ��s���Ă��������B
 * @note �f�[�^�ɂ��Ă� DRIVER_SUPER_RX() ���g�p���Ď�M���A���̒��� DRIVER_SUPER_Analyze() ���g�p���ăt���[���������Ƃ�A
 * �t���[���������Ƃꂽ�ꍇ�A DRIVER_SUPER_STRUCT.update_flg ��0�ɃN���A���A 
 *  DRIVER_SUPER_STRUCT.rx_count ���C���N�������g���A DRIVER_SUPER_STRUCT.update_time �ɂ��̎���OBC�������i�[���܂��B
 * @warning ���̊֐������s����O��DRIVER_SUPER�\���̓��̒���f�[�^��M�֌W�̐ݒ�l��ݒ肵�Ă����K�v������܂��B
 * @param DRIVER_SUPER_STRUCT *my_super : �ΏۂƂ���DRIVER_SUPER�\���̂ւ̃|�C���^
 * @param void *if_config : �g�p����IF�̐ݒ�l�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_SUPER_RX() �̖߂�l���Q��)
 */
int		DRIVER_Super_rec(DRIVER_SUPER_STRUCT *my_super, void *if_config){
	int		ret;
	
	if((ret = DRIVER_SUPER_RX(my_super, &(my_super->periodic_config), if_config, my_super->periodic_rx_frame)) == 1){
		my_super->update_flg = 0;
		my_super->rx_count++;
		my_super->update_time = my_time();
	}
	return(ret);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief �p����̋@��������R�}���h�𔭍s���A���̃��X�|���X����M���܂��B
 * 
 * �p����̋@��̃f�[�^�o�͎�����葁�������Œ���I�Ɏ��s���Ă��������B
 * @note ���X�|���X�f�[�^�ɂ��Ă� DRIVER_SUPER_RX() ���g�p���Ď�M���A���̒��� DRIVER_SUPER_Analyze() ���g�p���ăt���[���������Ƃ��Ă��܂��B
 * @warning ���̊֐������s����O��DRIVER_SUPER�\���̓��̔����R�}���h���s�E���X�|���X��M�֌W�̐ݒ�l��ݒ肵�Ă����K�v������܂��B
 * @param DRIVER_SUPER_STRUCT *my_super : �ΏۂƂ���DRIVER_SUPER�\���̂ւ̃|�C���^
 * @param void *if_config : �g�p����IF�̐ݒ�l�\���̂ւ̃|�C���^
 * @return 1 : ����I��
 * @return 0 : �^�C���A�E�g(200msec)
 * @return ��L�ȊO : �f�[�^���s����������(�ڍׂ� DRIVER_SUPER_RX() �̖߂�l���Q��)
 */
int		DRIVER_Super_conf(DRIVER_SUPER_STRUCT *my_super, void *if_config){
	int				ret;
	unsigned long	start_time;
	
	my_super->non_periodic_config.rx_frame_count = 0;
	my_super->non_periodic_config.rx_except_footer_size
	 = my_super->non_periodic_config.rx_frame_size - my_super->non_periodic_config.rx_footer_size;
	
	//DRIVER_SUPER_RX(my_super, &(my_super->non_periodic_config), my_super->non_periodic_rx_frame);
	
		#ifdef	DRIVER_SUPER_DEBUG
			Printf("DRIVER_SUPER: *** Conf Cmd. ***\n");
		#endif
	DRIVER_SUPER_TX(my_super, &(my_super->non_periodic_config), if_config);
	
	if(my_super->non_periodic_config.rx_frame_size == 0){
		return(1);
	}
	
	ret = 0;
	start_time  = my_time();
	while(((my_time() - start_time) < 200) && ((my_time() - start_time) > 0)){
		if((ret = DRIVER_SUPER_RX(my_super, &(my_super->non_periodic_config), if_config, my_super->non_periodic_rx_frame)) == 1){
			return (ret);
		}
		MilliSleep(1);
	}
	
	return(ret);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief DRIVER_SUPER_STRUCT.tx_count, rx_count, cmd_time, update_time���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param DRIVER_SUPER_STRUCT *my_super : �ΏۂƂ���DRIVER_SUPER�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		DRIVER_Super_debug_message(DRIVER_SUPER_STRUCT *my_super){
	if(my_super->periodic_config.rx_frame_size != 0){
		Printf("RX_Time:%ld ", my_super->update_time);
		Printf("RX:%d ", my_super->rx_count);
	}
	if(my_super->periodic_config.tx_frame_size != 0){
		Printf("TX_Time:%lu ", my_super->cmd_time);
		Printf("TX:%d ", my_super->tx_count);
	}
	
	
	return (0);
}

//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief DRIVER_SUPER_CONFIG�\���̂ɂĒ��/�����̎w�肳�ꂽ���̃R�}���h�𔭍s���܂��B
 * 
 * ���M�f�[�^�t���[���T�C�Y��0�̏ꍇ�ɂ͉������܂���B
 * @param DRIVER_SUPER_STRUCT *my_super : �Ή�����DRIVER_SUPER�\���̂ւ̃|�C���^
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : �Ή�����DRIVER_SUPER_CONFIG�\���̂ւ̃|�C���^
 * @param void *if_config : �g�p����IF�̐ݒ�l�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� �Ώ�IF_TX() �̖߂�l���Q��)
 */
int		DRIVER_SUPER_TX(DRIVER_SUPER_STRUCT *my_super, DRIVER_SUPER_CONFIG_STRUCT *config, void *if_config){
	if(config->tx_frame_size == 0){
		return(0);
	}
	
		#ifdef	DRIVER_SUPER_DEBUG
			Printf("DRIVER_SUPER: *** DATA Tx. ***\n");
		#endif
	return((*IF_TX[my_super->inter_face])(if_config, config->tx_frame, config->tx_frame_size));
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief ��M�f�[�^�����邩�m�F���܂��B
 * 
 * ��M�f�[�^���Ȃ����0�Ń��^�[�����܂��B
 * ��M�f�[�^������΁A�Œ蒷�f�[�^�̎��́A DRIVER_SUPER_STRUCT.rx_buffer[] �Ɋi�[���A1�o�C�g���� DRIVER_SUPER_Analyze() �ɂāA���/�����̎w�肳�ꂽ���̏�ԑJ�ڂɂ����܂��B
 * �ϒ��f�[�^�Ńt���[���T�C�Y�f�[�^�����݂��鎞�́A DRIVER_SUPER_STRUCT.rx_buffer[] �Ɋi�[���A1�o�C�g���� DRIVER_SUPER_Analyze_variable() �ɂāA���/�����̎w�肳�ꂽ���̏�ԑJ�ڂɂ����܂��B
 * �ϒ��f�[�^�Ńt���[���T�C�Y�f�[�^�����݂��Ȃ����́A DRIVER_SUPER_STRUCT.rx_buffer[] �Ɋi�[���A1�o�C�g���� DRIVER_SUPER_Analyze_variable_not_fsd() �ɂāA���/�����̎w�肳�ꂽ���̏�ԑJ�ڂɂ����܂��B
 * ��M�f�[�^�t���[���T�C�Y��0�̏ꍇ�ɂ͉������܂���B
 * @param DRIVER_SUPER_STRUCT *my_super : �Ή�����DRIVER_SUPER�\���̂ւ̃|�C���^
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : �Ή�����DRIVER_SUPER_CONFIG�\���̂ւ̃|�C���^
 * @param void *if_config : �g�p����IF�̐ݒ�l�\���̂ւ̃|�C���^
 * @param unsigned char *frame : �Ή������M�f�[�^�t���[��
 * @return 1 : ����I��
 * @return 0 : ��M�f�[�^�Ȃ�
 * @return ��L�ȊO(�Œ蒷�f�[�^�̎�) : �Ō�Ɏ��s���� DRIVER_SUPER_Analyze() �߂�l(�ڍׂ� DRIVER_SUPER_Analyze() �̖߂�l���Q��)
 * @return ��L�ȊO(�ϒ��f�[�^�Ńt���[���T�C�Y�f�[�^�����݂��鎞) : �Ō�Ɏ��s���� DRIVER_SUPER_Analyze_variable() �߂�l(�ڍׂ� DRIVER_SUPER_Analyze_variable() �̖߂�l���Q��)
 * @return ��L�ȊO(�ϒ��f�[�^�Ńt���[���T�C�Y�f�[�^�����݂��Ȃ���) : �Ō�Ɏ��s���� DRIVER_SUPER_Analyze_variable_not_fsd() �߂�l(�ڍׂ� DRIVER_SUPER_Analyze_variable_not_fsd() �̖߂�l���Q��)
 */
int		DRIVER_SUPER_RX(DRIVER_SUPER_STRUCT *my_super, DRIVER_SUPER_CONFIG_STRUCT *config, void *if_config, unsigned char *frame){
	int				ret;
	int				count;
	unsigned char	*data = my_super->rx_buffer;
	
	if(config->rx_frame_size == 0){
		return(1);
	}
	
	//	RX
	if((count = (*IF_RX[my_super->inter_face])(if_config, data, DRIVER_SUPER_RX_BUFFER_SIZE_MAX)) <= 0){
		return(0);
	}
	
		//	RX Process
	if(config->rx_frame_size < 0){	// �ϒ��f�[�^�̎�
		if(config->rx_framelength_place > 0){	// �t���[���T�C�Y�f�[�^�����݂��鎞
			while (count > 0){
				if((ret = DRIVER_SUPER_Analyze_variable(*data, config, frame)) == 1){
					return(ret);
				}
				data++;
				count--;
			}
		}else{	// �t���[���T�C�Y�f�[�^�����݂��Ȃ���
			while (count > 0){
				if((ret = DRIVER_SUPER_Analyze_variable_not_fsd(*data, config, frame)) == 1){
					return(ret);
				}
				data++;
				count--;
			}
		}
	}else{	// �Œ蒷�f�[�^�̎�
		while (count > 0){
			if((ret = DRIVER_SUPER_Analyze(*data, config, frame)) == 1){
				return(ret);
			}
			data++;
			count--;
		}
	}
	
	return(ret);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief data�̒l�ɂ����rx_frame_count�̏�ԑJ�ڂ��s���܂��B(�Œ蒷�f�[�^�p)
 * 
 * �w�b�_�ƃt�b�^�̃G���[�����o���܂��B���o�����ꍇ�f�[�^���X�V�����ɖ߂�܂��B
 * ��M�w�b�_�T�C�Y��0�̏ꍇ�̓w�b�_�̃`�F�b�N�͍s���܂���B
 * ��M�t�b�^�T�C�Y��0�̏ꍇ�̓t�b�^�̃`�F�b�N�͍s���܂���B
 * �t���[�����m�肵����1�����^�[�����܂��B
 * ��ԑJ�ڑ��̓\�[�X�t�@�C�����̃R�����g���Q�Ƃ��������B
 * @param unsigned char data : ��M�f�[�^
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : �Ή�����DRIVER_SUPER_CONFIG�\���̂ւ̃|�C���^
 * @param unsigned char *frame : �Ή������M�f�[�^�t���[��
 * @return 1 : �t���[���m��
 * @return 100�ԑ� : �w�b�_��M��(-100�����l�����݂̎�M�o�C�g��)
 * @return 200�ԑ� : �X�e�[�^�X�f�[�^��M��(-200�����l�����݂̎�M�o�C�g��)
 * @return 300�ԑ� : �t�b�^��M��(-300�����l�����݂̎�M�o�C�g��)
 * @return -100�ԑ� : �w�b�_�G���[(-1���|����-100�����l�̃o�C�g���ڂŃG���[)
 * @return -300�ԑ� : �t�b�^�G���[(-1���|����-300�����l�̃o�C�g���ڂŃG���[)
 * @return -1 : ���̑��G���[
 */
int		DRIVER_SUPER_Analyze(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame){
	int		ret;
	
	// frame_count����"�w�b�_��M����"�̏ꍇ
	if(config->rx_frame_count < config->rx_header_size){
		// �w�b�_�̃`�F�b�N
		if(data == config->rx_header[config->rx_frame_count]){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			return(100 + ret);
		}else{
			ret = config->rx_frame_count + 1;
			config->rx_frame_count = 0;
				#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: +++ Error Data in %d byte +++\n", ret);
				#endif
			return(-(100 + ret));
		}
	// frame_count����"�f�[�^��M����"�̏ꍇ
	}else if(config->rx_frame_count < config->rx_except_footer_size){
		frame[config->rx_frame_count] = data;
		ret = config->rx_frame_count + 1;
		config->rx_frame_count++;
		// �t�b�^���Ȃ��ꍇ�ŁA����frame_count����"�t���[���擾������"�̏ꍇ
		if((config->rx_footer_size == 0) && (config->rx_frame_count == config->rx_frame_size)){
				#ifdef	DRIVER_SUPER_DEBUG
					Printf("DRIVER_SUPER: *** FRAME ***\n");
				#endif
			config->rx_frame_count = 0;
			return(1);
		// ����ȊO
		}else{
			return(200 + ret);
		}
	// frame_count����"�f�[�^�I����"�̏ꍇ
	}else if(config->rx_frame_count < config->rx_frame_size){
		// �t�b�^�̃`�F�b�N
		if(data == config->rx_footer[config->rx_frame_count - config->rx_except_footer_size]){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			// frame_count����"�t���[���擾������"�̏ꍇ
			if(config->rx_frame_count == config->rx_frame_size){
					#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: *** FRAME ***\n");
					#endif
				config->rx_frame_count = 0;
				return(1);
			}else{
				return(300 + ret);
			}
		}else{
			ret = config->rx_frame_count + 1;
			config->rx_frame_count = 0;
				#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: +++ Error Data in %d byte +++\n", ret);
				#endif
			return(-(300 + ret));
		}
	}else{
		config->rx_frame_count = 0;
		return(-1);
	}
	return(0);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief data�̒l�ɂ����rx_frame_count�̏�ԑJ�ڂ��s���܂��B(�ϒ��f�[�^�Ńt���[���T�C�Y�f�[�^�����݂��鎞�p)
 * 
 * �w�b�_�ƃt�b�^�ƃt���[���T�C�Y�f�[�^�̃G���[�����o���܂��B���o�����ꍇ�f�[�^���X�V�����ɖ߂�܂��B
 * �t���[�����m�肵����1�����^�[�����܂��B
 * ��ԑJ�ڑ��̓\�[�X�t�@�C�����̃R�����g���Q�Ƃ��������B
 * @param unsigned char data : ��M�f�[�^
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : �Ή�����DRIVER_SUPER_CONFIG�\���̂ւ̃|�C���^
 * @param unsigned char *frame : �Ή������M�f�[�^�t���[��
 * @return 1 : �t���[���m��
 * @return 100�ԑ� : �w�b�_��M��(-100�����l�����݂̎�M�o�C�g��)
 * @return 200�ԑ� : �X�e�[�^�X�f�[�^��M��(�t���[���T�C�Y�f�[�^����M)(-200�����l�����݂̎�M�o�C�g��)
 * @return 300�ԑ� : �X�e�[�^�X�f�[�^��M��(�t���[���T�C�Y�f�[�^��M��)(-300�����l�����݂̎�M�o�C�g��)
 * @return 400�ԑ� : �X�e�[�^�X�f�[�^��M��(�t���[���T�C�Y�f�[�^��M��)(-400�����l�����݂̎�M�o�C�g��)
 * @return 500�ԑ� : �t�b�^��M��(-500�����l�����݂̎�M�o�C�g��)
 * @return -100�ԑ� : �w�b�_�G���[(-1���|����-100�����l�̃o�C�g���ڂŃG���[)
 * @return -500�ԑ� : �t�b�^�G���[(-1���|����-500�����l�̃o�C�g���ڂŃG���[)
 * @return -1 : �t���[���T�C�Y�f�[�^�̑��݂���ꏊ���w�b�_���ɐݒ肳��Ă��鎞
 * @return -2 : ���̑��G���[
 */
int		DRIVER_SUPER_Analyze_variable(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame){
	int		ret;
	
	// �t���[���T�C�Y�f�[�^�̑��݂���ꏊ���w�b�_���ɐݒ肳��Ă��鎞
	if(config->rx_framelength_place <= config->rx_header_size){
			#ifdef	DRIVER_SUPER_DEBUG
					Printf("DRIVER_SUPER: +++ config Erroe +++ (v)\n", ret);
			#endif
		return(-1);
	}
	
	// frame_count����"�w�b�_��M����"�̏ꍇ
	if(config->rx_frame_count < config->rx_header_size){
		// �w�b�_�̃`�F�b�N
		if(data == config->rx_header[config->rx_frame_count]){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			return(100 + ret);
		}else{
			ret = config->rx_frame_count + 1;
			config->rx_frame_count = 0;
				#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: +++ Error Data in %d byte +++ (v)\n", ret);
				#endif
			return(-(100 + ret));
		}
	// frame_count�����t���[���T�C�Y�f�[�^�̑��݂���ꏊ�����������ꍇ
	}else if(config->rx_frame_count < (config->rx_framelength_place - 1)){
		frame[config->rx_frame_count] = data;
		ret = config->rx_frame_count + 1;
		config->rx_frame_count++;
		return(200 + ret);
	// frame_count�����t���[���T�C�Y�f�[�^�̑��݂���ꏊ�ƂȂ����ꍇ
	}else if(config->rx_frame_count == (config->rx_framelength_place - 1)){
		frame[config->rx_frame_count] = data;
		ret = config->rx_frame_count + 1;
		config->rx_frame_count++;
		config->rx_frame_size_v = frame[config->rx_framelength_place - 1] + config->rx_framelength_offset;
		config->rx_except_footer_size = config->rx_frame_size_v - config->rx_footer_size;
		return(300 + ret);
	// frame_count�����t���[���T�C�Y�f�[�^�̑��݂���ꏊ�����傫���ꍇ
	}else if(config->rx_frame_count > (config->rx_framelength_place - 1)){
		// frame_count����"�f�[�^��M����"�̏ꍇ
		if(config->rx_frame_count < config->rx_except_footer_size){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			// �t�b�^���Ȃ��ꍇ�ŁA����frame_count����"�t���[���擾������"�̏ꍇ
			if((config->rx_footer_size == 0) && (config->rx_frame_count == config->rx_frame_size_v)){
					#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: *** FRAME *** (v)\n");
					#endif
				config->rx_frame_count = 0;
				return(1);
			// ����ȊO
			}else{
				return(400 + ret);
			}
		// frame_count����"�f�[�^�I����"�̏ꍇ
		}else if(config->rx_frame_count < config->rx_frame_size_v){
			// �t�b�^�̃`�F�b�N
			if(data == config->rx_footer[config->rx_frame_count - config->rx_except_footer_size]){
				frame[config->rx_frame_count] = data;
				ret = config->rx_frame_count + 1;
				config->rx_frame_count++;
				// frame_count����"�t���[���擾������"�̏ꍇ
				if(config->rx_frame_count == config->rx_frame_size_v){
						#ifdef	DRIVER_SUPER_DEBUG
							Printf("DRIVER_SUPER: *** FRAME *** (v)\n");
						#endif
					config->rx_frame_count = 0;
					return(1);
				}else{
					return(500 + ret);
				}
			}else{
				ret = config->rx_frame_count + 1;
				config->rx_frame_count = 0;
					#ifdef	DRIVER_SUPER_DEBUG
							Printf("DRIVER_SUPER: +++ Error Data in %d byte +++ (v)\n", ret);
					#endif
				return(-(500 + ret));
			}
		}else{
			config->rx_frame_count = 0;
			return(-2);
		}
	}
	return(0);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief data�̒l�ɂ����rx_frame_count�̏�ԑJ�ڂ��s���܂��B(�ϒ��f�[�^�Ńt���[���T�C�Y�f�[�^�����݂��Ȃ����p)
 * 
 * �w�b�_�̃G���[�����o���܂��B���o�����ꍇ�f�[�^���X�V�����ɖ߂�܂��B
 * �t�b�^�ɑ�������f�[�^�񂪔������ꂽ�ꍇ�Ɂu�t���[���m��v�Ƃ��܂��B
 * �t���[�����m�肵����1�����^�[�����܂��B
 * ��ԑJ�ڑ��̓\�[�X�t�@�C�����̃R�����g���Q�Ƃ��������B
 * @warning �w�b�_, �t�b�^��0�̏ꍇ�ɂ����āA�{�֐����g�p�����(�ϒ��f�[�^)�͋�����܂���
 * @param unsigned char data : ��M�f�[�^
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : �Ή�����DRIVER_SUPER_CONFIG�\���̂ւ̃|�C���^
 * @param unsigned char *frame : �Ή������M�f�[�^�t���[��
 * @return 1 : �t���[���m��
 * @return 100�ԑ� : �w�b�_��M��(-100�����l�����݂̎�M�o�C�g��)
 * @return 200�ԑ� : �X�e�[�^�X�f�[�^��M��(-200�����l�����݂̎�M�o�C�g��)
 * @return -100�ԑ� : �w�b�_�G���[(-1���|����-100�����l�̃o�C�g���ڂŃG���[)
 * @return -1 : �t���[���J�E���g���I�[�o�[(�w�b�_�͗������A���܂ł����Ă��t�b�^�����Ȃ�������)
 */
int		DRIVER_SUPER_Analyze_variable_not_fsd(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame){
	int		ret;
	
	// �t���[���J�E���g���I�[�o�[
	if(config->rx_frame_count >= DRIVER_SUPER_RX_FRAME_SIZE_MAX){
			#ifdef	DRIVER_SUPER_DEBUG
					Printf("DRIVER_SUPER: +++ frame_count Over +++ (v_n_fsd)\n", ret);
			#endif
		config->rx_frame_count = 0;
		return(-1);
	}
	
	// frame_count����"�w�b�_��M����"�̏ꍇ
	if(config->rx_frame_count < config->rx_header_size){
		// �w�b�_�̃`�F�b�N
		if(data == config->rx_header[config->rx_frame_count]){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			config->rx_footer_flag = 0;	//�w�b�_�̃`�F�b�N����rx_footer_flag�����������Ă���
			return(100 + ret);
		}else{
			ret = config->rx_frame_count + 1;
			config->rx_frame_count = 0;
				#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: +++ Error Data in %d byte +++ (v_n_fsd)\n", ret);
				#endif
			return(-(100 + ret));
		}
	// frame_count����"�w�b�_��M����"�ȊO�̏ꍇ
	}else{
		frame[config->rx_frame_count] = data;
		ret = config->rx_frame_count + 1;
		config->rx_frame_count++;
		// �t�b�^�`�F�b�N
		if(data == config->rx_footer[config->rx_footer_flag]){
			config->rx_footer_flag++;
			if(config->rx_footer_flag == config->rx_footer_size){
					#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: *** FRAME *** (v_n_fsd)\n");
					#endif
				config->rx_frame_count = 0;
				config->rx_footer_flag = 0;
				return(1);
			}
		}else{
			config->rx_footer_flag = 0;
		}
		return(200 + ret);
	}
	return(0);
}
