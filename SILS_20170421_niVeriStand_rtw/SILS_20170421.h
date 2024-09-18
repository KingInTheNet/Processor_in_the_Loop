#ifndef RTW_HEADER_SILS_20170421_h_
#define RTW_HEADER_SILS_20170421_h_
#include <stddef.h>
#include <string.h>
#include <float.h>
#include <math.h>
#ifndef SILS_20170421_COMMON_INCLUDES_
# define SILS_20170421_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif

#include "SILS_20170421_types.h"

#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include "rt_assert.h"
#include "rt_defines.h"

#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->ModelData.blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->ModelData.blockIO = (val))
#endif

#ifndef rtmGetChecksums
# define rtmGetChecksums(rtm)          ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
# define rtmSetChecksums(rtm, val)     ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetConstBlockIO
# define rtmGetConstBlockIO(rtm)       ((rtm)->ModelData.constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
# define rtmSetConstBlockIO(rtm, val)  ((rtm)->ModelData.constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ()
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ()
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->ModelData.defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->ModelData.defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
# define rtmGetDirectFeedThrough(rtm)  ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
# define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
# define rtmGetErrorStatusFlag(rtm)    ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
# define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
# define rtmSetFinalTime(rtm, val)     ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
# define rtmGetFirstInitCondFlag(rtm)  ((rtm)->Timing.firstInitCondFlag)
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ((rtm)->Timing.firstInitCondFlag = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetMdlRefGlobalTID
# define rtmGetMdlRefGlobalTID(rtm)    ()
#endif

#ifndef rtmSetMdlRefGlobalTID
# define rtmSetMdlRefGlobalTID(rtm, val) ()
#endif

#ifndef rtmGetMdlRefTriggerTID
# define rtmGetMdlRefTriggerTID(rtm)   ()
#endif

#ifndef rtmSetMdlRefTriggerTID
# define rtmSetMdlRefTriggerTID(rtm, val) ()
#endif

#ifndef rtmGetModelMappingInfo
# define rtmGetModelMappingInfo(rtm)   ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
# define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
# define rtmGetModelName(rtm)          ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
# define rtmSetModelName(rtm, val)     ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNonInlinedSFcns
# define rtmGetNonInlinedSFcns(rtm)    ((rtm)->NonInlinedSFcns)
#endif

#ifndef rtmSetNonInlinedSFcns
# define rtmSetNonInlinedSFcns(rtm, val) ((rtm)->NonInlinedSFcns = (val))
#endif

#ifndef rtmGetNumBlockIO
# define rtmGetNumBlockIO(rtm)         ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
# define rtmSetNumBlockIO(rtm, val)    ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
# define rtmGetNumBlockParams(rtm)     ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
# define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
# define rtmGetNumBlocks(rtm)          ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
# define rtmSetNumBlocks(rtm, val)     ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
# define rtmGetNumContStates(rtm)      ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
# define rtmSetNumContStates(rtm, val) ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
# define rtmGetNumDWork(rtm)           ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
# define rtmSetNumDWork(rtm, val)      ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
# define rtmGetNumInputPorts(rtm)      ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
# define rtmSetNumInputPorts(rtm, val) ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
# define rtmGetNumNonSampledZCs(rtm)   ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
# define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
# define rtmGetNumOutputPorts(rtm)     ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
# define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumSFcnParams
# define rtmGetNumSFcnParams(rtm)      ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
# define rtmSetNumSFcnParams(rtm, val) ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
# define rtmGetNumSFunctions(rtm)      ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
# define rtmSetNumSFunctions(rtm, val) ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
# define rtmGetNumSampleTimes(rtm)     ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
# define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
# define rtmGetNumU(rtm)               ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
# define rtmSetNumU(rtm, val)          ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
# define rtmGetNumY(rtm)               ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
# define rtmSetNumY(rtm, val)          ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetOffsetTimeArray
# define rtmGetOffsetTimeArray(rtm)    ((rtm)->Timing.offsetTimesArray)
#endif

#ifndef rtmSetOffsetTimeArray
# define rtmSetOffsetTimeArray(rtm, val) ((rtm)->Timing.offsetTimesArray = (val))
#endif

#ifndef rtmGetOffsetTimePtr
# define rtmGetOffsetTimePtr(rtm)      ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
# define rtmSetOffsetTimePtr(rtm, val) ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
# define rtmGetOptions(rtm)            ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
# define rtmSetOptions(rtm, val)       ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ()
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ()
#endif

#ifndef rtmGetPath
# define rtmGetPath(rtm)               ((rtm)->path)
#endif

#ifndef rtmSetPath
# define rtmSetPath(rtm, val)          ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
# define rtmGetPerTaskSampleHits(rtm)  ((rtm)->Timing.RateInteraction)
#endif

#ifndef rtmSetPerTaskSampleHits
# define rtmSetPerTaskSampleHits(rtm, val) ((rtm)->Timing.RateInteraction = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsArray
# define rtmGetPerTaskSampleHitsArray(rtm) ((rtm)->Timing.perTaskSampleHitsArray)
#endif

#ifndef rtmSetPerTaskSampleHitsArray
# define rtmSetPerTaskSampleHitsArray(rtm, val) ((rtm)->Timing.perTaskSampleHitsArray = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
# define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
# define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->ModelData.prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->ModelData.prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
# define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
# define rtmGetRTWGeneratedSFcn(rtm)   ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
# define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmSetRTWLogInfo
# define rtmSetRTWLogInfo(rtm, val)    ((rtm)->rtwLogInfo = (val))
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
# define rtmGetRTWRTModelMethodsInfo(rtm) ()
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
# define rtmSetRTWRTModelMethodsInfo(rtm, val) ()
#endif

#ifndef rtmGetRTWSfcnInfo
# define rtmGetRTWSfcnInfo(rtm)        ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
# define rtmSetRTWSfcnInfo(rtm, val)   ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
# define rtmGetRTWSolverInfo(rtm)      ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
# define rtmSetRTWSolverInfo(rtm, val) ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfoPtr
# define rtmGetRTWSolverInfoPtr(rtm)   ((rtm)->solverInfoPtr)
#endif

#ifndef rtmSetRTWSolverInfoPtr
# define rtmSetRTWSolverInfoPtr(rtm, val) ((rtm)->solverInfoPtr = (val))
#endif

#ifndef rtmGetReservedForXPC
# define rtmGetReservedForXPC(rtm)     ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
# define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->ModelData.dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->ModelData.dwork = (val))
#endif

#ifndef rtmGetSFunctions
# define rtmGetSFunctions(rtm)         ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
# define rtmSetSFunctions(rtm, val)    ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmSetSampleHitArray
# define rtmSetSampleHitArray(rtm, val) ((rtm)->Timing.sampleHitArray = (val))
#endif

#ifndef rtmGetSampleHitPtr
# define rtmGetSampleHitPtr(rtm)       ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
# define rtmSetSampleHitPtr(rtm, val)  ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimeArray
# define rtmGetSampleTimeArray(rtm)    ((rtm)->Timing.sampleTimesArray)
#endif

#ifndef rtmSetSampleTimeArray
# define rtmSetSampleTimeArray(rtm, val) ((rtm)->Timing.sampleTimesArray = (val))
#endif

#ifndef rtmGetSampleTimePtr
# define rtmGetSampleTimePtr(rtm)      ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
# define rtmSetSampleTimePtr(rtm, val) ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDArray
# define rtmGetSampleTimeTaskIDArray(rtm) ((rtm)->Timing.sampleTimeTaskIDArray)
#endif

#ifndef rtmSetSampleTimeTaskIDArray
# define rtmSetSampleTimeTaskIDArray(rtm, val) ((rtm)->Timing.sampleTimeTaskIDArray = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
# define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
# define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSimMode
# define rtmGetSimMode(rtm)            ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
# define rtmSetSimMode(rtm, val)       ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
# define rtmGetSimTimeStep(rtm)        ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
# define rtmSetSimTimeStep(rtm, val)   ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
# define rtmGetStartTime(rtm)          ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
# define rtmSetStartTime(rtm, val)     ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
# define rtmSetStepSize(rtm, val)      ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStopRequestedFlag
# define rtmGetStopRequestedFlag(rtm)  ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
# define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
# define rtmGetTaskCounters(rtm)       ((rtm)->Timing.TaskCounters)
#endif

#ifndef rtmSetTaskCounters
# define rtmSetTaskCounters(rtm, val)  ((rtm)->Timing.TaskCounters = (val))
#endif

#ifndef rtmGetTaskTimeArray
# define rtmGetTaskTimeArray(rtm)      ((rtm)->Timing.tArray)
#endif

#ifndef rtmSetTaskTimeArray
# define rtmSetTaskTimeArray(rtm, val) ((rtm)->Timing.tArray = (val))
#endif

#ifndef rtmGetTimePtr
# define rtmGetTimePtr(rtm)            ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
# define rtmSetTimePtr(rtm, val)       ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
# define rtmGetTimingData(rtm)         ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
# define rtmSetTimingData(rtm, val)    ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->ModelData.inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->ModelData.inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
# define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
# define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->ModelData.outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->ModelData.outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
# define rtmGetZCSignalValues(rtm)     ((rtm)->ModelData.zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
# define rtmSetZCSignalValues(rtm, val) ((rtm)->ModelData.zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
# define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetChecksumVal
# define rtmGetChecksumVal(rtm, idx)   ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
# define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
# define rtmGetDWork(rtm, idx)         ((rtm)->ModelData.dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->ModelData.dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
# define rtmGetOffsetTime(rtm, idx)    ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
# define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
# define rtmGetSFunction(rtm, idx)     ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
# define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
# define rtmGetSampleTime(rtm, idx)    ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
# define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
# define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
# define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTimeList
# define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
# define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
# define rtmIsContinuousTask(rtm, tid) ((tid) <= 1)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmSetFirstInitCond
# define rtmSetFirstInitCond(rtm, val) ((rtm)->Timing.firstInitCondFlag = (val))
#endif

#ifndef rtmIsFirstInitCond
# define rtmIsFirstInitCond(rtm)       ((rtm)->Timing.firstInitCondFlag)
#endif

#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) (((rtm)->Timing.sampleTimeTaskIDPtr[sti] == (tid)))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
# define rtmSetT(rtm, val)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
# define rtmSetTStart(rtm, val)        ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

#ifndef rtmGetTaskTime
# define rtmGetTaskTime(rtm, sti)      (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
# define rtmSetTaskTime(rtm, sti, val) (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifdef rtmGetRTWSolverInfo
#undef rtmGetRTWSolverInfo
#endif

#define rtmGetRTWSolverInfo(rtm)       &((rtm)->solverInfo)

#define SILS_20170421_rtModel          RT_MODEL_SILS_20170421_T

typedef struct {
  real_T c[3];
} B_cross_SILS_20170421_T;

typedef struct {
  real_T c[3];
} B_cross_SILS_20170421_p_T;

typedef struct {
  real_T TrigonometricFunction4;
} B_WhileIteratorSubsystem_SILS_20170421_T;

typedef struct {
  real_T Memory_PreviousInput;
} DW_WhileIteratorSubsystem_SILS_20170421_T;

typedef struct {
  real_T year;
  real_T month;
  real_T day;
  real_T hour;
  real_T minute;
  real_T second;
} B_MATLABFunction_SILS_20170421_T;

typedef struct {
  real_T c[3];
} B_multi_SILS_20170421_T;

typedef struct {
  real_T flag;
} B_MATLABFunction_SILS_20170421_d_T;

typedef struct {
  real_T ang;
} B_MATLABFunction_SILS_20170421_e_T;

typedef struct {
  real_T c[3];
} B_multi_SILS_20170421_e_T;

typedef struct {
  real_T c[3];
} B_multi_SILS_20170421_h_T;

typedef struct {
  real_T rpm;
} B_MATLABFunction_SILS_20170421_i_T;

typedef struct {
  real_T y;
  real_T over_voltage;
  real_T over_current;
} B_MATLABFunction_SILS_20170421_l_T;

typedef struct {
  real_T trq_dir;
} B_MATLABFunction1_SILS_20170421_T;

typedef struct {
  real_T omega_out;
  real_T rot_dir;
} B_MATLABFunction2_SILS_20170421_T;

typedef struct {
  real_T Constant2;
  real_T Constant3;
  real_T Sum2;
  real_T Constant1;
  real_T Constant6;
  real_T Constant2_k;
  real_T Constant3_c;
  real_T Sum2_g;
  real_T Constant1_e;
  real_T Constant1_f;
  real_T Constant2_n;
  real_T Constant3_k;
  real_T Sum2_e;
  real_T Constant1_a;
  real_T Constant2_p;
  real_T Constant2_i;
  real_T Constant3_b;
  real_T Sum2_g3;
  real_T Constant1_fl;
  real_T Constant3_l;
  real_T STT1_b2c_quat[4];
  real_T VectorConcatenate[9];
  real_T JD1;
  real_T JD2[6];
  real_T TOLERANCE;
  real_T GE;
  real_T Constant;
  real_T Constant_j;
  real_T Constant_c;
  real_T Constant_f;
  real_T Constant2_h[3];
  real_T Constant_ju;
  real_T Constant_l;
  real_T Constant_p;
  real_T Constant_g;
  real_T Constant_g0;
  real_T UT1_UTC;
  real_T km2m[3];
  real_T sqrt_l;
  real_T sincos_o1;
  real_T sincos_o2;
  real_T Product3;
  real_T Product4;
  real_T m2km;
  real_T earthradius__km_1;
  real_T STT_FOVsqrt2;
  real_T Constant_i;
  real_T Constant_h;
  real_T Constant_ic;
  real_T Constant_iu;
  real_T Constant_p0;
  real_T noise;
  real_T NSAS1_b2c[9];
  real_T noise1;
  real_T Constant_jn;
  real_T Constant_d;
  real_T Constant1_p[3];
  real_T Constant_k;
  real_T earthradius__km_1_e;
  real_T Constant_ph;
  real_T Constant2_g[2];
  real_T noise_c;
  real_T NSAS2_b2c[9];
  real_T noise1_m;
  real_T Constant_lb;
  real_T Constant_b;
  real_T Constant1_c[3];
  real_T Constant_bo;
  real_T earthradius__km_1_c;
  real_T Constant_im;
  real_T Constant2_nf[2];
  real_T noise_o;
  real_T NSAS3_b2c[9];
  real_T noise1_h;
  real_T Constant_k3;
  real_T Constant_bz;
  real_T Constant1_d[3];
  real_T Constant_fp;
  real_T earthradius__km_1_g;
  real_T Constant_ix;
  real_T Constant2_j[2];
  real_T noise_d;
  real_T NSAS4_b2c[9];
  real_T noise1_b;
  real_T Constant_je;
  real_T Constant_e;
  real_T Constant1_pe[3];
  real_T Constant_g2;
  real_T earthradius__km_1_a;
  real_T Constant_n;
  real_T Constant2_j1[2];
  real_T noise_f;
  real_T NSAS5_b2c[9];
  real_T noise1_f;
  real_T Constant_ji;
  real_T Constant_ep;
  real_T Constant1_ep[3];
  real_T Constant_ky;
  real_T earthradius__km_1_j;
  real_T Constant_jg;
  real_T Constant2_d[2];
  real_T noise_od;
  real_T NSAS6_b2c[9];
  real_T noise1_l;
  real_T Constant_ks;
  real_T Constant_nh;
  real_T Constant1_m[3];
  real_T Constant_en;
  real_T earthradius__km_1_m;
  real_T Constant_hj;
  real_T Constant2_ia[2];
  real_T noise_i[3];
  real_T ReferenceVoltage;
  real_T RandomNumber[3];
  real_T Sum[3];
  real_T sqrt_f;
  real_T sincos_o1_i;
  real_T sincos_o2_h;
  real_T Product3_c;
  real_T Product4_a;
  real_T noise3;
  real_T earth_radius;
  real_T UnitConversion[2];
  real_T VectorConcatenate_k[9];
  real_T Constant_km;
  real_T Constant_kk;
  real_T Constant_o;
  real_T earth_radius_f;
  real_T Gain[3];
  real_T Constant4;
  real_T Constant1_fg[12];
  real_T area1;
  real_T detMatrix;
  real_T detMatrix_l;
  real_T GE1;
  real_T Constant_a;
  real_T Constant1_f4;
  real_T Constant2_kf;
  real_T rem_mag[3];
  real_T IC[4];
  real_T IC1[3];
  real_T Constant2_c[12];
  real_T area;
  real_T iInertiamatrix__kgm2_3x3[9];
  real_T MTQ_c2b[3];
  real_T Product1[3];
  real_T b0degsec[3];
  real_T GYRO_b2c[9];
  real_T nvdegsec[3];
  real_T Sum1[3];
  real_T nudegsec2[3];
  real_T GAS_b2c[9];
  real_T Constant_oi;
  real_T Gamp;
  real_T momentumofinertia;
  real_T Constant_ib;
  real_T Gamp_k;
  real_T momentumofinertia_p;
  real_T Constant_or;
  real_T Gamp_a;
  real_T momentumofinertia_g;
  real_T Constant_l4;
  real_T Gamp_h;
  real_T momentumofinertia_c;
  real_T Clock;
  real_T ZeroOrderHold;
  real_T SFunction_o1;
  real_T SFunction_o2;
  real_T SFunction_o3;
  real_T SFunction_o4;
  real_T SFunction_o5;
  real_T W[3];
  real_T y[12];
  real_T y_e;
  real_T CR;
  real_T Constant_m;
  real_T Constant_hm;
  real_T pSR;
  real_T Constant_lr;
  real_T Constant_kv;
  real_T arm[3];
  real_T d_q[4];
  real_T d_rate[3];
  real_T d_OE[6];
  real_T GE_e;
  real_T Inertiamatrix__kgm2_3x3[9];
  real_T Constant_ki;
  real_T Constant_kl;
  real_T Constant_j4;
  real_T T[3];
  real_T GE_n;
  real_T J2;
  real_T Re;
  real_T a[3];
  real_T Sum4;
  real_T F107;
  real_T aph[7];
  real_T flag[23];
  real_T SFunction_o1_a;
  real_T SFunction_o2_k;
  real_T CD;
  real_T wE[3];
  real_T Constant_kh;
  real_T Constant_bo4;
  real_T Constant_me;
  real_T arm_h[3];
  real_T LST;
  real_T dy;
  real_T rate;
  uint8_T Compare;
  B_MATLABFunction2_SILS_20170421_T sf_MATLABFunction2_m;
  B_MATLABFunction1_SILS_20170421_T sf_MATLABFunction1_n;
  B_MATLABFunction_SILS_20170421_l_T sf_MATLABFunction_f;
  B_MATLABFunction2_SILS_20170421_T sf_MATLABFunction2_c;
  B_MATLABFunction1_SILS_20170421_T sf_MATLABFunction1_o;
  B_MATLABFunction_SILS_20170421_l_T sf_MATLABFunction_c;
  B_MATLABFunction2_SILS_20170421_T sf_MATLABFunction2_l;
  B_MATLABFunction1_SILS_20170421_T sf_MATLABFunction1_g;
  B_MATLABFunction_SILS_20170421_l_T sf_MATLABFunction_p;
  B_MATLABFunction2_SILS_20170421_T sf_MATLABFunction2;
  B_MATLABFunction1_SILS_20170421_T sf_MATLABFunction1;
  B_MATLABFunction_SILS_20170421_l_T sf_MATLABFunction;
  B_MATLABFunction_SILS_20170421_i_T sf_MATLABFunction3;
  B_MATLABFunction_SILS_20170421_i_T sf_MATLABFunction2_d;
  B_MATLABFunction_SILS_20170421_i_T sf_MATLABFunction1_e;
  B_MATLABFunction_SILS_20170421_i_T sf_MATLABFunction_oq;
  B_multi_SILS_20170421_h_T sf_multi_o;
  B_multi_SILS_20170421_h_T sf_multi;
  B_multi_SILS_20170421_e_T sf_multi_i;
  B_multi_SILS_20170421_e_T sf_multi_ag;
  B_multi_SILS_20170421_e_T sf_multi_f;
  B_multi_SILS_20170421_e_T sf_multi_n;
  B_multi_SILS_20170421_e_T sf_multi_e;
  B_multi_SILS_20170421_e_T sf_multi_k;
  B_multi_SILS_20170421_e_T sf_multi_l;
  B_multi_SILS_20170421_e_T sf_multi_h;
  B_multi_SILS_20170421_e_T sf_multi_eq;
  B_multi_SILS_20170421_e_T sf_multi_je;
  B_multi_SILS_20170421_e_T sf_multi_b;
  B_multi_SILS_20170421_h_T sf_multi_ol;
  B_multi_SILS_20170421_e_T sf_multi_j;
  B_multi_SILS_20170421_e_T sf_multi_a;
  B_MATLABFunction_SILS_20170421_e_T sf_MATLABFunction_b;
  B_MATLABFunction_SILS_20170421_e_T sf_MATLABFunction_hq;
  B_MATLABFunction_SILS_20170421_e_T sf_MATLABFunction_fw;
  B_MATLABFunction_SILS_20170421_e_T sf_MATLABFunction_k;
  B_MATLABFunction_SILS_20170421_e_T sf_MATLABFunction_g;
  B_MATLABFunction_SILS_20170421_e_T sf_MATLABFunction_ol;
  B_MATLABFunction_SILS_20170421_e_T sf_MATLABFunction_h;
  B_MATLABFunction_SILS_20170421_T sf_MATLABFunction_j;
  B_WhileIteratorSubsystem_SILS_20170421_T WhileIteratorSubsystem_k;
  B_MATLABFunction_SILS_20170421_d_T sf_MATLABFunction_l;
  B_MATLABFunction_SILS_20170421_d_T sf_MATLABFunction_ov;
  B_multi_SILS_20170421_T sf_multi_g;
  B_multi_SILS_20170421_T sf_multi_p;
  B_multi_SILS_20170421_T sf_multi_m;
  B_cross_SILS_20170421_p_T sf_cross_h;
  B_cross_SILS_20170421_T sf_cross_e3;
  B_MATLABFunction_SILS_20170421_T sf_MATLABFunction_fd;
  B_WhileIteratorSubsystem_SILS_20170421_T WhileIteratorSubsystem;
  B_cross_SILS_20170421_p_T sf_cross_e;
  B_cross_SILS_20170421_T sf_cross_k;
} B_SILS_20170421_T;

typedef struct {
  real_T NextOutput[3];
  real_T UniformRandomNumber_NextOutput;
  real_T NextOutput_f;
  real_T NextOutput_k;
  real_T NextOutput_b;
  real_T NextOutput_i;
  real_T NextOutput_bu;
  real_T NextOutput_c;
  real_T NextOutput_h;
  real_T NextOutput_e;
  real_T NextOutput_o;
  real_T NextOutput_e3;
  real_T NextOutput_d;
  real_T NextOutput_m;
  real_T NextOutput_hm[3];
  real_T NextOutput_n[3];
  real_T noise3_NextOutput;
  real_T Product_DWORK4[9];
  real_T Product_DWORK4_i[9];
  real_T IC_FirstOutputTime;
  real_T IC1_FirstOutputTime;
  real_T NextOutput_h0[3];
  real_T NextOutput_d2[3];
  struct {
    void *LoggedData;
  } ZS_PWORK;

  struct {
    void *LoggedData;
  } rate_PWORK;

  struct {
    void *LoggedData;
  } rate_xyz_PWORK;

  struct {
    void *LoggedData;
  } wheels_PWORK;

  struct {
    void *LoggedData;
  } qd_PWORK;

  uint32_T RandSeed[3];
  uint32_T RandSeed_d;
  uint32_T RandSeed_m;
  uint32_T RandSeed_b;
  uint32_T RandSeed_f;
  uint32_T RandSeed_n;
  uint32_T RandSeed_a;
  uint32_T RandSeed_dx;
  uint32_T RandSeed_n4;
  uint32_T RandSeed_c;
  uint32_T RandSeed_h;
  uint32_T RandSeed_df;
  uint32_T RandSeed_l;
  uint32_T RandSeed_aq;
  uint32_T RandSeed_my[3];
  uint32_T RandSeed_b5[3];
  uint32_T RandSeed_li;
  uint32_T RandSeed_hx[3];
  uint32_T RandSeed_p[3];
  struct {
    int_T IcNeedsLoading;
  } OE_integ_IWORK;

  boolean_T AirDrag_MODE;
  boolean_T GPperturbation_MODE;
  boolean_T GravityGradient_MODE;
  boolean_T RemnantMagnetism_MODE;
  boolean_T SRP_MODE;
  DW_WhileIteratorSubsystem_SILS_20170421_T WhileIteratorSubsystem_k;
  DW_WhileIteratorSubsystem_SILS_20170421_T WhileIteratorSubsystem;
} DW_SILS_20170421_T;

typedef struct {
  real_T TransferFcn1_CSTATE;
  real_T Integrator_CSTATE;
  real_T TransferFcn1_CSTATE_i;
  real_T Integrator_CSTATE_d;
  real_T TransferFcn1_CSTATE_a;
  real_T Integrator_CSTATE_p;
  real_T TransferFcn1_CSTATE_f;
  real_T Integrator_CSTATE_a;
  real_T Integrator_CSTATE_h[4];
  real_T OE_integ_CSTATE[6];
  real_T TransferFcn_CSTATE[2];
  real_T TransferFcn1_CSTATE_h[2];
  real_T TransferFcn2_CSTATE[2];
  real_T TransferFcn_CSTATE_m;
  real_T TransferFcn1_CSTATE_e;
  real_T TransferFcn2_CSTATE_f;
  real_T Integrator1_CSTATE[3];
  real_T TransferFcn_CSTATE_n;
  real_T TransferFcn_CSTATE_k;
  real_T TransferFcn_CSTATE_o;
  real_T Integrator_CSTATE_o[3];
} X_SILS_20170421_T;

typedef struct {
  real_T TransferFcn1_CSTATE;
  real_T Integrator_CSTATE;
  real_T TransferFcn1_CSTATE_i;
  real_T Integrator_CSTATE_d;
  real_T TransferFcn1_CSTATE_a;
  real_T Integrator_CSTATE_p;
  real_T TransferFcn1_CSTATE_f;
  real_T Integrator_CSTATE_a;
  real_T Integrator_CSTATE_h[4];
  real_T OE_integ_CSTATE[6];
  real_T TransferFcn_CSTATE[2];
  real_T TransferFcn1_CSTATE_h[2];
  real_T TransferFcn2_CSTATE[2];
  real_T TransferFcn_CSTATE_m;
  real_T TransferFcn1_CSTATE_e;
  real_T TransferFcn2_CSTATE_f;
  real_T Integrator1_CSTATE[3];
  real_T TransferFcn_CSTATE_n;
  real_T TransferFcn_CSTATE_k;
  real_T TransferFcn_CSTATE_o;
  real_T Integrator_CSTATE_o[3];
} XDot_SILS_20170421_T;

typedef struct {
  boolean_T TransferFcn1_CSTATE;
  boolean_T Integrator_CSTATE;
  boolean_T TransferFcn1_CSTATE_i;
  boolean_T Integrator_CSTATE_d;
  boolean_T TransferFcn1_CSTATE_a;
  boolean_T Integrator_CSTATE_p;
  boolean_T TransferFcn1_CSTATE_f;
  boolean_T Integrator_CSTATE_a;
  boolean_T Integrator_CSTATE_h[4];
  boolean_T OE_integ_CSTATE[6];
  boolean_T TransferFcn_CSTATE[2];
  boolean_T TransferFcn1_CSTATE_h[2];
  boolean_T TransferFcn2_CSTATE[2];
  boolean_T TransferFcn_CSTATE_m;
  boolean_T TransferFcn1_CSTATE_e;
  boolean_T TransferFcn2_CSTATE_f;
  boolean_T Integrator1_CSTATE[3];
  boolean_T TransferFcn_CSTATE_n;
  boolean_T TransferFcn_CSTATE_k;
  boolean_T TransferFcn_CSTATE_o;
  boolean_T Integrator_CSTATE_o[3];
} XDis_SILS_20170421_T;

#ifndef ODE4_INTG
#define ODE4_INTG

typedef struct {
  real_T *y;
  real_T *f[4];
} ODE4_IntgData;

#endif

typedef struct {
  real_T RW1[4];
  real_T RW2[4];
  real_T RW3[4];
  real_T RW4[4];
  real_T MTQ;
} ExtU_SILS_20170421_T;

typedef struct {
  real_T Measurement_RW1[8];
  real_T Measurement_RW2[8];
  real_T Measurement_RW3[8];
  real_T Measurement_RW4[8];
  real_T q_i2b__4[4];
  boolean_T error_flag___1;
  real_T CovMtrx__3x3[9];
  real_T rate_c_degsec_3[3];
  boolean_T NSAS1flg___1;
  real_T NSAS1ange_c__2[2];
  boolean_T NSAS2flg___1;
  real_T NSAS2ange_c__2[2];
  boolean_T NSAS3flg___1;
  real_T NSAS3ange_c__2[2];
  boolean_T NSAS4flg___1;
  real_T NSAS4ange_c__2[2];
  boolean_T NSAS5flg___1;
  real_T NSAS5ange_c__2[2];
  boolean_T NSAS6flg___1;
  real_T NSAS6ange_c__2[2];
  real_T Volt__V_4[4];
  real_T GPSout___12[12];
  real_T sun_b__3[3];
  real_T sun_flag___1;
  real_T mag_b_nT_3[3];
  real_T qi2b__4[4];
  real_T w_b_Rads_3[3];
  real_T moon_b__3[3];
  real_T moon_flag___1;
  real_T earth_b__3[3];
  real_T altitude_e_km_1;
  real_T Julian_Date__day_1;
  real_T SatPosition_e_km_3[3];
} ExtY_SILS_20170421_T;

#define rtB                            SILS_20170421_B
#define BlockIO                        B_SILS_20170421_T
#define rtU                            SILS_20170421_U
#define ExternalInputs                 ExtU_SILS_20170421_T
#define rtX                            SILS_20170421_X
#define ContinuousStates               X_SILS_20170421_T
#define rtXdot                         SILS_20170421_XDot
#define StateDerivatives               XDot_SILS_20170421_T
#define tXdis                          SILS_20170421_XDis
#define StateDisabled                  XDis_SILS_20170421_T
#define rtY                            SILS_20170421_Y
#define ExternalOutputs                ExtY_SILS_20170421_T
#define rtP                            SILS_20170421_P
#define Parameters                     P_SILS_20170421_T
#define rtDWork                        SILS_20170421_DW
#define D_Work                         DW_SILS_20170421_T

struct P_WhileIteratorSubsystem_SILS_20170421_T_ {
  real_T phi_Y0;
  real_T Memory_X0;
  real_T Constant1_Value;
  int8_T Switch_Threshold;
};

struct P_SILS_20170421_T_ {
  real_T ADSW;
  real_T CD;
  real_T CR;
  real_T GAS_Vref;
  real_T GAS_b2c[9];
  real_T GAS_seed1[3];
  real_T GE;
  real_T GGSW;
  real_T GPS_position_seed[3];
  real_T GPS_time_noise;
  real_T GPS_time_seed;
  real_T GPperturbationSW;
  real_T GYRO_b2c[9];
  real_T GYRO_seed1[3];
  real_T GYRO_seed2[3];
  real_T I[9];
  real_T J2;
  real_T MTQ_c2b[3];
  real_T NSAS1_b2c[9];
  real_T NSAS2_b2c[9];
  real_T NSAS3_b2c[9];
  real_T NSAS4_b2c[9];
  real_T NSAS5_b2c[9];
  real_T NSAS6_b2c[9];
  real_T NSAS_ang_limit;
  real_T NSAS_seed1;
  real_T NSAS_seed2;
  real_T NSAS_x_noise;
  real_T NSAS_y_noise;
  real_T RW_Gamp;
  real_T RW_J;
  real_T RW_Rsc;
  real_T RW_kE;
  real_T RW_kT;
  real_T SRPSW;
  real_T STT1_b2c_quat[4];
  real_T STT_AD_prob;
  real_T STT_FOV;
  real_T STT_moon_ang_limit;
  real_T STT_seed1[3];
  real_T STT_sun_ang_limit;
  real_T TOLERANCE;
  real_T UT1_UTC;
  real_T area;
  real_T arm[3];
  real_T earth_radius;
  real_T ele[6];
  real_T jd;
  real_T pSR;
  real_T q_ini[4];
  real_T rem_mag[3];
  real_T rem_magSW;
  real_T three_one_skew_matrix[12];
  real_T wE[3];
  real_T w_ini[3];
  real_T z0_const;
  real_T z0_const_m;
  real_T z0_const_g;
  real_T z0_const_o;
  real_T z0_const_h;
  real_T z0_const_p;
  real_T NormalizeVector_maxzero;
  real_T NormalizeVector_maxzero_l;
  real_T NormalizeVector_maxzero_p;
  real_T NormalizeVector_maxzero_j;
  real_T NormalizeVector_maxzero_pk;
  real_T NormalizeVector_maxzero_m;
  real_T NormalizeVector_maxzero_h;
  real_T NormalizeVector_maxzero_n;
  real_T NormalizeVector_maxzero_lt;
  real_T NormalizeVector_maxzero_b;
  real_T hour2sec_Gain;
  real_T min2sec_Gain;
  real_T F107_Value;
  real_T aph_Value[7];
  real_T flag_Value[23];
  real_T gcm3kgm3_Gain;
  real_T Constant_Value;
  real_T Gain_Gain;
  real_T Gain1_Gain;
  real_T Gain2_Gain;
  real_T Constant_Value_k;
  real_T Gain_Gain_d;
  real_T Gain1_Gain_e;
  real_T Gain2_Gain_l;
  real_T Constant_Value_a;
  real_T Gain_Gain_k;
  real_T Gain1_Gain_o;
  real_T Gain2_Gain_e;
  real_T GPperturbation_RSW_kms2_3_Y0[3];
  real_T deg2rad_Gain;
  real_T GG_b_Nm_3_Y0[3];
  real_T Constant_Value_p;
  real_T Gain2_Gain_n;
  real_T Gain_Gain_e;
  real_T Gain1_Gain_o0;
  real_T Gain_Gain_c;
  real_T Constant_Value_b;
  real_T Gain2_Gain_j;
  real_T Gain1_Gain_k;
  real_T Gain_Gain_l;
  real_T Gain1_Gain_p;
  real_T Constant_Value_g;
  real_T Gain2_Gain_na;
  real_T remmag_b_Nm_3_Y0[3];
  real_T nT2T_Gain;
  real_T SRP_b_Nm_3_Y0[3];
  real_T Constant_Value_n;
  real_T Constant_Value_c;
  real_T Gain_Gain_kp;
  real_T Gain1_Gain_k3;
  real_T Gain2_Gain_p;
  real_T Constant_Value_o;
  real_T Gain_Gain_b;
  real_T Gain1_Gain_g;
  real_T Gain2_Gain_g;
  real_T Constant_Value_d;
  real_T Gain_Gain_b0;
  real_T Gain1_Gain_i;
  real_T Gain2_Gain_p5;
  real_T rad2deg_Gain;
  real_T rad2deg_Gain_l;
  real_T rad2deg_Gain_a;
  real_T rad2deg_Gain_o;
  real_T rad2deg_Gain_c;
  real_T rad2deg_Gain_n;
  real_T Constant2_Value;
  real_T Constant3_Value;
  real_T Switch2_Threshold;
  real_T TransferFcn1_A;
  real_T TransferFcn1_C;
  real_T Integrator_IC;
  real_T motor_D;
  real_T Constant1_Value;
  real_T Switch1_Threshold;
  real_T rad2rpm_Gain;
  real_T Constant6_Value;
  real_T Constant2_Value_p;
  real_T Constant3_Value_d;
  real_T Switch2_Threshold_h;
  real_T TransferFcn1_A_i;
  real_T TransferFcn1_C_a;
  real_T Integrator_IC_a;
  real_T motor_D_e;
  real_T Constant1_Value_o;
  real_T Switch1_Threshold_a;
  real_T rad2rpm_Gain_e;
  real_T Constant1_Value_i;
  real_T Constant2_Value_l;
  real_T Constant3_Value_p;
  real_T Switch2_Threshold_f;
  real_T TransferFcn1_A_il;
  real_T TransferFcn1_C_e;
  real_T Integrator_IC_h;
  real_T motor_D_p;
  real_T Constant1_Value_j;
  real_T Switch1_Threshold_l;
  real_T rad2rpm_Gain_n;
  real_T Constant2_Value_f;
  real_T Constant2_Value_o;
  real_T Constant3_Value_i;
  real_T Switch2_Threshold_fn;
  real_T TransferFcn1_A_b;
  real_T TransferFcn1_C_ex;
  real_T Integrator_IC_l;
  real_T motor_D_n;
  real_T Constant1_Value_b;
  real_T Switch1_Threshold_n;
  real_T rad2rpm_Gain_p;
  real_T Constant3_Value_m;
  real_T noise1_Mean[3];
  real_T noise1_StdDev[3];
  real_T UniformRandomNumber_Minimum;
  real_T UniformRandomNumber_Maximum;
  real_T UniformRandomNumber_Seed;
  real_T Gain_Gain_o;
  real_T Gain_Gain_j;
  real_T Gain_Gain_ji;
  real_T Gain_Gain_i;
  real_T Gain_Gain_g;
  real_T Gain_Gain_gd;
  real_T sec_per_day_Gain;
  real_T Constant_Value_kx;
  real_T Constant_Value_cz;
  real_T Gain2_Gain_c;
  real_T Gain_Gain_l1;
  real_T Gain1_Gain_b;
  real_T Gain_Gain_id;
  real_T Constant_Value_h;
  real_T Gain2_Gain_k;
  real_T Gain1_Gain_bv;
  real_T Gain_Gain_p;
  real_T Gain1_Gain_j;
  real_T Constant_Value_bu;
  real_T Gain2_Gain_d;
  real_T Constant2_Value_g[3];
  real_T Gain_Gain_c5;
  real_T Constant_Value_gg;
  real_T Constant_Value_kb;
  real_T Gain2_Gain_f;
  real_T Gain_Gain_f;
  real_T Gain1_Gain_c;
  real_T Gain_Gain_cu;
  real_T Constant_Value_hg;
  real_T Gain2_Gain_o;
  real_T Gain1_Gain_p0;
  real_T Gain_Gain_m;
  real_T Gain1_Gain_f;
  real_T Constant_Value_j;
  real_T Gain2_Gain_ek;
  real_T km2m_Gain;
  real_T Constant_Value_oa;
  real_T Constant_Value_dk;
  real_T Constant1_Value_n;
  real_T Constant_Value_jt;
  real_T Constant_Value_m;
  real_T Constant1_Value_nu;
  real_T f_Value;
  real_T m2km_Gain;
  real_T Constant_Value_kg;
  real_T Constant_Value_ck;
  real_T Gain2_Gain_b;
  real_T Gain_Gain_p0;
  real_T Gain1_Gain_l;
  real_T Gain_Gain_cd;
  real_T Constant_Value_jd;
  real_T Gain2_Gain_i;
  real_T Gain1_Gain_m;
  real_T Gain_Gain_gn;
  real_T Gain1_Gain_a;
  real_T Constant_Value_my;
  real_T Gain2_Gain_a;
  real_T Constant_Value_i[3];
  real_T TransferFcn_A[2];
  real_T TransferFcn_C[2];
  real_T TransferFcn1_A_if[2];
  real_T TransferFcn1_C_d[2];
  real_T TransferFcn2_A[2];
  real_T TransferFcn2_C[2];
  real_T noise_Mean;
  real_T noise1_Mean_g;
  real_T Constant_Value_hm;
  real_T Constant_Value_l;
  real_T Constant1_Value_a[3];
  real_T Constant2_Value_ge[2];
  real_T noise_Mean_i;
  real_T noise1_Mean_d;
  real_T Constant_Value_hu;
  real_T Constant_Value_m2;
  real_T Constant1_Value_e[3];
  real_T Constant2_Value_c[2];
  real_T noise_Mean_f;
  real_T noise1_Mean_m;
  real_T Constant_Value_nd;
  real_T Constant_Value_iq;
  real_T Constant1_Value_l[3];
  real_T Constant2_Value_gn[2];
  real_T noise_Mean_g;
  real_T noise1_Mean_k;
  real_T Constant_Value_gh;
  real_T Constant_Value_f;
  real_T Constant1_Value_j0[3];
  real_T Constant2_Value_a[2];
  real_T noise_Mean_fj;
  real_T noise1_Mean_j;
  real_T Constant_Value_e;
  real_T Constant_Value_fn;
  real_T Constant1_Value_g[3];
  real_T Constant2_Value_k[2];
  real_T noise_Mean_h;
  real_T noise1_Mean_m2;
  real_T Constant_Value_ib;
  real_T Constant_Value_k3;
  real_T Constant1_Value_nc[3];
  real_T Constant2_Value_n[2];
  real_T noise_Mean_m[3];
  real_T noise_StdDev[3];
  real_T TransferFcn_A_c;
  real_T TransferFcn_C_c;
  real_T TransferFcn1_A_l;
  real_T TransferFcn1_C_b;
  real_T TransferFcn2_A_p;
  real_T TransferFcn2_C_f;
  real_T km2m_Gain_c;
  real_T RandomNumber_Mean[3];
  real_T RandomNumber_StdDev[3];
  real_T Constant_Value_d3;
  real_T Constant_Value_kj;
  real_T Constant1_Value_h;
  real_T Constant_Value_a0;
  real_T Constant_Value_k4;
  real_T UnitConversion_Gain;
  real_T Constant1_Value_b5;
  real_T f_Value_l;
  real_T noise3_Minimum;
  real_T UnitConversion_Gain_b;
  real_T UnitConversion_Gain_c;
  real_T Constant_Value_ns;
  real_T Constant_Value_am;
  real_T Gain2_Gain_m;
  real_T Gain_Gain_ky;
  real_T Gain1_Gain_jd;
  real_T Gain_Gain_a;
  real_T Constant_Value_mq;
  real_T Gain2_Gain_bo;
  real_T Gain1_Gain_h;
  real_T Gain_Gain_du;
  real_T Gain1_Gain_cj;
  real_T Constant_Value_kc;
  real_T Gain2_Gain_cy;
  real_T Gain_Gain_it;
  real_T rpm2rad_Gain;
  real_T rpm2rad1_Gain;
  real_T rpm2rad2_Gain;
  real_T rpm2rad3_Gain;
  real_T Constant_Value_ic;
  real_T Constant1_Value_oq;
  real_T Constant2_Value_e;
  real_T IC_Value[4];
  real_T IC1_Value[3];
  real_T losstorquepropotionto_Gain;
  real_T losstorquepropotionto_Gain_h;
  real_T losstorquepropotionto_Gain_f;
  real_T losstorquepropotionto_Gain_k;
  real_T reactiontorque_Gain;
  real_T TransferFcn_A_a;
  real_T TransferFcn_C_k;
  real_T TransferFcn_A_g;
  real_T TransferFcn_C_n;
  real_T TransferFcn_A_ax;
  real_T TransferFcn_C_c3;
  real_T nT_2_T_Gain;
  real_T Integrator_IC_f;
  real_T b0degsec_Value[3];
  real_T rad2deg_Gain_i;
  real_T nvdegsec_Mean[3];
  real_T nvdegsec_StdDev[3];
  real_T nudegsec2_Mean[3];
  real_T nudegsec2_StdDev[3];
  real_T Constant_Value_g3;
  real_T Switch_Threshold;
  real_T Constant_Value_ov;
  real_T Switch_Threshold_a;
  real_T Constant_Value_br;
  real_T Switch_Threshold_e;
  real_T Constant_Value_ki;
  real_T Switch_Threshold_m;
  P_WhileIteratorSubsystem_SILS_20170421_T WhileIteratorSubsystem_k;
  P_WhileIteratorSubsystem_SILS_20170421_T WhileIteratorSubsystem;
};

struct tag_RTM_SILS_20170421_T {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWLogInfo *rtwLogInfo;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[3];
    SimStruct childSFunctions[2];
    SimStruct *childSFunctionPtrs[2];
    struct _ssBlkInfo2 blkInfo2[2];
    struct _ssSFcnModelMethods2 methods2[2];
    struct _ssSFcnModelMethods3 methods3[2];
    struct _ssStatesInfo2 statesInfo2[2];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[11];
      int_T iDims9[2];
      int_T iDims10[2];
      struct _ssPortOutputs outputPortInfo[2];
    } Sfcn0;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssPortOutputs outputPortInfo[5];
    } Sfcn1;
  } NonInlinedSFcns;

  struct {
    void *blockIO;
    const void *constBlockIO;
    void *defaultParam;
    ZCSigState *prevZCSigState;
    real_T *contStates;
    real_T *derivs;
    void *zcSignalValues;
    void *inputs;
    void *outputs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[36];
    real_T odeF[4][36];
    ODE4_IntgData intgData;
    void *dwork;
  } ModelData;

  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T stepSize1;
    uint32_T clockTick2;
    uint32_T clockTickH2;
    time_T stepSize2;
    boolean_T firstInitCondFlag;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    struct {
      boolean_T TID0_2;
    } RateInteraction;

    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[3];
    time_T offsetTimesArray[3];
    int_T sampleTimeTaskIDArray[3];
    int_T sampleHitArray[3];
    int_T perTaskSampleHitsArray[9];
    time_T tArray[3];
  } Timing;
};

extern P_SILS_20170421_T SILS_20170421_P;
extern B_SILS_20170421_T SILS_20170421_B;
extern X_SILS_20170421_T SILS_20170421_X;
extern DW_SILS_20170421_T SILS_20170421_DW;
extern ExtU_SILS_20170421_T SILS_20170421_U;
extern ExtY_SILS_20170421_T SILS_20170421_Y;
extern time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
  ;
extern void SILS_20170421_initialize(void);
extern void SILS_20170421_output0(void);
extern void SILS_20170421_update0(void);
extern void SILS_20170421_output(int_T tid);
extern void SILS_20170421_update(int_T tid);
extern void SILS_20170421_terminate(void);
extern SILS_20170421_rtModel *SILS_20170421(void);
extern void MdlInitializeSizes(void);
extern void MdlInitializeSampleTimes(void);
extern void MdlInitialize(void);
extern void MdlStart(void);
extern void MdlOutputs(int_T tid);
extern void MdlUpdate(int_T tid);
extern void MdlTerminate(void);
extern RT_MODEL_SILS_20170421_T *const SILS_20170421_M;

#endif

#if !defined(NI_HEADER_SILS_20170421_h_)
#define NI_HEADER_SILS_20170421_h_
#ifdef NI_ROOTMODEL_SILS_20170421

#include "ni_pglobals.h"
#ifndef NI_VERISTAND_MODELDATAFILE
#ifdef NI_VERISTAND_MAINMODELFILE

int READSIDE = 0;
int tid = 0;

#ifdef MULTITASKING

P_SILS_20170421_T rtParameter[NUMST+!TID01EQ];
P_SILS_20170421_T *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[2], &rtParameter[2] },
};

#else

P_SILS_20170421_T rtParameter[2];

#endif

#else

extern int READSIDE;

#ifdef MULTITASKING

extern int tid;
extern P_SILS_20170421_T* param_lookup[NUMST][2];

#else

extern P_SILS_20170421_T rtParameter[];

#endif
#endif

#define _NI_DEFINE_PARAMS_DBL_BUFFER_
#include "ni_pglobals.h"
#endif
#endif
#endif
