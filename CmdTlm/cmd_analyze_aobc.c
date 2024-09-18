#include "utility.h"

#include "../others/Equipment_Instance.h"

#include "../Data_Processing/CRC.h"
#include "tlm_frame_aobc.h"
#include "cmd_action_aobc.h"

#include "cmd_analyze_aobc.h"

unsigned char mobc_cmd_data[CMD_DATA_MAX];
int mobc_cmd_byte;
int mobc_cmd_rec_status = 0;
int mobc_cmd_rec_count;

int CmdSts = 0;
int CmdCode;
int CmdCount;
int CmdErrorSts;

int CmdLength;
int CmdTo;
int CmdTlmCmd;


int	CmdErrorChack(unsigned char *cmd_data,int cmd_byte);
int cmdExec(const HUPacket* packet);

//*****************************************************
//	Command Analyze
//*****************************************************
void	CmdAnalyze(unsigned char *rec_buffer, int rec_byte, 
			unsigned char *cmd_data, int *cmd_byte, int *cmd_rec_status, int *cmd_rec_count)
{
	int		ret,ret2;
	int		i;
	
	Printf("\x1B[32m");
	
	while(rec_byte > 0)
	{
		if((*cmd_rec_status) == CMD_REC_STATUS_0)		//	STX
		{
			if((*rec_buffer) == CMD_STX)
			{
				(*cmd_byte) = 0;
				cmd_data[*cmd_byte] = (*rec_buffer);
				(*cmd_byte)++;
				(*cmd_rec_status) = CMD_REC_STATUS_1;
			}
			else
			{
			}
		}
		else if((*cmd_rec_status) == CMD_REC_STATUS_1)	//	STX
		{
			if(*rec_buffer == CMD_STX)
			{
				cmd_data[*cmd_byte] = (*rec_buffer);
				(*cmd_byte)++;
				(*cmd_rec_status) = CMD_REC_STATUS_2;
			}
			else
			{
				(*cmd_rec_status) = CMD_REC_STATUS_0;
			}
		}
		else if((*cmd_rec_status) == CMD_REC_STATUS_2)	//	Length
		{
			cmd_data[*cmd_byte] = (*rec_buffer);
			(*cmd_byte)++;
			(*cmd_rec_count) = (*rec_buffer);
			(*cmd_rec_count) += 4;		// IncludeCRC and ETX
			
			if((*cmd_rec_count) > CMD_DATA_MAX - 5)	// ***** Check
				(*cmd_rec_count) = CMD_DATA_MAX - 5;

			(*cmd_rec_status) = CMD_REC_STATUS_3;
		}
		else if((*cmd_rec_status) == CMD_REC_STATUS_3)	//	CMD_DATA
		{
			cmd_data[*cmd_byte] = (*rec_buffer);
			(*cmd_byte)++;
			(*cmd_rec_count)--;		
			if((*cmd_rec_count) <= 0)
			{
				CmdSts = CMD_STATUS_ACC;
				
				Printf("CMD: ");
				for(i = 0; i < (*cmd_byte); i++){
					Printf(" %2X",cmd_data[i]);
				}
				Printf("\n");
				
				ret = CmdErrorChack(cmd_data,(*cmd_byte));
				if(ret == 0)
				{
					ret2 = DoCommand(cmd_data,(*cmd_byte));
					if(ret2 != 0)
					{
						CmdSts = CMD_STATUS_ERROR_CMD;
						CmdErrorSts = ret2;
					}
				}
				else if(ret == -1)
				{
					Printf("*** LENGTH ERROR ***\n");
					CmdSts = CMD_STATUS_ERROR_CMD;
					CmdErrorSts = CMD_ERROR_ILLEGAL_LENGTH;
				}	
				else if(ret == -2)
				{
					Printf("*** CRC ERROR ***\n");
					CmdSts = CMD_STATUS_ERROR_CMD;
					CmdErrorSts = CMD_ERROR_CRC;	
				}
				(*cmd_rec_status) = CMD_REC_STATUS_0;
			}
		}
		rec_buffer++;
		rec_byte--;
	}
	
	Printf("\x1B[m");
	
}

//*****************************************************
//	Error Check
//*****************************************************
int	CmdErrorChack(unsigned char *cmd_data,int cmd_byte)
{
	unsigned int	crc_calc;
	unsigned int	crc_cmd;
	
//	ETX Check
	if(cmd_data[cmd_byte -1] != CMD_ETX)
		return(-1);	
	if(cmd_data[cmd_byte -2] != CMD_ETX)
		return(-1);

//	CRC Check
	crc_calc = crc(&cmd_data[CMD_POSITION_TLMCMD], (cmd_byte - 2 - 1 - 2 - 2));	// -STX*2 - LENGTH   -ETX*2 - CRC*2 
	crc_calc &= 0xffff;
	crc_cmd = cmd_data[cmd_byte -4];
	crc_cmd <<= 8;
	crc_cmd |= cmd_data[cmd_byte -3];	
	Printf("CRC_Calc %4X\n",crc_calc);
	Printf("CRC_Cmd  %4X\n",crc_cmd);
	
	if(crc_calc != crc_cmd)
		return(-2);
	
	return(0);
}


		//tentative
		static HUPacket temp_HUPacket;


//*****************************************************
//	Command Dispacher
//*****************************************************
int	DoCommand(unsigned char *cmd_data,int cmd_byte)
{
	unsigned char	ret;
	int		i;

//	FROM Check
	CmdTo		= cmd_data[CMD_POSITION_TO];
	CmdTlmCmd	= cmd_data[CMD_POSITION_TLMCMD];

	if(CmdTlmCmd != TLMCMD_CMD)
	{
		Printf("*** CMDTLM ERROR ***\n");
		Printf("%4X\n", CmdTlmCmd);
		return(CMD_ERROR_TLMCMD_ERROR);
	}

	if(CmdTo != FROM_TO_AOBC)
	{
		Printf("*** TO ERROR ***\n");
		Printf("%4X\n", CmdTo);
		return(CMD_ERROR_TO_ERROR);
	}
	
//	Command Code
	CmdCode = cmd_data[CMD_POSITION_CODE];
	CmdLength = cmd_data[CMD_POSITION_LENGTH];
	
//	Command Count
	CmdCount++;
	CmdCount &= 0xff;
	
			//tentative
			temp_HUPacket.length = cmd_byte;
			for(i = 0; i < cmd_byte; i++){
				temp_HUPacket.data[i] = cmd_data[i];
			}
	
	cmdExec(&temp_HUPacket);
	
	return(0);
}

int cmdExec(const HUPacket* packet)
{

/*
This pattern is a "separator".
This should not be changed.
This should not be used in other places.
*/
//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##


	if(CmdCode == 0x01){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_AOCS_MODE(packet);	// AOCS���[�h�J�ڕύX
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x02){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_TASK(packet);	// AOBC�^�X�N�̋N���ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x03){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_NSAS_GAIN(packet);	// NSAS�̃Q�C���R���g���[�����[�hON&�l�ݒ�/OFF
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x04){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MTQ(packet);	// MTQ1?3�ւ̓���R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x10){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW(packet);	// RW1?4�ւ̓���R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x11){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW_PARAMETER_REQUEST1(packet);	// RW:�d���֘A�p�����[�^�̗v���R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x12){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW_PARAMETER_REQUEST2(packet);	// RW:���x�֘A�p�����[�^�̗v���R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x13){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW_PARAMETER_CONFIG1(packet);	// RW:�d���֘A�p�����[�^�̐ݒ�R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x14){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW_PARAMETER_CONFIG2(packet);	// RW:���x�֘A�p�����[�^�̐ݒ�R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x20){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RCS_INITIALIZE_COMMAND(packet);	// RCS:�������R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x21){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RCS_INJECTION_PREPARATION(packet);	// RCS:���ˏ����R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x22){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RCS_INJECTION_START(packet);	// RCS:���ˊJ�n�R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x23){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RCS_INJECTION_STOP(packet);	// RCS:���˒�~�R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x30){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_AUTO_MODE(packet);	// STT:�I�[�g���[�h�ւ̈ڍs�R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x31){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_STOP(packet);	// STT:�d��OFF�̏����R�}���h
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x32){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_TEMPERATURE(packet);	// STT:���x�̎擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x33){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CHANGE_POWER_STATE_CAPTURE(packet);	// STT:�d����Ԃ��L���v�`���[���[�h�ɕύX
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x34){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CHANGE_POWER_STATE_IDLE(packet);	// STT:�d����Ԃ��A�C�h�����[�h�ɕύX
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x35){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_POWER_STATE(packet);	// STT:�d����Ԃ̎擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x36){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_EXPOSURE_TIME(packet);	// STT:�I�����Ԃ̎擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x37){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_SET_EXPOSURE_TIME(packet);	// STT:�I�����Ԃ̐ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x38){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_SYSTEM_RESET(packet);	// STT:�V�X�e�������Z�b�g����
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x39){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CAPTURE_ONLY(packet);	// STT:�B�e���A�㏈�����s��Ȃ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3A){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_POSTPROC_ONLY(packet);	// STT:�B�e�����A�㏈�����s��
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3B){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CAPTURE_AND_POSTPROC(packet);	// STT:�B�e���A�㏈�����s��
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3C){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_DETECTED_STAR_COUNT(packet);	// STT:���o�������̐����擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3D){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_DETECTED_STAR_INFO(packet);	// STT:���o�������̏����擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3E){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_SET_APPROXIMATE_ATTITUDE(packet);	// STT:�ߎ��p���̐ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3F){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_ESTIMATION_STATUS(packet);	// STT:�p������X�e�[�^�X�̎擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x40){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_ATTITUDE(packet);	// STT:����p�����擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x41){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_COVARIANCE_MATRIX(packet);	// STT:�덷�����U�s����擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x42){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CHANGE_OUTPUT_MODE(packet);	// STT:�o�̓��[�h�̕ύX
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x43){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_SEU_ERROR_CORRECTION_COUNT(packet);	// STT:SEU�G���[�����C���J�E���g�̎擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x44){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_ERROR(packet);	// STT:�G���[��Ԃ̎擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x45){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CLEAR_ERROR(packet);	// STT:�G���[��Ԃ̃N���A
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x46){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_OUTPUT_INTERVAL(packet);	// STT:�I�[�g�o�̓��[�h�̏o�͎����̎擾
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x47){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_SET_OUTPUT_INTERVAL(packet);	// STT:�I�[�g�o�̓��[�h�̏o�͎����̕ύX
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x48){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_START_OUTPUT(packet);	// STT:�I�[�g�o�̓��[�h���̘A���o�͂̊J�n�E�ĊJ
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x49){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_STOP_OUTPUT(packet);	// STT:�I�[�g�o�̓��[�h���̘A���o�͂𒆒f
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x4A){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_ENABLE_CONTROL(packet);	// STT:Enable Pin�̑���
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x50){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MIPS_HVPS(packet);	// MIPS:�����d����On/Off
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x51){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MIPS_TV_TIMER(packet);	// MIPS:�X���X�^�o���u�^�C�}�[����
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x52){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MIPS_TV(packet);	// MIPS:�X���X�^�o���u����
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x53){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MIPS_RV(packet);	// MIPS:���M�����[�^�[�o���u����
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x60){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_CONT_GAIN(packet);	// AOCS:3������Q�C���̐ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x61){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_INERTIA(packet);	// AOCS:�������[�����g�̐ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x62){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_SPIN_PARAM(packet);	// AOCS:�X�s�����[�h�̃p�����[�^�ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x63){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_RW_PARAM(packet);	// AOCS:RW�̋@�B�d�C�����p�����[�^�ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x64){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_RW_LIMIT(packet);	// AOCS:RW�̓d����]�����~�b�g�̐ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x65){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_DCM(packet);	// AOCS:�e�R���|�[�l���g��DCM�̐ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x66){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_MTQ_POL(packet);	// AOCS:MTQ�̋ɐ��ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x67){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_SKEW_PARAM(packet);	// AOCS:RW(SKEW)�̊p�x�ݒ�(alpha,beta)
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x68){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_D_MATRIX(packet);	// AOCS:RW�̕��z���̐ݒ�
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}


//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##
/*
This pattern is a "separator".
This should not be changed.
This should not be used in other places.
*/

	}else{
		Printf("*** UNKONWN CMD ***");
		Printf("%4X\n", CmdCode);
		return(CMD_ERROR_NOT_DEFINED);
	}
	
	return(CmdErrorSts);
}
