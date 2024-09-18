#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "SILS_20241709_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 17
#endif
#ifndef SS_INT64
#define SS_INT64 18
#endif
#else
#include "builtin_typeid_types.h"
#include "SILS_20241709.h"
#include "SILS_20241709_capi.h"
#include "SILS_20241709_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 1 , TARGET_STRING (
"SILS_20241709/Angular Rate" ) , TARGET_STRING ( "outAngularRate" ) , 0 , 0 ,
0 , 0 , 0 } , { 1 , 44 , TARGET_STRING ( "SILS_20241709/MATLAB Function1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 2 , 45 , TARGET_STRING (
"SILS_20241709/MATLAB Function3" ) , TARGET_STRING ( "" ) , 0 , 0 , 1 , 0 , 0
} , { 3 , 0 , TARGET_STRING ( "SILS_20241709/Gain" ) , TARGET_STRING (
"w_b_rad_s" ) , 0 , 0 , 2 , 0 , 0 } , { 4 , 0 , TARGET_STRING (
"SILS_20241709/S-Function1" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 1 } ,
{ 5 , 0 , TARGET_STRING ( "SILS_20241709/S-Function3" ) , TARGET_STRING ( ""
) , 0 , 0 , 3 , 0 , 1 } , { 6 , 0 , TARGET_STRING (
"SILS_20241709/S-Function4" ) , TARGET_STRING ( "" ) , 0 , 0 , 3 , 0 , 1 } ,
{ 7 , 0 , TARGET_STRING ( "SILS_20241709/S-Function5" ) , TARGET_STRING ( ""
) , 0 , 0 , 3 , 0 , 1 } , { 8 , 0 , TARGET_STRING (
"SILS_20241709/S-Function6" ) , TARGET_STRING ( "" ) , 0 , 0 , 3 , 0 , 1 } ,
{ 9 , 5 , TARGET_STRING ( "SILS_20241709/Environment&Dynamics/Air Drag" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 10 , 16 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/GPperturbation" ) , TARGET_STRING ( "" )
, 0 , 0 , 2 , 0 , 0 } , { 11 , 18 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Gravity Gradient" ) , TARGET_STRING ( ""
) , 0 , 0 , 2 , 0 , 0 } , { 12 , 29 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Remnant Magnetism" ) , TARGET_STRING ( ""
) , 0 , 0 , 2 , 0 , 0 } , { 13 , 34 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP" ) , TARGET_STRING ( "" ) , 0 , 0 , 2
, 0 , 0 } , { 14 , 0 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/m2km" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 15 , 0 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/ECEF Position to LLA" ) , TARGET_STRING (
"" ) , 0 , 0 , 4 , 0 , 0 } , { 16 , 0 , TARGET_STRING (
"SILS_20241709/MTQs/Product1" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 1 }
, { 17 , 0 , TARGET_STRING ( "SILS_20241709/OBC/Clock" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 18 , 0 , TARGET_STRING (
"SILS_20241709/OBC/S-Function" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 }
, { 19 , 0 , TARGET_STRING ( "SILS_20241709/OBC/S-Function" ) , TARGET_STRING
( "" ) , 1 , 0 , 0 , 0 , 2 } , { 20 , 0 , TARGET_STRING (
"SILS_20241709/OBC/S-Function" ) , TARGET_STRING ( "" ) , 2 , 0 , 0 , 0 , 2 }
, { 21 , 0 , TARGET_STRING ( "SILS_20241709/OBC/S-Function" ) , TARGET_STRING
( "" ) , 3 , 0 , 0 , 0 , 2 } , { 22 , 0 , TARGET_STRING (
"SILS_20241709/OBC/S-Function" ) , TARGET_STRING ( "" ) , 4 , 0 , 0 , 0 , 2 }
, { 23 , 0 , TARGET_STRING ( "SILS_20241709/OBC/Zero-Order Hold" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 24 , 91 , TARGET_STRING (
"SILS_20241709/three_one_skew/Combine Torque1" ) , TARGET_STRING ( "" ) , 0 ,
0 , 2 , 0 , 0 } , { 25 , 92 , TARGET_STRING (
"SILS_20241709/three_one_skew/MATLAB Function" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 0 } , { 26 , 93 , TARGET_STRING (
"SILS_20241709/three_one_skew/MATLAB Function1" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 27 , 94 , TARGET_STRING (
"SILS_20241709/three_one_skew/MATLAB Function2" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 28 , 95 , TARGET_STRING (
"SILS_20241709/three_one_skew/MATLAB Function3" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 29 , 3 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/MATLAB Function" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 30 , 7 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Sum4" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 31 , 16 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/GPperturbation/MATLAB Function1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 32 , 18 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Gravity Gradient/MATLAB Function" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 33 , 21 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/JD2GC/MATLAB Function" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 34 , 21 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/JD2GC/MATLAB Function" ) , TARGET_STRING
( "" ) , 1 , 0 , 0 , 0 , 0 } , { 35 , 21 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/JD2GC/MATLAB Function" ) , TARGET_STRING
( "" ) , 2 , 0 , 0 , 0 , 0 } , { 36 , 21 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/JD2GC/MATLAB Function" ) , TARGET_STRING
( "" ) , 3 , 0 , 0 , 0 , 0 } , { 37 , 21 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/JD2GC/MATLAB Function" ) , TARGET_STRING
( "" ) , 4 , 0 , 0 , 0 , 0 } , { 38 , 21 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/JD2GC/MATLAB Function" ) , TARGET_STRING
( "" ) , 5 , 0 , 0 , 0 , 0 } , { 39 , 27 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/OrbitalDynamics/orbital dynamics" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 5 , 0 , 0 } , { 40 , 0 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/OrbitalDynamics/JD2" ) , TARGET_STRING (
"" ) , 0 , 0 , 5 , 0 , 1 } , { 41 , 31 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/RigidBodyDynamics/dynamics" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 3 , 0 , 0 } , { 42 , 31 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/RigidBodyDynamics/dynamics" ) ,
TARGET_STRING ( "" ) , 1 , 0 , 2 , 0 , 0 } , { 43 , 0 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/RigidBodyDynamics/IC" ) , TARGET_STRING (
"" ) , 0 , 0 , 3 , 0 , 0 } , { 44 , 0 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/RigidBodyDynamics/IC1" ) , TARGET_STRING
( "" ) , 0 , 0 , 2 , 0 , 0 } , { 45 , 37 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/multi/multi" ) , TARGET_STRING ( "" ) , 0
, 0 , 2 , 0 , 0 } , { 46 , 38 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/multi1/multi" ) , TARGET_STRING ( "" ) ,
0 , 0 , 2 , 0 , 0 } , { 47 , 39 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/multi2/multi" ) , TARGET_STRING ( "" ) ,
0 , 0 , 2 , 0 , 0 } , { 48 , 49 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/STTDataConversion/MATLAB Function3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 6 , 0 , 3 } , { 49 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/GAS/noise" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 ,
3 } , { 50 , 0 , TARGET_STRING ( "SILS_20241709/Sensors/GYRO/nu(deg//sec^2)"
) , TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 3 } , { 51 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/GYRO/nv(deg//sec)" ) , TARGET_STRING ( "" ) , 0 , 0 ,
2 , 0 , 3 } , { 52 , 0 , TARGET_STRING ( "SILS_20241709/Sensors/GYRO/Sum1" )
, TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 53 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS1/noise" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 3 } , { 54 , 0 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS1/noise1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 55 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS2/noise" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 3 } , { 56 , 0 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS2/noise1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 57 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS3/noise" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 3 } , { 58 , 0 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS3/noise1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 59 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS4/noise" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 3 } , { 60 , 0 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS4/noise1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 61 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS5/noise" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 3 } , { 62 , 0 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS5/noise1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 63 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS6/noise" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 3 } , { 64 , 0 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS6/noise1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 65 , 69 , TARGET_STRING (
"SILS_20241709/Sensors/STT1/MATLAB Function" ) , TARGET_STRING ( "" ) , 0 , 0
, 7 , 0 , 3 } , { 66 , 73 , TARGET_STRING (
"SILS_20241709/Sensors/multi/multi" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 , 0
, 0 } , { 67 , 74 , TARGET_STRING ( "SILS_20241709/Sensors/multi1/multi" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 68 , 75 , TARGET_STRING (
"SILS_20241709/Sensors/multi10/multi" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 ,
0 , 0 } , { 69 , 76 , TARGET_STRING ( "SILS_20241709/Sensors/multi11/multi" )
, TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 70 , 77 , TARGET_STRING (
"SILS_20241709/Sensors/multi12/multi" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 ,
0 , 0 } , { 71 , 78 , TARGET_STRING ( "SILS_20241709/Sensors/multi13/multi" )
, TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 72 , 79 , TARGET_STRING (
"SILS_20241709/Sensors/multi14/multi" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 ,
0 , 0 } , { 73 , 80 , TARGET_STRING ( "SILS_20241709/Sensors/multi15/multi" )
, TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 74 , 81 , TARGET_STRING (
"SILS_20241709/Sensors/multi16/multi" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 ,
0 , 0 } , { 75 , 82 , TARGET_STRING ( "SILS_20241709/Sensors/multi2/multi" )
, TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 76 , 83 , TARGET_STRING (
"SILS_20241709/Sensors/multi3/multi" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 , 0
, 0 } , { 77 , 84 , TARGET_STRING ( "SILS_20241709/Sensors/multi4/multi" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 78 , 85 , TARGET_STRING (
"SILS_20241709/Sensors/multi5/multi" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 , 0
, 0 } , { 79 , 86 , TARGET_STRING ( "SILS_20241709/Sensors/multi6/multi" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 80 , 88 , TARGET_STRING (
"SILS_20241709/Sensors/multi8/multi" ) , TARGET_STRING ( "" ) , 0 , 0 , 2 , 0
, 0 } , { 81 , 89 , TARGET_STRING ( "SILS_20241709/Sensors/multi9/multi" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 82 , 96 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/MATLAB Function" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 83 , 96 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/MATLAB Function" ) , TARGET_STRING ( "" ) ,
1 , 0 , 0 , 0 , 0 } , { 84 , 96 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/MATLAB Function" ) , TARGET_STRING ( "" ) ,
2 , 0 , 0 , 0 , 0 } , { 85 , 97 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/MATLAB Function1" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 86 , 98 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/MATLAB Function2" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 87 , 98 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/MATLAB Function2" ) , TARGET_STRING ( "" )
, 1 , 0 , 0 , 0 , 0 } , { 88 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Gamp" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 89 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/momentum of inertia" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 90 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Product" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 91 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Sum2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 92 , 99 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/MATLAB Function" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 93 , 99 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/MATLAB Function" ) , TARGET_STRING ( "" ) ,
1 , 0 , 0 , 0 , 0 } , { 94 , 99 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/MATLAB Function" ) , TARGET_STRING ( "" ) ,
2 , 0 , 0 , 0 , 0 } , { 95 , 100 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/MATLAB Function1" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 96 , 101 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/MATLAB Function2" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 97 , 101 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/MATLAB Function2" ) , TARGET_STRING ( "" )
, 1 , 0 , 0 , 0 , 0 } , { 98 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Gamp" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 99 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/momentum of inertia" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 100 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Product" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 101 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Sum2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 102 , 102 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/MATLAB Function" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 103 , 102 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/MATLAB Function" ) , TARGET_STRING ( "" ) ,
1 , 0 , 0 , 0 , 0 } , { 104 , 102 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/MATLAB Function" ) , TARGET_STRING ( "" ) ,
2 , 0 , 0 , 0 , 0 } , { 105 , 103 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/MATLAB Function1" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 106 , 104 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/MATLAB Function2" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 107 , 104 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/MATLAB Function2" ) , TARGET_STRING ( "" )
, 1 , 0 , 0 , 0 , 0 } , { 108 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Gamp" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 109 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/momentum of inertia" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 110 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Product" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 111 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Sum2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 112 , 105 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/MATLAB Function" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 113 , 105 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/MATLAB Function" ) , TARGET_STRING ( "" ) ,
1 , 0 , 0 , 0 , 0 } , { 114 , 105 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/MATLAB Function" ) , TARGET_STRING ( "" ) ,
2 , 0 , 0 , 0 , 0 } , { 115 , 106 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/MATLAB Function1" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 116 , 107 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/MATLAB Function2" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 117 , 107 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/MATLAB Function2" ) , TARGET_STRING ( "" )
, 1 , 0 , 0 , 0 , 0 } , { 118 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Gamp" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 119 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/momentum of inertia" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 120 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Product" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 121 , 0 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Sum2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 122 , 4 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/cross/cross" ) , TARGET_STRING (
"" ) , 0 , 0 , 2 , 0 , 0 } , { 123 , 5 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/cross1/cross" ) , TARGET_STRING
( "" ) , 0 , 0 , 2 , 0 , 0 } , { 124 , 6 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/MATLAB Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 125 , 7 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/F107" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 126 , 7 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/aph" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 8 , 0 , 1 } , { 127 , 7 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/flag" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 9 , 0 , 1 } , { 128 , 0 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Invert  3x3 Matrix/Determinant of 3x3 Matrix/Sum"
) , TARGET_STRING ( "det(Matrix)" ) , 0 , 0 , 0 , 0 , 0 } , { 129 , 0 ,
TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Invert  3x3 Matrix1/Determinant of 3x3 Matrix/Sum"
) , TARGET_STRING ( "det(Matrix)" ) , 0 , 0 , 0 , 0 , 0 } , { 130 , 29 ,
TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Remnant Magnetism/cross/cross" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 0 } , { 131 , 34 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/cross/cross" ) , TARGET_STRING ( "" )
, 0 , 0 , 2 , 0 , 0 } , { 132 , 41 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/detect_obj/MATLAB Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 133 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/Random Number" ) , TARGET_STRING ( "" ) , 0
, 0 , 2 , 0 , 3 } , { 134 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/noise3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 3 } , { 135 , 53 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS1/half angle separation of the earth/MATLAB Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 136 , 56 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS2/half angle separation of the earth/MATLAB Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 137 , 59 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS3/half angle separation of the earth/MATLAB Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 138 , 62 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS4/half angle separation of the earth/MATLAB Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 139 , 65 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS5/half angle separation of the earth/MATLAB Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 140 , 68 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS6/half angle separation of the earth/MATLAB Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 141 , 0 , TARGET_STRING (
 "SILS_20241709/Sensors/Quaternions to  Direction Cosine Matrix/Create 3x3 Matrix/Vector Concatenate"
) , TARGET_STRING ( "" ) , 0 , 0 , 10 , 0 , 1 } , { 142 , 0 , TARGET_STRING (
"SILS_20241709/Sensors/STT1/Compare To Constant/Compare" ) , TARGET_STRING (
"" ) , 0 , 1 , 0 , 0 , 3 } , { 143 , 71 , TARGET_STRING (
"SILS_20241709/Sensors/STT1/half angle separation of the earth/MATLAB Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 144 , 7 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/nrlmsise-00 full/S-Function"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 145 , 7 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/nrlmsise-00 full/S-Function"
) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 146 , 50 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/JD2GC/MATLAB Function" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 147 , 50 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/JD2GC/MATLAB Function" ) , TARGET_STRING (
"" ) , 1 , 0 , 0 , 0 , 0 } , { 148 , 50 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/JD2GC/MATLAB Function" ) , TARGET_STRING (
"" ) , 2 , 0 , 0 , 0 , 0 } , { 149 , 50 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/JD2GC/MATLAB Function" ) , TARGET_STRING (
"" ) , 3 , 0 , 0 , 0 , 0 } , { 150 , 50 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/JD2GC/MATLAB Function" ) , TARGET_STRING (
"" ) , 4 , 0 , 0 , 0 , 0 } , { 151 , 50 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/JD2GC/MATLAB Function" ) , TARGET_STRING (
"" ) , 5 , 0 , 0 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 ,
0 } } ; static const rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 152
, TARGET_STRING ( "SILS_20241709/Constant1" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 153 , TARGET_STRING ( "SILS_20241709/Constant2" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 154 , TARGET_STRING (
"SILS_20241709/Constant3" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 155
, TARGET_STRING ( "SILS_20241709/Constant6" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 156 , TARGET_STRING ( "SILS_20241709/Gain" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 157 , TARGET_STRING (
"SILS_20241709/reaction torque" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } ,
{ 158 , TARGET_STRING ( "SILS_20241709/S-Function1" ) , TARGET_STRING ( "P1"
) , 0 , 0 , 0 } , { 159 , TARGET_STRING ( "SILS_20241709/S-Function2" ) ,
TARGET_STRING ( "P1" ) , 0 , 0 , 0 } , { 160 , TARGET_STRING (
"SILS_20241709/S-Function3" ) , TARGET_STRING ( "P1" ) , 0 , 0 , 0 } , { 161
, TARGET_STRING ( "SILS_20241709/S-Function4" ) , TARGET_STRING ( "P1" ) , 0
, 0 , 0 } , { 162 , TARGET_STRING ( "SILS_20241709/S-Function5" ) ,
TARGET_STRING ( "P1" ) , 0 , 0 , 0 } , { 163 , TARGET_STRING (
"SILS_20241709/S-Function6" ) , TARGET_STRING ( "P1" ) , 0 , 0 , 0 } , { 164
, TARGET_STRING ( "SILS_20241709/S-Function7" ) , TARGET_STRING ( "P1" ) , 0
, 0 , 0 } , { 165 , TARGET_STRING ( "SILS_20241709/S-Function8" ) ,
TARGET_STRING ( "P1" ) , 0 , 0 , 0 } , { 166 , TARGET_STRING (
"SILS_20241709/S-Function9" ) , TARGET_STRING ( "P1" ) , 0 , 0 , 0 } , { 167
, TARGET_STRING ( "SILS_20241709/Environment&Dynamics/km2m" ) , TARGET_STRING
( "Gain" ) , 0 , 0 , 0 } , { 168 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/m2km" ) , TARGET_STRING ( "Gain" ) , 0 ,
0 , 0 } , { 169 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/ECEF Position to LLA" ) , TARGET_STRING (
"F" ) , 0 , 0 , 0 } , { 170 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/ECEF Position to LLA" ) , TARGET_STRING (
"R" ) , 0 , 0 , 0 } , { 171 , TARGET_STRING ( "SILS_20241709/MTQs/nT_2_T" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 172 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/Constant1" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 173 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/Constant12" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 174 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/Constant15" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 175 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/Constant2" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 176 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/Constant3" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 177 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/Constant4" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 178 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/Constant5" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 179 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/Constant6" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 180 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 181 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function" ) , TARGET_STRING ( "P2" ) ,
0 , 0 , 0 } , { 182 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function1" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 183 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function2" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 184 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function2" ) , TARGET_STRING ( "P2" ) ,
0 , 0 , 0 } , { 185 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function3" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 186 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function3" ) , TARGET_STRING ( "P2" ) ,
0 , 0 , 0 } , { 187 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function4" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 188 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function4" ) , TARGET_STRING ( "P2" ) ,
0 , 0 , 0 } , { 189 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function5" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 190 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function6" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 191 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function6" ) , TARGET_STRING ( "P2" ) ,
0 , 0 , 0 } , { 192 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function7" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 193 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function7" ) , TARGET_STRING ( "P2" ) ,
0 , 0 , 0 } , { 194 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function8" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 195 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function8" ) , TARGET_STRING ( "P2" ) ,
0 , 0 , 0 } , { 196 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function9" ) , TARGET_STRING ( "P1" ) ,
0 , 0 , 0 } , { 197 , TARGET_STRING (
"SILS_20241709/SensorDataConversion/S-Function9" ) , TARGET_STRING ( "P2" ) ,
0 , 0 , 0 } , { 198 , TARGET_STRING ( "SILS_20241709/Sensors/km2m" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 199 , TARGET_STRING (
"SILS_20241709/Sensors/rad2deg" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } ,
{ 200 , TARGET_STRING ( "SILS_20241709/Sensors/noise1" ) , TARGET_STRING (
"Mean" ) , 0 , 11 , 0 } , { 201 , TARGET_STRING (
"SILS_20241709/Sensors/noise1" ) , TARGET_STRING ( "StdDev" ) , 0 , 11 , 0 }
, { 202 , TARGET_STRING ( "SILS_20241709/three_one_skew/rpm2rad" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 203 , TARGET_STRING (
"SILS_20241709/three_one_skew/rpm2rad1" ) , TARGET_STRING ( "Gain" ) , 0 , 0
, 0 } , { 204 , TARGET_STRING ( "SILS_20241709/three_one_skew/rpm2rad2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 205 , TARGET_STRING (
"SILS_20241709/three_one_skew/rpm2rad3" ) , TARGET_STRING ( "Gain" ) , 0 , 0
, 0 } , { 206 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/hour2sec" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 207 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/min2sec" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 208 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/AstroDynamics/sec_per_day" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 209 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/GPperturbation/GPperturbation_RSW_km//s^2_3"
) , TARGET_STRING ( "InitialOutput" ) , 0 , 2 , 0 } , { 210 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/GPperturbation/deg2rad" ) , TARGET_STRING
( "Gain" ) , 0 , 0 , 0 } , { 211 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Gravity Gradient/GG_b_Nm_3" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 2 , 0 } , { 212 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Remnant Magnetism/remmag_b_Nm_3" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 2 , 0 } , { 213 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Remnant Magnetism/nT2T" ) , TARGET_STRING
( "Gain" ) , 0 , 0 , 0 } , { 214 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/RigidBodyDynamics/IC" ) , TARGET_STRING (
"Value" ) , 0 , 12 , 0 } , { 215 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/RigidBodyDynamics/IC1" ) , TARGET_STRING
( "Value" ) , 0 , 11 , 0 } , { 216 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/SRP_b_Nm_3" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 2 , 0 } , { 217 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Normalize Vector" ) , TARGET_STRING (
"maxzero" ) , 0 , 0 , 0 } , { 218 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Normalize Vector" ) ,
TARGET_STRING ( "maxzero" ) , 0 , 0 , 0 } , { 219 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Gain" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 220 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Normalize Vector" ) ,
TARGET_STRING ( "maxzero" ) , 0 , 0 , 0 } , { 221 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Normalize Vector" ) ,
TARGET_STRING ( "maxzero" ) , 0 , 0 , 0 } , { 222 , TARGET_STRING (
"SILS_20241709/MTQs/MTQ_1/Transfer Fcn" ) , TARGET_STRING ( "A" ) , 0 , 0 , 0
} , { 223 , TARGET_STRING ( "SILS_20241709/MTQs/MTQ_1/Transfer Fcn" ) ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 224 , TARGET_STRING (
"SILS_20241709/MTQs/MTQ_2/Transfer Fcn" ) , TARGET_STRING ( "A" ) , 0 , 0 , 0
} , { 225 , TARGET_STRING ( "SILS_20241709/MTQs/MTQ_2/Transfer Fcn" ) ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 226 , TARGET_STRING (
"SILS_20241709/MTQs/MTQ_3/Transfer Fcn" ) , TARGET_STRING ( "A" ) , 0 , 0 , 0
} , { 227 , TARGET_STRING ( "SILS_20241709/MTQs/MTQ_3/Transfer Fcn" ) ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 228 , TARGET_STRING (
"SILS_20241709/Sensors/GAS/noise" ) , TARGET_STRING ( "Mean" ) , 0 , 11 , 0 }
, { 229 , TARGET_STRING ( "SILS_20241709/Sensors/GAS/noise" ) , TARGET_STRING
( "StdDev" ) , 0 , 11 , 0 } , { 230 , TARGET_STRING (
"SILS_20241709/Sensors/GAS/Transfer Fcn" ) , TARGET_STRING ( "A" ) , 0 , 0 ,
0 } , { 231 , TARGET_STRING ( "SILS_20241709/Sensors/GAS/Transfer Fcn" ) ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 232 , TARGET_STRING (
"SILS_20241709/Sensors/GAS/Transfer Fcn1" ) , TARGET_STRING ( "A" ) , 0 , 0 ,
0 } , { 233 , TARGET_STRING ( "SILS_20241709/Sensors/GAS/Transfer Fcn1" ) ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 234 , TARGET_STRING (
"SILS_20241709/Sensors/GAS/Transfer Fcn2" ) , TARGET_STRING ( "A" ) , 0 , 0 ,
0 } , { 235 , TARGET_STRING ( "SILS_20241709/Sensors/GAS/Transfer Fcn2" ) ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 236 , TARGET_STRING (
"SILS_20241709/Sensors/GYRO/b0(deg//sec)" ) , TARGET_STRING ( "Value" ) , 0 ,
11 , 0 } , { 237 , TARGET_STRING ( "SILS_20241709/Sensors/GYRO/Integrator" )
, TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 238 , TARGET_STRING
( "SILS_20241709/Sensors/GYRO/nu(deg//sec^2)" ) , TARGET_STRING ( "Mean" ) ,
0 , 11 , 0 } , { 239 , TARGET_STRING (
"SILS_20241709/Sensors/GYRO/nu(deg//sec^2)" ) , TARGET_STRING ( "StdDev" ) ,
0 , 11 , 0 } , { 240 , TARGET_STRING (
"SILS_20241709/Sensors/GYRO/nv(deg//sec)" ) , TARGET_STRING ( "Mean" ) , 0 ,
11 , 0 } , { 241 , TARGET_STRING ( "SILS_20241709/Sensors/GYRO/nv(deg//sec)"
) , TARGET_STRING ( "StdDev" ) , 0 , 11 , 0 } , { 242 , TARGET_STRING (
"SILS_20241709/Sensors/GYRO/Transfer Fcn" ) , TARGET_STRING ( "A" ) , 0 , 4 ,
0 } , { 243 , TARGET_STRING ( "SILS_20241709/Sensors/GYRO/Transfer Fcn" ) ,
TARGET_STRING ( "C" ) , 0 , 13 , 0 } , { 244 , TARGET_STRING (
"SILS_20241709/Sensors/GYRO/Transfer Fcn1" ) , TARGET_STRING ( "A" ) , 0 , 4
, 0 } , { 245 , TARGET_STRING ( "SILS_20241709/Sensors/GYRO/Transfer Fcn1" )
, TARGET_STRING ( "C" ) , 0 , 13 , 0 } , { 246 , TARGET_STRING (
"SILS_20241709/Sensors/GYRO/Transfer Fcn2" ) , TARGET_STRING ( "A" ) , 0 , 4
, 0 } , { 247 , TARGET_STRING ( "SILS_20241709/Sensors/GYRO/Transfer Fcn2" )
, TARGET_STRING ( "C" ) , 0 , 13 , 0 } , { 248 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS1/Normalize Vector" ) , TARGET_STRING ( "maxzero"
) , 0 , 0 , 0 } , { 249 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS1/z>0" )
, TARGET_STRING ( "const" ) , 0 , 0 , 0 } , { 250 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS1/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 251 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS1/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 2 , 0 } , { 252 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS1/Constant2" ) , TARGET_STRING ( "Value" ) , 0 ,
13 , 0 } , { 253 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS1/rad2deg" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 254 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS1/noise" ) , TARGET_STRING ( "Mean" ) , 0 , 0 , 0
} , { 255 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS1/noise1" ) ,
TARGET_STRING ( "Mean" ) , 0 , 0 , 0 } , { 256 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS2/Normalize Vector" ) , TARGET_STRING ( "maxzero"
) , 0 , 0 , 0 } , { 257 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS2/z>0" )
, TARGET_STRING ( "const" ) , 0 , 0 , 0 } , { 258 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS2/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 259 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS2/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 2 , 0 } , { 260 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS2/Constant2" ) , TARGET_STRING ( "Value" ) , 0 ,
13 , 0 } , { 261 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS2/rad2deg" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 262 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS2/noise" ) , TARGET_STRING ( "Mean" ) , 0 , 0 , 0
} , { 263 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS2/noise1" ) ,
TARGET_STRING ( "Mean" ) , 0 , 0 , 0 } , { 264 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS3/Normalize Vector" ) , TARGET_STRING ( "maxzero"
) , 0 , 0 , 0 } , { 265 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS3/z>0" )
, TARGET_STRING ( "const" ) , 0 , 0 , 0 } , { 266 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS3/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 267 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS3/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 2 , 0 } , { 268 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS3/Constant2" ) , TARGET_STRING ( "Value" ) , 0 ,
13 , 0 } , { 269 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS3/rad2deg" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 270 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS3/noise" ) , TARGET_STRING ( "Mean" ) , 0 , 0 , 0
} , { 271 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS3/noise1" ) ,
TARGET_STRING ( "Mean" ) , 0 , 0 , 0 } , { 272 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS4/Normalize Vector" ) , TARGET_STRING ( "maxzero"
) , 0 , 0 , 0 } , { 273 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS4/z>0" )
, TARGET_STRING ( "const" ) , 0 , 0 , 0 } , { 274 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS4/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 275 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS4/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 2 , 0 } , { 276 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS4/Constant2" ) , TARGET_STRING ( "Value" ) , 0 ,
13 , 0 } , { 277 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS4/rad2deg" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 278 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS4/noise" ) , TARGET_STRING ( "Mean" ) , 0 , 0 , 0
} , { 279 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS4/noise1" ) ,
TARGET_STRING ( "Mean" ) , 0 , 0 , 0 } , { 280 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS5/Normalize Vector" ) , TARGET_STRING ( "maxzero"
) , 0 , 0 , 0 } , { 281 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS5/z>0" )
, TARGET_STRING ( "const" ) , 0 , 0 , 0 } , { 282 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS5/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 283 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS5/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 2 , 0 } , { 284 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS5/Constant2" ) , TARGET_STRING ( "Value" ) , 0 ,
13 , 0 } , { 285 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS5/rad2deg" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 286 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS5/noise" ) , TARGET_STRING ( "Mean" ) , 0 , 0 , 0
} , { 287 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS5/noise1" ) ,
TARGET_STRING ( "Mean" ) , 0 , 0 , 0 } , { 288 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS6/Normalize Vector" ) , TARGET_STRING ( "maxzero"
) , 0 , 0 , 0 } , { 289 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS6/z>0" )
, TARGET_STRING ( "const" ) , 0 , 0 , 0 } , { 290 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS6/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 291 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS6/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 2 , 0 } , { 292 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS6/Constant2" ) , TARGET_STRING ( "Value" ) , 0 ,
13 , 0 } , { 293 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS6/rad2deg" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 294 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS6/noise" ) , TARGET_STRING ( "Mean" ) , 0 , 0 , 0
} , { 295 , TARGET_STRING ( "SILS_20241709/Sensors/NSAS6/noise1" ) ,
TARGET_STRING ( "Mean" ) , 0 , 0 , 0 } , { 296 , TARGET_STRING (
"SILS_20241709/Sensors/STT1/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 11
, 0 } , { 297 , TARGET_STRING ( "SILS_20241709/Sensors/STT1/Constant2" ) ,
TARGET_STRING ( "Value" ) , 0 , 11 , 0 } , { 298 , TARGET_STRING (
"SILS_20241709/Sensors/STT1/Uniform Random Number" ) , TARGET_STRING (
"Minimum" ) , 0 , 0 , 0 } , { 299 , TARGET_STRING (
"SILS_20241709/Sensors/STT1/Uniform Random Number" ) , TARGET_STRING (
"Maximum" ) , 0 , 0 , 0 } , { 300 , TARGET_STRING (
"SILS_20241709/Sensors/STT1/Uniform Random Number" ) , TARGET_STRING ( "Seed"
) , 0 , 0 , 0 } , { 301 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Constant" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 302 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Constant1" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 303 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Constant2" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 304 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Constant3" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 305 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/loss torque (propotion to ƒÖ)" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 306 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/rad2rpm" ) , TARGET_STRING ( "Gain" ) , 0 ,
0 , 0 } , { 307 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 308 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Switch" ) , TARGET_STRING ( "Threshold" ) ,
0 , 0 , 0 } , { 309 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Switch1" ) , TARGET_STRING ( "Threshold" )
, 0 , 0 , 0 } , { 310 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Switch2" ) , TARGET_STRING ( "Threshold" )
, 0 , 0 , 0 } , { 311 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Transfer Fcn1" ) , TARGET_STRING ( "A" ) ,
0 , 0 , 0 } , { 312 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/Transfer Fcn1" ) , TARGET_STRING ( "C" ) ,
0 , 0 , 0 } , { 313 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW1/motor" ) , TARGET_STRING ( "D" ) , 0 , 0 ,
0 } , { 314 , TARGET_STRING ( "SILS_20241709/three_one_skew/RW2/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 315 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Constant1" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 316 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Constant2" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 317 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Constant3" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 318 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/loss torque (propotion to ƒÖ)" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 319 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/rad2rpm" ) , TARGET_STRING ( "Gain" ) , 0 ,
0 , 0 } , { 320 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 321 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Switch" ) , TARGET_STRING ( "Threshold" ) ,
0 , 0 , 0 } , { 322 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Switch1" ) , TARGET_STRING ( "Threshold" )
, 0 , 0 , 0 } , { 323 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Switch2" ) , TARGET_STRING ( "Threshold" )
, 0 , 0 , 0 } , { 324 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Transfer Fcn1" ) , TARGET_STRING ( "A" ) ,
0 , 0 , 0 } , { 325 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/Transfer Fcn1" ) , TARGET_STRING ( "C" ) ,
0 , 0 , 0 } , { 326 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW2/motor" ) , TARGET_STRING ( "D" ) , 0 , 0 ,
0 } , { 327 , TARGET_STRING ( "SILS_20241709/three_one_skew/RW3/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 328 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Constant1" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 329 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Constant2" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 330 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Constant3" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 331 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/loss torque (propotion to ƒÖ)" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 332 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/rad2rpm" ) , TARGET_STRING ( "Gain" ) , 0 ,
0 , 0 } , { 333 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 334 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Switch" ) , TARGET_STRING ( "Threshold" ) ,
0 , 0 , 0 } , { 335 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Switch1" ) , TARGET_STRING ( "Threshold" )
, 0 , 0 , 0 } , { 336 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Switch2" ) , TARGET_STRING ( "Threshold" )
, 0 , 0 , 0 } , { 337 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Transfer Fcn1" ) , TARGET_STRING ( "A" ) ,
0 , 0 , 0 } , { 338 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/Transfer Fcn1" ) , TARGET_STRING ( "C" ) ,
0 , 0 , 0 } , { 339 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW3/motor" ) , TARGET_STRING ( "D" ) , 0 , 0 ,
0 } , { 340 , TARGET_STRING ( "SILS_20241709/three_one_skew/RW4/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 341 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Constant1" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 342 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Constant2" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 343 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Constant3" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 344 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/loss torque (propotion to ƒÖ)" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 345 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/rad2rpm" ) , TARGET_STRING ( "Gain" ) , 0 ,
0 , 0 } , { 346 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 347 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Switch" ) , TARGET_STRING ( "Threshold" ) ,
0 , 0 , 0 } , { 348 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Switch1" ) , TARGET_STRING ( "Threshold" )
, 0 , 0 , 0 } , { 349 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Switch2" ) , TARGET_STRING ( "Threshold" )
, 0 , 0 , 0 } , { 350 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Transfer Fcn1" ) , TARGET_STRING ( "A" ) ,
0 , 0 , 0 } , { 351 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/Transfer Fcn1" ) , TARGET_STRING ( "C" ) ,
0 , 0 , 0 } , { 352 , TARGET_STRING (
"SILS_20241709/three_one_skew/RW4/motor" ) , TARGET_STRING ( "D" ) , 0 , 0 ,
0 } , { 353 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/F107" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 354 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/aph" ) ,
TARGET_STRING ( "Value" ) , 0 , 14 , 0 } , { 355 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/flag" ) ,
TARGET_STRING ( "Value" ) , 0 , 15 , 0 } , { 356 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Direction Cosine Matrix ECEF to NED/A23/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 357 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/OrbitalDynamics/calc_q/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 358 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/OrbitalDynamics/calc_q/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 359 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/OrbitalDynamics/calc_q/Constant2" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 360 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V1/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 361 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V1/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 362 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V1/Gain1" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 363 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V1/Gain2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 364 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V2/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 365 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V2/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 366 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V2/Gain1" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 367 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V2/Gain2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 368 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V3/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 369 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V3/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 370 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V3/Gain1" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 371 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Quaternion Rotation/V3/Gain2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 372 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Normalize Vector/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 373 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Normalize Vector/Constant" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 374 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Normalize Vector/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 375 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Normalize Vector/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 376 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/Random Number" ) , TARGET_STRING ( "Mean" )
, 0 , 11 , 0 } , { 377 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/Random Number" ) , TARGET_STRING ( "StdDev"
) , 0 , 11 , 0 } , { 378 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/noise3" ) , TARGET_STRING ( "Minimum" ) , 0
, 0 , 0 } , { 379 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/ECEF Position to LLA" ) , TARGET_STRING (
"F" ) , 0 , 0 , 0 } , { 380 , TARGET_STRING (
"SILS_20241709/Sensors/GPS/GPS_R/ECEF Position to LLA" ) , TARGET_STRING (
"R" ) , 0 , 0 , 0 } , { 381 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS1/Normalize Vector/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 382 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS2/Normalize Vector/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 383 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS3/Normalize Vector/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 384 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS4/Normalize Vector/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 385 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS5/Normalize Vector/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 386 , TARGET_STRING (
"SILS_20241709/Sensors/NSAS6/Normalize Vector/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 387 , TARGET_STRING (
"SILS_20241709/Sensors/Quaternions to  Direction Cosine Matrix/A12/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 388 , TARGET_STRING (
"SILS_20241709/Sensors/Quaternions to  Direction Cosine Matrix/A13/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 389 , TARGET_STRING (
"SILS_20241709/Sensors/Quaternions to  Direction Cosine Matrix/A21/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 390 , TARGET_STRING (
"SILS_20241709/Sensors/Quaternions to  Direction Cosine Matrix/A23/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 391 , TARGET_STRING (
"SILS_20241709/Sensors/Quaternions to  Direction Cosine Matrix/A31/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 392 , TARGET_STRING (
"SILS_20241709/Sensors/Quaternions to  Direction Cosine Matrix/A32/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 393 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V1/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 394 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V1/Gain" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 395 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V1/Gain1" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 396 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V1/Gain2" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 397 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V2/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 398 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V2/Gain" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 399 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V2/Gain1" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 400 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V2/Gain2" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 401 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V3/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 402 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V3/Gain" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 403 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V3/Gain1" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 404 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/Air Drag/Quaternion Rotation2/V3/Gain2" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 405 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/nrlmsise-00 full/g//cm^3->kg//m^3"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 406 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V1/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 407 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V1/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 408 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V1/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 409 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V1/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 410 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V2/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 411 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V2/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 412 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V2/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 413 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V2/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 414 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V3/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 415 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V3/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 416 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V3/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 417 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/Gravity Gradient/Quaternion Rotation1/V3/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 418 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V1/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 419 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V1/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 420 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V1/Gain1" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 421 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V1/Gain2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 422 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V2/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 423 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V2/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 424 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V2/Gain1" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 425 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V2/Gain2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 426 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V3/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 427 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V3/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 428 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V3/Gain1" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 429 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/SRP/Quaternion Rotation2/V3/Gain2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 430 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V1/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 431 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V1/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 432 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V1/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 433 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V1/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 434 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V2/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 435 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V2/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 436 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V2/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 437 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V2/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 438 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V3/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 439 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V3/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 440 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V3/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 441 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/earth_vec_b/Quaternion Rotation/V3/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 442 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V1/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 443 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V1/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 444 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V1/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 445 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V1/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 446 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V2/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 447 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V2/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 448 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V2/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 449 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V2/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 450 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V3/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 451 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V3/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 452 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V3/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 453 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b/Quaternion Rotation/V3/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 454 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V1/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 455 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V1/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 456 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V1/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 457 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V1/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 458 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V2/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 459 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V2/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 460 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V2/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 461 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V2/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 462 , TARGET_STRING (
 "SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V3/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 463 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V3/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 464 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V3/Gain1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 465 , TARGET_STRING (
"SILS_20241709/Environment&Dynamics/sat2obj_vec_b1/Quaternion Rotation/V3/Gain2"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 ,
0 , 0 } } ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const
rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 ,
0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 466 , 0
, TARGET_STRING ( "SILS_20241709/outAngularRate" ) , TARGET_STRING (
"outAngularRate" ) , 1 , 0 , 0 , 0 , 0 } , { 467 , 0 , TARGET_STRING (
"SILS_20241709/sun_flag_#_#_1" ) , TARGET_STRING ( "sun_flag" ) , 2 , 0 , 0 ,
0 , 0 } , { 468 , 0 , TARGET_STRING ( "SILS_20241709/w_b_rad//s" ) ,
TARGET_STRING ( "w_b_rad_s" ) , 3 , 0 , 2 , 0 , 0 } , { 0 , 0 , ( NULL ) , (
NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_ModelParameters
rtModelParameters [ ] = { { 469 , TARGET_STRING ( "ADSW" ) , 0 , 0 , 0 } , {
470 , TARGET_STRING ( "CD" ) , 0 , 0 , 0 } , { 471 , TARGET_STRING ( "CR" ) ,
0 , 0 , 0 } , { 472 , TARGET_STRING ( "GAS_Vref" ) , 0 , 0 , 0 } , { 473 ,
TARGET_STRING ( "GAS_b2c" ) , 0 , 16 , 0 } , { 474 , TARGET_STRING (
"GAS_seed1" ) , 0 , 11 , 0 } , { 475 , TARGET_STRING ( "GE" ) , 0 , 0 , 0 } ,
{ 476 , TARGET_STRING ( "GGSW" ) , 0 , 0 , 0 } , { 477 , TARGET_STRING (
"GPS_position_seed" ) , 0 , 11 , 0 } , { 478 , TARGET_STRING (
"GPS_time_noise" ) , 0 , 0 , 0 } , { 479 , TARGET_STRING ( "GPS_time_seed" )
, 0 , 0 , 0 } , { 480 , TARGET_STRING ( "GPperturbationSW" ) , 0 , 0 , 0 } ,
{ 481 , TARGET_STRING ( "GYRO_b2c" ) , 0 , 16 , 0 } , { 482 , TARGET_STRING (
"GYRO_seed1" ) , 0 , 11 , 0 } , { 483 , TARGET_STRING ( "GYRO_seed2" ) , 0 ,
11 , 0 } , { 484 , TARGET_STRING ( "I" ) , 0 , 16 , 0 } , { 485 ,
TARGET_STRING ( "J2" ) , 0 , 0 , 0 } , { 486 , TARGET_STRING ( "MTQ_c2b" ) ,
0 , 2 , 0 } , { 487 , TARGET_STRING ( "NSAS1_b2c" ) , 0 , 16 , 0 } , { 488 ,
TARGET_STRING ( "NSAS2_b2c" ) , 0 , 16 , 0 } , { 489 , TARGET_STRING (
"NSAS3_b2c" ) , 0 , 16 , 0 } , { 490 , TARGET_STRING ( "NSAS4_b2c" ) , 0 , 16
, 0 } , { 491 , TARGET_STRING ( "NSAS5_b2c" ) , 0 , 16 , 0 } , { 492 ,
TARGET_STRING ( "NSAS6_b2c" ) , 0 , 16 , 0 } , { 493 , TARGET_STRING (
"NSAS_ang_limit" ) , 0 , 0 , 0 } , { 494 , TARGET_STRING ( "NSAS_seed1" ) , 0
, 0 , 0 } , { 495 , TARGET_STRING ( "NSAS_seed2" ) , 0 , 0 , 0 } , { 496 ,
TARGET_STRING ( "NSAS_x_noise" ) , 0 , 0 , 0 } , { 497 , TARGET_STRING (
"NSAS_y_noise" ) , 0 , 0 , 0 } , { 498 , TARGET_STRING ( "RW_Gamp" ) , 0 , 0
, 0 } , { 499 , TARGET_STRING ( "RW_J" ) , 0 , 0 , 0 } , { 500 ,
TARGET_STRING ( "RW_Rsc" ) , 0 , 0 , 0 } , { 501 , TARGET_STRING ( "RW_kE" )
, 0 , 0 , 0 } , { 502 , TARGET_STRING ( "RW_kT" ) , 0 , 0 , 0 } , { 503 ,
TARGET_STRING ( "SRPSW" ) , 0 , 0 , 0 } , { 504 , TARGET_STRING (
"STT1_b2c_quat" ) , 0 , 12 , 0 } , { 505 , TARGET_STRING ( "STT_AD_prob" ) ,
0 , 0 , 0 } , { 506 , TARGET_STRING ( "STT_FOV" ) , 0 , 0 , 0 } , { 507 ,
TARGET_STRING ( "STT_moon_ang_limit" ) , 0 , 0 , 0 } , { 508 , TARGET_STRING
( "STT_seed1" ) , 0 , 11 , 0 } , { 509 , TARGET_STRING ( "STT_sun_ang_limit"
) , 0 , 0 , 0 } , { 510 , TARGET_STRING ( "TOLERANCE" ) , 0 , 0 , 0 } , { 511
, TARGET_STRING ( "UT1_UTC" ) , 0 , 0 , 0 } , { 512 , TARGET_STRING ( "area"
) , 0 , 0 , 0 } , { 513 , TARGET_STRING ( "arm" ) , 0 , 2 , 0 } , { 514 ,
TARGET_STRING ( "earth_radius" ) , 0 , 0 , 0 } , { 515 , TARGET_STRING (
"ele" ) , 0 , 17 , 0 } , { 516 , TARGET_STRING ( "jd" ) , 0 , 0 , 0 } , { 517
, TARGET_STRING ( "pSR" ) , 0 , 0 , 0 } , { 518 , TARGET_STRING ( "q_ini" ) ,
0 , 12 , 0 } , { 519 , TARGET_STRING ( "rem_mag" ) , 0 , 2 , 0 } , { 520 ,
TARGET_STRING ( "rem_magSW" ) , 0 , 0 , 0 } , { 521 , TARGET_STRING (
"three_one_skew_matrix" ) , 0 , 18 , 0 } , { 522 , TARGET_STRING ( "wE" ) , 0
, 2 , 0 } , { 523 , TARGET_STRING ( "w_ini" ) , 0 , 11 , 0 } , { 0 , ( NULL )
, 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . jhikopnu5c , & rtB . a3fezsr2vw ,
& rtB . edgmu1taic [ 0 ] , & rtB . gv3z4rzpl5 [ 0 ] , & rtB . j3kezx3yvk [ 0
] , & rtB . lrdfz5anhg [ 0 ] , & rtB . d2nlp5u0iz [ 0 ] , & rtB . cvndu2lgp0
[ 0 ] , & rtB . mslzotztaf [ 0 ] , & rtB . l15tbbx15x . c1nd5nsrgs [ 0 ] , &
rtB . hm15o25lmb [ 0 ] , & rtB . b5ehs0zt32 [ 0 ] , & rtB . jclektca5o .
aupbtlrqjk [ 0 ] , & rtB . c5rolz011g . c1nd5nsrgs [ 0 ] , & rtB . mpca01r2m2
, & rtB . a5ald3g22i [ 0 ] , & rtB . jg4a0jn2o1 [ 0 ] , & rtB . gsio300bjg ,
& rtB . ozbqnpwmeu , & rtB . gbjcwtpbjf , & rtB . ogbf133q1z , & rtB .
ocfpzffbzh , & rtB . pzuqvdky0w , & rtB . i34t1ktiub , & rtB . oqvw4bmbeg [ 0
] , & rtB . d3cawecdgq . fkae5wqtcb , & rtB . ka15ybowc1 . fkae5wqtcb , & rtB
. gz3hxniyg2 . fkae5wqtcb , & rtB . ejln4gh0kq . fkae5wqtcb , & rtB .
jn52bjhkjf , & rtB . chrkykmk4n , & rtB . hm15o25lmb [ 0 ] , & rtB .
b5ehs0zt32 [ 0 ] , & rtB . e1zykr3jbv . crs3vbajbr , & rtB . e1zykr3jbv .
pyqwe5rsse , & rtB . e1zykr3jbv . agveekqpqv , & rtB . e1zykr3jbv .
le233aiaq5 , & rtB . e1zykr3jbv . b2jeeweznc , & rtB . e1zykr3jbv .
cnte5pmho4 , & rtB . gs20g4hobc [ 0 ] , & rtB . lzmaq0diab [ 0 ] , & rtB .
eij4bqg1qu [ 0 ] , & rtB . a5ybxummfl [ 0 ] , & rtB . jr21nlhhbn [ 0 ] , &
rtB . gyoxzzwqiz [ 0 ] , & rtB . ls5qu2j3gs . poahfmj3s1 [ 0 ] , & rtB .
hdgmktoixc . poahfmj3s1 [ 0 ] , & rtB . ca53m05hej . poahfmj3s1 [ 0 ] , & rtB
. bqbim0ae4p [ 0 ] , & rtB . hcpvpoawqx [ 0 ] , & rtB . ikgewnxpow [ 0 ] , &
rtB . nljkudwtrt [ 0 ] , & rtB . ht411kslhv [ 0 ] , & rtB . lizdm2xqna , &
rtB . laz0gn3eus , & rtB . ggo5omtwrw , & rtB . gu0xyts5qt , & rtB .
cpp1cmyksa , & rtB . necosqfbva , & rtB . mo4pqo22zy , & rtB . ooktctrg5d , &
rtB . onbsvxszlu , & rtB . ljv1mgpbcd , & rtB . lfncg5pvng , & rtB .
kfpd0jse5u , & rtB . ndtffugziw [ 0 ] , & rtB . ab0dpslgku . owg3qz0vb0 [ 0 ]
, & rtB . gwin1pepam . owg3qz0vb0 [ 0 ] , & rtB . axrlvoalzz . osxy5zocx5 [ 0
] , & rtB . fovozsjxj1 . owg3qz0vb0 [ 0 ] , & rtB . o05svadaty . owg3qz0vb0 [
0 ] , & rtB . jacwaaufsl . owg3qz0vb0 [ 0 ] , & rtB . jw1hn4rp4t . owg3qz0vb0
[ 0 ] , & rtB . ajpyzlqqkx . owg3qz0vb0 [ 0 ] , & rtB . eosebepeyc .
owg3qz0vb0 [ 0 ] , & rtB . awovp5grnq . owg3qz0vb0 [ 0 ] , & rtB . n3omup2lzv
. owg3qz0vb0 [ 0 ] , & rtB . gzwxmb2zl2 . owg3qz0vb0 [ 0 ] , & rtB .
ddwcgokc4u . owg3qz0vb0 [ 0 ] , & rtB . py0l0jdlqp . owg3qz0vb0 [ 0 ] , & rtB
. hiok3cyxgg . osxy5zocx5 [ 0 ] , & rtB . fe4ousljhv . osxy5zocx5 [ 0 ] , &
rtB . dbik3caean . ozezoxky3t , & rtB . dbik3caean . g5m2irbsxw , & rtB .
dbik3caean . h5cyove4ef , & rtB . nbdejsvdft . nd52bn25fb , & rtB .
mx32imycyi . jeak4pqr3j , & rtB . mx32imycyi . h0dxk1yimp , & rtB .
geuyf21jdw , & rtB . hfnierhiih , & rtB . llfqz3cih1 , & rtB . chofn13vqp , &
rtB . mzrdmi3ngp . ozezoxky3t , & rtB . mzrdmi3ngp . g5m2irbsxw , & rtB .
mzrdmi3ngp . h5cyove4ef , & rtB . k4gpt5xlei . nd52bn25fb , & rtB .
gszk3bc3vp . jeak4pqr3j , & rtB . gszk3bc3vp . h0dxk1yimp , & rtB .
ahgjrqaame , & rtB . e3dq3kgfi1 , & rtB . euwsxn4aph , & rtB . pmkqoqavmi , &
rtB . a4nohvrqys . ozezoxky3t , & rtB . a4nohvrqys . g5m2irbsxw , & rtB .
a4nohvrqys . h5cyove4ef , & rtB . fovau4dl3r . nd52bn25fb , & rtB .
df0oudwkj0 . jeak4pqr3j , & rtB . df0oudwkj0 . h0dxk1yimp , & rtB .
lyqxqxi2xc , & rtB . jbyqlkik0e , & rtB . kiyg1swe1h , & rtB . c5lfdegv0p , &
rtB . jjm2phe1us . ozezoxky3t , & rtB . jjm2phe1us . g5m2irbsxw , & rtB .
jjm2phe1us . h5cyove4ef , & rtB . aomn2ihkzv . nd52bn25fb , & rtB .
iroofsivyk . jeak4pqr3j , & rtB . iroofsivyk . h0dxk1yimp , & rtB .
owuvzpfz25 , & rtB . ddje2kvmhp , & rtB . el4rhtecud , & rtB . ju0zmrtbs0 , &
rtB . aav5pusdkp . aupbtlrqjk [ 0 ] , & rtB . l15tbbx15x . c1nd5nsrgs [ 0 ] ,
& rtB . i2mlgup0vd , & rtB . p4vsv1mu0t , & rtB . blzsybl1pb [ 0 ] , & rtB .
nspxciplv0 [ 0 ] , & rtB . mmxfckfrxp , & rtB . ovvyrfj4qq , & rtB .
jclektca5o . aupbtlrqjk [ 0 ] , & rtB . c5rolz011g . c1nd5nsrgs [ 0 ] , & rtB
. kimclls5ui , & rtB . gs0kzoznkl [ 0 ] , & rtB . jkg4capamp , & rtB .
jhrf4npwtn . a4ujzgnsun , & rtB . jrtx1iz4hz . a4ujzgnsun , & rtB .
d3edomwivh . a4ujzgnsun , & rtB . fxdnyd3caz . a4ujzgnsun , & rtB .
puqqfcdyyx . a4ujzgnsun , & rtB . odjpekassu . a4ujzgnsun , & rtB .
ghrb02xtti [ 0 ] , & rtB . ff5nefkxhm , & rtB . dd2g34vqpy . a4ujzgnsun , &
rtB . nevppfxrse , & rtB . bfrpnyoemv , & rtB . g5opol5dur . crs3vbajbr , &
rtB . g5opol5dur . pyqwe5rsse , & rtB . g5opol5dur . agveekqpqv , & rtB .
g5opol5dur . le233aiaq5 , & rtB . g5opol5dur . b2jeeweznc , & rtB .
g5opol5dur . cnte5pmho4 , & rtP . Constant1_Value_iq2e102mi0 , & rtP .
Constant2_Value_fgyxvvitry , & rtP . Constant3_Value_mtqeqchjq3 , & rtP .
Constant6_Value_oipnu5fd53 , & rtP . Gain_Gain_itrtl3m3mg , & rtP .
reactiontorque_Gain , & rtP . SFunction1_P1_ku32nmmjfh , & rtP .
SFunction2_P1 , & rtP . SFunction3_P1_jzwtpm1uma , & rtP .
SFunction4_P1_edpc41wy4o , & rtP . SFunction5_P1_brpnppqifr , & rtP .
SFunction6_P1_edgmn5fq4g , & rtP . SFunction7_P1 , & rtP . SFunction8_P1 , &
rtP . SFunction9_P1 , & rtP . km2m_Gain , & rtP . m2km_Gain , & rtP .
ECEFPositiontoLLA_F , & rtP . ECEFPositiontoLLA_R , & rtP . nT_2_T_Gain , &
rtP . Constant1_Value , & rtP . Constant12_Value , & rtP . Constant15_Value ,
& rtP . Constant2_Value , & rtP . Constant3_Value , & rtP . Constant4_Value ,
& rtP . Constant5_Value , & rtP . Constant6_Value , & rtP . SFunction_P1 , &
rtP . SFunction_P2 , & rtP . SFunction1_P1 , & rtP . SFunction2_P1_psdu2cwwwx
, & rtP . SFunction2_P2 , & rtP . SFunction3_P1 , & rtP . SFunction3_P2 , &
rtP . SFunction4_P1 , & rtP . SFunction4_P2 , & rtP . SFunction5_P1 , & rtP .
SFunction6_P1 , & rtP . SFunction6_P2 , & rtP . SFunction7_P1_c0oipohs5p , &
rtP . SFunction7_P2 , & rtP . SFunction8_P1_ddvmotdhun , & rtP .
SFunction8_P2 , & rtP . SFunction9_P1_nunfwxzwxg , & rtP . SFunction9_P2 , &
rtP . km2m_Gain_c3udq35tim , & rtP . rad2deg_Gain_i0zxrskrml , & rtP .
noise1_Mean [ 0 ] , & rtP . noise1_StdDev [ 0 ] , & rtP . rpm2rad_Gain , &
rtP . rpm2rad1_Gain , & rtP . rpm2rad2_Gain , & rtP . rpm2rad3_Gain , & rtP .
hour2sec_Gain , & rtP . min2sec_Gain , & rtP . sec_per_day_Gain , & rtP .
GPperturbation_RSW_kms2_3_Y0 [ 0 ] , & rtP . deg2rad_Gain , & rtP .
GG_b_Nm_3_Y0 [ 0 ] , & rtP . remmag_b_Nm_3_Y0 [ 0 ] , & rtP . nT2T_Gain , &
rtP . IC_Value [ 0 ] , & rtP . IC1_Value [ 0 ] , & rtP . SRP_b_Nm_3_Y0 [ 0 ]
, & rtP . NormalizeVector_maxzero , & rtP .
NormalizeVector_maxzero_p5fqgxj0sr , & rtP . Gain_Gain_c5svou2zai , & rtP .
NormalizeVector_maxzero_lpqo5h1ax3 , & rtP .
NormalizeVector_maxzero_jad2sd3ugf , & rtP . TransferFcn_A_aashwww0mz , & rtP
. TransferFcn_C_kwbfsnl1hg , & rtP . TransferFcn_A_gmkfu1bp5e , & rtP .
TransferFcn_C_n45ccaftaw , & rtP . TransferFcn_A_axh3uxseti , & rtP .
TransferFcn_C_c3yi1bxnht , & rtP . noise_Mean_m211emgdl3 [ 0 ] , & rtP .
noise_StdDev [ 0 ] , & rtP . TransferFcn_A_c34clvpx4a , & rtP .
TransferFcn_C_ciybxys4sn , & rtP . TransferFcn1_A_lrz1uxhxld , & rtP .
TransferFcn1_C_b2uz52ggce , & rtP . TransferFcn2_A_pnihap0iyy , & rtP .
TransferFcn2_C_f5zsdduuzq , & rtP . b0degsec_Value [ 0 ] , & rtP .
Integrator_IC_fuz2mronvk , & rtP . nudegsec2_Mean [ 0 ] , & rtP .
nudegsec2_StdDev [ 0 ] , & rtP . nvdegsec_Mean [ 0 ] , & rtP .
nvdegsec_StdDev [ 0 ] , & rtP . TransferFcn_A [ 0 ] , & rtP . TransferFcn_C [
0 ] , & rtP . TransferFcn1_A_if5catdafx [ 0 ] , & rtP .
TransferFcn1_C_dr34rukazf [ 0 ] , & rtP . TransferFcn2_A [ 0 ] , & rtP .
TransferFcn2_C [ 0 ] , & rtP . NormalizeVector_maxzero_pk2yr3b0h2 , & rtP .
z0_const , & rtP . Constant_Value_hmchyhprrs , & rtP .
Constant1_Value_abguselunm [ 0 ] , & rtP . Constant2_Value_gegmpg2rvu [ 0 ] ,
& rtP . rad2deg_Gain , & rtP . noise_Mean , & rtP . noise1_Mean_gvm1mdzxhn ,
& rtP . NormalizeVector_maxzero_mjhj4dvvo1 , & rtP . z0_const_m1oeisvxny , &
rtP . Constant_Value_hupkchseos , & rtP . Constant1_Value_ej0jppt02k [ 0 ] ,
& rtP . Constant2_Value_cthnum5wwf [ 0 ] , & rtP . rad2deg_Gain_lqcbchbdpx ,
& rtP . noise_Mean_ieihuy3dfl , & rtP . noise1_Mean_dss5wuzq4c , & rtP .
NormalizeVector_maxzero_hdshd0fhdt , & rtP . z0_const_gejhxxdnvf , & rtP .
Constant_Value_ndyne2tsni , & rtP . Constant1_Value_la1yhx1hao [ 0 ] , & rtP
. Constant2_Value_gn4fk3d1lp [ 0 ] , & rtP . rad2deg_Gain_asjrxybn0x , & rtP
. noise_Mean_frav3j55dx , & rtP . noise1_Mean_mtptilkq10 , & rtP .
NormalizeVector_maxzero_ngb4rhu5uq , & rtP . z0_const_otzh2whnvs , & rtP .
Constant_Value_ghgnj1qkgx , & rtP . Constant1_Value_j0a4ub2khm [ 0 ] , & rtP
. Constant2_Value_aeurx5t4ck [ 0 ] , & rtP . rad2deg_Gain_okxkrd2arw , & rtP
. noise_Mean_gbwkny3l3m , & rtP . noise1_Mean_k2frfueqdx , & rtP .
NormalizeVector_maxzero_lt2ddtxhuf , & rtP . z0_const_h3tpk4wmcz , & rtP .
Constant_Value_ejbbt4py2k , & rtP . Constant1_Value_g3xactptzz [ 0 ] , & rtP
. Constant2_Value_kj0dkshoay [ 0 ] , & rtP . rad2deg_Gain_cmtkrwe5gj , & rtP
. noise_Mean_fjgbzgisby , & rtP . noise1_Mean_jkwutj3nv4 , & rtP .
NormalizeVector_maxzero_bj3cfn3har , & rtP . z0_const_pdn2lzrjdp , & rtP .
Constant_Value_iba131uo1r , & rtP . Constant1_Value_nc5rt4jowx [ 0 ] , & rtP
. Constant2_Value_nqgiw5gjgz [ 0 ] , & rtP . rad2deg_Gain_ncnor3j1vi , & rtP
. noise_Mean_hueo1gemyg , & rtP . noise1_Mean_m2yixhjiff , & rtP .
Constant_Value_i11k1gefwq [ 0 ] , & rtP . Constant2_Value_gqzethcbdt [ 0 ] ,
& rtP . UniformRandomNumber_Minimum , & rtP . UniformRandomNumber_Maximum , &
rtP . UniformRandomNumber_Seed , & rtP . Constant_Value_g3sjkewgl1 , & rtP .
Constant1_Value_hlcqpzkeg5 , & rtP . Constant2_Value_jyuv2gy0ao , & rtP .
Constant3_Value_axvubao2wd , & rtP . losstorquepropotionto_Gain , & rtP .
rad2rpm_Gain_l4jmsoyq2v , & rtP . Integrator_IC_mzfuiafljt , & rtP .
Switch_Threshold , & rtP . Switch1_Threshold_gkzjd52v3i , & rtP .
Switch2_Threshold , & rtP . TransferFcn1_A_dpe12qdgeu , & rtP .
TransferFcn1_C_mq40l21bd4 , & rtP . motor_D_c2y52zc0tt , & rtP .
Constant_Value_ovuyhiuyim , & rtP . Constant1_Value_oxbz4wjuse , & rtP .
Constant2_Value_pdtexc4kgl , & rtP . Constant3_Value_ds1jzpwkjt , & rtP .
losstorquepropotionto_Gain_hahtzed0yk , & rtP . rad2rpm_Gain , & rtP .
Integrator_IC , & rtP . Switch_Threshold_a5rkjww04l , & rtP .
Switch1_Threshold , & rtP . Switch2_Threshold_hj15nt1i3x , & rtP .
TransferFcn1_A , & rtP . TransferFcn1_C , & rtP . motor_D , & rtP .
Constant_Value_br1klnkrdq , & rtP . Constant1_Value_jbsud0br1l , & rtP .
Constant2_Value_lepgnru1ev , & rtP . Constant3_Value_pq0io1rx2d , & rtP .
losstorquepropotionto_Gain_ftpubwm50g , & rtP . rad2rpm_Gain_nwcckeryhk , &
rtP . Integrator_IC_hzjgu55ip5 , & rtP . Switch_Threshold_eczahcudx1 , & rtP
. Switch1_Threshold_lagl2moogx , & rtP . Switch2_Threshold_f3oy1s34eo , & rtP
. TransferFcn1_A_iljtckl0vf , & rtP . TransferFcn1_C_e5t3t2za0w , & rtP .
motor_D_p4qvhshwgu , & rtP . Constant_Value_kibc2xmwm0 , & rtP .
Constant1_Value_bvl32d0cmp , & rtP . Constant2_Value_oaj3bo5322 , & rtP .
Constant3_Value_ihqrcdemxt , & rtP . losstorquepropotionto_Gain_k3z3t2gd1a ,
& rtP . rad2rpm_Gain_pceq0ixqio , & rtP . Integrator_IC_ly1tqocwk2 , & rtP .
Switch_Threshold_mxo352pg2c , & rtP . Switch1_Threshold_nalfp5zuzj , & rtP .
Switch2_Threshold_fnlhdgazir , & rtP . TransferFcn1_A_bf2c2hk3jc , & rtP .
TransferFcn1_C_exc4t4wdx0 , & rtP . motor_D_ngzzpzruyi , & rtP . F107_Value ,
& rtP . aph_Value [ 0 ] , & rtP . flag_Value [ 0 ] , & rtP .
Constant_Value_ns0uhctphf , & rtP . Constant_Value_icfwmptllg , & rtP .
Constant1_Value_oqvdx5zpsu , & rtP . Constant2_Value_e1f4g20e1v , & rtP .
Constant_Value_amoommf0mg , & rtP . Gain_Gain_kyqyxgfjjc , & rtP .
Gain1_Gain_jdzh1vayht , & rtP . Gain2_Gain_mjvcbm4pqd , & rtP .
Constant_Value_mq4m5be1k3 , & rtP . Gain_Gain_ag50armt4q , & rtP .
Gain1_Gain_hahbyfhvn1 , & rtP . Gain2_Gain_bob4otocpt , & rtP .
Constant_Value_kcvsynl3gu , & rtP . Gain_Gain_du1axyb1td , & rtP .
Gain1_Gain_cjxo0bvxyl , & rtP . Gain2_Gain_cyuruau31y , & rtP .
Constant_Value_n0n1a4zdn2 , & rtP . Constant_Value_ggebjt2fys , & rtP .
Constant_Value_kxh4uvpty4 , & rtP . Constant_Value_kg1gkk2nel , & rtP .
RandomNumber_Mean [ 0 ] , & rtP . RandomNumber_StdDev [ 0 ] , & rtP .
noise3_Minimum , & rtP . ECEFPositiontoLLA_F_h5d2qe30it , & rtP .
ECEFPositiontoLLA_R_dv1fhj4bwm , & rtP . Constant_Value_lxzojy1yts , & rtP .
Constant_Value_m2hdvkft2v , & rtP . Constant_Value_iqckjhnrkz , & rtP .
Constant_Value_fvwnrwg2d1 , & rtP . Constant_Value_fnhawrwcfw , & rtP .
Constant_Value_k3ehwbv3db , & rtP . Gain_Gain_jiwysirinb , & rtP .
Gain_Gain_gueaxs1w4d , & rtP . Gain_Gain_o54eldgojd , & rtP .
Gain_Gain_gdjmrybomw , & rtP . Gain_Gain_jzbglr3iwn , & rtP .
Gain_Gain_ijnc3iled3 , & rtP . Constant_Value , & rtP . Gain_Gain , & rtP .
Gain1_Gain , & rtP . Gain2_Gain , & rtP . Constant_Value_kjzrxx2pwp , & rtP .
Gain_Gain_dkxjnn2goq , & rtP . Gain1_Gain_ewxpcgxoho , & rtP .
Gain2_Gain_lev0onxthq , & rtP . Constant_Value_a2453xvslr , & rtP .
Gain_Gain_kwo0jnespy , & rtP . Gain1_Gain_oz4csetmxu , & rtP .
Gain2_Gain_ekmxnyjdgq , & rtP . gcm3kgm3_Gain , & rtP .
Constant_Value_p1jiuwoh41 , & rtP . Gain_Gain_eirpwpy25e , & rtP .
Gain1_Gain_o0zodm4wod , & rtP . Gain2_Gain_nbadgk3cn2 , & rtP .
Constant_Value_boboxxtlqz , & rtP . Gain_Gain_cng034c550 , & rtP .
Gain1_Gain_kzqbx21odb , & rtP . Gain2_Gain_jw4ny4s1oi , & rtP .
Constant_Value_gtgl4kppkk , & rtP . Gain_Gain_lv4xtg4q1g , & rtP .
Gain1_Gain_pmepj0f34k , & rtP . Gain2_Gain_nafalxbj3s , & rtP .
Constant_Value_ckovqqesxd , & rtP . Gain_Gain_kpmqxdzy5m , & rtP .
Gain1_Gain_k3bjbhd2mm , & rtP . Gain2_Gain_pyvsmmmr0o , & rtP .
Constant_Value_og0eeytiqd , & rtP . Gain_Gain_bsruw13utp , & rtP .
Gain1_Gain_gox4r1jkwy , & rtP . Gain2_Gain_gvo2u1fvu1 , & rtP .
Constant_Value_dxdbvme4z2 , & rtP . Gain_Gain_b0hzjatx0r , & rtP .
Gain1_Gain_i30g2qbzrq , & rtP . Gain2_Gain_p5meiylvde , & rtP .
Constant_Value_kblt0a3uql , & rtP . Gain_Gain_fso4j4ph32 , & rtP .
Gain1_Gain_c2qfvofd2q , & rtP . Gain2_Gain_fbbevcwdu4 , & rtP .
Constant_Value_hgvjimspu2 , & rtP . Gain_Gain_cuyfsgurxk , & rtP .
Gain1_Gain_p0weipavif , & rtP . Gain2_Gain_o2m2nfo04s , & rtP .
Constant_Value_jyoylqpxtd , & rtP . Gain_Gain_mtzedpzgxf , & rtP .
Gain1_Gain_fpivyqdmyd , & rtP . Gain2_Gain_eknqknt03s , & rtP .
Constant_Value_czynuf313b , & rtP . Gain_Gain_l1oovl4sve , & rtP .
Gain1_Gain_bysm1h5wxu , & rtP . Gain2_Gain_ckacseigw1 , & rtP .
Constant_Value_h4xungkdn0 , & rtP . Gain_Gain_iduukqmyr5 , & rtP .
Gain1_Gain_bv1sce1ofn , & rtP . Gain2_Gain_kdxyjqh15k , & rtP .
Constant_Value_but5tairxf , & rtP . Gain_Gain_py1ocxtdbg , & rtP .
Gain1_Gain_jhnqeojsbu , & rtP . Gain2_Gain_dmh23oivep , & rtP .
Constant_Value_ckqmocsjmk , & rtP . Gain_Gain_p0g5ioz0tt , & rtP .
Gain1_Gain_l1syl1i1nc , & rtP . Gain2_Gain_bprrd5rgzt , & rtP .
Constant_Value_jdq04jy3wj , & rtP . Gain_Gain_cdekolw0kh , & rtP .
Gain1_Gain_mbywpxkyv2 , & rtP . Gain2_Gain_inxlw0u2vd , & rtP .
Constant_Value_mydahigf2l , & rtP . Gain_Gain_gnbof3p2ih , & rtP .
Gain1_Gain_ai10xj1huz , & rtP . Gain2_Gain_aryjtg3qqc , & rtY . jwku2vbe0w ,
& rtY . fudrm4x01v , & rtY . nza55qah0g [ 0 ] , & rtP . ADSW , & rtP . CD , &
rtP . CR , & rtP . GAS_Vref , & rtP . GAS_b2c [ 0 ] , & rtP . GAS_seed1 [ 0 ]
, & rtP . GE , & rtP . GGSW , & rtP . GPS_position_seed [ 0 ] , & rtP .
GPS_time_noise , & rtP . GPS_time_seed , & rtP . GPperturbationSW , & rtP .
GYRO_b2c [ 0 ] , & rtP . GYRO_seed1 [ 0 ] , & rtP . GYRO_seed2 [ 0 ] , & rtP
. I [ 0 ] , & rtP . J2 , & rtP . MTQ_c2b [ 0 ] , & rtP . NSAS1_b2c [ 0 ] , &
rtP . NSAS2_b2c [ 0 ] , & rtP . NSAS3_b2c [ 0 ] , & rtP . NSAS4_b2c [ 0 ] , &
rtP . NSAS5_b2c [ 0 ] , & rtP . NSAS6_b2c [ 0 ] , & rtP . NSAS_ang_limit , &
rtP . NSAS_seed1 , & rtP . NSAS_seed2 , & rtP . NSAS_x_noise , & rtP .
NSAS_y_noise , & rtP . RW_Gamp , & rtP . RW_J , & rtP . RW_Rsc , & rtP .
RW_kE , & rtP . RW_kT , & rtP . SRPSW , & rtP . STT1_b2c_quat [ 0 ] , & rtP .
STT_AD_prob , & rtP . STT_FOV , & rtP . STT_moon_ang_limit , & rtP .
STT_seed1 [ 0 ] , & rtP . STT_sun_ang_limit , & rtP . TOLERANCE , & rtP .
UT1_UTC , & rtP . area , & rtP . arm [ 0 ] , & rtP . earth_radius , & rtP .
ele [ 0 ] , & rtP . jd , & rtP . pSR , & rtP . q_ini [ 0 ] , & rtP . rem_mag
[ 0 ] , & rtP . rem_magSW , & rtP . three_one_skew_matrix [ 0 ] , & rtP . wE
[ 0 ] , & rtP . w_ini [ 0 ] , } ; static int32_T * rtVarDimsAddrMap [ ] = { (
NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } ,
{ "unsigned char" , "uint8_T" , 0 , 0 , sizeof ( uint8_T ) , ( uint8_T )
SS_UINT8 , 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } , {
rtwCAPI_VECTOR , 8 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 10 , 2 , 0 } , {
rtwCAPI_VECTOR , 12 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 14 , 2 , 0 } , {
rtwCAPI_VECTOR , 16 , 2 , 0 } , { rtwCAPI_VECTOR , 18 , 2 , 0 } , {
rtwCAPI_VECTOR , 20 , 2 , 0 } , { rtwCAPI_VECTOR , 22 , 2 , 0 } , {
rtwCAPI_VECTOR , 2 , 2 , 0 } , { rtwCAPI_VECTOR , 24 , 2 , 0 } , {
rtwCAPI_VECTOR , 26 , 2 , 0 } , { rtwCAPI_VECTOR , 28 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 30 , 2 , 0 } , { rtwCAPI_VECTOR , 10 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 32 , 2 , 0 } } ; static const uint_T
rtDimensionArray [ ] = { 1 , 1 , 1 , 4 , 3 , 1 , 4 , 1 , 2 , 1 , 1 , 6 , 6 ,
1 , 1 , 12 , 7 , 1 , 23 , 1 , 9 , 1 , 1 , 3 , 1 , 2 , 1 , 7 , 1 , 23 , 3 , 3
, 3 , 4 } ; static const real_T rtcapiStoredFloats [ ] = { 0.0 , 0.05 , 0.01
} ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , (
int8_T ) 0 , ( uint8_T ) 0 } , { ( NULL ) , ( NULL ) , 3 , 0 } , { ( const
void * ) & rtcapiStoredFloats [ 1 ] , ( const void * ) & rtcapiStoredFloats [
0 ] , ( int8_T ) 2 , ( uint8_T ) 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , (
int8_T ) 1 , ( uint8_T ) 0 } } ; static rtwCAPI_ModelMappingStaticInfo
mmiStatic = { { rtBlockSignals , 152 , rtRootInputs , 0 , rtRootOutputs , 3 }
, { rtBlockParameters , 314 , rtModelParameters , 55 } , { ( NULL ) , 0 } , {
rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap
, rtDimensionArray } , "float" , { 2405234056U , 151909971U , 1794605402U ,
3767048926U } , ( NULL ) , 0 , ( boolean_T ) 0 , rt_LoggedStateIdxList } ;
const rtwCAPI_ModelMappingStaticInfo * SILS_20241709_GetCAPIStaticMap ( void
) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void SILS_20241709_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void SILS_20241709_host_InitializeDataMapInfo (
SILS_20241709_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetPath ( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap ->
mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
