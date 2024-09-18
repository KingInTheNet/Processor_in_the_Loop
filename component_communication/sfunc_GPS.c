#define S_FUNCTION_NAME sfunc_GPS
#define S_FUNCTION_LEVEL 2
#define MDL_START
#include "simstruc.h"
#include <windows.h>
//#include "communication.h"
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
#include "../Drivers/AOCS/GPS/GPS.h"
// #include "../Drivers/AOCS/GYRO/GYRO.h"
// #include "../Drivers/AOCS/MTQ/MTQ.h"
// #include "../Drivers/AOCS/NSAS/NSAS.h"
// #include "../Drivers/AOCS/RW/RW.h"
// #include "../Drivers/AOCS/STT/STT.h"
// #include "../Drivers/AOCS/AKI_GPS/AKI_GPS.h"

#define GPSNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 0))
//#define COMNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 1))

HANDLE GPS_hShm[1];  // handle for shared memory
GPS_STRUCT *GPS[1]; // structure to share

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 1); // number of parameter of sfunction
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return;
    }

    if (!ssSetNumInputPorts(S, 1)) return; //number of input port

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
    unsigned char GPSnum = GPSNUM;
    
    // open shared memory
    sprintf(SharedMemName, "GPS%d", GPSnum);
    GPS_hShm[GPSnum] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(GPS_STRUCT), SharedMemName);
    // share structure
    GPS[GPSnum] = (GPS_STRUCT *)MapViewOfFile(GPS_hShm[GPSnum], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(GPS_STRUCT));
    
    // initialize structure
    GPS[GPSnum]->latitude     = 0;
    GPS[GPSnum]->longitude    = 0;
    GPS[GPSnum]->altitude     = 0;
	GPS[GPSnum]->vector_x     = 0L;
	GPS[GPSnum]->vector_y     = 0L;
	GPS[GPSnum]->vector_z     = 0L;
    GPS[GPSnum]->speed        = 0;
    GPS[GPSnum]->direction    = 0;
    GPS[GPSnum]->pdop         = 0;
    GPS[GPSnum]->utc.year     = 0;
    GPS[GPSnum]->utc.month    = 0;
    GPS[GPSnum]->utc.day      = 0;
    GPS[GPSnum]->utc.hour     = 0;
    GPS[GPSnum]->utc.min      = 0;
    GPS[GPSnum]->utc.sec      = 0;
    GPS[GPSnum]->visible_sat  = 0;
    GPS[GPSnum]->delay_time   = 0;
    GPS[GPSnum]->pps          = 0;
    GPS[GPSnum]->status1.byte = 0;
    
}

static void mdlInitializeSampleTimes(SimStruct *S)
{  
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0);
} 

static void mdlOutputs(SimStruct *S, int_T tid)
{
    const double *u = (const double *)ssGetInputPortSignal(S, 0);
    unsigned char GPSnum = GPSNUM;
    int latitude, longitude;
    long long vector_x, vector_y, vector_z;
    
    if(u[0] >= 0.0){
        latitude = (int)(u[0] * 60.0 * 1000.0);
    }else{
        latitude = ~((int)(fabs(u[0]) * 60.0 * 1000.0)) + 1;
    }
    
    if(u[1] >= 0.0){
        longitude = (int)(u[1] * 60.0 * 1000.0);
    }else{
        longitude = ~((int)(fabs(u[1]) * 60.0 * 1000.0)) + 1;
    }

    if(u[3] >= 0.0){
        vector_x = (long long)(u[3] * 1000.0);
    }else{
        vector_x = ~((long long)(fabs(u[3]) * 1000.0)) + 1L;
    }
    
    if(u[4] >= 0.0){
        vector_y = (long long)(u[4] * 1000.0);
    }else{
        vector_y = ~((long long)(fabs(u[4]) * 1000.0)) + 1L;
    }
    
    if(u[5] >= 0.0){
        vector_z = (long long)(u[5] * 1000.0);
    }else{
        vector_z = ~((long long)(fabs(u[5]) * 1000.0)) + 1L;
    }

    GPS[GPSnum]->latitude    = latitude;
    GPS[GPSnum]->longitude   = longitude;
    GPS[GPSnum]->altitude    = (unsigned int)u[2];
	GPS[GPSnum]->vector_x    = vector_x;
	GPS[GPSnum]->vector_y    = vector_y;
	GPS[GPSnum]->vector_z    = vector_z;
    GPS[GPSnum]->utc.year    = (unsigned char)(u[6] - 2000.0);
    GPS[GPSnum]->utc.month   = (unsigned char)u[7];
    GPS[GPSnum]->utc.day     = (unsigned char)u[8];
    GPS[GPSnum]->utc.hour    = (unsigned char)u[9];
    GPS[GPSnum]->utc.min     = (unsigned char)u[10];
    GPS[GPSnum]->utc.sec     = (unsigned char)u[11];
    
}

static void mdlTerminate(SimStruct *S)
{
    unsigned char GPSnum = GPSNUM;
    
    // close shared memory
    UnmapViewOfFile(GPS[GPSnum]);
    CloseHandle(GPS_hShm[GPSnum]);
}

#ifdef MATLAB_MEX_FILE
#include "simulink.c" 
#else
#include "cg_sfun.h"
#endif