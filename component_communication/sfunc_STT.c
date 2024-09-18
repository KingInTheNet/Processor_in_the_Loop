#define S_FUNCTION_NAME sfunc_STT
#define S_FUNCTION_LEVEL 2
#define MDL_START
#include "simstruc.h"
#include <windows.h>
// #include "communication.h"

#include "../IF_Wrapper/IF_list.h"
#include "../IF_Wrapper/DC.h"
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
// #include "../Drivers/AOCS/RW/RW.h"
#include "../Drivers/AOCS/STT/STT.h"
// #include "../Drivers/AOCS/AKI_GPS/AKI_GPS.h"

#define STTNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 0))
#define COMNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 1))

HANDLE STT_hShm[1]; // handle for shared memory
STT_STRUCT *STT[1]; // structure to share

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 2); // number of parameter of sfunction
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return;
    }

    if (!ssSetNumInputPorts(S, 1)) return; // number of input port

    ssSetInputPortWidth(S, 0, 12); // dimension of input port
    ssSetInputPortDataType(S, 0, SS_DOUBLE); // data type of input port
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 0)) return; // number of output port
    ssSetNumSampleTimes(S, 1);
}

static void mdlStart(SimStruct *S)
{   
     char SharedMemName[16]; // name of shared memory
     unsigned char STTnum = STTNUM;
    
    // open shared memory
    sprintf(SharedMemName, "STT%d", STTnum);
    STT_hShm[STTnum] = CreateFileMappingA((HANDLE)-1, NULL, PAGE_READWRITE, 0, sizeof(STT_STRUCT), SharedMemName);
    // share structure
    STT[STTnum] = (STT_STRUCT *)MapViewOfFile(STT_hShm[STTnum], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(STT_STRUCT));
    
    // initialize structure
    STT[STTnum]->capture_id = 0;
    STT[STTnum]->integration_state.byte[0] = 0;
    STT[STTnum]->integration_state.byte[1] = 0;
    STT[STTnum]->attitude[0] = 0.0;
    STT[STTnum]->attitude[1] = 0.0;
    STT[STTnum]->attitude[2] = 0.0;
    STT[STTnum]->attitude[3] = 1.0;
    STT[STTnum]->error_covariance_matrix[0][0] = 0.0;
    STT[STTnum]->error_covariance_matrix[0][1] = 0.0;
    STT[STTnum]->error_covariance_matrix[0][2] = 0.0;
    STT[STTnum]->error_covariance_matrix[1][0] = 0.0;
    STT[STTnum]->error_covariance_matrix[1][1] = 0.0;
    STT[STTnum]->error_covariance_matrix[1][2] = 0.0;
    STT[STTnum]->error_covariance_matrix[2][0] = 0.0;
    STT[STTnum]->error_covariance_matrix[2][1] = 0.0;
    STT[STTnum]->error_covariance_matrix[2][2] = 0.0;
    STT[STTnum]->master_imager_temperature = 0.0;
    STT[STTnum]->master_detected_star_count = 0;
    STT[STTnum]->master_star_info[0].hipparcos_id = 0;
    STT[STTnum]->master_star_info[0].luminance = 0;
    STT[STTnum]->master_star_info[0].tan_azimuth = 0.0;
    STT[STTnum]->master_star_info[0].tan_elevation = 0.0;
    STT[STTnum]->master_star_info[1].hipparcos_id = 0;
    STT[STTnum]->master_star_info[1].luminance = 0;
    STT[STTnum]->master_star_info[1].tan_azimuth = 0.0;
    STT[STTnum]->master_star_info[1].tan_elevation = 0.0;
    STT[STTnum]->master_star_info[2].hipparcos_id = 0;
    STT[STTnum]->master_star_info[2].luminance = 0;
    STT[STTnum]->master_star_info[2].tan_azimuth = 0.0;
    STT[STTnum]->master_star_info[2].tan_elevation = 0.0;
    STT[STTnum]->master_star_info[3].hipparcos_id = 0;
    STT[STTnum]->master_star_info[3].luminance = 0;
    STT[STTnum]->master_star_info[3].tan_azimuth = 0.0;
    STT[STTnum]->master_star_info[3].tan_elevation = 0.0;
    STT[STTnum]->master_star_info[4].hipparcos_id = 0;
    STT[STTnum]->master_star_info[4].luminance = 0;
    STT[STTnum]->master_star_info[4].tan_azimuth = 0.0;
    STT[STTnum]->master_star_info[4].tan_elevation = 0.0;
    STT[STTnum]->master_star_info[5].hipparcos_id = 0;
    STT[STTnum]->master_star_info[5].luminance = 0;
    STT[STTnum]->master_star_info[5].tan_azimuth = 0.0;
    STT[STTnum]->master_star_info[5].tan_elevation = 0.0;
    STT[STTnum]->master_estimation_status.byte[0] = 0;
    STT[STTnum]->master_estimation_status.byte[1] = 0;
    STT[STTnum]->master_estimation_status.byte[2] = 0;
    STT[STTnum]->master_estimation_status.byte[3] = 0;
}

static void mdlInitializeSampleTimes(SimStruct *S)
{  
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0);
} 

static void mdlOutputs(SimStruct *S, int_T tid)
{
     unsigned char STTnum = STTNUM;     
     const double *u = (const double*) ssGetInputPortSignal(S, 0);
//     
//     unsigned char header[4] = "st2z";
//     
     STT[STTnum]->attitude[0] = u[0];
     STT[STTnum]->attitude[1] = u[1];
     STT[STTnum]->attitude[2] = u[2];
     STT[STTnum]->attitude[3] = u[3];
     
     if(u[4] > 0.5) STT[STTnum]->master_estimation_status.bit.status = 0x05;
     if(u[4] < 0.5) STT[STTnum]->master_estimation_status.bit.status = 0x01;
     
     STT[STTnum]->error_covariance_matrix[0][0] = u[5];
     STT[STTnum]->error_covariance_matrix[0][1] = u[6];
     STT[STTnum]->error_covariance_matrix[0][2] = u[7];
     STT[STTnum]->error_covariance_matrix[1][0] = u[6];
     STT[STTnum]->error_covariance_matrix[1][1] = u[8];
     STT[STTnum]->error_covariance_matrix[1][2] = u[9];
     STT[STTnum]->error_covariance_matrix[2][0] = u[7];
     STT[STTnum]->error_covariance_matrix[2][1] = u[9];
     STT[STTnum]->error_covariance_matrix[2][2] = u[10];
 
     STT[STTnum]->master_imager_temperature = (float)u[11];
    
}

static void mdlTerminate(SimStruct *S)
{
    unsigned char STTnum = STTNUM;
    
    // close shared memory
    UnmapViewOfFile(STT[STTnum]);
    CloseHandle(STT_hShm[STTnum]);
}

#ifdef MATLAB_MEX_FILE
#include "simulink.c" 
#else
#include "cg_sfun.h"
#endif