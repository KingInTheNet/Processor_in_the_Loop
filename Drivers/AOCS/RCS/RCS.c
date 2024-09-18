/**
 * @file RCS.c
 * @brief RCS�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * RCS�C���^�[�t�F�[�X���W���[���́A��s��RCS�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g�A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.10.06
 */

#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "../../../../Port_Config.h"		//�f�o�b�O���[�h�̎��ɂ͕K�v

#include "RCS.h"

//#define	RCS_DEBUG


int		RCS_Data_Conv(RCS_STRUCT *my_rcs);


#define RCS_RX_FRAME_SIZE			26	/**< @brief ��M�t���[���̒���*/
#define RCS_TX_FRAME_SIZE			8	/**< @brief ���M�t���[���̒���*/

static unsigned int		rcs_dummy1;
static unsigned char	rcs_tx_frame[RCS_TX_FRAME_SIZE];	/**< @brief ���M�t���[��(�ėp)*/
static unsigned int		rcs_dummy2;
static unsigned char	rcs_tx_frame_periodic[RCS_TX_FRAME_SIZE] = {0x80, 0x80, 0x01, 0x00, 0x10, 0x00, 0x81, 0x81};	/**< @brief ���M�t���[��(������M(�e�����v��)�p)*/

static unsigned char	rcs_header[2] = {0x80, 0x80};	/**< @brief �t���[���̃w�b�_*/
static unsigned char	rcs_footer[2] = {0x81, 0x81};	/**< @brief �t���[���̃t�b�^*/

//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCS�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA RCS_STRUCT.driver_super �ɒ����M���̃w�b�_,�t�b�^,�t���[���T�C�Y�A����R�}���h���s���̏����L�^���܂��B
 * �܂��A�������Ɠ����ɁARCS�ɑ΂��ďo�͂��u�W���o�́v�݂̂ɂ���悤�ɃR�}���h�𔭍s���܂��B
 * @note RCS�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param RCS_STRUCT *my_rcs : ����������RCS�\���̂ւ̃|�C���^
 * @param unsigned char ch : RCS���ڑ�����Ă���UART�|�[�g�ԍ�
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_init() �̖߂�l���Q��)
 */
int		RCS_init(RCS_STRUCT *my_rcs, unsigned char ch){
    int		i_ret;
	
	my_rcs->rs422_config.ch = ch;
	my_rcs->rs422_config.baudrate = 38400;
	my_rcs->rs422_config.stop_bit = 1;
	
	my_rcs->driver_super.inter_face = RS422;
	
	my_rcs->driver_super.periodic_config.rx_header_size = sizeof(rcs_header);
	my_rcs->driver_super.periodic_config.rx_header = rcs_header;
	
	my_rcs->driver_super.periodic_config.rx_footer_size = sizeof(rcs_footer);
	my_rcs->driver_super.periodic_config.rx_footer = rcs_footer;
	
	my_rcs->driver_super.periodic_config.rx_frame_size = RCS_RX_FRAME_SIZE;
	
	my_rcs->driver_super.periodic_config.tx_frame_size = sizeof(rcs_tx_frame_periodic);
	my_rcs->driver_super.periodic_config.tx_frame = rcs_tx_frame_periodic;
	
	if((i_ret = DRIVER_Super_init(&(my_rcs->driver_super), &(my_rcs->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	return(0);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCS�����p�̃f�o�b�O���[�h�ł��B
 * 
 * �f�o�b�O�R���\�[�����RCS����̃X�e�[�^�X��\��������ARCS�ɑ΂��R�}���h�𑗐M�����肵�܂��B
 * @param �Ȃ�
 * @return �Ȃ�
 */
void Debug_RCS(void){
	extern RCS_STRUCT	rcs1;
	u_char				c;
	unsigned int	end_flg = 0;
	int				cnt = 0;
	int				debug_rcs_loop = 1;
	int				i_ret;
	unsigned int	tmp = 0;
	
	//	Channel Setting
	Printf("RCS Test \n");
	while(!end_flg){
		Printf("  Which channel (0-15) ?\n");
		ScanfUIntD( &tmp );
		if(tmp < 0 || tmp > 15){
			Printf("Illegal Ch Number\n");
		}else{
			end_flg = 1;
		}
	}
	end_flg = 0;
	
	i_ret = RCS_init(&rcs1, (unsigned char)tmp);
	if(i_ret != 0){
		Printf("RCS Init Error (%d)\n", i_ret);
		return;
	}
	
	Printf("============  1:Init     2:Preparation  =========\n");
	Printf("============  4:Start    8:Stop  ================\n");
	Printf("=============  q:Quit  ==========================\n");
	while(debug_rcs_loop){
		MilliSleep(5);
		
		i_ret = RCS_rec(&(rcs1));
		if(i_ret == 1){
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
			
			if(rcs1.flag.bit.vo_au == 0){
				Printf("VO-AU_flag:Close        ");
			}else if(rcs1.flag.bit.vo_au == 1){
				Printf("VO-AU_flag:Open_Wait    ");
			}else if(rcs1.flag.bit.vo_au == 2){
				Printf("VO-AU_flag:Opening      ");
			}else if(rcs1.flag.bit.vo_au == 3){
				Printf("VO-AU_flag:Open         ");
			}
			if(rcs1.flag.bit.vo_ad == 0){
				Printf("VO-AD_flag:Close        ");
			}else if(rcs1.flag.bit.vo_ad == 1){
				Printf("VO-AD_flag:Open_Wait    ");
			}else if(rcs1.flag.bit.vo_ad == 2){
				Printf("VO-AD_flag:Opening      ");
			}else if(rcs1.flag.bit.vo_ad == 3){
				Printf("VO-AD_flag:Open         ");
			}
			Printf("\n");
			if(rcs1.flag.bit.vo_bu == 0){
				Printf("VO-BU_flag:Close        ");
			}else if(rcs1.flag.bit.vo_bu == 1){
				Printf("VO-BU_flag:Open_Wait    ");
			}else if(rcs1.flag.bit.vo_bu == 2){
				Printf("VO-BU_flag:Opening      ");
			}else if(rcs1.flag.bit.vo_bu == 3){
				Printf("VO-BU_flag:Open         ");
			}
			if(rcs1.flag.bit.vo_bd == 0){
				Printf("VO-BD_flag:Close        ");
			}else if(rcs1.flag.bit.vo_bd == 1){
				Printf("VO-BD_flag:Open_Wait    ");
			}else if(rcs1.flag.bit.vo_bd == 2){
				Printf("VO-BD_flag:Opening      ");
			}else if(rcs1.flag.bit.vo_bd == 3){
				Printf("VO-BD_flag:Open         ");
			}
			Printf("\n");
			
			if(rcs1.status.bit.vo_au == 0){
				Printf("VO-AU_pin:Close    ");
			}else if(rcs1.status.bit.vo_au == 1){
				Printf("VO-AU_pin:Open     ");
			}
			if(rcs1.status.bit.vo_ad == 0){
				Printf("VO-AD_pin:Close    ");
			}else if(rcs1.status.bit.vo_ad == 1){
				Printf("VO-AD_pin:Open     ");
			}
			if(rcs1.status.bit.vo_bu == 0){
				Printf("VO-BU_pin:Close    ");
			}else if(rcs1.status.bit.vo_bu == 1){
				Printf("VO-BU_pin:Open     ");
			}
			if(rcs1.status.bit.vo_bd == 0){
				Printf("VO-BD_pin:Close    ");
			}else if(rcs1.status.bit.vo_bd == 1){
				Printf("VO-BD_pin:Open     ");
			}
			Printf("\n");
			if(rcs1.status.bit.flag_12v == 0){
				Printf("12V_flag:OFF    ");
			}else if(rcs1.status.bit.flag_12v == 1){
				Printf("12V_flag:ON     ");
			}
			if(rcs1.status.bit.pin_12v == 0){
				Printf("12V_pin:OFF    ");
			}else if(rcs1.status.bit.pin_12v == 1){
				Printf("12V_pin:ON     ");
			}
			Printf("Mode:L%d", rcs1.status.bit.mode);
			Printf("\n");
			
			if(rcs1.last_cmd == 0x01){
				Printf("LastCmd:Init           ");
			}else if(rcs1.last_cmd == 0x02){
				Printf("LastCmd:Preparation    ");
			}else if(rcs1.last_cmd == 0x04){
				Printf("LastCmd:Start          ");
			}else if(rcs1.last_cmd == 0x08){
				Printf("LastCmd:Stop           ");
			}else if(rcs1.last_cmd == 0x10){
				Printf("LastCmd:Tlm_Req        ");
			}else{
				Printf("LastCmd:?              ");
			}
			Printf("Ack:0x%02X", rcs1.ack);
			Printf("\n");
			
			Printf("Tank_reference_tempe:%5d         ", rcs1.tt0);
			Printf("Tank_relative_tempe:%5d", rcs1.tt1);
			Printf("\n");
			
			Printf("Thruster_reference_tempe:%5d     ", rcs1.tc0);
			Printf("Thruster_relative_tempe:%5d", rcs1.tc1);
			Printf("\n");
			
			Printf("Tank_pressure:%5d                ", rcs1.pt);
			Printf("Thruster_pressure:%5d", rcs1.pc);
			Printf("\n");
			
			Printf("Pressure gauge_PT_current:%5d    ", rcs1.i_pt);
			Printf("Pressure gauge_PC_current:%5d", rcs1.i_pc);
			Printf("\n");
			
		}
		
		if(cnt == 0){
			RCS_cycle(&(rcs1));
		}
		cnt++;
		cnt %= 1000;
		
		c = CheckChar();
		if(c == '1'){
			Printf("Send %d\n", RCS_initialize_command(&rcs1));
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
		}else if(c == '2'){
			Printf("  Valve Select (DEC)        Quit : >255\n");
			Printf(" -> ");
			ScanfUIntD( &tmp );
			if(tmp <= 0xFF){
				Printf("Send %d\n", RCS_injection_preparation(&rcs1, (unsigned char)tmp));
			}
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
		}else if(c == '4'){
			Printf("  Injection Time (DEC)        Quit : >255\n");
			Printf(" -> ");
			ScanfUIntD( &tmp );
			if(tmp <= 0xFF){
				Printf("Send %d\n", RCS_injection_start(&rcs1, (unsigned char)tmp));
			}
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
		}else if(c == '8'){
			Printf("Send %d\n", RCS_injection_stop(&rcs1));
			Printf("\n");
			Printf("============  1:Init     2:Preparation  =========\n");
			Printf("============  4:Start    8:Stop  ================\n");
			Printf("=============  q:Quit  ==========================\n");
		}else if(c == 'q' || c == 'Q'){
			debug_rcs_loop = 0;
		}
	}
	
	
	return;
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCS�ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * @param RCS_STRUCT *my_rcs : �ΏۂƂ���RCS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_cycle() �̖߂�l���Q��)
 */
int		RCS_cycle(RCS_STRUCT *my_rcs){
	int		i_ret;
	
		#ifdef	RCS_DEBUG
			Printf("RCS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_rcs->driver_super), &(my_rcs->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCS����̃f�[�^�p�P�b�g���Ď����A��M�������e�� RCS_STRUCT �Ɋi�[���܂��B
 * 
 * ����R�}���h���M������葁�������Œ���I�Ɏ��s���Ă��������B
 * @note �f�[�^�p�P�b�g�ɂ��Ă� DRIVER_Super_rec() ���g�p���ăt���[���������Ƃ�A
 * �t���[���������Ƃꂽ�ꍇ�Ɏ�M���e�� RCS_STRUCT �Ɋi�[���܂��B
 * @param RCS_STRUCT *my_rcs : �ΏۂƂ���RCS�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		RCS_rec(RCS_STRUCT *my_rcs){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret == 1){
			#ifdef	RCS_DEBUG
				Printf("RCS: *** Frame ***\n");
			#endif
		RCS_Data_Conv(my_rcs);
	}
	
	return(i_ret);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCS�\���̂̃f�[�^���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param RCS_STRUCT *my_rcs : �ΏۂƂ���RCS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		RCS_debug_message(RCS_STRUCT* my_rcs){
	Printf("Mode: L%u  ", my_rcs->status.bit.mode);
	if(my_rcs->last_cmd == 0x01){
		Printf("LastCmd: Init  ");
	}else if(my_rcs->last_cmd == 0x02){
		Printf("LastCmd: Preparation  ");
	}else if(my_rcs->last_cmd == 0x04){
		Printf("LastCmd: Start  ");
	}else if(my_rcs->last_cmd == 0x08){
		Printf("LastCmd: Stop  ");
	}else if(my_rcs->last_cmd == 0x10){
		Printf("LastCmd: Tlm_Req  ");
	}else{
		Printf("LastCmd: ?  ");
	}
	
	DRIVER_Super_debug_message(&(my_rcs->driver_super));
	
	
	return(0);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief RCS�̋N���Ə����ݒ���s���R�}���h��RCS�֑��M���܂��B
 * 
 * @param RCS_STRUCT *my_rcs : �ΏۂƂ���RCS�\���̂ւ̃|�C���^
 * @return 1 : ����I��
 * @return 1�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_conf() �̖߂�l���Q��)
 */
int		RCS_initialize_command(RCS_STRUCT *my_rcs){
	int				i_ret;
	unsigned char	*p_tmp;
	
	
	p_tmp = (unsigned char *)rcs_header;
	rcs_tx_frame[0] = *(p_tmp + 0);
	rcs_tx_frame[1] = *(p_tmp + 1);
	
	rcs_tx_frame[2] = 0x01;	// �p�P�b�g��(�Œ�l)
	rcs_tx_frame[3] = 0x00;	// �R���|ID(�Œ�l)
	rcs_tx_frame[4] = 0x01;	// �R�}���hHEX(������)
	rcs_tx_frame[5] = 0x00;	// �R�}���h����(�_�~�[)
	
	p_tmp = (unsigned char *)rcs_footer;
	rcs_tx_frame[6] = *(p_tmp + 0);
	rcs_tx_frame[7] = *(p_tmp + 1);
	
	
	my_rcs->driver_super.non_periodic_config.tx_frame_size = RCS_TX_FRAME_SIZE;
	my_rcs->driver_super.non_periodic_config.tx_frame = rcs_tx_frame;
	
	my_rcs->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief ���ˏ����R�}���h��RCS�֑��M���܂��B
 * 
 * @param RCS_STRUCT *my_rcs : �ΏۂƂ���RCS�\���̂ւ̃|�C���^
 * @param unsigned char valve : �o���u�I��
 * @return 1 : ����I��
 * @return 1�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_conf() �̖߂�l���Q��)
 */
int		RCS_injection_preparation(RCS_STRUCT *my_rcs, unsigned char valve){
	int				i_ret;
	unsigned char	*p_tmp;
	
	
	p_tmp = (unsigned char *)rcs_header;
	rcs_tx_frame[0] = *(p_tmp + 0);
	rcs_tx_frame[1] = *(p_tmp + 1);
	
	rcs_tx_frame[2] = 0x01;	// �p�P�b�g��(�Œ�l)
	rcs_tx_frame[3] = 0x00;	// �R���|ID(�Œ�l)
	rcs_tx_frame[4] = 0x02;	// �R�}���hHEX(���ˏ���)
	rcs_tx_frame[5] = valve;	// �R�}���h����(�o���u�I��)
	
	p_tmp = (unsigned char *)rcs_footer;
	rcs_tx_frame[6] = *(p_tmp + 0);
	rcs_tx_frame[7] = *(p_tmp + 1);
	
	
	my_rcs->driver_super.non_periodic_config.tx_frame_size = RCS_TX_FRAME_SIZE;
	my_rcs->driver_super.non_periodic_config.tx_frame = rcs_tx_frame;
	
	my_rcs->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief ���ˊJ�n�R�}���h��RCS�֑��M���܂��B
 * 
 * @param RCS_STRUCT *my_rcs : �ΏۂƂ���RCS�\���̂ւ̃|�C���^
 * @param unsigned char second : ���˕b��
 * @return 1 : ����I��
 * @return 1�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_conf() �̖߂�l���Q��)
 */
int		RCS_injection_start(RCS_STRUCT *my_rcs, unsigned char second){
	int				i_ret;
	unsigned char	*p_tmp;
	
	
	p_tmp = (unsigned char *)rcs_header;
	rcs_tx_frame[0] = *(p_tmp + 0);
	rcs_tx_frame[1] = *(p_tmp + 1);
	
	rcs_tx_frame[2] = 0x01;	// �p�P�b�g��(�Œ�l)
	rcs_tx_frame[3] = 0x00;	// �R���|ID(�Œ�l)
	rcs_tx_frame[4] = 0x04;	// �R�}���hHEX(���ˊJ�n)
	rcs_tx_frame[5] = second;	// �R�}���h����(���˕b��)
	
	p_tmp = (unsigned char *)rcs_footer;
	rcs_tx_frame[6] = *(p_tmp + 0);
	rcs_tx_frame[7] = *(p_tmp + 1);
	
	
	my_rcs->driver_super.non_periodic_config.tx_frame_size = RCS_TX_FRAME_SIZE;
	my_rcs->driver_super.non_periodic_config.tx_frame = rcs_tx_frame;
	
	my_rcs->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}

/**
 * @memberof RCS_STRUCT
 * @public
 * @brief ���˒�~�R�}���h��RCS�֑��M���܂��B
 * 
 * @param RCS_STRUCT *my_rcs : �ΏۂƂ���RCS�\���̂ւ̃|�C���^
 * @return 1 : ����I��
 * @return 1�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_conf() �̖߂�l���Q��)
 */
int		RCS_injection_stop(RCS_STRUCT *my_rcs){
	int				i_ret;
	unsigned char	*p_tmp;
	
	
	p_tmp = (unsigned char *)rcs_header;
	rcs_tx_frame[0] = *(p_tmp + 0);
	rcs_tx_frame[1] = *(p_tmp + 1);
	
	rcs_tx_frame[2] = 0x01;	// �p�P�b�g��(�Œ�l)
	rcs_tx_frame[3] = 0x00;	// �R���|ID(�Œ�l)
	rcs_tx_frame[4] = 0x08;	// �R�}���hHEX(���˒�~)
	rcs_tx_frame[5] = 0x00;	// �R�}���h����(�_�~�[)
	
	p_tmp = (unsigned char *)rcs_footer;
	rcs_tx_frame[6] = *(p_tmp + 0);
	rcs_tx_frame[7] = *(p_tmp + 1);
	
	
	my_rcs->driver_super.non_periodic_config.tx_frame_size = RCS_TX_FRAME_SIZE;
	my_rcs->driver_super.non_periodic_config.tx_frame = rcs_tx_frame;
	
	my_rcs->driver_super.non_periodic_config.rx_frame_size = 0;
	
	i_ret = DRIVER_Super_conf(&(my_rcs->driver_super), &(my_rcs->rs422_config));
	if(i_ret != 1){		// ERROR
		return (i_ret);
	}
	
	return (i_ret);
}


//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof RCS_STRUCT
 * @private
 * @brief �t���[���f�[�^��RCS�\���̂̃f�[�^���e�ɕϊ����܂��B
 * 
 * �H�w�l�ϊ����K�v�ȏꍇ�͂����ɏ������݂܂��B
 * @param RCS_STRUCT *my_rcs : �ΏۂƂ���RCS�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		RCS_Data_Conv(RCS_STRUCT* my_rcs){
	/** @brief �t���[���f�[�^�̃w�b�_�����I�t�Z�b�g�����|�C���^*/
	unsigned char *rcs_rx_data = my_rcs->driver_super.periodic_rx_frame + sizeof(rcs_header);
	
	// �p�P�b�g��(�Œ�l) = *(rcs_rx_data + 0);
	// �R���|ID(�Œ�l) = *(rcs_rx_data + 1);
	
	my_rcs->flag.byte = *(rcs_rx_data + 2);
	my_rcs->status.byte = *(rcs_rx_data + 3);
	
	my_rcs->last_cmd = *(rcs_rx_data + 4);
	my_rcs->ack = *(rcs_rx_data + 5);
	
	my_rcs->tt0 = ((*(rcs_rx_data + 6)) * 16) + (*(rcs_rx_data + 7));
	my_rcs->tt1 = ((*(rcs_rx_data + 8)) * 16) + (*(rcs_rx_data + 9));
	my_rcs->tc0 = ((*(rcs_rx_data + 10)) * 256) + (*(rcs_rx_data + 11));
	my_rcs->tc1 = ((*(rcs_rx_data + 12)) * 256) + (*(rcs_rx_data + 13));
	my_rcs->pt = ((*(rcs_rx_data + 14)) * 256) + (*(rcs_rx_data + 15));
	my_rcs->pc = ((*(rcs_rx_data + 16)) * 256) + (*(rcs_rx_data + 17));
	my_rcs->i_pt = ((*(rcs_rx_data + 18)) * 256) + (*(rcs_rx_data + 19));
	my_rcs->i_pc = ((*(rcs_rx_data + 20)) * 256) + (*(rcs_rx_data + 21));
	
	return (0);
}
