/*
 *  SPI.h
 *  
 *
 *  Created by Shinichi kimura on  09/07/11.
 *  Copyright 2009 Yokyo University of Science. All rights reserved.
 *
 */

extern	int		SPI_init(void);
extern	int		SPI_RX(unsigned char *data, int count);
extern	int		SPI_TX(unsigned char *data, int count);
extern	int		SPI_TRX(unsigned char *data_tx, unsigned char *data_rx, unsigned int count, unsigned int max);
