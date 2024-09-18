#ifndef RTW_HEADER_SILS_20241709_cap_host_h__
#define RTW_HEADER_SILS_20241709_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap_simtarget.h"
typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
SILS_20241709_host_DataMapInfo_T ;
#ifdef __cplusplus
extern "C" {
#endif
void SILS_20241709_host_InitializeDataMapInfo (
SILS_20241709_host_DataMapInfo_T * dataMap , const char * path ) ;
#ifdef __cplusplus
}
#endif
#endif
#endif
