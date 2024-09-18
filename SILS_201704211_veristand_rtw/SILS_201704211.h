#ifndef RTW_HEADER_SILS_201704211_h_
#define RTW_HEADER_SILS_201704211_h_
#include <stddef.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "rtw_modelmap.h"
#ifndef SILS_201704211_COMMON_INCLUDES_
#define SILS_201704211_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif

#include "SILS_201704211_types.h"

#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rt_assert.h"
#include "rt_defines.h"

#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)    ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetSampleHitArray
#define rtmGetSampleHitArray(rtm)      ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmGetStepSize
#define rtmGetStepSize(rtm)            ((rtm)->Timing.stepSize)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
#define rtmGet_TimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmCounterLimit
#define rtmCounterLimit(rtm, idx)      ((rtm)->Timing.TaskCounters.cLimit[(idx)])
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

#ifndef rtmGetTimeOfLastOutput
#define rtmGetTimeOfLastOutput(rtm)    ((rtm)->Timing.timeOfLastOutput)
#endif

typedef struct {
  real_T c[3];
} B_cross_SILS_201704211_T;

typedef struct {
  real_T c[3];
} B_cross_SILS_201704211_p_T;

typedef struct {
  real_T year;
  real_T month;
  real_T day;
  real_T hour;
  real_T minute;
  real_T second;
} B_MATLABFunction_SILS_201704211_T;

typedef struct {
  real_T c[3];
} B_multi_SILS_201704211_T;

typedef struct {
  real_T flag;
} B_MATLABFunction_SILS_201704211_d_T;

typedef struct {
  real_T ang;
} B_MATLABFunction_SILS_201704211_e_T;

typedef struct {
  real_T c[3];
} B_multi_SILS_201704211_e_T;

typedef struct {
  real_T c[3];
} B_multi_SILS_201704211_h_T;

typedef struct {
  real_T rpm;
} B_MATLABFunction_SILS_201704211_i_T;

typedef struct {
  real_T y;
  real_T over_voltage;
  real_T over_current;
} B_MATLABFunction_SILS_201704211_l_T;

typedef struct {
  real_T trq_dir;
} B_MATLABFunction1_SILS_201704211_T;

typedef struct {
  real_T omega_out;
  real_T rot_dir;
} B_MATLABFunction2_SILS_201704211_T;

typedef struct {
  real_T SFunction4[4];
  real_T Product;
  real_T Sum2;
  real_T TmpSignalConversionAtSFunction2Inport1[8];
  real_T SFunction3[4];
  real_T Product_m;
  real_T Sum2_k;
  real_T TmpSignalConversionAtSFunction7Inport1[8];
  real_T SFunction5[4];
  real_T Product_i;
  real_T Sum2_e;
  real_T TmpSignalConversionAtSFunction8Inport1[8];
  real_T SFunction6[4];
  real_T Product_iu;
  real_T Sum2_g;
  real_T TmpSignalConversionAtSFunction9Inport1[8];
  real_T VectorConcatenate[9];
  real_T JD2[6];
  real_T ECEFPositiontoLLA_o1[2];
  real_T m2km;
  real_T TmpSignalConversionAtSFunction6Inport1[12];
  real_T TmpSignalConversionAtSFunctionInport1[4];
  real_T noise;
  real_T noise1;
  real_T TmpSignalConversionAtSFunction2Inport1_e[4];
  real_T noise_c;
  real_T noise1_m;
  real_T TmpSignalConversionAtSFunction3Inport1[4];
  real_T noise_o;
  real_T noise1_h;
  real_T TmpSignalConversionAtSFunction4Inport1[4];
  real_T noise_d;
  real_T noise1_b;
  real_T TmpSignalConversionAtSFunction7Inport1_o[4];
  real_T noise_f;
  real_T noise1_f;
  real_T TmpSignalConversionAtSFunction8Inport1_j[4];
  real_T noise_od;
  real_T noise1_l;
  real_T TmpSignalConversionAtSFunction9Inport1_p[4];
  real_T noise_i[3];
  real_T TmpSignalConversionAtSFunction1Inport1[4];
  real_T RandomNumber[3];
  real_T noise3;
  real_T TmpSignalConversionAtSFunction5Inport1[12];
  real_T VectorConcatenate_k[9];
  real_T detMatrix;
  real_T detMatrix_n;
  real_T IC[4];
  real_T IC1[3];
  real_T SFunction1[3];
  real_T Product1[3];
  real_T nvdegsec[3];
  real_T Sum1[3];
  real_T nudegsec2[3];
  real_T Gamp;
  real_T momentumofinertia;
  real_T Gamp_k;
  real_T momentumofinertia_p;
  real_T Gamp_a;
  real_T momentumofinertia_g;
  real_T Gamp_h;
  real_T momentumofinertia_c;
  real_T Clock;
  real_T ZeroOrderHold;
  real_T SFunction_o1;
  real_T SFunction_o2;
  real_T SFunction_o3;
  real_T SFunction_o4;
  real_T SFunction_o5;
  real_T y[12];
  real_T y_e[6];
  real_T d_q[4];
  real_T d_rate[3];
  real_T d_OE[6];
  real_T T[3];
  real_T a[3];
  real_T Sum4;
  real_T F107;
  real_T aph[7];
  real_T flag[23];
  real_T SFunction_o1_a;
  real_T SFunction_o2_k;
  real_T LST;
  real_T dy;
  uint8_T Compare;
  B_MATLABFunction2_SILS_201704211_T sf_MATLABFunction2_m;
  B_MATLABFunction1_SILS_201704211_T sf_MATLABFunction1_n;
  B_MATLABFunction_SILS_201704211_l_T sf_MATLABFunction_f0;
  B_MATLABFunction2_SILS_201704211_T sf_MATLABFunction2_cf;
  B_MATLABFunction1_SILS_201704211_T sf_MATLABFunction1_o;
  B_MATLABFunction_SILS_201704211_l_T sf_MATLABFunction_c;
  B_MATLABFunction2_SILS_201704211_T sf_MATLABFunction2_l;
  B_MATLABFunction1_SILS_201704211_T sf_MATLABFunction1_gl;
  B_MATLABFunction_SILS_201704211_l_T sf_MATLABFunction_p;
  B_MATLABFunction2_SILS_201704211_T sf_MATLABFunction2_c;
  B_MATLABFunction1_SILS_201704211_T sf_MATLABFunction1_d;
  B_MATLABFunction_SILS_201704211_l_T sf_MATLABFunction_i;
  B_MATLABFunction_SILS_201704211_i_T sf_MATLABFunction3_a;
  B_MATLABFunction_SILS_201704211_i_T sf_MATLABFunction2_d;
  B_MATLABFunction_SILS_201704211_i_T sf_MATLABFunction1_e;
  B_MATLABFunction_SILS_201704211_i_T sf_MATLABFunction_oq;
  B_multi_SILS_201704211_h_T sf_multi_os;
  B_multi_SILS_201704211_h_T sf_multi_lx;
  B_multi_SILS_201704211_e_T sf_multi_i;
  B_multi_SILS_201704211_e_T sf_multi_ag;
  B_multi_SILS_201704211_e_T sf_multi_f;
  B_multi_SILS_201704211_e_T sf_multi_n;
  B_multi_SILS_201704211_e_T sf_multi_ea;
  B_multi_SILS_201704211_e_T sf_multi_k;
  B_multi_SILS_201704211_e_T sf_multi_l;
  B_multi_SILS_201704211_e_T sf_multi_h;
  B_multi_SILS_201704211_e_T sf_multi_e;
  B_multi_SILS_201704211_e_T sf_multi_je;
  B_multi_SILS_201704211_e_T sf_multi_b;
  B_multi_SILS_201704211_h_T sf_multi_o;
  B_multi_SILS_201704211_e_T sf_multi_j;
  B_multi_SILS_201704211_e_T sf_multi_a;
  B_MATLABFunction_SILS_201704211_e_T sf_MATLABFunction_b;
  B_MATLABFunction_SILS_201704211_e_T sf_MATLABFunction_hq;
  B_MATLABFunction_SILS_201704211_e_T sf_MATLABFunction_fw;
  B_MATLABFunction_SILS_201704211_e_T sf_MATLABFunction_k;
  B_MATLABFunction_SILS_201704211_e_T sf_MATLABFunction_g;
  B_MATLABFunction_SILS_201704211_e_T sf_MATLABFunction_ol;
  B_MATLABFunction_SILS_201704211_e_T sf_MATLABFunction_h;
  B_MATLABFunction_SILS_201704211_T sf_MATLABFunction_j;
  B_MATLABFunction_SILS_201704211_d_T sf_MATLABFunction_l;
  B_MATLABFunction_SILS_201704211_d_T sf_MATLABFunction_ov;
  B_multi_SILS_201704211_T sf_multi_g;
  B_multi_SILS_201704211_T sf_multi_p;
  B_multi_SILS_201704211_T sf_multi;
  B_cross_SILS_201704211_p_T sf_cross_h;
  B_cross_SILS_201704211_T sf_cross_e3;
  B_MATLABFunction_SILS_201704211_T sf_MATLABFunction_f;
  B_cross_SILS_201704211_p_T sf_cross_e;
  B_cross_SILS_201704211_T sf_cross_k;
} B_SILS_201704211_T;

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
  int_T OE_integ_IWORK;
  boolean_T SRP_MODE;
  boolean_T RemnantMagnetism_MODE;
  boolean_T GravityGradient_MODE;
  boolean_T GPperturbation_MODE;
  boolean_T AirDrag_MODE;
} DW_SILS_201704211_T;

typedef struct {
  real_T TransferFcn1_CSTATE;
  real_T Integrator_CSTATE;
  real_T TransferFcn1_CSTATE_f;
  real_T Integrator_CSTATE_a;
  real_T TransferFcn1_CSTATE_a;
  real_T Integrator_CSTATE_p;
  real_T TransferFcn1_CSTATE_fc;
  real_T Integrator_CSTATE_a5;
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
} X_SILS_201704211_T;

typedef struct {
  real_T TransferFcn1_CSTATE;
  real_T Integrator_CSTATE;
  real_T TransferFcn1_CSTATE_f;
  real_T Integrator_CSTATE_a;
  real_T TransferFcn1_CSTATE_a;
  real_T Integrator_CSTATE_p;
  real_T TransferFcn1_CSTATE_fc;
  real_T Integrator_CSTATE_a5;
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
} XDot_SILS_201704211_T;

typedef struct {
  boolean_T TransferFcn1_CSTATE;
  boolean_T Integrator_CSTATE;
  boolean_T TransferFcn1_CSTATE_f;
  boolean_T Integrator_CSTATE_a;
  boolean_T TransferFcn1_CSTATE_a;
  boolean_T Integrator_CSTATE_p;
  boolean_T TransferFcn1_CSTATE_fc;
  boolean_T Integrator_CSTATE_a5;
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
} XDis_SILS_201704211_T;

#ifndef ODE4_INTG
#define ODE4_INTG

typedef struct {
  real_T *y;
  real_T *f[4];
} ODE4_IntgData;

#endif

struct P_SILS_201704211_T_ {
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
  real_T Constant2_Value_p;
  real_T Constant3_Value_d;
  real_T Constant2_Value_l;
  real_T Constant3_Value_p;
  real_T Constant2_Value_o;
  real_T Constant3_Value_i;
  real_T SFunction4_P1_Size[2];
  real_T SFunction4_P1;
  real_T Switch2_Threshold;
  real_T TransferFcn1_A;
  real_T TransferFcn1_C;
  real_T Integrator_IC;
  real_T motor_D;
  real_T Constant1_Value;
  real_T Switch1_Threshold;
  real_T rad2rpm_Gain;
  real_T Constant1_Value_i;
  real_T SFunction2_P1_Size[2];
  real_T SFunction2_P1;
  real_T SFunction3_P1_Size[2];
  real_T SFunction3_P1;
  real_T Switch2_Threshold_f;
  real_T TransferFcn1_A_d;
  real_T TransferFcn1_C_m;
  real_T Integrator_IC_m;
  real_T motor_D_c;
  real_T Constant1_Value_h;
  real_T Switch1_Threshold_g;
  real_T rad2rpm_Gain_l;
  real_T Constant6_Value;
  real_T SFunction7_P1_Size[2];
  real_T SFunction7_P1;
  real_T SFunction5_P1_Size[2];
  real_T SFunction5_P1;
  real_T Switch2_Threshold_f3;
  real_T TransferFcn1_A_i;
  real_T TransferFcn1_C_e;
  real_T Integrator_IC_h;
  real_T motor_D_p;
  real_T Constant1_Value_j;
  real_T Switch1_Threshold_l;
  real_T rad2rpm_Gain_n;
  real_T Constant2_Value_f;
  real_T SFunction8_P1_Size[2];
  real_T SFunction8_P1;
  real_T SFunction6_P1_Size[2];
  real_T SFunction6_P1;
  real_T Switch2_Threshold_fn;
  real_T TransferFcn1_A_b;
  real_T TransferFcn1_C_ex;
  real_T Integrator_IC_l;
  real_T motor_D_n;
  real_T Constant1_Value_b;
  real_T Switch1_Threshold_n;
  real_T rad2rpm_Gain_p;
  real_T Constant3_Value_m;
  real_T SFunction9_P1_Size[2];
  real_T SFunction9_P1;
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
  real_T ECEFPositiontoLLA_F;
  real_T ECEFPositiontoLLA_R;
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
  real_T Constant_Value_m;
  real_T Gain2_Gain_a;
  real_T Constant_Value_i[3];
  real_T Constant6_Value_o;
  real_T SFunction6_P1_Size_g[2];
  real_T SFunction6_P1_c;
  real_T SFunction6_P2_Size[2];
  real_T SFunction6_P2;
  real_T TransferFcn_A[2];
  real_T TransferFcn_C[2];
  real_T TransferFcn1_A_if[2];
  real_T TransferFcn1_C_d[2];
  real_T TransferFcn2_A[2];
  real_T TransferFcn2_C[2];
  real_T Constant5_Value;
  real_T SFunction_P1_Size[2];
  real_T SFunction_P1;
  real_T SFunction_P2_Size[2];
  real_T SFunction_P2;
  real_T noise_Mean;
  real_T noise1_Mean_g;
  real_T Constant_Value_hm;
  real_T Constant_Value_l;
  real_T Constant1_Value_a[3];
  real_T Constant2_Value_j;
  real_T Constant2_Value_ge[2];
  real_T SFunction2_P1_Size_a[2];
  real_T SFunction2_P1_p;
  real_T SFunction2_P2_Size[2];
  real_T SFunction2_P2;
  real_T noise_Mean_i;
  real_T noise1_Mean_d;
  real_T Constant_Value_hu;
  real_T Constant_Value_m2;
  real_T Constant1_Value_e[3];
  real_T Constant12_Value;
  real_T Constant2_Value_c[2];
  real_T SFunction3_P1_Size_p[2];
  real_T SFunction3_P1_f;
  real_T SFunction3_P2_Size[2];
  real_T SFunction3_P2;
  real_T noise_Mean_f;
  real_T noise1_Mean_m;
  real_T Constant_Value_nd;
  real_T Constant_Value_iq;
  real_T Constant1_Value_l[3];
  real_T Constant15_Value;
  real_T Constant2_Value_gn[2];
  real_T SFunction4_P1_Size_b[2];
  real_T SFunction4_P1_j;
  real_T SFunction4_P2_Size[2];
  real_T SFunction4_P2;
  real_T noise_Mean_g;
  real_T noise1_Mean_k;
  real_T Constant_Value_gh;
  real_T Constant_Value_f;
  real_T Constant1_Value_j0[3];
  real_T Constant4_Value;
  real_T Constant2_Value_a[2];
  real_T SFunction7_P1_Size_b[2];
  real_T SFunction7_P1_c;
  real_T SFunction7_P2_Size[2];
  real_T SFunction7_P2;
  real_T noise_Mean_fj;
  real_T noise1_Mean_j;
  real_T Constant_Value_e;
  real_T Constant_Value_fn;
  real_T Constant1_Value_g[3];
  real_T Constant1_Value_lw;
  real_T Constant2_Value_k[2];
  real_T SFunction8_P1_Size_o[2];
  real_T SFunction8_P1_d;
  real_T SFunction8_P2_Size[2];
  real_T SFunction8_P2;
  real_T noise_Mean_h;
  real_T noise1_Mean_m2;
  real_T Constant_Value_ib;
  real_T Constant_Value_k3;
  real_T Constant1_Value_n[3];
  real_T Constant3_Value_e;
  real_T Constant2_Value_n[2];
  real_T SFunction9_P1_Size_n[2];
  real_T SFunction9_P1_n;
  real_T SFunction9_P2_Size[2];
  real_T SFunction9_P2;
  real_T noise_Mean_m[3];
  real_T noise_StdDev[3];
  real_T TransferFcn_A_c;
  real_T TransferFcn_C_c;
  real_T TransferFcn1_A_l;
  real_T TransferFcn1_C_b;
  real_T TransferFcn2_A_p;
  real_T TransferFcn2_C_f;
  real_T SFunction1_P1_Size[2];
  real_T SFunction1_P1;
  real_T km2m_Gain_c;
  real_T RandomNumber_Mean[3];
  real_T RandomNumber_StdDev[3];
  real_T ECEFPositiontoLLA_F_h;
  real_T ECEFPositiontoLLA_R_d;
  real_T noise3_Minimum;
  real_T SFunction5_P1_Size_h[2];
  real_T SFunction5_P1_i;
  real_T Constant_Value_ns;
  real_T Constant_Value_ic;
  real_T Constant1_Value_o;
  real_T Constant2_Value_e;
  real_T Constant_Value_am;
  real_T Gain_Gain_ky;
  real_T Gain1_Gain_jd;
  real_T Gain2_Gain_m;
  real_T Constant_Value_mq;
  real_T Gain_Gain_a;
  real_T Gain1_Gain_h;
  real_T Gain2_Gain_bo;
  real_T Constant_Value_kc;
  real_T Gain_Gain_du;
  real_T Gain1_Gain_cj;
  real_T Gain2_Gain_cy;
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
  real_T rpm2rad_Gain;
  real_T rpm2rad1_Gain;
  real_T rpm2rad2_Gain;
  real_T rpm2rad3_Gain;
  real_T SFunction1_P1_Size_o[2];
  real_T SFunction1_P1_k;
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
};

struct tag_RTM_SILS_201704211_T {
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[3];
    SimStruct childSFunctions[21];
    SimStruct *childSFunctionPtrs[21];
    struct _ssBlkInfo2 blkInfo2[21];
    struct _ssSFcnModelMethods2 methods2[21];
    struct _ssSFcnModelMethods3 methods3[21];
    struct _ssSFcnModelMethods4 methods4[21];
    struct _ssStatesInfo2 statesInfo2[21];
    ssPeriodicStatesInfo periodicStatesInfo[21];
    struct _ssPortInfo2 inputOutputPortInfo2[21];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[11];
      struct _ssInPortUnit inputPortUnits[11];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[11];
      int_T iDims9[2];
      int_T iDims10[2];
      struct _ssPortOutputs outputPortInfo[2];
      struct _ssOutPortUnit outputPortUnits[2];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[2];
    } Sfcn0;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn1;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn2;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn3;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn4;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn5;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn6;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn7;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn8;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
    } Sfcn9;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
    } Sfcn10;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
    } Sfcn11;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
    } Sfcn12;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
    } Sfcn13;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
    } Sfcn14;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
    } Sfcn15;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
    } Sfcn16;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn17;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn18;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      real_T const *UPtrs0[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn19;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      struct _ssPortOutputs outputPortInfo[5];
      struct _ssOutPortUnit outputPortUnits[5];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[5];
    } Sfcn20;
  } NonInlinedSFcns;

  X_SILS_201704211_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[36];
  real_T odeF[4][36];
  ODE4_IntgData intgData;
  struct {
    rtwCAPI_ModelMappingInfo mmi;
  } DataMapInfo;

  struct {
    uint32_T options;
    int_T numContStates;
    int_T numPeriodicContStates;
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
      uint8_T cLimit[3];
    } TaskCounters;

    struct {
      uint8_T TID0_2;
    } RateInteraction;

    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
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

extern P_SILS_201704211_T SILS_201704211_P;
extern B_SILS_201704211_T SILS_201704211_B;
extern X_SILS_201704211_T SILS_201704211_X;
extern DW_SILS_201704211_T SILS_201704211_DW;
extern const real_T SILS_201704211_RGND;
extern void SILS_201704211_initialize(void);
extern void SILS_201704211_output0(void);
extern void SILS_201704211_update0(void);
extern void SILS_201704211_output(int_T tid);
extern void SILS_201704211_update(int_T tid);
extern void SILS_201704211_terminate(void);
extern const rtwCAPI_ModelMappingStaticInfo*
  SILS_201704211_GetCAPIStaticMap(void);
extern RT_MODEL_SILS_201704211_T *const SILS_201704211_M;

#endif
