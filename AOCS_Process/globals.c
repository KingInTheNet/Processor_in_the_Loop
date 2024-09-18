#include "../IF_Wrapper/IF_list.h"
#include "../IF_Wrapper/DC.h"
#include "../IF_Wrapper/RS422.h"
#include "../IF_Wrapper/SPI.h"
#include "../IF_Wrapper/AA.h"
#include "../IF_Wrapper/PA.h"
#include "../IF_Wrapper/CCSDS.h"
#include "../Drivers/Super/Driver_Super.h"
#include "../Drivers/AOCS/GAS/GAS.h"
#include "../Drivers/AOCS/GPS/GPS.h"
#include "../Drivers/AOCS/GYRO/GYRO.h"
//#include "../Drivers/AOCS/MTQ/MTQ.h"
#include "../Drivers/AOCS/NSAS/NSAS.h"
#include "../Drivers/AOCS/RW/RW.h"
#include "../Drivers/AOCS/STT/STT.h"
#include "../Drivers/AOCS/AKI_GPS/AKI_GPS.h"
#include "../CmdTlm/cmd_frame_aobc.h"
#include "../CmdTlm/cmd_action_aobc.h"

#include "MTQ.h"
#include "BPDU.h"
#include "CMD.h"

GAS_STRUCT  gas1;
GPS_STRUCT  gps1;
GYRO_STRUCT gyro1;
NSAS_STRUCT nsas1, nsas2, nsas3, nsas4, nsas5, nsas6;
RW_STRUCT   rw1, rw2, rw3, rw4;
STT_STRUCT  stt1;
MTQ_STRUCT mtq123;
BPDU_STRUCT *BPDU[1];
CMD_STRUCT *CMD[1];

unsigned long update_time;

int CmdSend_PowerOn(unsigned char id){
    
    if(id == STT){
        BPDU[0]->stt1 = 1;
    }
    
    if(id == GYRO){
        BPDU[0]->gyro = 1;
    }
    
    if(id == DCDC_SNS){
        BPDU[0]->dcdc_sns = 1;
    }
    
    if(id == DCDC_MTQ){
        BPDU[0]->dcdc_mtq = 1;
    }
    
    if(id == DCDC_RW){
        BPDU[0]->dcdc_rw = 1;
    }
    
    if(id == GPSR){
        BPDU[0]->gps = 1;
    }
    
    if(id == NSAS1){
        BPDU[0]->nsas1 = 1;
    }
    
    if(id == NSAS2){
        BPDU[0]->nsas2 = 1;
    }
    
    if(id == NSAS3){
        BPDU[0]->nsas3 = 1;
    }
    
    if(id == NSAS4){
        BPDU[0]->nsas4 = 1;
    }
    
    if(id == NSAS5){
        BPDU[0]->nsas5 = 1;
    }
    
    if(id == NSAS6){
        BPDU[0]->nsas6 = 1;
    }
    
    if(id == GAS){
        BPDU[0]->gas = 1;
    }
    
    if(id == MTQ_X_PLUS){
        mtq123.bit.x = 1;
    }
    if(id == MTQ_X_MINUS){
        mtq123.bit.x = 2;
    }
    
    if(id == MTQ_Y_PLUS){
        mtq123.bit.y = 1;
    }
    if(id == MTQ_Y_MINUS){
        mtq123.bit.y = 2;
    }
    
    if(id == MTQ_Z_PLUS){
        mtq123.bit.z = 1;
    }
    if(id == MTQ_Z_MINUS){
        mtq123.bit.z = 2;
    }
    
    if(id == RW1_ON){
        BPDU[0]->rw1 = 3;
    }
    if(id == RW1_SAFE){
        BPDU[0]->rw1 = 1;
    }
    
    if(id == RW2_ON){
        BPDU[0]->rw2 = 3;
    }
    if(id == RW2_SAFE){
        BPDU[0]->rw2 = 1;
    }
    
    if(id == RW3_ON){
        BPDU[0]->rw3 = 3;
    }
    if(id == RW3_SAFE){
        BPDU[0]->rw3 = 1;
    }
    
    if(id == RW4_ON){
        BPDU[0]->rw4 = 3;
    }
    if(id == RW4_SAFE){
        BPDU[0]->rw4 = 1;
    }
    
    return 0;
    
}

int	CmdSend_PowerOff(unsigned char id){
    
    if(id == STT){
        BPDU[0]->stt1 = 0;
    }
   
    if(id == GYRO){
        BPDU[0]->gyro = 0;
    }
    
    if(id == DCDC_SNS){
        BPDU[0]->dcdc_sns = 0;
    }
    
    if(id == DCDC_MTQ){
        BPDU[0]->dcdc_mtq = 0;
    }
    
    if(id == DCDC_RW){
        BPDU[0]->dcdc_rw = 0;
    }
    
    if(id == GPSR){
        BPDU[0]->gps = 0;
    }
    
    if(id == NSAS1){
        BPDU[0]->nsas1 = 0;
    }
    
    if(id == NSAS2){
        BPDU[0]->nsas2 = 0;
    }
    
    if(id == NSAS3){
        BPDU[0]->nsas3 = 0;
    }
    
    if(id == NSAS4){
        BPDU[0]->nsas4 = 0;
    }
    
    if(id == NSAS5){
        BPDU[0]->nsas5 = 0;
    }
    
    if(id == NSAS6){
        BPDU[0]->nsas6 = 0;
    }
    
    if(id == GAS){
        BPDU[0]->gas = 0;
    }
        
    if(id == MTQ_X_OFF){
        mtq123.bit.x = 3;
    }
    
    if(id == MTQ_Y_OFF){
        mtq123.bit.y = 3;
    }

    if(id == MTQ_Z_OFF){
        mtq123.bit.z = 3;
    }
    
    if(id == RW1_OFF){
        BPDU[0]->rw1 = 0;
    }
    
    if(id == RW2_OFF){
        BPDU[0]->rw2 = 0;
    }
    
    if(id == RW3_OFF){
        BPDU[0]->rw3 = 0;
    }
    
    if(id == RW4_OFF){
        BPDU[0]->rw4 = 0;
    }

    return 0;
    
}

int CmdSend_MTQ(MTQ_CMD x, MTQ_CMD y, MTQ_CMD z){
	
	mtq123.bit.x = x;
	mtq123.bit.y = y;
	mtq123.bit.z = z;

	return 0;

}

int		RW_tx_comm(RW_STRUCT *my_rw, unsigned char Comm1, unsigned short Comm2, unsigned short Comm3){
	my_rw->rw_tx_comm.comm1.byte = (Comm1 & 0x07); // chi lay 3 bit cuoi
	my_rw->rw_tx_comm.comm2 = Comm2;
	my_rw->rw_tx_comm.comm3 = Comm3;
	
	return(0);
}

unsigned long my_time(){
    return update_time;
}

void MilliSleep(int a){
}