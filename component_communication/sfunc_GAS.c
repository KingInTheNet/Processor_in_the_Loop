#define S_FUNCTION_NAME sfunc_GAS
#define S_FUNCTION_LEVEL 2
#define MDL_START
#include "simstruc.h"
#include <windows.h>
//#include "communication.h"
#include <math.h>

#include "../IF_Wrapper/IF_list.h"
// #include "../IF_Wrapper/DC.h"
// #include "../IF_Wrapper/RS422.h"
// #include "../IF_Wrapper/SPI.h"
#include "../IF_Wrapper/AA.h"
// #include "../IF_Wrapper/PA.h"
// #include "../IF_Wrapper/CCSDS.h"
#include "../Drivers/Super/Driver_Super.h"
#include "../Drivers/AOCS/GAS/GAS.h"
// #include "../Drivers/AOCS/GPS/GPS.h"
// #include "../Drivers/AOCS/GYRO/GYRO.h"
// #include "../Drivers/AOCS/MTQ/MTQ.h"
// #include "../Drivers/AOCS/NSAS/NSAS.h"
// #include "../Drivers/AOCS/RW/RW.h"
// #include "../Drivers/AOCS/STT/STT.h"
// #include "../Drivers/AOCS/AKI_GPS/AKI_GPS.h"

#define GASNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 0))

HANDLE GAS_hShm[1];  // handle for shared memory
GAS_STRUCT *GAS[1]; // structure to share

float pow_2_15;

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 1); // number of parameter of sfunction
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return;
    }

    if (!ssSetNumInputPorts(S, 1)) return; //number of input port

    ssSetInputPortWidth(S, 0, 4); // dimension of input port
    ssSetInputPortDataType(S, 0, SS_DOUBLE); // data type of input port
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 0)) return; // number of output port
    ssSetNumSampleTimes(S, 1);
}

static void mdlStart(SimStruct *S)
{   
    char SharedMemName[16]; // name of shared memory
    unsigned char GASnum = GASNUM;
    
    // open shared memory
    sprintf(SharedMemName, "GAS%d", GASnum);
    GAS_hShm[GASnum] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(GAS_STRUCT), SharedMemName);
    // share structure
    GAS[GASnum] = (GAS_STRUCT *)MapViewOfFile(GAS_hShm[GASnum], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(GAS_STRUCT));
    
    // initialize structure
    //GAS[GASnum]->x   = 0.0F;
    //GAS[GASnum]->y   = 0.0F;
    //GAS[GASnum]->z   = 0.0F;
	//GAS[GASnum]->ref = 0.0F;
    
    //GAS[GASnum]->cycle_sum_x   = 0.0F;
    //GAS[GASnum]->cycle_sum_y   = 0.0F;
    //GAS[GASnum]->cycle_sum_z   = 0.0F;
    //GAS[GASnum]->cycle_sum_ref = 0.0F;
    //GAS[GASnum]->cycle_cnt     = 0;
    
    GAS[GASnum]->x   = 0;
    GAS[GASnum]->y   = 0;
    GAS[GASnum]->z   = 0;
	GAS[GASnum]->ref = 0;
    
    GAS[GASnum]->cycle_sum_x   = 0;
    GAS[GASnum]->cycle_sum_y   = 0;
    GAS[GASnum]->cycle_sum_z   = 0;
    GAS[GASnum]->cycle_sum_ref = 0;
    GAS[GASnum]->cycle_cnt     = 0;
    
    pow_2_15 = powf(2.0F, 15.0F);
    
}

static void mdlInitializeSampleTimes(SimStruct *S)
{  
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0);
} 

static void mdlOutputs(SimStruct *S, int_T tid)
{
    const double *u = (const double *)ssGetInputPortSignal(S, 0);
    unsigned char GASnum = GASNUM;
    
    //int16_T bin_x   = (int16_T)((float)u[0] / 5.0F * pow_2_15);
    //int16_T bin_y   = (int16_T)((float)u[1] / 5.0F * pow_2_15);
    //int16_T bin_z   = (int16_T)((float)u[2] / 5.0F * pow_2_15);
    //int16_T bin_ref = (int16_T)((float)u[3] / 5.0F * pow_2_15);

    GAS[GASnum]->x   = (int16_T)((float)u[0] / 5.0F * pow_2_15);
    GAS[GASnum]->y   = (int16_T)((float)u[1] / 5.0F * pow_2_15);
    GAS[GASnum]->z   = (int16_T)((float)u[2] / 5.0F * pow_2_15);
    GAS[GASnum]->ref = (int16_T)((float)u[3] / 5.0F * pow_2_15);

    //GAS[GASnum]->x   = (float)bin_x   / pow_2_15 * 5.0F;
    //GAS[GASnum]->y   = (float)bin_y   / pow_2_15 * 5.0F;
    //GAS[GASnum]->z   = (float)bin_z   / pow_2_15 * 5.0F;
    //GAS[GASnum]->ref = (float)bin_ref / pow_2_15 * 5.0F;
    
    //GAS[GASnum]->x = 1.0F;
    //GAS[GASnum]->y = 2.0F;
    //GAS[GASnum]->z = 3.0F;
    //GAS[GASnum]->ref = 4.0F;
}

static void mdlTerminate(SimStruct *S)
{
    unsigned char GASnum = GASNUM;
    
    // close shared memory
    UnmapViewOfFile(GAS[GASnum]);
    CloseHandle(GAS_hShm[GASnum]);
}

#ifdef MATLAB_MEX_FILE
#include "simulink.c" 
#else
#include "cg_sfun.h"
#endif