#ifndef VERISTAND_MODEL_CAPI_H
#define VERISTAND_MODEL_CAPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if kNIOSLinux
#define VSMODEL_EXPORT
#else
#define VSMODEL_EXPORT __declspec(dllexport)
#endif

    enum VSModelError
    {
        VSModelError_NoError = 0,
        VSModelError_OutOfMemory = -1,
        VSModelError_ModelError = -2,
        VSModelError_InvalidHandle = -3,
        VSModelError_InvalidTID = -4,
        VSModelError_UsingTID1WhenTID01EQ = -5,
        VSModelError_NotAMultiInstanceCode = -6,
        VSModelError_EnumConversionError = -7,
        VSModelError_LoadingFunctionFailed = -8
    };

    enum VSModelExtMode
    {
        VSModelExtMode_NoExtMode = 0,
        VSModelExtMode_TCPExtMode
    };

    enum VSModelOrientation
    {
        VSModelOrientation_SCALAR,
        VSModelOrientation_VECTOR,
        VSModelOrientation_MATRIX_ROW_MAJOR,
        VSModelOrientation_MATRIX_COL_MAJOR,
        VSModelOrientation_MATRIX_COL_MAJOR_ND,
        VSModelOrientation_MATRIX_ROW_MAJOR_ND
    };

    typedef struct VSModel* VSModelHandle;

    // clang-format off
#ifndef VSMODEL_MMI_SIMULINK_BASED_HANDLES
    typedef struct VSModelMappingInfo* VSModelMappingInfoHandle;
    typedef struct VSModelDataAddressMap* VSModelDataAddressMapHandle;
    typedef struct VSModelDataTypeMap* VSModelDataTypeMapHandle;
    typedef struct VSModelDimensionMap* VSModelDimensionMapHandle;
    typedef struct VSModelVardimsMap* VSModelVardimsMapHandle;
    typedef struct VSModelDimensionArray* VSModelDimensionArrayHandle;
    typedef struct VSModelSignals* VSModelSignalsHandle;
    typedef struct VSModelParameters* VSModelParametersHandle;
    typedef struct VSModelElementMap* VSModelElementMapHandle;
    typedef struct VSModelStates* VSModelStatesHandle;
#else
    typedef rtwCAPI_ModelMappingInfo* VSModelMappingInfoHandle;
    typedef void** VSModelDataAddressMapHandle;
    typedef rtwCAPI_DataTypeMap const* VSModelDataTypeMapHandle;
    typedef rtwCAPI_DimensionMap const* VSModelDimensionMapHandle;
    typedef int32_T** VSModelVardimsMapHandle;
    typedef uint_T const* VSModelDimensionArrayHandle;
    typedef rtwCAPI_Signals const* VSModelSignalsHandle;
    typedef rtwCAPI_ModelParameters const* VSModelParametersHandle;
    typedef rtwCAPI_ElementMap const* VSModelElementMapHandle;
    typedef rtwCAPI_States const* VSModelStatesHandle;
#endif
    // clang-format on

    /*
     * VSModel_GetAPIVersion
     * Returns the API Version which can be used for backwards compatibility support
     * Outputs
     *      major : major version number
     *      minor : minor version number
     */
    VSMODEL_EXPORT void VSModel_GetApiVersion(uint32_t* major, uint32_t* minor);
    typedef void (*VSModel_GetApiVersionFunction)(uint32_t* major, uint32_t* minor);

    /*
     * VSModel_GetModelName
     * Return value: The name of the model defined by MODEL
     */
    VSMODEL_EXPORT const char* VSModel_GetModelName();
    typedef const char* (*VSModel_GetModelNameFunction)();

    /*
     * VSModel_GetNumOfSampleTimes
     * Return value: Number of sample times
     */
    VSMODEL_EXPORT int32_t VSModel_GetNumOfSampleTimes();
    typedef int32_t (*VSModel_GetNumOfSampleTimesFunction)();

    /*
     * VSModel_GetStepSize0
     * Return value: The fundamental sample time of the model if the periodic sample time constraint is 'Unconstrained'; -1 if the periodic sample time constraint is 'Ensure sample time independent'
     */
    VSMODEL_EXPORT double VSModel_GetStepSize0();
    typedef double (*VSModel_GetStepSize0Function)();

    /*
     * VSModel_GetExtMode
     * Return value: One of the VSModelExtMode values, representing the type of external mode
     */
    VSMODEL_EXPORT int32_t VSModel_GetExtMode();
    typedef int32_t (*VSModel_GetExtModeFunction)();

    /*
     * VSModel_Tid01Eq
     * Return value: 1 if TID0 and TID1 are treated as one rate. This can happen if model has continuous time and both continous time and the fastest discrete time are treated as one rate in generate code.
     *      In case this function returns 1, you should never pass TID1 to the schedule functions
     */
    VSMODEL_EXPORT int32_t VSModel_Tid01Eq();
    typedef int32_t (*VSModel_Tid01EqFunction)();

    /*
     * VSModel_IsMultitasking
     * Return value: 1 if the model is multi rate and the task scheduler is implemented externally, 0 otherwise.
     */
    VSMODEL_EXPORT int32_t VSModel_IsMultitasking();
    typedef int32_t (*VSModel_IsMultitaskingFunction)();

    /*
     * VSModel_IsMultiInstanceCode
     * Return value 1 if MULTI_INSTANCE_CODE is defined, 0 otherwise. We enforce Non-reusable functions from the TLC so this should always be 0.
     */
    VSMODEL_EXPORT int32_t VSModel_IsMultiInstanceCode();
    typedef int32_t (*VSModel_IsMultiInstanceCodeFunction)();

    /*
     * VSModel_Initialize
     * Initializes the model.
     *
     * Inputs:
     *    extModeArgc: number of external mode arguments
     *    extModeArgv: external mode arguments. Note that Simulink expects that argv[0] contains the process name. Empty string can also be passed, but don't pass an option argument in argv[0] (e.g. -port)
     *    disableExternalMode: indication whether to disable the external mode at runtime
     * Outputs:
     *    model: the handle of the model instance. Use this reference in other functions
     *    errorStatus: may contain a string describing the error. Is set to NULL if there is no error status
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_Initialize(VSModelHandle* model, int32_t extModeArgc, const char* extModeArgv[], int32_t disableExternalMode, const char** errorStatus);
    typedef int32_t (*VSModel_InitializeFunction)(VSModelHandle* model, int32_t extModeArgc, const char* extModeArgv[], int32_t disableExternalMode, const char** errorStatus);

    /*
     * VSModel_Terminate
     * Terminates the model.
     *
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_Terminate(VSModelHandle model);
    typedef int32_t (*VSModel_TerminateFunction)(VSModelHandle model);

    /*
     * VSModel_GetErrorStatus
     * Returns the error status.
     *
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     * Outputs:
     *    errorStatus: will contain the error status string. Is set to NULL if there is no error status
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetErrorStatus(VSModelHandle model, const char** errorStatus);
    typedef int32_t (*VSModel_GetErrorStatusFunction)(VSModelHandle model, const char** errorStatus);

    /*
     * VSModel_GetStopRequested
     * Returns the stop requested flag
     *
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     * Returns: 1 if stop is requested, 0 if not.
     *    A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetStopRequested(VSModelHandle model);
    typedef int32_t (*VSModel_GetStopRequestedFunction)(VSModelHandle model);

    /*
     * VSModel_SetTFinal
     * Sets the final time. If the model does not have a final time defined (e.g. time independent model) this function
     * has not effect.
     *
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     *    finalTime: final time in seconds. -1 means infinity
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_SetTFinal(VSModelHandle model, double finalTime);
    typedef int32_t (*VSModel_SetTFinalFunction)(VSModelHandle model, double finalTime);

    /*
     * VSModel_TaskOutput
     * Implements model output function
     *
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     *    tid: task id for multirate models. For single rate models pass 0
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_TaskOutput(VSModelHandle model, int32_t tid);
    typedef int32_t (*VSModel_TaskOutputFunction)(VSModelHandle model, int32_t tid);

    /*
     * VSModel_TaskUpdate
     * Implements model update function
     *
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     *    tid: task id for multirate models. For single rate models pass 0
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_TaskUpdate(VSModelHandle model, int32_t tid);
    typedef int32_t (*VSModel_TaskUpdateFunction)(VSModelHandle model, int32_t tid);

    /*
     * VSModel_StepTask
     * Gives an indication whether the task with tid can be scheduled
     *
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     *    tid: task id for multirate models. For single rate models pass 0
     * Returns: 1 if the task can be scheduled, 0 otherwise.
     *    A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_StepTask(VSModelHandle model, int32_t tid);
    typedef int32_t (*VSModel_StepTaskFunction)(VSModelHandle model, int32_t tid);

    /*
     * VSModel_ExtModePauseIfNeeded
     * Pause the process if needed
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_ExtModePauseIfNeeded(VSModelHandle model);
    typedef int32_t (*VSModel_ExtModePauseIfNeededFunction)(VSModelHandle model);

    /*
     * VSModel_ExtModeOneStep
     * Execute external mode. Can be called in a low priority thread.
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_ExtModeOneStep(VSModelHandle model);
    typedef int32_t (*VSModel_ExtModeOneStepFunction)(VSModelHandle model);

    /*
     * VSModel_GetRawInputsPtr
     * Returns the address and the size of the inputs structure.
     * Note that if the model has not inputs, this function is not exported.
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     * Outputs:
     *    inputsPtr: address of the struct
     *    inputsSize: size of the structure in bytes
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetRawInputsPtr(VSModelHandle model, void** inputsPtr, int32_t* inputsSize);
    typedef int32_t (*VSModel_GetRawInputsPtrFunction)(VSModelHandle model, void** inputsPtr, int32_t* inputsSize);

    /*
     * VSModel_GetRawOutputsPtr
     * Returns the address and the size of the outputs structure.
     * Note that if the model has not outputs, this function is not exported.
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     * Outputs:
     *    outputsPtr: address of the struct
     *    outputsSize: size of the structure in bytes
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetRawOutputsPtr(VSModelHandle model, void** outputsPtr, int32_t* outputsSize);
    typedef int32_t (*VSModel_GetRawOutputsPtrFunction)(VSModelHandle model, void** outputsPtr, int32_t* outputsSize);

    /*
     * VSModel_GetModelMappingInfo
     * Returns a pointer to the rtwCAPI_ModelMappingInfo structure
     * Inputs:
     *    model: model reference returned by VSModel_Initialize
     * Outputs:
     *    mmi: address of the struct rtwCAPI_ModelMappingInfo
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetModelMappingInfo(VSModelHandle model, VSModelMappingInfoHandle* mmi);
    typedef int32_t (*VSModel_GetModelMappingInfoFunction)(VSModelHandle model, VSModelMappingInfoHandle* mmi);

    /*
     * VSModel_GetDataAddressMap
     * Returns a pointer to the rtDataAddrMap array
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    dataAddressMap: address of the rtDataAddrMap array
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetDataAddressMap(VSModelMappingInfoHandle mmi, VSModelDataAddressMapHandle* dataAddressMap);
    typedef int32_t (*VSModel_GetDataAddressMapFunction)(VSModelMappingInfoHandle mmi, VSModelDataAddressMapHandle* dataAddressMap);

    /*
     * VSModel_GetDataAddress
     * Returns the data adress from a data address map
     * Inputs:
     *    dataAddressMap: VSModelDataAddressMapHandle returned by VSModel_GetDataAddressMap
     *    addrMapIndex: index in the map returned by VSModel_GetSignalInfo or VSModel_GetModelParameterInfo
     * Outputs:
     *    dataAddress: address of the data
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetDataAddress(VSModelDataAddressMapHandle dataAddressMap, uint32_t addrMapIndex, void** dataAddress);
    typedef int32_t (*VSModel_GetDataAddressFunction)(VSModelDataAddressMapHandle dataAddressMap, uint32_t addrMapIndex, void** dataAddress);

    /*
     * VSModel_GetDataTypeMap
     * Returns a pointer to the rtwCAPI_DataTypeMap struct
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    dataTypeMap: address of the rtwCAPI_DataTypeMap struct
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetDataTypeMap(VSModelMappingInfoHandle mmi, VSModelDataTypeMapHandle* dataTypeMap);
    typedef int32_t (*VSModel_GetDataTypeMapFunction)(VSModelMappingInfoHandle mmi, VSModelDataTypeMapHandle* dataTypeMap);

    /*
     * VSModel_GetDataTypeInfo
     * Returns information about the data type of a signal or parameter. Passing in a null at any of the output parameters will ignore that parameter.
     * Inputs:
     *    dataTypeMap: VSModelDataTypeMapHandle returned by VSModel_GetDataTypeMap
     *    index: the index of the dataType returned by VSModel_GetSignalInfo or VSModel_GetModelParameterInfo
     * Outputs:
     *    cDataName: C language data type name
     *    mwDataName: MathWorks data type, typedef in rtwtypes.h
     *    numElements: number of elements, 0 for non-structure data
     *    elemMapIndex: index into the ElementMap, gives Bus Info
     *    dataSize: data size in Bytes
     *    slDataId: enumerated data type from simstruc_types.h
     *    isComplex: is the data type complex (1=Complex, 0=Real)
     *    isPointer: is data accessed Via Pointer (1=yes, 0=no)
     *    enumStorageType: storage type for enum data types
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetDataTypeInfo(VSModelDataTypeMapHandle dataTypeMap, uint16_t index, const char** cDataName, const char** mwDataName, uint16_t* numElements, uint16_t* elemMapIndex, uint16_t* dataSize, uint8_t* slDataId, uint8_t* isComplex, uint8_t* isPointer, uint8_t* enumStorageType);
    typedef int32_t (*VSModel_GetDataTypeInfoFunction)(VSModelDataTypeMapHandle dataTypeMap, uint16_t index, const char** cDataName, const char** mwDataName, uint16_t* numElements, uint16_t* elemMapIndex, uint16_t* dataSize, uint8_t* slDataId, uint8_t* isComplex, uint8_t* isPointer, uint8_t* enumStorageType);

    /*
     * VSModel_GetDimensionMap
     * Returns a pointer to the rtwCAPI_DimensionMap struct
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    dimensionMap: address of the rtwCAPI_DimensionMap struct
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetDimensionMap(VSModelMappingInfoHandle mmi, VSModelDimensionMapHandle* dimensionMap);
    typedef int32_t (*VSModel_GetDimensionMapFunction)(VSModelMappingInfoHandle mmi, VSModelDimensionMapHandle* dimensionMap);

    /*
     * VSModel_GetVardimsMap
     * Returns a pointer to the vardimsAddrMap
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    vardimsAddrMap: address of the vardimsAddrMap
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetVardimsMap(VSModelMappingInfoHandle mmi, VSModelVardimsMapHandle* vardimsMap);
    typedef int32_t (*VSModel_GetVardimsMapFunction)(VSModelMappingInfoHandle mmi, VSModelVardimsMapHandle* vardimsMap);

    /*
     * VSModel_GetDimensionInfo
     * Returns information about the dimesion at a given index. Passing in a null at any of the output parameters will ignore that parameter.
     * Inputs:
     *    dimensionMap: VSModelDimensionMapHandle returned by VSModel_GetDimensionMap
     *    index: the dimIndex returned by info getter API (e.g. VSModel_GetSignalInfo)
     * Outputs:
     *    orientation: orientation of data (scalar, vector, etc.)
     *    dimArrayIndex: index into dimension array
     *    numDims: number of dimensions
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetDimensionInfo(VSModelDimensionMapHandle dimensionMap, uint16_t index, VSModelOrientation* orientation, uint32_t* dimArrayIndex, uint8_t* numDims);
    typedef int32_t (*VSModel_GetDimensionInfoFunction)(VSModelDimensionMapHandle dimensionMap, uint16_t index, VSModelOrientation* orientation, uint32_t* dimArrayIndex, uint8_t* numDims);

    /*
     * VSModel_GetDimensionIsVariable
     * Returns whether the dimension information is a variable.
     * Inputs:
     *    dimensionMap: VSModelDimensionMapHandle returned by VSModel_GetDimensionMap
     *    vardimsMap: VSModelVardimsMapHandle returned by VSModel_GetVardimsMap
     *    index: the dimIndex returned by info getter API (e.g. VSModel_GetSignalInfo)
     * Outputs:
     *    dimIsVariable: 1 if dimesion is variable, 0 otherwise
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetDimensionIsVariable(VSModelDimensionMapHandle dimensionMap, VSModelVardimsMapHandle vardimsMap, uint16_t index, uint8_t* dimIsVariable);
    typedef int32_t (*VSModel_GetDimensionIsVariableFunction)(VSModelDimensionMapHandle dimensionMap, VSModelVardimsMapHandle vardimsMap, uint16_t index, uint8_t* dimIsVariable);

    /*
     * VSModel_GetDimensionArray
     * Returns a pointer to the static map's dimensionArray
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    dimensionArray: address of the static map's dimensionArray
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetDimensionArray(VSModelMappingInfoHandle mmi, VSModelDimensionArrayHandle* dimensionArray);
    typedef int32_t (*VSModel_GetDimensionArrayFunction)(VSModelMappingInfoHandle mmi, VSModelDimensionArrayHandle* dimensionArray);

    /*
     * VSModel_GetDimension
     * Returns the actual dimension from a dimension array, at a given index
     * Inputs:
     *   dimensionArray: VSModelDimensionArrayHandle returned by VSModel_GetDimensionArray
     *   index: the dimArrayIndex returned by VSModel_GetDimensionInfo
     * Outputs:
     *   dimension: the dimension at the index
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetDimension(VSModelDimensionArrayHandle dimensionArray, uint32_t index, uint32_t* dimension);
    typedef int32_t (*VSModel_GetDimensionFunction)(VSModelDimensionArrayHandle dimensionArray, uint32_t index, uint32_t* dimension);

    /*
     * VSModel_GetRootInputs
     * Returns a pointer to the static map's rootInputs structure
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    rootInputs: address of the static map's rootInputs
     *    numRootInputs: number of root inputs
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetRootInputs(VSModelMappingInfoHandle mmi, VSModelSignalsHandle* rootInputs, uint32_t* numRootInputs);
    typedef int32_t (*VSModel_GetRootInputsFunction)(VSModelMappingInfoHandle mmi, VSModelSignalsHandle* rootInputs, uint32_t* numRootInputs);

    /*
     * VSModel_GetRootOutputs
     * Returns a pointer to the static map's rootOutputs structure
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    rootOutputs: address of the static map's rootOutputs
     *    numRootOutputs: number of root outputs
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetRootOutputs(VSModelMappingInfoHandle mmi, VSModelSignalsHandle* rootOutputs, uint32_t* numRootOutputs);
    typedef int32_t (*VSModel_GetRootOutputsFunction)(VSModelMappingInfoHandle mmi, VSModelSignalsHandle* rootOutputs, uint32_t* numRootOutputs);

    /*
     * VSModel_GetSignalInfo
     * Returns information about the signal which can be a root input or a root output. Passing in a null at any of the output parameters will ignore that parameter.
     * Inputs:
     *    signals: VSModelSignalsHandle returned by VSModel_GetRootInputs or VSModel_GetRootOutputs
     *    index: the index of the signal from 0 to numRootInputs/numRootOutputs - 1
     * Outputs:
     *    addrMapIndex: index in the map returned by VSModel_GetDataAddressMap
     *    sysNum: system identification number, where 0 = root
     *    blockPath: block's full path name
     *    signalName: signal label
     *    portNumber: port number
     *    dataTypeIndex: index in the map returned by VSModel_GetDataTypeMap
     *    dimIndex: index in the map returned by VSModel_GetDimensionMap
     *    fxpIndex: index into FixPtMap
     *    sTimeIndex: index into SampleTimeMap
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetSignalInfo(VSModelSignalsHandle signals, uint32_t index, uint32_t* addrMapIndex, uint32_t* sysNum, const char** blockPath, const char** signalName, uint16_t* portNumber, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex, uint16_t* sTimeIndex);
    typedef int32_t (*VSModel_GetSignalInfoFunction)(VSModelSignalsHandle signals, uint32_t index, uint32_t* addrMapIndex, uint32_t* sysNum, const char** blockPath, const char** signalName, uint16_t* portNumber, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex, uint16_t* sTimeIndex);

    /*
     * VSModel_GetModelParameters
     * Returns a pointer to the static map's modelParameters structure
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    modelParameters: address of the static map's modelParameters
     *    numModelParameters: number of model parameters
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetModelParameters(VSModelMappingInfoHandle mmi, VSModelParametersHandle* modelParameters, uint32_t* numModelParameters);
    typedef int32_t (*VSModel_GetModelParametersFunction)(VSModelMappingInfoHandle mmi, VSModelParametersHandle* modelParameters, uint32_t* numModelParameters);

    /*
     * VSModel_GetModelParameterInfo
     * Returns information about the model parameter. Passing in a null at any of the output parameters will ignore that parameter.
     * Inputs:
     *    modelParameters: VSModelParametersHandle returned by VSModel_GetModelParameters
     *    index: the index of the parameter from 0 to numModelParameters - 1
     * Outputs:
     *    addrMapIndex: index in the map returned by VSModel_GetDataAddressMap
     *    varName: name of the parameter
     *    dataTypeIndex: index in the map returned by VSModel_GetDataTypeMap
     *    dimIndex: index in the map returned by VSModel_GetDimensionMap
     *    fxpIndex: index into FixPtMap
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetModelParameterInfo(VSModelParametersHandle modelParameters, uint32_t index, uint32_t* addrMapIndex, const char** varName, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex);
    typedef int32_t (*VSModel_GetModelParameterInfoFunction)(VSModelParametersHandle modelParameters, uint32_t index, uint32_t* addrMapIndex, const char** varName, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex);

    /*
     * VSModel_GetChildMMI
     * Returns the element found in the index position in the instance map's childMMIArray
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     *    index: the index of the child MMI from 0 to childMMIArrayLen - 1
     * Outputs:
     *    childMMI: the childMMI at index position
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetChildMMI(VSModelMappingInfoHandle mmi, uint32_t index, VSModelMappingInfoHandle* childMMI);
    typedef int32_t (*VSModel_GetChildMMIFunction)(VSModelMappingInfoHandle mmi, uint32_t index, VSModelMappingInfoHandle* childMMI);

    /*
     * VSModel_GetChildMMIArrayLen
     * Returns the length of the instance map's childMMIArray
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    childMMIArrayLen: length of the childMMIArray
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetChildMMIArrayLen(VSModelMappingInfoHandle mmi, uint32_t* childMMIArrayLen);
    typedef int32_t (*VSModel_GetChildMMIArrayLenFunction)(VSModelMappingInfoHandle mmi, uint32_t* childMMIArrayLen);

    /*
     * VSModel_GetElementMap
     * Returns a pointer to the rtwCAPI_ElementMap struct
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    elementMap: address of the rtwCAPI_ElementMap struct
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetElementMap(VSModelMappingInfoHandle mmi, VSModelElementMapHandle* elementMap);
    typedef int32_t (*VSModel_GetElementMapFunction)(VSModelMappingInfoHandle mmi, VSModelElementMapHandle* elementMap);

    /*
     * VSModel_GetElementInfo
     * Returns information about an element. Passing in a null at any of the output parameters will ignore that parameter.
     * Inputs:
     *    elementMap: VSModelElementMapHandle returned by VSModel_GetElementMap
     *    index: the elemMapIndex returned by VSModel_GetDataTypeInfo
     * Outputs:
     *    elementName: the name of the element
     *    elementOffset: offset relative to the structure containing the element
     *    dataTypeIndex: index in the map returned by VSModel_GetDataTypeMap
     *    dimIndex: index in the map returned by VSModel_GetDimensionMap
     *    fxpIndex: index into FixPtMap
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetElementInfo(VSModelElementMapHandle elementMap, uint16_t index, const char** elementName, uint32_t* elementOffset, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex);
    typedef int32_t (*VSModel_GetElementInfoFunction)(VSModelElementMapHandle elementMap, uint16_t index, const char** elementName, uint32_t* elementOffset, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex);

    /*
     * VSModel_GetPath
     * Returns information about the path
     * Inputs:
     *    mmi: address of the struct rtwCAPI_ModelMappingInfo
     * Outputs:
     *    path: the path corresponding to the mmi
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetPath(VSModelMappingInfoHandle mmi, const char** path);
    typedef int32_t (*VSModel_GetPathFunction)(VSModelMappingInfoHandle mmi, const char** path);

    /*
     * VSModel_GetSignals
     * Returns a pointer to the static map's signals structure
     * Inputs:
     *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
     * Outputs:
     *    signals: address of the static map's signals
     *    numSignals: number of signals
     * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
     */
    VSMODEL_EXPORT int32_t VSModel_GetSignals(VSModelMappingInfoHandle mmi, VSModelSignalsHandle* signals, uint32_t* numSignals);
    typedef int32_t (*VSModel_GetSignalsFunction)(VSModelMappingInfoHandle mmi, VSModelSignalsHandle* signals, uint32_t* numSignals);

    /*
    * VSModel_GetStates
    * Returns a pointer to the static map's state structure
    * Inputs:
    *    mmi: VSModelMappingInfoHandle returned by VSModel_GetModelMappingInfo
    * Outputs:
    *    States: address of the static map's states
    *    numStates: number of states
    * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
    */
    VSMODEL_EXPORT int32_t VSModel_GetStates(VSModelMappingInfoHandle mmi, VSModelStatesHandle* states, uint32_t* numStates);
    typedef int32_t (*VSModel_GetStatesFunction)(VSModelMappingInfoHandle mmi, VSModelStatesHandle* states, uint32_t* numStates);

    /*
    * VSModel_GetStateInfo
    * Returns information about the state. Passing in a null at any of the output parameters will ignore that parameter.
    * Inputs:
    *    states: VSModelStatesHandle returned by VSModel_GetModelParameters
    *    index: the index of the parameter from 0 to numStates - 1
    * Outputs:
    *    addrMapIndex: index into the data address map 
    *    contStateStartIndex: starting index in the model's continuous state and state derivative vectors. This is set to -1 for discrete states
    *    blockPath: block's full path name (RTW mangled version)
    *    stateName: state name, Default:DWork/Cont State Identifier 
    *    pathAlias: Alias block path 
    *    dWorkIndex: Index into the Block DWork, 0 for cont. states
    *    dataTypeIndex: index into DataTypeMap, gives state data type 
    *    dimIndex: index into DimensionMap, gives state dimensions 
    *    fxpIndex: index into FixPtMap, gives Fixed point info 
    *    sTimeIndex: index into SampleTimeMap, gives Task info 
    *    isContinuous: if the state is a Continuous state
    *    hierInfoIdx: the hierInfo associated with this state, -1 if no hierInfo 
    *    flatElemIdx: flat element index in hierarchy
    * Returns: value indicating whether the function was successful. A negative number indicates that an error occurred (see VSModelError error codes)
    */
    VSMODEL_EXPORT int32_t VSModel_GetStateInfo(VSModelStatesHandle states, uint32_t index, uint32_t* addrMapIndex, int32_t* contStateStartIndex, const char** blockPath, const char** stateName, const char** pathAlias, uint16_t* dWorkIndex, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex, uint8_t* sTimeIndex, uint8_t* isContinuous, int32_t* hierInfoIdx, uint32_t* flatElemIdx);
    typedef int32_t (*VSModel_GetStateInfoFunction)(VSModelStatesHandle states, uint32_t index, uint32_t* addrMapIndex, int32_t* contStateStartIndex, const char** blockPath, const char** stateName, const char** pathAlias, uint16_t* dWorkIndex, uint16_t* dataTypeIndex, uint16_t* dimIndex, uint16_t* fxpIndex, uint8_t* sTimeIndex, uint8_t* isContinuous, int32_t* hierInfoIdx, uint32_t* flatElemIdx);

#ifdef __cplusplus
}
#endif

#endif /* VERISTAND_MODEL_CAPI_H */