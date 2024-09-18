#include "ni_modelframework.h"
#include <float.h>
#include "tmwtypes.h"
#include "rtmodel.h"
#include "rt_sim.h"
#include "rt_logging.h"
#ifdef UseMMIDataLogging
#include "rt_logging_mmi.h"
#endif

#include "rt_nonfinite.h"
#include "ni_modelframework_ex.h"

#ifndef RT
#error "must define RT"
#endif

#ifndef MODEL
#error "must define MODEL"
#endif

#ifndef NUMST
#error "must define number of sample times, NUMST"
#endif

#ifndef NCSTATES
#error "must define NCSTATES"
#endif

#ifndef TRUE
#define FALSE                          (0)
#define TRUE                           (1)
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE                   1
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS                   0
#endif

#ifndef SAVEFILE
#define MATFILE2(file)                 #file ".mat"
#define MATFILE1(file)                 MATFILE2(file)
#define MATFILE                        MATFILE1(MODEL)
#else
#define MATFILE                        QUOTE(SAVEFILE)
#endif

#define RUN_FOREVER                    -1.0
#define EXPAND_CONCAT(name1,name2)     name1 ## name2
#define CONCAT(name1,name2)            EXPAND_CONCAT(name1,name2)
#define RT_MODEL                       CONCAT(MODEL,_rtModel)
#define QUOTE1(name)                   #name
#define QUOTE(name)                    QUOTE1(name)

NI_Version NIVS_APIversion DataSection(".NIVS.APIVersion") = { NIMF_VER_MAJOR,
  NIMF_VER_MINOR, NIMF_VER_FIX, NIMF_VER_BUILD };

#ifdef VXWORKS

HANDLE CreateSemaphore(void* lpSemaphoreAttributes, int lInitialCount, int
  lMaximumCount, char* lpName)
{
  UNUSED_PARAMETER(lpSemaphoreAttributes);
  UNUSED_PARAMETER(lInitialCount);
  UNUSED_PARAMETER(lMaximumCount);
  UNUSED_PARAMETER(lpName);
  return semBCreate(SEM_Q_PRIORITY, SEM_FULL);
}

void WaitForSingleObject(HANDLE hHandle, int dwMilliseconds)
{
  int ticks = INFINITE;
  if (dwMilliseconds != INFINITE) {
    ticks = (CLOCKS_PER_SEC * (dwMilliseconds/1000)) + 1;
  }

  semTake(hHandle, ticks);
}

void ReleaseSemaphore(HANDLE hSemaphore, int lReleaseCount, void
                      * lpPreviousCount)
{
  UNUSED_PARAMETER(lReleaseCount);
  UNUSED_PARAMETER(lpPreviousCount);
  semGive(hSemaphore);
}

void CloseHandle(HANDLE hObject)
{
  semFlush(hObject);
  semDelete(hObject);
}

void InitializeCriticalSection(CRITICAL_SECTION *CriticalSection)
{
  *CriticalSection = CreateSemaphore(NULL, 1, 1, NULL);
}

void EnterCriticalSection(CRITICAL_SECTION *CriticalSection)
{
  semTake(*CriticalSection, WAIT_FOREVER);
}

void LeaveCriticalSection(CRITICAL_SECTION *CriticalSection)
{
  semGive(*CriticalSection);
}

void DeleteCriticalSection(CRITICAL_SECTION *CriticalSection)
{
  semFlush(*CriticalSection);
  semDelete(*CriticalSection);
}

boolean_T _isnan(real_T value)
{
  return isNan(value);
}

#elif kNIOSLinux

HANDLE CreateSemaphore(void* lpSemaphoreAttributes, int lInitialCount, int
  lMaximumCount, char* lpName)
{
  UNUSED_PARAMETER(lpSemaphoreAttributes);
  UNUSED_PARAMETER(lpName);
  UNUSED_PARAMETER(lMaximumCount);
  HANDLE sem = (HANDLE) malloc(sizeof(sem_t));
  int err = sem_init(sem, 0, lInitialCount);
  if (err == 0) {
    return sem;
  } else {
    free(sem);
    return NULL;
  }
}

void WaitForSingleObject(HANDLE hHandle, int dwMilliseconds)
{
  if (dwMilliseconds == INFINITE) {
    sem_wait(hHandle);
  } else {
    struct timespec ts;
    ts.tv_nsec = dwMilliseconds * 10^6;
    sem_timedwait(hHandle, &ts);
  }
}

void ReleaseSemaphore(HANDLE hSemaphore, int lReleaseCount, void
                      * lpPreviousCount)
{
  UNUSED_PARAMETER(lReleaseCount);
  UNUSED_PARAMETER(lpPreviousCount);
  sem_post(hSemaphore);
}

void CloseHandle(HANDLE hObject)
{
  sem_destroy(hObject);
  free(hObject);
}

void InitializeCriticalSection(CRITICAL_SECTION *CriticalSection)
{
  *CriticalSection = CreateSemaphore(NULL, 1, 1, NULL);
}

void EnterCriticalSection(CRITICAL_SECTION *CriticalSection)
{
  sem_wait(*CriticalSection);
}

void LeaveCriticalSection(CRITICAL_SECTION *CriticalSection)
{
  sem_post(*CriticalSection);
}

void DeleteCriticalSection(CRITICAL_SECTION *CriticalSection)
{
  CloseHandle(*CriticalSection);
}

boolean_T _isnan(real_T value)
{
  return isnan(value);
}

#endif

extern RT_MODEL *MODEL(void);
extern void MdlInitializeSizes(void);
extern void MdlInitializeSampleTimes(void);
extern void MdlStart(void);
extern void MdlOutputs(int_T tid);
extern void MdlUpdate(int_T tid);
extern void MdlTerminate(void);

#if NCSTATES > 0

extern void rt_ODECreateIntegrationData(RTWSolverInfo *si);
extern void rt_ODEUpdateContinuousStates(RTWSolverInfo *si);

#define rt_CreateIntegrationData(S)    rt_ODECreateIntegrationData(rtmGetRTWSolverInfo(S));
#define rt_UpdateContinuousStates(S)   rt_ODEUpdateContinuousStates(rtmGetRTWSolverInfo(S));
#else
#define rt_CreateIntegrationData(S)    rtsiSetSolverName(rtmGetRTWSolverInfo(S),"FixedStepDiscrete");
#define rt_UpdateContinuousStates(S)   rtmSetT(S, rtsiGetSolverStopTime(rtmGetRTWSolverInfo(S)));
#endif

static struct {
  int_T stopExecutionFlag;
  int_T isrOverrun;
  int_T overrunFlags[NUMST];
  int_T overrunCount[NUMST];
  int_T haltonOverrun;
  CRITICAL_SECTION taskCriticalSection;
  const char_T *errmsg;
  boolean_T isFirstTimeStep;
  boolean_T isModelStarted;
} SITglobals;

_SITexportglobals SITexportglobals;
RT_MODEL *S = NULL;
void SetExternalInputs(double *data, int_T* sampleHit);
void SetExternalOutputs(double *data, int_T* sampleHit);
int32_t NumInputPorts(void);
int32_t NumOutputPorts(void);
int32_t NI_InitParamDoubleBuf(void);
int32_t NI_InitializeParamStruct(void);
int32_t NI_InitExternalOutputs(void);
void SetSITErrorMessage(const char *ErrMsg, int32_t isError)
{
  if (isError && (SITglobals.stopExecutionFlag == 0)) {
    SITglobals.stopExecutionFlag = 1;
    SITglobals.errmsg = NULL;
  }

  if (SITglobals.errmsg == NULL) {
    SITglobals.errmsg = ErrMsg;
  }

  if (SITglobals.errmsg != NULL) {
    if (isError) {
      (void)fprintf(stderr,"VeriStand Error: %s\n", SITglobals.errmsg);
    } else {
      (void)fprintf(stderr,"VeriStand Warning: %s\n", SITglobals.errmsg);
    }
  }
}

#ifndef MULTITASKING
#define FIRST_TID                      0

static int32_t rt_OneStep(RT_MODEL *S, double *inData)
{
  real_T tnext = 0;
  int_T *sampleHit = rtmGetSampleHitPtr(S);
  if (SITglobals.isrOverrun++) {
    SITglobals.stopExecutionFlag = 1;
    return -1;
  }

  if (rtmGetErrorStatus(S) != NULL) {
    SITglobals.stopExecutionFlag = 1;
    return -1;
  }

  SetExternalInputs(inData, sampleHit);
  tnext = rt_SimGetNextSampleHit();
  rtsiSetSolverStopTime(rtmGetRTWSolverInfo(S),tnext);
  MdlOutputs(0);
  SITglobals.isrOverrun--;
  return NI_OK;
}

#else
#if TID01EQ == 1
#define FIRST_TID                      1
#else
#define FIRST_TID                      0
#endif

static int32_t SCHEDULER(RT_MODEL *S)
{
  int_T i = 0;
  real_T tnext = 0;
  int_T *sampleHit = rtmGetSampleHitPtr(S);
  if (SITglobals.isrOverrun++) {
    SITglobals.stopExecutionFlag = 1;
    return -1;
  }

  if (rtmGetErrorStatus(S) != NULL) {
    SITglobals.stopExecutionFlag = 1;
    return -1;
  }

  tnext = rt_SimUpdateDiscreteEvents(rtmGetNumSampleTimes(S),
    rtmGetTimingData(S),
    rtmGetSampleHitPtr(S),
    rtmGetPerTaskSampleHitsPtr(S));
  rtsiSetSolverStopTime(rtmGetRTWSolverInfo(S),tnext);
  for (i=1+FIRST_TID; i<NUMST; i++) {
    if (sampleHit[i]) {
      if (SITglobals.overrunFlags[i] > 0) {
        printf("overrun in task %d: %d\n", i, SITglobals.overrunFlags[i]);
        SITglobals.overrunCount[i]++;
        if (SITglobals.haltonOverrun) {
          SetSITErrorMessage("Task Overran", 1);
        }
      } else {
        SITglobals.overrunFlags[i] = 1;
      }
    }
  }

  SITglobals.isrOverrun--;
  return NI_OK;
}

DLL_EXPORT int32_t NIRT_ScheduleTasks2(int32_t *dispatchtasks, char
  *isFirstSchedule)
{

#ifndef MULTITASKING

  SetSITErrorMessage("Called ScheduleTasks2() for a single-rate model.  Use Schedule() instead.",
                     1);
  return NI_ERROR;

#else

  int32_t tid = 0;
  int32_t retVal = 0;
  int_T *sampleHits = rtmGetSampleHitPtr(S);
  retVal = SCHEDULER(S);
  if (retVal == 0) {
    for (tid=0; tid<NUMST; tid++) {
      dispatchtasks[tid] = sampleHits[tid + TID01EQ];
    }
  }

  *isFirstSchedule = SITglobals.isFirstTimeStep;
  return retVal;

#endif

}

static int32_t rt_OneStepTask(RT_MODEL *S, int32_t tid, double *inData)
{
  if (tid == FIRST_TID) {
    if (SITglobals.stopExecutionFlag) {
      return -1;
    }

    if ((inData == NULL) && (NumInputPorts() > 0)) {
      SetSITErrorMessage("External Input data array is NULL for base rate task",
                         1);
      return -1;
    }

    SetExternalInputs(inData, rtmGetSampleHitPtr(S));
    MdlOutputs(FIRST_TID);
  } else {
    if ((tid < (FIRST_TID+1)) || (tid >= NUMST) ) {
      return -1;
    }

    MdlOutputs(tid);
    MdlUpdate(tid);
    rt_SimUpdateDiscreteTaskTime(rtmGetTPtr(S), rtmGetTimingData(S),tid);
    SITglobals.overrunFlags[tid]--;
  }

  return NI_OK;
}

#endif

DLL_EXPORT int32_t NIRT_GetModelFrameworkVersion(uint32_t* major, uint32_t*
  minor, uint32_t* fix, uint32_t* build)
{
  *major = NIVS_APIversion.major;
  *minor = NIVS_APIversion.minor;
  *fix = NIVS_APIversion.fix;
  *build = NIVS_APIversion.build;
  return NI_OK;
}

DLL_EXPORT int32_t NIRT_InitializeModel (double finaltime, double *outTimeStep,
  int32_t *outNumInports, int32_t *outNumOutports, int32_t *numTasks)
{
  const char *status = NULL;
  (void)memset(&SITglobals, 0, sizeof(SITglobals));
  (void)memset(&SITexportglobals, 0, sizeof(SITexportglobals));
  rt_InitInfAndNaN(sizeof(real_T));
  NI_InitializeParamStruct();
  S = MODEL();
  if (rtmGetErrorStatus(S) != NULL) {
    (void)fprintf(stderr,"Error during model registration: %s\n",
                  rtmGetErrorStatus(S));
    return 5;
  }

  if ((finaltime >= 0.0) || (finaltime == RUN_FOREVER)) {
    rtmSetTFinal(S,finaltime);
  }

  MdlInitializeSizes();
  MdlInitializeSampleTimes();
  status = rt_SimInitTimingEngine(rtmGetNumSampleTimes(S),
    rtmGetStepSize(S),
    rtmGetSampleTimePtr(S),
    rtmGetOffsetTimePtr(S),
    rtmGetSampleHitPtr(S),
    rtmGetSampleTimeTaskIDPtr(S),
    rtmGetTStart(S),
    &rtmGetSimTimeStep(S),
    &rtmGetTimingData(S));
  if (status != NULL) {
    (void)fprintf(stderr, "Failed to initialize sample time engine: %s\n",
                  status);
    exit(EXIT_FAILURE);
  }

  rt_CreateIntegrationData(S);
  SITglobals.errmsg = rt_StartDataLogging(rtmGetRTWLogInfo(S),
    rtmGetTFinal(S),
    rtmGetStepSize(S),
    &rtmGetErrorStatus(S));
  if (SITglobals.errmsg != NULL) {
    (void)fprintf(stderr,"Error starting data logging: %s\n",SITglobals.errmsg);
    return(3);
  }

  NI_InitParamDoubleBuf();
  if (rtmGetErrorStatus(S) != NULL) {
    SITglobals.stopExecutionFlag = 1;
  }

  NIRT_GetModelSpec(NULL, 0, outTimeStep, outNumInports, outNumOutports,
                    numTasks);
  InitializeCriticalSection(&SITglobals.taskCriticalSection);
  SITexportglobals.flipCriticalSection = CreateSemaphore(NULL, 1, 1, NULL);
  if (SITexportglobals.flipCriticalSection == NULL) {
    SetSITErrorMessage("Failed to create semaphore.", 1);
  }

  return NI_OK;
}

DLL_EXPORT int32_t NIRT_ModelStart(void)
{
  MdlStart();
  NI_InitExternalOutputs();

#if defined(MULTITASKING)

  {
    SITglobals.isFirstTimeStep = TRUE;
    rt_SimUpdateDiscreteEvents(rtmGetNumSampleTimes(S),
      rtmGetTimingData(S),
      rtmGetSampleHitPtr(S),
      rtmGetPerTaskSampleHitsPtr(S));
  }

#endif

  SITglobals.isModelStarted = true;
  return NI_OK;
}

DLL_EXPORT int32_t NIRT_ModelUpdate(void)
{
  if (SITexportglobals.inCriticalSection) {
    SITexportglobals.inCriticalSection--;
    MdlUpdate(FIRST_TID);

#if defined(MULTITASKING)

    if (rtmGetSampleTime(S,0) == CONTINUOUS_SAMPLE_TIME) {
      rt_UpdateContinuousStates(S);
    } else {
      rt_SimUpdateDiscreteTaskTime(rtmGetTPtr(S), rtmGetTimingData(S), 0);
    }

#if FIRST_TID == 1

    rt_SimUpdateDiscreteTaskTime(rtmGetTPtr(S), rtmGetTimingData(S),1);

#endif

#else

    rt_SimUpdateDiscreteTaskSampleHits(rtmGetNumSampleTimes(S), rtmGetTimingData
                                       (S), rtmGetSampleHitPtr(S), rtmGetTPtr(S));
    if (rtmGetSampleTime(S,0) == CONTINUOUS_SAMPLE_TIME) {
      rt_UpdateContinuousStates(S);
    }

#endif

    ReleaseSemaphore(SITexportglobals.flipCriticalSection,1,NULL);
  }

  return SITexportglobals.inCriticalSection;
}

DLL_EXPORT int32_t NIRT_StepBaseTask(double *inData, double *outTime, double
  *outData)
{

#ifndef MULTITASKING

  SetSITErrorMessage("Called StepBaseTask() for a single-rate model.  Use Schedule() instead.",
                     1);
  return NI_ERROR;

#else

  int32_t i = 0;
  int32_t lastStep = 1;
  int_T *sampleHits = rtmGetSampleHitPtr(S);
  if (outTime != NULL) {
    *outTime = rtmGetT(S);
  }

  WaitForSingleObject(SITexportglobals.flipCriticalSection, INFINITE);
  if (SITexportglobals.inCriticalSection > 0) {
    SetSITErrorMessage("Each call to StepBaseTask() MUST be followed by a call to ModelUpdate() before StepBaseTask() is called again.",
                       1);
    ReleaseSemaphore(SITexportglobals.flipCriticalSection, 1, NULL);
    return 1;
  }

# ifdef NI_SIT_PARAMS

  for (i = 1; i < NUMST - TID01EQ; i++) {
    if (sampleHits[i + TID01EQ] && (SITexportglobals.copyTaskBitfield & (1 << i)))
    {
      memcpy(param_lookup[i+TID01EQ][1-READSIDE], param_lookup[0][READSIDE],
             sizeof(NI_PARAM_TYPEDEF));
      SITexportglobals.copyTaskBitfield &= ~(1 << i);
    }
  }

# endif

  if (!SITglobals.stopExecutionFlag) {
    if ((rtmGetTFinal(S) == RUN_FOREVER) || ((rtmGetTFinal(S) - rtmGetT(S)) >
         (rtmGetT(S) *DBL_EPSILON))) {
      rt_OneStepTask(S,FIRST_TID, inData);
      lastStep = rtmGetStopRequested(S);
    } else if (!rtmGetStopRequested(S)) {
      rt_OneStepTask(S,FIRST_TID, inData);
    }

    SetExternalOutputs(outData, sampleHits);
  }

  SITexportglobals.inCriticalSection++;
  SITglobals.isFirstTimeStep = FALSE;
  return SITglobals.stopExecutionFlag | lastStep;

#endif

}

DLL_EXPORT int32_t NIRT_Schedule(double *inData, double *outData, double
  *outTime, int32_t *dispatchtasks)
{

#ifdef MULTITASKING

  SetSITErrorMessage("Called Schedule() for a multi-rate model.  Use ScheduleTasks2() instead.",
                     1);
  return NI_ERROR;

#else

  int32_t lastStep = 1;
  if (outTime != NULL) {
    *outTime = rtmGetT(S);
  }

  WaitForSingleObject(SITexportglobals.flipCriticalSection, INFINITE);
  if (SITexportglobals.inCriticalSection > 0) {
    SetSITErrorMessage("Each call to Schedule() MUST be followed by a call to ModelUpdate() before Schedule() is called again.",
                       1);
    ReleaseSemaphore(SITexportglobals.flipCriticalSection, 1, NULL);
    return 1;
  }

  if (!SITglobals.stopExecutionFlag && ((rtmGetTFinal(S) == RUN_FOREVER) ||
       ((rtmGetTFinal(S) - rtmGetT(S)) > (rtmGetT(S) * DBL_EPSILON)))) {
    rt_OneStep(S, inData);
    lastStep = rtmGetStopRequested(S);
  } else if (!SITglobals.stopExecutionFlag && !rtmGetStopRequested(S)) {
    rt_OneStep(S, inData);
  }

  SetExternalOutputs(outData, rtmGetSampleHitPtr(S));
  SITexportglobals.inCriticalSection++;
  return lastStep;

#endif

}

DLL_EXPORT int32_t NIRT_TakeOneStep(double *inData, double *outData, double
  *outTime)
{
  return NIRT_Schedule(inData, outData, outTime, NULL);
}

DLL_EXPORT int32_t NIRT_TaskTakeOneStep(int32_t tid)
{

#if defined(MULTITASKING)

  return rt_OneStepTask(S,tid, NULL);

#else

  return NI_OK;

#endif

}

DLL_EXPORT int32_t NIRT_FinalizeModel(void)
{
  rt_StopDataLogging(MATFILE,rtmGetRTWLogInfo(S));
  if (SITglobals.errmsg != NULL) {
    (void)fprintf(stderr,"%s\n",SITglobals.errmsg);
    return NI_ERROR;
  }

  if (rtmGetErrorStatus(S) != NULL) {
    (void)fprintf(stderr,"%s\n", rtmGetErrorStatus(S));
    return NI_ERROR;
  }

  if (SITglobals.isModelStarted) {
    MdlTerminate();
  }

  DeleteCriticalSection(&SITglobals.taskCriticalSection);
  CloseHandle(SITexportglobals.flipCriticalSection);
  return NI_OK;
}

DLL_EXPORT int32_t NIRT_GetErrorMessageLength(void)
{
  int32_t retval = 0;
  if (SITglobals.errmsg != NULL) {
    retval = strlen(SITglobals.errmsg);
  } else if (rtmGetErrorStatus(S) != NULL) {
    retval = strlen(rtmGetErrorStatus(S));
  } else {
    retval = 0;
  }

  return retval;
}

DLL_EXPORT int32_t NIRT_ModelError(char* errmsg, int32_t *msglen)
{
  int32_t retVal = NI_OK;
  const char *sysmsg = NULL;
  const char *simStoppedMsg =
    "The model simulation was stopped, but no reason was specified. This may be expected behavior.";
  if ((SITglobals.errmsg != NULL) || (rtmGetErrorStatus(S) != NULL)) {
    retVal = NI_ERROR;
    if (*msglen > 0) {
      if (SITglobals.errmsg != NULL) {
        sysmsg = SITglobals.errmsg;
      } else {
        sysmsg = rtmGetErrorStatus(S);
      }

      if (*msglen > (int32_t)strlen(sysmsg)) {
        *msglen = strlen(sysmsg);
      }

      strncpy(errmsg, sysmsg, *msglen);
    }
  } else if (SITglobals.stopExecutionFlag == 1) {
    retVal = NI_OK;
    if (*msglen > 0) {
      if (*msglen > (int32_t)strlen(simStoppedMsg)) {
        *msglen = strlen(simStoppedMsg);
      }

      strncpy(errmsg, simStoppedMsg, *msglen);
    }
  } else {
    retVal = NI_OK;
    *msglen = 0;
  }

  return retVal;
}

extern const NI_Task NI_TaskList[];
extern const int32_t NI_NumTasks;
DLL_EXPORT int32_t NIRT_TaskRunTimeInfo(int32_t halt, int32_t* overruns, int32_t
  *numtasks)
{
  int32_t TaskOverrun = 0;
  int32_t i = 0;
  if (halt) {
    SITglobals.haltonOverrun = halt-1;
  }

  for (i=0; i<NUMST-TID01EQ; i++) {
    TaskOverrun+= overruns[i] = SITglobals.overrunCount[i+FIRST_TID];
  }

  *numtasks = NUMST;
  return TaskOverrun;
}

DLL_EXPORT int32_t NIRT_GetTaskSpec(int32_t index, int32_t *tID, double *tstep,
  double *offset)
{
  if ((index < 0) || (index >= NI_NumTasks) ) {
    return NI_NumTasks;
  }

  if (tID != NULL) {
    *tID = NI_TaskList[index].tid;
  }

  if (tstep != NULL) {
    *tstep = NI_TaskList[index].tstep;
  }

  if (offset != NULL) {
    *offset = NI_TaskList[index].offset;
  }

  return NI_OK;
}

DLL_EXPORT int32_t NIRT_GetModelSpec(char* name, int32_t *namelen, double
  *baseTimeStep,
  int32_t *outNumInports, int32_t *outNumOutports, int32_t *numTasks)
{
  if (namelen != NULL) {
    int32_t i = 0;
    int32_t length = 0;
    length = (int32_t)strlen(QUOTE(MODEL));
    if (*namelen == -1) {
      *namelen = length;
    } else if (name != NULL) {
      if (*namelen > length) {
        *namelen = length;
      }

      strncpy(name, QUOTE(MODEL), *namelen);
      for (i=0; i<*namelen; i++) {
        name[i] = (char) tolower(name[i]);
      }
    }
  }

  if (baseTimeStep != NULL) {
    *baseTimeStep = NI_TaskList[0].tstep;
  }

  if (outNumInports != NULL) {
    *outNumInports = NumInputPorts();
  }

  if (outNumOutports != NULL) {
    *outNumOutports = NumOutputPorts();
  }

  if (numTasks != NULL) {

#if !defined(MULTITASKING)

    *numTasks = 1;

#else

    *numTasks = NI_NumTasks;

#endif

  }

  return NI_OK;
}
