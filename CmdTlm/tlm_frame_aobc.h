#define		TLM_AOBC_40_ID		40
#define		TLM_AOBC_41_ID		41
#define		TLM_AOBC_42_ID		42
#define		TLM_AOBC_43_ID		43
#define		TLM_AOBC_44_ID		44
#define		TLM_AOBC_45_ID		45
#define		TLM_AOBC_201_ID		201
#define		TLM_AOBC_202_ID		202




#ifndef	_TLM_FRAME_INCLUDE
#define	_TLM_FRAME_INCLUDE


typedef enum {
		TLM_MODE_SAFE,
		TLM_MODE_SUNSHINE,
		TLM_MODE_SUNSHADE,
		TLM_MODE_ALL,
}	TLM_MODE_AOBC_ENUM;


#endif




#ifdef  _TLM_FRAME_MAIN


	int 	TLM_AOBC_40(void);
	int 	TLM_AOBC_41(void);
	int 	TLM_AOBC_42(void);
	int 	TLM_AOBC_43(void);
	int 	TLM_AOBC_44(void);
	int 	TLM_AOBC_45(void);
	int 	TLM_AOBC_201(void);
	int 	TLM_AOBC_202(void);


#else


extern  int 	TLM_AOBC_40(void);
extern  int 	TLM_AOBC_41(void);
extern  int 	TLM_AOBC_42(void);
extern  int 	TLM_AOBC_43(void);
extern  int 	TLM_AOBC_44(void);
extern  int 	TLM_AOBC_45(void);
extern  int 	TLM_AOBC_201(void);
extern  int 	TLM_AOBC_202(void);


#endif


//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##
/*
This pattern is a "separator".
This should not be changed.
This should not be used in other places.
*/


#define		TLM_PACKET_MAX	256
#define		TLM_STX			0x80
#define		TLM_ETX			0x81

#define		TLM_POSITION_STX1			0
#define		TLM_POSITION_STX2			1
#define		TLM_POSITION_LENGTH			2
#define		TLM_POSITION_DISCRIMINATE	3
#define		TLM_POSITION_TLM_MODE		4
#define		TLM_POSITION_TLM_COUNT		5
#define		TLM_POSITION_TLM_TIME		6
#define		TLM_POSITION_CMD_CODE		10
#define		TLM_POSITION_CMD_STAT		11
#define		TLM_POSITION_CMD_ERR_STAT	12
#define		TLM_POSITION_CMD_COUNT		13
#define		TLM_POSITION_MAIN			14

#define		TLM_POSITION_CRC_H		14
#define		TLM_POSITION_CRC_L		15
#define		TLM_POSITION_ETX1		16
#define		TLM_POSITION_ETX2		17
#define		TLM_BYTE_COUNT			(TLM_POSITION_ETX2+1)


#ifdef	_TLM_FRAME_MAIN
	int		(*tlm_packet_ptr[0xFF])(void);
	
	int		TlmPacket_combining(unsigned char tlm_id, int (*TlmDataSet_p)(void));
	int		MakeTlmPacket(TLM_MODE_AOBC_ENUM	mode);
	void	TlmSend(int ofs);
	int		TlmCmd_init(void);
	
	unsigned char		TLM_ID;
	unsigned char		TlmSts;
	unsigned char		TlmCount[256];
	unsigned int		TlmPacket_dummy;
	unsigned char 		TlmPacket[TLM_PACKET_MAX];
#else
extern	int		(*tlm_packet_ptr[0xFF])(void);

extern	int		TlmPacket_combining(unsigned char tlm_id, int (*TlmDataSet_p)(void));
extern	int		MakeTlmPacket(TLM_MODE_AOBC_ENUM	mode);
extern	void	TlmSend(unsigned char id);
extern	int		TlmCmd_init(void);

extern	unsigned char		TLM_ID;
extern	unsigned char		TlmSts;
extern	unsigned char		TlmCount[256];
extern	unsigned int		TlmPacket_dummy;
extern	unsigned char 		TlmPacket[TLM_PACKET_MAX];
#endif
