#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "SILS_201704211_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else
#include "builtin_typeid_types.h"
#include "SILS_201704211.h"
#include "SILS_201704211_capi.h"
#include "SILS_201704211_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               (NULL)
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif

static const rtwCAPI_BlockParameters rtBlockParameters[] = {

  { 0, TARGET_STRING("SILS_201704211/Constant1"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 1, TARGET_STRING("SILS_201704211/Constant2"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 2, TARGET_STRING("SILS_201704211/Constant3"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 3, TARGET_STRING("SILS_201704211/Constant6"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 4, TARGET_STRING("SILS_201704211/reaction torque"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 5, TARGET_STRING("SILS_201704211/S-Function1"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 6, TARGET_STRING("SILS_201704211/S-Function2"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 7, TARGET_STRING("SILS_201704211/S-Function3"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 8, TARGET_STRING("SILS_201704211/S-Function4"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 9, TARGET_STRING("SILS_201704211/S-Function5"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 10, TARGET_STRING("SILS_201704211/S-Function6"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 11, TARGET_STRING("SILS_201704211/S-Function7"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 12, TARGET_STRING("SILS_201704211/S-Function8"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 13, TARGET_STRING("SILS_201704211/S-Function9"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 14, TARGET_STRING("SILS_201704211/Environment&Dynamics/km2m"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 15, TARGET_STRING("SILS_201704211/Environment&Dynamics/m2km"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 16, TARGET_STRING("SILS_201704211/Environment&Dynamics/ECEF Position to LLA"),
    TARGET_STRING("F"), 0, 0, 0 },

  { 17, TARGET_STRING("SILS_201704211/Environment&Dynamics/ECEF Position to LLA"),
    TARGET_STRING("R"), 0, 0, 0 },

  { 18, TARGET_STRING("SILS_201704211/MTQs/nT_2_T"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 19, TARGET_STRING("SILS_201704211/SensorDataConversion/Constant1"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 20, TARGET_STRING("SILS_201704211/SensorDataConversion/Constant12"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 21, TARGET_STRING("SILS_201704211/SensorDataConversion/Constant15"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 22, TARGET_STRING("SILS_201704211/SensorDataConversion/Constant2"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 23, TARGET_STRING("SILS_201704211/SensorDataConversion/Constant3"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 24, TARGET_STRING("SILS_201704211/SensorDataConversion/Constant4"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 25, TARGET_STRING("SILS_201704211/SensorDataConversion/Constant5"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 26, TARGET_STRING("SILS_201704211/SensorDataConversion/Constant6"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 27, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 28, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 29, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function1"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 30, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function2"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 31, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function2"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 32, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function3"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 33, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function3"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 34, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function4"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 35, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function4"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 36, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function5"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 37, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function6"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 38, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function6"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 39, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function7"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 40, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function7"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 41, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function8"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 42, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function8"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 43, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function9"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 44, TARGET_STRING("SILS_201704211/SensorDataConversion/S-Function9"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 45, TARGET_STRING("SILS_201704211/Sensors/km2m"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 46, TARGET_STRING("SILS_201704211/Sensors/rad2deg"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 47, TARGET_STRING("SILS_201704211/Sensors/noise1"),
    TARGET_STRING("Mean"), 0, 1, 0 },

  { 48, TARGET_STRING("SILS_201704211/Sensors/noise1"),
    TARGET_STRING("StdDev"), 0, 1, 0 },

  { 49, TARGET_STRING("SILS_201704211/three_one_skew/rpm2rad"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 50, TARGET_STRING("SILS_201704211/three_one_skew/rpm2rad1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 51, TARGET_STRING("SILS_201704211/three_one_skew/rpm2rad2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 52, TARGET_STRING("SILS_201704211/three_one_skew/rpm2rad3"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 53, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/hour2sec"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 54, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/min2sec"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 55, TARGET_STRING("SILS_201704211/Environment&Dynamics/AstroDynamics/sec_per_day"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 56, TARGET_STRING("SILS_201704211/Environment&Dynamics/GPperturbation/GPperturbation_RSW_km//s^2_3"),
    TARGET_STRING("InitialOutput"), 0, 2, 0 },

  { 57, TARGET_STRING("SILS_201704211/Environment&Dynamics/GPperturbation/deg2rad"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 58, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/GG_b_Nm_3"),
    TARGET_STRING("InitialOutput"), 0, 2, 0 },

  { 59, TARGET_STRING("SILS_201704211/Environment&Dynamics/Remnant Magnetism/remmag_b_Nm_3"),
    TARGET_STRING("InitialOutput"), 0, 2, 0 },

  { 60, TARGET_STRING("SILS_201704211/Environment&Dynamics/Remnant Magnetism/nT2T"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 61, TARGET_STRING("SILS_201704211/Environment&Dynamics/RigidBodyDynamics/IC"),
    TARGET_STRING("Value"), 0, 3, 0 },

  { 62, TARGET_STRING("SILS_201704211/Environment&Dynamics/RigidBodyDynamics/IC1"),
    TARGET_STRING("Value"), 0, 1, 0 },

  { 63, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/SRP_b_Nm_3"),
    TARGET_STRING("InitialOutput"), 0, 2, 0 },

  { 64, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 65, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 66, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 67, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 68, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 69, TARGET_STRING("SILS_201704211/MTQs/MTQ_1/Transfer Fcn"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 70, TARGET_STRING("SILS_201704211/MTQs/MTQ_1/Transfer Fcn"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 71, TARGET_STRING("SILS_201704211/MTQs/MTQ_2/Transfer Fcn"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 72, TARGET_STRING("SILS_201704211/MTQs/MTQ_2/Transfer Fcn"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 73, TARGET_STRING("SILS_201704211/MTQs/MTQ_3/Transfer Fcn"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 74, TARGET_STRING("SILS_201704211/MTQs/MTQ_3/Transfer Fcn"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 75, TARGET_STRING("SILS_201704211/Sensors/GAS/noise"),
    TARGET_STRING("Mean"), 0, 1, 0 },

  { 76, TARGET_STRING("SILS_201704211/Sensors/GAS/noise"),
    TARGET_STRING("StdDev"), 0, 1, 0 },

  { 77, TARGET_STRING("SILS_201704211/Sensors/GAS/Transfer Fcn"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 78, TARGET_STRING("SILS_201704211/Sensors/GAS/Transfer Fcn"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 79, TARGET_STRING("SILS_201704211/Sensors/GAS/Transfer Fcn1"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 80, TARGET_STRING("SILS_201704211/Sensors/GAS/Transfer Fcn1"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 81, TARGET_STRING("SILS_201704211/Sensors/GAS/Transfer Fcn2"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 82, TARGET_STRING("SILS_201704211/Sensors/GAS/Transfer Fcn2"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 83, TARGET_STRING("SILS_201704211/Sensors/GYRO/b0(deg//sec)"),
    TARGET_STRING("Value"), 0, 1, 0 },

  { 84, TARGET_STRING("SILS_201704211/Sensors/GYRO/Integrator"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 85, TARGET_STRING("SILS_201704211/Sensors/GYRO/nu(deg//sec^2)"),
    TARGET_STRING("Mean"), 0, 1, 0 },

  { 86, TARGET_STRING("SILS_201704211/Sensors/GYRO/nu(deg//sec^2)"),
    TARGET_STRING("StdDev"), 0, 1, 0 },

  { 87, TARGET_STRING("SILS_201704211/Sensors/GYRO/nv(deg//sec)"),
    TARGET_STRING("Mean"), 0, 1, 0 },

  { 88, TARGET_STRING("SILS_201704211/Sensors/GYRO/nv(deg//sec)"),
    TARGET_STRING("StdDev"), 0, 1, 0 },

  { 89, TARGET_STRING("SILS_201704211/Sensors/GYRO/Transfer Fcn"),
    TARGET_STRING("A"), 0, 4, 0 },

  { 90, TARGET_STRING("SILS_201704211/Sensors/GYRO/Transfer Fcn"),
    TARGET_STRING("C"), 0, 5, 0 },

  { 91, TARGET_STRING("SILS_201704211/Sensors/GYRO/Transfer Fcn1"),
    TARGET_STRING("A"), 0, 4, 0 },

  { 92, TARGET_STRING("SILS_201704211/Sensors/GYRO/Transfer Fcn1"),
    TARGET_STRING("C"), 0, 5, 0 },

  { 93, TARGET_STRING("SILS_201704211/Sensors/GYRO/Transfer Fcn2"),
    TARGET_STRING("A"), 0, 4, 0 },

  { 94, TARGET_STRING("SILS_201704211/Sensors/GYRO/Transfer Fcn2"),
    TARGET_STRING("C"), 0, 5, 0 },

  { 95, TARGET_STRING("SILS_201704211/Sensors/NSAS1/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 96, TARGET_STRING("SILS_201704211/Sensors/NSAS1/z>0"),
    TARGET_STRING("const"), 0, 0, 0 },

  { 97, TARGET_STRING("SILS_201704211/Sensors/NSAS1/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 98, TARGET_STRING("SILS_201704211/Sensors/NSAS1/Constant1"),
    TARGET_STRING("Value"), 0, 2, 0 },

  { 99, TARGET_STRING("SILS_201704211/Sensors/NSAS1/Constant2"),
    TARGET_STRING("Value"), 0, 5, 0 },

  { 100, TARGET_STRING("SILS_201704211/Sensors/NSAS1/rad2deg"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 101, TARGET_STRING("SILS_201704211/Sensors/NSAS1/noise"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 102, TARGET_STRING("SILS_201704211/Sensors/NSAS1/noise1"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 103, TARGET_STRING("SILS_201704211/Sensors/NSAS2/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 104, TARGET_STRING("SILS_201704211/Sensors/NSAS2/z>0"),
    TARGET_STRING("const"), 0, 0, 0 },

  { 105, TARGET_STRING("SILS_201704211/Sensors/NSAS2/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 106, TARGET_STRING("SILS_201704211/Sensors/NSAS2/Constant1"),
    TARGET_STRING("Value"), 0, 2, 0 },

  { 107, TARGET_STRING("SILS_201704211/Sensors/NSAS2/Constant2"),
    TARGET_STRING("Value"), 0, 5, 0 },

  { 108, TARGET_STRING("SILS_201704211/Sensors/NSAS2/rad2deg"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 109, TARGET_STRING("SILS_201704211/Sensors/NSAS2/noise"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 110, TARGET_STRING("SILS_201704211/Sensors/NSAS2/noise1"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 111, TARGET_STRING("SILS_201704211/Sensors/NSAS3/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 112, TARGET_STRING("SILS_201704211/Sensors/NSAS3/z>0"),
    TARGET_STRING("const"), 0, 0, 0 },

  { 113, TARGET_STRING("SILS_201704211/Sensors/NSAS3/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 114, TARGET_STRING("SILS_201704211/Sensors/NSAS3/Constant1"),
    TARGET_STRING("Value"), 0, 2, 0 },

  { 115, TARGET_STRING("SILS_201704211/Sensors/NSAS3/Constant2"),
    TARGET_STRING("Value"), 0, 5, 0 },

  { 116, TARGET_STRING("SILS_201704211/Sensors/NSAS3/rad2deg"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 117, TARGET_STRING("SILS_201704211/Sensors/NSAS3/noise"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 118, TARGET_STRING("SILS_201704211/Sensors/NSAS3/noise1"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 119, TARGET_STRING("SILS_201704211/Sensors/NSAS4/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 120, TARGET_STRING("SILS_201704211/Sensors/NSAS4/z>0"),
    TARGET_STRING("const"), 0, 0, 0 },

  { 121, TARGET_STRING("SILS_201704211/Sensors/NSAS4/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 122, TARGET_STRING("SILS_201704211/Sensors/NSAS4/Constant1"),
    TARGET_STRING("Value"), 0, 2, 0 },

  { 123, TARGET_STRING("SILS_201704211/Sensors/NSAS4/Constant2"),
    TARGET_STRING("Value"), 0, 5, 0 },

  { 124, TARGET_STRING("SILS_201704211/Sensors/NSAS4/rad2deg"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 125, TARGET_STRING("SILS_201704211/Sensors/NSAS4/noise"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 126, TARGET_STRING("SILS_201704211/Sensors/NSAS4/noise1"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 127, TARGET_STRING("SILS_201704211/Sensors/NSAS5/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 128, TARGET_STRING("SILS_201704211/Sensors/NSAS5/z>0"),
    TARGET_STRING("const"), 0, 0, 0 },

  { 129, TARGET_STRING("SILS_201704211/Sensors/NSAS5/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 130, TARGET_STRING("SILS_201704211/Sensors/NSAS5/Constant1"),
    TARGET_STRING("Value"), 0, 2, 0 },

  { 131, TARGET_STRING("SILS_201704211/Sensors/NSAS5/Constant2"),
    TARGET_STRING("Value"), 0, 5, 0 },

  { 132, TARGET_STRING("SILS_201704211/Sensors/NSAS5/rad2deg"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 133, TARGET_STRING("SILS_201704211/Sensors/NSAS5/noise"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 134, TARGET_STRING("SILS_201704211/Sensors/NSAS5/noise1"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 135, TARGET_STRING("SILS_201704211/Sensors/NSAS6/Normalize Vector"),
    TARGET_STRING("maxzero"), 0, 0, 0 },

  { 136, TARGET_STRING("SILS_201704211/Sensors/NSAS6/z>0"),
    TARGET_STRING("const"), 0, 0, 0 },

  { 137, TARGET_STRING("SILS_201704211/Sensors/NSAS6/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 138, TARGET_STRING("SILS_201704211/Sensors/NSAS6/Constant1"),
    TARGET_STRING("Value"), 0, 2, 0 },

  { 139, TARGET_STRING("SILS_201704211/Sensors/NSAS6/Constant2"),
    TARGET_STRING("Value"), 0, 5, 0 },

  { 140, TARGET_STRING("SILS_201704211/Sensors/NSAS6/rad2deg"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 141, TARGET_STRING("SILS_201704211/Sensors/NSAS6/noise"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 142, TARGET_STRING("SILS_201704211/Sensors/NSAS6/noise1"),
    TARGET_STRING("Mean"), 0, 0, 0 },

  { 143, TARGET_STRING("SILS_201704211/Sensors/STT1/Constant"),
    TARGET_STRING("Value"), 0, 1, 0 },

  { 144, TARGET_STRING("SILS_201704211/Sensors/STT1/Constant2"),
    TARGET_STRING("Value"), 0, 1, 0 },

  { 145, TARGET_STRING("SILS_201704211/Sensors/STT1/Uniform Random Number"),
    TARGET_STRING("Minimum"), 0, 0, 0 },

  { 146, TARGET_STRING("SILS_201704211/Sensors/STT1/Uniform Random Number"),
    TARGET_STRING("Maximum"), 0, 0, 0 },

  { 147, TARGET_STRING("SILS_201704211/Sensors/STT1/Uniform Random Number"),
    TARGET_STRING("Seed"), 0, 0, 0 },

  { 148, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 149, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Constant1"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 150, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Constant2"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 151, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Constant3"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 152, TARGET_STRING("SILS_201704211/three_one_skew/RW1/loss torque (propotion to ƒÖ)"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 153, TARGET_STRING("SILS_201704211/three_one_skew/RW1/rad2rpm"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 154, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Integrator"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 155, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Switch"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 156, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Switch1"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 157, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Switch2"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 158, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Transfer Fcn1"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 159, TARGET_STRING("SILS_201704211/three_one_skew/RW1/Transfer Fcn1"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 160, TARGET_STRING("SILS_201704211/three_one_skew/RW1/motor"),
    TARGET_STRING("D"), 0, 0, 0 },

  { 161, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 162, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Constant1"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 163, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Constant2"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 164, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Constant3"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 165, TARGET_STRING("SILS_201704211/three_one_skew/RW2/loss torque (propotion to ƒÖ)"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 166, TARGET_STRING("SILS_201704211/three_one_skew/RW2/rad2rpm"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 167, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Integrator"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 168, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Switch"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 169, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Switch1"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 170, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Switch2"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 171, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Transfer Fcn1"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 172, TARGET_STRING("SILS_201704211/three_one_skew/RW2/Transfer Fcn1"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 173, TARGET_STRING("SILS_201704211/three_one_skew/RW2/motor"),
    TARGET_STRING("D"), 0, 0, 0 },

  { 174, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 175, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Constant1"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 176, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Constant2"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 177, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Constant3"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 178, TARGET_STRING("SILS_201704211/three_one_skew/RW3/loss torque (propotion to ƒÖ)"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 179, TARGET_STRING("SILS_201704211/three_one_skew/RW3/rad2rpm"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 180, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Integrator"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 181, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Switch"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 182, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Switch1"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 183, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Switch2"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 184, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Transfer Fcn1"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 185, TARGET_STRING("SILS_201704211/three_one_skew/RW3/Transfer Fcn1"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 186, TARGET_STRING("SILS_201704211/three_one_skew/RW3/motor"),
    TARGET_STRING("D"), 0, 0, 0 },

  { 187, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 188, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Constant1"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 189, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Constant2"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 190, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Constant3"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 191, TARGET_STRING("SILS_201704211/three_one_skew/RW4/loss torque (propotion to ƒÖ)"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 192, TARGET_STRING("SILS_201704211/three_one_skew/RW4/rad2rpm"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 193, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Integrator"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 194, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Switch"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 195, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Switch1"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 196, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Switch2"),
    TARGET_STRING("Threshold"), 0, 0, 0 },

  { 197, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Transfer Fcn1"),
    TARGET_STRING("A"), 0, 0, 0 },

  { 198, TARGET_STRING("SILS_201704211/three_one_skew/RW4/Transfer Fcn1"),
    TARGET_STRING("C"), 0, 0, 0 },

  { 199, TARGET_STRING("SILS_201704211/three_one_skew/RW4/motor"),
    TARGET_STRING("D"), 0, 0, 0 },

  { 200, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/nrlmsise-00 simple/F107"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 201, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/nrlmsise-00 simple/aph"),
    TARGET_STRING("Value"), 0, 6, 0 },

  { 202, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/nrlmsise-00 simple/flag"),
    TARGET_STRING("Value"), 0, 7, 0 },

  { 203, TARGET_STRING("SILS_201704211/Environment&Dynamics/Direction Cosine Matrix ECEF to NED/A23/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 204, TARGET_STRING("SILS_201704211/Environment&Dynamics/OrbitalDynamics/calc_q/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 205, TARGET_STRING("SILS_201704211/Environment&Dynamics/OrbitalDynamics/calc_q/Constant1"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 206, TARGET_STRING("SILS_201704211/Environment&Dynamics/OrbitalDynamics/calc_q/Constant2"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 207, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V1/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 208, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V1/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 209, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V1/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 210, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V1/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 211, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V2/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 212, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V2/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 213, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V2/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 214, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V2/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 215, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V3/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 216, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V3/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 217, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V3/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 218, TARGET_STRING("SILS_201704211/Environment&Dynamics/Quaternion Rotation/V3/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 219, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 220, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 221, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 222, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 223, TARGET_STRING("SILS_201704211/Sensors/GPS/GPS_R/Random Number"),
    TARGET_STRING("Mean"), 0, 1, 0 },

  { 224, TARGET_STRING("SILS_201704211/Sensors/GPS/GPS_R/Random Number"),
    TARGET_STRING("StdDev"), 0, 1, 0 },

  { 225, TARGET_STRING("SILS_201704211/Sensors/GPS/GPS_R/noise3"),
    TARGET_STRING("Minimum"), 0, 0, 0 },

  { 226, TARGET_STRING("SILS_201704211/Sensors/GPS/GPS_R/ECEF Position to LLA"),
    TARGET_STRING("F"), 0, 0, 0 },

  { 227, TARGET_STRING("SILS_201704211/Sensors/GPS/GPS_R/ECEF Position to LLA"),
    TARGET_STRING("R"), 0, 0, 0 },

  { 228, TARGET_STRING("SILS_201704211/Sensors/NSAS1/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 229, TARGET_STRING("SILS_201704211/Sensors/NSAS2/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 230, TARGET_STRING("SILS_201704211/Sensors/NSAS3/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 231, TARGET_STRING("SILS_201704211/Sensors/NSAS4/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 232, TARGET_STRING("SILS_201704211/Sensors/NSAS5/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 233, TARGET_STRING("SILS_201704211/Sensors/NSAS6/Normalize Vector/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 234, TARGET_STRING("SILS_201704211/Sensors/Quaternions to  Direction Cosine Matrix/A12/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 235, TARGET_STRING("SILS_201704211/Sensors/Quaternions to  Direction Cosine Matrix/A13/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 236, TARGET_STRING("SILS_201704211/Sensors/Quaternions to  Direction Cosine Matrix/A21/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 237, TARGET_STRING("SILS_201704211/Sensors/Quaternions to  Direction Cosine Matrix/A23/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 238, TARGET_STRING("SILS_201704211/Sensors/Quaternions to  Direction Cosine Matrix/A31/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 239, TARGET_STRING("SILS_201704211/Sensors/Quaternions to  Direction Cosine Matrix/A32/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 240, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V1/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 241, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V1/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 242, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V1/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 243, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V1/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 244, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V2/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 245, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V2/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 246, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V2/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 247, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V2/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 248, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V3/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 249, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V3/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 250, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V3/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 251, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/Quaternion Rotation2/V3/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 252, TARGET_STRING("SILS_201704211/Environment&Dynamics/Air Drag/nrlmsise-00 simple/nrlmsise-00 full/g//cm^3->kg//m^3"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 253, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V1/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 254, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V1/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 255, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V1/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 256, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V1/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 257, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V2/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 258, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V2/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 259, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V2/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 260, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V2/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 261, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V3/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 262, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V3/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 263, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V3/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 264, TARGET_STRING("SILS_201704211/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V3/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 265, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V1/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 266, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V1/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 267, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V1/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 268, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V1/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 269, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V2/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 270, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V2/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 271, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V2/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 272, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V2/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 273, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V3/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 274, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V3/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 275, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V3/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 276, TARGET_STRING("SILS_201704211/Environment&Dynamics/SRP/Quaternion Rotation2/V3/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 277, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V1/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 278, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V1/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 279, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V1/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 280, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V1/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 281, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V2/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 282, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V2/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 283, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V2/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 284, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V2/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 285, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V3/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 286, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V3/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 287, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V3/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 288, TARGET_STRING("SILS_201704211/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V3/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 289, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V1/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 290, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V1/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 291, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V1/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 292, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V1/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 293, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V2/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 294, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V2/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 295, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V2/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 296, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V2/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 297, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V3/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 298, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V3/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 299, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V3/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 300, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V3/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 301, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V1/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 302, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V1/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 303, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V1/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 304, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V1/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 305, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V2/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 306, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V2/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 307, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V2/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 308, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V2/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 309, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V3/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 310, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V3/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 311, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V3/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 312, TARGET_STRING("SILS_201704211/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V3/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

static const rtwCAPI_Signals rtRootInputs[] = {

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

static const rtwCAPI_Signals rtRootOutputs[] = {

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

static const rtwCAPI_ModelParameters rtModelParameters[] = {

  { 313, TARGET_STRING("ADSW"), 0, 0, 0 },

  { 314, TARGET_STRING("CD"), 0, 0, 0 },

  { 315, TARGET_STRING("CR"), 0, 0, 0 },

  { 316, TARGET_STRING("GAS_Vref"), 0, 0, 0 },

  { 317, TARGET_STRING("GAS_b2c"), 0, 8, 0 },

  { 318, TARGET_STRING("GAS_seed1"), 0, 1, 0 },

  { 319, TARGET_STRING("GE"), 0, 0, 0 },

  { 320, TARGET_STRING("GGSW"), 0, 0, 0 },

  { 321, TARGET_STRING("GPS_position_seed"), 0, 1, 0 },

  { 322, TARGET_STRING("GPS_time_noise"), 0, 0, 0 },

  { 323, TARGET_STRING("GPS_time_seed"), 0, 0, 0 },

  { 324, TARGET_STRING("GPperturbationSW"), 0, 0, 0 },

  { 325, TARGET_STRING("GYRO_b2c"), 0, 8, 0 },

  { 326, TARGET_STRING("GYRO_seed1"), 0, 1, 0 },

  { 327, TARGET_STRING("GYRO_seed2"), 0, 1, 0 },

  { 328, TARGET_STRING("I"), 0, 8, 0 },

  { 329, TARGET_STRING("J2"), 0, 0, 0 },

  { 330, TARGET_STRING("MTQ_c2b"), 0, 2, 0 },

  { 331, TARGET_STRING("NSAS1_b2c"), 0, 8, 0 },

  { 332, TARGET_STRING("NSAS2_b2c"), 0, 8, 0 },

  { 333, TARGET_STRING("NSAS3_b2c"), 0, 8, 0 },

  { 334, TARGET_STRING("NSAS4_b2c"), 0, 8, 0 },

  { 335, TARGET_STRING("NSAS5_b2c"), 0, 8, 0 },

  { 336, TARGET_STRING("NSAS6_b2c"), 0, 8, 0 },

  { 337, TARGET_STRING("NSAS_ang_limit"), 0, 0, 0 },

  { 338, TARGET_STRING("NSAS_seed1"), 0, 0, 0 },

  { 339, TARGET_STRING("NSAS_seed2"), 0, 0, 0 },

  { 340, TARGET_STRING("NSAS_x_noise"), 0, 0, 0 },

  { 341, TARGET_STRING("NSAS_y_noise"), 0, 0, 0 },

  { 342, TARGET_STRING("RW_Gamp"), 0, 0, 0 },

  { 343, TARGET_STRING("RW_J"), 0, 0, 0 },

  { 344, TARGET_STRING("RW_Rsc"), 0, 0, 0 },

  { 345, TARGET_STRING("RW_kE"), 0, 0, 0 },

  { 346, TARGET_STRING("RW_kT"), 0, 0, 0 },

  { 347, TARGET_STRING("SRPSW"), 0, 0, 0 },

  { 348, TARGET_STRING("STT1_b2c_quat"), 0, 3, 0 },

  { 349, TARGET_STRING("STT_AD_prob"), 0, 0, 0 },

  { 350, TARGET_STRING("STT_FOV"), 0, 0, 0 },

  { 351, TARGET_STRING("STT_moon_ang_limit"), 0, 0, 0 },

  { 352, TARGET_STRING("STT_seed1"), 0, 1, 0 },

  { 353, TARGET_STRING("STT_sun_ang_limit"), 0, 0, 0 },

  { 354, TARGET_STRING("TOLERANCE"), 0, 0, 0 },

  { 355, TARGET_STRING("UT1_UTC"), 0, 0, 0 },

  { 356, TARGET_STRING("area"), 0, 0, 0 },

  { 357, TARGET_STRING("arm"), 0, 2, 0 },

  { 358, TARGET_STRING("earth_radius"), 0, 0, 0 },

  { 359, TARGET_STRING("ele"), 0, 9, 0 },

  { 360, TARGET_STRING("jd"), 0, 0, 0 },

  { 361, TARGET_STRING("pSR"), 0, 0, 0 },

  { 362, TARGET_STRING("q_ini"), 0, 3, 0 },

  { 363, TARGET_STRING("rem_mag"), 0, 2, 0 },

  { 364, TARGET_STRING("rem_magSW"), 0, 0, 0 },

  { 365, TARGET_STRING("three_one_skew_matrix"), 0, 10, 0 },

  { 366, TARGET_STRING("wE"), 0, 2, 0 },

  { 367, TARGET_STRING("w_ini"), 0, 1, 0 },

  { 0, (NULL), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

static void* rtDataAddrMap[] = {
  &SILS_201704211_P.Constant1_Value_i,
  &SILS_201704211_P.Constant2_Value_f,
  &SILS_201704211_P.Constant3_Value_m,
  &SILS_201704211_P.Constant6_Value,
  &SILS_201704211_P.reactiontorque_Gain,
  &SILS_201704211_P.SFunction1_P1_k,
  &SILS_201704211_P.SFunction2_P1,
  &SILS_201704211_P.SFunction3_P1,
  &SILS_201704211_P.SFunction4_P1,
  &SILS_201704211_P.SFunction5_P1,
  &SILS_201704211_P.SFunction6_P1,
  &SILS_201704211_P.SFunction7_P1,
  &SILS_201704211_P.SFunction8_P1,
  &SILS_201704211_P.SFunction9_P1,
  &SILS_201704211_P.km2m_Gain,
  &SILS_201704211_P.m2km_Gain,
  &SILS_201704211_P.ECEFPositiontoLLA_F,
  &SILS_201704211_P.ECEFPositiontoLLA_R,
  &SILS_201704211_P.nT_2_T_Gain,
  &SILS_201704211_P.Constant1_Value_lw,
  &SILS_201704211_P.Constant12_Value,
  &SILS_201704211_P.Constant15_Value,
  &SILS_201704211_P.Constant2_Value_j,
  &SILS_201704211_P.Constant3_Value_e,
  &SILS_201704211_P.Constant4_Value,
  &SILS_201704211_P.Constant5_Value,
  &SILS_201704211_P.Constant6_Value_o,
  &SILS_201704211_P.SFunction_P1,
  &SILS_201704211_P.SFunction_P2,
  &SILS_201704211_P.SFunction1_P1,
  &SILS_201704211_P.SFunction2_P1_p,
  &SILS_201704211_P.SFunction2_P2,
  &SILS_201704211_P.SFunction3_P1_f,
  &SILS_201704211_P.SFunction3_P2,
  &SILS_201704211_P.SFunction4_P1_j,
  &SILS_201704211_P.SFunction4_P2,
  &SILS_201704211_P.SFunction5_P1_i,
  &SILS_201704211_P.SFunction6_P1_c,
  &SILS_201704211_P.SFunction6_P2,
  &SILS_201704211_P.SFunction7_P1_c,
  &SILS_201704211_P.SFunction7_P2,
  &SILS_201704211_P.SFunction8_P1_d,
  &SILS_201704211_P.SFunction8_P2,
  &SILS_201704211_P.SFunction9_P1_n,
  &SILS_201704211_P.SFunction9_P2,
  &SILS_201704211_P.km2m_Gain_c,
  &SILS_201704211_P.rad2deg_Gain_i,
  &SILS_201704211_P.noise1_Mean[0],
  &SILS_201704211_P.noise1_StdDev[0],
  &SILS_201704211_P.rpm2rad_Gain,
  &SILS_201704211_P.rpm2rad1_Gain,
  &SILS_201704211_P.rpm2rad2_Gain,
  &SILS_201704211_P.rpm2rad3_Gain,
  &SILS_201704211_P.hour2sec_Gain,
  &SILS_201704211_P.min2sec_Gain,
  &SILS_201704211_P.sec_per_day_Gain,
  &SILS_201704211_P.GPperturbation_RSW_kms2_3_Y0[0],
  &SILS_201704211_P.deg2rad_Gain,
  &SILS_201704211_P.GG_b_Nm_3_Y0[0],
  &SILS_201704211_P.remmag_b_Nm_3_Y0[0],
  &SILS_201704211_P.nT2T_Gain,
  &SILS_201704211_P.IC_Value[0],
  &SILS_201704211_P.IC1_Value[0],
  &SILS_201704211_P.SRP_b_Nm_3_Y0[0],
  &SILS_201704211_P.NormalizeVector_maxzero,
  &SILS_201704211_P.NormalizeVector_maxzero_p,
  &SILS_201704211_P.Gain_Gain_c5,
  &SILS_201704211_P.NormalizeVector_maxzero_l,
  &SILS_201704211_P.NormalizeVector_maxzero_j,
  &SILS_201704211_P.TransferFcn_A_a,
  &SILS_201704211_P.TransferFcn_C_k,
  &SILS_201704211_P.TransferFcn_A_g,
  &SILS_201704211_P.TransferFcn_C_n,
  &SILS_201704211_P.TransferFcn_A_ax,
  &SILS_201704211_P.TransferFcn_C_c3,
  &SILS_201704211_P.noise_Mean_m[0],
  &SILS_201704211_P.noise_StdDev[0],
  &SILS_201704211_P.TransferFcn_A_c,
  &SILS_201704211_P.TransferFcn_C_c,
  &SILS_201704211_P.TransferFcn1_A_l,
  &SILS_201704211_P.TransferFcn1_C_b,
  &SILS_201704211_P.TransferFcn2_A_p,
  &SILS_201704211_P.TransferFcn2_C_f,
  &SILS_201704211_P.b0degsec_Value[0],
  &SILS_201704211_P.Integrator_IC_f,
  &SILS_201704211_P.nudegsec2_Mean[0],
  &SILS_201704211_P.nudegsec2_StdDev[0],
  &SILS_201704211_P.nvdegsec_Mean[0],
  &SILS_201704211_P.nvdegsec_StdDev[0],
  &SILS_201704211_P.TransferFcn_A[0],
  &SILS_201704211_P.TransferFcn_C[0],
  &SILS_201704211_P.TransferFcn1_A_if[0],
  &SILS_201704211_P.TransferFcn1_C_d[0],
  &SILS_201704211_P.TransferFcn2_A[0],
  &SILS_201704211_P.TransferFcn2_C[0],
  &SILS_201704211_P.NormalizeVector_maxzero_pk,
  &SILS_201704211_P.z0_const,
  &SILS_201704211_P.Constant_Value_hm,
  &SILS_201704211_P.Constant1_Value_a[0],
  &SILS_201704211_P.Constant2_Value_ge[0],
  &SILS_201704211_P.rad2deg_Gain,
  &SILS_201704211_P.noise_Mean,
  &SILS_201704211_P.noise1_Mean_g,
  &SILS_201704211_P.NormalizeVector_maxzero_m,
  &SILS_201704211_P.z0_const_m,
  &SILS_201704211_P.Constant_Value_hu,
  &SILS_201704211_P.Constant1_Value_e[0],
  &SILS_201704211_P.Constant2_Value_c[0],
  &SILS_201704211_P.rad2deg_Gain_l,
  &SILS_201704211_P.noise_Mean_i,
  &SILS_201704211_P.noise1_Mean_d,
  &SILS_201704211_P.NormalizeVector_maxzero_h,
  &SILS_201704211_P.z0_const_g,
  &SILS_201704211_P.Constant_Value_nd,
  &SILS_201704211_P.Constant1_Value_l[0],
  &SILS_201704211_P.Constant2_Value_gn[0],
  &SILS_201704211_P.rad2deg_Gain_a,
  &SILS_201704211_P.noise_Mean_f,
  &SILS_201704211_P.noise1_Mean_m,
  &SILS_201704211_P.NormalizeVector_maxzero_n,
  &SILS_201704211_P.z0_const_o,
  &SILS_201704211_P.Constant_Value_gh,
  &SILS_201704211_P.Constant1_Value_j0[0],
  &SILS_201704211_P.Constant2_Value_a[0],
  &SILS_201704211_P.rad2deg_Gain_o,
  &SILS_201704211_P.noise_Mean_g,
  &SILS_201704211_P.noise1_Mean_k,
  &SILS_201704211_P.NormalizeVector_maxzero_lt,
  &SILS_201704211_P.z0_const_h,
  &SILS_201704211_P.Constant_Value_e,
  &SILS_201704211_P.Constant1_Value_g[0],
  &SILS_201704211_P.Constant2_Value_k[0],
  &SILS_201704211_P.rad2deg_Gain_c,
  &SILS_201704211_P.noise_Mean_fj,
  &SILS_201704211_P.noise1_Mean_j,
  &SILS_201704211_P.NormalizeVector_maxzero_b,
  &SILS_201704211_P.z0_const_p,
  &SILS_201704211_P.Constant_Value_ib,
  &SILS_201704211_P.Constant1_Value_n[0],
  &SILS_201704211_P.Constant2_Value_n[0],
  &SILS_201704211_P.rad2deg_Gain_n,
  &SILS_201704211_P.noise_Mean_h,
  &SILS_201704211_P.noise1_Mean_m2,
  &SILS_201704211_P.Constant_Value_i[0],
  &SILS_201704211_P.Constant2_Value_g[0],
  &SILS_201704211_P.UniformRandomNumber_Minimum,
  &SILS_201704211_P.UniformRandomNumber_Maximum,
  &SILS_201704211_P.UniformRandomNumber_Seed,
  &SILS_201704211_P.Constant_Value_g3,
  &SILS_201704211_P.Constant1_Value_h,
  &SILS_201704211_P.Constant2_Value,
  &SILS_201704211_P.Constant3_Value,
  &SILS_201704211_P.losstorquepropotionto_Gain,
  &SILS_201704211_P.rad2rpm_Gain_l,
  &SILS_201704211_P.Integrator_IC_m,
  &SILS_201704211_P.Switch_Threshold,
  &SILS_201704211_P.Switch1_Threshold_g,
  &SILS_201704211_P.Switch2_Threshold_f,
  &SILS_201704211_P.TransferFcn1_A_d,
  &SILS_201704211_P.TransferFcn1_C_m,
  &SILS_201704211_P.motor_D_c,
  &SILS_201704211_P.Constant_Value_ov,
  &SILS_201704211_P.Constant1_Value,
  &SILS_201704211_P.Constant2_Value_p,
  &SILS_201704211_P.Constant3_Value_d,
  &SILS_201704211_P.losstorquepropotionto_Gain_h,
  &SILS_201704211_P.rad2rpm_Gain,
  &SILS_201704211_P.Integrator_IC,
  &SILS_201704211_P.Switch_Threshold_a,
  &SILS_201704211_P.Switch1_Threshold,
  &SILS_201704211_P.Switch2_Threshold,
  &SILS_201704211_P.TransferFcn1_A,
  &SILS_201704211_P.TransferFcn1_C,
  &SILS_201704211_P.motor_D,
  &SILS_201704211_P.Constant_Value_br,
  &SILS_201704211_P.Constant1_Value_j,
  &SILS_201704211_P.Constant2_Value_l,
  &SILS_201704211_P.Constant3_Value_p,
  &SILS_201704211_P.losstorquepropotionto_Gain_f,
  &SILS_201704211_P.rad2rpm_Gain_n,
  &SILS_201704211_P.Integrator_IC_h,
  &SILS_201704211_P.Switch_Threshold_e,
  &SILS_201704211_P.Switch1_Threshold_l,
  &SILS_201704211_P.Switch2_Threshold_f3,
  &SILS_201704211_P.TransferFcn1_A_i,
  &SILS_201704211_P.TransferFcn1_C_e,
  &SILS_201704211_P.motor_D_p,
  &SILS_201704211_P.Constant_Value_ki,
  &SILS_201704211_P.Constant1_Value_b,
  &SILS_201704211_P.Constant2_Value_o,
  &SILS_201704211_P.Constant3_Value_i,
  &SILS_201704211_P.losstorquepropotionto_Gain_k,
  &SILS_201704211_P.rad2rpm_Gain_p,
  &SILS_201704211_P.Integrator_IC_l,
  &SILS_201704211_P.Switch_Threshold_m,
  &SILS_201704211_P.Switch1_Threshold_n,
  &SILS_201704211_P.Switch2_Threshold_fn,
  &SILS_201704211_P.TransferFcn1_A_b,
  &SILS_201704211_P.TransferFcn1_C_ex,
  &SILS_201704211_P.motor_D_n,
  &SILS_201704211_P.F107_Value,
  &SILS_201704211_P.aph_Value[0],
  &SILS_201704211_P.flag_Value[0],
  &SILS_201704211_P.Constant_Value_ns,
  &SILS_201704211_P.Constant_Value_ic,
  &SILS_201704211_P.Constant1_Value_o,
  &SILS_201704211_P.Constant2_Value_e,
  &SILS_201704211_P.Constant_Value_am,
  &SILS_201704211_P.Gain_Gain_ky,
  &SILS_201704211_P.Gain1_Gain_jd,
  &SILS_201704211_P.Gain2_Gain_m,
  &SILS_201704211_P.Constant_Value_mq,
  &SILS_201704211_P.Gain_Gain_a,
  &SILS_201704211_P.Gain1_Gain_h,
  &SILS_201704211_P.Gain2_Gain_bo,
  &SILS_201704211_P.Constant_Value_kc,
  &SILS_201704211_P.Gain_Gain_du,
  &SILS_201704211_P.Gain1_Gain_cj,
  &SILS_201704211_P.Gain2_Gain_cy,
  &SILS_201704211_P.Constant_Value_n,
  &SILS_201704211_P.Constant_Value_gg,
  &SILS_201704211_P.Constant_Value_kx,
  &SILS_201704211_P.Constant_Value_kg,
  &SILS_201704211_P.RandomNumber_Mean[0],
  &SILS_201704211_P.RandomNumber_StdDev[0],
  &SILS_201704211_P.noise3_Minimum,
  &SILS_201704211_P.ECEFPositiontoLLA_F_h,
  &SILS_201704211_P.ECEFPositiontoLLA_R_d,
  &SILS_201704211_P.Constant_Value_l,
  &SILS_201704211_P.Constant_Value_m2,
  &SILS_201704211_P.Constant_Value_iq,
  &SILS_201704211_P.Constant_Value_f,
  &SILS_201704211_P.Constant_Value_fn,
  &SILS_201704211_P.Constant_Value_k3,
  &SILS_201704211_P.Gain_Gain_ji,
  &SILS_201704211_P.Gain_Gain_g,
  &SILS_201704211_P.Gain_Gain_o,
  &SILS_201704211_P.Gain_Gain_gd,
  &SILS_201704211_P.Gain_Gain_j,
  &SILS_201704211_P.Gain_Gain_i,
  &SILS_201704211_P.Constant_Value,
  &SILS_201704211_P.Gain_Gain,
  &SILS_201704211_P.Gain1_Gain,
  &SILS_201704211_P.Gain2_Gain,
  &SILS_201704211_P.Constant_Value_k,
  &SILS_201704211_P.Gain_Gain_d,
  &SILS_201704211_P.Gain1_Gain_e,
  &SILS_201704211_P.Gain2_Gain_l,
  &SILS_201704211_P.Constant_Value_a,
  &SILS_201704211_P.Gain_Gain_k,
  &SILS_201704211_P.Gain1_Gain_o,
  &SILS_201704211_P.Gain2_Gain_e,
  &SILS_201704211_P.gcm3kgm3_Gain,
  &SILS_201704211_P.Constant_Value_p,
  &SILS_201704211_P.Gain_Gain_e,
  &SILS_201704211_P.Gain1_Gain_o0,
  &SILS_201704211_P.Gain2_Gain_n,
  &SILS_201704211_P.Constant_Value_b,
  &SILS_201704211_P.Gain_Gain_c,
  &SILS_201704211_P.Gain1_Gain_k,
  &SILS_201704211_P.Gain2_Gain_j,
  &SILS_201704211_P.Constant_Value_g,
  &SILS_201704211_P.Gain_Gain_l,
  &SILS_201704211_P.Gain1_Gain_p,
  &SILS_201704211_P.Gain2_Gain_na,
  &SILS_201704211_P.Constant_Value_c,
  &SILS_201704211_P.Gain_Gain_kp,
  &SILS_201704211_P.Gain1_Gain_k3,
  &SILS_201704211_P.Gain2_Gain_p,
  &SILS_201704211_P.Constant_Value_o,
  &SILS_201704211_P.Gain_Gain_b,
  &SILS_201704211_P.Gain1_Gain_g,
  &SILS_201704211_P.Gain2_Gain_g,
  &SILS_201704211_P.Constant_Value_d,
  &SILS_201704211_P.Gain_Gain_b0,
  &SILS_201704211_P.Gain1_Gain_i,
  &SILS_201704211_P.Gain2_Gain_p5,
  &SILS_201704211_P.Constant_Value_kb,
  &SILS_201704211_P.Gain_Gain_f,
  &SILS_201704211_P.Gain1_Gain_c,
  &SILS_201704211_P.Gain2_Gain_f,
  &SILS_201704211_P.Constant_Value_hg,
  &SILS_201704211_P.Gain_Gain_cu,
  &SILS_201704211_P.Gain1_Gain_p0,
  &SILS_201704211_P.Gain2_Gain_o,
  &SILS_201704211_P.Constant_Value_j,
  &SILS_201704211_P.Gain_Gain_m,
  &SILS_201704211_P.Gain1_Gain_f,
  &SILS_201704211_P.Gain2_Gain_ek,
  &SILS_201704211_P.Constant_Value_cz,
  &SILS_201704211_P.Gain_Gain_l1,
  &SILS_201704211_P.Gain1_Gain_b,
  &SILS_201704211_P.Gain2_Gain_c,
  &SILS_201704211_P.Constant_Value_h,
  &SILS_201704211_P.Gain_Gain_id,
  &SILS_201704211_P.Gain1_Gain_bv,
  &SILS_201704211_P.Gain2_Gain_k,
  &SILS_201704211_P.Constant_Value_bu,
  &SILS_201704211_P.Gain_Gain_p,
  &SILS_201704211_P.Gain1_Gain_j,
  &SILS_201704211_P.Gain2_Gain_d,
  &SILS_201704211_P.Constant_Value_ck,
  &SILS_201704211_P.Gain_Gain_p0,
  &SILS_201704211_P.Gain1_Gain_l,
  &SILS_201704211_P.Gain2_Gain_b,
  &SILS_201704211_P.Constant_Value_jd,
  &SILS_201704211_P.Gain_Gain_cd,
  &SILS_201704211_P.Gain1_Gain_m,
  &SILS_201704211_P.Gain2_Gain_i,
  &SILS_201704211_P.Constant_Value_m,
  &SILS_201704211_P.Gain_Gain_gn,
  &SILS_201704211_P.Gain1_Gain_a,
  &SILS_201704211_P.Gain2_Gain_a,
  &SILS_201704211_P.ADSW,
  &SILS_201704211_P.CD,
  &SILS_201704211_P.CR,
  &SILS_201704211_P.GAS_Vref,
  &SILS_201704211_P.GAS_b2c[0],
  &SILS_201704211_P.GAS_seed1[0],
  &SILS_201704211_P.GE,
  &SILS_201704211_P.GGSW,
  &SILS_201704211_P.GPS_position_seed[0],
  &SILS_201704211_P.GPS_time_noise,
  &SILS_201704211_P.GPS_time_seed,
  &SILS_201704211_P.GPperturbationSW,
  &SILS_201704211_P.GYRO_b2c[0],
  &SILS_201704211_P.GYRO_seed1[0],
  &SILS_201704211_P.GYRO_seed2[0],
  &SILS_201704211_P.I[0],
  &SILS_201704211_P.J2,
  &SILS_201704211_P.MTQ_c2b[0],
  &SILS_201704211_P.NSAS1_b2c[0],
  &SILS_201704211_P.NSAS2_b2c[0],
  &SILS_201704211_P.NSAS3_b2c[0],
  &SILS_201704211_P.NSAS4_b2c[0],
  &SILS_201704211_P.NSAS5_b2c[0],
  &SILS_201704211_P.NSAS6_b2c[0],
  &SILS_201704211_P.NSAS_ang_limit,
  &SILS_201704211_P.NSAS_seed1,
  &SILS_201704211_P.NSAS_seed2,
  &SILS_201704211_P.NSAS_x_noise,
  &SILS_201704211_P.NSAS_y_noise,
  &SILS_201704211_P.RW_Gamp,
  &SILS_201704211_P.RW_J,
  &SILS_201704211_P.RW_Rsc,
  &SILS_201704211_P.RW_kE,
  &SILS_201704211_P.RW_kT,
  &SILS_201704211_P.SRPSW,
  &SILS_201704211_P.STT1_b2c_quat[0],
  &SILS_201704211_P.STT_AD_prob,
  &SILS_201704211_P.STT_FOV,
  &SILS_201704211_P.STT_moon_ang_limit,
  &SILS_201704211_P.STT_seed1[0],
  &SILS_201704211_P.STT_sun_ang_limit,
  &SILS_201704211_P.TOLERANCE,
  &SILS_201704211_P.UT1_UTC,
  &SILS_201704211_P.area,
  &SILS_201704211_P.arm[0],
  &SILS_201704211_P.earth_radius,
  &SILS_201704211_P.ele[0],
  &SILS_201704211_P.jd,
  &SILS_201704211_P.pSR,
  &SILS_201704211_P.q_ini[0],
  &SILS_201704211_P.rem_mag[0],
  &SILS_201704211_P.rem_magSW,
  &SILS_201704211_P.three_one_skew_matrix[0],
  &SILS_201704211_P.wE[0],
  &SILS_201704211_P.w_ini[0],
};

static int32_T* rtVarDimsAddrMap[] = {
  (NULL)
};

#endif

static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {

  { "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {

  { (NULL), 0, 0, 0, 0 },
};

static const rtwCAPI_DimensionMap rtDimensionMap[] = {

  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 },

  { rtwCAPI_VECTOR, 4, 2, 0 },

  { rtwCAPI_VECTOR, 6, 2, 0 },

  { rtwCAPI_VECTOR, 8, 2, 0 },

  { rtwCAPI_VECTOR, 10, 2, 0 },

  { rtwCAPI_VECTOR, 12, 2, 0 },

  { rtwCAPI_VECTOR, 14, 2, 0 },

  { rtwCAPI_MATRIX_COL_MAJOR, 16, 2, 0 },

  { rtwCAPI_VECTOR, 18, 2, 0 },

  { rtwCAPI_MATRIX_COL_MAJOR, 20, 2, 0 }
};

static const uint_T rtDimensionArray[] = {
  1,
  1,
  1,
  3,
  3,
  1,
  1,
  4,
  2,
  1,
  1,
  2,
  1,
  7,
  1,
  23,
  3,
  3,
  1,
  6,
  3,
  4
};

static const rtwCAPI_FixPtMap rtFixPtMap[] = {

  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, 0 },
};

static const rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {

  {
    (NULL), (NULL), 0, 0
  }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {

  { (NULL), 0,
    rtRootInputs, 0,
    rtRootOutputs, 0 },

  { rtBlockParameters, 313,
    rtModelParameters, 55 },

  { (NULL), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 647963715U,
    720395599U,
    1319951311U,
    2261731908U },
  (NULL), 0,
  0
};

const rtwCAPI_ModelMappingStaticInfo*
  SILS_201704211_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

#ifndef HOST_CAPI_BUILD

void SILS_201704211_InitializeDataMapInfo(void)
{
  rtwCAPI_SetVersion(SILS_201704211_M->DataMapInfo.mmi, 1);
  rtwCAPI_SetStaticMap(SILS_201704211_M->DataMapInfo.mmi, &mmiStatic);
  rtwCAPI_SetLoggingStaticMap(SILS_201704211_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetDataAddressMap(SILS_201704211_M->DataMapInfo.mmi, rtDataAddrMap);
  rtwCAPI_SetVarDimsAddressMap(SILS_201704211_M->DataMapInfo.mmi,
    rtVarDimsAddrMap);
  rtwCAPI_SetInstanceLoggingInfo(SILS_201704211_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArray(SILS_201704211_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(SILS_201704211_M->DataMapInfo.mmi, 0);
}

#else
#ifdef __cplusplus

extern "C" {

#endif

  void SILS_201704211_host_InitializeDataMapInfo
    (SILS_201704211_host_DataMapInfo_T *dataMap, const char *path)
  {
    rtwCAPI_SetVersion(dataMap->mmi, 1);
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);
    rtwCAPI_SetDataAddressMap(dataMap->mmi, NULL);
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, NULL);
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, NULL);
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}
#endif
#endif

