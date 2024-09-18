/**
 * @file RW.c
 * @brief RW�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * RW�C���^�[�t�F�[�X���W���[���́A�����쐸�@�������TS4431�Ƃ̃C���^�[�t�F�[�X���������A
 * �f�[�^�擾�E�R�}���h���M���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.09.17
 */

#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "../../../../Port_Config.h"		//�f�o�b�O���[�h�ɂ͕K�v

#include "../../../Data_Processing/endian_conv.h"
#include "../../../Data_Processing/exor.h"

#include "RW.h"

//#define	RW_DEBUG


int				RW_Data_Conv(RW_STRUCT* my_rw);


#define RW_RX_FRAME_SIZE			13	/**< @brief ��M�t���[���̒���*/
#define RW_TX_FRAME_SIZE			10	/**< @brief ���M�t���[���̒���*/

static unsigned char	rw_rx_header[2] = {0x02, 0x01};	/**< @brief ��M�t���[���̃w�b�_*/

//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof RW_STRUCT
 * @public
 * @brief RW�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA RW_STRUCT.driver_super �ɒ����M���̃w�b�_,�t�b�^,�t���[���T�C�Y�A����R�}���h���s���̏����L�^���܂��B
 * �܂��A�������Ɠ����ɁARW�ɑ΂��ďo�͂��u�W���o�́v�݂̂ɂ���悤�ɃR�}���h�𔭍s���܂��B
 * @note RW�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param RW_STRUCT *my_rw : ����������RW�\���̂ւ̃|�C���^
 * @param unsigned char ch : RW���ڑ�����Ă���UART�|�[�g�ԍ�
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_init() �̖߂�l���Q��)
 */
int RW_init(RW_STRUCT* my_rw, unsigned char ch){
	int		i_ret;
	
	my_rw->rs422_config.ch = ch;
	my_rw->rs422_config.baudrate = 19200;
	my_rw->rs422_config.stop_bit = 1;
	
	my_rw->driver_super.inter_face = RS422;
	
	my_rw->driver_super.periodic_config.rx_header_size = sizeof(rw_rx_header);
	my_rw->driver_super.periodic_config.rx_header = rw_rx_header;
	
	my_rw->driver_super.periodic_config.rx_footer_size = 0;
	
	my_rw->driver_super.periodic_config.rx_frame_size = RW_RX_FRAME_SIZE;
	
	my_rw->driver_super.periodic_config.tx_frame_size = RW_TX_FRAME_SIZE;
	
	if((i_ret = DRIVER_Super_init(&(my_rw->driver_super), &(my_rw->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	return(0);
}

/**
 * @memberof RW_STRUCT
 * @public
 * @brief RW�����p�̃f�o�b�O���[�h�ł��B
 * 
 * �f�o�b�O�R���\�[�����RW����̃X�e�[�^�X��\��������ARW�ɑ΂��R�}���h�𑗐M�����肵�܂��B
 * @param �Ȃ�
 * @return �Ȃ�
 */
void Debug_RW(void){
	extern RW_STRUCT	rw1, rw2, rw3, rw4;
	RW_STRUCT			*rwx_p;
	int				i_ret;
	unsigned int	end_flg = 0;
	int				debug_rw_loop = 1;
	unsigned int	tmp = 0;
	unsigned char	ch = 0;
	unsigned char	Comm1 = 0;
	unsigned short	Comm2 = 0;
	unsigned short	Comm3 = 0;
	unsigned char	c = 0;
	int				ope = 0;
	int				ret = 0;
	
	int				cnt = 0;
	
	Printf("RW Test \n");
	while(!end_flg){
		Printf("  Which RW (1-4) ?    99:end\n");
		ScanfUIntD( &tmp );
		if(tmp == 99){
			return;
		}
		if(tmp < 1 || tmp > 4){
			Printf("Illegal RW Number\n");
		}else{
			end_flg = 1;
		}
	}
	end_flg = 0;
	
	switch(tmp){
		case 1:
			rwx_p = &rw1;
			ch = RW1_CH;
		break;
		
		case 2:
			rwx_p = &rw2;
			ch = RW2_CH;
		break;
		
		case 3:
			rwx_p = &rw3;
			ch = RW3_CH;
		break;
		
		case 4:
			rwx_p = &rw4;
			ch = RW4_CH;
		break;
		
		default:
		break;
	}
	
	i_ret = RW_init(rwx_p, ch);
	if(i_ret != 0){
		Printf("RW Init Error (%d)\n", i_ret);
		return;
	}
	
	Printf("  d:Data Set, s:Data Send q:Quit\n");
	while(debug_rw_loop){
		MilliSleep(5);
		
		if(RW_rec(rwx_p) == 1){
			Printf("Message Number: %u\n", (unsigned int)rwx_p->rw_rx_sts.mess_no);
			
			if((((rwx_p->rw_rx_sts.sts1.byte) & 0x01) >> 0) == 1){
				Printf("Motor Drive: ON\n");
			}else if((((rwx_p->rw_rx_sts.sts1.byte) & 0x01) >> 0) == 0){
				Printf("Motor Drive: OFF\n");
			}
			if((((rwx_p->rw_rx_sts.sts1.byte) & 0x02) >> 1) == 1){
				Printf("Torque Direction: CCW\n");
			}else if((((rwx_p->rw_rx_sts.sts1.byte) & 0x02) >> 1) == 0){
				Printf("Torque Direction: CW\n");
			}
			if((((rwx_p->rw_rx_sts.sts1.byte) & 0x04) >> 2) == 1){
				Printf("Motor Rotatory Direction: CCW\n");
			}else if((((rwx_p->rw_rx_sts.sts1.byte) & 0x04) >> 2) == 0){
				Printf("Motor Rotatory Direction: CW\n");
			}
			
			if((((rwx_p->rw_rx_sts.sts2.byte) & 0x01) >> 0) == 1){
				Printf("No Command\n");
			}
			if((((rwx_p->rw_rx_sts.sts2.byte) & 0x02) >> 1) == 1){
				Printf("BCC Error(Tx)\n");
			}
			if((((rwx_p->rw_rx_sts.sts2.byte) & 0x04) >> 2) == 1){
				Printf("Command Error\n");
			}
			if((((rwx_p->rw_rx_sts.sts2.byte) & 0x08) >> 3) == 1){
				Printf("Over Voltage\n");
			}
			if((((rwx_p->rw_rx_sts.sts2.byte) & 0x10) >> 4) == 1){
				Printf("Sensor Error\n");
			}
			if((((rwx_p->rw_rx_sts.sts2.byte) & 0x20) >> 5) == 1){
				Printf("Over Current\n");
			}
			
			Printf("Revolution Speed: %u[rpm]\n", (unsigned int)rwx_p->rw_rx_sts.sts3);
			
			Printf("Current: %d[mA]\n", (int)rwx_p->rw_rx_sts.sts4);
			
			Printf("Bearing Temperature: %d[C]\n", (int)rwx_p->rw_rx_sts.sts5);
			Printf("\n");
		}
		
		if(cnt == 0){
			RW_cycle(rwx_p);
		}
		cnt++;
		cnt %= 100;
		
		c = CheckChar();
		if(c == 'd' || c == 'D'){
			Printf(" Entering Data Set Mode\n");
			Comm1 = 0;
			while(!end_flg){
				Printf("  Motor Drive?  0:OFF 1:ON\n");
				ScanfUIntD( &tmp );
				if(tmp == 0 || tmp == 1){
					end_flg = 1;
				}
			}
			end_flg = 0;
			Comm1 |= (unsigned char)(tmp << 0);
			
			while(!end_flg){
				Printf("  Torque Direction?  0:CW 1:CCW\n");
				ScanfUIntD( &tmp );
				if(tmp == 0 || tmp == 1){
					end_flg = 1;
				}
			}
			end_flg = 0;
			Comm1 |= (unsigned char)(tmp << 1);
			
			while(!end_flg){
				Printf("  Open/Close Loop?  0:Open 1:Close\n");
				ScanfUIntD( &tmp );
				if(tmp == 0 || tmp == 1){
					end_flg = 1;
				}
			}
			end_flg = 0;
			Comm1 |= (unsigned char)(tmp << 2);
			
			while(!end_flg){
				Printf("  Voltage Set (0-28000[mV]): \n");
				ScanfUIntD( &tmp );
				if(tmp >= 0 && tmp <= 28000){
					end_flg = 1;
				}
			}
			end_flg = 0;
			// 2013/01/15 Changed by kkamiya
			//Comm2 = (unsigned short)tmp;
			Comm2 = (unsigned short)((double)tmp / 50000.0 * (double)0x10000);
			
			Printf("  d:Data Set, s:Data Send q:Quit\n");
		}else if(c == 's' || c == 'S'){
			RW_tx_comm(rwx_p, Comm1, Comm2, Comm3);
			Printf("Send\n");
		}else if(c == 'q' || c == 'Q'){
			debug_rw_loop = 0;
		}
	}
	return;
}

/**
 * @memberof RW_STRUCT
 * @public
 * @brief �����ɂ���ė^����ꂽ�w�ߒl��RW�\���̂Ɋi�[���܂��B
 * @param RW_STRUCT *my_rw : �ΏۂƂ���RW�\���̂ւ̃|�C���^
 * @param unsigned char Comm1 : �R�}���h1(RW�ʐM�d�l���Q��)
 * @param unsigned short Comm2 : �R�}���h2(RW�ʐM�d�l���Q��)
 * @param unsigned short Comm3 : �R�}���h3(RW�ʐM�d�l���Q��)
 * @return 0 : ����I��
 */
int		RW_tx_comm(RW_STRUCT *my_rw, unsigned char Comm1, unsigned short Comm2, unsigned short Comm3){
	my_rw->rw_tx_comm.comm1.byte = (Comm1 & 0x07);
	my_rw->rw_tx_comm.comm2 = Comm2;
	my_rw->rw_tx_comm.comm3 = Comm3;
	
	return(0);
}

/**
 * @memberof RW_STRUCT
 * @public
 * @brief RW�ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * 
 * ���̊֐������s����x�Ƀ��b�Z�[�W�i���o�[�l�������ŃC���N�������g(256��0�Ƀ��Z�b�g)���đ��M���܂��B
 * @note �G���f�B�A���̕ϊ��� endian_conv() ���g�p���čs���Ă��܂��B
 * @note BCC�̎Z�o�� exor() ���g�p���čs���Ă��܂��B
 * @param RW_STRUCT *my_rw : �ΏۂƂ���RW�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_cycle() �̖߂�l���Q��)
 */
int		RW_cycle(RW_STRUCT *my_rw){
	int		i_ret;
	unsigned char	rw_tx_frame[RW_TX_FRAME_SIZE] = {0x02, 0x01, 0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,};
	unsigned short	Comm2;
	
	// 2013/01/15 Changed by kkamiya
	/*
	if((my_rw->rw_tx_comm.comm2) > 28000){	// 28V�ȏォ���Ă͂Ȃ�Ȃ�
		Comm2 = (unsigned short)(((double)(28000) / 50000) * 0xFFFF);
	}else{
		Comm2 = (unsigned short)(((double)(my_rw->rw_tx_comm.comm2) / 50000) * 0xFFFF);
	}
	*/
	
	if((my_rw->rw_tx_comm.comm2) > (unsigned short)(28000.0 / 50000.0 * (double)0x10000)){	// 28V�ȏォ���Ă͂Ȃ�Ȃ�
		Comm2 = (unsigned short)(28000.0 / 50000.0 * (double)0x10000);
	}else{
		Comm2 = my_rw->rw_tx_comm.comm2;
	}
	//Printf("Comm2: %04X\n", Comm2);
	
	my_rw->driver_super.periodic_config.tx_frame = rw_tx_frame;
	
	my_rw->rw_tx_comm.mess_no++;
	my_rw->rw_tx_comm.mess_no %= 256;
	rw_tx_frame[2] = my_rw->rw_tx_comm.mess_no;
	my_rw->rw_tx_comm.comm1.byte &= 0x07;
	endian_conv(&(my_rw->rw_tx_comm.comm1.byte), &(rw_tx_frame[3]), sizeof(my_rw->rw_tx_comm.comm1.byte));
	endian_conv(&Comm2, &(rw_tx_frame[4]), sizeof(Comm2));
	endian_conv(&(my_rw->rw_tx_comm.comm3), &(rw_tx_frame[6]), sizeof(my_rw->rw_tx_comm.comm3));
	rw_tx_frame[9] = exor(&(rw_tx_frame[1]), 8);
	
		#ifdef	RW_DEBUG
			Printf("RW: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_rw->driver_super), &(my_rw->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof RW_STRUCT
 * @public
 * @brief RW����̃f�[�^�p�P�b�g���Ď����A��M�������e�� RW_STRUCT �Ɋi�[���܂��B
 * 
 * RW�̃f�[�^�o�͎����ł���A20Hz��葁�������Œ���I�Ɏ��s���Ă��������B
 * @note �f�[�^�p�P�b�g�ɂ��Ă� DRIVER_Super_rec() ���g�p���ăt���[���������Ƃ�A
 * �t���[���������Ƃꂽ�ꍇ�Ɏ�M���e�� RW_STRUCT �Ɋi�[���܂��B
 * @param RW_STRUCT *my_rw : �ΏۂƂ���RW�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1000 : BCC�G���[
 * @return ��L�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int RW_rec(RW_STRUCT* my_rw){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_rw->driver_super), &(my_rw->rs422_config));
	if(i_ret == 1){
			#ifdef	RW_DEBUG
				Printf("RW: *** Frame ***\n");
			#endif
		if(RW_Data_Conv(my_rw) == 1){
			return(1000);
		}
	}
	
	return(i_ret);
}

/**
 * @memberof RW_STRUCT
 * @public
 * @brief RW�\���̂̃f�[�^���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param RW_STRUCT *my_rw : �ΏۂƂ���RW�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int RW_debug_message(RW_STRUCT* my_rw){
	Printf("MessNO:%u ", (unsigned int)my_rw->rw_rx_sts.mess_no);
	Printf("Sts1:0x%2X ", my_rw->rw_rx_sts.sts1.byte);
	Printf("Sts2:0x%2X ", my_rw->rw_rx_sts.sts2.byte);
	Printf("Sts3:%u ", (unsigned int)my_rw->rw_rx_sts.sts3);
	Printf("Sts4:%d ", (int)my_rw->rw_rx_sts.sts4);
	Printf("Sts5:%d ", (int)my_rw->rw_rx_sts.sts5);
	
	DRIVER_Super_debug_message(&(my_rw->driver_super));
	
	
	return(0);
}

/**
 * @memberof RW_STRUCT
 * @public
 * @brief RW�ցu�p�����[�^�v��1(�d���֘A)�v�R�}���h�𑗐M���A�X�e�[�^�X���擾���܂��B
 * 
 * @note aosc_super�ɔ����R�}���h���s���ƁA���̃R�}���h�ɑ΂��郌�X�|���X��M���̏����������݁A
 *  DRIVER_Super_conf() �����s���Ă��܂��B
 * @param RW_STRUCT *my_rw : �ΏۂƂ���RW�\���̂ւ̃|�C���^
 * @param unsigned short *current_gain : �d���Q�C���i�[��̃|�C���^
 * @param unsigned short *current_integ_gain : �d���ϕ��Q�C���i�[��̃|�C���^
 * @param unsigned short *current_limit : �d�������l(�P��:mA)�i�[��̃|�C���^
 * @return 1 : ���X�|���X����
 * @return 1000 : ���X�|���X�̃t���[�������͐��킾���A���M�������b�Z�[�W�i���o�[�ƈ�v���Ȃ�
 * @return 2000 : ���X�|���X�̃t���[�������͐��킾���AOBC����BCC�G���[�ƕԓ����ꂽ
 * @return 3000 : ���X�|���X�̃t���[�������͐��킾���ARW�������BCC����v���Ȃ�
 * @return ��L�ȊO : ���X�|���X�ُ�(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		RW_Parameter_Request1(RW_STRUCT *my_rw, unsigned short *current_gain, unsigned short *current_integ_gain, unsigned short *current_limit){
	int	ret;
	unsigned char	rw_param_req1[5] = {0x02, 0x10, 0x00, 0x03, 0x00};
	unsigned char	rw_param_req1_rx_header[2] = {0x02, 0x10};
	unsigned short	res_tmp;
	
	my_rw->param_req_mess_no++;
	rw_param_req1[2] = my_rw->param_req_mess_no;
	
	rw_param_req1[4] = exor(&(rw_param_req1[1]), 3);
	
	my_rw->driver_super.non_periodic_config.tx_frame_size = sizeof(rw_param_req1);
	my_rw->driver_super.non_periodic_config.tx_frame = rw_param_req1;
	
	my_rw->driver_super.non_periodic_config.rx_header_size = sizeof(rw_param_req1_rx_header);
	my_rw->driver_super.non_periodic_config.rx_header = rw_param_req1_rx_header;
	
	my_rw->driver_super.non_periodic_config.rx_footer_size = 0;
	
	my_rw->driver_super.non_periodic_config.rx_frame_size = 12;
	
	ret = DRIVER_Super_conf(&(my_rw->driver_super), &(my_rw->rs422_config));
	
	if(ret == 1){
		if((my_rw->driver_super.non_periodic_rx_frame[2]) != my_rw->param_req_mess_no){
			return (1000);
		}
		if((my_rw->driver_super.non_periodic_rx_frame[3]) != 0x00){
			return (2000);
		}
		if((my_rw->driver_super.non_periodic_rx_frame[11]) != exor(&(my_rw->driver_super.non_periodic_rx_frame[1]), 10)){
			return (3000);
		}
		
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[4]), &(res_tmp), sizeof(res_tmp));
		*current_gain = res_tmp;
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[6]), &(res_tmp), sizeof(res_tmp));
		*current_integ_gain = res_tmp;
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[8]), &(res_tmp), sizeof(res_tmp));
		*current_limit = res_tmp * 10;
	}
	
	return (ret);
}

/**
 * @memberof RW_STRUCT
 * @public
 * @brief RW�ցu�p�����[�^�v��2(���x�֘A)�v�R�}���h�𑗐M���A�X�e�[�^�X���擾���܂��B
 * 
 * @note aosc_super�ɔ����R�}���h���s���ƁA���̃R�}���h�ɑ΂��郌�X�|���X��M���̏����������݁A
 *  DRIVER_Super_conf() �����s���Ă��܂��B
 * @param RW_STRUCT *my_rw : �ΏۂƂ���RW�\���̂ւ̃|�C���^
 * @param unsigned short *temperature_gain : ���x�Q�C��(LSB:0.01)�i�[��̃|�C���^
 * @param unsigned short *temperature_offset : ���x�I�t�Z�b�g(LSB:0.01)�i�[��̃|�C���^
 * @param unsigned short *system_config : �V�X�e���ݒ�l�i�[��̃|�C���^
 * @return 1 : ���X�|���X����
 * @return 1000 : ���X�|���X�̃t���[�������͐��킾���A���M�������b�Z�[�W�i���o�[�ƈ�v���Ȃ�
 * @return 2000 : ���X�|���X�̃t���[�������͐��킾���AOBC����BCC�G���[�ƕԓ����ꂽ
 * @return 3000 : ���X�|���X�̃t���[�������͐��킾���ARW�������BCC����v���Ȃ�
 * @return ��L�ȊO : ���X�|���X�ُ�(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		RW_Parameter_Request2(RW_STRUCT *my_rw, unsigned short *temperature_gain, unsigned short *temperature_offset, unsigned short *system_config){
	int	ret;
	unsigned char	rw_param_req2[5] = {0x02, 0x12, 0x00, 0x03, 0x00};
	unsigned char	rw_param_req2_rx_header[2] = {0x02, 0x12};
	unsigned short	res_tmp;
	
	my_rw->param_req_mess_no++;
	rw_param_req2[2] = my_rw->param_req_mess_no;
	
	rw_param_req2[4] = exor(&(rw_param_req2[1]), 3);
	
	my_rw->driver_super.non_periodic_config.tx_frame_size = sizeof(rw_param_req2);
	my_rw->driver_super.non_periodic_config.tx_frame = rw_param_req2;
	
	my_rw->driver_super.non_periodic_config.rx_header_size = sizeof(rw_param_req2_rx_header);
	my_rw->driver_super.non_periodic_config.rx_header = rw_param_req2_rx_header;
	
	my_rw->driver_super.non_periodic_config.rx_footer_size = 0;
	
	my_rw->driver_super.non_periodic_config.rx_frame_size = 12;
	
	ret = DRIVER_Super_conf(&(my_rw->driver_super), &(my_rw->rs422_config));
	
	if(ret == 1){
		if((my_rw->driver_super.non_periodic_rx_frame[2]) != my_rw->param_req_mess_no){
			return (1000);
		}
		if((my_rw->driver_super.non_periodic_rx_frame[3]) != 0x00){
			return (2000);
		}
		if((my_rw->driver_super.non_periodic_rx_frame[11]) != exor(&(my_rw->driver_super.non_periodic_rx_frame[1]), 10)){
			return (3000);
		}
		
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[4]), &(res_tmp), sizeof(res_tmp));
		*temperature_gain = res_tmp;
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[6]), &(res_tmp), sizeof(res_tmp));
		*temperature_offset = res_tmp;
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[8]), &(res_tmp), sizeof(res_tmp));
		*system_config = res_tmp;
	}
	
	return (ret);
}

/**
 * @memberof RW_STRUCT
 * @public
 * @brief RW�ցu�p�����[�^�ݒ�1(�d���֘A)�v�R�}���h�𑗐M���A���̐��ۂ��擾���܂��B
 * 
 * @note aosc_super�ɔ����R�}���h���s���ƁA���̃R�}���h�ɑ΂��郌�X�|���X��M���̏����������݁A
 *  DRIVER_Super_conf() �����s���Ă��܂��B
 * @param RW_STRUCT *my_rw : �ΏۂƂ���RW�\���̂ւ̃|�C���^
 * @param unsigned short current_gain : �d���Q�C���ݒ�l
 * @param unsigned short current_integ_gain : �d���ϕ��Q�C���ݒ�l
 * @param unsigned short current_limit : �d������(�P��:mA)�ݒ�l
 * @return 1 : ���X�|���X����
 * @return 1000 : ���X�|���X�̃t���[�������͐��킾���A���M�������b�Z�[�W�i���o�[�ƈ�v���Ȃ�
 * @return 2000�ԑ� : ���X�|���X�̃t���[�������͐��킾���A�ُ�X�e�[�^�X�̃r�b�g�������Ă���(�ڍׂ�-2000������ RW�ʐM�d�l���Q��)
 * @return 3000 : ���X�|���X�̃t���[�������͐��킾���ARW�������BCC����v���Ȃ�
 * @return ��L�ȊO : ���X�|���X�ُ�(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		RW_Parameter_Config1(RW_STRUCT *my_rw, unsigned short current_gain, unsigned short current_integ_gain, unsigned short current_limit){
	int	ret;
	unsigned char	rw_param_cfg1[11] = {0x02, 0x11, 0x00,
										 0x00, 0x00,
										 0x00, 0x00,
										 0x00, 0x00,
										 0x03, 0x00
										};
	unsigned char	rw_param_cfg1_rx_header[2] = {0x02, 0x11};
	unsigned short	res_tmp;
	
	my_rw->param_cfg_mess_no++;
	rw_param_cfg1[2] = my_rw->param_cfg_mess_no;
	
	endian_conv(&current_gain, &(rw_param_cfg1[3]), sizeof(current_gain));
	endian_conv(&current_integ_gain, &(rw_param_cfg1[5]), sizeof(current_integ_gain));
	current_limit /= 10;
	endian_conv(&current_limit, &(rw_param_cfg1[7]), sizeof(current_limit));
	
	rw_param_cfg1[10] = exor(&(rw_param_cfg1[1]), 9);
	
	my_rw->driver_super.non_periodic_config.tx_frame_size = sizeof(rw_param_cfg1);
	my_rw->driver_super.non_periodic_config.tx_frame = rw_param_cfg1;
	
	my_rw->driver_super.non_periodic_config.rx_header_size = sizeof(rw_param_cfg1_rx_header);
	my_rw->driver_super.non_periodic_config.rx_header = rw_param_cfg1_rx_header;
	
	my_rw->driver_super.non_periodic_config.rx_footer_size = 0;
	
	my_rw->driver_super.non_periodic_config.rx_frame_size = 12;
	
	ret = DRIVER_Super_conf(&(my_rw->driver_super), &(my_rw->rs422_config));
	
	if(ret == 1){
		if((my_rw->driver_super.non_periodic_rx_frame[2]) != my_rw->param_cfg_mess_no){
			return (1000);
		}
		if(((my_rw->driver_super.non_periodic_rx_frame[3]) & 0x07) != 0x00){
			return (2000 + ((my_rw->driver_super.non_periodic_rx_frame[3]) & 0x07));
		}
		if((my_rw->driver_super.non_periodic_rx_frame[11]) != exor(&(my_rw->driver_super.non_periodic_rx_frame[1]), 10)){
			return (3000);
		}
		
		/*endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[4]), &(res_tmp), sizeof(res_tmp));
		if(res_tmp != current_gain){
			return (4001);
		}
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[6]), &(res_tmp), sizeof(res_tmp));
		if(res_tmp != current_integ_gain){
			return (4002);
		}
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[8]), &(res_tmp), sizeof(res_tmp));
		if(res_tmp != current_limit){
			return (4003);
		}*/
		
	}
	
	return (ret);
}

/**
 * @memberof RW_STRUCT
 * @public
 * @brief RW�ցu�p�����[�^�ݒ�2(���x�֘A)�v�R�}���h�𑗐M���A���̐��ۂ��擾���܂��B
 * 
 * @note aosc_super�ɔ����R�}���h���s���ƁA���̃R�}���h�ɑ΂��郌�X�|���X��M���̏����������݁A
 *  DRIVER_Super_conf() �����s���Ă��܂��B
 * @param RW_STRUCT *my_rw : �ΏۂƂ���RW�\���̂ւ̃|�C���^
 * @param unsigned short temperature_gain : ���x�Q�C��(LSB:0.01)�ݒ�l
 * @param unsigned short temperature_offset : ���x�I�t�Z�b�g(LSB:0.01)�ݒ�l
 * @param unsigned short system_config : �V�X�e���ݒ�l
 * @return 1 : ���X�|���X����
 * @return 1000 : ���X�|���X�̃t���[�������͐��킾���A���M�������b�Z�[�W�i���o�[�ƈ�v���Ȃ�
 * @return 2000�ԑ� : ���X�|���X�̃t���[�������͐��킾���A�ُ�X�e�[�^�X�̃r�b�g�������Ă���(�ڍׂ�-2000������ RW�ʐM�d�l���Q��)
 * @return 3000 : ���X�|���X�̃t���[�������͐��킾���ARW�������BCC����v���Ȃ�
 * @return ��L�ȊO : ���X�|���X�ُ�(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		RW_Parameter_Config2(RW_STRUCT *my_rw, unsigned short temperature_gain, unsigned short temperature_offset, unsigned short system_config){
	int	ret;
	unsigned char	rw_param_cfg2[11] = {0x02, 0x13, 0x00,
										 0x00, 0x00,
										 0x00, 0x00,
										 0x00, 0x00,
										 0x03, 0x00
										};
	unsigned char	rw_param_cfg2_rx_header[2] = {0x02, 0x13};
	unsigned short	res_tmp;
	
	my_rw->param_cfg_mess_no++;
	rw_param_cfg2[2] = my_rw->param_cfg_mess_no;
	
	endian_conv(&temperature_gain, &(rw_param_cfg2[3]), sizeof(temperature_gain));
	endian_conv(&temperature_offset, &(rw_param_cfg2[5]), sizeof(temperature_offset));
	endian_conv(&system_config, &(rw_param_cfg2[7]), sizeof(system_config));
	
	rw_param_cfg2[10] = exor(&(rw_param_cfg2[1]), 9);
	
	my_rw->driver_super.non_periodic_config.tx_frame_size = sizeof(rw_param_cfg2);
	my_rw->driver_super.non_periodic_config.tx_frame = rw_param_cfg2;
	
	my_rw->driver_super.non_periodic_config.rx_header_size = sizeof(rw_param_cfg2_rx_header);
	my_rw->driver_super.non_periodic_config.rx_header = rw_param_cfg2_rx_header;
	
	my_rw->driver_super.non_periodic_config.rx_footer_size = 0;
	
	my_rw->driver_super.non_periodic_config.rx_frame_size = 12;
	
	ret = DRIVER_Super_conf(&(my_rw->driver_super), &(my_rw->rs422_config));
	
	if(ret == 1){
		if((my_rw->driver_super.non_periodic_rx_frame[2]) != my_rw->param_cfg_mess_no){
			return (1000);
		}
		if(((my_rw->driver_super.non_periodic_rx_frame[3]) & 0x07) != 0x00){
			return (2000 + ((my_rw->driver_super.non_periodic_rx_frame[3]) & 0x07));
		}
		if((my_rw->driver_super.non_periodic_rx_frame[11]) != exor(&(my_rw->driver_super.non_periodic_rx_frame[1]), 10)){
			return (3000);
		}
		
		/*endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[4]), &(res_tmp), sizeof(res_tmp));
		if(res_tmp != temperature_gain){
			return (4001);
		}
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[6]), &(res_tmp), sizeof(res_tmp));
		if(res_tmp != temperature_offset){
			return (4002);
		}
		endian_conv(&(my_rw->driver_super.non_periodic_rx_frame[8]), &(res_tmp), sizeof(res_tmp));
		if(res_tmp != system_config){
			return (4003);
		}*/
		
	}
	
	return (ret);
}


//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof RW_STRUCT
 * @private
 * @brief �t���[���f�[�^��RW�\���̂̃f�[�^���e�ɕϊ����܂��B
 * 
 * ��M�����f�[�^��BCC�̃`�F�b�N���s���A�����������ꍇ�ɂ̂�RW�\���̂Ɋi�[���܂��B
 * �H�w�l�ϊ����K�v�ȏꍇ�͂����ɏ������݂܂��B
 * @note BCC�̎Z�o�� exor() ���g�p���čs���Ă��܂��B
 * @note �G���f�B�A���̕ϊ��� endian_conv() ���g�p���čs���Ă��܂��B
 * @param RW_STRUCT *my_rw : �ΏۂƂ���RW�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 1 : BCC�G���[
 */
int		RW_Data_Conv(RW_STRUCT* my_rw){
	/** @brief �t���[���f�[�^�̃w�b�_�����I�t�Z�b�g�����|�C���^*/
	unsigned char *rw_rx_data = my_rw->driver_super.periodic_rx_frame + sizeof(rw_rx_header);
	
	if(*(rw_rx_data + 10) != exor(&(my_rw->driver_super.periodic_rx_frame[1]), 11)){
			#ifdef	RW_DEBUG
				Printf("RW: *** BCC Error ***\n");
			#endif
		return (1);
	}
	
	my_rw->rw_rx_sts.mess_no = *(rw_rx_data + 0);
	endian_conv((rw_rx_data + 1), &(my_rw->rw_rx_sts.sts1.byte), sizeof(my_rw->rw_rx_sts.sts1.byte));
	endian_conv((rw_rx_data + 2), &(my_rw->rw_rx_sts.sts2.byte), sizeof(my_rw->rw_rx_sts.sts2.byte));
	endian_conv((rw_rx_data + 3), &(my_rw->rw_rx_sts.sts3), sizeof(my_rw->rw_rx_sts.sts3));
	endian_conv((rw_rx_data + 5), &(my_rw->rw_rx_sts.sts4), sizeof(my_rw->rw_rx_sts.sts4));
	endian_conv((rw_rx_data + 7), &(my_rw->rw_rx_sts.sts5), sizeof(my_rw->rw_rx_sts.sts5));
	
	return (0);
}
