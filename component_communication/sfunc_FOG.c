#define S_FUNCTION_NAME sfunc_FOG
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
// #include "../Drivers/AOCS/GPS/GPS.h"
#include "../Drivers/AOCS/GYRO/GYRO.h"
// #include "../Drivers/AOCS/MTQ/MTQ.h"
// #include "../Drivers/AOCS/NSAS/NSAS.h"
// #include "../Drivers/AOCS/RW/RW.h"
// #include "../Drivers/AOCS/STT/STT.h"
// #include "../Drivers/AOCS/AKI_GPS/AKI_GPS.h"

#define FOGNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 0))
#define COMNUM (unsigned char)mxGetScalar(ssGetSFcnParam(S, 1))

extern HANDLE createHandle(char commPortName[], int port_baud_rate, int port_stopbits);

HANDLE FOG_hShm[1];  // handle for shared memory
GYRO_STRUCT *FOG[1]; // structure to share

float pow_2_31, pow_2_15;
    
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 2); //number of parameter of sfunction
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
    unsigned char FOGnum = FOGNUM;
    
    // open shared memory
    sprintf(SharedMemName, "FOG%d", FOGnum);
    FOG_hShm[FOGnum] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(GYRO_STRUCT), SharedMemName);
    // share structure
    FOG[FOGnum] = (GYRO_STRUCT *)MapViewOfFile(FOG_hShm[FOGnum], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(GYRO_STRUCT));
    
    // initialize structure
    FOG[FOGnum]->rs422_config.ch = 0;
    FOG[FOGnum]->rs422_config.baudrate = 0;
    FOG[FOGnum]->rs422_config.stop_bit = 0;
    
    FOG[FOGnum]->counter = 0;
    FOG[FOGnum]->status.byte[0] = 0;
    FOG[FOGnum]->status.byte[1] = 0;
	//FOG[FOGnum]->del_x = 0.0F;
	//FOG[FOGnum]->del_y = 0.0F;
	//FOG[FOGnum]->del_z = 0.0F;
	//FOG[FOGnum]->current_x = 50.0F;
	//FOG[FOGnum]->current_y = 60.0F;
	//FOG[FOGnum]->current_z = 70.0F;
	//FOG[FOGnum]->tempe = 0.0F;
	FOG[FOGnum]->del_x = 0;
	FOG[FOGnum]->del_y = 0;
	FOG[FOGnum]->del_z = 0;
	FOG[FOGnum]->current_x = 0;
	FOG[FOGnum]->current_y = 0;
	FOG[FOGnum]->current_z = 0;
	FOG[FOGnum]->tempe = 0;
    
    pow_2_31 = powf(2.0F, 31.0F);
    pow_2_15 = powf(2.0F, 15.0F);

}

static void mdlInitializeSampleTimes(SimStruct *S)
{  
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0);
} 

static void mdlOutputs(SimStruct *S, int_T tid)
{
    
    //int i;
    int n;
    
    unsigned char FOGnum = FOGNUM;
    
    const double *u = (const double *)ssGetInputPortSignal(S, 0);
    double rate[3];
    int32_T bin_rate_x, bin_rate_y, bin_rate_z;
    
    rate[0] = u[0];
    rate[1] = u[1];
    rate[2] = u[2];
    
    //unsigned char *temp;
    
    if(rate[0] >  9.9) rate[0] =  9.9;
    if(rate[0] < -9.9) rate[0] = -9.9;
    if(rate[1] >  9.9) rate[1] =  9.9;
    if(rate[1] < -9.9) rate[1] = -9.9;
    if(rate[2] >  9.9) rate[2] =  9.9;
    if(rate[2] < -9.9) rate[2] = -9.9;
    
    bin_rate_x = (int32_T)((float)rate[0] / 10.0F * pow_2_31);
    bin_rate_y = (int32_T)((float)rate[1] / 10.0F * pow_2_31);
    bin_rate_z = (int32_T)((float)rate[2] / 10.0F * pow_2_31);
    //int16_T bin_current_x = (int16_T)(FOG[FOGnum]->current_x / 5000.0F * pow_2_15);
    //int16_T bin_current_y = (int16_T)(FOG[FOGnum]->current_y / 5000.0F * pow_2_15);
    //int16_T bin_current_z = (int16_T)(FOG[FOGnum]->current_z / 5000.0F * pow_2_15);
    //int16_T bin_tempe = (int16_T)(u[3] / 100.0F * pow_2_15);
    
    //FOG[FOGnum]->del_x = (float)bin_rate_x / pow_2_31 * 10.0F;
	//FOG[FOGnum]->del_y = (float)bin_rate_y / pow_2_31 * 10.0F;
	//FOG[FOGnum]->del_z = (float)bin_rate_z / pow_2_31 * 10.0F;
    //FOG[FOGnum]->del_x_aa = (float)rate[0] * 0.4F;
    //FOG[FOGnum]->del_y_aa = (float)rate[1] * 0.4F;
    //FOG[FOGnum]->del_z_aa = (float)rate[2] * 0.4F;
    FOG[FOGnum]->del_x = bin_rate_x;
	FOG[FOGnum]->del_y = bin_rate_y;
	FOG[FOGnum]->del_z = bin_rate_z;
    FOG[FOGnum]->del_x_aa = (int32_T)((float)rate[0] * 0.4F / 5.0F * pow_2_15);
    FOG[FOGnum]->del_y_aa = (int32_T)((float)rate[1] * 0.4F / 5.0F * pow_2_15);
    FOG[FOGnum]->del_z_aa = (int32_T)((float)rate[2] * 0.4F / 5.0F * pow_2_15);
    
    //FOG[FOGnum]->del_x = (float)bin_rate_x;
    //FOG[FOGnum]->del_y = pow_2_15;
    //FOG[FOGnum]->del_z = 10.0F;
    //printf("%f\n", pow_2_31);

}

static void mdlTerminate(SimStruct *S)
{
    unsigned char FOGnum = FOGNUM;
    
    // close shared memory
    UnmapViewOfFile(FOG[FOGnum]);
    CloseHandle(FOG_hShm[FOGnum]);
}

#ifdef MATLAB_MEX_FILE
#include "simulink.c" 
#else
#include "cg_sfun.h"
#endif