/*
* Copyright 2016-2021 The MathWorks, Inc.
*
* File: xcp_platform_default.h
*
* Abstract:
*  Default implementation for XCP Platform Abstraction Layer interface
*  supporting generic Linux, Windows and Mac
*/

#ifndef XCP_PLATFORM_CUSTOM_VERISTAND_H
#define XCP_PLATFORM_CUSTOM_VERISTAND_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)

#include "windows.h"

#elif defined(__linux__)

#include <sys/time.h>

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <stddef.h>
#include <sys/select.h>
#endif /* _POSIX_C_SOURCE >= 199309L */

#else

#error "Inavalid Target"

#endif

#define XCP_PRINTF printf

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)

/* Define Mutual exclusion APIs */
#define XCP_MUTEX_DEFINE(lock) HANDLE lock
#define XCP_MUTEX_INIT(lock) lock = CreateMutex(0, false, 0)
#define XCP_MUTEX_LOCK(lock) WaitForSingleObject((lock), INFINITE)
#define XCP_MUTEX_UNLOCK(lock) ReleaseMutex(lock)

#ifdef XCP_LOCKLESS_SYNC_DATA_TRANSFER_SUPPORT
/* The above mutex implementation does not support independent
   event locks to protect DAQ list data structures */
#define XCP_DAQ_LIST_INDEPENDENT_EVENT_LOCK 0
#endif

#elif defined(__linux__)

#include <pthread.h>

/* Define Mutual exclusion APIs */
#define XCP_MUTEX_DEFINE(lock) pthread_mutex_t lock
#define XCP_MUTEX_INIT(lock) pthread_mutex_init(&(lock), NULL)
#define XCP_MUTEX_LOCK(lock) pthread_mutex_lock(&(lock))
#define XCP_MUTEX_UNLOCK(lock) pthread_mutex_unlock(&(lock))

#else

#error "Inavalid Target"

#endif

extern uint8_T* xcpAddressGet(uint8_T addressExtension, uint32_T address);
#define XCP_ADDRESS_GET(addressExtension, address) xcpAddressGet(addressExtension, address)

#ifndef XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME

extern uint32_T xcpGetTimestamp(void);
#define XCP_TIMESTAMP_GET xcpGetTimestamp

#endif

extern void xcpSleep(uint32_T seconds, uint32_T microseconds);
#define XCP_SLEEP(seconds, microseconds) xcpSleep(seconds, microseconds)

#if defined(__linux__)
/* Use __attribute__((packed)) and __attribute__((aligned(n))) on GCC */
#define XCP_PRAGMA_PACK_BEGIN(n)
#define XCP_PRAGMA_PACK_END()
#define XCP_ATTRIBUTE_ALIGNED(n) __attribute__((aligned(n)))
#define XCP_ATTRIBUTE_PACKED __attribute__((packed))
#else

#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && defined(_MSC_VER)
/* _Pragma was introduced in C99, but it's supported by VS only
   from VS2019 v.16.6. To allow earlier versions of the compiler
   we use the Microsoft-specific __pragma instead */
#define PRAGMA(n) __pragma(n)
#else
/* Default to the standard implementation in all other cases, including MinGW */
#define PRAGMA(n) _Pragma(#n)
#endif

#define XCP_PRAGMA_PACK_BEGIN(n) PRAGMA(pack(push, n))
#define XCP_PRAGMA_PACK_END() PRAGMA(pack(pop))
#define XCP_ATTRIBUTE_ALIGNED(n)
#define XCP_ATTRIBUTE_PACKED
#endif /* defined(__linux__) */

#endif /* XCP_PLATFORM_CUSTOM_VERISTAND_H */
