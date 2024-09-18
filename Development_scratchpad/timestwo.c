#define S_FUNCTION_NAME timestwo /* Specifies the name of the S-function (timestwo) */
#define S_FUNCTION_LEVEL 2 /* Specifies that the S-function is in the Level 2 format */

#include "simstruc.h" /* Defines the data structure */
static void mdlInitializeSizes(SimStruct *S) /* Initialize the input and output ports and their size */
{
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch reported by the Simulink engine*/
    }

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S,2)) return;
    ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetOutputPortWidth(S, 1, DYNAMICALLY_SIZED);

    ssSetNumSampleTimes(S, 1);

    /* Take care when specifying exception free code - see sfuntmpl.doc */
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
    }
static void mdlInitializeSampleTimes(SimStruct *S) /* Set the sample time of the S-function as inherited */
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME); 
    ssSetOffsetTime(S, 0, 0.0);
}
static void mdlOutputs(SimStruct *S, int_T tid) /* Calculate the block output for each time step */
{
    int_T i;
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    real_T *y = ssGetOutputPortRealSignal(S,0);
    int_T widthy = ssGetOutputPortWidth(S,0);

    real_T *z = ssGetOutputPortRealSignal(S,1);
    int_T widthz = ssGetOutputPortWidth(S,1);

    for (i=0; i<widthy; i++) {
        *y++ = 2.0 *(*uPtrs[i]);
    }
    i = 0;
    for (i=0; i<widthz; i++) {
        *y++ = (*uPtrs[i]);
    }
}
static void mdlTerminate(SimStruct *S){} /* Perform tasks at the end of the simulation */

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif