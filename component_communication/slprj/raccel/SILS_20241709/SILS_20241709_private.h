#ifndef RTW_HEADER_SILS_20241709_private_h_
#define RTW_HEADER_SILS_20241709_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "SILS_20241709.h"
#include "SILS_20241709_types.h"
#if !defined(rt_VALIDATE_MEMORY)
#define rt_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
    ssSetErrorStatus(rtS, RT_MEMORY_ALLOCATION_ERROR);\
    }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((ptr));\
    (ptr) = (NULL);\
    }
#else
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((void *)(ptr));\
    (ptr) = (NULL);\
    }
#endif
#endif
extern real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) ; extern real_T
rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T * u ) ; extern void rt_invd3x3_snf (
const real_T u [ 9 ] , real_T y [ 9 ] ) ; extern void sfunc_nrlmsise00 (
SimStruct * rts ) ; extern void sfunc_RW_RX ( SimStruct * rts ) ; extern void
sfunc_STT ( SimStruct * rts ) ; extern void sfunc_FOG ( SimStruct * rts ) ;
extern void sfunc_NSAS ( SimStruct * rts ) ; extern void sfunc_GAS (
SimStruct * rts ) ; extern void sfunc_GPS ( SimStruct * rts ) ; extern void
sfunc_AOBC ( SimStruct * rts ) ; extern void sfunc_MTQ ( SimStruct * rts ) ;
extern void sfunc_RW_TX ( SimStruct * rts ) ; extern void fsnekqmcuz ( const
real_T cxpbrxwvph [ 3 ] , const real_T mq5wdpevr4 [ 3 ] , oct3g4vhoh * localB
) ; extern void lkjrchjyiy ( const real_T ff43jzuww3 [ 3 ] , real_T
mzyoemzng2 , real_T mklgzo1miu , real_T gcqtcaennh , pigla2omys * localB ) ;
extern void bjzuls4oiv ( real_T c0vftrcglr , cyjo4x5ck1 * localB ) ; extern
void ivx0j3mj3l ( const real_T i5kphrrr2y [ 9 ] , const real_T m4eydfuwzq [ 3
] , d5mabmixx5 * localB ) ; extern void ajln0dl4w5 ( real_T kqww0sjoke ,
real_T obxid0zk5a , oxebiebxcs * localB ) ; extern void n4mcthnbsb ( const
real_T mzw1h4tlas [ 9 ] , real_T gydnt10vhl , real_T pgiit2glgs , real_T
eav11ieugn , haq3dksarh * localB ) ; extern void llkwb1gopr ( const real_T
m3lcewolkc [ 9 ] , real_T nxvel350vb , real_T kydlusovm3 , real_T knmjfmjkag
, bmt3ngprbx * localB ) ; extern void e3r1b51sa5 ( real_T itzvgvcmcv , real_T
nzpyxtxcny , gacwgjuhge * localB ) ; extern void gla0ncnrx0 ( real_T
lymk5v0m2t , real_T ppz354xn4r , real_T l2fqg1kzln , fbvoxbsppm * localB ) ;
extern void g3res1bek1 ( real_T ha5qtaji51 , fuwz32fyfq * localB ) ; extern
void fgza3nsgzk ( real_T c1st5kmkya , hdyhizuepg * localB ) ;
#if !defined(MULTITASKING) && !defined(NRT)
#error Model (SILS_20241709) was built \in MultiTasking solver mode, however the MULTITASKING define \is not present. Please verify that your template makefile is \configured correctly.
#endif
#endif
