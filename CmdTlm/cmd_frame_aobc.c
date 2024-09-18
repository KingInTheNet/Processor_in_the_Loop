#include "utility.h"

#include "../others/Equipment_Instance.h"

#include "../Data_Processing/CRC.h"
#include "cmd_analyze_aobc.h"

#include "cmd_frame_aobc.h"

unsigned char CmdPacket[CMD_PACKET_MAX];
int MyCmdCount = 0;

void	CmdHeader(
			unsigned char	cmd_from,
			unsigned char	cmd_to,
			unsigned char	cmd_exe_type,
			unsigned long	cmd_time,
			unsigned char	cmd_type
		)
{	
	MyCmdCount++;
	MyCmdCount &= 0xff;
	
	// Make Command Packet 
	CmdPacket[CMD_POSITION_STX1]			= CMD_STX;
	CmdPacket[CMD_POSITION_STX2]			= CMD_STX;
	CmdPacket[CMD_POSITION_DISCRIMINATE]	= TLMCMD_CMD;
	CmdPacket[CMD_POSITION_CMD_FROM]		= cmd_from;
	CmdPacket[CMD_POSITION_CMD_TO]			= cmd_to;
	CmdPacket[CMD_POSITION_CMD_EXE_TYPE]	= cmd_exe_type;
	CmdPacket[CMD_POSITION_CMD_TIME + 0]	= (unsigned char)((cmd_time >> 24) & 0xff);
	CmdPacket[CMD_POSITION_CMD_TIME + 1]	= (unsigned char)((cmd_time >> 16) & 0xff);
	CmdPacket[CMD_POSITION_CMD_TIME + 2]	= (unsigned char)((cmd_time >> 8) & 0xff);
	CmdPacket[CMD_POSITION_CMD_TIME + 3]	= (unsigned char)(cmd_time & 0xff);
	CmdPacket[CMD_POSITION_CMD_TYPE]		= cmd_type;
	CmdPacket[CMD_POSITION_CMD_COUNT]		= (unsigned char)MyCmdCount;
}

void	CmdFooter(int	ofs)
{
	unsigned int	ret_crc;
	
	CmdPacket[CMD_POSITION_LENGTH]		= (unsigned char)(CMD_BYTE_COUNT + ofs - 7);	// Packet Size - STX*2 - ETX*2 - CRC*2 - LENGTH	
	
	ret_crc = crc(&(CmdPacket[CMD_POSITION_DISCRIMINATE]), CMD_BYTE_COUNT + ofs - 7);
	CmdPacket[CMD_POSITION_CRC_H + ofs] = (unsigned char)((ret_crc >> 8) & 0xFF);	// CRC H
	CmdPacket[CMD_POSITION_CRC_L + ofs] = (unsigned char)((ret_crc >> 0) & 0xFF);	// CRC L
	CmdPacket[CMD_POSITION_ETX1 + ofs] = CMD_ETX;
	CmdPacket[CMD_POSITION_ETX2 + ofs] = CMD_ETX;
}

//****************************************************************
/*	CmdSend		Send Command to other unit
		Patrameters:
			unsigned char	cmd_from		Command From(Self) ID 
			unsigned char	cmd_to			Command To ID
			unsigned char	cmd_exe_type	Command Execution Type
			unsigned long	cmd_time		Command Time
			unsigned char	cmd_type		Command Type

			unsigned char	*cmd_data		Command Data
			int				cmd_data_count	The Byte Count of Command Data 
		Return:
			0:	No Error
			-1:	Error (Command not be sent)
*/

int	CmdSend(
			unsigned char	cmd_from,
			unsigned char	cmd_to,
			unsigned char	cmd_exe_type,
			unsigned long	cmd_time,
			unsigned char	cmd_type,

			unsigned char	*cmd_data,
			int				cmd_data_count
		)
{
	int		ofs = 0;
	int		i;
	
	CmdHeader(cmd_from,	cmd_to,	cmd_exe_type, cmd_time, cmd_type);
	for(i = 0; i < cmd_data_count; i++)
	{
		CmdPacket[CMD_POSITION_MAIN + ofs] = cmd_data[i];
		ofs++;
	}	
	CmdFooter(ofs);
	
	//	Send
	if(cmd_to == FROM_TO_MOBC)		//	MOBC
	{
		Printf("Send MOBC CMD \r\n");
		MOBC_RS422_Data_Send(&mobc1, CmdPacket, (CMD_BYTE_COUNT+ofs));
	}
	else
	{
		Printf("*** TO ERROR ***\r\n");
		Printf("%4X\r\n", cmd_to);
		return(-1);
	}
	
	Printf("CMD: ");
	for(i = 0; i < CMD_BYTE_COUNT+ofs; i++){
		Printf(" %2X",CmdPacket[i]);
	}
	Printf("\r\n");
	return(0);
}

int	CmdSend_PowerOn(unsigned char	id)
{
	unsigned char	cmd_data[2] = {0x08,0x00};
	
	cmd_data[1] = id;
	return(CmdSend(1,0,0,0,0,cmd_data,sizeof(cmd_data)));
}

int	CmdSend_PowerOff(unsigned char	id)
{
	unsigned char	cmd_data[2] = {0x09,0x00};
		
	cmd_data[1] = id;
	return(CmdSend(1,0,0,0,0,cmd_data,sizeof(cmd_data)));
}		

int CmdSend_MTQ(MTQ_CMD x, MTQ_CMD y, MTQ_CMD z)
{
  unsigned char cmd_data[2] = {0x69, 0x00};
  unsigned char cmd_param = 0;
  cmd_param += z; cmd_param <<=2;
  cmd_param += y; cmd_param <<=2;
  cmd_param += x;

  cmd_data[1] = cmd_param;

  return(CmdSend(1, 0, 0, 0, 0, cmd_data, sizeof(cmd_data)));
}
