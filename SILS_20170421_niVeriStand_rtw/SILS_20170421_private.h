#ifndef RTW_HEADER_SILS_20170421_private_h_
#define RTW_HEADER_SILS_20170421_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern void rt_invd3x3_snf(const real_T u[9], real_T y[9]);
extern real_T rt_roundd_snf(real_T u);
extern real_T rt_remd_snf(real_T u0, real_T u1);
extern void sfunc_nrlmsise00(SimStruct *rts);
extern void sfunc_AOBC(SimStruct *rts);
extern void SILS_20170421_cross(const real_T rtu_a[3], const real_T rtu_b[3],
  B_cross_SILS_20170421_T *localB);
extern void SILS_20170421_cross_e(const real_T rtu_a[3], real_T rtu_b, real_T
  rtu_b_d, real_T rtu_b_p, B_cross_SILS_20170421_p_T *localB);
extern void SILS_20170421_WhileIteratorSubsystem_Init
  (DW_WhileIteratorSubsystem_SILS_20170421_T *localDW,
   P_WhileIteratorSubsystem_SILS_20170421_T *localP);
extern void SILS_20170421_WhileIteratorSubsystem_Start
  (B_WhileIteratorSubsystem_SILS_20170421_T *localB,
   DW_WhileIteratorSubsystem_SILS_20170421_T *localDW,
   P_WhileIteratorSubsystem_SILS_20170421_T *localP);
extern void SILS_20170421_WhileIteratorSubsystem(real_T rtu_rho, real_T rtu_z,
  real_T rtu_b, real_T rtu_f, real_T rtu_e2, real_T rtu_ep2,
  B_WhileIteratorSubsystem_SILS_20170421_T *localB,
  DW_WhileIteratorSubsystem_SILS_20170421_T *localDW,
  P_WhileIteratorSubsystem_SILS_20170421_T *localP);
extern void SILS_20170421_MATLABFunction(real_T rtu_JD,
  B_MATLABFunction_SILS_20170421_T *localB);
extern void SILS_20170421_multi(const real_T rtu_a[9], const real_T rtu_b[3],
  B_multi_SILS_20170421_T *localB);
extern void SILS_20170421_MATLABFunction_o(const real_T rtu_obj[3], const real_T
  rtu_pos[3], real_T rtu_Re, B_MATLABFunction_SILS_20170421_d_T *localB);
extern void SILS_20170421_MATLABFunction_h(real_T rtu_h, real_T rtu_R,
  B_MATLABFunction_SILS_20170421_e_T *localB);
extern void SILS_20170421_multi_a(const real_T rtu_a[9], real_T rtu_b, real_T
  rtu_b_o, real_T rtu_b_f, B_multi_SILS_20170421_e_T *localB);
extern void SILS_20170421_multi_o(const real_T rtu_a[9], real_T rtu_b, real_T
  rtu_b_c, real_T rtu_b_o, B_multi_SILS_20170421_h_T *localB);
extern void SILS_20170421_MATLABFunction_oq(real_T rtu_absrpm, real_T rtu_rotdir,
  B_MATLABFunction_SILS_20170421_i_T *localB);
extern void SILS_20170421_MATLABFunction_i(real_T rtu_onoff, real_T rtu_voltage,
  real_T rtu_current, B_MATLABFunction_SILS_20170421_l_T *localB);
extern void SILS_20170421_MATLABFunction1(real_T rtu_current,
  B_MATLABFunction1_SILS_20170421_T *localB);
extern void SILS_20170421_MATLABFunction2(real_T rtu_omega,
  B_MATLABFunction2_SILS_20170421_T *localB);
void SILS_20170421_output0(void);
void SILS_20170421_update0(void);
void SILS_20170421_output2(void);
void SILS_20170421_update2(void);
extern void SILS_20170421_derivatives(void);

#endif
