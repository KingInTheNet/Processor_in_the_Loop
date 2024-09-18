#ifndef RTW_HEADER_SILS_201704211_private_h_
#define RTW_HEADER_SILS_201704211_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "SILS_201704211.h"

#ifndef rtmSetFirstInitCond
#define rtmSetFirstInitCond(rtm, val)  ((rtm)->Timing.firstInitCondFlag = (val))
#endif

#ifndef rtmIsFirstInitCond
#define rtmIsFirstInitCond(rtm)        ((rtm)->Timing.firstInitCondFlag)
#endif

#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern real_T rt_modd_snf(real_T u0, real_T u1);
extern real_T rt_remd_snf(real_T u0, real_T u1);
extern void rt_invd3x3_snf(const real_T u[9], real_T y[9]);
extern void sfunc_nrlmsise00(SimStruct *rts);
extern void sfunc_RW_TX(SimStruct *rts);
extern void sfunc_RW_RX(SimStruct *rts);
extern void sfunc_STT(SimStruct *rts);
extern void sfunc_FOG(SimStruct *rts);
extern void sfunc_NSAS(SimStruct *rts);
extern void sfunc_GAS(SimStruct *rts);
extern void sfunc_GPS(SimStruct *rts);
extern void sfunc_MTQ(SimStruct *rts);
extern void sfunc_AOBC(SimStruct *rts);
extern void SILS_201704211_cross(const real_T rtu_a[3], const real_T rtu_b[3],
  B_cross_SILS_201704211_T *localB);
extern void SILS_201704211_cross_e(const real_T rtu_a[3], real_T rtu_b, real_T
  rtu_b_d, real_T rtu_b_p, B_cross_SILS_201704211_p_T *localB);
extern void SILS_201704211_MATLABFunction(real_T rtu_JD,
  B_MATLABFunction_SILS_201704211_T *localB);
extern void SILS_201704211_multi(const real_T rtu_a[9], const real_T rtu_b[3],
  B_multi_SILS_201704211_T *localB);
extern void SILS_201704211_MATLABFunction_o(const real_T rtu_obj[3], const
  real_T rtu_pos[3], real_T rtu_Re, B_MATLABFunction_SILS_201704211_d_T *localB);
extern void SILS_201704211_MATLABFunction_h(real_T rtu_h, real_T rtu_R,
  B_MATLABFunction_SILS_201704211_e_T *localB);
extern void SILS_201704211_multi_a(const real_T rtu_a[9], real_T rtu_b, real_T
  rtu_b_o, real_T rtu_b_f, B_multi_SILS_201704211_e_T *localB);
extern void SILS_201704211_multi_o(const real_T rtu_a[9], real_T rtu_b, real_T
  rtu_b_c, real_T rtu_b_o, B_multi_SILS_201704211_h_T *localB);
extern void SILS_201704211_MATLABFunction_oq(real_T rtu_absrpm, real_T
  rtu_rotdir, B_MATLABFunction_SILS_201704211_i_T *localB);
extern void SILS_201704211_MATLABFunction_i(real_T rtu_onoff, real_T rtu_voltage,
  real_T rtu_current, B_MATLABFunction_SILS_201704211_l_T *localB);
extern void SILS_201704211_MATLABFunction1(real_T rtu_current,
  B_MATLABFunction1_SILS_201704211_T *localB);
extern void SILS_201704211_MATLABFunction2(real_T rtu_omega,
  B_MATLABFunction2_SILS_201704211_T *localB);
void SILS_201704211_output0(void);
void SILS_201704211_update0(void);
void SILS_201704211_output2(void);
void SILS_201704211_update2(void);
extern void SILS_201704211_derivatives(void);

#endif
