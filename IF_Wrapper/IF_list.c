#include "IF_list.h"

int (*IF_init[])(void *my_if) ={
  RS422_init,
  //SPI_init,
  DC_init,
  AA_init,
  PA_init,
  CCSDS_init,
  SPWIRE_init,
};

int (*IF_RX[])(void *my_if, void *data_v, int count) = {
  RS422_RX,
  //SPI_RX,
  DC_RX,
  AA_RX,
  PA_RX,
  CCSDS_RX,
  SPWIRE_RX,
};

int (*IF_TX[])(void *my_if, void *data_v, int count) = {
  RS422_TX,
  //SPI_TX,
  DC_TX,
  AA_TX,
  PA_TX,
  CCSDS_TX,
  SPWIRE_TX,
};
