/**
 * @file Equipment_Instance.h
 * @brief �@��̃C���X�^���X�Ɋւ���t�@�C���ł�?B
 * 
 * �{�t�@�C���ł�?A�@��̃C���X�^���X?�?���?A?�����?��?����`����Ă��܂�?B
 * @date 2013.06.29
 */

#ifndef	EQUIPMENT_INSTANCE_INCLUDE_
#define	EQUIPMENT_INSTANCE_INCLUDE_


#include "../Drivers/AOCS/NSAS/NSAS.h"
#include "../Drivers/AOCS/GAS/GAS.h"
#include "../Drivers/AOCS/GPS/GPS.h"
#include "../Drivers/AOCS/STT/STT.h"
#include "../Drivers/AOCS/RW/RW.h"
#include "../Drivers/AOCS/GYRO/GYRO.h"

extern	NSAS_STRUCT		nsas1, nsas2, nsas3, nsas4, nsas5, nsas6;
extern	GAS_STRUCT		gas1;
extern	GPS_STRUCT		gps1;
extern	GYRO_STRUCT		gyro1;
extern	RW_STRUCT		rw1, rw2, rw3, rw4;
extern	STT_STRUCT		stt1;

int		equipment_init(void);

#endif // EQUIPMENT_INSTANCE_INCLUDE_
