#define S_FUNCTION_NAME VeriStandIO
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"
#define STRING_SIZE 2048
// Parameter access
enum { DIMS = 0, DTYPE, STIME, STYPE, IN_OR_OUT, NUM_PARAMS };
#define DIMS_ARG ssGetSFcnParam(S, DIMS)
#define DTYPE_ARG ssGetSFcnParam(S, DTYPE)
#define STIME_ARG ssGetSFcnParam(S, STIME)
#define STYPE_ARG ssGetSFcnParam(S, STYPE)
#define IN_OR_OUT_ARG ssGetSFcnParam(S, IN_OR_OUT)
#define EDIT_OK(S, ARG) (!((ssGetSimMode(S) == SS_SIMMODE_SIZES_CALL_ONLY) && mxIsEmpty(ARG)))
#define MDL_INITIALIZE_SAMPLE_TIMES
static void mdlInitializeSampleTimes(SimStruct* S)
{
    const real_T* sampleTimeArg = mxGetPr(STIME_ARG);
    // set the sample time to the parameter specified by the user
    ssSetSampleTime(S, 0, sampleTimeArg[0]);
    ssSetOffsetTime(S, 0, 0.0);
}
#define MDL_OUTPUTS
// TODO: What about fixed point?
static void mdlOutputs(SimStruct* S, int_T tid)
{
    UNUSED_ARG(tid);
}
#define MDL_START
static void mdlStart(SimStruct* S)
{
    UNUSED_ARG(S);
}
#define MDL_TERMINATE
static void mdlTerminate(SimStruct* S)
{
    UNUSED_ARG(S);
}

/* Forward declaration of functions that are defined later. */
#if defined(MATLAB_MEX_FILE)
#define MDL_CHECK_PARAMETERS
static void mdlCheckParameters(SimStruct* S);
static void processDataType(SimStruct* S, DTypeId* typeIdReg);
#endif

#define MDL_INITIALIZE_SIZES
static void mdlInitializeSizes(SimStruct* S)
{
    // we expect 6 parameters
    ssSetNumSFcnParams(S, NUM_PARAMS);
#if defined(MATLAB_MEX_FILE)
    const real_T* pr;
    DECL_AND_INIT_DIMSINFO(di);
    int dims[2];
    DTypeId dtype;
    int stype;
    int this_is_input = (int)*mxGetPr(IN_OR_OUT_ARG);
    // parameters received must equal parameters requested
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        ssSetErrorStatus(S, "VeriStand Error: Incorrect number of parameters.");
        return;
    }
    mdlCheckParameters(S);
    if (ssGetErrorStatus(S) != NULL)
        return;

    { // Parameters should not be tunable
        int pIdx;
        for (pIdx = 0; pIdx < NUM_PARAMS; pIdx++)
            ssSetSFcnParamTunable(S, pIdx, SS_PRM_NOT_TUNABLE);
    }
    // no states
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    // either 1 in 0 out, or 0 in 1 out.
    if (!ssSetNumInputPorts(S, 1 - this_is_input))
        return;
    if (!ssSetNumOutputPorts(S, this_is_input))
        return;
    if (!this_is_input) {
        DTypeId inputTypeIdReg;
        processDataType(S, &inputTypeIdReg);
        // INFO: ssGetDataTypeId returns INVALID_DTYPE_ID for userdefined datatypes and invalid datatypes for more information:https://in.mathworks.com/help/simulink/sfg/ssgetdtypeidfrommxarray.html
        if (inputTypeIdReg == INVALID_DTYPE_ID) {
            ssRegisterTypeFromParameter(S, DTYPE, &inputTypeIdReg);
            if (inputTypeIdReg == INVALID_DTYPE_ID) {
                ssSetErrorStatus(S, "VeriStand Error: Invalid InputBus type");
                return;
            }
            ssSetInputPortBusMode(S, 0, SL_BUS_MODE);
            ssSetBusInputAsStruct(S, 0, true);
        }
        ssSetInputPortDataType(S, 0, inputTypeIdReg);
    } else {
        DTypeId outputTypeIdReg;
        processDataType(S, &outputTypeIdReg);
        // INFO: ssGetDataTypeId returns INVALID_DTYPE_ID for userdefined datatypes and invalid datatypes for more information:https://in.mathworks.com/help/simulink/sfg/ssgetdtypeidfrommxarray.html
        if (outputTypeIdReg == INVALID_DTYPE_ID) {
            ssRegisterTypeFromParameter(S, DTYPE, &outputTypeIdReg);
            if (outputTypeIdReg == INVALID_DTYPE_ID) {
                ssSetErrorStatus(S, "VeriStand Error: Invalid OutputBus type");
                return;
            }
            const char* busName = ssGetDataTypeName(S, outputTypeIdReg);
            ssSetBusOutputObjectName(S, 0, (void*)busName);
            ssSetOutputPortBusMode(S, 0, SL_BUS_MODE);
            ssSetBusOutputAsStruct(S, 0, true);
        }
        ssSetOutputPortDataType(S, 0, outputTypeIdReg);
    }

    // get the dimensions
    pr = mxGetPr(DIMS_ARG);
    // setup the diminfo type
    di.numDims = 2;
    dims[0] = pr[0];
    // if they specified a scalar, then the second dim is 1
    dims[1] = (mxGetDimensions(DIMS_ARG)[1] == 1) ? 1 : pr[1];
    di.dims = (int*)&dims;
    di.width = dims[0] * dims[1];
    // if they specified -1, let simulink set the dimensions for us.
    if (this_is_input)
        ssSetOutputPortDimensionInfo(S, 0, (dims[0] != -1) ? &di : DYNAMIC_DIMENSION);
    else
        ssSetInputPortDimensionInfo(S, 0, (dims[0] != -1) ? &di : DYNAMIC_DIMENSION);
    /*
    STYPE_ARG is enumerated with the values:		Which need to map to
    1: auto											COMPLEX_INHERITED -1
    2: real											COMPLEX_NO		   0
    3: complex										COMPLEX_YES		   1
    again the values are off by 2, so subtract 2
    */
    stype = ((int)*mxGetPr(STYPE_ARG)) - 2;
    if (this_is_input)
        ssSetOutputPortComplexSignal(S, 0, stype);
    else
        ssSetInputPortComplexSignal(S, 0, stype);
    // for outports, we need to set directfeedthrough to access the input signal in mdlOutputs
    // and we need contiguous memory
    if (!this_is_input) {
        ssSetInputPortDirectFeedThrough(S, 0, 1);
        ssSetInputPortRequiredContiguous(S, 0, 1);
    }
    // only one sample time, and one mode
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    // we don't generate exceptions, and we want to force the usage of our TLC in RTW
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE || SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE);
#endif
}

#if defined(MATLAB_MEX_FILE)
#define MDL_CHECK_PARAMETERS
static void mdlCheckParameters(SimStruct* S)
{
    if (!EDIT_OK(S, DTYPE_ARG)) {
        ssSetErrorStatus(S, "VeriStand Error: Invalid data type.");
        return;
    }
    if (!EDIT_OK(S, STYPE_ARG)) {
        ssSetErrorStatus(S, "VeriStand Error: Invalid signal type.");
        return;
    }
    if (EDIT_OK(S, IN_OR_OUT_ARG)) {
        if ((int)*mxGetPr(IN_OR_OUT_ARG) != 0 && (int)*mxGetPr(IN_OR_OUT_ARG) != 1) {
            ssSetErrorStatus(S, "VeriStand Error: Invalid block type. Use 1 for inport, 0 for outport.");
            return;
        }
    } else {
        ssSetErrorStatus(S, "VeriStand Error: Invalid block type. Use 1 for inport, 0 for outport.");
        return;
    }
    if (EDIT_OK(S, DIMS_ARG)) {
        // DIMS_ARG should always have 2 dimensions
        if (mxGetNumberOfDimensions(DIMS_ARG) != 2) {
            ssSetErrorStatus(S, "VeriStand Error: Invalid port dimensions. Only scalars and [m n] matrices are allowed.");
            return;
        }
        // The 0th element of is always 1. The 1st element tells us how many dimensions were specified.
        if (mxGetDimensions(DIMS_ARG)[1] > 2) {
            ssSetErrorStatus(S, "VeriStand Error: Invalid port dimensions. Only scalars and [m n] matrices are allowed.");
            return;
        }
        // Dimensions must be an integer
        if (mxGetPr(DIMS_ARG)[0] - (int)mxGetPr(DIMS_ARG)[0] != 0) {
            ssSetErrorStatus(S, "VeriStand Error: Invalid port dimensions. Dimensions must be integer values.");
            return;
        }

        // Account for some corner cases that Simulink doesn't trap.
        if (mxGetDimensions(DIMS_ARG)[1] == 2) {
            if ((int)mxGetPr(DIMS_ARG)[0] < 1 && (int)mxGetPr(DIMS_ARG)[1] != 0) {
                ssSetErrorStatus(S, "VeriStand Error: Invalid port dimensions. For dynamiccaly sized dimensions, specify -1.");
                return;
            }
            if ((int)mxGetPr(DIMS_ARG)[0] == 1 && (int)mxGetPr(DIMS_ARG)[1] == -1) {
                ssSetErrorStatus(S, "VeriStand Error: Invalid port dimensions. For dynamiccaly sized dimensions, specify -1.");
                return;
            }
            // Dimensions must be an integer
            if (mxGetPr(DIMS_ARG)[1] - (int)mxGetPr(DIMS_ARG)[1] != 0) {
                ssSetErrorStatus(S, "VeriStand Error: Invalid port dimensions. Dimensions must be integer values.");
                return;
            }
        }
    } else {
        ssSetErrorStatus(S, "VeriStand Error: Invalid port dimensions.");
        return;
    }
    if (EDIT_OK(S, STIME_ARG)) {
        // STIME_ARG should always have 2 dimensions
        if (mxGetNumberOfDimensions(STIME_ARG) != 2) {
            ssSetErrorStatus(S, "VeriStand Error: Invalid sample time. Only scalars are allowed");
            return;
        }
        // The 0th element is always 1. The 1st element tells us how many dimensions were specified.
        if (mxGetDimensions(STIME_ARG)[1] != 1) {
            ssSetErrorStatus(S, "VeriStand Error: Invalid sample time. Only scalars are allowed.");
            return;
        }
        // Sample times can be -1, and any values greater than or equal to 0.
        if ((mxGetPr(STIME_ARG)[0] - (int)mxGetPr(STIME_ARG)[0] < 0.0) || mxGetPr(STIME_ARG)[0] < -1) {
            ssSetErrorStatus(S, "VeriStand Error: Invalid sample time. Valid sample times are -1, and values greater than or equal to 0.");
            return;
        }
    } else {
        ssSetErrorStatus(S, "VeriStand Error: Invalid sample time.");
        return;
    }
}

static void processDataType(SimStruct* S, DTypeId* typeIdReg)
{
    const char* INHERIT_AUTO = "Inherit: auto";
    char dialog_datatype_name[STRING_SIZE] = {0};
    mxGetString(DTYPE_ARG, dialog_datatype_name, (STRING_SIZE - 1));
    *typeIdReg = ssGetDataTypeId(S, dialog_datatype_name);
    // const char* dataType = ssGetDataTypeName(S, *typeIdReg);

    if (!strcmp(dialog_datatype_name, INHERIT_AUTO)) {
        *typeIdReg = -1;
    }
}

static void throwIfInvalidDataType(SimStruct* S, DTypeId dType)
{
    if (dType > SS_BOOLEAN) {
        if (ssIsDataTypeABus(S, dType) != 1) {
            ssSetErrorStatus(S, "VeriStand Error: DataType not supported");
            return;
        }
    }
}

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct* S, int port, DTypeId dType)
{
    throwIfInvalidDataType(S, dType);
    ssSetInputPortDataType(S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct* S, int port, DTypeId dType)
{
    throwIfInvalidDataType(S, dType);
    ssSetOutputPortDataType(S, 0, dType);
}

// simulink calls this function when we let it determine our dimensions
#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
static void mdlSetOutputPortDimensionInfo(SimStruct* S, int_T port, const DimsInfo_T* dimsInfo)
{
    // anything is okay as long as it has the correct dimensions
    if (dimsInfo->numDims > 2 || dimsInfo->numDims < 1) {
        ssSetErrorStatus(S, "VeriStand Error: Invalid dynamically sized port dimensions. Only scalars and [m n] matrices are allowed.");
        return;
    }
    ssSetOutputPortDimensionInfo(S, port, dimsInfo);
}
// simulink calls this function when we let it determine our dimensions
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct* S, int_T port, const DimsInfo_T* dimsInfo)
{
    // anything is okay as long as it has the correct dimensions
    if (dimsInfo->numDims > 2 || dimsInfo->numDims < 1) {
        ssSetErrorStatus(S, "VeriStand Error: Invalid dynamically sized port dimensions. Only scalars and [m n] matrices are allowed.");
        return;
    }
    ssSetInputPortDimensionInfo(S, port, dimsInfo);
}

#define MDL_SET_WORK_WIDTHS
static void mdlSetWorkWidths(SimStruct* S)
{
    UNUSED_ARG(S);
}
#endif

#ifdef MATLAB_MEX_FILE
#define MDL_RTW
#else
#undef MDL_RTW
#endif
#if defined(MDL_RTW)
static void mdlRTW(SimStruct* S)
{
    UNUSED_ARG(S);
}
#endif /* MDL_RTW */

/* Required S-function trailer */
#ifdef MATLAB_MEX_FILE
#include "simulink.c"
#else
#include "cg_sfun.h"
#endif