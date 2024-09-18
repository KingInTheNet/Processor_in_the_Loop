/*==================*
 * Required defines *
 *==================*/

#ifndef MODEL
#error Must specify a model name.  Define MODEL=name.
#else
/* create generic macros that work with any model */
#define EXPAND_CONCAT(name1, name2) name1##name2
#define CONCAT(name1, name2) EXPAND_CONCAT(name1, name2)
#define MODEL_INITIALIZE CONCAT(MODEL, _initialize)
#define MODEL_OUTPUT CONCAT(MODEL, _output)
#define MODEL_UPDATE CONCAT(MODEL, _update)
#define MODEL_TERMINATE CONCAT(MODEL, _terminate)
#define RT_MDL CONCAT(MODEL, _M)
#endif

#ifndef NUMST
#error Must specify the number of sample times.  Define NUMST=number.
#endif

#if CLASSIC_INTERFACE == 1
#error Classic call interface is not supported.
#endif

#if ONESTEPFCN == 1
#error Single output/update function option not supported. Uncheck the 'Single output/update function' option
#endif

#if TERMFCN == 0
#error The terminate function is required. You must select the 'Terminate function required' option.
#endif

#if MULTI_INSTANCE_CODE == 1
#error Reusable code generation not supported. You must select 'Nonreusable function' option in 'Code interface packaging'
#endif

#define QUOTE1(name) #name
#define QUOTE(name) QUOTE1(name) /* need to expand name    */

#ifndef SAVEFILE
#define MATFILE2(file) #file ".mat"
#define MATFILE1(file) MATFILE2(file)
#define MATFILE MATFILE1(MODEL)
#else
#define MATFILE QUOTE(SAVEFILE)
#endif

#define VSMODEL_MMI_SIMULINK_BASED_HANDLES

/*==========*
 * Includes *
 *==========*/

#include <cassert>

extern "C"
{
#include "rtmodel.h"
}

#include "veristand_model_capi.h"

#include "rt_logging.h"
#ifdef UseMMIDataLogging
#include "rt_logging_mmi.h"
#endif

#include "ext_work.h"

#ifdef MODEL_STEP_FCN_CONTROL_USED
#error Model step function prototype control not supported.
#endif

/*========================*
 * Setup for multitasking *
 *========================*/

/*
 * Let MT be synonym for MULTITASKING
 */
#if defined(MT)
#if MT == 0
#undef MT
#else
#define MULTITASKING 1
#endif
#endif

#if defined(TID01EQ) && TID01EQ == 1
#define FIRST_TID 1
#else
#define FIRST_TID 0
#endif

#if defined(TID01EQ) && TID01EQ == 1
#define DISC_NUMST (NUMST - 1)
#else
#define DISC_NUMST NUMST
#endif

#if defined(EXT_MODE) && !defined(MULTITASKING) && DISC_NUMST > 1
#error External mode with Single-Task Multi-Rate models not supported.
#endif

#define ASSERT_NOT_NULL(x) assert(x && "NULL pointer passed")

struct VSModel
{
    bool extModeInitialized;
#ifdef EXT_MODE
#ifdef MULTITASKING
    double taskStepSizes[NUMST];
    double taskTimeOffsets[NUMST];
#endif /* MULTITASKING */
    uint64_T clockTicks[NUMST];
#endif /* EXT_MODE */
};

static struct VSModel* volatile vsModelSingleInstance = NULL;

static inline bool IsValidModelHandle(VSModelHandle model)
{
    return model != NULL && model == vsModelSingleInstance;
}

static inline bool IsValidMMIHandle(VSModelMappingInfoHandle mmi)
{
    return mmi != NULL;
}

static inline bool IsValidDataAddressMapHandle(VSModelDataAddressMapHandle dataAddressMap)
{
    return dataAddressMap != NULL;
}

static inline bool IsValidSignalsHandle(VSModelSignalsHandle signals)
{
    return signals != NULL;
}

static inline bool IsValidModelParametersHandle(VSModelParametersHandle modelParameters)
{
    return modelParameters != NULL;
}

static inline bool IsValidStatesHandle(VSModelStatesHandle states)
{
    return states != NULL;
}

static inline bool IsValidDimensionArrayHandle(VSModelDimensionArrayHandle dimensionArrayHandle)
{
    return dimensionArrayHandle != NULL;
}

static inline bool IsValidDimensionMapHandle(VSModelDimensionMapHandle dimensionMapHandle)
{
    return dimensionMapHandle != NULL;
}

static inline bool IsValidVardimsMapHandle(VSModelVardimsMapHandle vardimsMapHandle)
{
    return vardimsMapHandle != NULL;
}

static inline bool IsValidDataTypeMapHandle(VSModelDataTypeMapHandle dataTypeMap)
{
    return dataTypeMap != NULL;
}

static inline bool IsValidElementMapHandle(VSModelElementMapHandle elementMap)
{
    return elementMap != NULL;
}

static inline VSModelError ValidateTid(int32_t tid)
{
#ifdef MULTITASKING
    if (tid >= 0 && tid < NUMST) {
        // If TID01EQ==1, then TID 0 and TID 1 executes at the same rate and are merged togheter, TID1 should not be used anywhere in the code
#if defined(TID01EQ) && TID01EQ == 1
        if (tid == 1)
            return VSModelError_UsingTID1WhenTID01EQ;
#endif
    } else
        return VSModelError_InvalidTID;
#else /* else MULTITASKING */
    if (tid != 0)
        return VSModelError_InvalidTID;
#endif /* endif MULTITASKING */

    return VSModelError_NoError;
}

#ifdef MULTITASKING

static void RateScheduler(int32_t tid)
{
    if (tid == 0) {
        for (int32_t i = FIRST_TID + 1; i < NUMST; i++) {
            if (++rtmTaskCounter(RT_MDL, i) == rtmCounterLimit(RT_MDL, i))
                rtmTaskCounter(RT_MDL, i) = 0;
        };
    };
}

#endif

#ifdef EXT_MODE

static void InitializeTaskTimeInfo(struct VSModel* model)
{
#ifdef MULTITASKING
    for (int32_t tid = 0; tid < NUMST; tid++) {
        model->taskStepSizes[tid] = rtmCounterLimit(RT_MDL, tid) * RT_MDL->Timing.stepSize0;

        if (rtmTaskCounter(RT_MDL, tid) > 0) {
            uint32_t counterOffset = rtmCounterLimit(RT_MDL, tid) - rtmTaskCounter(RT_MDL, tid);
            model->taskTimeOffsets[tid] = counterOffset * RT_MDL->Timing.stepSize0;
        } else {
            model->taskTimeOffsets[tid] = 0;
        }
    }
#endif
}

static inline double GetTaskTime(struct VSModel* model, int32_t tid)
{
#ifdef MULTITASKING
    return model->clockTicks[tid] * model->taskStepSizes[tid] + model->taskTimeOffsets[tid];
#else
    return model->clockTicks[tid] * RT_MDL->Timing.stepSize0;
#endif
}

#endif

VSMODEL_EXPORT void VSModel_GetApiVersion(uint32_t* major, uint32_t* minor)
{
    ASSERT_NOT_NULL(major);
    ASSERT_NOT_NULL(minor);

    *major = VSMODEL_MAJOR_VERSION;
    *minor = VSMODEL_MINOR_VERSION;
}

VSMODEL_EXPORT const char* VSModel_GetModelName()
{
    return QUOTE(MODEL);
}

VSMODEL_EXPORT int32_t VSModel_GetNumOfSampleTimes()
{
    return NUMST;
}

VSMODEL_EXPORT double VSModel_GetStepSize0()
{
    return VSMODEL_STEP_SIZE0;
}

VSMODEL_EXPORT int32_t VSModel_GetExtMode()
{
#ifdef EXT_MODE
    return VSModelExtMode_TCPExtMode;
#else
    return VSModelExtMode_NoExtMode;
#endif
}

VSMODEL_EXPORT int32_t VSModel_Tid01Eq()
{
#ifdef TID01EQ
    return TID01EQ;
#else
    return 0;
#endif
}

VSMODEL_EXPORT int32_t VSModel_IsMultitasking()
{
#ifdef MULTITASKING
    return 1;
#else
    return 0;
#endif
}

VSMODEL_EXPORT int32_t VSModel_IsMultiInstanceCode()
{
#if MULTI_INSTANCE_CODE
    return 1;
#else
    return 0;
#endif
}

VSMODEL_EXPORT int32_t VSModel_Initialize(VSModelHandle* model, int32_t extModeArgc, const char* extModeArgv[], int32_t disableExternalMode, const char** errorStatus)
{
    ASSERT_NOT_NULL(model);
    ASSERT_NOT_NULL(errorStatus);

    *model = NULL;
    *errorStatus = NULL;

    if (vsModelSingleInstance != NULL)
        return VSModelError_NotAMultiInstanceCode;

    vsModelSingleInstance = (struct VSModel*)calloc(1, sizeof(struct VSModel));
    if (vsModelSingleInstance == NULL)
        return VSModelError_OutOfMemory;

    /* External mode */
    if (!disableExternalMode) {
        rtParseArgsForExtMode(extModeArgc, extModeArgv);
    }

    /* Initialize the model */
    MODEL_INITIALIZE();

    /* External mode */
    if (!disableExternalMode) {
        rtSetTFinalForExtMode(&rtmGetTFinal(RT_MDL));
        rtExtModeCheckInit(NUMST);
        rtExtModeWaitForStartPkt(rtmGetRTWExtModeInfo(RT_MDL),
            NUMST,
            (boolean_T*)&rtmGetStopRequested(RT_MDL));
        vsModelSingleInstance->extModeInitialized = true;
    }

    *errorStatus = rtmGetErrorStatus(RT_MDL);
    if (*errorStatus != NULL) {
        VSModel_Terminate(vsModelSingleInstance);
        return VSModelError_ModelError;
    }

#ifdef EXT_MODE
    if (!disableExternalMode) {
        InitializeTaskTimeInfo(vsModelSingleInstance);
    }
#endif

    *model = vsModelSingleInstance;
    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_Terminate(VSModelHandle model)
{
    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

#ifdef UseMMIDataLogging
    rt_CleanUpForStateLogWithMMI(rtmGetRTWLogInfo(RT_MDL));
#endif
    rt_StopDataLogging(MATFILE, rtmGetRTWLogInfo(RT_MDL));

    MODEL_TERMINATE();

    if (model->extModeInitialized) {
        rtExtModeShutdown(NUMST);
    }

    free(model);
    vsModelSingleInstance = NULL;

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetErrorStatus(VSModelHandle model, const char** errorStatus)
{
    ASSERT_NOT_NULL(errorStatus);

    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    *errorStatus = rtmGetErrorStatus(RT_MDL);
    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetStopRequested(VSModelHandle model)
{
    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    return rtmGetStopRequested(RT_MDL) ? 1 : 0;
}

VSMODEL_EXPORT int32_t VSModel_SetTFinal(VSModelHandle model, double finalTime)
{
    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

#ifdef rtmGetTFinal
    rtmGetTFinal(RT_MDL) = finalTime;
#endif
    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_TaskOutput(VSModelHandle model, int32_t tid)
{
    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    VSModelError error = ValidateTid(tid);
    if (error != VSModelError_NoError)
        return error;

#ifdef MULTITASKING
    MODEL_OUTPUT(tid);
#else
    MODEL_OUTPUT();
#endif

#ifdef EXT_MODE
    if (model->extModeInitialized) {
        if (tid == 0)
            rtExtModeUploadCheckTrigger(NUMST);

        rtExtModeUpload(tid, GetTaskTime(model, tid));
#if defined(TID01EQ) && TID01EQ == 1
        if (tid == 0)
            rtExtModeUpload(1, GetTaskTime(model, 0));
#endif /* (TID01EQ) && TID01EQ == 1*/
    }
#endif /* EXT_MODE */

    if (rtmGetErrorStatus(RT_MDL))
        return VSModelError_ModelError;

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_TaskUpdate(VSModelHandle model, int32_t tid)
{
    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    VSModelError error = ValidateTid(tid);
    if (error != VSModelError_NoError)
        return error;

#ifdef MULTITASKING
    MODEL_UPDATE(tid);
    RateScheduler(tid);
#else
    MODEL_UPDATE();
#endif

#ifdef EXT_MODE
    if (model->extModeInitialized) {
        if (tid == 0) {
            rtExtModeCheckEndTrigger();
        }

        ++model->clockTicks[tid];
    }
#endif

    if (rtmGetErrorStatus(RT_MDL))
        return VSModelError_ModelError;

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_StepTask(VSModelHandle model, int32_t tid)
{
    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    VSModelError error = ValidateTid(tid);
    if (error != VSModelError_NoError)
        return error;

#ifdef MULTITASKING
    return rtmStepTask(RT_MDL, tid);
#else
    return 1;
#endif
}

VSMODEL_EXPORT int32_t VSModel_ExtModePauseIfNeeded(VSModelHandle model)
{
    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    if (model->extModeInitialized) {
        rtExtModePauseIfNeeded(rtmGetRTWExtModeInfo(RT_MDL),
            NUMST,
            (boolean_T*)&rtmGetStopRequested(RT_MDL));
    }

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_ExtModeOneStep(VSModelHandle model)
{
    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    if (model->extModeInitialized) {
        rtExtModeOneStep(rtmGetRTWExtModeInfo(RT_MDL),
            NUMST,
            (boolean_T*)&rtmGetStopRequested(RT_MDL));
    }

    return VSModelError_NoError;
}

#ifdef VSMODEL_RT_MDL_INPUTS

VSMODEL_EXPORT int32_t VSModel_GetRawInputsPtr(VSModelHandle model, void** inputsPtr, int32_t* inputsSize)
{
    ASSERT_NOT_NULL(inputsPtr);
    ASSERT_NOT_NULL(inputsSize);

    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    *inputsSize = sizeof(VSMODEL_RT_MDL_INPUTS);
    *inputsPtr = &VSMODEL_RT_MDL_INPUTS;

    return VSModelError_NoError;
}

#endif /* VSMODEL_RT_MDL_INPUTS */

#ifdef VSMODEL_RT_MDL_OUTPUTS

VSMODEL_EXPORT int32_t VSModel_GetRawOutputsPtr(VSModelHandle model, void** outputsPtr, int32_t* outputsSize)
{
    ASSERT_NOT_NULL(outputsPtr);
    ASSERT_NOT_NULL(outputsSize);

    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    *outputsSize = sizeof(VSMODEL_RT_MDL_OUTPUTS);
    *outputsPtr = &VSMODEL_RT_MDL_OUTPUTS;

    return VSModelError_NoError;
}

#endif /* VSMODEL_RT_MDL_OUTPUTS */

VSMODEL_EXPORT int32_t VSModel_GetModelMappingInfo(VSModelHandle model, VSModelMappingInfoHandle* mmi)
{
    ASSERT_NOT_NULL(mmi);

    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    *mmi = &(rtmGetDataMapInfo(RT_MDL).mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetDataAddressMap(VSModelMappingInfoHandle mmi, VSModelDataAddressMapHandle* dataAddressMap)
{
    ASSERT_NOT_NULL(dataAddressMap);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *dataAddressMap = rtwCAPI_GetDataAddressMap(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetDataAddress(VSModelDataAddressMapHandle dataAddressMap, uint32_t addrMapIndex, void** dataAddress)
{
    ASSERT_NOT_NULL(dataAddress);

    if (!IsValidDataAddressMapHandle(dataAddressMap))
        return VSModelError_InvalidHandle;

    *dataAddress = rtwCAPI_GetDataAddress(dataAddressMap, addrMapIndex);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetDataTypeMap(VSModelMappingInfoHandle mmi, VSModelDataTypeMapHandle* dataTypeMap)
{
    ASSERT_NOT_NULL(dataTypeMap);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *dataTypeMap = rtwCAPI_GetDataTypeMap(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetDataTypeInfo(VSModelDataTypeMapHandle dataTypeMap, uint16_t index, const char** cDataName, const char** mwDataName, uint16_t* numElements, uint16_t* elemMapIndex, uint16_t* dataSize, uint8_t* slDataId, uint8_t* isComplex, uint8_t* isPointer, uint8_t* enumStorageType)
{
    if (!IsValidDataTypeMapHandle(dataTypeMap))
        return VSModelError_InvalidHandle;

    if (cDataName != NULL) {
        *cDataName = rtwCAPI_GetDataTypeCName(dataTypeMap, index);
    }

    if (mwDataName != NULL) {
        *mwDataName = rtwCAPI_GetDataTypeMWName(dataTypeMap, index);
    }

    if (numElements != NULL) {
        *numElements = rtwCAPI_GetDataTypeNumElements(dataTypeMap, index);
    }

    if (elemMapIndex != NULL) {
        *elemMapIndex = rtwCAPI_GetDataTypeElemMapIndex(dataTypeMap, index);
    }

    if (dataSize != NULL) {
        *dataSize = rtwCAPI_GetDataTypeSize(dataTypeMap, index);
    }

    if (slDataId != NULL) {
        *slDataId = rtwCAPI_GetDataTypeSLId(dataTypeMap, index);
    }

    if (isComplex != NULL) {
        *isComplex = rtwCAPI_GetDataIsComplex(dataTypeMap, index);
    }

    if (isPointer != NULL) {
        *isPointer = rtwCAPI_GetDataIsPointer(dataTypeMap, index);
    }

    if (enumStorageType != NULL) {
        *enumStorageType = rtwCAPI_GetDataEnumStorageType(dataTypeMap, index);
    }

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetDimensionMap(VSModelMappingInfoHandle mmi, VSModelDimensionMapHandle* dimensionMap)
{
    ASSERT_NOT_NULL(dimensionMap);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *dimensionMap = rtwCAPI_GetDimensionMap(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetVardimsMap(VSModelMappingInfoHandle mmi, VSModelVardimsMapHandle* vardimsMap)
{
    ASSERT_NOT_NULL(vardimsMap);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *vardimsMap = rtwCAPI_GetVarDimsAddressMap(mmi);

    return VSModelError_NoError;
}

static VSModelError ConvertToVSModelOrientation(rtwCAPI_Orientation simulinkOrientation, VSModelOrientation* vsmodelOrientation)
{
    switch (simulinkOrientation) {
        case rtwCAPI_SCALAR:
            *vsmodelOrientation = VSModelOrientation_SCALAR;
            break;
        case rtwCAPI_VECTOR:
            *vsmodelOrientation = VSModelOrientation_VECTOR;
            break;
        case rtwCAPI_MATRIX_ROW_MAJOR:
            *vsmodelOrientation = VSModelOrientation_MATRIX_ROW_MAJOR;
            break;
        case rtwCAPI_MATRIX_COL_MAJOR:
            *vsmodelOrientation = VSModelOrientation_MATRIX_COL_MAJOR;
            break;
        case rtwCAPI_MATRIX_COL_MAJOR_ND:
            *vsmodelOrientation = VSModelOrientation_MATRIX_COL_MAJOR_ND;
            break;
        case rtwCAPI_MATRIX_ROW_MAJOR_ND:
            *vsmodelOrientation = VSModelOrientation_MATRIX_ROW_MAJOR_ND;
            break;
        default:
            return VSModelError_EnumConversionError;
            break;
    }

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetDimensionInfo(VSModelDimensionMapHandle dimensionMap, uint16_t index, VSModelOrientation* orientation, uint32_t* dimArrayIndex, uint8_t* numDims)
{
    if (!IsValidDimensionMapHandle(dimensionMap))
        return VSModelError_InvalidHandle;

    if (orientation != NULL) {
        VSModelError enumError = ConvertToVSModelOrientation(rtwCAPI_GetOrientation(dimensionMap, index), orientation);
        if (enumError != VSModelError_NoError)
            return enumError;
    }

    if (dimArrayIndex != NULL) {
        *dimArrayIndex = rtwCAPI_GetDimArrayIndex(dimensionMap, index);
    }

    if (numDims != NULL) {
        *numDims = rtwCAPI_GetNumDims(dimensionMap, index);
    }

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetDimensionIsVariable(VSModelDimensionMapHandle dimensionMap, VSModelVardimsMapHandle vardimsMap, uint16_t index, uint8_t* dimIsVariable)
{
    ASSERT_NOT_NULL(dimIsVariable);

    if (!IsValidDimensionMapHandle(dimensionMap) || !IsValidVardimsMapHandle(vardimsMap))
        return VSModelError_InvalidHandle;

    *dimIsVariable = rtwCAPI_GetDimsIsVariable(vardimsMap, dimensionMap, index);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetDimensionArray(VSModelMappingInfoHandle mmi, VSModelDimensionArrayHandle* dimensionArray)
{
    ASSERT_NOT_NULL(dimensionArray);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *dimensionArray = rtwCAPI_GetDimensionArray(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetDimension(VSModelDimensionArrayHandle dimensionArray, uint32_t index, uint32_t* dimension)
{
    ASSERT_NOT_NULL(dimension);

    if (!IsValidDimensionArrayHandle(dimensionArray))
        return VSModelError_InvalidHandle;

    *dimension = dimensionArray[index];

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetRootInputs(VSModelMappingInfoHandle mmi, VSModelSignalsHandle* rootInputs, uint32_t* numRootInputs)
{
    ASSERT_NOT_NULL(rootInputs);
    ASSERT_NOT_NULL(numRootInputs);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *rootInputs = rtwCAPI_GetRootInputs(mmi);
    *numRootInputs = rtwCAPI_GetNumRootInputs(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetRootOutputs(VSModelMappingInfoHandle mmi, VSModelSignalsHandle* rootOutputs, uint32_t* numRootOutputs)
{
    ASSERT_NOT_NULL(rootOutputs);
    ASSERT_NOT_NULL(numRootOutputs);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *rootOutputs = rtwCAPI_GetRootOutputs(mmi);
    *numRootOutputs = rtwCAPI_GetNumRootOutputs(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetSignalInfo(VSModelSignalsHandle signals, uint32_t index, uint32_t* addrMapIndex, uint32_t* sysNum, const char** blockPath, const char** signalName, uint16_t* portNumber, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex, uint16_t* sTimeIndex)
{
    if (!IsValidSignalsHandle(signals))
        return VSModelError_InvalidHandle;

    if (addrMapIndex != NULL) {
        *addrMapIndex = rtwCAPI_GetSignalAddrIdx(signals, index);
    }

    if (sysNum != NULL) {
        *sysNum = rtwCAPI_GetSignalSysNum(signals, index);
    }

    if (blockPath != NULL) {
        *blockPath = rtwCAPI_GetSignalBlockPath(signals, index);
    }

    if (signalName != NULL) {
        *signalName = rtwCAPI_GetSignalName(signals, index);
    }

    if (portNumber != NULL) {
        *portNumber = rtwCAPI_GetSignalPortNumber(signals, index);
    }

    if (dataTypeIndex != NULL) {
        *dataTypeIndex = rtwCAPI_GetSignalDataTypeIdx(signals, index);
    }

    if (dimIndex != NULL) {
        *dimIndex = rtwCAPI_GetSignalDimensionIdx(signals, index);
    }

    if (fxpIndex != NULL) {
        *fxpIndex = rtwCAPI_GetSignalFixPtIdx(signals, index);
    }

    if (sTimeIndex != NULL) {
        *sTimeIndex = rtwCAPI_GetSignalSampleTimeIdx(signals, index);
    }

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetModelParameters(VSModelMappingInfoHandle mmi, VSModelParametersHandle* modelParameters, uint32_t* numModelParameters)
{
    ASSERT_NOT_NULL(modelParameters);
    ASSERT_NOT_NULL(numModelParameters);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *modelParameters = rtwCAPI_GetModelParameters(mmi);
    *numModelParameters = rtwCAPI_GetNumModelParameters(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetModelParameterInfo(VSModelParametersHandle modelParameters, uint32_t index, uint32_t* addrMapIndex, const char** varName, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex)
{
    if (!IsValidModelParametersHandle(modelParameters))
        return VSModelError_InvalidHandle;

    if (addrMapIndex != NULL) {
        *addrMapIndex = rtwCAPI_GetModelParameterAddrIdx(modelParameters, index);
    }

    if (varName != NULL) {
        *varName = rtwCAPI_GetModelParameterName(modelParameters, index);
    }

    if (dataTypeIndex != NULL) {
        *dataTypeIndex = rtwCAPI_GetModelParameterDataTypeIdx(modelParameters, index);
    }

    if (dimIndex != NULL) {
        *dimIndex = rtwCAPI_GetModelParameterDimensionIdx(modelParameters, index);
    }

    if (fxpIndex != NULL) {
        *fxpIndex = rtwCAPI_GetModelParameterFixPtIdx(modelParameters, index);
    }

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetChildMMI(VSModelMappingInfoHandle mmi, uint32_t index, VSModelMappingInfoHandle* childMMI)
{
    ASSERT_NOT_NULL(childMMI);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *childMMI = rtwCAPI_GetChildMMI(mmi, index);
    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetChildMMIArrayLen(VSModelMappingInfoHandle mmi, uint32_t* childMMIArrayLen)
{
    ASSERT_NOT_NULL(childMMIArrayLen);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *childMMIArrayLen = rtwCAPI_GetChildMMIArrayLen(mmi);
    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetElementMap(VSModelMappingInfoHandle mmi, VSModelElementMapHandle* elementMap)
{
    ASSERT_NOT_NULL(elementMap);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *elementMap = rtwCAPI_GetElementMap(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetElementInfo(VSModelElementMapHandle elementMap, uint16_t index, const char** elementName, uint32_t* elementOffset, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex)
{
    if (!IsValidElementMapHandle(elementMap))
        return VSModelError_InvalidHandle;

    if (elementName != NULL) {
        *elementName = rtwCAPI_GetElementName(elementMap, index);
    }

    if (elementOffset != NULL) {
        *elementOffset = rtwCAPI_GetElementOffset(elementMap, index);
    }

    if (dataTypeIndex != NULL) {
        *dataTypeIndex = rtwCAPI_GetElementDataTypeIdx(elementMap, index);
    }

    if (dimIndex != NULL) {
        *dimIndex = rtwCAPI_GetElementDimensionIdx(elementMap, index);
    }

    if (fxpIndex != NULL) {
        *fxpIndex = rtwCAPI_GetElementFixPtIdx(elementMap, index);
    }

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetPath(VSModelMappingInfoHandle mmi, const char** path)
{
    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    if (path != NULL) {
        *path = rtwCAPI_GetPath(mmi);
    }

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetSignals(VSModelMappingInfoHandle mmi, VSModelSignalsHandle* signals, uint32_t* numSignals)
{
    ASSERT_NOT_NULL(signals);
    ASSERT_NOT_NULL(numSignals);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *signals = rtwCAPI_GetSignals(mmi);
    *numSignals = rtwCAPI_GetNumSignals(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetStates(VSModelMappingInfoHandle mmi, VSModelStatesHandle* states, uint32_t* numStates)
{
    ASSERT_NOT_NULL(states);
    ASSERT_NOT_NULL(numStates);

    if (!IsValidMMIHandle(mmi))
        return VSModelError_InvalidHandle;

    *states = rtwCAPI_GetStates(mmi);
    *numStates = rtwCAPI_GetNumStates(mmi);

    return VSModelError_NoError;
}

VSMODEL_EXPORT int32_t VSModel_GetStateInfo(VSModelStatesHandle states, uint32_t index, uint32_t* addrMapIndex, int32_t* contStateStartIndex, const char** blockPath, const char** stateName, const char** pathAlias, uint16_t* dWorkIndex, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex, uint8_t* sTimeIndex, uint8_t* isContinuous, int32_t* hierInfoIdx, uint32_t* flatElemIdx)
{
    if (!IsValidStatesHandle(states))
        return VSModelError_InvalidHandle;

    if (addrMapIndex != NULL) {
        *addrMapIndex = rtwCAPI_GetStateAddrIdx(states, index);
    }

    if (contStateStartIndex != NULL) {
        *contStateStartIndex = rtwCAPI_GetContStateStartIndex(states, index);
    }

    if (blockPath != NULL) {
        *blockPath = rtwCAPI_GetStateBlockPath(states, index);
    }

    if (stateName != NULL) {
        *stateName = rtwCAPI_GetStateName(states, index);
    }

    if (pathAlias != NULL) {
        *pathAlias = rtwCAPI_GetStatePathAlias(states, index);
    }

    if (dWorkIndex != NULL) {
        *dWorkIndex = rtwCAPI_GetStateDWorkIdx(states, index);
    }

    if (dataTypeIndex != NULL) {
        *dataTypeIndex = rtwCAPI_GetStateDataTypeIdx(states, index);
    }

    if (dimIndex != NULL) {
        *dimIndex = rtwCAPI_GetStateDimensionIdx(states, index);
    }

    if (fxpIndex != NULL) {
        *fxpIndex = rtwCAPI_GetStateFixPtIndex(states, index);
    }

    if (sTimeIndex != NULL) {
        *sTimeIndex = rtwCAPI_GetStateSampleTimeIdx(states, index);
    }

    if (isContinuous != NULL) {
        *isContinuous = rtwCAPI_IsAContinuousState(states, index);
    }

    if (hierInfoIdx != NULL) {
        *hierInfoIdx = rtwCAPI_GetStateHierInfoIdx(states, index);
    }

    if (flatElemIdx != NULL) {
        *flatElemIdx = rtwCAPI_GetStateFlatElemIdx(states, index);
    }

    return VSModelError_NoError;
}

#ifdef EXT_MODE

extern "C" VSMODEL_EXPORT int32_t _VSModel_GetTaskTime(VSModelHandle model, int32_t tid, double* taskTime)
{
    ASSERT_NOT_NULL(taskTime);

    if (!IsValidModelHandle(model))
        return VSModelError_InvalidHandle;

    VSModelError error = ValidateTid(tid);
    if (error != VSModelError_NoError)
        return error;

    *taskTime = GetTaskTime(model, tid);
    return VSModelError_NoError;
}

#endif