/*
 *  SPI.c
 *  
 *
 *  Created by Shinichi Kimura on  09/07/11.
 *  Copyright 2009 Yokyo University of Science. All rights reserved.
 *
 */

/* �C���N���[�h�t�@�C���錾 */
#include "t_services.h"         /* TOPPERS�p�w�b�_�t�@�C��              */
#include "../source/mw_header.h"          /* �~�h���E�F�A�p�w�b�_�t�@�C��         */
#include "IF_Board_Number.h"

/* �ϐ���` */
unsigned long long* ullp_sendData_SPI;
M_T_COM_REF_BUFF    t_sendData_SPI = {0};   /*  ���M�f�[�^���ݒ�p    */
unsigned int        ui_rcvDataSize_SPI;     /*  ��M�f�[�^�T�C�Y�ݒ�p  */
M_T_COM_SET_BUFF    t_rcvBuff_SPI = {0};    /*  ��M�f�[�^���ݒ�p    */
unsigned long long* ullp_RcvCargoData_SPI;  /*  ��M�f�[�^�i�[��A�h���X    */ 

int		SPI_init(void);
int		SPI_RX(unsigned char *data, int count);
int		SPI_TX(unsigned char *data, int count);
int		SPI_TRX(unsigned char *data_tx, unsigned char *data_rx, unsigned int count, unsigned int max);

//unsigned int		spi_speed = 4;		/* �ʐM���x 250kbos */
//unsigned int		spi_speed = 21;		/* �ʐM���x 57.6kbos */
unsigned int		spi_speed = 31;		/* �ʐM���x 38.4kbos */
//unsigned int		spi_speed = 64;		/* �ʐM���x 19.2kbos */
//unsigned int		spi_speed = 86;		/* �ʐM���x 14.4kbos */
//unsigned int		spi_speed = 129;		/* �ʐM���x 9.6kbos */
//unsigned int		spi_speed = 259;	/* �ʐM���x 4kbos */

//***************************************************
//	Init	wrapper
//***************************************************
int	SPI_init()
{
    int                 i_ret = 0;    
    int                 i;
	unsigned int		cond = 0x01;		/* �ʐM���� �펞Low ������ǂݏo��*/ //PIC�p
	//unsigned int		cond = 0x00;		/* �ʐM���� �펞Low �����ǂݏo��*/ //STT�p
	unsigned int		tc_cnt = 1;		/* ���Ԑݒ� */
	unsigned int		slv_ch = 0;		/* �X���[�u�`�����l�� */

    /********************************************************/
    /* �f�[�^�ݒ�						                    */
    /********************************************************/
    t_rcvBuff_SPI.ui_bufSize        = 2048;
    t_rcvBuff_SPI.vp_add            = (unsigned long long*)0x0B000000;
    t_rcvBuff_SPI.uip_dataSize      = &ui_rcvDataSize_SPI;

    /********************************************************/
    /* �|�[�g�ݒ�						                    */
    /********************************************************/
	/*  ���ݒ� �ʐM���[�g�E�ʐM����	*/
	i_ret = M_AP_nobc_spi_ctrl( d_IF_BORD1, spi_speed, cond );
	/*  ���M����	*/
	i_ret = M_AP_nobc_spi_sndCtrl( d_IF_BORD1, tc_cnt );
	/*	�X���[�u�`�����l��	*/
	i_ret = M_AP_nobc_spi_setCh( d_IF_BORD1, slv_ch );
	/*  ��DMA���{�ݒ�       */
	i_ret = M_AP_nobc_spi_sndTrigger( d_IF_BORD1, M_d_SIO_SEND_TRG_SET );
	
	return	i_ret;
}

//***************************************************
//	RX wrapper
//***************************************************
int		SPI_RX(unsigned char *data, int count)
{
    int				i_ret = 0;    
	unsigned int	ret_count;
	unsigned int	error;

	t_rcvBuff_SPI.ui_bufSize        = count;
	t_rcvBuff_SPI.vp_add            = (unsigned long long*)data;
	t_rcvBuff_SPI.uip_dataSize      = &ret_count;

	i_ret += M_AP_nobc_spi_getRcvData( d_IF_BORD1, &error, t_rcvBuff_SPI, count );
	return	ret_count;
}

//***************************************************
//	TX wrapper
//***************************************************
int		SPI_TX(unsigned char *data, int count)
{
    int		i_ret = 0;    

    t_sendData_SPI.ui_dataSize  = (unsigned int)count;
	t_sendData_SPI.vp_add = (unsigned long long*)data;
	i_ret = M_AP_nobc_spi_SndData( d_IF_BORD1, t_sendData_SPI );

	return	i_ret;
}


//***************************************************
//	TRX wrapper
//***************************************************

int		SPI_TRX(unsigned char *data_tx, unsigned char *data_rx, unsigned int count, unsigned int max)
{
    int				i_ret = 0;    
	unsigned int	ret_count;
	unsigned int	error;
	TMO				t_spi = ((TMO)spi_speed + 1) * 16 * count * 8 / 20000 + 1;

    t_sendData_SPI.ui_dataSize  = count;
	t_sendData_SPI.vp_add = (unsigned long long*)data_tx;

	i_ret = M_AP_nobc_spi_SndData( d_IF_BORD1, t_sendData_SPI );
	
//	tslp_tsk(t_spi);
	CheckChar();
	
	t_rcvBuff_SPI.ui_bufSize        = max;
	t_rcvBuff_SPI.vp_add          = (unsigned long long*)data_rx;
	t_rcvBuff_SPI.uip_dataSize      = &ret_count;

	i_ret += M_AP_nobc_spi_getRcvData( d_IF_BORD1, &error, t_rcvBuff_SPI, count );
	
	return	ret_count;	
}
