/*
 *  SPI.c
 *  
 *
 *  Created by Shinichi Kimura on  09/07/11.
 *  Copyright 2009 Yokyo University of Science. All rights reserved.
 *
 */

/* インクルードファイル宣言 */
#include "t_services.h"         /* TOPPERS用ヘッダファイル              */
#include "../source/mw_header.h"          /* ミドルウェア用ヘッダファイル         */
#include "IF_Board_Number.h"

/* 変数定義 */
unsigned long long* ullp_sendData_SPI;
M_T_COM_REF_BUFF    t_sendData_SPI = {0};   /*  送信データ情報設定用    */
unsigned int        ui_rcvDataSize_SPI;     /*  受信データサイズ設定用  */
M_T_COM_SET_BUFF    t_rcvBuff_SPI = {0};    /*  受信データ情報設定用    */
unsigned long long* ullp_RcvCargoData_SPI;  /*  受信データ格納先アドレス    */ 

int		SPI_init(void);
int		SPI_RX(unsigned char *data, int count);
int		SPI_TX(unsigned char *data, int count);
int		SPI_TRX(unsigned char *data_tx, unsigned char *data_rx, unsigned int count, unsigned int max);

//unsigned int		spi_speed = 4;		/* 通信速度 250kbos */
//unsigned int		spi_speed = 21;		/* 通信速度 57.6kbos */
unsigned int		spi_speed = 31;		/* 通信速度 38.4kbos */
//unsigned int		spi_speed = 64;		/* 通信速度 19.2kbos */
//unsigned int		spi_speed = 86;		/* 通信速度 14.4kbos */
//unsigned int		spi_speed = 129;		/* 通信速度 9.6kbos */
//unsigned int		spi_speed = 259;	/* 通信速度 4kbos */

//***************************************************
//	Init	wrapper
//***************************************************
int	SPI_init()
{
    int                 i_ret = 0;    
    int                 i;
	unsigned int		cond = 0x01;		/* 通信条件 常時Low 立下り読み出し*/ //PIC用
	//unsigned int		cond = 0x00;		/* 通信条件 常時Low 立上り読み出し*/ //STT用
	unsigned int		tc_cnt = 1;		/* 時間設定 */
	unsigned int		slv_ch = 0;		/* スレーブチャンネル */

    /********************************************************/
    /* データ設定						                    */
    /********************************************************/
    t_rcvBuff_SPI.ui_bufSize        = 2048;
    t_rcvBuff_SPI.vp_add            = (unsigned long long*)0x0B000000;
    t_rcvBuff_SPI.uip_dataSize      = &ui_rcvDataSize_SPI;

    /********************************************************/
    /* ポート設定						                    */
    /********************************************************/
	/*  環境設定 通信レート・通信条件	*/
	i_ret = M_AP_nobc_spi_ctrl( d_IF_BORD1, spi_speed, cond );
	/*  送信周期	*/
	i_ret = M_AP_nobc_spi_sndCtrl( d_IF_BORD1, tc_cnt );
	/*	スレーブチャンネル	*/
	i_ret = M_AP_nobc_spi_setCh( d_IF_BORD1, slv_ch );
	/*  即DMA実施設定       */
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
