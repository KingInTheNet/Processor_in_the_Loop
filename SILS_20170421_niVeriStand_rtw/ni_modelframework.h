#ifndef NI_MODELFRAMEWORK_H
#define NI_MODELFRAMEWORK_H

#define NIMF_VER_MAJOR                 2016
#define NIMF_VER_MINOR                 0
#define NIMF_VER_FIX                   0
#define NIMF_VER_BUILD                 72
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
#if defined (VXWORKS) || defined (kNIOSLinux)
#ifdef __cplusplus
#define DLL_EXPORT                     extern "C"
#else
#define DLL_EXPORT
#endif

#define DataSection(t)                 __attribute__ ((section((t))))
#else

#ifdef __cplusplus
#define DLL_EXPORT                     extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT                     __declspec(dllexport)
#endif

#define DataSection(t)
#endif

#if defined (VXWORKS) || defined (kNIOSLinux) || _MSC_VER > 1500

#include <stdint.h>
#else

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;

#ifndef _UINTPTR_T_DEFINED

typedef unsigned int uintptr_t;

#endif
#endif

#ifdef VXWORKS

# include <vxWorks.h>
# include <sysLib.h>
# include <math.h>
# include <semLib.h>
# include <time.h>
# include <private/mathP.h>

# define HANDLE                        SEM_ID
# define INFINITE                      WAIT_FOREVER
#elif kNIOSLinux

# include <semaphore.h>
# include <time.h>
# include <math.h>

# define HANDLE                        sem_t *
# define INFINITE                      -1
#else

# include <windows.h>
#endif

#ifndef UNUSED_PARAMETER
#define UNUSED_PARAMETER(x)            (void)(x)
#endif

#define NI_OK                          0
#define NI_ERROR                       1

typedef struct {
  int32_t idx;
  const char* name;
  int32_t TID;
  int32_t type;
  int32_t width;
  int32_t dimX;
  int32_t dimY;
} NI_ExternalIO;

typedef struct {
  int32_t idx;
  const char* paramname;
  uintptr_t addr;
  int32_t datatype;
  int32_t width;
  int32_t numofdims;
  int32_t dimListOffset;
  int32_t IsComplex;
} NI_Parameter;

typedef struct {
  int32_t idx;
  const char* blockname;
  int32_t portno;
  const char* signalname;
  uintptr_t addr;
  uintptr_t baseaddr;
  int32_t datatype;
  int32_t width;
  int32_t numofdims;
  int32_t dimListOffset;
  int32_t IsComplex;
} NI_Signal;

typedef struct {
  int32_t tid;
  double tstep;
  double offset;
  int32_t priority;
} NI_Task;

typedef struct {
  int32_t size;
  int32_t width;
  int32_t basetype;
} ParamSizeWidth;

typedef struct {
  uint32_t major;
  uint32_t minor;
  uint32_t fix;
  uint32_t build;
} NI_Version;

extern NI_Version NIVS_APIversion;
double USER_GetValueByDataType(void* ptr, int32_t subindex, int32_t type);
int32_t USER_SetValueByDataType(void* ptr, int32_t subindex, double value,
  int32_t type);
int32_t USER_Initialize(void);
int32_t USER_ModelStart(void);
int32_t USER_TakeOneStep(double *inData, double *outData, double timestamp);
int32_t USER_Finalize(void);
DLL_EXPORT int32_t NIRT_GetModelFrameworkVersion(uint32_t* major, uint32_t*
  minor, uint32_t* fix, uint32_t* build);
DLL_EXPORT int32_t NIRT_ModelStart(void);
DLL_EXPORT int32_t NIRT_InitializeModel(double finaltime, double *outTimeStep,
  int32_t *num_in, int32_t *num_out, int32_t* num_tasks);
DLL_EXPORT int32_t NIRT_PostOutputs(double *outData);
DLL_EXPORT int32_t NIRT_ModelUpdate(void);
DLL_EXPORT int32_t NIRT_Schedule(double *inData, double *outData, double
  *outTime, int32_t *dispatchtasks);
DLL_EXPORT int32_t NIRT_TaskTakeOneStep(int32_t taskid);
DLL_EXPORT int32_t NIRT_FinalizeModel(void);
DLL_EXPORT int32_t NIRT_ProbeSignals(int32_t *sigindices, int32_t numsigs,
  double *value, int32_t* num);
DLL_EXPORT int32_t NIRT_SetScalarParameterInline(uint32_t index, uint32_t
  subindex, double paramvalue);
DLL_EXPORT int32_t NIRT_SetVectorParameter(uint32_t index, const double
  * paramvalues, uint32_t paramlength);
DLL_EXPORT int32_t NIRT_SetParameter(int32_t index, int32_t subindex, double val);
DLL_EXPORT int32_t NIRT_GetParameter(int32_t index, int32_t subindex, double
  * val);
DLL_EXPORT int32_t NIRT_GetVectorParameter(uint32_t index, double* paramValues,
  uint32_t paramLength);
DLL_EXPORT int32_t NIRT_GetErrorMessageLength(void);
DLL_EXPORT int32_t NIRT_ModelError(char* errmsg, int32_t* msglen);
DLL_EXPORT int32_t NIRT_TaskRunTimeInfo(int32_t halt, int32_t* overruns, int32_t
  *numtasks);
DLL_EXPORT int32_t NIRT_GetSimState(int32_t* numContStates, char
  * contStatesNames, double* contStates, int32_t* numDiscStates,
  char* discStatesNames, double* discStates, int32_t* numClockTicks, char
  * clockTicksNames, int32_t* clockTicks);
DLL_EXPORT int32_t NIRT_SetSimState(double* contStates, double* discStates,
  int32_t* clockTicks);
DLL_EXPORT int32_t NIRT_GetBuildInfo(char* detail, int32_t* len);
DLL_EXPORT int32_t NIRT_GetModelSpec(char* name, int32_t *namelen, double
  *baseTimeStep, int32_t *outNumInports,
  int32_t *outNumOutports, int32_t *numtasks);
DLL_EXPORT int32_t NIRT_GetParameterIndices(int32_t* indices, int32_t* len);
DLL_EXPORT int32_t NIRT_GetParameterSpec(int32_t* paramidx, char* ID, int32_t*
  ID_len, char* paramname, int32_t *pnlen,
  int32_t *datatype, int32_t* dims, int32_t* numdim);
DLL_EXPORT int32_t NIRT_GetSignalSpec(int32_t* sigidx, char* ID, int32_t* ID_len,
  char* blkname, int32_t* bnlen, int32_t *portnum,
  char* signame, int32_t* snlen, int32_t *datatype, int32_t* dims, int32_t*
  numdim);
DLL_EXPORT int32_t NIRT_GetTaskSpec(int32_t index, int32_t* tid, double *tstep,
  double *offset);
DLL_EXPORT int32_t NIRT_GetExtIOSpec(int32_t index, int32_t *idx, char* name,
  int32_t* tid, int32_t *type, int32_t *dims, int32_t* numdims);

#endif
