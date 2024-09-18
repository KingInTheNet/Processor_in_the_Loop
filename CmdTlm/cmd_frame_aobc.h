#ifndef	CMD_FRAME_AOBC_INCLUDE_
#define	CMD_FRAME_AOBC_INCLUDE_

#define CMD_PACKET_MAX	256
#define	CMD_STX			0x80
#define CMD_ETX			0x81

#define		CMD_POSITION_STX1					0
#define		CMD_POSITION_STX2					1
#define		CMD_POSITION_LENGTH					2
#define		CMD_POSITION_DISCRIMINATE			3
#define		CMD_POSITION_CMD_FROM				4
#define		CMD_POSITION_CMD_TO					5
#define		CMD_POSITION_CMD_EXE_TYPE			6
#define		CMD_POSITION_CMD_TIME				7
#define		CMD_POSITION_CMD_TYPE				11
#define		CMD_POSITION_CMD_COUNT				12
#define		CMD_POSITION_MAIN					13


#define		CMD_POSITION_CRC_H		13
#define		CMD_POSITION_CRC_L		14
#define		CMD_POSITION_ETX1		15
#define		CMD_POSITION_ETX2		16
#define		CMD_BYTE_COUNT			(CMD_POSITION_ETX2+1)

typedef enum { MTQ_KEEP, MTQ_PLUS, MTQ_MINUS, MTQ_OFF } MTQ_CMD;


int	CmdSend(
			unsigned char	cmd_from,
			unsigned char	cmd_to,
			unsigned char	cmd_exe_type,
			unsigned long	cmd_time,
			unsigned char	cmd_type,
			
			unsigned char	*cmd_data,
			int				cmd_data_count
		);
int	CmdSend_PowerOn(unsigned char	id);
int	CmdSend_PowerOff(unsigned char	id);
int CmdSend_MTQ(MTQ_CMD x, MTQ_CMD y, MTQ_CMD z);

extern	unsigned char	CmdPacket[CMD_PACKET_MAX];
extern	int				MyCmdCount;

#endif // CMD_FRAME_AOBC_INCLUDE_
