#define S_FUNCTION_NAME sfunc_RW_RX
#define S_FUNCTION_LEVEL 2
#define MDL_START
#include "simstruc.h"
#include <windows.h>
// #include "communication.h"
#include <math.h>

#include "../IF_Wrapper/IF_list.h"
// #include "../IF_Wrapper/DC.h"
#include "../IF_Wrapper/RS422.h"
// #include "../IF_Wrapper/SPI.h"
// #include "../IF_Wrapper/AA.h"
// #include "../IF_Wrapper/PA.h"
// #include "../IF_Wrapper/CCSDS.h"
#include "../Drivers/Super/Driver_Super.h"
// #include "../Drivers/AOCS/GAS/GAS.h"
// #include "../Drivers/AOCS/GPS/GPS.h"
// #include "../Drivers/AOCS/GYRO/GYRO.h"
// #include "../Drivers/AOCS/MTQ/MTQ.h"
// #include "../Drivers/AOCS/NSAS/NSAS.h"
#include "../Drivers/AOCS/RW/RW.h"
// #include "../Drivers/AOCS/STT/STT.h"
// #include "../Drivers/AOCS/AKI_GPS/AKI_GPS.h"

#define RWNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 0))

HANDLE RW_hShm[4];  // handle for shared memory
RW_STRUCT *RW[4]; // structure to share

float pow_2_15, pow_2_16;
    
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 1); // number of parameter of sfunction
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return;
    }

    if (!ssSetNumInputPorts(S, 1)) return; //number of input port

    ssSetInputPortWidth(S, 0, 8); // dimension of input port
    ssSetInputPortDataType(S, 0, SS_DOUBLE); // data type of input port
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 0)) return; // number of output port
    ssSetNumSampleTimes(S, 1);
}

static void mdlStart(SimStruct *S)
{   
    char SharedMemName[16]; // name of shared memory
    unsigned char RWnum = RWNUM;
    
    // ‹¤open shared memory
    sprintf(SharedMemName, "RW%d", RWnum);
    RW_hShm[RWnum] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(RW_STRUCT), SharedMemName);
    // share structure
    RW[RWnum] = (RW_STRUCT *)MapViewOfFile(RW_hShm[RWnum], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(RW_STRUCT));
    
    // initialize structure
    RW[RWnum]->rw_tx_comm.mess_no = 0;
    RW[RWnum]->rw_tx_comm.comm1.byte = 0;
    RW[RWnum]->rw_tx_comm.comm2 = 0;
    RW[RWnum]->rw_tx_comm.comm3 = 0;
    
    RW[RWnum]->rw_rx_sts.mess_no = 0;
    RW[RWnum]->rw_rx_sts.sts1.byte = 0;
    RW[RWnum]->rw_rx_sts.sts2.byte = 0;
    RW[RWnum]->rw_rx_sts.sts3 = 0;
    RW[RWnum]->rw_rx_sts.sts4 = 0;
    RW[RWnum]->rw_rx_sts.sts5 = 0;    
    
    //pow_2_31 = powf(2.0F, 31.0F);
    pow_2_15 = powf(2.0F, 15.0F);
    pow_2_16 = pow_2_15 * 2.0F;

}

static void mdlInitializeSampleTimes(SimStruct *S)
{  
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0);
} 

static void mdlOutputs(SimStruct *S, int_T tid)
{
    unsigned char RWnum = RWNUM;
    
    const double *u = (const double *)ssGetInputPortSignal(S, 0);
    //double *y = ssGetOutputPortRealSignal(S, 0);
    //unsigned short int bin_volt;
    
    //y[0] = (double)RW[RWnum]->rw_tx_comm.comm1.bit.open_close_loop;
    //y[1] = (double)RW[RWnum]->rw_tx_comm.comm1.bit.torque_output_direction;
    //y[2] = (double)RW[RWnum]->rw_tx_comm.comm1.bit.motor_drive;
    //y[3] = (double)((float)RW[RWnum]->rw_tx_comm.comm2 / pow_2_16 * 50.0F);
    
    RW[RWnum]->rw_rx_sts.mess_no = RW[RWnum]->rw_tx_comm.mess_no;
    RW[RWnum]->rw_rx_sts.sts1.bit.motor_drive = (unsigned)u[0];
    RW[RWnum]->rw_rx_sts.sts1.bit.torque_output_direction = (unsigned)u[1];
    RW[RWnum]->rw_rx_sts.sts1.bit.rotation_direction = (unsigned)u[2];
    
    RW[RWnum]->rw_rx_sts.sts2.bit.overvoltage = (unsigned)u[3];
    RW[RWnum]->rw_rx_sts.sts2.bit.overcurrent = (unsigned)u[4];
    
    RW[RWnum]->rw_rx_sts.sts3 = (unsigned short int)u[5];
    RW[RWnum]->rw_rx_sts.sts4 = (signed short int)(u[6] / 0.001);
    RW[RWnum]->rw_rx_sts.sts5 = (signed short int)u[7];
    
}

static void mdlTerminate(SimStruct *S)
{
    unsigned char RWnum = RWNUM;
    
    // close shared memory
    UnmapViewOfFile(RW[RWnum]);
    CloseHandle(RW_hShm[RWnum]);
}

#ifdef MATLAB_MEX_FILE
#include "simulink.c" 
#else
#include "cg_sfun.h"
#endif