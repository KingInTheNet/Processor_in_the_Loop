#define S_FUNCTION_NAME sfunc_AOBC
#define S_FUNCTION_LEVEL 2
#define MDL_START
#include "simstruc.h"
#include <windows.h>

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

#include "MTQ.h"
#include "BPDU.h"
#include "CMD.h"

extern void AOCS_Init();
extern void AOCS_Process();

extern unsigned long update_time;

HANDLE NSAS_hShm[6];  // handle for shared memory
NSAS_STRUCT *NSAS[6]; // structure to share

HANDLE STT_hShm[1]; // handle for shared memory
STT_STRUCT *STT[1]; // structure to share

HANDLE FOG_hShm[1];  // handle for shared memory
GYRO_STRUCT *FOG[1]; // structure to share

HANDLE GAS_hShm[1];  // handle for shared memory
GAS_STRUCT *GAS[1]; // structure to share

HANDLE MTQ_hShm[1];  // handle for shared memory
MTQ_STRUCT *MTQ[1]; // structure to share

HANDLE RW_hShm[4];  // handle for shared memory
RW_STRUCT *RW[4]; // structure to share

HANDLE GPS_hShm[1];  // handle for shared memory
GPS_STRUCT *GPS[1]; // structure to share

HANDLE BPDU_hShm[1];  // handle for shared memory
extern BPDU_STRUCT *BPDU[1]; // structure to share

HANDLE CMD_hShm[1];  // handle for shared memory
extern CMD_STRUCT *CMD[1]; // structure to share

extern GAS_STRUCT  gas1;
extern GPS_STRUCT  gps1;
extern GYRO_STRUCT gyro1;
extern NSAS_STRUCT nsas1, nsas2, nsas3, nsas4, nsas5, nsas6;
extern RW_STRUCT   rw1, rw2, rw3, rw4;
extern STT_STRUCT  stt1;
extern MTQ_STRUCT  mtq123;

unsigned char temp_counter;
unsigned char gps1_on_counter = 0;
unsigned short GPS_wait = 0;
BPDU_STRUCT BPDU_old;
CMD_STRUCT CMD_old;

extern unsigned char AOCS_mode;
extern unsigned char unloading_flag;

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0); // number of parameter of sfunction
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return;
    }

    if (!ssSetNumInputPorts(S, 1)) return; //number of input port

    ssSetInputPortWidth(S, 0, 1); // dimension of input port
    ssSetInputPortDataType(S, 0, SS_DOUBLE); // data type of input port
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);

//    if (!ssSetNumOutputPorts(S, 0)) return; // number of output port
//    ssSetNumSampleTimes(S, 1);
    
    if (!ssSetNumOutputPorts(S, 5)) return;
    /* Output Port 0 */
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 0, 0);
    /* Output Port 1 */
    ssSetOutputPortWidth(S, 1, 1);
    ssSetOutputPortDataType(S, 1, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 1, 0);
    /* Output Port 2 */
    ssSetOutputPortWidth(S, 2, 1);
    ssSetOutputPortDataType(S, 2, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 2, 0);
    /* Output Port 3 */
    ssSetOutputPortWidth(S, 3, 1);
    ssSetOutputPortDataType(S, 3, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 3, 0);
	/* Output Port 4 */
    ssSetOutputPortWidth(S, 4, 1);
    ssSetOutputPortDataType(S, 4, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 4, 0);
}

static void mdlStart(SimStruct *S)
{   
    char SharedMemNameMTQ[16];
    char SharedMemNameFOG[16];
    char SharedMemNameGAS[16];
    char SharedMemNameNSAS[6][16];
    char SharedMemNameGPS[16];
    char SharedMemNameSTT[16];
    char SharedMemNameRW[4][16];
    char SharedMemNameBPDU[16];
    char SharedMemNameCMD[16];
    
    // open shared memory
    sprintf(SharedMemNameFOG, "FOG%d", 0);
    FOG_hShm[0] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(GYRO_STRUCT), SharedMemNameFOG);
    // share structure
    FOG[0] = (GYRO_STRUCT *)MapViewOfFile(FOG_hShm[0], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(GYRO_STRUCT));
        
    // open shared memory
    sprintf(SharedMemNameMTQ, "MTQ%d", 0);
    MTQ_hShm[0] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(MTQ_STRUCT), SharedMemNameMTQ);
    // share structure
    MTQ[0] = (MTQ_STRUCT *)MapViewOfFile(MTQ_hShm[0], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MTQ_STRUCT));

    // open shared memory
    sprintf(SharedMemNameNSAS[0], "NSAS%d", 0);
    sprintf(SharedMemNameNSAS[1], "NSAS%d", 1);
    sprintf(SharedMemNameNSAS[2], "NSAS%d", 2);
    sprintf(SharedMemNameNSAS[3], "NSAS%d", 3);
    sprintf(SharedMemNameNSAS[4], "NSAS%d", 4);
    sprintf(SharedMemNameNSAS[5], "NSAS%d", 5);
    NSAS_hShm[0] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(NSAS_STRUCT), SharedMemNameNSAS[0]);
    NSAS_hShm[1] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(NSAS_STRUCT), SharedMemNameNSAS[1]);
    NSAS_hShm[2] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(NSAS_STRUCT), SharedMemNameNSAS[2]);
    NSAS_hShm[3] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(NSAS_STRUCT), SharedMemNameNSAS[3]);
    NSAS_hShm[4] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(NSAS_STRUCT), SharedMemNameNSAS[4]);
    NSAS_hShm[5] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(NSAS_STRUCT), SharedMemNameNSAS[5]);
    // share structure
    NSAS[0] = (NSAS_STRUCT *)MapViewOfFile(NSAS_hShm[0], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(NSAS_STRUCT));
    NSAS[1] = (NSAS_STRUCT *)MapViewOfFile(NSAS_hShm[1], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(NSAS_STRUCT));
    NSAS[2] = (NSAS_STRUCT *)MapViewOfFile(NSAS_hShm[2], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(NSAS_STRUCT));
    NSAS[3] = (NSAS_STRUCT *)MapViewOfFile(NSAS_hShm[3], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(NSAS_STRUCT));
    NSAS[4] = (NSAS_STRUCT *)MapViewOfFile(NSAS_hShm[4], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(NSAS_STRUCT));
    NSAS[5] = (NSAS_STRUCT *)MapViewOfFile(NSAS_hShm[5], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(NSAS_STRUCT));
	
    // open shared memory
    sprintf(SharedMemNameGAS, "GAS%d", 0);
    GAS_hShm[0] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(GAS_STRUCT), SharedMemNameGAS);
    // share structure
    GAS[0] = (GAS_STRUCT *)MapViewOfFile(GAS_hShm[0], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(GAS_STRUCT));
    
    // open shared memory
    sprintf(SharedMemNameGPS, "GPS%d", 0);
    GPS_hShm[0] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(GPS_STRUCT), SharedMemNameGPS);
    // share structure
    GPS[0] = (GPS_STRUCT *)MapViewOfFile(GPS_hShm[0], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(GPS_STRUCT));

    // open shared memory
    sprintf(SharedMemNameSTT, "STT%d", 0);
    STT_hShm[0] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(STT_STRUCT), SharedMemNameSTT);
    // share structure
    STT[0] = (STT_STRUCT *)MapViewOfFile(STT_hShm[0], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(STT_STRUCT));
    
    // open shared memory
    sprintf(SharedMemNameRW[0], "RW%d", 0);
    sprintf(SharedMemNameRW[1], "RW%d", 1);
    sprintf(SharedMemNameRW[2], "RW%d", 2);
    sprintf(SharedMemNameRW[3], "RW%d", 3);
    RW_hShm[0] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(RW_STRUCT), SharedMemNameRW[0]);
    RW_hShm[1] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(RW_STRUCT), SharedMemNameRW[1]);
    RW_hShm[2] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(RW_STRUCT), SharedMemNameRW[2]);
    RW_hShm[3] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(RW_STRUCT), SharedMemNameRW[3]);
    // share structure
    RW[0] = (RW_STRUCT *)MapViewOfFile(RW_hShm[0], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(RW_STRUCT));
    RW[1] = (RW_STRUCT *)MapViewOfFile(RW_hShm[1], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(RW_STRUCT));
    RW[2] = (RW_STRUCT *)MapViewOfFile(RW_hShm[2], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(RW_STRUCT));
    RW[3] = (RW_STRUCT *)MapViewOfFile(RW_hShm[3], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(RW_STRUCT));
    
    // open shared memory
    sprintf(SharedMemNameBPDU, "BPDU%d", 0);
    BPDU_hShm[0] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(BPDU_STRUCT), SharedMemNameBPDU);
    // share structure
    BPDU[0] = (BPDU_STRUCT *)MapViewOfFile(BPDU_hShm[0], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(BPDU_STRUCT));
    
    // open shared memory
    sprintf(SharedMemNameCMD, "CMD%d", 0);
    CMD_hShm[0] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(CMD_STRUCT), SharedMemNameCMD);
    // share structure
    CMD[0] = (CMD_STRUCT *)MapViewOfFile(CMD_hShm[0], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(CMD_STRUCT));
    
    FOG[0]->driver_super.rx_count = 0;
    NSAS[0]->driver_super.rx_count = 0;
    NSAS[1]->driver_super.rx_count = 0;
    NSAS[2]->driver_super.rx_count = 0;
    NSAS[3]->driver_super.rx_count = 0;
    NSAS[4]->driver_super.rx_count = 0;
    NSAS[5]->driver_super.rx_count = 0;
    GAS[0]->driver_super.rx_count = 0;
    GPS[0]->driver_super.rx_count = 0;
    STT[0]->driver_super.rx_count = 0;
    RW[0]->driver_super.rx_count = 0;
    RW[1]->driver_super.rx_count = 0;
    RW[2]->driver_super.rx_count = 0;
    RW[3]->driver_super.rx_count = 0;
    
    GPS[0]->status1.bit.three_dim_positioning_flag = 0;
    
    temp_counter = 0;
    
    //---------AOCS_init---------//
    
    AOCS_Init();
    
    //---------AOCS_init---------//
    
    CMD[0]->AOCS_mode = AOCS_mode;
    CMD[0]->unloading_flag = unloading_flag;
    
}

static void mdlInitializeSampleTimes(SimStruct *S)
{  
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0);
} 

static void mdlOutputs(SimStruct *S, int_T tid)
{
    const double *u = (const double*) ssGetInputPortSignal(S, 0);
    //unsigned long update_time = (unsigned long)(*u * 1000.0);
    double        *q0  = (real_T *)ssGetOutputPortRealSignal(S,0);
    double        *q1  = (real_T *)ssGetOutputPortRealSignal(S,1);
    double        *q2  = (real_T *)ssGetOutputPortRealSignal(S,2);
    double        *q3  = (real_T *)ssGetOutputPortRealSignal(S,3);
	double        *q4  = (real_T *)ssGetOutputPortRealSignal(S,4);
    
    update_time = (unsigned long)(*u * 1000.0);
    AOCS_mode = CMD[0]->AOCS_mode;
    unloading_flag = CMD[0]->unloading_flag;
    
    if(BPDU[0]->gyro){
        FOG[0]->driver_super.update_time = update_time;
        FOG[0]->driver_super.rx_count++;
        memcpy(&gyro1, FOG[0], sizeof(GYRO_STRUCT));
    }
    
    if(BPDU[0]->dcdc_sns && BPDU[0]->nsas1){
        NSAS[0]->driver_super.update_time = update_time;
        NSAS[0]->driver_super.rx_count++;
        memcpy(&nsas1, NSAS[0], sizeof(NSAS_STRUCT));
    }
	
    if(BPDU[0]->dcdc_sns && BPDU[0]->nsas2){
        NSAS[1]->driver_super.update_time = update_time;
        NSAS[1]->driver_super.rx_count++;
        memcpy(&nsas2, NSAS[1], sizeof(NSAS_STRUCT));
    }
	
    if(BPDU[0]->dcdc_sns && BPDU[0]->nsas3){
        NSAS[2]->driver_super.update_time = update_time;
        NSAS[2]->driver_super.rx_count++;
        memcpy(&nsas3, NSAS[2], sizeof(NSAS_STRUCT));
    }
	
    if(BPDU[0]->dcdc_sns && BPDU[0]->nsas4){
        NSAS[3]->driver_super.update_time = update_time;
        NSAS[3]->driver_super.rx_count++;
        memcpy(&nsas4, NSAS[3], sizeof(NSAS_STRUCT));
    }
	
    if(BPDU[0]->dcdc_sns && BPDU[0]->nsas5){
        NSAS[4]->driver_super.update_time = update_time;
        NSAS[4]->driver_super.rx_count++;
        memcpy(&nsas5, NSAS[4], sizeof(NSAS_STRUCT));
    }
	
    if(BPDU[0]->dcdc_sns && BPDU[0]->nsas6){
        NSAS[5]->driver_super.update_time = update_time;
        NSAS[5]->driver_super.rx_count++;
        memcpy(&nsas6, NSAS[5], sizeof(NSAS_STRUCT));
    }
    
    if(BPDU[0]->dcdc_sns == 0 || BPDU[0]->gas == 0){
        GAS[0]->x = 0;
        GAS[0]->y = 0;
        GAS[0]->z = 0;
        GAS[0]->ref = 0;
        GAS[0]->cycle_sum_x = 0;
        GAS[0]->cycle_sum_y = 0;
        GAS[0]->cycle_sum_z = 0;
        GAS[0]->cycle_sum_ref = 0;
    }
    GAS[0]->driver_super.update_time = update_time;
    GAS[0]->driver_super.rx_count++;
    memcpy(&gas1, GAS[0], sizeof(GAS_STRUCT));
    
    if(BPDU[0]->dcdc_rw && BPDU[0]->rw1){
        RW[0]->driver_super.update_time = update_time;
        RW[0]->driver_super.rx_count++;
        memcpy(&rw1, RW[0], sizeof(RW_STRUCT));
    }
    
    if(BPDU[0]->dcdc_rw && BPDU[0]->rw2){
        RW[1]->driver_super.update_time = update_time;
        RW[1]->driver_super.rx_count++;
        memcpy(&rw2, RW[1], sizeof(RW_STRUCT));
    }
    
    if(BPDU[0]->dcdc_rw && BPDU[0]->rw3){
        RW[2]->driver_super.update_time = update_time;
        RW[2]->driver_super.rx_count++;
        memcpy(&rw3, RW[2], sizeof(RW_STRUCT));
    }
    
    if(BPDU[0]->dcdc_rw && BPDU[0]->rw4){
        RW[3]->driver_super.update_time = update_time;
        RW[3]->driver_super.rx_count++;
        memcpy(&rw4, RW[3], sizeof(RW_STRUCT));
    }

    if(BPDU[0]->dcdc_sns && BPDU[0]->gps){
        if(temp_counter == gps1_on_counter){
            GPS[0]->driver_super.update_time = update_time;
            GPS[0]->driver_super.rx_count++;
            if(GPS_wait == 900){
                GPS[0]->status1.bit.three_dim_positioning_flag = 1;
                GPS[0]->pps = 1;
                GPS[0]->delay_time = 10;
                GPS_wait = 0;
            }
            if(GPS_wait != 0){
                GPS_wait++;
            }
            memcpy(&gps1, GPS[0], sizeof(GPS_STRUCT));
        }
    }
    
    if(temp_counter == 0){
        memcpy(&stt1, STT[0], sizeof(STT_STRUCT));
        STT[0]->capture_id++;
    }
    
    //---------AOCS_process---------//
    
    AOCS_Process();
    
    //---------AOCS_process---------//
    
    CMD[0]->AOCS_mode = AOCS_mode;
    CMD[0]->unloading_flag = unloading_flag;

    if((BPDU_old.gps == 0 || BPDU_old.dcdc_sns == 0) && (BPDU[0]->gps == 1 && BPDU[0]->dcdc_sns == 1)){
        gps1_on_counter = temp_counter;
        GPS[0]->status1.bit.three_dim_positioning_flag = 0;
        GPS[0]->pps = 0;
        GPS[0]->delay_time = 0;
        GPS_wait = 1;
    }
    if(BPDU[0]->dcdc_mtq == 0){
        mtq123.byte = 63;
    }
    memcpy(MTQ[0], &mtq123, sizeof(MTQ_STRUCT));
    
    memcpy(RW[0], &rw1, sizeof(RW_STRUCT));
    if(BPDU[0]->dcdc_rw == 0 || BPDU[0]->rw1 == 0){
        RW[0]->rw_tx_comm.comm1.bit.motor_drive = 0;
    }
    
    memcpy(RW[1], &rw2, sizeof(RW_STRUCT));    
    if(BPDU[0]->dcdc_rw == 0 || BPDU[0]->rw2 == 0){
        RW[1]->rw_tx_comm.comm1.bit.motor_drive = 0;
    }
    
    memcpy(RW[2], &rw3, sizeof(RW_STRUCT));
    if(BPDU[0]->dcdc_rw == 0 || BPDU[0]->rw3 == 0){
        RW[2]->rw_tx_comm.comm1.bit.motor_drive = 0;
    }
    
    memcpy(RW[3], &rw4, sizeof(RW_STRUCT));
    if(BPDU[0]->dcdc_rw == 0 || BPDU[0]->rw4 == 0){
        RW[3]->rw_tx_comm.comm1.bit.motor_drive = 0;
    }
    
    temp_counter++;
    if(temp_counter == 20){
        temp_counter = 0;
    }
    
    memcpy(&BPDU_old, BPDU[0], sizeof(BPDU_STRUCT));
    memcpy(&CMD_old, CMD[0], sizeof(CMD_STRUCT));
    
    //use these for checking output
    *q0 = 1.0; // this can be a variable
    *q1 = 0.0;
    *q2 = 0.0;
    *q3 = 0.0;
	
	*q4 = AOCS_mode;
    
    //use printf function to display values on MATLAB console
    //here is examples
    //printf("%lf %lf %lf %lf\n", AOCS_qd[0], AOCS_qd[1], AOCS_qd[2], AOCS_qd[3]);
    //printf("%d %d\n", AOCS_det_time, STT_exptime);
    printf("\n");
    //printf("%d %d\n", AOCS_mode, CMD[0]->AOCS_mode);
    
}

static void mdlTerminate(SimStruct *S)
{    
    
    // close shared memory
    UnmapViewOfFile(FOG[0]);
    CloseHandle(FOG_hShm[0]);
    
    UnmapViewOfFile(GAS[0]);
    CloseHandle(GAS_hShm[0]);
    
    UnmapViewOfFile(GPS[0]);
    CloseHandle(GPS_hShm[0]);
    
    UnmapViewOfFile(MTQ[0]);
    CloseHandle(MTQ_hShm[0]);
    
    UnmapViewOfFile(NSAS[0]);
    CloseHandle(NSAS_hShm[0]);
    
    UnmapViewOfFile(NSAS[1]);
    CloseHandle(NSAS_hShm[1]);

    UnmapViewOfFile(NSAS[2]);
    CloseHandle(NSAS_hShm[2]);
    
    UnmapViewOfFile(NSAS[3]);
    CloseHandle(NSAS_hShm[3]);
    
    UnmapViewOfFile(NSAS[4]);
    CloseHandle(NSAS_hShm[4]);
    
    UnmapViewOfFile(NSAS[5]);
    CloseHandle(NSAS_hShm[5]);
    
    UnmapViewOfFile(RW[0]);
    CloseHandle(RW_hShm[0]);
    
    UnmapViewOfFile(RW[1]);
    CloseHandle(RW_hShm[1]);
    
    UnmapViewOfFile(RW[2]);
    CloseHandle(RW_hShm[2]);
    
    UnmapViewOfFile(RW[3]);
    CloseHandle(RW_hShm[3]);
    
    UnmapViewOfFile(STT[0]);
    CloseHandle(STT_hShm[0]);
    
    UnmapViewOfFile(BPDU[0]);
    CloseHandle(BPDU_hShm[0]);
    
    UnmapViewOfFile(CMD[0]);
    CloseHandle(CMD_hShm[0]);

}

#ifdef MATLAB_MEX_FILE
#include "simulink.c" 
#else
#include "cg_sfun.h"
#endif