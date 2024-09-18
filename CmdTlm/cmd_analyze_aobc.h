#ifndef CMD_ANALYZE_AOBC_INCLUDE_
#define CMD_ANALYZE_AOBC_INCLUDE_

//tentative
#include "HodoUniPacket_simple_tentative.h"

#define		CMD_STX		0x80
#define		CMD_ETX		0x81

#define		CMD_POSITION_STX1		0
#define		CMD_POSITION_STX2		1
#define		CMD_POSITION_LENGTH		2
#define		CMD_POSITION_TLMCMD		3
#define		CMD_POSITION_FROM		4
#define		CMD_POSITION_TO			5
#define		CMD_POSITION_EXE_TYPE	6
#define		CMD_POSITION_TIME		7
#define		CMD_POSITION_TYPE		11
#define		CMD_POSITION_COUNT		12
#define		CMD_POSITION_CODE		13
#define		CMD_POSITION_PARAM		14

#define		CMD_CODE_PDU_ON			0x01
#define		CMD_CODE_PDU_OFF		0x02
#define		CMD_CODE_MTQ			0x03
#define		CMD_CODE_RW				0x04
#define		CMD_CODE_TASK			0x05
#define		CMD_CODE_PCU_ON			0x06
#define		CMD_CODE_PCU_OFF		0x07
#define		CMD_CODE_AOCS_MODE		0x08

#define		CMD_LENGTH_PDU_ON		12
#define		CMD_LENGTH_PDU_OFF		12
#define		CMD_LENGTH_MTQ			13
#define		CMD_LENGTH_RW			14
#define		CMD_LENGTH_TASK			12

#define		CMD_REC_STATUS_0	0
#define		CMD_REC_STATUS_1	1
#define		CMD_REC_STATUS_2	2
#define		CMD_REC_STATUS_3	3

#define		CMD_ERROR_NONE					0x00
#define		CMD_ERROR_NOT_DEFINED			0xff
#define		CMD_ERROR_CRC					0xfe
#define		CMD_ERROR_ILLEGAL_LENGTH		0xfd
#define		CMD_ERROR_ILLEGAL_PARAMETER		0xfc
#define		CMD_ERROR_ILLEGAL_CONTEXT		0xe0
#define		CMD_ERROR_CONFLICT				0xe1
#define		CMD_ERROR_TO_ERROR				0xe2
#define		CMD_ERROR_TLMCMD_ERROR			0xe3

#define		CMD_STATUS_NONE					0x00
#define		CMD_STATUS_ACC					0x01
#define		CMD_STATUS_START				0x02
#define		CMD_STATUS_END					0x03
#define		CMD_STATUS_ERROR_CMD			0xFE
#define		CMD_STATUS_ERROR_EXE			0xFF

#define		FROM_TO_MOBC					0x00
#define		FROM_TO_AOBC					0x01
#define		FROM_TO_SHU						0x02
#define		FROM_TO_DAS						0xFF

#define		TLMCMD_TLM						0xFF
#define		TLMCMD_CMD						0x00

#define CMD_DATA_MAX 256


void CmdAnalyze(unsigned char *rec_buffer, int rec_byte, 
				unsigned char *cmd_data, int *cmd_byte, int *cmd_rec_status, int *cmd_rec_count);
int DoCommand(unsigned char *cmd_data, int cmd_byte);


extern	unsigned char	mobc_cmd_data[CMD_DATA_MAX];
extern	int 			mobc_cmd_byte;
extern	int				mobc_cmd_rec_status;
extern	int				mobc_cmd_rec_count;

extern	int				CmdSts;
extern	int				CmdCode;
extern	int				CmdCount;
extern	int				CmdErrorSts;

extern	int				CmdLength;
extern	int				CmdTo;
extern	int				CmdTlmCmd;

#endif // CMD_ANALYZE_AOBC_INCLUDE_
