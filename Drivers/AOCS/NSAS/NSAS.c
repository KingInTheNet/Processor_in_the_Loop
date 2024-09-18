/**
 * @file NSAS.c
 * @brief NSAS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * NSAS�C���^�[�t�F�[�X���W���[���́AAxelSpace��AxelSun�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g�A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2013.03.09
 */

#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "../../../../Port_Config.h"		//�f�o�b�O���[�h�ɂ͕K�v

#include "NSAS.h"

//#define	NSAS_DEBUG


int		NSAS_Data_Conv(NSAS_STRUCT *my_nsas);

static unsigned int		nsas_dummy1;
static unsigned char	nsas_cmd_data_req_angle[3] = {0xC2, 0x00, 0x0D};	/**< @brief �p�x�o�̓f�[�^���N�G�X�g�R�}���h*/
static unsigned int		nsas_dummy2;
static unsigned char	nsas_cmd_data_req[3] = {0xC2, 0x01, 0x0D};	/**< @brief �x�N�g���o�̓f�[�^���N�G�X�g�R�}���h*/

/** @brief �p�x�o�̓f�[�^�p�P�b�g�ɂ��āA�t���[���̒������`(��)*/
#define	NSAS_RX_FRAME_SIZE_ANGLE_OLD		23	// HEADER 2 + ERROR CODE 1 + PACKET DATA 18 + FOOTER 2 = 23
/** @brief �p�x�o�̓f�[�^�p�P�b�g�ɂ��āA�t���[���̒������`(�V)*/
#define	NSAS_RX_FRAME_SIZE_ANGLE_NEW		13	// HEADER 2 + ERROR CODE 1 + PACKET DATA 8 + FOOTER 2 = 13
/** @brief �x�N�g���o�̓f�[�^�p�P�b�g�ɂ��āA�t���[���̒������`*/
#define	NSAS_RX_FRAME_SIZE_VECTOR		27	// HEADER 2 + ERROR CODE 1 + PACKET DATA 22 + FOOTER 2 = 27

static unsigned char	nsas_rx_header[2] = {0x02, 0xC2};	/**< @brief ��M�t���[���̃w�b�_*/
static unsigned char	nsas_rx_footer[2] = {0x0D, 0x0A};	/**< @brief ��M�t���[���̃t�b�^*/

//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSAS�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA NSAS_STRUCT.driver_super �ɒ����M���̃w�b�_,�t�b�^,�t���[���T�C�Y�A����R�}���h���s���̏����L�^���܂��B
 * �܂��A�������Ɠ����ɁANSAS�ɑ΂��ďo�͂��u�W���o�́v�݂̂ɂ���悤�ɃR�}���h�𔭍s���܂��B
 * @note NSAS�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param NSAS_STRUCT *my_nsas : ����������NSAS�\���̂ւ̃|�C���^
 * @param unsigned char ch : NSAS���ڑ�����Ă���UART�|�[�g�ԍ�
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_init() �̖߂�l���Q��)
 */
int		NSAS_init(NSAS_STRUCT *my_nsas, unsigned char ch){
    int		i_ret;
	
	
	//if(ch == NSAS1_CH){	//�V��
		my_nsas->rs422_config.ch = ch;
		my_nsas->rs422_config.baudrate = 38400;
		my_nsas->rs422_config.stop_bit = 1;
		
		my_nsas->driver_super.inter_face = RS422;
		
		my_nsas->driver_super.periodic_config.rx_header_size = sizeof(nsas_rx_header);
		my_nsas->driver_super.periodic_config.rx_header = nsas_rx_header;
		
		my_nsas->driver_super.periodic_config.rx_footer_size = sizeof(nsas_rx_footer);
		my_nsas->driver_super.periodic_config.rx_footer = nsas_rx_footer;
		
		my_nsas->driver_super.periodic_config.rx_frame_size = NSAS_RX_FRAME_SIZE_ANGLE_NEW;
		
		my_nsas->driver_super.periodic_config.tx_frame_size = sizeof(nsas_cmd_data_req_angle);
		my_nsas->driver_super.periodic_config.tx_frame = nsas_cmd_data_req_angle;
		
		if((i_ret = DRIVER_Super_init(&(my_nsas->driver_super), &(my_nsas->rs422_config))) != 0){	// Error
			return(i_ret);
		}
	/*}else{	//����
		my_nsas->rs422_config.ch = ch;
		my_nsas->rs422_config.baudrate = 38400;
		my_nsas->rs422_config.stop_bit = 1;
		
		my_nsas->driver_super.inter_face = RS422;
		
		my_nsas->driver_super.periodic_config.rx_header_size = sizeof(nsas_rx_header);
		my_nsas->driver_super.periodic_config.rx_header = nsas_rx_header;
		
		my_nsas->driver_super.periodic_config.rx_footer_size = sizeof(nsas_rx_footer);
		my_nsas->driver_super.periodic_config.rx_footer = nsas_rx_footer;
		
		my_nsas->driver_super.periodic_config.rx_frame_size = NSAS_RX_FRAME_SIZE_ANGLE_OLD;
		
		my_nsas->driver_super.periodic_config.tx_frame_size = sizeof(nsas_cmd_data_req_angle);
		my_nsas->driver_super.periodic_config.tx_frame = nsas_cmd_data_req_angle;
		
		if((i_ret = DRIVER_Super_init(&(my_nsas->driver_super), &(my_nsas->rs422_config))) != 0){	// Error
			return(i_ret);
		}
	}
	*/
	
	
	return(0);
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSAS�����p�̃f�o�b�O���[�h�ł��B
 * 
 * �f�o�b�O�R���\�[����ŁANSAS�ɑ΂��Q�C���ݒ�R�}���h�𑗐M���܂��B
 * @param �Ȃ�
 * @return �Ȃ�
 */
void		Debug_NSAS_gain_set(void){
	extern NSAS_STRUCT	nsas1, nsas2, nsas3;
	NSAS_STRUCT			*nsasx_p;
	int				i_ret;
	unsigned int	end_flg = 0;
	unsigned int	tmp = 0;
	unsigned char	ch = 0;
	unsigned char	ope = 0;
	unsigned char	gain = 0;
	int				ret = 0;
	
	while(1){
		Printf("\nNSAS Gain Set \n");
		while(!end_flg){
			Printf("  Which NSAS (1-3)?    99:end\n");
			ScanfUIntD( &tmp );
			if(tmp == 99){
				return;
			}
			if(tmp < 1 || tmp > 3){
				Printf("Illegal NSAS Number\n");
			}else{
				end_flg = 1;
			}
		}
		end_flg = 0;
		
		switch(tmp){
			case 1:
				nsasx_p = &nsas1;
				ch = NSAS1_CH;
			break;
			
			case 2:
				nsasx_p = &nsas2;
				ch = NSAS2_CH;
			break;
			
			case 3:
				nsasx_p = &nsas3;
				ch = NSAS3_CH;
			break;
			
			default:
			break;
		}
		
		i_ret = NSAS_init(nsasx_p, ch);
		if(i_ret != 0){
			Printf("NSAS Init Error (%d)\n", i_ret);
			return;
		}
		
		while(!end_flg){
			Printf(" Gain Control?  0:OFF 1:ON\n");
			ScanfUIntD( &tmp );
			if(tmp == 0 || tmp == 1){
				ope = (unsigned char)tmp;
				end_flg = 1;
			}
		}
		end_flg = 0;
		
		while(!end_flg){
			Printf(" Gain? (0-255)\n");
			ScanfUIntD( &tmp );
			if(tmp >= 0 || tmp <= 255){
				gain = (unsigned char)tmp;
				end_flg = 1;
			}
		}
		end_flg = 0;
		
		ret = NSAS_gain(nsasx_p, ope, gain);
		if(ret == 0){
			Printf("Time Out\n");
		}else if(ret == 202){
			Printf("NSAS Rx OK - Data Error\n");
		}else if(ret == 201){
			Printf("NSAS Rx OK - Set Gain Error\n");
		}else if(ret < 0){
			Printf("Rx Data Error ");
			if(ret < -300){
				Printf("in %d byte (Footer)\n", (-ret) - 300);
			}else{
				Printf("in %d byte (Header)\n", (-ret) - 100);
			}
		}else if(ret == 1){
			Printf("Done\n");
		}else{
			Printf("?\n");
		}
	}
	return;
	
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSAS�ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * @param NSAS_STRUCT *my_nsas : �ΏۂƂ���NSAS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_cycle() �̖߂�l���Q��)
 */
int		NSAS_cycle(NSAS_STRUCT *my_nsas){
	int		i_ret;
	
		#ifdef	NSAS_DEBUG
			Printf("NSAS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_nsas->driver_super), &(my_nsas->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSAS����̃f�[�^�p�P�b�g���Ď����A��M�������e�� NSAS_STRUCT �Ɋi�[���܂��B
 * 
 * ����R�}���h���M������葁�������Œ���I�Ɏ��s���Ă��������B
 * @note �f�[�^�p�P�b�g�ɂ��Ă� DRIVER_Super_rec() ���g�p���ăt���[���������Ƃ�A
 * �t���[���������Ƃꂽ�ꍇ�Ɏ�M���e�� NSAS_STRUCT �Ɋi�[���܂��B
 * @param NSAS_STRUCT *my_nsas : �ΏۂƂ���NSAS�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		NSAS_rec(NSAS_STRUCT *my_nsas){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_nsas->driver_super), &(my_nsas->rs422_config));
	if(i_ret == 1){
			#ifdef	NSAS_DEBUG
				Printf("NSAS: *** Frame ***\n");
			#endif
		NSAS_Data_Conv(my_nsas);
	}
	
	return(i_ret);
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSAS�\���̂̃f�[�^���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param NSAS_STRUCT *my_nsas : �ΏۂƂ���NSAS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		NSAS_debug_message(NSAS_STRUCT* my_nsas){
	Printf("X:%u ", my_nsas->x);
	Printf("Y:%u ", my_nsas->y);
	//Printf("Z:%f ", my_nsas->z);
		Printf("ID:%u ", (unsigned int)my_nsas->id);
		Printf("GF:%u ", (unsigned int)my_nsas->gain_flag);
		Printf("SF:%u ", (unsigned int)my_nsas->sun_flag);
		Printf("Ga:%u ", (unsigned int)my_nsas->gain);
		Printf("Te:%u ", my_nsas->tempe);
	
	DRIVER_Super_debug_message(&(my_nsas->driver_super));
	
	
	return(0);
}

/**
 * @memberof NSAS_STRUCT
 * @public
 * @brief NSAS�փQ�C���ݒ�R�}���h�𑗐M���A����ɑ΂��郌�X�|���X�̉ۂ����^�[�����܂��B
 * 
 * @note aosc_super�ɔ����R�}���h���s���ƁA���̃R�}���h�ɑ΂��郌�X�|���X��M���̏����������݁A
 *  DRIVER_Super_conf() �����s���Ă��܂��B
 * @param NSAS_STRUCT *my_nsas : �ΏۂƂ���NSAS�\���̂ւ̃|�C���^
 * @param unsigned char ope : �Q�C���R���g���[�����[�h��ON/OFF(ON:1  OFF:0)
 * @param unsigned char gain : �ݒ肷��Q�C���̒l
 * @return 1 : ���X�|���X����
 * @return 1000 : �������̃G���[(0��1�ȊO����ꂽ�ꍇ)
 * @return 2001 : ���X�|���X���̂͐��킾���A�Q�C���̐ݒ�Ɏ��s
 * @return 2002 : ���X�|���X�̃t���[�������͐��킾���A�f�[�^���Ӗ��s��
 * @return ��L�ȊO : ���X�|���X�ُ�(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		NSAS_gain(NSAS_STRUCT *my_nsas, unsigned char ope, unsigned char gain){
	int	ret;
	unsigned char	nsas_cmd_gain[4] = {0xD1, 0x4D, 0x00, 0x0D};
	unsigned char	nsas_cmd_gain_rx_header[2] = {0x02, 0xD1};
	unsigned char	nsas_cmd_gain_rx_footer[2] = {0x0D, 0x0A};
	
	if(ope == 0){
		nsas_cmd_gain[1] = 0x4D;
	}else if(ope == 1){
		nsas_cmd_gain[1] = 0x41;
	}else{
		return (1000);
	}
	
	nsas_cmd_gain[2] = gain;
	
	my_nsas->driver_super.non_periodic_config.tx_frame_size = sizeof(nsas_cmd_gain);
	my_nsas->driver_super.non_periodic_config.tx_frame = nsas_cmd_gain;
	
	my_nsas->driver_super.non_periodic_config.rx_header_size = sizeof(nsas_cmd_gain_rx_header);
	my_nsas->driver_super.non_periodic_config.rx_header = nsas_cmd_gain_rx_header;
	
	my_nsas->driver_super.non_periodic_config.rx_footer_size = sizeof(nsas_cmd_gain_rx_footer);
	my_nsas->driver_super.non_periodic_config.rx_footer = nsas_cmd_gain_rx_footer;
	
	my_nsas->driver_super.non_periodic_config.rx_frame_size = 7;
	
	ret = DRIVER_Super_conf(&(my_nsas->driver_super), &(my_nsas->rs422_config));
	
	if(ret == 1){
		if((my_nsas->driver_super.non_periodic_rx_frame[2]) == 0x00){
			return (1);
		}else if((my_nsas->driver_super.non_periodic_rx_frame[2]) == 0x01){
			return (2001);
		}else{
			return (2002);
		}
	}
	
	return (ret);
}


//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof NSAS_STRUCT
 * @private
 * @brief �t���[���f�[�^��NSAS�\���̂̃f�[�^���e�ɕϊ����܂��B
 * 
 * �H�w�l�ϊ����K�v�ȏꍇ�͂����ɏ������݂܂��B
 * @param NSAS_STRUCT *my_nsas : �ΏۂƂ���NSAS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		NSAS_Data_Conv(NSAS_STRUCT* my_nsas){
	/** @brief �t���[���f�[�^�̃w�b�_�����I�t�Z�b�g�����|�C���^*/
	unsigned char *nsas_rx_data = my_nsas->driver_super.periodic_rx_frame + sizeof(nsas_rx_header);
	
	
	//if(my_nsas->rs422_config.ch == NSAS1_CH){	//�V��
		my_nsas->error = *(nsas_rx_data + 0);
		my_nsas->id = *(nsas_rx_data + 1);
		//�R�R(nsas_rx_data + 2)�ɂ͕K���[��������̂Ŏ擾���Ȃ�
		my_nsas->gain_flag = *(nsas_rx_data + 3);
		my_nsas->sun_flag = *(nsas_rx_data + 4);
		my_nsas->gain = *(nsas_rx_data + 5);
		//my_nsas->tempe = ((28.0+85.0) / (0xFF) * nsas_rx_data[6]) - 28.0;
		//my_nsas->x = ((55.0+55.0) / (0xFF) * nsas_rx_data[7]) - 55.0;
		//my_nsas->y = ((55.0+55.0) / (0xFF) * nsas_rx_data[8]) - 55.0;
		my_nsas->tempe = nsas_rx_data[6];
		my_nsas->x = nsas_rx_data[7];
		my_nsas->y = nsas_rx_data[8];
	/*}else{	//����
		my_nsas->error = *(nsas_rx_data + 0);
		
		//�R�R(nsas_rx_data + 1)�ɂ͂Ȃ����]����1�o�C�g�����M����Ă���炵��?
		
		my_nsas->id = *(nsas_rx_data + 2);
		
		//�R�R(nsas_rx_data + 3)�ɂ͕K���[��������̂Ŏ擾���Ȃ�
		
		my_nsas->gain_flag = *(nsas_rx_data + 4);
		
		my_nsas->sun_flag = *(nsas_rx_data + 5);
		
		my_nsas->gain = *(nsas_rx_data + 6);
		
		*((unsigned char*)(&(my_nsas->tempe)) + 0) = *(nsas_rx_data + 7);
		*((unsigned char*)(&(my_nsas->tempe)) + 1) = *(nsas_rx_data + 8);
		*((unsigned char*)(&(my_nsas->tempe)) + 2) = *(nsas_rx_data + 9);
		*((unsigned char*)(&(my_nsas->tempe)) + 3) = *(nsas_rx_data + 10);
		
		*((unsigned char*)(&(my_nsas->x)) + 0) = *(nsas_rx_data + 11);
		*((unsigned char*)(&(my_nsas->x)) + 1) = *(nsas_rx_data + 12);
		*((unsigned char*)(&(my_nsas->x)) + 2) = *(nsas_rx_data + 13);
		*((unsigned char*)(&(my_nsas->x)) + 3) = *(nsas_rx_data + 14);
		
		*((unsigned char*)(&(my_nsas->y)) + 0) = *(nsas_rx_data + 15);
		*((unsigned char*)(&(my_nsas->y)) + 1) = *(nsas_rx_data + 16);
		*((unsigned char*)(&(my_nsas->y)) + 2) = *(nsas_rx_data + 17);
		*((unsigned char*)(&(my_nsas->y)) + 3) = *(nsas_rx_data + 18);
	}
	*/
	
	
	return (0);
}
