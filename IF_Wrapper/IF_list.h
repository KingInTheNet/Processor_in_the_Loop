#ifndef	IF_LIST_INCLUDE_
#define	IF_LIST_INCLUDE_


#include "RS422.h"
#include "SPI.h"
#include "DC.h"
#include "AA.h"
#include "PA.h"
#include "CCSDS.h"
#include "SPWIRE.h"


typedef	enum {
		RS422,
		//SPI,
		DC,
		AA,
		PA,
		CCSDS,
		SPWIRE,
}	IF_LIST_ENUM;


extern	int			(*IF_init[])(void *my_if);
extern	int			(*IF_RX[])(void *my_if, void *data_v, int count);
extern	int			(*IF_TX[])(void *my_if, void *data_v, int count);

#endif // IF_LIST_INCLUDE_

