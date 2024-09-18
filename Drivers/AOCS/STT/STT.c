/**
 * @file STT.c
 * @brief STT�Ƃ̃C���^�[�t�F�[�X���W���[���Q�ł��B
 * 
 * STT�C���^�[�t�F�[�X���W���[���́AAxelSpace��AXELSTAR-2�Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g�A�f�[�^�擾���s�����W���[���Q�ł��B
 * @author ���� �@���Y
 * @date 2012.11.01
 */

#include "utility.h"	// Printf()�g�p���ɂ͕K�v

#include "STT.h"

//#define	STT_DEBUG


int				STT_Data_Conv(STT_STRUCT *my_stt);

#define STT_RX_FRAME_SIZE			241	/**< @brief ��M�t���[���̒���(�I�[�g���[�h��)*/
//#define STT_RX_FRAME_SIZE			242	/**< @brief ��M�t���[���̒���(�I�[�g���[�h��)*/

static unsigned char	stt_rx_header[4] = {'s', 't', '2', 'z'};	/**< @brief ��M�t���[���̃w�b�_(�I�[�g���[�h��)*/

//*****************************************************************************
//	�C���^�[�t�F�[�X���W���[��
//*****************************************************************************
/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * 
 * �����āA STT_STRUCT.driver_super �ɒ����M���̃w�b�_,�t�b�^,�t���[���T�C�Y�A����R�}���h���s���̏����L�^���܂��B
 * @note STT�C���^�[�t�F�[�X���W���[�����g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @param STT_STRUCT *my_stt : ����������STT�\���̂ւ̃|�C���^
 * @param unsigned char ch : STT���ڑ�����Ă���UART�|�[�g�ԍ�
 * @param unsigned short up_enable_bit : STT�́uUP-ENABLE�v�s�����ڑ�����Ă���DC�|�[�g�ԍ�
 * @return 0 : ����I��
 * @return 100�ԑ� : �ُ�I��(�ڍׂ� DRIVER_Super_init() �̖߂�l���Q��)
 * @return 100000�ԑ� : �ُ�I��(�ڍׂ�-100000���� DC_init() �̖߂�l���Q��)
 */
int		STT_init(STT_STRUCT* my_stt, unsigned char ch, unsigned short up_enable_bit){
    int		i_ret;
	
	my_stt->dc_config.ch_out = up_enable_bit;
	
	my_stt->rs422_config.ch = ch;
	my_stt->rs422_config.baudrate = 115200;
	my_stt->rs422_config.stop_bit = 1;
	
	my_stt->driver_super.inter_face = RS422;
	
	my_stt->driver_super.periodic_config.rx_header_size = sizeof(stt_rx_header);
	my_stt->driver_super.periodic_config.rx_header = stt_rx_header;
	
	my_stt->driver_super.periodic_config.rx_footer_size = 0;
	
	my_stt->driver_super.periodic_config.rx_frame_size = STT_RX_FRAME_SIZE;
	
	my_stt->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_stt->driver_super), &(my_stt->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	if((i_ret = DC_init(&(my_stt->dc_config))) != 0){
		return (100000 + i_ret);
	}
	
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ɑ΂��Ē���R�}���h�𑗐M���܂��B
 * 
 * �{STT�͒���R�}���h���M���s�v�Ȃ̂ŁA���̊֐��͎��s���Ă������N���܂���
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 0�ȊO : �ُ�I��(�ڍׂ� DRIVER_Super_cycle() �̖߂�l���Q��)
 */
int		STT_cycle(STT_STRUCT* my_stt){
	int		i_ret;
	
		#ifdef	STT_DEBUG
			Printf("STT: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_stt->driver_super), &(my_stt->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT����̃f�[�^�p�P�b�g���Ď����A��M�������e�� STT_STRUCT �Ɋi�[���܂��B
 * 
 * STT�̃f�[�^�o�͎����ł���A1�b��葁�������Œ���I�Ɏ��s���Ă��������B
 * @note �f�[�^�p�P�b�g�ɂ��Ă� DRIVER_Super_rec() ���g�p���ăt���[���������Ƃ�A
 * �t���[���������Ƃꂽ�ꍇ�Ɏ�M���e�� STT_STRUCT �Ɋi�[���܂��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 1 : �t���[����������
 * @return 1�ȊO : �f�[�^����M����Ȃ�������(�ڍׂ� DRIVER_Super_rec() �̖߂�l���Q��)
 */
int		STT_rec(STT_STRUCT* my_stt){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_stt->driver_super), &(my_stt->rs422_config));
	if(i_ret == 1){
			#ifdef	STT_DEBUG
				Printf("STT: *** Frame ***\n");
			#endif
		STT_Data_Conv(my_stt);
	}
	
	return(i_ret);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�\���̂̃f�[�^���f�o�b�O�R���\�[����ɕ\�����܂��B
 * 
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		STT_debug_message(STT_STRUCT* my_stt){
	Printf("Capt_ID:%u ", (unsigned int)my_stt->capture_id);
	Printf("Tempe:%f ", my_stt->master_imager_temperature);
	Printf("Quat[0]:%f ", my_stt->attitude[0]);
	Printf("Quat[1]:%f ", my_stt->attitude[1]);
	Printf("Quat[2]:%f ", my_stt->attitude[2]);
	Printf("Quat[3]:%f ", my_stt->attitude[3]);
	
	DRIVER_Super_debug_message(&(my_stt->driver_super));
	
	
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT���u�I�[�g���[�h�v�ֈڍs�����鏈��������֐��ł��B
 * 
 *  STT_Up_Enable_Idle() �ɂ��ADC�M���́uUP-ENABLE�v�s����"HIGH"�ɂ��āuIdle State�v�Ɉڍs�����A
 * �uGet/Change Power State�v�R�}���h�𔭍s���āuCapture State�v�Ɉڍs�����A
 * �uChange Output Mode�v�R�}���h�𔭍s���ďo�̓��[�h��ύX�����A
 * �uStart/Stop Output�v�R�}���h�𔭍s���ĎB�e���J�n���܂��B
 * @note aosc_super�ɔ����R�}���h���s���ƁA���̃R�}���h�ɑ΂��郌�X�|���X��M���̏����������݁A
 *  DRIVER_Super_conf()�����s���Ă��܂��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 1000�ԑ� : STT_Up_Enable_Power_Down() �łُ̈�I��(�ڍׂ�-1000������ STT_Up_Enable_Power_Down() �̖߂�l���Q��)
 * @return 2000�ԑ� : STT_Up_Enable_Idle() �łُ̈�I��(�ڍׂ�-2000������ STT_Up_Enable_Idle() �̖߂�l���Q��)
 * @return 3000�ԑ� : STT_Change_Power_State_Capture() �łُ̈�I��(�ڍׂ�-3000������ STT_Change_Power_State_Capture() �̖߂�l���Q��)
 * @return 4000�ԑ� : STT_Change_Output_Mode() (1���)�łُ̈�I��(�ڍׂ�-4000������ STT_Change_Output_Mode() �̖߂�l���Q��)
 * @return 5000�ԑ� : STT_Change_Output_Mode() (2���)�łُ̈�I��(�ڍׂ�-5000������ STT_Change_Output_Mode() �̖߂�l���Q��)
 * @return 6000�ԑ� : STT_Start_Output() �łُ̈�I��(�ڍׂ�-6000������ STT_Start_Output() �̖߂�l���Q��)
 */
int		STT_auto_mode(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	state = 0x00;
	
	i_ret = STT_Change_Output_Mode(my_stt, &state);
	if(i_ret != 0){	// Error
		
	}else if(state != 'm'){
		MilliSleep(100);	//100msec wait
		i_ret = STT_Change_Output_Mode(my_stt, &state);
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Change_Power_State_Idle(my_stt)) != 0){	// Error
		
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Up_Enable_Power_Down(my_stt)) != 0){
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Up_Enable_Power_Down +++\n");
			#endif
		return (1000 + i_ret);
	}
	MilliSleep(1000);	//1sec wait
	
	if((i_ret = STT_Up_Enable_Idle(my_stt)) != 0){
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Up_Enable_Idle +++\n");
			#endif
		return (2000 + i_ret);
	}
	MilliSleep(5000);	//5sec wait
	
	if((i_ret = STT_Change_Power_State_Capture(my_stt)) != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Power_State_Capture +++\n");
			#endif
		return (3000 + i_ret);
	}
	MilliSleep(100);	//100msec wait
	
	i_ret = STT_Change_Output_Mode(my_stt, &state);
	if(i_ret != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Output_Mode(2-1) +++\n");
			#endif
		return (4000 + i_ret);
	}else if((state != 'a') && (state != 'b')){
		MilliSleep(100);	//100msec wait
		i_ret = STT_Change_Output_Mode(my_stt, &state);
		if((state != 'a') && (state != 'b')){
				#ifdef	STT_DEBUG
					Printf("STT: +++ STT_Change_Output_Mode(2-2) +++\n");
				#endif
			return (5000 + i_ret);
		}
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Start_Output(my_stt)) != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Start_Output +++\n");
			#endif
		return (6000 + i_ret);
	}
	
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT��d��OFF�ł����Ԃɂ��܂��B
 * 
 * �uChange Output Mode�v�R�}���h�𔭍s���ďo�̓��[�h��ύX�����A
 * �uGet/Change Power State�v�R�}���h�𔭍s���āuIdle State�v�Ɉڍs�����A
 *  STT_Up_Enable_Power_Down() �ɂ��ADC�M���́uUP-ENABLE�v�s����"LOW"�ɂ��āA�uPower-Down State�v�Ɉڍs�����܂��B
 * @note aosc_super�ɔ����R�}���h���s���ƁA���̃R�}���h�ɑ΂��郌�X�|���X��M���̏����������݁A
 *  DRIVER_Super_conf()�����s���Ă��܂��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 1000�ԑ� : STT_Change_Output_Mode() �łُ̈�I��(�ڍׂ�-1000������ STT_Change_Output_Mode() �̖߂�l���Q��)
 * @return 2000�ԑ� : STT_Change_Output_Mode() �łُ̈�I��(�ڍׂ�-2000������ STT_Change_Output_Mode() �̖߂�l���Q��)
 * @return 3000�ԑ� : STT_Change_Power_State_Capture() �łُ̈�I��(�ڍׂ�-3000������ STT_Change_Power_State_Capture() �̖߂�l���Q��)
 * @return 4000�ԑ� : STT_Up_Enable_Power_Down() �łُ̈�I��(�ڍׂ�-4000������ STT_Up_Enable_Power_Down() �̖߂�l���Q��)
 */
int		STT_stop(STT_STRUCT* my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	dc_tx = 0;
	unsigned char	state = 0x00;
	
	i_ret = STT_Change_Output_Mode(my_stt, &state);
	if(i_ret != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Output_Mode +++\n");
			#endif
		return (1000 + i_ret);
	}else if(state != 'm'){
		i_ret = STT_Change_Output_Mode(my_stt, &state);
		MilliSleep(100);	//100msec wait
	}
	
	if(state != 'm'){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Output_Mode +++\n");
			#endif
		return (2000 + i_ret);
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Change_Power_State_Idle(my_stt)) != 0){	// Error
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Change_Power_State_Idle +++\n");
			#endif
		return (3000 + i_ret);
	}
	MilliSleep(100);	//100msec wait
	
	if((i_ret = STT_Up_Enable_Power_Down(my_stt)) != 0){
			#ifdef	STT_DEBUG
				Printf("STT: +++ STT_Up_Enable_Power_Down +++\n");
			#endif
		return (4000 + i_ret);
	}
	
	return(0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ւ́uUP-ENABLE�v�s����"LOW"�ɂ��āuPower-Down State�v�Ɉڍs����֐��ł��B
 * 
 * DC�M���́uUP-ENABLE�v�s����"LOW"�ɂ��āuPower-Down State�v�Ɉڍs�����܂��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return ��L�ȊO : DC_TX() �łُ̈�I��(�ڍׂ� DC_TX() �̖߂�l���Q��)
 */
int		STT_Up_Enable_Power_Down(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	dc_tx = 0;
	
	
	if((i_ret = DC_TX(&(my_stt->dc_config), &dc_tx, sizeof(dc_tx))) != 0){
		return (i_ret);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ւ́uUP-ENABLE�v�s����"HIGH"�ɂ��āuIdle State�v�Ɉڍs����֐��ł��B
 * 
 * DC�M���́uUP-ENABLE�v�s����"HIGH"�ɂ��āuIdle State�v�Ɉڍs�����܂��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return ��L�ȊO : DC_TX() �łُ̈�I��(�ڍׂ� DC_TX() �̖߂�l���Q��)
 */
int		STT_Up_Enable_Idle(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	dc_tx = 1;
	
	
	if((i_ret = DC_TX(&(my_stt->dc_config), &dc_tx, sizeof(dc_tx))) != 0){
		return (i_ret);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet Temperature�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param float *image_sensor_board : �C���[�W�Z���T����x�i�[��ւ̃|�C���^
 * @param float *fpga : FPGA���x�i�[��ւ̃|�C���^
 * @param float *image_sensor : �C���[�W�Z���T���x�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_Temperature(STT_STRUCT *my_stt, float *image_sensor_board, float *fpga, float *image_sensor){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[4] = {'s', 't', '2', 0x02};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x02};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+12;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)image_sensor_board) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)image_sensor_board) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	*(((unsigned char *)image_sensor_board) + 2) = my_stt->driver_super.non_periodic_rx_frame[7];
	*(((unsigned char *)image_sensor_board) + 3) = my_stt->driver_super.non_periodic_rx_frame[8];
	
	*(((unsigned char *)fpga) + 0) = my_stt->driver_super.non_periodic_rx_frame[9];
	*(((unsigned char *)fpga) + 1) = my_stt->driver_super.non_periodic_rx_frame[10];
	*(((unsigned char *)fpga) + 2) = my_stt->driver_super.non_periodic_rx_frame[11];
	*(((unsigned char *)fpga) + 3) = my_stt->driver_super.non_periodic_rx_frame[12];
	
	*(((unsigned char *)image_sensor) + 0) = my_stt->driver_super.non_periodic_rx_frame[13];
	*(((unsigned char *)image_sensor) + 1) = my_stt->driver_super.non_periodic_rx_frame[14];
	*(((unsigned char *)image_sensor) + 2) = my_stt->driver_super.non_periodic_rx_frame[15];
	*(((unsigned char *)image_sensor) + 3) = my_stt->driver_super.non_periodic_rx_frame[16];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet/Change Power State - Capture State�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 * @return 30000�ԑ� : �uCapture State�v�ł͂Ȃ��B�������͕ςȒl���Ԃ��Ă����B(�ڍׂ�-30000�����Ė߂�l���Q��)
 */
int		STT_Change_Power_State_Capture(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x03, 'c'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x03};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[5] != 'c'){
		return (30000 + my_stt->driver_super.non_periodic_rx_frame[5]);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet/Change Power State - Idle State�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 * @return 30000�ԑ� : �uIdle State�v�ł͂Ȃ��B�������͕ςȒl���Ԃ��Ă����B(�ڍׂ�-30000�����Ė߂�l���Q��)
 */
int		STT_Change_Power_State_Idle(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x03, 'i'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x03};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[5] != 'i'){
		return (30000 + my_stt->driver_super.non_periodic_rx_frame[5]);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet Power State�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned char *state : ���݂̓d����Ԋi�[��ւ̃|�C���^(�i�[�l��AXELSTAR-2���[�U�[�Y�}�j���A���́uGet/Change Power State�v�R�}���h���Q��)
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 * @return 30000�ԑ� : �ςȒl���Ԃ��Ă����B(�ڍׂ�-30000�����Ė߂�l���Q��)
 */
int		STT_Get_Power_State(STT_STRUCT *my_stt, unsigned char *state){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x03, 'g'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x03};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*state = my_stt->driver_super.non_periodic_rx_frame[5];
	
	if((*state != 'c') || (*state != 'i')){
		
		return (30000 + *state);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet Exposure Time�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned short *get_time : ���݂̘I�����Ԋi�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_Exposure_Time(STT_STRUCT *my_stt, unsigned short *get_time){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x06, 'g'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x06};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+2;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)get_time) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)get_time) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuSet Exposure Time�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned short *get_time : ���݂̘I�����Ԋi�[��ւ̃|�C���^
 * @param unsigned short set_time : �ݒ肷��I������
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Set_Exposure_Time(STT_STRUCT *my_stt, unsigned short *get_time, unsigned short set_time){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[7] = {'s', 't', '2', 0x06, 's', 0x00, 0x00};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x06};
	
	tx[5] = *(((unsigned char*)&set_time) + 0);
	tx[6] = *(((unsigned char*)&set_time) + 1);
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+2;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)get_time) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)get_time) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuSystem Reset�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 */
int		STT_System_Reset(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[4] = {'s', 't', '2', 0x12};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuCapture/PostProc - Capture Only�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Capture_Only(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x13, 'c'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x13};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuCapture/PostProc - PostProc Only�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_PostProc_Only(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x13, 'p'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x13};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuCapture/PostProc - Capture+PostProc�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Capture_And_PostProc(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x13, 'a'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x13};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet Detected Star Count�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned char *star_count : �C���[�W�Z���T����x�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_Detected_Star_Count(STT_STRUCT *my_stt, unsigned char *star_count){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[4] = {'s', 't', '2', 0x18};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x18};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+2;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)star_count) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)star_count) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet Detected Star Info�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned short read_index : �ǂݏo�����J�n���鐯��index
 * @param unsigned char count : �ǂݏo������
 * @param GET_DETECTED_STAR_INFO_COMMAND_STRUCT *info_data : ���̏��f�[�^�\���̂̔z��̊i�[��ւ̃|�C���^
 * @param unsigned int size : ���̏��f�[�^�\���̂̔z��̊i�[��̃T�C�Y(��L��O������sizeof()���Ă�������)
 * @return 0 : ����I��
 * @return 10000 : ��2�����G���[(64�ȉ��łȂ�)
 * @return 10001 : �f�[�^�i�[��T�C�Y�s��
 * @return 20000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-20000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 30000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-30000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_Detected_Star_Info(STT_STRUCT *my_stt, unsigned short read_index, unsigned char count, GET_DETECTED_STAR_INFO_COMMAND_STRUCT *info_data, unsigned int size){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[7] = {'s', 't', '2', 0x19, 0x00, 0x00, 0x00};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x19};
	int		info_data_cnt;
	int		data_cnt;
	
	if(count > 64){
		return (10000);
	}
	
	if((count * sizeof(GET_DETECTED_STAR_INFO_COMMAND_STRUCT)) > size){
		return (10001);
	}
	
	tx[4] = *(((unsigned char*)&read_index) + 0);
	tx[5] = *(((unsigned char*)&read_index) + 1);
	tx[6] = *(((unsigned char*)&count) + 0);
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+(count * sizeof(GET_DETECTED_STAR_INFO_COMMAND_STRUCT));
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (20000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (30000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	data_cnt = 5;
	for(info_data_cnt = 0; info_data_cnt < count; info_data_cnt++){
		*(((unsigned char *)info_data->read_star_count) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->index) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->index) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->flag) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->hipparcos_id) + 0) = 0x00;
		*(((unsigned char *)info_data->hipparcos_id) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->hipparcos_id) + 2) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->hipparcos_id) + 3) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->area) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->area) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->luminance) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->luminance) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->luminance) + 2) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->luminance) + 3) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 2) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 3) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 4) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 5) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 6) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_azimuth) + 7) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 0) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 1) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 2) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 3) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 4) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 5) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 6) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		*(((unsigned char *)info_data->tan_elevation) + 7) = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	data_cnt++;
		
		info_data++;
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuSet Approximate Attitude�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param double quaternion1 : Quaternion1
 * @param double quaternion2 : Quaternion2
 * @param double quaternion3 : Quaternion3
 * @param double quaternion4 : Quaternion4
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Set_Approximate_Attitude(STT_STRUCT *my_stt, double quaternion1, double quaternion2, double quaternion3, double quaternion4){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[36] = {'s', 't', '2', 0x1A,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x1A};
	
	double	*quaternion_p = (double *)(tx + 4);
	
	
	*quaternion_p = quaternion1;
	quaternion_p++;
	*quaternion_p = quaternion2;
	quaternion_p++;
	*quaternion_p = quaternion3;
	quaternion_p++;
	*quaternion_p = quaternion4;
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+0;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet Estimation Status�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param GET_ESTIMATION_STATUS_UNION *st_data : �p������X�e�[�^�X�f�[�^�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_Estimation_Status(STT_STRUCT *my_stt, GET_ESTIMATION_STATUS_UNION *st_data){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[4] = {'s', 't', '2', 0x1B};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x1B};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+4;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)st_data->byte) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)st_data->byte) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	*(((unsigned char *)st_data->byte) + 2) = my_stt->driver_super.non_periodic_rx_frame[7];
	*(((unsigned char *)st_data->byte) + 3) = my_stt->driver_super.non_periodic_rx_frame[8];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet Attitude�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param double *quaternion1 : Quaternion1�i�[��ւ̃|�C���^
 * @param double *quaternion2 : Quaternion2�i�[��ւ̃|�C���^
 * @param double *quaternion3 : Quaternion3�i�[��ւ̃|�C���^
 * @param double *quaternion4 : Quaternion4�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_Attitude(STT_STRUCT *my_stt, double *quaternion1, double *quaternion2, double *quaternion3, double *quaternion4){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[4] = {'s', 't', '2', 0x1D};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x1D};
	
	unsigned char	*quaternion_p;
	int		data_cnt;
	int		i;
	
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5 + (4 * sizeof(double));
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	data_cnt = 5;
	
	quaternion_p = (unsigned char*)quaternion1;
	for(i = 0; i < sizeof(double); i++){
		*quaternion_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	quaternion_p++;	data_cnt++;
	}
	
	quaternion_p = (unsigned char*)quaternion2;
	for(i = 0; i < sizeof(double); i++){
		*quaternion_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	quaternion_p++;	data_cnt++;
	}
	
	quaternion_p = (unsigned char*)quaternion3;
	for(i = 0; i < sizeof(double); i++){
		*quaternion_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	quaternion_p++;	data_cnt++;
	}
	
	quaternion_p = (unsigned char*)quaternion4;
	for(i = 0; i < sizeof(double); i++){
		*quaternion_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	quaternion_p++;	data_cnt++;
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet Error Covariance Matrix�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param double *ecm00 : error_covariance_matrix00�i�[��ւ̃|�C���^
 * @param double *ecm01 : error_covariance_matrix01�i�[��ւ̃|�C���^
 * @param double *ecm02 : error_covariance_matrix02�i�[��ւ̃|�C���^
 * @param double *ecm11 : error_covariance_matrix11�i�[��ւ̃|�C���^
 * @param double *ecm12 : error_covariance_matrix12�i�[��ւ̃|�C���^
 * @param double *ecm22 : error_covariance_matrix22�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_Error_Covariance_Matrix(STT_STRUCT *my_stt, double *ecm00, double *ecm01, double *ecm02, double *ecm11, double *ecm12, double *ecm22){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[4] = {'s', 't', '2', 0x1F};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x1F};
	
	unsigned char	*ecm_p;
	int		data_cnt;
	int		i;
	
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5 + (6 * sizeof(double));
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	data_cnt = 5;
	
	ecm_p = (unsigned char*)ecm00;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm01;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm02;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm11;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm12;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	ecm_p = (unsigned char*)ecm22;
	for(i = 0; i < sizeof(double); i++){
		*ecm_p = my_stt->driver_super.non_periodic_rx_frame[data_cnt];	ecm_p++;	data_cnt++;
	}
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuChange Output Mode�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned char *state : ���݂̏o�̓��[�h�i�[��ւ̃|�C���^(�i�[�l��AXELSTAR-2���[�U�[�Y�}�j���A���́uChange Output Mode�v�R�}���h���Q��)
 * @return '0' : ����I��(�ڍׂ�AXELSTAR-2���[�U�[�Y�}�j���A���́uChange Output Mode�v�R�}���h���Q��)
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 * @return 30000�ԑ� : �ςȒl���Ԃ��Ă���(-30000�����Ė߂�l���Q��)
 */
int		STT_Change_Output_Mode(STT_STRUCT *my_stt, unsigned char *state){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[4] = {'s', 't', '2', 0x21};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x21};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*state = my_stt->driver_super.non_periodic_rx_frame[5];
	
	if(*state != 'a' && *state != 'b' && *state != 'm'){
		return (30000 + *state);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet SEU Error Correction Count�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned short *seu_error_count : SEU�G���[�����C���J�E���g�l�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_SEU_Error_Correction_Count(STT_STRUCT *my_stt, unsigned short *seu_error_count){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[4] = {'s', 't', '2', 0x26};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x26};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+2;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)seu_error_count) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	*(((unsigned char *)seu_error_count) + 1) = my_stt->driver_super.non_periodic_rx_frame[6];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet/Clear Error - Get Error�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned char *error : �G���[��Ԓl�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_Error(STT_STRUCT *my_stt, unsigned char *error){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x27, 'g'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x27};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)error) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet/Clear Error - Clear Error�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned char *error : �G���[��Ԓl�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Clear_Error(STT_STRUCT *my_stt, unsigned char *error){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x27, 'c'};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x27};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)error) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet/Set Output Interval - Get Output Interval�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned char *interval : �o�͎����擾�l�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Get_Output_Interval(STT_STRUCT *my_stt, unsigned char *interval){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[6] = {'s', 't', '2', 0x28, 'g', 0x00};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x28};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)interval) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuGet/Set Output Interval - Set Output Interval�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @param unsigned char set_interval : �o�͎����ݒ�l
 * @param unsigned char *interval : �o�͎����擾�l�i�[��ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 * @return 20000�ԑ� : STT���ł̃G���[(�R�}���h����M���̂�OK)(�ڍׂ�-20000������AXELSTAR-2���[�U�[�Y�}�j���A���̕\8.4���Q��)
 */
int		STT_Set_Output_Interval(STT_STRUCT *my_stt, unsigned char set_interval, unsigned char *interval){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[6] = {'s', 't', '2', 0x28, 's', 0x00};
	unsigned char	rx_head[4] = {'s', 't', '2', 0x28};
	
	tx[5] = set_interval;
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 5+1;
	my_stt->driver_super.non_periodic_config.rx_header_size = sizeof(rx_head);
	my_stt->driver_super.non_periodic_config.rx_header = rx_head;
	my_stt->driver_super.non_periodic_config.rx_footer_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	if(my_stt->driver_super.non_periodic_rx_frame[4] != '0'){
		return (20000 + my_stt->driver_super.non_periodic_rx_frame[4]);
	}
	
	*(((unsigned char *)interval) + 0) = my_stt->driver_super.non_periodic_rx_frame[5];
	
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuStart Output�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 */
int		STT_Start_Output(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x2B, 1};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	return (0);
}

/**
 * @memberof STT_STRUCT
 * @public
 * @brief STT�ցuStop Output�v�R�}���h�𔭍s����֐��ł��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return 10000�ԑ� : DRIVER_Super_conf() �łُ̈�I��(�ڍׂ�-10000������ DRIVER_Super_conf() �̖߂�l���Q��)
 */
int		STT_Stop_Output(STT_STRUCT *my_stt){
	int		i_ret;	/**< @brief �߂�l�i�[*/
	unsigned char	tx[5] = {'s', 't', '2', 0x2B, 0};
	
	my_stt->driver_super.non_periodic_config.rx_frame_size = 0;
	my_stt->driver_super.non_periodic_config.tx_frame_size = sizeof(tx);
	my_stt->driver_super.non_periodic_config.tx_frame = tx;
	
	if((i_ret = DRIVER_Super_conf(&(my_stt->driver_super), &(my_stt->rs422_config))) != 1){	// Error
		return (10000 + i_ret);
	}
	
	return (0);
}


//*****************************************************************************
//	�������W���[��
//*****************************************************************************
/**
 * @memberof STT_STRUCT
 * @private
 * @brief �t���[���f�[�^��STT�\���̂̃f�[�^���e�ɕϊ����܂��B
 * 
 * �H�w�l�ϊ����K�v�ȏꍇ�͂����ɏ������݂܂��B
 * @param STT_STRUCT *my_stt : �ΏۂƂ���STT�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 */
int		STT_Data_Conv(STT_STRUCT *my_stt){
	/** @brief �t���[���f�[�^�̃w�b�_�����I�t�Z�b�g�����|�C���^*/
	unsigned char *stt_rx_data = my_stt->driver_super.periodic_rx_frame + sizeof(stt_rx_header);
	
	*((unsigned char *)(&(my_stt->capture_id)) + 0) = *(stt_rx_data + 0);
	*((unsigned char *)(&(my_stt->capture_id)) + 1) = *(stt_rx_data + 1);
	
	*((unsigned char *)(&(my_stt->integration_state.byte)) + 0) = *(stt_rx_data + 2);
	*((unsigned char *)(&(my_stt->integration_state.byte)) + 1) = *(stt_rx_data + 3);
	
	*((unsigned char *)(&(my_stt->attitude[0])) + 0) = *(stt_rx_data + 4);
	*((unsigned char *)(&(my_stt->attitude[0])) + 1) = *(stt_rx_data + 5);
	*((unsigned char *)(&(my_stt->attitude[0])) + 2) = *(stt_rx_data + 6);
	*((unsigned char *)(&(my_stt->attitude[0])) + 3) = *(stt_rx_data + 7);
	*((unsigned char *)(&(my_stt->attitude[0])) + 4) = *(stt_rx_data + 8);
	*((unsigned char *)(&(my_stt->attitude[0])) + 5) = *(stt_rx_data + 9);
	*((unsigned char *)(&(my_stt->attitude[0])) + 6) = *(stt_rx_data + 10);
	*((unsigned char *)(&(my_stt->attitude[0])) + 7) = *(stt_rx_data + 11);
	
	*((unsigned char *)(&(my_stt->attitude[1])) + 0) = *(stt_rx_data + 12);
	*((unsigned char *)(&(my_stt->attitude[1])) + 1) = *(stt_rx_data + 13);
	*((unsigned char *)(&(my_stt->attitude[1])) + 2) = *(stt_rx_data + 14);
	*((unsigned char *)(&(my_stt->attitude[1])) + 3) = *(stt_rx_data + 15);
	*((unsigned char *)(&(my_stt->attitude[1])) + 4) = *(stt_rx_data + 16);
	*((unsigned char *)(&(my_stt->attitude[1])) + 5) = *(stt_rx_data + 17);
	*((unsigned char *)(&(my_stt->attitude[1])) + 6) = *(stt_rx_data + 18);
	*((unsigned char *)(&(my_stt->attitude[1])) + 7) = *(stt_rx_data + 19);
	
	*((unsigned char *)(&(my_stt->attitude[2])) + 0) = *(stt_rx_data + 20);
	*((unsigned char *)(&(my_stt->attitude[2])) + 1) = *(stt_rx_data + 21);
	*((unsigned char *)(&(my_stt->attitude[2])) + 2) = *(stt_rx_data + 22);
	*((unsigned char *)(&(my_stt->attitude[2])) + 3) = *(stt_rx_data + 23);
	*((unsigned char *)(&(my_stt->attitude[2])) + 4) = *(stt_rx_data + 24);
	*((unsigned char *)(&(my_stt->attitude[2])) + 5) = *(stt_rx_data + 25);
	*((unsigned char *)(&(my_stt->attitude[2])) + 6) = *(stt_rx_data + 26);
	*((unsigned char *)(&(my_stt->attitude[2])) + 7) = *(stt_rx_data + 27);
	
	*((unsigned char *)(&(my_stt->attitude[3])) + 0) = *(stt_rx_data + 28);
	*((unsigned char *)(&(my_stt->attitude[3])) + 1) = *(stt_rx_data + 29);
	*((unsigned char *)(&(my_stt->attitude[3])) + 2) = *(stt_rx_data + 30);
	*((unsigned char *)(&(my_stt->attitude[3])) + 3) = *(stt_rx_data + 31);
	*((unsigned char *)(&(my_stt->attitude[3])) + 4) = *(stt_rx_data + 32);
	*((unsigned char *)(&(my_stt->attitude[3])) + 5) = *(stt_rx_data + 33);
	*((unsigned char *)(&(my_stt->attitude[3])) + 6) = *(stt_rx_data + 34);
	*((unsigned char *)(&(my_stt->attitude[3])) + 7) = *(stt_rx_data + 35);
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 0) = *(stt_rx_data + 36);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 1) = *(stt_rx_data + 37);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 2) = *(stt_rx_data + 38);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 3) = *(stt_rx_data + 39);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 4) = *(stt_rx_data + 40);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 5) = *(stt_rx_data + 41);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 6) = *(stt_rx_data + 42);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][0])) + 7) = *(stt_rx_data + 43);
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 0) = *(stt_rx_data + 44);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 1) = *(stt_rx_data + 45);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 2) = *(stt_rx_data + 46);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 3) = *(stt_rx_data + 47);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 4) = *(stt_rx_data + 48);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 5) = *(stt_rx_data + 49);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 6) = *(stt_rx_data + 50);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][1])) + 7) = *(stt_rx_data + 51);
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 0) = *(stt_rx_data + 52);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 1) = *(stt_rx_data + 53);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 2) = *(stt_rx_data + 54);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 3) = *(stt_rx_data + 55);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 4) = *(stt_rx_data + 56);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 5) = *(stt_rx_data + 57);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 6) = *(stt_rx_data + 58);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[0][2])) + 7) = *(stt_rx_data + 59);
	
	my_stt->error_covariance_matrix[1][0] = my_stt->error_covariance_matrix[0][1];
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 0) = *(stt_rx_data + 60);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 1) = *(stt_rx_data + 61);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 2) = *(stt_rx_data + 62);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 3) = *(stt_rx_data + 63);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 4) = *(stt_rx_data + 64);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 5) = *(stt_rx_data + 65);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 6) = *(stt_rx_data + 66);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][1])) + 7) = *(stt_rx_data + 67);
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 0) = *(stt_rx_data + 68);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 1) = *(stt_rx_data + 69);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 2) = *(stt_rx_data + 70);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 3) = *(stt_rx_data + 71);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 4) = *(stt_rx_data + 72);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 5) = *(stt_rx_data + 73);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 6) = *(stt_rx_data + 74);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[1][2])) + 7) = *(stt_rx_data + 75);
	
	my_stt->error_covariance_matrix[2][0] = my_stt->error_covariance_matrix[0][2];
	
	my_stt->error_covariance_matrix[2][1] = my_stt->error_covariance_matrix[1][2];
	
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 0) = *(stt_rx_data + 76);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 1) = *(stt_rx_data + 77);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 2) = *(stt_rx_data + 78);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 3) = *(stt_rx_data + 79);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 4) = *(stt_rx_data + 80);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 5) = *(stt_rx_data + 81);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 6) = *(stt_rx_data + 82);
	*((unsigned char *)(&(my_stt->error_covariance_matrix[2][2])) + 7) = *(stt_rx_data + 83);
	
	*((unsigned char *)(&(my_stt->master_imager_temperature)) + 0) = *(stt_rx_data + 84);
	*((unsigned char *)(&(my_stt->master_imager_temperature)) + 1) = *(stt_rx_data + 85);
	*((unsigned char *)(&(my_stt->master_imager_temperature)) + 2) = *(stt_rx_data + 86);
	*((unsigned char *)(&(my_stt->master_imager_temperature)) + 3) = *(stt_rx_data + 87);
	
	*((unsigned char *)(&(my_stt->master_detected_star_count)) + 0) = *(stt_rx_data + 88);
	//*((unsigned char *)(&(my_stt->master_detected_star_count)) + 1) = *(stt_rx_data + 89);
	
	if(my_stt->master_detected_star_count > 0){
		*((unsigned char *)(&(my_stt->master_star_info[0].hipparcos_id)) + 0) = *(stt_rx_data + 89);
		*((unsigned char *)(&(my_stt->master_star_info[0].hipparcos_id)) + 1) = *(stt_rx_data + 90);
		*((unsigned char *)(&(my_stt->master_star_info[0].hipparcos_id)) + 2) = *(stt_rx_data + 91);
		*((unsigned char *)(&(my_stt->master_star_info[0].hipparcos_id)) + 3) = *(stt_rx_data + 92);
		
		*((unsigned char *)(&(my_stt->master_star_info[0].luminance)) + 0) = *(stt_rx_data + 93);
		*((unsigned char *)(&(my_stt->master_star_info[0].luminance)) + 1) = *(stt_rx_data + 94);
		*((unsigned char *)(&(my_stt->master_star_info[0].luminance)) + 2) = *(stt_rx_data + 95);
		*((unsigned char *)(&(my_stt->master_star_info[0].luminance)) + 3) = *(stt_rx_data + 96);
		
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 0) = *(stt_rx_data + 97);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 1) = *(stt_rx_data + 98);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 2) = *(stt_rx_data + 99);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 3) = *(stt_rx_data + 100);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 4) = *(stt_rx_data + 101);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 5) = *(stt_rx_data + 102);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 6) = *(stt_rx_data + 103);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_azimuth)) + 7) = *(stt_rx_data + 104);
		
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 0) = *(stt_rx_data + 105);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 1) = *(stt_rx_data + 106);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 2) = *(stt_rx_data + 107);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 3) = *(stt_rx_data + 108);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 4) = *(stt_rx_data + 109);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 5) = *(stt_rx_data + 110);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 6) = *(stt_rx_data + 111);
		*((unsigned char *)(&(my_stt->master_star_info[0].tan_elevation)) + 7) = *(stt_rx_data + 112);
	}else{
		my_stt->master_star_info[0].hipparcos_id = 0;
		my_stt->master_star_info[0].luminance = 0;
		my_stt->master_star_info[0].tan_azimuth = 0;
		my_stt->master_star_info[0].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 1){
		*((unsigned char *)(&(my_stt->master_star_info[1].hipparcos_id)) + 0) = *(stt_rx_data + 113);
		*((unsigned char *)(&(my_stt->master_star_info[1].hipparcos_id)) + 1) = *(stt_rx_data + 114);
		*((unsigned char *)(&(my_stt->master_star_info[1].hipparcos_id)) + 2) = *(stt_rx_data + 115);
		*((unsigned char *)(&(my_stt->master_star_info[1].hipparcos_id)) + 3) = *(stt_rx_data + 116);
		
		*((unsigned char *)(&(my_stt->master_star_info[1].luminance)) + 0) = *(stt_rx_data + 117);
		*((unsigned char *)(&(my_stt->master_star_info[1].luminance)) + 1) = *(stt_rx_data + 118);
		*((unsigned char *)(&(my_stt->master_star_info[1].luminance)) + 2) = *(stt_rx_data + 119);
		*((unsigned char *)(&(my_stt->master_star_info[1].luminance)) + 3) = *(stt_rx_data + 120);
		
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 0) = *(stt_rx_data + 121);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 1) = *(stt_rx_data + 122);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 2) = *(stt_rx_data + 123);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 3) = *(stt_rx_data + 124);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 4) = *(stt_rx_data + 125);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 5) = *(stt_rx_data + 126);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 6) = *(stt_rx_data + 127);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_azimuth)) + 7) = *(stt_rx_data + 128);
		
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 0) = *(stt_rx_data + 129);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 1) = *(stt_rx_data + 130);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 2) = *(stt_rx_data + 131);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 3) = *(stt_rx_data + 132);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 4) = *(stt_rx_data + 133);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 5) = *(stt_rx_data + 134);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 6) = *(stt_rx_data + 135);
		*((unsigned char *)(&(my_stt->master_star_info[1].tan_elevation)) + 7) = *(stt_rx_data + 136);
	}else{
		my_stt->master_star_info[1].hipparcos_id = 0;
		my_stt->master_star_info[1].luminance = 0;
		my_stt->master_star_info[1].tan_azimuth = 0;
		my_stt->master_star_info[1].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 2){
		*((unsigned char *)(&(my_stt->master_star_info[2].hipparcos_id)) + 0) = *(stt_rx_data + 137);
		*((unsigned char *)(&(my_stt->master_star_info[2].hipparcos_id)) + 1) = *(stt_rx_data + 138);
		*((unsigned char *)(&(my_stt->master_star_info[2].hipparcos_id)) + 2) = *(stt_rx_data + 139);
		*((unsigned char *)(&(my_stt->master_star_info[2].hipparcos_id)) + 3) = *(stt_rx_data + 140);
		
		*((unsigned char *)(&(my_stt->master_star_info[2].luminance)) + 0) = *(stt_rx_data + 141);
		*((unsigned char *)(&(my_stt->master_star_info[2].luminance)) + 1) = *(stt_rx_data + 142);
		*((unsigned char *)(&(my_stt->master_star_info[2].luminance)) + 2) = *(stt_rx_data + 143);
		*((unsigned char *)(&(my_stt->master_star_info[2].luminance)) + 3) = *(stt_rx_data + 144);
		
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 0) = *(stt_rx_data + 145);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 1) = *(stt_rx_data + 146);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 2) = *(stt_rx_data + 147);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 3) = *(stt_rx_data + 148);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 4) = *(stt_rx_data + 149);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 5) = *(stt_rx_data + 150);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 6) = *(stt_rx_data + 151);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_azimuth)) + 7) = *(stt_rx_data + 152);
		
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 0) = *(stt_rx_data + 153);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 1) = *(stt_rx_data + 154);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 2) = *(stt_rx_data + 155);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 3) = *(stt_rx_data + 156);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 4) = *(stt_rx_data + 157);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 5) = *(stt_rx_data + 158);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 6) = *(stt_rx_data + 159);
		*((unsigned char *)(&(my_stt->master_star_info[2].tan_elevation)) + 7) = *(stt_rx_data + 160);
	}else{
		my_stt->master_star_info[2].hipparcos_id = 0;
		my_stt->master_star_info[2].luminance = 0;
		my_stt->master_star_info[2].tan_azimuth = 0;
		my_stt->master_star_info[2].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 3){
		*((unsigned char *)(&(my_stt->master_star_info[3].hipparcos_id)) + 0) = *(stt_rx_data + 161);
		*((unsigned char *)(&(my_stt->master_star_info[3].hipparcos_id)) + 1) = *(stt_rx_data + 162);
		*((unsigned char *)(&(my_stt->master_star_info[3].hipparcos_id)) + 2) = *(stt_rx_data + 163);
		*((unsigned char *)(&(my_stt->master_star_info[3].hipparcos_id)) + 3) = *(stt_rx_data + 164);
		
		*((unsigned char *)(&(my_stt->master_star_info[3].luminance)) + 0) = *(stt_rx_data + 165);
		*((unsigned char *)(&(my_stt->master_star_info[3].luminance)) + 1) = *(stt_rx_data + 166);
		*((unsigned char *)(&(my_stt->master_star_info[3].luminance)) + 2) = *(stt_rx_data + 167);
		*((unsigned char *)(&(my_stt->master_star_info[3].luminance)) + 3) = *(stt_rx_data + 168);
		
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 0) = *(stt_rx_data + 169);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 1) = *(stt_rx_data + 170);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 2) = *(stt_rx_data + 171);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 3) = *(stt_rx_data + 172);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 4) = *(stt_rx_data + 173);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 5) = *(stt_rx_data + 174);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 6) = *(stt_rx_data + 175);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_azimuth)) + 7) = *(stt_rx_data + 176);
		
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 0) = *(stt_rx_data + 177);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 1) = *(stt_rx_data + 178);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 2) = *(stt_rx_data + 179);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 3) = *(stt_rx_data + 180);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 4) = *(stt_rx_data + 181);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 5) = *(stt_rx_data + 182);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 6) = *(stt_rx_data + 183);
		*((unsigned char *)(&(my_stt->master_star_info[3].tan_elevation)) + 7) = *(stt_rx_data + 184);
	}else{
		my_stt->master_star_info[3].hipparcos_id = 0;
		my_stt->master_star_info[3].luminance = 0;
		my_stt->master_star_info[3].tan_azimuth = 0;
		my_stt->master_star_info[3].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 4){
		*((unsigned char *)(&(my_stt->master_star_info[4].hipparcos_id)) + 0) = *(stt_rx_data + 185);
		*((unsigned char *)(&(my_stt->master_star_info[4].hipparcos_id)) + 1) = *(stt_rx_data + 186);
		*((unsigned char *)(&(my_stt->master_star_info[4].hipparcos_id)) + 2) = *(stt_rx_data + 187);
		*((unsigned char *)(&(my_stt->master_star_info[4].hipparcos_id)) + 3) = *(stt_rx_data + 188);
		
		*((unsigned char *)(&(my_stt->master_star_info[4].luminance)) + 0) = *(stt_rx_data + 189);
		*((unsigned char *)(&(my_stt->master_star_info[4].luminance)) + 1) = *(stt_rx_data + 190);
		*((unsigned char *)(&(my_stt->master_star_info[4].luminance)) + 2) = *(stt_rx_data + 191);
		*((unsigned char *)(&(my_stt->master_star_info[4].luminance)) + 3) = *(stt_rx_data + 192);
		
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 0) = *(stt_rx_data + 193);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 1) = *(stt_rx_data + 194);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 2) = *(stt_rx_data + 195);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 3) = *(stt_rx_data + 196);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 4) = *(stt_rx_data + 197);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 5) = *(stt_rx_data + 198);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 6) = *(stt_rx_data + 199);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_azimuth)) + 7) = *(stt_rx_data + 200);
		
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 0) = *(stt_rx_data + 201);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 1) = *(stt_rx_data + 202);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 2) = *(stt_rx_data + 203);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 3) = *(stt_rx_data + 204);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 4) = *(stt_rx_data + 205);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 5) = *(stt_rx_data + 206);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 6) = *(stt_rx_data + 207);
		*((unsigned char *)(&(my_stt->master_star_info[4].tan_elevation)) + 7) = *(stt_rx_data + 208);
	}else{
		my_stt->master_star_info[4].hipparcos_id = 0;
		my_stt->master_star_info[4].luminance = 0;
		my_stt->master_star_info[4].tan_azimuth = 0;
		my_stt->master_star_info[4].tan_elevation = 0;
	}
	
	if(my_stt->master_detected_star_count > 5){
		*((unsigned char *)(&(my_stt->master_star_info[5].hipparcos_id)) + 0) = *(stt_rx_data + 209);
		*((unsigned char *)(&(my_stt->master_star_info[5].hipparcos_id)) + 1) = *(stt_rx_data + 210);
		*((unsigned char *)(&(my_stt->master_star_info[5].hipparcos_id)) + 2) = *(stt_rx_data + 211);
		*((unsigned char *)(&(my_stt->master_star_info[5].hipparcos_id)) + 3) = *(stt_rx_data + 212);
		
		*((unsigned char *)(&(my_stt->master_star_info[5].luminance)) + 0) = *(stt_rx_data + 213);
		*((unsigned char *)(&(my_stt->master_star_info[5].luminance)) + 1) = *(stt_rx_data + 214);
		*((unsigned char *)(&(my_stt->master_star_info[5].luminance)) + 2) = *(stt_rx_data + 215);
		*((unsigned char *)(&(my_stt->master_star_info[5].luminance)) + 3) = *(stt_rx_data + 216);
		
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 0) = *(stt_rx_data + 217);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 1) = *(stt_rx_data + 218);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 2) = *(stt_rx_data + 219);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 3) = *(stt_rx_data + 220);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 4) = *(stt_rx_data + 221);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 5) = *(stt_rx_data + 222);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 6) = *(stt_rx_data + 223);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_azimuth)) + 7) = *(stt_rx_data + 224);
		
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 0) = *(stt_rx_data + 225);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 1) = *(stt_rx_data + 226);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 2) = *(stt_rx_data + 227);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 3) = *(stt_rx_data + 228);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 4) = *(stt_rx_data + 229);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 5) = *(stt_rx_data + 230);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 6) = *(stt_rx_data + 231);
		*((unsigned char *)(&(my_stt->master_star_info[5].tan_elevation)) + 7) = *(stt_rx_data + 232);
	}else{
		my_stt->master_star_info[5].hipparcos_id = 0;
		my_stt->master_star_info[5].luminance = 0;
		my_stt->master_star_info[5].tan_azimuth = 0;
		my_stt->master_star_info[5].tan_elevation = 0;
	}
	
	*((unsigned char *)(&(my_stt->master_estimation_status.byte)) + 0) = *(stt_rx_data + 233);
	*((unsigned char *)(&(my_stt->master_estimation_status.byte)) + 1) = *(stt_rx_data + 234);
	*((unsigned char *)(&(my_stt->master_estimation_status.byte)) + 2) = *(stt_rx_data + 235);
	*((unsigned char *)(&(my_stt->master_estimation_status.byte)) + 3) = *(stt_rx_data + 236);
	
	return(0);
}
