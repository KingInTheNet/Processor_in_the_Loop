#define S_FUNCTION_NAME sfunc_NSAS
#define S_FUNCTION_LEVEL 2
#define MDL_START
#include "simstruc.h"
#include <windows.h>
// #include "communication.h"

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
#include "../Drivers/AOCS/NSAS/NSAS.h"
// #include "../Drivers/AOCS/RW/RW.h"
// #include "../Drivers/AOCS/STT/STT.h"
// #include "../Drivers/AOCS/AKI_GPS/AKI_GPS.h"

#define NSASID (unsigned char)mxGetScalar(ssGetSFcnParam(S, 0))
#define NSASNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 1))

HANDLE NSAS_hShm[6];  // handle for shared memory
NSAS_STRUCT *NSAS[6]; // structure to share

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 2); // number of parameter of sfunction
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return;
    }

    if (!ssSetNumInputPorts(S, 1)) return; // number of input port

    ssSetInputPortWidth(S, 0, 4); // dimension of input port
    ssSetInputPortDataType(S, 0, SS_DOUBLE); // data type of input port
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 0)) return; // number of output port
    ssSetNumSampleTimes(S, 1);
}

static void mdlStart(SimStruct *S)
{   
    char SharedMemName[16]; // shared memory name
    unsigned char NSASnum = NSASNUM;
    
    // open shared memory
    sprintf(SharedMemName, "NSAS%d", NSASnum);
    NSAS_hShm[NSASnum] = CreateFileMappingA((HANDLE)-1, NULL, PAGE_READWRITE, 0, sizeof(NSAS_STRUCT), SharedMemName);
    // share structure
    NSAS[NSASnum] = (NSAS_STRUCT *)MapViewOfFile(NSAS_hShm[NSASnum], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(NSAS_STRUCT));
    
    // inirialize structure
    NSAS[NSASnum]->error = 0;
    NSAS[NSASnum]->id = NSASID;
    NSAS[NSASnum]->gain_flag = 0;
    NSAS[NSASnum]->sun_flag = 0;
    NSAS[NSASnum]->gain = 0;
    NSAS[NSASnum]->tempe = 0;
    NSAS[NSASnum]->x = 0;
    NSAS[NSASnum]->y = 0;
}

static void mdlInitializeSampleTimes(SimStruct *S)
{  
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0);
} 

static void mdlOutputs(SimStruct *S, int_T tid)
{
    unsigned char NSASnum = NSASNUM;
    
    const double *u = (const double*) ssGetInputPortSignal(S, 0);
    
    //unsigned char stx = 0x02;
    //unsigned char packet_designator = 0x00;
    //unsigned char byte0 = 0x00;
    //unsigned char cr = 0x0d;
    //unsigned char lf = 0x0a;

    // -28degC - +85degC is devided by 256 
    unsigned char bin_tempe = (unsigned char)((u[1] + 28.0) / (85.0 + 28.0) * 256.0);
    // -55deg - +55deg is deveded by 256
    unsigned char bin_x = (unsigned char)((u[2] + 55.0) / (55.0 + 55.0) * 256.0);
    unsigned char bin_y = (unsigned char)((u[3] + 55.0) / (55.0 + 55.0) * 256.0);

    NSAS[NSASnum]->sun_flag = (unsigned char)u[0];
    if(NSAS[NSASnum]->sun_flag == 0){
        bin_x = 0;
        bin_y = 0;
    }
    //NSAS[NSASnum]->tempe = (float)bin_tempe / 256.0F * (85.0F + 28.0F) - 28.0F;
    //NSAS[NSASnum]->x = (float)bin_x / 256.0F * (55.0F + 55.0F) - 55.0F;
    //NSAS[NSASnum]->y = (float)bin_y / 256.0F * (55.0F + 55.0F) - 55.0F;
    NSAS[NSASnum]->tempe = bin_tempe;
    NSAS[NSASnum]->x = bin_x;
    NSAS[NSASnum]->y = bin_y;
}

static void mdlTerminate(SimStruct *S)
{
    unsigned char NSASnum = NSASNUM;
    
    // close shared memory
    UnmapViewOfFile(NSAS[NSASnum]);
    CloseHandle(NSAS_hShm[NSASnum]);
}

#ifdef MATLAB_MEX_FILE
#include "simulink.c" 
#else
#include "cg_sfun.h"
#endif