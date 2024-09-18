#define S_FUNCTION_NAME sfunc_MTQ
#define S_FUNCTION_LEVEL 2
#define MDL_START
#include "simstruc.h"
#include <windows.h>
// #include "communication.h"

#include "../IF_Wrapper/IF_list.h"
#include "../IF_Wrapper/DC.h"
// #include "../IF_Wrapper/RS422.h"
// #include "../IF_Wrapper/SPI.h"
// #include "../IF_Wrapper/AA.h"
// #include "../IF_Wrapper/PA.h"
// #include "../IF_Wrapper/CCSDS.h"
#include "../Drivers/Super/Driver_Super.h"
// #include "../Drivers/AOCS/GAS/GAS.h"
// #include "../Drivers/AOCS/GPS/GPS.h"
// #include "../Drivers/AOCS/GYRO/GYRO.h"
#include "../AOCS_Process/MTQ.h"
// #include "../Drivers/AOCS/NSAS/NSAS.h"
// #include "../Drivers/AOCS/RW/RW.h"
// #include "../Drivers/AOCS/STT/STT.h"
// #include "../Drivers/AOCS/AKI_GPS/AKI_GPS.h"

#define MTQNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 0))
//#define COMNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 1))

HANDLE MTQ_hShm[1];  // handle for shared memory
MTQ_STRUCT *MTQ[1]; // structure to share

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 1); // number of parameter of sfunction
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return;
    }

    if (!ssSetNumInputPorts(S, 1)) return; //number of input port

    ssSetInputPortWidth(S, 0, 1); // dimension of input port
    //ssSetInputPortDataType(S, 0, SS_DOUBLE); // data type of input port
    //ssSetInputPortDirectFeedThrough(S, 0, 1);
    //ssSetInputPortRequiredContiguous(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1)) return; // number of output port
    ssSetOutputPortWidth(S, 0, 3);
    ssSetNumSampleTimes(S, 1);
}

static void mdlStart(SimStruct *S)
{   
    char SharedMemName[16]; // name of shared memory
    unsigned char MTQnum = MTQNUM;
    
    // open shared memory
    sprintf(SharedMemName, "MTQ%d", MTQNUM);
    MTQ_hShm[MTQnum] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(MTQ_STRUCT), SharedMemName);
    // share structure
    MTQ[MTQnum] = (MTQ_STRUCT *)MapViewOfFile(MTQ_hShm[MTQnum], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MTQ_STRUCT));
    
    // initialize structure
    MTQ[MTQnum]->byte = 0;
    
}

static void mdlInitializeSampleTimes(SimStruct *S)
{  
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0);
} 

static void mdlOutputs(SimStruct *S, int_T tid)
{
    double *y = ssGetOutputPortRealSignal(S, 0);
    unsigned char MTQnum = MTQNUM;
    
    if(MTQ[MTQnum]->bit.x == 3){
        y[0] = 0.0;
    }
    if(MTQ[MTQnum]->bit.y == 3){
        y[1] = 0.0;
    }
    if(MTQ[MTQnum]->bit.z == 3){
        y[2] = 0.0;
    }
    if(MTQ[MTQnum]->bit.x == 1){
        y[0] = 5.0;
    }
    if(MTQ[MTQnum]->bit.y == 1){
        y[1] = 5.0;
    }
    if(MTQ[MTQnum]->bit.z == 1){
        y[2] = 5.0;
    }
    if(MTQ[MTQnum]->bit.x == 2){
        y[0] = -5.0;
    }
    if(MTQ[MTQnum]->bit.y == 2){
        y[1] = -5.0;
    }
    if(MTQ[MTQnum]->bit.z == 2){
        y[2] = -5.0;
    }
        
}

static void mdlTerminate(SimStruct *S)
{
    unsigned char MTQnum = MTQNUM;
    
    // close shared memory
    UnmapViewOfFile(MTQ[MTQnum]);
    CloseHandle(MTQ_hShm[MTQnum]);

}

#ifdef MATLAB_MEX_FILE
#include "simulink.c" 
#else
#include "cg_sfun.h"
#endif