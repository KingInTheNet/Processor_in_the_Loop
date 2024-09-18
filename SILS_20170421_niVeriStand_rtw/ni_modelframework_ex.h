#ifndef NI_MODELFRAMEWORK_EX_H
#define NI_MODELFRAMEWORK_EX_H
#include "ni_modelframework.h"

#define VIRTUAL_SIG                    2
#define BLOCKIO_SIG                    0
#define EXTIO_SIG                      1
#define EXT_IN                         0
#define EXT_OUT                        1

typedef struct {
  HANDLE flipCriticalSection;
  uint_T copyTaskBitfield;
  uint_T inCriticalSection;
} _SITexportglobals;

#if defined(__cplusplus)

extern "C" {

#endif

  void SetSITErrorMessage(const char *ErrMsg, int32_t Error);

#if defined (VXWORKS) || defined (kNIOSLinux)
#define CRITICAL_SECTION               HANDLE

  void InitializeCriticalSection(CRITICAL_SECTION *CriticalSection);
  HANDLE CreateSemaphore(void* lpSemaphoreAttributes, int lInitialCount, int
    lMaximumCount, char* lpName);
  void EnterCriticalSection(CRITICAL_SECTION *CriticalSection);
  void WaitForSingleObject(HANDLE hHandle, int dwMilliseconds);
  void LeaveCriticalSection(CRITICAL_SECTION *CriticalSection);
  void ReleaseSemaphore(HANDLE hSemaphore, int lReleaseCount, void
                        * lpPreviousCount);
  void DeleteCriticalSection(CRITICAL_SECTION *CriticalSection);
  void CloseHandle(HANDLE hObject);

#endif

#if defined(__cplusplus)

}
#endif
#endif
