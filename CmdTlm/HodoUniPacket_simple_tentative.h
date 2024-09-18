#ifndef HODO_UNI_PACKET_H_
#define HODO_UNI_PACKET_H_

#include <stddef.h>


#define HUP_MAX_PACKET_LENGTH (204)


typedef struct
{
  size_t length;
  unsigned char data[HUP_MAX_PACKET_LENGTH];
} HUPacket;


#endif // HODO_UNI_PACKET_H_
