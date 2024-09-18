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
		CmdErrorSts = CMD_AOCS_MODE(packet);	// AOCSモード遷移変更
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x02){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_TASK(packet);	// AOBCタスクの起動設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x03){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_NSAS_GAIN(packet);	// NSASのゲインコントロールモードON&値設定/OFF
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x04){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MTQ(packet);	// MTQ1?3への動作コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x10){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW(packet);	// RW1?4への動作コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x11){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW_PARAMETER_REQUEST1(packet);	// RW:電流関連パラメータの要求コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x12){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW_PARAMETER_REQUEST2(packet);	// RW:温度関連パラメータの要求コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x13){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW_PARAMETER_CONFIG1(packet);	// RW:電流関連パラメータの設定コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x14){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RW_PARAMETER_CONFIG2(packet);	// RW:温度関連パラメータの設定コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x20){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RCS_INITIALIZE_COMMAND(packet);	// RCS:初期化コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x21){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RCS_INJECTION_PREPARATION(packet);	// RCS:噴射準備コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x22){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RCS_INJECTION_START(packet);	// RCS:噴射開始コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x23){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_RCS_INJECTION_STOP(packet);	// RCS:噴射停止コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x30){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_AUTO_MODE(packet);	// STT:オートモードへの移行コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x31){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_STOP(packet);	// STT:電源OFFの準備コマンド
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x32){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_TEMPERATURE(packet);	// STT:温度の取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x33){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CHANGE_POWER_STATE_CAPTURE(packet);	// STT:電源状態をキャプチャーモードに変更
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x34){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CHANGE_POWER_STATE_IDLE(packet);	// STT:電源状態をアイドルモードに変更
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x35){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_POWER_STATE(packet);	// STT:電源状態の取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x36){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_EXPOSURE_TIME(packet);	// STT:露光時間の取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x37){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_SET_EXPOSURE_TIME(packet);	// STT:露光時間の設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x38){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_SYSTEM_RESET(packet);	// STT:システムをリセットする
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x39){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CAPTURE_ONLY(packet);	// STT:撮影し、後処理を行わない
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3A){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_POSTPROC_ONLY(packet);	// STT:撮影せず、後処理を行う
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3B){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CAPTURE_AND_POSTPROC(packet);	// STT:撮影し、後処理を行う
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3C){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_DETECTED_STAR_COUNT(packet);	// STT:検出した星の数を取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3D){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_DETECTED_STAR_INFO(packet);	// STT:検出した星の情報を取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3E){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_SET_APPROXIMATE_ATTITUDE(packet);	// STT:近似姿勢の設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x3F){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_ESTIMATION_STATUS(packet);	// STT:姿勢推定ステータスの取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x40){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_ATTITUDE(packet);	// STT:推定姿勢を取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x41){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_COVARIANCE_MATRIX(packet);	// STT:誤差共分散行列を取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x42){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CHANGE_OUTPUT_MODE(packet);	// STT:出力モードの変更
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x43){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_SEU_ERROR_CORRECTION_COUNT(packet);	// STT:SEUエラー自動修正カウントの取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x44){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_ERROR(packet);	// STT:エラー状態の取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x45){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_CLEAR_ERROR(packet);	// STT:エラー状態のクリア
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x46){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_GET_OUTPUT_INTERVAL(packet);	// STT:オート出力モードの出力周期の取得
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x47){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_SET_OUTPUT_INTERVAL(packet);	// STT:オート出力モードの出力周期の変更
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x48){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_START_OUTPUT(packet);	// STT:オート出力モード中の連続出力の開始・再開
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x49){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_STOP_OUTPUT(packet);	// STT:オート出力モード中の連続出力を中断
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x4A){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_STT_ENABLE_CONTROL(packet);	// STT:Enable Pinの操作
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x50){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MIPS_HVPS(packet);	// MIPS:高圧電源のOn/Off
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x51){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MIPS_TV_TIMER(packet);	// MIPS:スラスタバルブタイマー動作
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x52){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MIPS_TV(packet);	// MIPS:スラスタバルブ動作
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x53){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_MIPS_RV(packet);	// MIPS:レギュレーターバルブ動作
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x60){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_CONT_GAIN(packet);	// AOCS:3軸制御ゲインの設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x61){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_INERTIA(packet);	// AOCS:慣性モーメントの設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x62){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_SPIN_PARAM(packet);	// AOCS:スピンモードのパラメータ設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x63){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_RW_PARAM(packet);	// AOCS:RWの機械電気特性パラメータ設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x64){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_RW_LIMIT(packet);	// AOCS:RWの電圧回転数リミットの設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x65){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_DCM(packet);	// AOCS:各コンポーネントのDCMの設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x66){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_MTQ_POL(packet);	// AOCS:MTQの極性設定
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x67){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_SKEW_PARAM(packet);	// AOCS:RW(SKEW)の角度設定(alpha,beta)
		if(CmdErrorSts == CMD_ERROR_NONE){
			CmdSts = CMD_STATUS_END;
		}else{
			CmdSts = CMD_STATUS_ERROR_EXE;
		}
	}else if(CmdCode == 0x68){
		CmdSts = CMD_STATUS_START;
		CmdErrorSts = CMD_SET_D_MATRIX(packet);	// AOCS:RWの分配則の設定
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
