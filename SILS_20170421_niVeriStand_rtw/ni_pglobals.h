#if !defined(_DEFINED_TYPEDEF_FOR_niUrtParametersTypeDef_)
#define _DEFINED_TYPEDEF_FOR_niUrtParametersTypeDef_

#define NI_PARAM_TYPEDEF               P_SILS_20170421_T
#endif

#if defined(_NI_DEFINE_PARAMS_DBL_BUFFER_)
#undef _NI_DEFINE_PARAMS_DBL_BUFFER_
#ifdef MULTITASKING
#define NI_PARAM_BUFF                  (*param_lookup[tid][READSIDE])
#else
#define NI_PARAM_BUFF                  rtParameter[READSIDE]
#endif

#define SILS_20170421_P                NI_PARAM_BUFF
#elif defined(_NI_UNDEFINE_PARAMS_DBL_BUFFER_)
#undef _NI_UNDEFINE_PARAMS_DBL_BUFFER_
#undef SILS_20170421_P
#endif
