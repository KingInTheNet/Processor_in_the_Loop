#include "SILS_20241709.h"
#include "rtwtypes.h"
#include "SILS_20241709_private.h"
#include "mwmathutil.h"
#include <string.h>
#include <math.h>
#include <emmintrin.h>
#include "rt_logging_mmi.h"
#include "SILS_20241709_capi.h"
#include "SILS_20241709_dt.h"
#include "sfcn_loader_c_api.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; void
raccelForceExtModeShutdown ( boolean_T extModeStartPktReceived ) { if ( !
extModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 3 , & stopRequested ) ; }
rtExtModeShutdown ( 3 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_sim_engine.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 1 ; int_T gbl_raccel_NumST = 4 ; const char_T
* gbl_raccel_Version = "9.8 (R2022b) 13-May-2022" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const int_T gblNumRootInportBlks = 0 ; const int_T
gblNumModelInputs = 0 ; extern const char * gblInportFileName ; extern
rtInportTUtable * gblInportTUtables ; const int_T gblInportDataTypeIdx [ ] =
{ - 1 } ; const int_T gblInportDims [ ] = { - 1 } ; const int_T
gblInportComplex [ ] = { - 1 } ; const int_T gblInportInterpoFlag [ ] = { - 1
} ; const int_T gblInportContinuous [ ] = { - 1 } ; int_T enableFcnCallFlag [
] = { 1 , 1 , 1 , 1 } ; const char * raccelLoadInputsAndAperiodicHitTimes (
SimStruct * S , const char * inportFileName , int * matFileFormat ) { return
rt_RAccelReadInportsMatFile ( S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
const real_T SILS_20241709_RGND = 0.0 ; B rtB ; X rtX ; DW rtDW ; ExtY rtY ;
static SimStruct model_S ; SimStruct * const rtS = & model_S ; static real_T
aq3jzkyuad ( const real_T x [ 3 ] ) ; static boolean_T jd5umm0a5g ( real_T
year ) ; void fsnekqmcuz ( const real_T cxpbrxwvph [ 3 ] , const real_T
mq5wdpevr4 [ 3 ] , oct3g4vhoh * localB ) { localB -> aupbtlrqjk [ 0 ] =
cxpbrxwvph [ 1 ] * mq5wdpevr4 [ 2 ] - mq5wdpevr4 [ 1 ] * cxpbrxwvph [ 2 ] ;
localB -> aupbtlrqjk [ 1 ] = mq5wdpevr4 [ 0 ] * cxpbrxwvph [ 2 ] - cxpbrxwvph
[ 0 ] * mq5wdpevr4 [ 2 ] ; localB -> aupbtlrqjk [ 2 ] = cxpbrxwvph [ 0 ] *
mq5wdpevr4 [ 1 ] - mq5wdpevr4 [ 0 ] * cxpbrxwvph [ 1 ] ; } void lkjrchjyiy (
const real_T ff43jzuww3 [ 3 ] , real_T mzyoemzng2 , real_T mklgzo1miu ,
real_T gcqtcaennh , pigla2omys * localB ) { localB -> c1nd5nsrgs [ 0 ] =
ff43jzuww3 [ 1 ] * gcqtcaennh - mklgzo1miu * ff43jzuww3 [ 2 ] ; localB ->
c1nd5nsrgs [ 1 ] = mzyoemzng2 * ff43jzuww3 [ 2 ] - ff43jzuww3 [ 0 ] *
gcqtcaennh ; localB -> c1nd5nsrgs [ 2 ] = ff43jzuww3 [ 0 ] * mklgzo1miu -
mzyoemzng2 * ff43jzuww3 [ 1 ] ; } void bjzuls4oiv ( real_T c0vftrcglr ,
cyjo4x5ck1 * localB ) { real_T b_x ; real_T fday ; real_T in2 ; fday = (
c0vftrcglr + 0.5 ) - muDoubleScalarFloor ( c0vftrcglr + 0.5 ) ; in2 =
muDoubleScalarFloor ( c0vftrcglr + 0.5 ) ; in2 += muDoubleScalarFloor (
muDoubleScalarFloor ( ( in2 - 4479.5 ) / 36524.25 ) * 0.75 + 0.5 ) - 37.0 ;
localB -> crs3vbajbr = muDoubleScalarFloor ( in2 / 365.25 ) - 4712.0 ; in2 =
muDoubleScalarFloor ( ( in2 - 59.25 ) - muDoubleScalarFloor ( ( in2 - 59.25 )
/ 365.25 ) * 365.25 ) ; b_x = muDoubleScalarFloor ( ( in2 + 0.5 ) / 30.6 ) ;
localB -> pyqwe5rsse = ( ( b_x + 2.0 ) - muDoubleScalarFloor ( ( b_x + 2.0 )
/ 12.0 ) * 12.0 ) + 1.0 ; localB -> agveekqpqv = ( ( in2 + 0.5 ) -
muDoubleScalarFloor ( ( in2 + 0.5 ) / 30.6 ) * 30.6 ) + 1.0 ; localB ->
agveekqpqv = muDoubleScalarFloor ( localB -> agveekqpqv ) ; localB ->
le233aiaq5 = fday * 24.0 ; localB -> le233aiaq5 = muDoubleScalarFloor (
localB -> le233aiaq5 ) ; localB -> b2jeeweznc = ( fday * 24.0 -
muDoubleScalarFloor ( fday * 24.0 ) ) * 60.0 ; localB -> b2jeeweznc =
muDoubleScalarFloor ( localB -> b2jeeweznc ) ; localB -> cnte5pmho4 = ( fday
* 24.0 * 60.0 * 60.0 - muDoubleScalarFloor ( fday * 24.0 ) * 60.0 * 60.0 ) -
muDoubleScalarFloor ( ( fday * 24.0 - muDoubleScalarFloor ( fday * 24.0 ) ) *
60.0 ) * 60.0 ; } void ivx0j3mj3l ( const real_T i5kphrrr2y [ 9 ] , const
real_T m4eydfuwzq [ 3 ] , d5mabmixx5 * localB ) { int32_T i ; for ( i = 0 ; i
< 3 ; i ++ ) { localB -> poahfmj3s1 [ i ] = 0.0 ; localB -> poahfmj3s1 [ i ]
+= i5kphrrr2y [ i ] * m4eydfuwzq [ 0 ] ; localB -> poahfmj3s1 [ i ] +=
i5kphrrr2y [ i + 3 ] * m4eydfuwzq [ 1 ] ; localB -> poahfmj3s1 [ i ] +=
i5kphrrr2y [ i + 6 ] * m4eydfuwzq [ 2 ] ; } } void ajln0dl4w5 ( real_T
kqww0sjoke , real_T obxid0zk5a , oxebiebxcs * localB ) { localB -> a4ujzgnsun
= muDoubleScalarAsin ( obxid0zk5a / ( obxid0zk5a + kqww0sjoke ) ) ; } void
n4mcthnbsb ( const real_T mzw1h4tlas [ 9 ] , real_T gydnt10vhl , real_T
pgiit2glgs , real_T eav11ieugn , haq3dksarh * localB ) { int32_T i ; for ( i
= 0 ; i < 3 ; i ++ ) { localB -> owg3qz0vb0 [ i ] = 0.0 ; localB ->
owg3qz0vb0 [ i ] += mzw1h4tlas [ i ] * gydnt10vhl ; localB -> owg3qz0vb0 [ i
] += mzw1h4tlas [ i + 3 ] * pgiit2glgs ; localB -> owg3qz0vb0 [ i ] +=
mzw1h4tlas [ i + 6 ] * eav11ieugn ; } } void llkwb1gopr ( const real_T
m3lcewolkc [ 9 ] , real_T nxvel350vb , real_T kydlusovm3 , real_T knmjfmjkag
, bmt3ngprbx * localB ) { int32_T i ; for ( i = 0 ; i < 3 ; i ++ ) { localB
-> osxy5zocx5 [ i ] = 0.0 ; localB -> osxy5zocx5 [ i ] += m3lcewolkc [ i ] *
nxvel350vb ; localB -> osxy5zocx5 [ i ] += m3lcewolkc [ i + 3 ] * kydlusovm3
; localB -> osxy5zocx5 [ i ] += m3lcewolkc [ i + 6 ] * knmjfmjkag ; } } void
e3r1b51sa5 ( real_T itzvgvcmcv , real_T nzpyxtxcny , gacwgjuhge * localB ) {
localB -> fkae5wqtcb = itzvgvcmcv ; if ( nzpyxtxcny == 1.0 ) { localB ->
fkae5wqtcb = - itzvgvcmcv ; } } void gla0ncnrx0 ( real_T lymk5v0m2t , real_T
ppz354xn4r , real_T l2fqg1kzln , fbvoxbsppm * localB ) { localB -> ozezoxky3t
= 1.0 ; localB -> g5m2irbsxw = 0.0 ; localB -> h5cyove4ef = 0.0 ; if (
lymk5v0m2t == 0.0 ) { localB -> ozezoxky3t = 0.0 ; } if ( muDoubleScalarAbs (
ppz354xn4r ) > 37.0 ) { localB -> ozezoxky3t = 0.0 ; localB -> g5m2irbsxw =
1.0 ; } if ( muDoubleScalarAbs ( l2fqg1kzln ) > 3.0 ) { localB -> ozezoxky3t
= 0.0 ; localB -> h5cyove4ef = 1.0 ; } } void g3res1bek1 ( real_T ha5qtaji51
, fuwz32fyfq * localB ) { localB -> nd52bn25fb = ! ( ha5qtaji51 > 0.0 ) ; }
void fgza3nsgzk ( real_T c1st5kmkya , hdyhizuepg * localB ) { localB ->
h0dxk1yimp = ! ( c1st5kmkya > 0.0 ) ; localB -> jeak4pqr3j =
muDoubleScalarAbs ( c1st5kmkya ) ; } real_T rt_urand_Upu32_Yd_f_pw_snf (
uint32_T * u ) { uint32_T hi ; uint32_T lo ; lo = * u % 127773U * 16807U ; hi
= * u / 127773U * 2836U ; if ( lo < hi ) { * u = 2147483647U - ( hi - lo ) ;
} else { * u = lo - hi ; } return ( real_T ) * u * 4.6566128752457969E-10 ; }
real_T rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { real_T si ; real_T sr ;
real_T y ; do { sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = 2.0
* rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = sr * sr + si * si ; } while (
si > 1.0 ) ; y = muDoubleScalarSqrt ( - 2.0 * muDoubleScalarLog ( si ) / si )
* sr ; return y ; } static real_T aq3jzkyuad ( const real_T x [ 3 ] ) {
real_T absxk ; real_T scale ; real_T t ; real_T y ; scale =
3.3121686421112381E-170 ; absxk = muDoubleScalarAbs ( x [ 0 ] ) ; if ( absxk
> 3.3121686421112381E-170 ) { y = 1.0 ; scale = absxk ; } else { t = absxk /
3.3121686421112381E-170 ; y = t * t ; } absxk = muDoubleScalarAbs ( x [ 1 ] )
; if ( absxk > scale ) { t = scale / absxk ; y = y * t * t + 1.0 ; scale =
absxk ; } else { t = absxk / scale ; y += t * t ; } absxk = muDoubleScalarAbs
( x [ 2 ] ) ; if ( absxk > scale ) { t = scale / absxk ; y = y * t * t + 1.0
; scale = absxk ; } else { t = absxk / scale ; y += t * t ; } return scale *
muDoubleScalarSqrt ( y ) ; } static boolean_T jd5umm0a5g ( real_T year ) {
return ( ( ! ( muDoubleScalarRem ( year , 4.0 ) != 0.0 ) ) && (
muDoubleScalarRem ( year , 100.0 ) != 0.0 ) ) || ( ! ( muDoubleScalarRem (
year , 400.0 ) != 0.0 ) ) ; } void rt_invd3x3_snf ( const real_T u [ 9 ] ,
real_T y [ 9 ] ) { real_T x [ 9 ] ; real_T absx11 ; real_T absx21 ; real_T
absx31 ; int32_T itmp ; int32_T p1 ; int32_T p2 ; int32_T p3 ; memcpy ( & x [
0 ] , & u [ 0 ] , 9U * sizeof ( real_T ) ) ; p1 = 1 ; p2 = 3 ; p3 = 6 ;
absx11 = muDoubleScalarAbs ( u [ 0 ] ) ; absx21 = muDoubleScalarAbs ( u [ 1 ]
) ; absx31 = muDoubleScalarAbs ( u [ 2 ] ) ; if ( ( absx21 > absx11 ) && (
absx21 > absx31 ) ) { p1 = 4 ; p2 = 0 ; x [ 0 ] = u [ 1 ] ; x [ 1 ] = u [ 0 ]
; x [ 3 ] = u [ 4 ] ; x [ 4 ] = u [ 3 ] ; x [ 6 ] = u [ 7 ] ; x [ 7 ] = u [ 6
] ; } else if ( absx31 > absx11 ) { p1 = 7 ; p3 = 0 ; x [ 2 ] = x [ 0 ] ; x [
0 ] = u [ 2 ] ; x [ 5 ] = x [ 3 ] ; x [ 3 ] = u [ 5 ] ; x [ 8 ] = x [ 6 ] ; x
[ 6 ] = u [ 8 ] ; } absx11 = x [ 1 ] / x [ 0 ] ; x [ 1 ] /= x [ 0 ] ; absx21
= x [ 2 ] / x [ 0 ] ; x [ 2 ] /= x [ 0 ] ; x [ 4 ] -= absx11 * x [ 3 ] ; x [
5 ] -= absx21 * x [ 3 ] ; x [ 7 ] -= absx11 * x [ 6 ] ; x [ 8 ] -= absx21 * x
[ 6 ] ; if ( muDoubleScalarAbs ( x [ 5 ] ) > muDoubleScalarAbs ( x [ 4 ] ) )
{ itmp = p2 ; p2 = p3 ; p3 = itmp ; x [ 1 ] = absx21 ; x [ 2 ] = absx11 ;
absx11 = x [ 4 ] ; x [ 4 ] = x [ 5 ] ; x [ 5 ] = absx11 ; absx11 = x [ 7 ] ;
x [ 7 ] = x [ 8 ] ; x [ 8 ] = absx11 ; } absx11 = x [ 5 ] / x [ 4 ] ; x [ 5 ]
/= x [ 4 ] ; x [ 8 ] -= absx11 * x [ 7 ] ; absx11 = ( x [ 1 ] * x [ 5 ] - x [
2 ] ) / x [ 8 ] ; absx21 = - ( x [ 7 ] * absx11 + x [ 1 ] ) / x [ 4 ] ; y [
p1 - 1 ] = ( ( 1.0 - x [ 3 ] * absx21 ) - x [ 6 ] * absx11 ) / x [ 0 ] ; y [
p1 ] = absx21 ; y [ p1 + 1 ] = absx11 ; absx11 = - x [ 5 ] / x [ 8 ] ; absx21
= ( 1.0 - x [ 7 ] * absx11 ) / x [ 4 ] ; y [ p2 ] = - ( x [ 3 ] * absx21 + x
[ 6 ] * absx11 ) / x [ 0 ] ; y [ p2 + 1 ] = absx21 ; y [ p2 + 2 ] = absx11 ;
absx11 = 1.0 / x [ 8 ] ; absx21 = - x [ 7 ] * absx11 / x [ 4 ] ; y [ p3 ] = -
( x [ 3 ] * absx21 + x [ 6 ] * absx11 ) / x [ 0 ] ; y [ p3 + 1 ] = absx21 ; y
[ p3 + 2 ] = absx11 ; } void MdlInitialize ( void ) { real_T tmp_p ; int32_T
r ; int32_T t ; uint32_T tseed ; boolean_T tmp ; rtX . hjkn3n4lly [ 0 ] = rtP
. w_ini [ 0 ] ; rtX . hjkn3n4lly [ 1 ] = rtP . w_ini [ 1 ] ; rtX . hjkn3n4lly
[ 2 ] = rtP . w_ini [ 2 ] ; rtDW . cu35sqihey = 1 ; if ( ssIsFirstInitCond (
rtS ) ) { rtX . oxovzkyrgp [ 0 ] = 7009.1037527181206 ; rtX . oxovzkyrgp [ 1
] = 0.0010552 ; rtX . oxovzkyrgp [ 2 ] = 1.7086389404589049 ; rtX .
oxovzkyrgp [ 3 ] = 4.5979041081001215 ; rtX . oxovzkyrgp [ 4 ] =
4.73949219833891 ; rtX . oxovzkyrgp [ 5 ] = 1.5436669289018967 ; tmp =
slIsRapidAcceleratorSimulating ( ) ; if ( tmp ) { tmp =
ssGetGlobalInitialStatesAvailable ( rtS ) ; rtDW . cu35sqihey = ! tmp ; }
else { rtDW . cu35sqihey = 1 ; } } rtX . pcdkwn41rb [ 0 ] = rtP . q_ini [ 0 ]
; rtX . pcdkwn41rb [ 1 ] = rtP . q_ini [ 1 ] ; rtX . pcdkwn41rb [ 2 ] = rtP .
q_ini [ 2 ] ; rtX . pcdkwn41rb [ 3 ] = rtP . q_ini [ 3 ] ; rtX . l50b0cuk2h =
0.0 ; rtX . b4ena3lr0n = rtP . Integrator_IC ; rtX . lbdfwq1i3y = 0.0 ; rtX .
fnheb54sgb = rtP . Integrator_IC_mzfuiafljt ; rtX . muv5xwjpjd = 0.0 ; rtX .
argwmtgb5v = rtP . Integrator_IC_hzjgu55ip5 ; rtX . bxdhuzrxz2 = 0.0 ; rtX .
cmyui1ww54 = rtP . Integrator_IC_ly1tqocwk2 ; tmp_p = muDoubleScalarFloor (
rtP . STT_seed1 [ 0 ] ) ; if ( muDoubleScalarIsNaN ( tmp_p ) ||
muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . kjzrcidvjf [
0 ] = tseed ; rtDW . hrquh23lee [ 0 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
kjzrcidvjf [ 0 ] ) * rtP . noise1_StdDev [ 0 ] + rtP . noise1_Mean [ 0 ] ;
tmp_p = muDoubleScalarFloor ( rtP . STT_seed1 [ 1 ] ) ; if (
muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . kjzrcidvjf [ 1 ] = tseed ; rtDW . hrquh23lee [ 1 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjzrcidvjf [ 1 ] ) * rtP .
noise1_StdDev [ 1 ] + rtP . noise1_Mean [ 1 ] ; tmp_p = muDoubleScalarFloor (
rtP . STT_seed1 [ 2 ] ) ; if ( muDoubleScalarIsNaN ( tmp_p ) ||
muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . kjzrcidvjf [
2 ] = tseed ; rtDW . hrquh23lee [ 2 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
kjzrcidvjf [ 2 ] ) * rtP . noise1_StdDev [ 2 ] + rtP . noise1_Mean [ 2 ] ;
tmp_p = muDoubleScalarFloor ( rtP . UniformRandomNumber_Seed ) ; if (
muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . mc4jx3i45v = tseed ; rtDW . bya5fxrz4g = ( rtP .
UniformRandomNumber_Maximum - rtP . UniformRandomNumber_Minimum ) *
rt_urand_Upu32_Yd_f_pw_snf ( & rtDW . mc4jx3i45v ) + rtP .
UniformRandomNumber_Minimum ; rtX . i1iguten22 [ 0 ] = 0.0 ; rtX . pkf1lgikiz
[ 0 ] = 0.0 ; rtX . f3jtaj41sb [ 0 ] = 0.0 ; rtX . i1iguten22 [ 1 ] = 0.0 ;
rtX . pkf1lgikiz [ 1 ] = 0.0 ; rtX . f3jtaj41sb [ 1 ] = 0.0 ; tmp_p =
muDoubleScalarFloor ( rtP . NSAS_seed1 ) ; if ( muDoubleScalarIsNaN ( tmp_p )
|| muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . eqyhiq4b21 =
tseed ; rtDW . ldpiguzau3 = muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP .
NSAS_x_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . eqyhiq4b21 ) + rtP .
noise_Mean ; tmp_p = muDoubleScalarFloor ( rtP . NSAS_seed2 ) ; if (
muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . pvrk0p3rm1 = tseed ; rtDW . jx2njiskco = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
pvrk0p3rm1 ) + rtP . noise1_Mean_gvm1mdzxhn ; tmp_p = muDoubleScalarFloor (
rtP . NSAS_seed1 ) ; if ( muDoubleScalarIsNaN ( tmp_p ) ||
muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . jlc5fbv0er =
tseed ; rtDW . fg3gr5w1yf = muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP .
NSAS_x_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . jlc5fbv0er ) + rtP .
noise_Mean_ieihuy3dfl ; tmp_p = muDoubleScalarFloor ( rtP . NSAS_seed2 ) ; if
( muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . mcbywo0nsz = tseed ; rtDW . l0mqdwlhk0 = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
mcbywo0nsz ) + rtP . noise1_Mean_dss5wuzq4c ; tmp_p = muDoubleScalarFloor (
rtP . NSAS_seed1 ) ; if ( muDoubleScalarIsNaN ( tmp_p ) ||
muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . izuwdoquaq =
tseed ; rtDW . b5i1u5nxk5 = muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP .
NSAS_x_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . izuwdoquaq ) + rtP .
noise_Mean_frav3j55dx ; tmp_p = muDoubleScalarFloor ( rtP . NSAS_seed2 ) ; if
( muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . iy3vcqbba5 = tseed ; rtDW . ik23rulsvu = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
iy3vcqbba5 ) + rtP . noise1_Mean_mtptilkq10 ; tmp_p = muDoubleScalarFloor (
rtP . NSAS_seed1 ) ; if ( muDoubleScalarIsNaN ( tmp_p ) ||
muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . inevc2d42p =
tseed ; rtDW . ia3ohifukf = muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP .
NSAS_x_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . inevc2d42p ) + rtP .
noise_Mean_gbwkny3l3m ; tmp_p = muDoubleScalarFloor ( rtP . NSAS_seed2 ) ; if
( muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . omztnckksa = tseed ; rtDW . ewzxpp1cyz = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
omztnckksa ) + rtP . noise1_Mean_k2frfueqdx ; tmp_p = muDoubleScalarFloor (
rtP . NSAS_seed1 ) ; if ( muDoubleScalarIsNaN ( tmp_p ) ||
muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . peboqqfifh =
tseed ; rtDW . hdjjo4r4gm = muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP .
NSAS_x_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . peboqqfifh ) + rtP .
noise_Mean_fjgbzgisby ; tmp_p = muDoubleScalarFloor ( rtP . NSAS_seed2 ) ; if
( muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . hjlfer4jb5 = tseed ; rtDW . coji3apumi = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
hjlfer4jb5 ) + rtP . noise1_Mean_jkwutj3nv4 ; tmp_p = muDoubleScalarFloor (
rtP . NSAS_seed1 ) ; if ( muDoubleScalarIsNaN ( tmp_p ) ||
muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . bhy4lqzamt =
tseed ; rtDW . m2ylj5cu2h = muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP .
NSAS_x_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . bhy4lqzamt ) + rtP .
noise_Mean_hueo1gemyg ; tmp_p = muDoubleScalarFloor ( rtP . NSAS_seed2 ) ; if
( muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . l3fdu4jify = tseed ; rtDW . dbnkttelok = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
l3fdu4jify ) + rtP . noise1_Mean_m2yixhjiff ; tmp_p = muDoubleScalarFloor (
rtP . GAS_seed1 [ 0 ] ) ; if ( muDoubleScalarIsNaN ( tmp_p ) ||
muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . dplhf1lj21 [
0 ] = tseed ; rtDW . fzlqp4iexm [ 0 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
dplhf1lj21 [ 0 ] ) * rtP . noise_StdDev [ 0 ] + rtP . noise_Mean_m211emgdl3 [
0 ] ; tmp_p = muDoubleScalarFloor ( rtP . GAS_seed1 [ 1 ] ) ; if (
muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . dplhf1lj21 [ 1 ] = tseed ; rtDW . fzlqp4iexm [ 1 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dplhf1lj21 [ 1 ] ) * rtP . noise_StdDev
[ 1 ] + rtP . noise_Mean_m211emgdl3 [ 1 ] ; tmp_p = muDoubleScalarFloor ( rtP
. GAS_seed1 [ 2 ] ) ; if ( muDoubleScalarIsNaN ( tmp_p ) ||
muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . dplhf1lj21 [
2 ] = tseed ; rtDW . fzlqp4iexm [ 2 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
dplhf1lj21 [ 2 ] ) * rtP . noise_StdDev [ 2 ] + rtP . noise_Mean_m211emgdl3 [
2 ] ; rtX . ae0okdyidm = 0.0 ; rtX . cok521zc4f = 0.0 ; rtX . pf4hzftljn =
0.0 ; tmp_p = muDoubleScalarFloor ( rtP . GPS_position_seed [ 0 ] ) ; if (
muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . kjjgprkxtu [ 0 ] = tseed ; rtDW . hsxmncoiha [ 0 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjjgprkxtu [ 0 ] ) * rtP .
RandomNumber_StdDev [ 0 ] + rtP . RandomNumber_Mean [ 0 ] ; tmp_p =
muDoubleScalarFloor ( rtP . GPS_position_seed [ 1 ] ) ; if (
muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . kjjgprkxtu [ 1 ] = tseed ; rtDW . hsxmncoiha [ 1 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjjgprkxtu [ 1 ] ) * rtP .
RandomNumber_StdDev [ 1 ] + rtP . RandomNumber_Mean [ 1 ] ; tmp_p =
muDoubleScalarFloor ( rtP . GPS_position_seed [ 2 ] ) ; if (
muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . kjjgprkxtu [ 2 ] = tseed ; rtDW . hsxmncoiha [ 2 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjjgprkxtu [ 2 ] ) * rtP .
RandomNumber_StdDev [ 2 ] + rtP . RandomNumber_Mean [ 2 ] ; tmp_p =
muDoubleScalarFloor ( rtP . GPS_time_seed ) ; if ( muDoubleScalarIsNaN (
tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . eh3i2huuk3 =
tseed ; rtDW . bpg2iofpcz = ( rtP . GPS_time_noise - rtP . noise3_Minimum ) *
rt_urand_Upu32_Yd_f_pw_snf ( & rtDW . eh3i2huuk3 ) + rtP . noise3_Minimum ;
rtX . ek1dcgndv4 = 0.0 ; rtX . iyvywkyjkt = 0.0 ; rtX . cscwx5acjj = 0.0 ;
rtX . l0nfea2luh [ 0 ] = rtP . Integrator_IC_fuz2mronvk ; tmp_p =
muDoubleScalarFloor ( rtP . GYRO_seed1 [ 0 ] ) ; if ( muDoubleScalarIsNaN (
tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . dslhvlg4ym [
0 ] = tseed ; rtDW . i3rfdszits [ 0 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
dslhvlg4ym [ 0 ] ) * rtP . nvdegsec_StdDev [ 0 ] + rtP . nvdegsec_Mean [ 0 ]
; tmp_p = muDoubleScalarFloor ( rtP . GYRO_seed2 [ 0 ] ) ; if (
muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . czp4qnh0py [ 0 ] = tseed ; rtDW . achzjspzj0 [ 0 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . czp4qnh0py [ 0 ] ) * rtP .
nudegsec2_StdDev [ 0 ] + rtP . nudegsec2_Mean [ 0 ] ; rtB . hm15o25lmb [ 0 ]
= rtP . GPperturbation_RSW_kms2_3_Y0 [ 0 ] ; rtB . b5ehs0zt32 [ 0 ] = rtP .
GG_b_Nm_3_Y0 [ 0 ] ; rtX . l0nfea2luh [ 1 ] = rtP . Integrator_IC_fuz2mronvk
; tmp_p = muDoubleScalarFloor ( rtP . GYRO_seed1 [ 1 ] ) ; if (
muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p =
0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed
= tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T
) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U
) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) <<
16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed =
1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U ; }
rtDW . dslhvlg4ym [ 1 ] = tseed ; rtDW . i3rfdszits [ 1 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dslhvlg4ym [ 1 ] ) * rtP .
nvdegsec_StdDev [ 1 ] + rtP . nvdegsec_Mean [ 1 ] ; tmp_p =
muDoubleScalarFloor ( rtP . GYRO_seed2 [ 1 ] ) ; if ( muDoubleScalarIsNaN (
tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . czp4qnh0py [
1 ] = tseed ; rtDW . achzjspzj0 [ 1 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
czp4qnh0py [ 1 ] ) * rtP . nudegsec2_StdDev [ 1 ] + rtP . nudegsec2_Mean [ 1
] ; rtB . hm15o25lmb [ 1 ] = rtP . GPperturbation_RSW_kms2_3_Y0 [ 1 ] ; rtB .
b5ehs0zt32 [ 1 ] = rtP . GG_b_Nm_3_Y0 [ 1 ] ; rtX . l0nfea2luh [ 2 ] = rtP .
Integrator_IC_fuz2mronvk ; tmp_p = muDoubleScalarFloor ( rtP . GYRO_seed1 [ 2
] ) ; if ( muDoubleScalarIsNaN ( tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) {
tmp_p = 0.0 ; } else { tmp_p = muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ;
} tseed = tmp_p < 0.0 ? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : (
uint32_T ) tmp_p ; r = ( int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed
& 32768U ) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T
) t ) << 16U ) + ( uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) {
tseed = 1144108930U ; } else if ( tseed > 2147483646U ) { tseed = 2147483646U
; } rtDW . dslhvlg4ym [ 2 ] = tseed ; rtDW . i3rfdszits [ 2 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dslhvlg4ym [ 2 ] ) * rtP .
nvdegsec_StdDev [ 2 ] + rtP . nvdegsec_Mean [ 2 ] ; tmp_p =
muDoubleScalarFloor ( rtP . GYRO_seed2 [ 2 ] ) ; if ( muDoubleScalarIsNaN (
tmp_p ) || muDoubleScalarIsInf ( tmp_p ) ) { tmp_p = 0.0 ; } else { tmp_p =
muDoubleScalarRem ( tmp_p , 4.294967296E+9 ) ; } tseed = tmp_p < 0.0 ? (
uint32_T ) - ( int32_T ) ( uint32_T ) - tmp_p : ( uint32_T ) tmp_p ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + ( uint32_T ) t ) << 16U ) + (
uint32_T ) t ) + ( uint32_T ) r ; if ( tseed < 1U ) { tseed = 1144108930U ; }
else if ( tseed > 2147483646U ) { tseed = 2147483646U ; } rtDW . czp4qnh0py [
2 ] = tseed ; rtDW . achzjspzj0 [ 2 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
czp4qnh0py [ 2 ] ) * rtP . nudegsec2_StdDev [ 2 ] + rtP . nudegsec2_Mean [ 2
] ; rtB . hm15o25lmb [ 2 ] = rtP . GPperturbation_RSW_kms2_3_Y0 [ 2 ] ; rtB .
b5ehs0zt32 [ 2 ] = rtP . GG_b_Nm_3_Y0 [ 2 ] ; rtB . jclektca5o . aupbtlrqjk [
0 ] = rtP . remmag_b_Nm_3_Y0 [ 0 ] ; rtB . jclektca5o . aupbtlrqjk [ 1 ] =
rtP . remmag_b_Nm_3_Y0 [ 1 ] ; rtB . jclektca5o . aupbtlrqjk [ 2 ] = rtP .
remmag_b_Nm_3_Y0 [ 2 ] ; rtB . c5rolz011g . c1nd5nsrgs [ 0 ] = rtP .
SRP_b_Nm_3_Y0 [ 0 ] ; rtB . c5rolz011g . c1nd5nsrgs [ 1 ] = rtP .
SRP_b_Nm_3_Y0 [ 1 ] ; rtB . c5rolz011g . c1nd5nsrgs [ 2 ] = rtP .
SRP_b_Nm_3_Y0 [ 2 ] ; } void MdlStart ( void ) { int32_T i ; { bool
externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "outAngularRate" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "outAngularRate" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "SILS_20241709/Angular Rate" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars (
"outAngularRate" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. lqwrbhd21x . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"5fe8da7a-4c96-46de-aa63-d686b8b1eacb" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . lqwrbhd21x . AQHandles , hDT , & srcInfo ) ; if ( rtDW . lqwrbhd21x .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . lqwrbhd21x . AQHandles ,
"0.01" , 0.01 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
lqwrbhd21x . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . lqwrbhd21x .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . lqwrbhd21x . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . lqwrbhd21x . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "sun_flag" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "sun_flag" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"SILS_20241709/Environment&Dynamics" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "sun_flag" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 1 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . ko5el0avio . AQHandles =
sdiStartAsyncioQueueCreation ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "e1734409-ca56-43c6-a6f4-5d8cc7684666" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ;
sdiCompleteAsyncioQueueCreation ( rtDW . ko5el0avio . AQHandles , hDT , &
srcInfo ) ; if ( rtDW . ko5el0avio . AQHandles ) {
sdiSetSignalSampleTimeString ( rtDW . ko5el0avio . AQHandles , "0.01" , 0.01
, ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW . ko5el0avio . AQHandles
, 0.0 ) ; sdiSetRunStartTime ( rtDW . ko5el0avio . AQHandles , ssGetTaskTime
( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW . ko5el0avio .
AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW . ko5el0avio .
AQHandles , loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName
) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel
( propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "w_b_rad_s" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "w_b_rad_s" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "SILS_20241709/Gain" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "w_b_rad_s" )
; sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 3 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . d11ycakunl . AQHandles =
sdiStartAsyncioQueueCreation ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "ec3c05a6-53de-4bec-9ade-f00ef293f976" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ;
sdiCompleteAsyncioQueueCreation ( rtDW . d11ycakunl . AQHandles , hDT , &
srcInfo ) ; if ( rtDW . d11ycakunl . AQHandles ) {
sdiSetSignalSampleTimeString ( rtDW . d11ycakunl . AQHandles , "0.01" , 0.01
, ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW . d11ycakunl . AQHandles
, 0.0 ) ; sdiSetRunStartTime ( rtDW . d11ycakunl . AQHandles , ssGetTaskTime
( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW . d11ycakunl .
AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW . d11ycakunl .
AQHandles , loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName
) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel
( propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} { RTWLogSignalInfo rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [
] = { 1 , 1 , 1 , 1 } ; static int_T rt_ScopeSignalNumDimensions [ ] = { 2 ,
2 , 2 , 2 } ; static int_T rt_ScopeSignalDimensions [ ] = { 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 } ; static void * rt_ScopeCurrSigDims [ ] = { ( NULL ) , ( NULL )
, ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) } ; static
int_T rt_ScopeCurrSigDimsSize [ ] = { 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4 } ;
static const char_T * rt_ScopeSignalLabels [ ] = { "" , "" , "" , "" } ;
static char_T rt_ScopeSignalTitles [ ] = "" ; static int_T
rt_ScopeSignalTitleLengths [ ] = { 0 , 0 , 0 , 0 } ; static boolean_T
rt_ScopeSignalIsVarDims [ ] = { 0 , 0 , 0 , 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 0 , 0 , 0 , 0 } ; BuiltInDTypeId dTypes [ 4
] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ; static char_T
rt_ScopeBlockName [ ] = "SILS_20241709/rw_rate2" ; static int_T
rt_ScopeFrameData [ ] = { 0 , 0 , 0 , 0 } ; static RTWPreprocessingFcnPtr
rt_ScopeSignalLoggingPreprocessingFcnPtrs [ ] = { ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) } ;
rt_ScopeSignalInfo . numSignals = 4 ; rt_ScopeSignalInfo . numCols =
rt_ScopeSignalWidths ; rt_ScopeSignalInfo . numDims =
rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = rt_ScopeFrameData ; rt_ScopeSignalInfo . preprocessingPtrs =
rt_ScopeSignalLoggingPreprocessingFcnPtrs ; rt_ScopeSignalInfo . labels .
cptr = rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles =
rt_ScopeSignalTitles ; rt_ScopeSignalInfo . titleLengths =
rt_ScopeSignalTitleLengths ; rt_ScopeSignalInfo . plotStyles =
rt_ScopeSignalPlotStyles ; rt_ScopeSignalInfo . blockNames . cptr = ( NULL )
; rt_ScopeSignalInfo . stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
crossMdlRef = ( NULL ) ; rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ;
rtDW . hflxu4olzs . LoggedData [ 0 ] = rt_CreateStructLogVar (
ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , (
& ssGetErrorStatus ( rtS ) ) , "rw_information" , 1 , 0 , 1 , 0.01 , &
rt_ScopeSignalInfo , rt_ScopeBlockName ) ; if ( rtDW . hflxu4olzs .
LoggedData [ 0 ] == ( NULL ) ) return ; } rtDW . lqozsqepug = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtB . p4vsv1mu0t = rtP .
F107_Value ; for ( i = 0 ; i < 7 ; i ++ ) { rtB . blzsybl1pb [ i ] = rtP .
aph_Value [ i ] ; } memcpy ( & rtB . nspxciplv0 [ 0 ] , & rtP . flag_Value [
0 ] , 23U * sizeof ( real_T ) ) ; rtDW . odkn5lgudq = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . bdwu52mmaq =
false ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; for ( i = 0 ; i
< 6 ; i ++ ) { rtB . lzmaq0diab [ i ] = rtP . ele [ i ] ; } rtDW . kc0x0orqmh
= false ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW .
hp42fr3fka = false ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; {
SimStruct * rts = ssGetSFunction ( rtS , 16 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:541" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } { SimStruct * rts =
ssGetSFunction ( rtS , 17 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:542" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) =
ssGetmdlStart ( rts ) ; sfcnLoader_separateComplexHandler ( rts ,
sfcnMethodPtr ) ; } if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } {
SimStruct * rts = ssGetSFunction ( rtS , 18 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:543" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } { SimStruct * rts =
ssGetSFunction ( rtS , 19 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:544" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) =
ssGetmdlStart ( rts ) ; sfcnLoader_separateComplexHandler ( rts ,
sfcnMethodPtr ) ; } if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } {
SimStruct * rts = ssGetSFunction ( rtS , 20 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:545" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } { SimStruct * rts =
ssGetSFunction ( rtS , 1 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:552" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) =
ssGetmdlStart ( rts ) ; sfcnLoader_separateComplexHandler ( rts ,
sfcnMethodPtr ) ; } if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } {
SimStruct * rts = ssGetSFunction ( rtS , 2 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:549" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } { SimStruct * rts =
ssGetSFunction ( rtS , 3 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:555" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) =
ssGetmdlStart ( rts ) ; sfcnLoader_separateComplexHandler ( rts ,
sfcnMethodPtr ) ; } if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } {
SimStruct * rts = ssGetSFunction ( rtS , 4 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:558" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } { SimStruct * rts =
ssGetSFunction ( rtS , 5 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:523" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) =
ssGetmdlStart ( rts ) ; sfcnLoader_separateComplexHandler ( rts ,
sfcnMethodPtr ) ; } if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } {
SimStruct * rts = ssGetSFunction ( rtS , 6 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:517" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } { SimStruct * rts =
ssGetSFunction ( rtS , 7 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:519" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) =
ssGetmdlStart ( rts ) ; sfcnLoader_separateComplexHandler ( rts ,
sfcnMethodPtr ) ; } if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } {
SimStruct * rts = ssGetSFunction ( rtS , 8 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:520" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } { SimStruct * rts =
ssGetSFunction ( rtS , 9 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:521" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) =
ssGetmdlStart ( rts ) ; sfcnLoader_separateComplexHandler ( rts ,
sfcnMethodPtr ) ; } if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } {
SimStruct * rts = ssGetSFunction ( rtS , 10 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:630" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } { SimStruct * rts =
ssGetSFunction ( rtS , 11 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:631" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) =
ssGetmdlStart ( rts ) ; sfcnLoader_separateComplexHandler ( rts ,
sfcnMethodPtr ) ; } if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } {
SimStruct * rts = ssGetSFunction ( rtS , 12 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:632" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } { SimStruct * rts =
ssGetSFunction ( rtS , 13 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:518" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) =
ssGetmdlStart ( rts ) ; sfcnLoader_separateComplexHandler ( rts ,
sfcnMethodPtr ) ; } if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } {
SimStruct * rts = ssGetSFunction ( rtS , 14 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:522" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } rtB . jr21nlhhbn [ 0 ] =
rtP . IC_Value [ 0 ] ; rtB . jr21nlhhbn [ 1 ] = rtP . IC_Value [ 1 ] ; rtB .
jr21nlhhbn [ 2 ] = rtP . IC_Value [ 2 ] ; rtB . jr21nlhhbn [ 3 ] = rtP .
IC_Value [ 3 ] ; rtDW . mmkouxeune = ( rtMinusInf ) ; rtB . gyoxzzwqiz [ 0 ]
= rtP . IC1_Value [ 0 ] ; rtB . gyoxzzwqiz [ 1 ] = rtP . IC1_Value [ 1 ] ;
rtB . gyoxzzwqiz [ 2 ] = rtP . IC1_Value [ 2 ] ; rtDW . jeeaiz3533 = (
rtMinusInf ) ; { SimStruct * rts = ssGetSFunction ( rtS , 15 ) ; { static
const char * blockSIDForSFcnLoader = "SILS_20241709:537" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = ssGetmdlStart ( rts ) ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } MdlInitialize ( ) ; } void
MdlOutputs ( int_T tid ) { real_T jkvgcfu3cx ; real_T drd0rcd33w ; real_T
lgn4rji20w ; real_T ebdsqxa0pr ; real_T lf41id4igu ; real_T i4jz3egckp ;
real_T geanfu3bne ; real_T ljtf33toyo ; real_T g2acauyoyt ; real_T ivwumm0lpw
; real_T mkyk40n3sw ; real_T hxeyppvwpl ; real_T p1oqolb2r3 ; real_T
flu00snx4l ; real_T j4xyasklvt ; real_T anqmvhm2ud ; real_T c2y5dtcawp ;
real_T bcyok1fmxf ; real_T lmhgznz12o ; real_T afmdwca1nj [ 9 ] ; real_T
mjbycp0jir ; real_T gvlvah3pa0 ; real_T a0ueoyvf4v ; real_T n4kwubetr3 ;
real_T dw412mfedm [ 9 ] ; real_T o1gf1sn0wj [ 9 ] ; real_T balzhvtkpr ;
real_T i3r45wjfj2 ; real_T lit5wfpqiy ; real_T mu3v2yavfb ; real_T myjibr0vt0
; real_T omrvjcewtk ; real_T bf1axylr5a ; real_T h3zuftpwti [ 3 ] ; real_T
hqbmtiz1ck [ 3 ] ; real_T d22ngtbkmu [ 6 ] ; real_T ouoayp2yxm [ 3 ] ; real_T
bmxglekqjv ; real_T fuaqyhzuaf ; real_T dlemuqwiz2 ; __m128d tmp_e ; __m128d
tmp_p ; real_T p_data [ 105 ] ; real_T q_data [ 105 ] ; real_T tmp [ 16 ] ;
real_T cl [ 13 ] ; real_T sl [ 13 ] ; real_T T_p [ 9 ] ; real_T b [ 9 ] ;
real_T b_p [ 9 ] ; real_T c [ 9 ] ; real_T c_cp_p [ 9 ] ; real_T eozueattnw [
9 ] ; real_T h1gu4wqhux [ 9 ] ; real_T lq1oh3hzzm [ 6 ] ; real_T elhmhs4fto [
3 ] ; real_T kclbezm4gf [ 3 ] ; real_T lyw5zuxpkh [ 3 ] ; real_T M ; real_T T
; real_T T3 ; real_T absxk ; real_T b_sp ; real_T cW ; real_T c_cp ; real_T
c_sp ; real_T ci ; real_T cu ; real_T delta ; real_T dk2rjxlhn5 ; real_T
dn2nlybx4r ; real_T e ; real_T ea ; real_T g5zew52spt ; real_T gomxyom0vc ;
real_T h ; real_T hakul2mmal_idx_1 ; real_T hmyegtxsdh_idx_1 ; real_T
hmyegtxsdh_idx_2 ; real_T hmyegtxsdh_idx_3 ; real_T irzywnigjr_idx_0 ; real_T
irzywnigjr_idx_1 ; real_T irzywnigjr_idx_2 ; real_T jwppuzxlko ; real_T
k50kzncrsl ; real_T kl0gyfxice ; real_T lnr42yo3kc_idx_1 ; real_T
luilsch3m0_idx_1 ; real_T m5crkrq425_idx_0 ; real_T ono5ii4s3b_idx_0 ; real_T
ono5ii4s3b_idx_1 ; real_T ono5ii4s3b_idx_2 ; real_T oqmv0ahkug ; real_T
otiigwfvqy ; real_T ovpn3bsi5w ; real_T r_dot ; real_T sW ; real_T sp ;
real_T su ; real_T u ; int32_T i ; int32_T kmx ; int32_T nc ; int32_T r3 ;
boolean_T hreqnea3pv ; SimStruct * S ; void * diag ; static const int8_T b_e
[ 3 ] = { 1 , 0 , 0 } ; static const int8_T b_i [ 3 ] = { 0 , 0 , 1 } ;
static const int16_T b_m [ 12 ] = { 0 , 31 , 59 , 90 , 120 , 151 , 181 , 212
, 243 , 273 , 304 , 334 } ; static const real_T c_p [ 3255 ] = { - 31543.0 ,
- 2298.0 , 5922.0 , - 677.0 , 2905.0 , - 1061.0 , 924.0 , 1121.0 , 1022.0 , -
1469.0 , - 330.0 , 1256.0 , 3.0 , 572.0 , 523.0 , 876.0 , 628.0 , 195.0 ,
660.0 , - 69.0 , - 361.0 , - 210.0 , 134.0 , - 75.0 , - 184.0 , 328.0 , -
210.0 , 264.0 , 53.0 , 5.0 , - 33.0 , - 86.0 , - 124.0 , - 16.0 , 3.0 , 63.0
, 61.0 , - 9.0 , - 11.0 , 83.0 , - 217.0 , 2.0 , - 58.0 , - 35.0 , 59.0 ,
36.0 , - 90.0 , - 69.0 , 70.0 , - 55.0 , - 45.0 , 0.0 , - 13.0 , 34.0 , -
10.0 , - 41.0 , - 1.0 , - 21.0 , 28.0 , 18.0 , - 12.0 , 6.0 , - 22.0 , 11.0 ,
8.0 , 8.0 , - 4.0 , - 14.0 , - 9.0 , 7.0 , 1.0 , - 13.0 , 2.0 , 5.0 , - 9.0 ,
16.0 , 5.0 , - 5.0 , 8.0 , - 18.0 , 8.0 , 10.0 , - 20.0 , 1.0 , 14.0 , - 11.0
, 5.0 , 12.0 , - 3.0 , 1.0 , - 2.0 , - 2.0 , 8.0 , 2.0 , 10.0 , - 1.0 , - 2.0
, - 1.0 , 2.0 , - 3.0 , - 4.0 , 2.0 , 2.0 , 1.0 , - 5.0 , 2.0 , - 2.0 , 6.0 ,
6.0 , - 4.0 , 4.0 , 0.0 , 0.0 , - 2.0 , 2.0 , 4.0 , 2.0 , 0.0 , 0.0 , - 6.0 ,
- 31464.0 , - 2298.0 , 5909.0 , - 728.0 , 2928.0 , - 1086.0 , 1041.0 , 1065.0
, 1037.0 , - 1494.0 , - 357.0 , 1239.0 , 34.0 , 635.0 , 480.0 , 880.0 , 643.0
, 203.0 , 653.0 , - 77.0 , - 380.0 , - 201.0 , 146.0 , - 65.0 , - 192.0 ,
328.0 , - 193.0 , 259.0 , 56.0 , - 1.0 , - 32.0 , - 93.0 , - 125.0 , - 26.0 ,
11.0 , 62.0 , 60.0 , - 7.0 , - 11.0 , 86.0 , - 221.0 , 4.0 , - 57.0 , - 32.0
, 57.0 , 32.0 , - 92.0 , - 67.0 , 70.0 , - 54.0 , - 46.0 , 0.0 , - 14.0 ,
33.0 , - 11.0 , - 41.0 , 0.0 , - 20.0 , 28.0 , 18.0 , - 12.0 , 6.0 , - 22.0 ,
11.0 , 8.0 , 8.0 , - 4.0 , - 15.0 , - 9.0 , 7.0 , 1.0 , - 13.0 , 2.0 , 5.0 ,
- 8.0 , 16.0 , 5.0 , - 5.0 , 8.0 , - 18.0 , 8.0 , 10.0 , - 20.0 , 1.0 , 14.0
, - 11.0 , 5.0 , 12.0 , - 3.0 , 1.0 , - 2.0 , - 2.0 , 8.0 , 2.0 , 10.0 , 0.0
, - 2.0 , - 1.0 , 2.0 , - 3.0 , - 4.0 , 2.0 , 2.0 , 1.0 , - 5.0 , 2.0 , - 2.0
, 6.0 , 6.0 , - 4.0 , 4.0 , 0.0 , 0.0 , - 2.0 , 2.0 , 4.0 , 2.0 , 0.0 , 0.0 ,
- 6.0 , - 31354.0 , - 2297.0 , 5898.0 , - 769.0 , 2948.0 , - 1128.0 , 1176.0
, 1000.0 , 1058.0 , - 1524.0 , - 389.0 , 1223.0 , 62.0 , 705.0 , 425.0 ,
884.0 , 660.0 , 211.0 , 644.0 , - 90.0 , - 400.0 , - 189.0 , 160.0 , - 55.0 ,
- 201.0 , 327.0 , - 172.0 , 253.0 , 57.0 , - 9.0 , - 33.0 , - 102.0 , - 126.0
, - 38.0 , 21.0 , 62.0 , 58.0 , - 5.0 , - 11.0 , 89.0 , - 224.0 , 5.0 , -
54.0 , - 29.0 , 54.0 , 28.0 , - 95.0 , - 65.0 , 71.0 , - 54.0 , - 47.0 , 1.0
, - 14.0 , 32.0 , - 12.0 , - 40.0 , 1.0 , - 19.0 , 28.0 , 18.0 , - 13.0 , 6.0
, - 22.0 , 11.0 , 8.0 , 8.0 , - 4.0 , - 15.0 , - 9.0 , 6.0 , 1.0 , - 13.0 ,
2.0 , 5.0 , - 8.0 , 16.0 , 5.0 , - 5.0 , 8.0 , - 18.0 , 8.0 , 10.0 , - 20.0 ,
1.0 , 14.0 , - 11.0 , 5.0 , 12.0 , - 3.0 , 1.0 , - 2.0 , - 2.0 , 8.0 , 2.0 ,
10.0 , 0.0 , - 2.0 , - 1.0 , 2.0 , - 3.0 , - 4.0 , 2.0 , 2.0 , 1.0 , - 5.0 ,
2.0 , - 2.0 , 6.0 , 6.0 , - 4.0 , 4.0 , 0.0 , 0.0 , - 2.0 , 2.0 , 4.0 , 2.0 ,
0.0 , 0.0 , - 6.0 , - 31212.0 , - 2306.0 , 5875.0 , - 802.0 , 2956.0 , -
1191.0 , 1309.0 , 917.0 , 1084.0 , - 1559.0 , - 421.0 , 1212.0 , 84.0 , 778.0
, 360.0 , 887.0 , 678.0 , 218.0 , 631.0 , - 109.0 , - 416.0 , - 173.0 , 178.0
, - 51.0 , - 211.0 , 327.0 , - 148.0 , 245.0 , 58.0 , - 16.0 , - 34.0 , -
111.0 , - 126.0 , - 51.0 , 32.0 , 61.0 , 57.0 , - 2.0 , - 10.0 , 93.0 , -
228.0 , 8.0 , - 51.0 , - 26.0 , 49.0 , 23.0 , - 98.0 , - 62.0 , 72.0 , - 54.0
, - 48.0 , 2.0 , - 14.0 , 31.0 , - 12.0 , - 38.0 , 2.0 , - 18.0 , 28.0 , 19.0
, - 15.0 , 6.0 , - 22.0 , 11.0 , 8.0 , 8.0 , - 4.0 , - 15.0 , - 9.0 , 6.0 ,
2.0 , - 13.0 , 3.0 , 5.0 , - 8.0 , 16.0 , 6.0 , - 5.0 , 8.0 , - 18.0 , 8.0 ,
10.0 , - 20.0 , 1.0 , 14.0 , - 11.0 , 5.0 , 12.0 , - 3.0 , 1.0 , - 2.0 , -
2.0 , 8.0 , 2.0 , 10.0 , 0.0 , - 2.0 , - 1.0 , 2.0 , - 3.0 , - 4.0 , 2.0 ,
2.0 , 1.0 , - 5.0 , 2.0 , - 2.0 , 6.0 , 6.0 , - 4.0 , 4.0 , 0.0 , 0.0 , - 2.0
, 1.0 , 4.0 , 2.0 , 0.0 , 0.0 , - 6.0 , - 31060.0 , - 2317.0 , 5845.0 , -
839.0 , 2959.0 , - 1259.0 , 1407.0 , 823.0 , 1111.0 , - 1600.0 , - 445.0 ,
1205.0 , 103.0 , 839.0 , 293.0 , 889.0 , 695.0 , 220.0 , 616.0 , - 134.0 , -
424.0 , - 153.0 , 199.0 , - 57.0 , - 221.0 , 326.0 , - 122.0 , 236.0 , 58.0 ,
- 23.0 , - 38.0 , - 119.0 , - 125.0 , - 62.0 , 43.0 , 61.0 , 55.0 , 0.0 , -
10.0 , 96.0 , - 233.0 , 11.0 , - 46.0 , - 22.0 , 44.0 , 18.0 , - 101.0 , -
57.0 , 73.0 , - 54.0 , - 49.0 , 2.0 , - 14.0 , 29.0 , - 13.0 , - 37.0 , 4.0 ,
- 16.0 , 28.0 , 19.0 , - 16.0 , 6.0 , - 22.0 , 11.0 , 7.0 , 8.0 , - 3.0 , -
15.0 , - 9.0 , 6.0 , 2.0 , - 14.0 , 4.0 , 5.0 , - 7.0 , 17.0 , 6.0 , - 5.0 ,
8.0 , - 19.0 , 8.0 , 10.0 , - 20.0 , 1.0 , 14.0 , - 11.0 , 5.0 , 12.0 , - 3.0
, 1.0 , - 2.0 , - 2.0 , 9.0 , 2.0 , 10.0 , 0.0 , - 2.0 , - 1.0 , 2.0 , - 3.0
, - 4.0 , 2.0 , 2.0 , 1.0 , - 5.0 , 2.0 , - 2.0 , 6.0 , 6.0 , - 4.0 , 4.0 ,
0.0 , 0.0 , - 2.0 , 1.0 , 4.0 , 3.0 , 0.0 , 0.0 , - 6.0 , - 30926.0 , -
2318.0 , 5817.0 , - 893.0 , 2969.0 , - 1334.0 , 1471.0 , 728.0 , 1140.0 , -
1645.0 , - 462.0 , 1202.0 , 119.0 , 881.0 , 229.0 , 891.0 , 711.0 , 216.0 ,
601.0 , - 163.0 , - 426.0 , - 130.0 , 217.0 , - 70.0 , - 230.0 , 326.0 , -
96.0 , 226.0 , 58.0 , - 28.0 , - 44.0 , - 125.0 , - 122.0 , - 69.0 , 51.0 ,
61.0 , 54.0 , 3.0 , - 9.0 , 99.0 , - 238.0 , 14.0 , - 40.0 , - 18.0 , 39.0 ,
13.0 , - 103.0 , - 52.0 , 73.0 , - 54.0 , - 50.0 , 3.0 , - 14.0 , 27.0 , -
14.0 , - 35.0 , 5.0 , - 14.0 , 29.0 , 19.0 , - 17.0 , 6.0 , - 21.0 , 11.0 ,
7.0 , 8.0 , - 3.0 , - 15.0 , - 9.0 , 6.0 , 2.0 , - 14.0 , 4.0 , 5.0 , - 7.0 ,
17.0 , 7.0 , - 5.0 , 8.0 , - 19.0 , 8.0 , 10.0 , - 20.0 , 1.0 , 14.0 , - 11.0
, 5.0 , 12.0 , - 3.0 , 1.0 , - 2.0 , - 2.0 , 9.0 , 2.0 , 10.0 , 0.0 , - 2.0 ,
- 1.0 , 2.0 , - 3.0 , - 4.0 , 2.0 , 2.0 , 1.0 , - 5.0 , 2.0 , - 2.0 , 6.0 ,
6.0 , - 4.0 , 4.0 , 0.0 , 0.0 , - 2.0 , 1.0 , 4.0 , 3.0 , 0.0 , 0.0 , - 6.0 ,
- 30805.0 , - 2316.0 , 5808.0 , - 951.0 , 2980.0 , - 1424.0 , 1517.0 , 644.0
, 1172.0 , - 1692.0 , - 480.0 , 1205.0 , 133.0 , 907.0 , 166.0 , 896.0 ,
727.0 , 205.0 , 584.0 , - 195.0 , - 422.0 , - 109.0 , 234.0 , - 90.0 , -
237.0 , 327.0 , - 72.0 , 218.0 , 60.0 , - 32.0 , - 53.0 , - 131.0 , - 118.0 ,
- 74.0 , 58.0 , 60.0 , 53.0 , 4.0 , - 9.0 , 102.0 , - 242.0 , 19.0 , - 32.0 ,
- 16.0 , 32.0 , 8.0 , - 104.0 , - 46.0 , 74.0 , - 54.0 , - 51.0 , 4.0 , -
15.0 , 25.0 , - 14.0 , - 34.0 , 6.0 , - 12.0 , 29.0 , 18.0 , - 18.0 , 6.0 , -
20.0 , 11.0 , 7.0 , 8.0 , - 3.0 , - 15.0 , - 9.0 , 5.0 , 2.0 , - 14.0 , 5.0 ,
5.0 , - 6.0 , 18.0 , 8.0 , - 5.0 , 8.0 , - 19.0 , 8.0 , 10.0 , - 20.0 , 1.0 ,
14.0 , - 12.0 , 5.0 , 12.0 , - 3.0 , 1.0 , - 2.0 , - 2.0 , 9.0 , 3.0 , 10.0 ,
0.0 , - 2.0 , - 2.0 , 2.0 , - 3.0 , - 4.0 , 2.0 , 2.0 , 1.0 , - 5.0 , 2.0 , -
2.0 , 6.0 , 6.0 , - 4.0 , 4.0 , 0.0 , 0.0 , - 2.0 , 1.0 , 4.0 , 3.0 , 0.0 ,
0.0 , - 6.0 , - 30715.0 , - 2306.0 , 5812.0 , - 1018.0 , 2984.0 , - 1520.0 ,
1550.0 , 586.0 , 1206.0 , - 1740.0 , - 494.0 , 1215.0 , 146.0 , 918.0 , 101.0
, 903.0 , 744.0 , 188.0 , 565.0 , - 226.0 , - 415.0 , - 90.0 , 249.0 , -
114.0 , - 241.0 , 329.0 , - 51.0 , 211.0 , 64.0 , - 33.0 , - 64.0 , - 136.0 ,
- 115.0 , - 76.0 , 64.0 , 59.0 , 53.0 , 4.0 , - 8.0 , 104.0 , - 246.0 , 25.0
, - 25.0 , - 15.0 , 25.0 , 4.0 , - 106.0 , - 40.0 , 74.0 , - 53.0 , - 52.0 ,
4.0 , - 17.0 , 23.0 , - 14.0 , - 33.0 , 7.0 , - 11.0 , 29.0 , 18.0 , - 19.0 ,
6.0 , - 19.0 , 11.0 , 7.0 , 8.0 , - 3.0 , - 15.0 , - 9.0 , 5.0 , 1.0 , - 15.0
, 6.0 , 5.0 , - 6.0 , 18.0 , 8.0 , - 5.0 , 7.0 , - 19.0 , 8.0 , 10.0 , - 20.0
, 1.0 , 15.0 , - 12.0 , 5.0 , 11.0 , - 3.0 , 1.0 , - 3.0 , - 2.0 , 9.0 , 3.0
, 11.0 , 0.0 , - 2.0 , - 2.0 , 2.0 , - 3.0 , - 4.0 , 2.0 , 2.0 , 1.0 , - 5.0
, 2.0 , - 2.0 , 6.0 , 6.0 , - 4.0 , 4.0 , 0.0 , 0.0 , - 1.0 , 2.0 , 4.0 , 3.0
, 0.0 , 0.0 , - 6.0 , - 30654.0 , - 2292.0 , 5821.0 , - 1106.0 , 2981.0 , -
1614.0 , 1566.0 , 528.0 , 1240.0 , - 1790.0 , - 499.0 , 1232.0 , 163.0 ,
916.0 , 43.0 , 914.0 , 762.0 , 169.0 , 550.0 , - 252.0 , - 405.0 , - 72.0 ,
265.0 , - 141.0 , - 241.0 , 334.0 , - 33.0 , 208.0 , 71.0 , - 33.0 , - 75.0 ,
- 141.0 , - 113.0 , - 76.0 , 69.0 , 57.0 , 54.0 , 4.0 , - 7.0 , 105.0 , -
249.0 , 33.0 , - 18.0 , - 15.0 , 18.0 , 0.0 , - 107.0 , - 33.0 , 74.0 , -
53.0 , - 52.0 , 4.0 , - 18.0 , 20.0 , - 14.0 , - 31.0 , 7.0 , - 9.0 , 29.0 ,
17.0 , - 20.0 , 5.0 , - 19.0 , 11.0 , 7.0 , 8.0 , - 3.0 , - 14.0 , - 10.0 ,
5.0 , 1.0 , - 15.0 , 6.0 , 5.0 , - 5.0 , 19.0 , 9.0 , - 5.0 , 7.0 , - 19.0 ,
8.0 , 10.0 , - 21.0 , 1.0 , 15.0 , - 12.0 , 5.0 , 11.0 , - 3.0 , 1.0 , - 3.0
, - 2.0 , 9.0 , 3.0 , 11.0 , 1.0 , - 2.0 , - 2.0 , 2.0 , - 3.0 , - 4.0 , 2.0
, 2.0 , 1.0 , - 5.0 , 2.0 , - 2.0 , 6.0 , 6.0 , - 4.0 , 4.0 , 0.0 , 0.0 , -
1.0 , 2.0 , 4.0 , 3.0 , 0.0 , 0.0 , - 6.0 , - 30594.0 , - 2285.0 , 5810.0 , -
1244.0 , 2990.0 , - 1702.0 , 1578.0 , 477.0 , 1282.0 , - 1834.0 , - 499.0 ,
1255.0 , 186.0 , 913.0 , - 11.0 , 944.0 , 776.0 , 144.0 , 544.0 , - 276.0 , -
421.0 , - 55.0 , 304.0 , - 178.0 , - 253.0 , 346.0 , - 12.0 , 194.0 , 95.0 ,
- 20.0 , - 67.0 , - 142.0 , - 119.0 , - 82.0 , 82.0 , 59.0 , 57.0 , 6.0 , 6.0
, 100.0 , - 246.0 , 16.0 , - 25.0 , - 9.0 , 21.0 , - 16.0 , - 104.0 , - 39.0
, 70.0 , - 40.0 , - 45.0 , 0.0 , - 18.0 , 0.0 , 2.0 , - 29.0 , 6.0 , - 10.0 ,
28.0 , 15.0 , - 17.0 , 29.0 , - 22.0 , 13.0 , 7.0 , 12.0 , - 8.0 , - 21.0 , -
5.0 , - 12.0 , 9.0 , - 7.0 , 7.0 , 2.0 , - 10.0 , 18.0 , 7.0 , 3.0 , 2.0 , -
11.0 , 5.0 , - 21.0 , - 27.0 , 1.0 , 17.0 , - 11.0 , 29.0 , 3.0 , - 9.0 ,
16.0 , 4.0 , - 3.0 , 9.0 , - 4.0 , 6.0 , - 3.0 , 1.0 , - 4.0 , 8.0 , - 3.0 ,
11.0 , 5.0 , 1.0 , 1.0 , 2.0 , - 20.0 , - 5.0 , - 1.0 , - 1.0 , - 6.0 , 8.0 ,
6.0 , - 1.0 , - 4.0 , - 3.0 , - 2.0 , 5.0 , 0.0 , - 2.0 , - 2.0 , - 30554.0 ,
- 2250.0 , 5815.0 , - 1341.0 , 2998.0 , - 1810.0 , 1576.0 , 381.0 , 1297.0 ,
- 1889.0 , - 476.0 , 1274.0 , 206.0 , 896.0 , - 46.0 , 954.0 , 792.0 , 136.0
, 528.0 , - 278.0 , - 408.0 , - 37.0 , 303.0 , - 210.0 , - 240.0 , 349.0 ,
3.0 , 211.0 , 103.0 , - 20.0 , - 87.0 , - 147.0 , - 122.0 , - 76.0 , 80.0 ,
54.0 , 57.0 , - 1.0 , 4.0 , 99.0 , - 247.0 , 33.0 , - 16.0 , - 12.0 , 12.0 ,
- 12.0 , - 105.0 , - 30.0 , 65.0 , - 55.0 , - 35.0 , 2.0 , - 17.0 , 1.0 , 0.0
, - 40.0 , 10.0 , - 7.0 , 36.0 , 5.0 , - 18.0 , 19.0 , - 16.0 , 22.0 , 15.0 ,
5.0 , - 4.0 , - 22.0 , - 1.0 , 0.0 , 11.0 , - 21.0 , 15.0 , - 8.0 , - 13.0 ,
17.0 , 5.0 , - 4.0 , - 1.0 , - 17.0 , 3.0 , - 7.0 , - 24.0 , - 1.0 , 19.0 , -
25.0 , 12.0 , 10.0 , 2.0 , 5.0 , 2.0 , - 5.0 , 8.0 , - 2.0 , 8.0 , 3.0 , -
11.0 , 8.0 , - 7.0 , - 8.0 , 4.0 , 13.0 , - 1.0 , - 2.0 , 13.0 , - 10.0 , -
4.0 , 2.0 , 4.0 , - 3.0 , 12.0 , 6.0 , 3.0 , - 3.0 , 2.0 , 6.0 , 10.0 , 11.0
, 3.0 , 8.0 , - 30500.0 , - 2215.0 , 5820.0 , - 1440.0 , 3003.0 , - 1898.0 ,
1581.0 , 291.0 , 1302.0 , - 1944.0 , - 462.0 , 1288.0 , 216.0 , 882.0 , -
83.0 , 958.0 , 796.0 , 133.0 , 510.0 , - 274.0 , - 397.0 , - 23.0 , 290.0 , -
230.0 , - 229.0 , 360.0 , 15.0 , 230.0 , 110.0 , - 23.0 , - 98.0 , - 152.0 ,
- 121.0 , - 69.0 , 78.0 , 47.0 , 57.0 , - 9.0 , 3.0 , 96.0 , - 247.0 , 48.0 ,
- 8.0 , - 16.0 , 7.0 , - 12.0 , - 107.0 , - 24.0 , 65.0 , - 56.0 , - 50.0 ,
2.0 , - 24.0 , 10.0 , - 4.0 , - 32.0 , 8.0 , - 11.0 , 28.0 , 9.0 , - 20.0 ,
18.0 , - 18.0 , 11.0 , 9.0 , 10.0 , - 6.0 , - 15.0 , - 14.0 , 5.0 , 6.0 , -
23.0 , 10.0 , 3.0 , - 7.0 , 23.0 , 6.0 , - 4.0 , 9.0 , - 13.0 , 4.0 , 9.0 , -
11.0 , - 4.0 , 12.0 , - 5.0 , 7.0 , 2.0 , 6.0 , 4.0 , - 2.0 , 1.0 , 10.0 ,
2.0 , 7.0 , 2.0 , - 6.0 , 5.0 , 5.0 , - 3.0 , - 5.0 , - 4.0 , - 1.0 , 0.0 ,
2.0 , - 8.0 , - 3.0 , - 2.0 , 7.0 , - 4.0 , 4.0 , 1.0 , - 2.0 , - 3.0 , 6.0 ,
7.0 , - 2.0 , - 1.0 , 0.0 , - 3.0 , - 30421.0 , - 2169.0 , 5791.0 , - 1555.0
, 3002.0 , - 1967.0 , 1590.0 , 206.0 , 1302.0 , - 1992.0 , - 414.0 , 1289.0 ,
224.0 , 878.0 , - 130.0 , 957.0 , 800.0 , 135.0 , 504.0 , - 278.0 , - 394.0 ,
3.0 , 269.0 , - 255.0 , - 222.0 , 362.0 , 16.0 , 242.0 , 125.0 , - 26.0 , -
117.0 , - 156.0 , - 114.0 , - 63.0 , 81.0 , 46.0 , 58.0 , - 10.0 , 1.0 , 99.0
, - 237.0 , 60.0 , - 1.0 , - 20.0 , - 2.0 , - 11.0 , - 113.0 , - 17.0 , 67.0
, - 56.0 , - 55.0 , 5.0 , - 28.0 , 15.0 , - 6.0 , - 32.0 , 7.0 , - 7.0 , 23.0
, 17.0 , - 18.0 , 8.0 , - 17.0 , 15.0 , 6.0 , 11.0 , - 4.0 , - 14.0 , - 11.0
, 7.0 , 2.0 , - 18.0 , 10.0 , 4.0 , - 5.0 , 23.0 , 10.0 , 1.0 , 8.0 , - 20.0
, 4.0 , 6.0 , - 18.0 , 0.0 , 12.0 , - 9.0 , 2.0 , 1.0 , 0.0 , 4.0 , - 3.0 , -
1.0 , 9.0 , - 2.0 , 8.0 , 3.0 , 0.0 , - 1.0 , 5.0 , 1.0 , - 3.0 , 4.0 , 4.0 ,
1.0 , 0.0 , 0.0 , - 1.0 , 2.0 , 4.0 , - 5.0 , 6.0 , 1.0 , 1.0 , - 1.0 , - 1.0
, 6.0 , 2.0 , 0.0 , 0.0 , - 7.0 , - 30334.0 , - 2119.0 , 5776.0 , - 1662.0 ,
2997.0 , - 2016.0 , 1594.0 , 114.0 , 1297.0 , - 2038.0 , - 404.0 , 1292.0 ,
240.0 , 856.0 , - 165.0 , 957.0 , 804.0 , 148.0 , 479.0 , - 269.0 , - 390.0 ,
13.0 , 252.0 , - 269.0 , - 219.0 , 358.0 , 19.0 , 254.0 , 128.0 , - 31.0 , -
126.0 , - 157.0 , - 97.0 , - 62.0 , 81.0 , 45.0 , 61.0 , - 11.0 , 8.0 , 100.0
, - 228.0 , 68.0 , 4.0 , - 32.0 , 1.0 , - 8.0 , - 111.0 , - 7.0 , 75.0 , -
57.0 , - 61.0 , 4.0 , - 27.0 , 13.0 , - 2.0 , - 26.0 , 6.0 , - 6.0 , 26.0 ,
13.0 , - 23.0 , 1.0 , - 12.0 , 13.0 , 5.0 , 7.0 , - 4.0 , - 12.0 , - 14.0 ,
9.0 , 0.0 , - 16.0 , 8.0 , 4.0 , - 1.0 , 24.0 , 11.0 , - 3.0 , 4.0 , - 17.0 ,
8.0 , 10.0 , - 22.0 , 2.0 , 15.0 , - 13.0 , 7.0 , 10.0 , - 4.0 , - 1.0 , -
5.0 , - 1.0 , 10.0 , 5.0 , 10.0 , 1.0 , - 4.0 , - 2.0 , 1.0 , - 2.0 , - 3.0 ,
2.0 , 2.0 , 1.0 , - 5.0 , 2.0 , - 2.0 , 6.0 , 4.0 , - 4.0 , 4.0 , 0.0 , 0.0 ,
- 2.0 , 2.0 , 3.0 , 2.0 , 0.0 , 0.0 , - 6.0 , - 30220.0 , - 2068.0 , 5737.0 ,
- 1781.0 , 3000.0 , - 2047.0 , 1611.0 , 25.0 , 1287.0 , - 2091.0 , - 366.0 ,
1278.0 , 251.0 , 838.0 , - 196.0 , 952.0 , 800.0 , 167.0 , 461.0 , - 266.0 ,
- 395.0 , 26.0 , 234.0 , - 279.0 , - 216.0 , 359.0 , 26.0 , 262.0 , 139.0 , -
42.0 , - 139.0 , - 160.0 , - 91.0 , - 56.0 , 83.0 , 43.0 , 64.0 , - 12.0 ,
15.0 , 100.0 , - 212.0 , 72.0 , 2.0 , - 37.0 , 3.0 , - 6.0 , - 112.0 , 1.0 ,
72.0 , - 57.0 , - 70.0 , 1.0 , - 27.0 , 14.0 , - 4.0 , - 22.0 , 8.0 , - 2.0 ,
23.0 , 13.0 , - 23.0 , - 2.0 , - 11.0 , 14.0 , 6.0 , 7.0 , - 2.0 , - 15.0 , -
13.0 , 6.0 , - 3.0 , - 17.0 , 5.0 , 6.0 , 0.0 , 21.0 , 11.0 , - 6.0 , 3.0 , -
16.0 , 8.0 , 10.0 , - 21.0 , 2.0 , 16.0 , - 12.0 , 6.0 , 10.0 , - 4.0 , - 1.0
, - 5.0 , 0.0 , 10.0 , 3.0 , 11.0 , 1.0 , - 2.0 , - 1.0 , 1.0 , - 3.0 , - 3.0
, 1.0 , 2.0 , 1.0 , - 5.0 , 3.0 , - 1.0 , 4.0 , 6.0 , - 4.0 , 4.0 , 0.0 , 1.0
, - 1.0 , 0.0 , 3.0 , 3.0 , 1.0 , - 1.0 , - 4.0 , - 30100.0 , - 2013.0 ,
5675.0 , - 1902.0 , 3010.0 , - 2067.0 , 1632.0 , - 68.0 , 1276.0 , - 2144.0 ,
- 333.0 , 1260.0 , 262.0 , 830.0 , - 223.0 , 946.0 , 791.0 , 191.0 , 438.0 ,
- 265.0 , - 405.0 , 39.0 , 216.0 , - 288.0 , - 218.0 , 356.0 , 31.0 , 264.0 ,
148.0 , - 59.0 , - 152.0 , - 159.0 , - 83.0 , - 49.0 , 88.0 , 45.0 , 66.0 , -
13.0 , 28.0 , 99.0 , - 198.0 , 75.0 , 1.0 , - 41.0 , 6.0 , - 4.0 , - 111.0 ,
11.0 , 71.0 , - 56.0 , - 77.0 , 1.0 , - 26.0 , 16.0 , - 5.0 , - 14.0 , 10.0 ,
0.0 , 22.0 , 12.0 , - 23.0 , - 5.0 , - 12.0 , 14.0 , 6.0 , 6.0 , - 1.0 , -
16.0 , - 12.0 , 4.0 , - 8.0 , - 19.0 , 4.0 , 6.0 , 0.0 , 18.0 , 10.0 , - 10.0
, 1.0 , - 17.0 , 7.0 , 10.0 , - 21.0 , 2.0 , 16.0 , - 12.0 , 7.0 , 10.0 , -
4.0 , - 1.0 , - 5.0 , - 1.0 , 10.0 , 4.0 , 11.0 , 1.0 , - 3.0 , - 2.0 , 1.0 ,
- 3.0 , - 3.0 , 1.0 , 2.0 , 1.0 , - 5.0 , 3.0 , - 2.0 , 4.0 , 5.0 , - 4.0 ,
4.0 , - 1.0 , 1.0 , - 1.0 , 0.0 , 3.0 , 3.0 , 1.0 , - 1.0 , - 5.0 , - 29992.0
, - 1956.0 , 5604.0 , - 1997.0 , 3027.0 , - 2129.0 , 1663.0 , - 200.0 ,
1281.0 , - 2180.0 , - 336.0 , 1251.0 , 271.0 , 833.0 , - 252.0 , 938.0 ,
782.0 , 212.0 , 398.0 , - 257.0 , - 419.0 , 53.0 , 199.0 , - 297.0 , - 218.0
, 357.0 , 46.0 , 261.0 , 150.0 , - 74.0 , - 151.0 , - 162.0 , - 78.0 , - 48.0
, 92.0 , 48.0 , 66.0 , - 15.0 , 42.0 , 93.0 , - 192.0 , 71.0 , 4.0 , - 43.0 ,
14.0 , - 2.0 , - 108.0 , 17.0 , 72.0 , - 59.0 , - 82.0 , 2.0 , - 27.0 , 21.0
, - 5.0 , - 12.0 , 16.0 , 1.0 , 18.0 , 11.0 , - 23.0 , - 2.0 , - 10.0 , 18.0
, 6.0 , 7.0 , 0.0 , - 18.0 , - 11.0 , 4.0 , - 7.0 , - 22.0 , 4.0 , 9.0 , 3.0
, 16.0 , 6.0 , - 13.0 , - 1.0 , - 15.0 , 5.0 , 10.0 , - 21.0 , 1.0 , 16.0 , -
12.0 , 9.0 , 9.0 , - 5.0 , - 3.0 , - 6.0 , - 1.0 , 9.0 , 7.0 , 10.0 , 2.0 , -
6.0 , - 5.0 , 2.0 , - 4.0 , - 4.0 , 1.0 , 2.0 , 0.0 , - 5.0 , 3.0 , - 2.0 ,
6.0 , 5.0 , - 4.0 , 3.0 , 0.0 , 1.0 , - 1.0 , 2.0 , 4.0 , 3.0 , 0.0 , 0.0 , -
6.0 , - 29873.0 , - 1905.0 , 5500.0 , - 2072.0 , 3044.0 , - 2197.0 , 1687.0 ,
- 306.0 , 1296.0 , - 2208.0 , - 310.0 , 1247.0 , 284.0 , 829.0 , - 297.0 ,
936.0 , 780.0 , 232.0 , 361.0 , - 249.0 , - 424.0 , 69.0 , 170.0 , - 297.0 ,
- 214.0 , 355.0 , 47.0 , 253.0 , 150.0 , - 93.0 , - 154.0 , - 164.0 , - 75.0
, - 46.0 , 95.0 , 53.0 , 65.0 , - 16.0 , 51.0 , 88.0 , - 185.0 , 69.0 , 4.0 ,
- 48.0 , 16.0 , - 1.0 , - 102.0 , 21.0 , 74.0 , - 62.0 , - 83.0 , 3.0 , -
27.0 , 24.0 , - 2.0 , - 6.0 , 20.0 , 4.0 , 17.0 , 10.0 , - 23.0 , 0.0 , - 7.0
, 21.0 , 6.0 , 8.0 , 0.0 , - 19.0 , - 11.0 , 5.0 , - 9.0 , - 23.0 , 4.0 ,
11.0 , 4.0 , 14.0 , 4.0 , - 15.0 , - 4.0 , - 11.0 , 5.0 , 10.0 , - 21.0 , 1.0
, 15.0 , - 12.0 , 9.0 , 9.0 , - 6.0 , - 3.0 , - 6.0 , - 1.0 , 9.0 , 7.0 , 9.0
, 1.0 , - 7.0 , - 5.0 , 2.0 , - 4.0 , - 4.0 , 1.0 , 3.0 , 0.0 , - 5.0 , 3.0 ,
- 2.0 , 6.0 , 5.0 , - 4.0 , 3.0 , 0.0 , 1.0 , - 1.0 , 2.0 , 4.0 , 3.0 , 0.0 ,
0.0 , - 6.0 , - 29775.0 , - 1848.0 , 5406.0 , - 2131.0 , 3059.0 , - 2279.0 ,
1686.0 , - 373.0 , 1314.0 , - 2239.0 , - 284.0 , 1248.0 , 293.0 , 802.0 , -
352.0 , 939.0 , 780.0 , 247.0 , 325.0 , - 240.0 , - 423.0 , 84.0 , 141.0 , -
299.0 , - 214.0 , 353.0 , 46.0 , 245.0 , 154.0 , - 109.0 , - 153.0 , - 165.0
, - 69.0 , - 36.0 , 97.0 , 61.0 , 65.0 , - 16.0 , 59.0 , 82.0 , - 178.0 ,
69.0 , 3.0 , - 52.0 , 18.0 , 1.0 , - 96.0 , 24.0 , 77.0 , - 64.0 , - 80.0 ,
2.0 , - 26.0 , 26.0 , 0.0 , - 1.0 , 21.0 , 5.0 , 17.0 , 9.0 , - 23.0 , 0.0 ,
- 4.0 , 23.0 , 5.0 , 10.0 , - 1.0 , - 19.0 , - 10.0 , 6.0 , - 12.0 , - 22.0 ,
3.0 , 12.0 , 4.0 , 12.0 , 2.0 , - 16.0 , - 6.0 , - 10.0 , 4.0 , 9.0 , - 20.0
, 1.0 , 15.0 , - 12.0 , 11.0 , 9.0 , - 7.0 , - 4.0 , - 7.0 , - 2.0 , 9.0 ,
7.0 , 8.0 , 1.0 , - 7.0 , - 6.0 , 2.0 , - 3.0 , - 4.0 , 2.0 , 2.0 , 1.0 , -
5.0 , 3.0 , - 2.0 , 6.0 , 4.0 , - 4.0 , 3.0 , 0.0 , 1.0 , - 2.0 , 3.0 , 3.0 ,
3.0 , - 1.0 , 0.0 , - 6.0 , - 29692.0 , - 1784.0 , 5306.0 , - 2200.0 , 3070.0
, - 2366.0 , 1681.0 , - 413.0 , 1335.0 , - 2267.0 , - 262.0 , 1249.0 , 302.0
, 759.0 , - 427.0 , 940.0 , 780.0 , 262.0 , 290.0 , - 236.0 , - 418.0 , 97.0
, 122.0 , - 306.0 , - 214.0 , 352.0 , 46.0 , 235.0 , 165.0 , - 118.0 , -
143.0 , - 166.0 , - 55.0 , - 17.0 , 107.0 , 68.0 , 67.0 , - 17.0 , 68.0 ,
72.0 , - 170.0 , 67.0 , - 1.0 , - 58.0 , 19.0 , 1.0 , - 93.0 , 36.0 , 77.0 ,
- 72.0 , - 69.0 , 1.0 , - 25.0 , 28.0 , 4.0 , 5.0 , 24.0 , 4.0 , 17.0 , 8.0 ,
- 24.0 , - 2.0 , - 6.0 , 25.0 , 6.0 , 11.0 , - 6.0 , - 21.0 , - 9.0 , 8.0 , -
14.0 , - 23.0 , 9.0 , 15.0 , 6.0 , 11.0 , - 5.0 , - 16.0 , - 7.0 , - 4.0 ,
4.0 , 9.0 , - 20.0 , 3.0 , 15.0 , - 10.0 , 12.0 , 8.0 , - 6.0 , - 8.0 , - 8.0
, - 1.0 , 8.0 , 10.0 , 5.0 , - 2.0 , - 8.0 , - 8.0 , 3.0 , - 3.0 , - 6.0 ,
1.0 , 2.0 , 0.0 , - 4.0 , 4.0 , - 1.0 , 5.0 , 4.0 , - 5.0 , 2.0 , - 1.0 , 2.0
, - 2.0 , 5.0 , 1.0 , 1.0 , - 2.0 , 0.0 , - 7.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , - 29619.4 , - 1728.2 , 5186.1 , - 2267.7 ,
3068.4 , - 2481.6 , 1670.9 , - 458.0 , 1339.6 , - 2288.0 , - 227.6 , 1252.1 ,
293.4 , 714.5 , - 491.1 , 932.3 , 786.8 , 272.6 , 250.0 , - 231.9 , - 403.0 ,
119.8 , 111.3 , - 303.8 , - 218.8 , 351.4 , 43.8 , 222.3 , 171.9 , - 130.4 ,
- 133.1 , - 168.6 , - 39.3 , - 12.9 , 106.3 , 72.3 , 68.2 , - 17.4 , 74.2 ,
63.7 , - 160.9 , 65.1 , - 5.9 , - 61.2 , 16.9 , 0.7 , - 90.4 , 43.8 , 79.0 ,
- 74.0 , - 64.6 , 0.0 , - 24.2 , 33.3 , 6.2 , 9.1 , 24.0 , 6.9 , 14.8 , 7.3 ,
- 25.4 , - 1.2 , - 5.8 , 24.4 , 6.6 , 11.9 , - 9.2 , - 21.5 , - 7.9 , 8.5 , -
16.6 , - 21.5 , 9.1 , 15.5 , 7.0 , 8.9 , - 7.9 , - 14.9 , - 7.0 , - 2.1 , 5.0
, 9.4 , - 19.7 , 3.0 , 13.4 , - 8.4 , 12.5 , 6.3 , - 6.2 , - 8.9 , - 8.4 , -
1.5 , 8.4 , 9.3 , 3.8 , - 4.3 , - 8.2 , - 8.2 , 4.8 , - 2.6 , - 6.0 , 1.7 ,
1.7 , 0.0 , - 3.1 , 4.0 , - 0.5 , 4.9 , 3.7 , - 5.9 , 1.0 , - 1.2 , 2.0 , -
2.9 , 4.2 , 0.2 , 0.3 , - 2.2 , - 1.1 , - 7.4 , 2.7 , - 1.7 , 0.1 , - 1.9 ,
1.3 , 1.5 , - 0.9 , - 0.1 , - 2.6 , 0.1 , 0.9 , - 0.7 , - 0.7 , 0.7 , - 2.8 ,
1.7 , - 0.9 , 0.1 , - 1.2 , 1.2 , - 1.9 , 4.0 , - 0.9 , - 2.2 , - 0.3 , - 0.4
, 0.2 , 0.3 , 0.9 , 2.5 , - 0.2 , - 2.6 , 0.9 , 0.7 , - 0.5 , 0.3 , 0.3 , 0.0
, - 0.3 , 0.0 , - 0.4 , 0.3 , - 0.1 , - 0.9 , - 0.2 , - 0.4 , - 0.4 , 0.8 , -
0.2 , - 0.9 , - 0.9 , 0.3 , 0.2 , 0.1 , 1.8 , - 0.4 , - 0.4 , 1.3 , - 1.0 , -
0.4 , - 0.1 , 0.7 , 0.7 , - 0.4 , 0.3 , 0.3 , 0.6 , - 0.1 , 0.3 , 0.4 , - 0.2
, 0.0 , - 0.5 , 0.1 , - 0.9 , - 29554.63 , - 1669.05 , 5077.99 , - 2337.24 ,
3047.69 , - 2594.5 , 1657.76 , - 515.43 , 1336.3 , - 2305.83 , - 198.86 ,
1246.39 , 269.72 , 672.51 , - 524.72 , 920.55 , 797.96 , 282.07 , 210.65 , -
225.23 , - 379.86 , 145.15 , 100.0 , - 305.36 , - 227.0 , 354.41 , 42.72 ,
208.95 , 180.25 , - 136.54 , - 123.45 , - 168.05 , - 19.57 , - 13.55 , 103.85
, 73.6 , 69.56 , - 20.33 , 76.74 , 54.75 , - 151.34 , 63.63 , - 14.58 , -
63.53 , 14.58 , 0.24 , - 86.36 , 50.94 , 79.88 , - 74.46 , - 61.14 , - 1.65 ,
- 22.57 , 38.73 , 6.82 , 12.3 , 25.35 , 9.37 , 10.93 , 5.42 , - 26.32 , 1.94
, - 4.64 , 24.8 , 7.62 , 11.2 , - 11.73 , - 20.88 , - 6.88 , 9.83 , - 18.11 ,
- 19.71 , 10.17 , 16.22 , 9.36 , 7.61 , - 11.25 , - 12.76 , - 4.87 , - 0.06 ,
5.58 , 9.76 , - 20.11 , 3.58 , 12.69 , - 6.94 , 12.67 , 5.01 , - 6.72 , -
10.76 , - 8.16 , - 1.25 , 8.1 , 8.76 , 2.92 , - 6.66 , - 7.73 , - 9.22 , 6.01
, - 2.17 , - 6.12 , 2.19 , 1.42 , 0.1 , - 2.35 , 4.46 , - 0.15 , 4.76 , 3.06
, - 6.58 , 0.29 , - 1.01 , 2.06 , - 3.47 , 3.77 , - 0.86 , - 0.21 , - 2.31 ,
- 2.09 , - 7.93 , 2.95 , - 1.6 , 0.26 , - 1.88 , 1.44 , 1.44 , - 0.77 , -
0.31 , - 2.27 , 0.29 , 0.9 , - 0.79 , - 0.58 , 0.53 , - 2.69 , 1.8 , - 1.08 ,
0.16 , - 1.58 , 0.96 , - 1.9 , 3.99 , - 1.39 , - 2.15 , - 0.29 , - 0.55 ,
0.21 , 0.23 , 0.89 , 2.38 , - 0.38 , - 2.63 , 0.96 , 0.61 , - 0.3 , 0.4 ,
0.46 , 0.01 , - 0.35 , 0.02 , - 0.36 , 0.28 , 0.08 , - 0.87 , - 0.49 , - 0.34
, - 0.08 , 0.88 , - 0.16 , - 0.88 , - 0.76 , 0.3 , 0.33 , 0.28 , 1.72 , -
0.43 , - 0.54 , 1.18 , - 1.07 , - 0.37 , - 0.04 , 0.75 , 0.63 , - 0.26 , 0.21
, 0.35 , 0.53 , - 0.05 , 0.38 , 0.41 , - 0.22 , - 0.1 , - 0.57 , - 0.18 , -
0.82 , - 29496.5 , - 1585.9 , 4945.1 , - 2396.6 , 3026.0 , - 2707.7 , 1668.6
, - 575.4 , 1339.7 , - 2326.3 , - 160.5 , 1231.7 , 251.7 , 634.2 , - 536.8 ,
912.6 , 809.0 , 286.4 , 166.6 , - 211.2 , - 357.1 , 164.4 , 89.7 , - 309.2 ,
- 231.1 , 357.2 , 44.7 , 200.3 , 188.9 , - 141.2 , - 118.1 , - 163.1 , 0.1 ,
- 7.7 , 100.9 , 72.8 , 68.6 , - 20.8 , 76.0 , 44.2 , - 141.4 , 61.5 , - 22.9
, - 66.3 , 13.1 , 3.1 , - 77.9 , 54.9 , 80.4 , - 75.0 , - 57.8 , - 4.7 , -
21.2 , 45.3 , 6.6 , 14.0 , 24.9 , 10.4 , 7.0 , 1.6 , - 27.7 , 4.9 , - 3.4 ,
24.3 , 8.2 , 10.9 , - 14.5 , - 20.0 , - 5.7 , 11.9 , - 19.3 , - 17.4 , 11.6 ,
16.7 , 10.9 , 7.1 , - 14.1 , - 10.8 , - 3.7 , 1.7 , 5.4 , 9.4 , - 20.5 , 3.4
, 11.6 , - 5.3 , 12.8 , 3.1 , - 7.2 , - 12.4 , - 7.4 , - 0.8 , 8.0 , 8.4 ,
2.2 , - 8.4 , - 6.1 , - 10.1 , 7.0 , - 2.0 , - 6.3 , 2.8 , 0.9 , - 0.1 , -
1.1 , 4.7 , - 0.2 , 4.4 , 2.5 , - 7.2 , - 0.3 , - 1.0 , 2.2 , - 4.0 , 3.1 , -
2.0 , - 1.0 , - 2.0 , - 2.8 , - 8.3 , 3.0 , - 1.5 , 0.1 , - 2.1 , 1.7 , 1.6 ,
- 0.6 , - 0.5 , - 1.8 , 0.5 , 0.9 , - 0.8 , - 0.4 , 0.4 , - 2.5 , 1.8 , - 1.3
, 0.2 , - 2.1 , 0.8 , - 1.9 , 3.8 , - 1.8 , - 2.1 , - 0.2 , - 0.8 , 0.3 , 0.3
, 1.0 , 2.2 , - 0.7 , - 2.5 , 0.9 , 0.5 , - 0.1 , 0.6 , 0.5 , 0.0 , - 0.4 ,
0.1 , - 0.4 , 0.3 , 0.2 , - 0.9 , - 0.8 , - 0.2 , 0.0 , 0.8 , - 0.2 , - 0.9 ,
- 0.8 , 0.3 , 0.3 , 0.4 , 1.7 , - 0.4 , - 0.6 , 1.1 , - 1.2 , - 0.3 , - 0.1 ,
0.8 , 0.5 , - 0.2 , 0.1 , 0.4 , 0.5 , 0.0 , 0.4 , 0.4 , - 0.2 , - 0.3 , - 0.5
, - 0.3 , - 0.8 , 11.4 , 16.7 , - 28.8 , - 11.3 , - 3.9 , - 23.0 , 2.7 , -
12.9 , 1.3 , - 3.9 , 8.6 , - 2.9 , - 2.9 , - 8.1 , - 2.1 , - 1.4 , 2.0 , 0.4
, - 8.9 , 3.2 , 4.4 , 3.6 , - 2.3 , - 0.8 , - 0.5 , 0.5 , 0.5 , - 1.5 , 1.5 ,
- 0.7 , 0.9 , 1.3 , 3.7 , 1.4 , - 0.6 , - 0.3 , - 0.3 , - 0.1 , - 0.3 , - 2.1
, 1.9 , - 0.4 , - 1.6 , - 0.5 , - 0.2 , 0.8 , 1.8 , 0.5 , 0.2 , - 0.1 , 0.6 ,
- 0.6 , 0.3 , 1.4 , - 0.2 , 0.3 , - 0.1 , 0.1 , - 0.8 , - 0.8 , - 0.3 , 0.4 ,
0.2 , - 0.1 , 0.1 , 0.0 , - 0.5 , 0.2 , 0.3 , 0.5 , - 0.3 , 0.4 , 0.3 , 0.1 ,
0.2 , - 0.1 , - 0.5 , 0.4 , 0.2 , 0.4 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 } ; if ( ssIsContinuousTask ( rtS , 0 ) ) {
srClearBC ( rtDW . icv4qsjrec ) ; srClearBC ( rtDW . ggsva4qu4a ) ; srClearBC
( rtDW . kddtry4ekq ) ; srClearBC ( rtDW . gxgp4hskcm ) ; srClearBC ( rtDW .
azyx1ts0yu ) ; irzywnigjr_idx_0 = rtX . hjkn3n4lly [ 0 ] ; irzywnigjr_idx_1 =
rtX . hjkn3n4lly [ 1 ] ; irzywnigjr_idx_2 = rtX . hjkn3n4lly [ 2 ] ; rtB .
jhikopnu5c = muDoubleScalarSqrt ( ( rtX . hjkn3n4lly [ 0 ] * rtX . hjkn3n4lly
[ 0 ] + rtX . hjkn3n4lly [ 1 ] * rtX . hjkn3n4lly [ 1 ] ) + rtX . hjkn3n4lly
[ 2 ] * rtX . hjkn3n4lly [ 2 ] ) * 180.0 / 3.1415926535897931 ; rtY .
jwku2vbe0w = rtB . jhikopnu5c ; jkvgcfu3cx = rtP . sec_per_day_Gain * ssGetT
( rtS ) + rtP . jd ; T = ( jkvgcfu3cx - 2.451545E+6 ) / 36525.0 ; M = (
35999.045 * T + 357.5256 ) * 0.017453292519943295 ; ovpn3bsi5w = ( ( ( (
muDoubleScalarSin ( 2.0 * M ) * 72.0 + 6892.0 * muDoubleScalarSin ( M ) ) +
1250.09115 * T ) / 3600.0 + 282.94 ) - 0.002652 ) * 0.017453292519943295 + M
; M = ( 1.49619E+8 - 2.499E+6 * muDoubleScalarCos ( M ) ) - muDoubleScalarCos
( 2.0 * M ) * 21000.0 ; T = muDoubleScalarSin ( ovpn3bsi5w ) ; lyw5zuxpkh [ 0
] = M * muDoubleScalarCos ( ovpn3bsi5w ) ; lyw5zuxpkh [ 1 ] = M *
0.91748206207689575 * T ; lyw5zuxpkh [ 2 ] = M * 0.39777715591412138 * T ; if
( ssIsModeUpdateTimeStep ( rtS ) ) { for ( i = 0 ; i < 6 ; i ++ ) { if ( rtDW
. cu35sqihey != 0 ) { rtX . oxovzkyrgp [ i ] = rtB . lzmaq0diab [ i ] ; }
lq1oh3hzzm [ i ] = rtX . oxovzkyrgp [ i ] ; } } else { for ( i = 0 ; i < 6 ;
i ++ ) { lq1oh3hzzm [ i ] = rtX . oxovzkyrgp [ i ] ; } } d22ngtbkmu [ 1 ] =
lq1oh3hzzm [ 1 ] ; ovpn3bsi5w = lq1oh3hzzm [ 4 ] ; M = lq1oh3hzzm [ 5 ] ; if
( lq1oh3hzzm [ 1 ] < 0.0 ) { d22ngtbkmu [ 1 ] = - lq1oh3hzzm [ 1 ] ;
ovpn3bsi5w = lq1oh3hzzm [ 4 ] + 3.1415926535897931 ; M = lq1oh3hzzm [ 5 ] +
3.1415926535897931 ; } d22ngtbkmu [ 4 ] = ovpn3bsi5w - muDoubleScalarFloor (
ovpn3bsi5w / 2.0 / 3.1415926535897931 ) * 6.2831853071795862 ; d22ngtbkmu [ 5
] = M - muDoubleScalarFloor ( M / 2.0 / 3.1415926535897931 ) *
6.2831853071795862 ; d22ngtbkmu [ 0 ] = lq1oh3hzzm [ 0 ] ; d22ngtbkmu [ 2 ] =
lq1oh3hzzm [ 2 ] ; d22ngtbkmu [ 3 ] = lq1oh3hzzm [ 3 ] - muDoubleScalarFloor
( lq1oh3hzzm [ 3 ] / 2.0 / 3.1415926535897931 ) * 6.2831853071795862 ; e =
d22ngtbkmu [ 1 ] ; M = d22ngtbkmu [ 5 ] ; ovpn3bsi5w = ( 1.0 - d22ngtbkmu [ 1
] ) * d22ngtbkmu [ 0 ] ; if ( d22ngtbkmu [ 1 ] == 0.0 ) { M = d22ngtbkmu [ 5
] ; e = d22ngtbkmu [ 0 ] ; } else if ( d22ngtbkmu [ 1 ] == 1.0 ) { e =
d22ngtbkmu [ 5 ] * d22ngtbkmu [ 5 ] ; delta = e * d22ngtbkmu [ 5 ] ; ea = (
2.0 * delta + d22ngtbkmu [ 5 ] ) / ( ( e + 1.0 ) * 3.0 ) ; delta = ( 3.0 * ea
+ delta ) - d22ngtbkmu [ 5 ] ; while ( muDoubleScalarAbs ( delta ) > rtP .
TOLERANCE ) { e = ea * ea ; delta = e * ea ; ea = ( 2.0 * delta + M ) / ( ( e
+ 1.0 ) * 3.0 ) ; delta = ( 3.0 * ea + delta ) - M ; } M = 2.0 *
muDoubleScalarAtan ( ea ) ; e = ( e + 1.0 ) * ovpn3bsi5w ; } else { ea =
d22ngtbkmu [ 5 ] ; for ( delta = ( d22ngtbkmu [ 5 ] - d22ngtbkmu [ 1 ] *
muDoubleScalarSin ( d22ngtbkmu [ 5 ] ) ) - d22ngtbkmu [ 5 ] ;
muDoubleScalarAbs ( delta ) > rtP . TOLERANCE ; delta = ( ea - e *
muDoubleScalarSin ( ea ) ) - M ) { ea -= delta / ( 1.0 - e *
muDoubleScalarCos ( ea ) ) ; } M = muDoubleScalarAtan ( muDoubleScalarSqrt (
( d22ngtbkmu [ 1 ] + 1.0 ) / ( 1.0 - d22ngtbkmu [ 1 ] ) ) * muDoubleScalarTan
( ea / 2.0 ) ) * 2.0 ; e = ( d22ngtbkmu [ 1 ] + 1.0 ) * ovpn3bsi5w / (
d22ngtbkmu [ 1 ] * muDoubleScalarCos ( M ) + 1.0 ) ; } ea = M -
muDoubleScalarFloor ( M / 2.0 / 3.1415926535897931 ) * 6.2831853071795862 ; u
= d22ngtbkmu [ 4 ] + ea ; h = muDoubleScalarSqrt ( ( 1.0 - d22ngtbkmu [ 1 ] *
d22ngtbkmu [ 1 ] ) * d22ngtbkmu [ 0 ] * rtP . GE ) ; cu = muDoubleScalarCos (
u ) ; su = muDoubleScalarSin ( u ) ; ci = muDoubleScalarCos ( d22ngtbkmu [ 2
] ) ; u = muDoubleScalarSin ( d22ngtbkmu [ 2 ] ) ; cW = muDoubleScalarCos (
d22ngtbkmu [ 3 ] ) ; sW = muDoubleScalarSin ( d22ngtbkmu [ 3 ] ) ; hqbmtiz1ck
[ 0 ] = ( cu * cW - su * ci * sW ) * e ; hqbmtiz1ck [ 1 ] = ( su * ci * cW +
cu * sW ) * e ; hqbmtiz1ck [ 2 ] = e * su * u ; r_dot = h / d22ngtbkmu [ 0 ]
/ ( 1.0 - d22ngtbkmu [ 1 ] * d22ngtbkmu [ 1 ] ) * d22ngtbkmu [ 1 ] *
muDoubleScalarSin ( ea ) ; h = h / e / e ; M = aq3jzkyuad ( hqbmtiz1ck ) ;
otiigwfvqy = aq3jzkyuad ( lyw5zuxpkh ) ; ovpn3bsi5w = ( lyw5zuxpkh [ 0 ] /
otiigwfvqy * hqbmtiz1ck [ 0 ] + lyw5zuxpkh [ 1 ] / otiigwfvqy * hqbmtiz1ck [
1 ] ) + lyw5zuxpkh [ 2 ] / otiigwfvqy * hqbmtiz1ck [ 2 ] ; rtB . kimclls5ui =
0.0 ; if ( ( ovpn3bsi5w > 0.0 ) || ( M * M - ovpn3bsi5w * ovpn3bsi5w > rtP .
earth_radius * rtP . earth_radius ) ) { rtB . kimclls5ui = 1.0 ; } rtY .
fudrm4x01v = rtB . kimclls5ui ; rtB . gv3z4rzpl5 [ 0 ] = rtP .
Gain_Gain_itrtl3m3mg * rtX . hjkn3n4lly [ 0 ] ; rtY . nza55qah0g [ 0 ] = rtB
. gv3z4rzpl5 [ 0 ] ; ono5ii4s3b_idx_2 = lyw5zuxpkh [ 0 ] - hqbmtiz1ck [ 0 ] ;
M = ono5ii4s3b_idx_2 * ono5ii4s3b_idx_2 ; ono5ii4s3b_idx_0 = ono5ii4s3b_idx_2
; rtB . gv3z4rzpl5 [ 1 ] = rtP . Gain_Gain_itrtl3m3mg * rtX . hjkn3n4lly [ 1
] ; rtY . nza55qah0g [ 1 ] = rtB . gv3z4rzpl5 [ 1 ] ; ono5ii4s3b_idx_2 =
lyw5zuxpkh [ 1 ] - hqbmtiz1ck [ 1 ] ; hakul2mmal_idx_1 = ono5ii4s3b_idx_2 *
ono5ii4s3b_idx_2 ; ono5ii4s3b_idx_1 = ono5ii4s3b_idx_2 ; rtB . gv3z4rzpl5 [ 2
] = rtP . Gain_Gain_itrtl3m3mg * rtX . hjkn3n4lly [ 2 ] ; rtY . nza55qah0g [
2 ] = rtB . gv3z4rzpl5 [ 2 ] ; ono5ii4s3b_idx_2 = lyw5zuxpkh [ 2 ] -
hqbmtiz1ck [ 2 ] ; hakul2mmal_idx_1 = ( M + hakul2mmal_idx_1 ) +
ono5ii4s3b_idx_2 * ono5ii4s3b_idx_2 ; if ( hakul2mmal_idx_1 < 0.0 ) {
hakul2mmal_idx_1 = - muDoubleScalarSqrt ( muDoubleScalarAbs (
hakul2mmal_idx_1 ) ) ; } else { hakul2mmal_idx_1 = muDoubleScalarSqrt (
hakul2mmal_idx_1 ) ; } if ( hakul2mmal_idx_1 > rtP .
NormalizeVector_maxzero_lpqo5h1ax3 ) { m5crkrq425_idx_0 = hakul2mmal_idx_1 ;
} else { ono5ii4s3b_idx_0 *= 0.0 ; ono5ii4s3b_idx_1 *= 0.0 ; ono5ii4s3b_idx_2
*= 0.0 ; m5crkrq425_idx_0 = rtP . Constant_Value_kxh4uvpty4 ; }
ono5ii4s3b_idx_0 /= m5crkrq425_idx_0 ; ono5ii4s3b_idx_1 /= m5crkrq425_idx_0 ;
ono5ii4s3b_idx_2 /= m5crkrq425_idx_0 ; M = muDoubleScalarSqrt ( ( ( rtX .
pcdkwn41rb [ 0 ] * rtX . pcdkwn41rb [ 0 ] + rtX . pcdkwn41rb [ 1 ] * rtX .
pcdkwn41rb [ 1 ] ) + rtX . pcdkwn41rb [ 2 ] * rtX . pcdkwn41rb [ 2 ] ) + rtX
. pcdkwn41rb [ 3 ] * rtX . pcdkwn41rb [ 3 ] ) ; hakul2mmal_idx_1 = rtX .
pcdkwn41rb [ 2 ] / M ; delta = rtX . pcdkwn41rb [ 0 ] / M ; ovpn3bsi5w = rtX
. pcdkwn41rb [ 1 ] / M ; M = rtX . pcdkwn41rb [ 3 ] / M ; dk2rjxlhn5 =
muDoubleScalarSqrt ( ( ( delta * delta + ovpn3bsi5w * ovpn3bsi5w ) +
hakul2mmal_idx_1 * hakul2mmal_idx_1 ) + M * M ) ; otiigwfvqy =
hakul2mmal_idx_1 / dk2rjxlhn5 ; T = M / dk2rjxlhn5 ; g5zew52spt = ovpn3bsi5w
/ dk2rjxlhn5 ; dk2rjxlhn5 = delta / dk2rjxlhn5 ; drd0rcd33w = ( ( ( rtP .
Constant_Value_czynuf313b - otiigwfvqy * otiigwfvqy ) - T * T ) * rtP .
Gain2_Gain_ckacseigw1 * ono5ii4s3b_idx_0 + ( g5zew52spt * otiigwfvqy +
dk2rjxlhn5 * T ) * rtP . Gain_Gain_l1oovl4sve * ono5ii4s3b_idx_1 ) + (
g5zew52spt * T - dk2rjxlhn5 * otiigwfvqy ) * rtP . Gain1_Gain_bysm1h5wxu *
ono5ii4s3b_idx_2 ; lgn4rji20w = ( ( ( rtP . Constant_Value_h4xungkdn0 -
g5zew52spt * g5zew52spt ) - T * T ) * rtP . Gain2_Gain_kdxyjqh15k *
ono5ii4s3b_idx_1 + ( g5zew52spt * otiigwfvqy - dk2rjxlhn5 * T ) * rtP .
Gain_Gain_iduukqmyr5 * ono5ii4s3b_idx_0 ) + ( dk2rjxlhn5 * g5zew52spt +
otiigwfvqy * T ) * rtP . Gain1_Gain_bv1sce1ofn * ono5ii4s3b_idx_2 ;
ebdsqxa0pr = ( ( g5zew52spt * T + dk2rjxlhn5 * otiigwfvqy ) * rtP .
Gain_Gain_py1ocxtdbg * ono5ii4s3b_idx_0 + ( otiigwfvqy * T - dk2rjxlhn5 *
g5zew52spt ) * rtP . Gain1_Gain_jhnqeojsbu * ono5ii4s3b_idx_1 ) + ( ( rtP .
Constant_Value_but5tairxf - g5zew52spt * g5zew52spt ) - otiigwfvqy *
otiigwfvqy ) * rtP . Gain2_Gain_dmh23oivep * ono5ii4s3b_idx_2 ; dk2rjxlhn5 =
3.3121686421112381E-170 ; absxk = muDoubleScalarAbs ( drd0rcd33w ) ; if (
absxk > 3.3121686421112381E-170 ) { g5zew52spt = 1.0 ; dk2rjxlhn5 = absxk ; }
else { T = absxk / 3.3121686421112381E-170 ; g5zew52spt = T * T ; } absxk =
muDoubleScalarAbs ( lgn4rji20w ) ; if ( absxk > dk2rjxlhn5 ) { T = dk2rjxlhn5
/ absxk ; g5zew52spt = g5zew52spt * T * T + 1.0 ; dk2rjxlhn5 = absxk ; } else
{ T = absxk / dk2rjxlhn5 ; g5zew52spt += T * T ; } absxk = muDoubleScalarAbs
( ebdsqxa0pr ) ; if ( absxk > dk2rjxlhn5 ) { T = dk2rjxlhn5 / absxk ;
g5zew52spt = g5zew52spt * T * T + 1.0 ; dk2rjxlhn5 = absxk ; } else { T =
absxk / dk2rjxlhn5 ; g5zew52spt += T * T ; } g5zew52spt = dk2rjxlhn5 *
muDoubleScalarSqrt ( g5zew52spt ) ; otiigwfvqy = ( drd0rcd33w / g5zew52spt *
0.0 + lgn4rji20w / g5zew52spt * 0.0 ) - ebdsqxa0pr / g5zew52spt ; if (
otiigwfvqy > 1.0 ) { otiigwfvqy = 1.0 ; } if ( otiigwfvqy < - 1.0 ) {
otiigwfvqy = - 1.0 ; } rtB . a3fezsr2vw = muDoubleScalarAcos ( otiigwfvqy ) /
3.1415926535897931 * 180.0 ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { }
otiigwfvqy = rtX . b4ena3lr0n ; rtB . pmkqoqavmi = ( rtB . euwsxn4aph - rtP .
TransferFcn1_C * rtX . l50b0cuk2h ) - rtP . RW_kE * rtX . b4ena3lr0n ;
lf41id4igu = 0.0 ; lf41id4igu += rtP . motor_D * rtB . pmkqoqavmi ;
gla0ncnrx0 ( rtB . d2nlp5u0iz [ 0 ] , rtB . pmkqoqavmi , lf41id4igu , & rtB .
mzrdmi3ngp ) ; if ( rtB . mzrdmi3ngp . ozezoxky3t >= rtP . Switch1_Threshold
) { i4jz3egckp = lf41id4igu ; } else { i4jz3egckp = rtP .
Constant1_Value_oxbz4wjuse ; } g3res1bek1 ( i4jz3egckp , & rtB . k4gpt5xlei )
; geanfu3bne = rtP . rad2rpm_Gain * rtX . b4ena3lr0n ; fgza3nsgzk (
geanfu3bne , & rtB . gszk3bc3vp ) ; rtB . fdbl5l21n4 [ 0 ] = rtB . mzrdmi3ngp
. ozezoxky3t ; rtB . fdbl5l21n4 [ 1 ] = rtB . k4gpt5xlei . nd52bn25fb ; rtB .
fdbl5l21n4 [ 2 ] = rtB . gszk3bc3vp . h0dxk1yimp ; rtB . fdbl5l21n4 [ 3 ] =
rtB . mzrdmi3ngp . g5m2irbsxw ; rtB . fdbl5l21n4 [ 4 ] = rtB . mzrdmi3ngp .
h5cyove4ef ; rtB . fdbl5l21n4 [ 5 ] = rtB . gszk3bc3vp . jeak4pqr3j ; rtB .
fdbl5l21n4 [ 6 ] = i4jz3egckp ; rtB . fdbl5l21n4 [ 7 ] = rtP .
Constant1_Value_iq2e102mi0 ; { SimStruct * rts = ssGetSFunction ( rtS , 1 ) ;
{ static const char * blockSIDForSFcnLoader = "SILS_20241709:552" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 0 <= 1 ) && gbl_raccel_tid01eq ? 0 : 0 ) ; } } k50kzncrsl =
rtX . fnheb54sgb ; rtB . chofn13vqp = ( rtB . llfqz3cih1 - rtP .
TransferFcn1_C_mq40l21bd4 * rtX . lbdfwq1i3y ) - rtP . RW_kE * rtX .
fnheb54sgb ; ljtf33toyo = 0.0 ; ljtf33toyo += rtP . motor_D_c2y52zc0tt * rtB
. chofn13vqp ; gla0ncnrx0 ( rtB . lrdfz5anhg [ 0 ] , rtB . chofn13vqp ,
ljtf33toyo , & rtB . dbik3caean ) ; if ( rtB . dbik3caean . ozezoxky3t >= rtP
. Switch1_Threshold_gkzjd52v3i ) { g2acauyoyt = ljtf33toyo ; } else {
g2acauyoyt = rtP . Constant1_Value_hlcqpzkeg5 ; } g3res1bek1 ( g2acauyoyt , &
rtB . nbdejsvdft ) ; ivwumm0lpw = rtP . rad2rpm_Gain_l4jmsoyq2v * rtX .
fnheb54sgb ; fgza3nsgzk ( ivwumm0lpw , & rtB . mx32imycyi ) ; rtB .
oucj4k4y2q [ 0 ] = rtB . dbik3caean . ozezoxky3t ; rtB . oucj4k4y2q [ 1 ] =
rtB . nbdejsvdft . nd52bn25fb ; rtB . oucj4k4y2q [ 2 ] = rtB . mx32imycyi .
h0dxk1yimp ; rtB . oucj4k4y2q [ 3 ] = rtB . dbik3caean . g5m2irbsxw ; rtB .
oucj4k4y2q [ 4 ] = rtB . dbik3caean . h5cyove4ef ; rtB . oucj4k4y2q [ 5 ] =
rtB . mx32imycyi . jeak4pqr3j ; rtB . oucj4k4y2q [ 6 ] = g2acauyoyt ; rtB .
oucj4k4y2q [ 7 ] = rtP . Constant6_Value_oipnu5fd53 ; { SimStruct * rts =
ssGetSFunction ( rtS , 2 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:549" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } jwppuzxlko = rtX . argwmtgb5v ; rtB .
c5lfdegv0p = ( rtB . kiyg1swe1h - rtP . TransferFcn1_C_e5t3t2za0w * rtX .
muv5xwjpjd ) - rtP . RW_kE * rtX . argwmtgb5v ; mkyk40n3sw = 0.0 ; mkyk40n3sw
+= rtP . motor_D_p4qvhshwgu * rtB . c5lfdegv0p ; gla0ncnrx0 ( rtB .
cvndu2lgp0 [ 0 ] , rtB . c5lfdegv0p , mkyk40n3sw , & rtB . a4nohvrqys ) ; if
( rtB . a4nohvrqys . ozezoxky3t >= rtP . Switch1_Threshold_lagl2moogx ) {
hxeyppvwpl = mkyk40n3sw ; } else { hxeyppvwpl = rtP .
Constant1_Value_jbsud0br1l ; } g3res1bek1 ( hxeyppvwpl , & rtB . fovau4dl3r )
; p1oqolb2r3 = rtP . rad2rpm_Gain_nwcckeryhk * rtX . argwmtgb5v ; fgza3nsgzk
( p1oqolb2r3 , & rtB . df0oudwkj0 ) ; rtB . ktlu1ekw1m [ 0 ] = rtB .
a4nohvrqys . ozezoxky3t ; rtB . ktlu1ekw1m [ 1 ] = rtB . fovau4dl3r .
nd52bn25fb ; rtB . ktlu1ekw1m [ 2 ] = rtB . df0oudwkj0 . h0dxk1yimp ; rtB .
ktlu1ekw1m [ 3 ] = rtB . a4nohvrqys . g5m2irbsxw ; rtB . ktlu1ekw1m [ 4 ] =
rtB . a4nohvrqys . h5cyove4ef ; rtB . ktlu1ekw1m [ 5 ] = rtB . df0oudwkj0 .
jeak4pqr3j ; rtB . ktlu1ekw1m [ 6 ] = hxeyppvwpl ; rtB . ktlu1ekw1m [ 7 ] =
rtP . Constant2_Value_fgyxvvitry ; { SimStruct * rts = ssGetSFunction ( rtS ,
3 ) ; { static const char * blockSIDForSFcnLoader = "SILS_20241709:555" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 0 <= 1 ) && gbl_raccel_tid01eq ? 0 : 0 ) ; } } gomxyom0vc =
rtX . cmyui1ww54 ; rtB . ju0zmrtbs0 = ( rtB . el4rhtecud - rtP .
TransferFcn1_C_exc4t4wdx0 * rtX . bxdhuzrxz2 ) - rtP . RW_kE * rtX .
cmyui1ww54 ; flu00snx4l = 0.0 ; flu00snx4l += rtP . motor_D_ngzzpzruyi * rtB
. ju0zmrtbs0 ; gla0ncnrx0 ( rtB . mslzotztaf [ 0 ] , rtB . ju0zmrtbs0 ,
flu00snx4l , & rtB . jjm2phe1us ) ; if ( rtB . jjm2phe1us . ozezoxky3t >= rtP
. Switch1_Threshold_nalfp5zuzj ) { j4xyasklvt = flu00snx4l ; } else {
j4xyasklvt = rtP . Constant1_Value_bvl32d0cmp ; } g3res1bek1 ( j4xyasklvt , &
rtB . aomn2ihkzv ) ; anqmvhm2ud = rtP . rad2rpm_Gain_pceq0ixqio * rtX .
cmyui1ww54 ; fgza3nsgzk ( anqmvhm2ud , & rtB . iroofsivyk ) ; rtB .
innw5sywzg [ 0 ] = rtB . jjm2phe1us . ozezoxky3t ; rtB . innw5sywzg [ 1 ] =
rtB . aomn2ihkzv . nd52bn25fb ; rtB . innw5sywzg [ 2 ] = rtB . iroofsivyk .
h0dxk1yimp ; rtB . innw5sywzg [ 3 ] = rtB . jjm2phe1us . g5m2irbsxw ; rtB .
innw5sywzg [ 4 ] = rtB . jjm2phe1us . h5cyove4ef ; rtB . innw5sywzg [ 5 ] =
rtB . iroofsivyk . jeak4pqr3j ; rtB . innw5sywzg [ 6 ] = j4xyasklvt ; rtB .
innw5sywzg [ 7 ] = rtP . Constant3_Value_mtqeqchjq3 ; { SimStruct * rts =
ssGetSFunction ( rtS , 4 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:558" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } dk2rjxlhn5 = ( ( delta * rtP .
STT1_b2c_quat [ 0 ] - ovpn3bsi5w * rtP . STT1_b2c_quat [ 1 ] ) -
hakul2mmal_idx_1 * rtP . STT1_b2c_quat [ 2 ] ) - M * rtP . STT1_b2c_quat [ 3
] ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . ndtffugziw [ 0 ] =
muDoubleScalarCos ( rtDW . hrquh23lee [ 0 ] / 2.0 ) ; rtB . ndtffugziw [ 1 ]
= muDoubleScalarSin ( rtDW . hrquh23lee [ 0 ] / 2.0 ) ; rtB . ndtffugziw [ 2
] = 0.0 ; rtB . ndtffugziw [ 3 ] = 0.0 ; rtB . ndtffugziw [ 4 ] =
muDoubleScalarCos ( rtDW . hrquh23lee [ 1 ] / 2.0 ) ; rtB . ndtffugziw [ 5 ]
= 0.0 ; rtB . ndtffugziw [ 6 ] = muDoubleScalarSin ( rtDW . hrquh23lee [ 1 ]
/ 2.0 ) ; rtB . ndtffugziw [ 7 ] = 0.0 ; rtB . ndtffugziw [ 8 ] =
muDoubleScalarCos ( rtDW . hrquh23lee [ 2 ] / 2.0 ) ; rtB . ndtffugziw [ 9 ]
= 0.0 ; rtB . ndtffugziw [ 10 ] = 0.0 ; rtB . ndtffugziw [ 11 ] =
muDoubleScalarSin ( rtDW . hrquh23lee [ 2 ] / 2.0 ) ; } absxk = ( ( delta *
rtP . STT1_b2c_quat [ 1 ] + ovpn3bsi5w * rtP . STT1_b2c_quat [ 0 ] ) +
hakul2mmal_idx_1 * rtP . STT1_b2c_quat [ 3 ] ) - M * rtP . STT1_b2c_quat [ 2
] ; ono5ii4s3b_idx_0 = ( ( delta * rtP . STT1_b2c_quat [ 2 ] - ovpn3bsi5w *
rtP . STT1_b2c_quat [ 3 ] ) + hakul2mmal_idx_1 * rtP . STT1_b2c_quat [ 0 ] )
+ M * rtP . STT1_b2c_quat [ 1 ] ; ono5ii4s3b_idx_1 = ( ( delta * rtP .
STT1_b2c_quat [ 3 ] + ovpn3bsi5w * rtP . STT1_b2c_quat [ 2 ] ) -
hakul2mmal_idx_1 * rtP . STT1_b2c_quat [ 1 ] ) + M * rtP . STT1_b2c_quat [ 0
] ; T = ( ( dk2rjxlhn5 * rtB . ndtffugziw [ 0 ] - absxk * rtB . ndtffugziw [
1 ] ) - ono5ii4s3b_idx_0 * rtB . ndtffugziw [ 2 ] ) - ono5ii4s3b_idx_1 * rtB
. ndtffugziw [ 3 ] ; g5zew52spt = ( ( dk2rjxlhn5 * rtB . ndtffugziw [ 1 ] +
absxk * rtB . ndtffugziw [ 0 ] ) + ono5ii4s3b_idx_0 * rtB . ndtffugziw [ 3 ]
) - ono5ii4s3b_idx_1 * rtB . ndtffugziw [ 2 ] ; oqmv0ahkug = ( ( dk2rjxlhn5 *
rtB . ndtffugziw [ 2 ] - absxk * rtB . ndtffugziw [ 3 ] ) + ono5ii4s3b_idx_0
* rtB . ndtffugziw [ 0 ] ) + ono5ii4s3b_idx_1 * rtB . ndtffugziw [ 1 ] ;
ono5ii4s3b_idx_1 = ( ( dk2rjxlhn5 * rtB . ndtffugziw [ 3 ] + absxk * rtB .
ndtffugziw [ 2 ] ) - ono5ii4s3b_idx_0 * rtB . ndtffugziw [ 1 ] ) +
ono5ii4s3b_idx_1 * rtB . ndtffugziw [ 0 ] ; dk2rjxlhn5 = ( ( T * rtB .
ndtffugziw [ 4 ] - g5zew52spt * rtB . ndtffugziw [ 5 ] ) - oqmv0ahkug * rtB .
ndtffugziw [ 6 ] ) - ono5ii4s3b_idx_1 * rtB . ndtffugziw [ 7 ] ; absxk = ( (
T * rtB . ndtffugziw [ 5 ] + g5zew52spt * rtB . ndtffugziw [ 4 ] ) +
oqmv0ahkug * rtB . ndtffugziw [ 7 ] ) - ono5ii4s3b_idx_1 * rtB . ndtffugziw [
6 ] ; ono5ii4s3b_idx_0 = ( ( T * rtB . ndtffugziw [ 6 ] - g5zew52spt * rtB .
ndtffugziw [ 7 ] ) + oqmv0ahkug * rtB . ndtffugziw [ 4 ] ) + ono5ii4s3b_idx_1
* rtB . ndtffugziw [ 5 ] ; ono5ii4s3b_idx_1 = ( ( T * rtB . ndtffugziw [ 7 ]
+ g5zew52spt * rtB . ndtffugziw [ 6 ] ) - oqmv0ahkug * rtB . ndtffugziw [ 5 ]
) + ono5ii4s3b_idx_1 * rtB . ndtffugziw [ 4 ] ; T = ( ( dk2rjxlhn5 * rtB .
ndtffugziw [ 8 ] - absxk * rtB . ndtffugziw [ 9 ] ) - ono5ii4s3b_idx_0 * rtB
. ndtffugziw [ 10 ] ) - ono5ii4s3b_idx_1 * rtB . ndtffugziw [ 11 ] ;
g5zew52spt = ( ( dk2rjxlhn5 * rtB . ndtffugziw [ 9 ] + absxk * rtB .
ndtffugziw [ 8 ] ) + ono5ii4s3b_idx_0 * rtB . ndtffugziw [ 11 ] ) -
ono5ii4s3b_idx_1 * rtB . ndtffugziw [ 10 ] ; oqmv0ahkug = ( ( dk2rjxlhn5 *
rtB . ndtffugziw [ 10 ] - absxk * rtB . ndtffugziw [ 11 ] ) +
ono5ii4s3b_idx_0 * rtB . ndtffugziw [ 8 ] ) + ono5ii4s3b_idx_1 * rtB .
ndtffugziw [ 9 ] ; dk2rjxlhn5 = ( ( dk2rjxlhn5 * rtB . ndtffugziw [ 11 ] +
absxk * rtB . ndtffugziw [ 10 ] ) - ono5ii4s3b_idx_0 * rtB . ndtffugziw [ 9 ]
) + ono5ii4s3b_idx_1 * rtB . ndtffugziw [ 8 ] ; absxk = muDoubleScalarSqrt (
( ( T * T + g5zew52spt * g5zew52spt ) + oqmv0ahkug * oqmv0ahkug ) +
dk2rjxlhn5 * dk2rjxlhn5 ) ; ono5ii4s3b_idx_0 = T / absxk ; if (
ono5ii4s3b_idx_0 < 0.0 ) { rtB . asykhtld2n [ 3 ] = - ono5ii4s3b_idx_0 ;
hmyegtxsdh_idx_1 = - ( g5zew52spt / absxk ) ; hmyegtxsdh_idx_2 = - (
oqmv0ahkug / absxk ) ; hmyegtxsdh_idx_3 = - ( dk2rjxlhn5 / absxk ) ; } else {
rtB . asykhtld2n [ 3 ] = ono5ii4s3b_idx_0 ; hmyegtxsdh_idx_1 = g5zew52spt /
absxk ; hmyegtxsdh_idx_2 = oqmv0ahkug / absxk ; hmyegtxsdh_idx_3 = dk2rjxlhn5
/ absxk ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . ff5nefkxhm = (
uint8_T ) ( rtDW . bya5fxrz4g >= rtP . STT_AD_prob ) ; } llkwb1gopr ( rtB .
ghrb02xtti , drd0rcd33w , lgn4rji20w , ebdsqxa0pr , & rtB . hiok3cyxgg ) ;
ono5ii4s3b_idx_2 = rtP . Gain_Gain_c5svou2zai * hqbmtiz1ck [ 0 ] ;
m5crkrq425_idx_0 = ono5ii4s3b_idx_2 * ono5ii4s3b_idx_2 ; ono5ii4s3b_idx_0 =
ono5ii4s3b_idx_2 ; ono5ii4s3b_idx_2 = rtP . Gain_Gain_c5svou2zai * hqbmtiz1ck
[ 1 ] ; T = ono5ii4s3b_idx_2 * ono5ii4s3b_idx_2 ; ono5ii4s3b_idx_1 =
ono5ii4s3b_idx_2 ; ono5ii4s3b_idx_2 = rtP . Gain_Gain_c5svou2zai * hqbmtiz1ck
[ 2 ] ; m5crkrq425_idx_0 = ( m5crkrq425_idx_0 + T ) + ono5ii4s3b_idx_2 *
ono5ii4s3b_idx_2 ; if ( m5crkrq425_idx_0 < 0.0 ) { m5crkrq425_idx_0 = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( m5crkrq425_idx_0 ) ) ; } else {
m5crkrq425_idx_0 = muDoubleScalarSqrt ( m5crkrq425_idx_0 ) ; } if ( ! (
m5crkrq425_idx_0 > rtP . NormalizeVector_maxzero_p5fqgxj0sr ) ) {
ono5ii4s3b_idx_0 *= 0.0 ; ono5ii4s3b_idx_1 *= 0.0 ; ono5ii4s3b_idx_2 *= 0.0 ;
m5crkrq425_idx_0 = rtP . Constant_Value_ggebjt2fys ; } ono5ii4s3b_idx_0 /=
m5crkrq425_idx_0 ; ono5ii4s3b_idx_1 /= m5crkrq425_idx_0 ; ono5ii4s3b_idx_2 /=
m5crkrq425_idx_0 ; oqmv0ahkug = muDoubleScalarSqrt ( ( ( delta * delta +
ovpn3bsi5w * ovpn3bsi5w ) + hakul2mmal_idx_1 * hakul2mmal_idx_1 ) + M * M ) ;
m5crkrq425_idx_0 = hakul2mmal_idx_1 / oqmv0ahkug ; T = M / oqmv0ahkug ;
g5zew52spt = ovpn3bsi5w / oqmv0ahkug ; oqmv0ahkug = delta / oqmv0ahkug ;
c2y5dtcawp = ( ( ( rtP . Constant_Value_kblt0a3uql - m5crkrq425_idx_0 *
m5crkrq425_idx_0 ) - T * T ) * rtP . Gain2_Gain_fbbevcwdu4 * ono5ii4s3b_idx_0
+ ( g5zew52spt * m5crkrq425_idx_0 + oqmv0ahkug * T ) * rtP .
Gain_Gain_fso4j4ph32 * ono5ii4s3b_idx_1 ) + ( g5zew52spt * T - oqmv0ahkug *
m5crkrq425_idx_0 ) * rtP . Gain1_Gain_c2qfvofd2q * ono5ii4s3b_idx_2 ;
bcyok1fmxf = ( ( ( rtP . Constant_Value_hgvjimspu2 - g5zew52spt * g5zew52spt
) - T * T ) * rtP . Gain2_Gain_o2m2nfo04s * ono5ii4s3b_idx_1 + ( g5zew52spt *
m5crkrq425_idx_0 - oqmv0ahkug * T ) * rtP . Gain_Gain_cuyfsgurxk *
ono5ii4s3b_idx_0 ) + ( oqmv0ahkug * g5zew52spt + m5crkrq425_idx_0 * T ) * rtP
. Gain1_Gain_p0weipavif * ono5ii4s3b_idx_2 ; lmhgznz12o = ( ( g5zew52spt * T
+ oqmv0ahkug * m5crkrq425_idx_0 ) * rtP . Gain_Gain_mtzedpzgxf *
ono5ii4s3b_idx_0 + ( m5crkrq425_idx_0 * T - oqmv0ahkug * g5zew52spt ) * rtP .
Gain1_Gain_fpivyqdmyd * ono5ii4s3b_idx_1 ) + ( ( rtP .
Constant_Value_jyoylqpxtd - g5zew52spt * g5zew52spt ) - m5crkrq425_idx_0 *
m5crkrq425_idx_0 ) * rtP . Gain2_Gain_eknqknt03s * ono5ii4s3b_idx_2 ;
llkwb1gopr ( rtB . ghrb02xtti , c2y5dtcawp , bcyok1fmxf , lmhgznz12o , & rtB
. fe4ousljhv ) ; m5crkrq425_idx_0 = ( jkvgcfu3cx - 2.4000005E+6 ) + rtP .
UT1_UTC / 86400.0 ; g5zew52spt = ( m5crkrq425_idx_0 - muDoubleScalarFloor (
m5crkrq425_idx_0 ) ) * 86400.0 ; m5crkrq425_idx_0 = muDoubleScalarFloor (
m5crkrq425_idx_0 ) ; T = ( m5crkrq425_idx_0 - 51544.5 ) / 36525.0 ;
m5crkrq425_idx_0 = T * T ; ono5ii4s3b_idx_2 = ( ( ( - 6.2E-6 * T + 0.093104 )
* m5crkrq425_idx_0 + 8.640184812866E+6 * T ) + 24110.54841 ) + ( ( 5.9006E-11
* T + 1.0027379093507951 ) - 5.9E-15 * m5crkrq425_idx_0 ) * g5zew52spt ;
ono5ii4s3b_idx_2 -= muDoubleScalarFloor ( ono5ii4s3b_idx_2 / 86400.0 ) *
86400.0 ; T = ( jkvgcfu3cx - 2.451545E+6 ) / 36525.0 ; m5crkrq425_idx_0 = T *
T ; T3 = m5crkrq425_idx_0 * T ; dk2rjxlhn5 = ( ( ( 1.739527263137E+9 * T +
335778.877 ) - 13.257 * m5crkrq425_idx_0 ) + 0.011 * T3 ) *
4.84813681109536E-6 ; g5zew52spt = ( ( ( 1.602961601328E+9 * T +
1.072261307E+6 ) - 6.891 * m5crkrq425_idx_0 ) + 0.019 * T3 ) *
4.84813681109536E-6 ; oqmv0ahkug = ( ( ( 450160.28 - 6.962890539E+6 * T ) +
7.455 * m5crkrq425_idx_0 ) + 0.008 * T3 ) * 4.84813681109536E-6 ; sp = ( ( (
84381.448 - 46.815 * T ) - 0.00059 * m5crkrq425_idx_0 ) + 0.001813 * T3 ) *
4.84813681109536E-6 ; c_sp = ( ( ( ( - 17.1996 - 0.01742 * T ) *
muDoubleScalarSin ( oqmv0ahkug ) + ( 2.0E-5 * T + 0.2062 ) *
muDoubleScalarSin ( 2.0 * oqmv0ahkug ) ) + muDoubleScalarSin ( ( ( dk2rjxlhn5
- g5zew52spt ) + oqmv0ahkug ) * 2.0 ) * ( - 1.3187 - 0.00016 * T ) ) + ( -
0.2274 - 2.0E-5 * T ) * muDoubleScalarSin ( ( dk2rjxlhn5 + oqmv0ahkug ) * 2.0
) ) * 4.84813681109536E-6 ; T = ( ( muDoubleScalarCos ( ( ( dk2rjxlhn5 -
g5zew52spt ) + oqmv0ahkug ) * 2.0 ) * ( 0.5736 - 0.00031 * T ) + ( 0.00089 *
T + 9.2025 ) * muDoubleScalarCos ( oqmv0ahkug ) ) + ( 0.0977 - 5.0E-5 * T ) *
muDoubleScalarCos ( ( dk2rjxlhn5 + oqmv0ahkug ) * 2.0 ) ) *
4.84813681109536E-6 ; m5crkrq425_idx_0 = - sp - T ; g5zew52spt =
muDoubleScalarCos ( m5crkrq425_idx_0 ) ; oqmv0ahkug = muDoubleScalarSin (
m5crkrq425_idx_0 ) ; dk2rjxlhn5 = muDoubleScalarCos ( - c_sp ) ; absxk =
muDoubleScalarSin ( - c_sp ) ; ono5ii4s3b_idx_0 = muDoubleScalarCos ( sp ) ;
ono5ii4s3b_idx_1 = muDoubleScalarSin ( sp ) ; m5crkrq425_idx_0 =
ono5ii4s3b_idx_2 / 43200.0 * 3.1415926535897931 + muDoubleScalarCos ( sp + T
) * c_sp ; ono5ii4s3b_idx_2 = muDoubleScalarCos ( m5crkrq425_idx_0 ) ; sp =
muDoubleScalarSin ( m5crkrq425_idx_0 ) ; T = ( jkvgcfu3cx - 2.451545E+6 ) /
36525.0 ; m5crkrq425_idx_0 = T * T ; T3 = m5crkrq425_idx_0 * T ; c_sp = ( (
2306.2181 * T + 0.30188 * m5crkrq425_idx_0 ) + 0.017998 * T3 ) *
4.84813681109536E-6 ; b_sp = ( ( 2004.3109 * T - 0.42665 * m5crkrq425_idx_0 )
- 0.041833 * T3 ) * 4.84813681109536E-6 ; m5crkrq425_idx_0 = ( ( 2306.2181 *
T + 1.09468 * m5crkrq425_idx_0 ) + 0.018203 * T3 ) * 4.84813681109536E-6 ; T
= muDoubleScalarCos ( - 1.5707963267948966 - m5crkrq425_idx_0 ) ;
m5crkrq425_idx_0 = muDoubleScalarSin ( - 1.5707963267948966 -
m5crkrq425_idx_0 ) ; T3 = muDoubleScalarCos ( b_sp ) ; b_sp =
muDoubleScalarSin ( b_sp ) ; c_cp = muDoubleScalarCos ( 1.5707963267948966 -
c_sp ) ; c_sp = muDoubleScalarSin ( 1.5707963267948966 - c_sp ) ; h1gu4wqhux
[ 1 ] = 0.0 ; h1gu4wqhux [ 4 ] = g5zew52spt ; h1gu4wqhux [ 7 ] = oqmv0ahkug ;
h1gu4wqhux [ 2 ] = 0.0 ; h1gu4wqhux [ 5 ] = - oqmv0ahkug ; h1gu4wqhux [ 8 ] =
g5zew52spt ; eozueattnw [ 0 ] = dk2rjxlhn5 ; eozueattnw [ 3 ] = absxk ;
eozueattnw [ 6 ] = 0.0 ; eozueattnw [ 1 ] = - absxk ; eozueattnw [ 4 ] =
dk2rjxlhn5 ; eozueattnw [ 7 ] = 0.0 ; h1gu4wqhux [ 0 ] = 1.0 ; eozueattnw [ 2
] = 0.0 ; h1gu4wqhux [ 3 ] = 0.0 ; eozueattnw [ 5 ] = 0.0 ; h1gu4wqhux [ 6 ]
= 0.0 ; eozueattnw [ 8 ] = 1.0 ; b_p [ 1 ] = 0.0 ; b_p [ 4 ] =
ono5ii4s3b_idx_0 ; b_p [ 7 ] = ono5ii4s3b_idx_1 ; b_p [ 2 ] = 0.0 ; b_p [ 5 ]
= - ono5ii4s3b_idx_1 ; b_p [ 8 ] = ono5ii4s3b_idx_0 ; T_p [ 0 ] = T ; T_p [ 3
] = m5crkrq425_idx_0 ; T_p [ 6 ] = 0.0 ; T_p [ 1 ] = - m5crkrq425_idx_0 ; T_p
[ 4 ] = T ; T_p [ 7 ] = 0.0 ; for ( i = 0 ; i < 3 ; i ++ ) { for ( kmx = 0 ;
kmx < 3 ; kmx ++ ) { b [ i + 3 * kmx ] = 0.0 ; b [ i + 3 * kmx ] +=
eozueattnw [ 3 * kmx ] * h1gu4wqhux [ i ] ; b [ i + 3 * kmx ] += eozueattnw [
3 * kmx + 1 ] * h1gu4wqhux [ i + 3 ] ; b [ i + 3 * kmx ] += eozueattnw [ 3 *
kmx + 2 ] * h1gu4wqhux [ i + 6 ] ; } b_p [ 3 * i ] = b_e [ i ] ; T_p [ 3 * i
+ 2 ] = b_i [ i ] ; c [ 3 * i ] = b_e [ i ] ; } c [ 1 ] = 0.0 ; c [ 4 ] = T3
; c [ 7 ] = b_sp ; c [ 2 ] = 0.0 ; c [ 5 ] = - b_sp ; c [ 8 ] = T3 ; c_cp_p [
0 ] = c_cp ; c_cp_p [ 3 ] = c_sp ; c_cp_p [ 6 ] = 0.0 ; c_cp_p [ 1 ] = - c_sp
; c_cp_p [ 4 ] = c_cp ; c_cp_p [ 7 ] = 0.0 ; for ( i = 0 ; i < 3 ; i ++ ) {
c_cp_p [ 3 * i + 2 ] = b_i [ i ] ; for ( kmx = 0 ; kmx < 3 ; kmx ++ ) {
eozueattnw [ i + 3 * kmx ] = 0.0 ; h1gu4wqhux [ i + 3 * kmx ] = 0.0 ;
eozueattnw [ i + 3 * kmx ] += c [ 3 * kmx ] * T_p [ i ] ; h1gu4wqhux [ i + 3
* kmx ] += b_p [ 3 * kmx ] * b [ i ] ; eozueattnw [ i + 3 * kmx ] += c [ 3 *
kmx + 1 ] * T_p [ i + 3 ] ; h1gu4wqhux [ i + 3 * kmx ] += b_p [ 3 * kmx + 1 ]
* b [ i + 3 ] ; eozueattnw [ i + 3 * kmx ] += c [ 3 * kmx + 2 ] * T_p [ i + 6
] ; h1gu4wqhux [ i + 3 * kmx ] += b_p [ 3 * kmx + 2 ] * b [ i + 6 ] ; } } b_p
[ 0 ] = ono5ii4s3b_idx_2 ; b_p [ 3 ] = sp ; b_p [ 6 ] = 0.0 ; b_p [ 1 ] = -
sp ; b_p [ 4 ] = ono5ii4s3b_idx_2 ; b_p [ 7 ] = 0.0 ; for ( i = 0 ; i < 3 ; i
++ ) { for ( kmx = 0 ; kmx < 3 ; kmx ++ ) { T_p [ i + 3 * kmx ] = 0.0 ; T_p [
i + 3 * kmx ] += c_cp_p [ 3 * kmx ] * eozueattnw [ i ] ; T_p [ i + 3 * kmx ]
+= c_cp_p [ 3 * kmx + 1 ] * eozueattnw [ i + 3 ] ; T_p [ i + 3 * kmx ] +=
c_cp_p [ 3 * kmx + 2 ] * eozueattnw [ i + 6 ] ; } b_p [ 3 * i + 2 ] = b_i [ i
] ; } for ( i = 0 ; i < 3 ; i ++ ) { for ( kmx = 0 ; kmx < 3 ; kmx ++ ) { b [
kmx + 3 * i ] = 0.0 ; b [ kmx + 3 * i ] += T_p [ 3 * i ] * h1gu4wqhux [ kmx ]
; b [ kmx + 3 * i ] += T_p [ 3 * i + 1 ] * h1gu4wqhux [ kmx + 3 ] ; b [ kmx +
3 * i ] += T_p [ 3 * i + 2 ] * h1gu4wqhux [ kmx + 6 ] ; } for ( kmx = 0 ; kmx
< 3 ; kmx ++ ) { afmdwca1nj [ kmx + 3 * i ] = 0.0 ; afmdwca1nj [ kmx + 3 * i
] += b [ 3 * i ] * b_p [ kmx ] ; afmdwca1nj [ kmx + 3 * i ] += b [ 3 * i + 1
] * b_p [ kmx + 3 ] ; afmdwca1nj [ kmx + 3 * i ] += b [ 3 * i + 2 ] * b_p [
kmx + 6 ] ; } } ivx0j3mj3l ( afmdwca1nj , hqbmtiz1ck , & rtB . ls5qu2j3gs ) ;
ono5ii4s3b_idx_0 = rtP . km2m_Gain * rtB . ls5qu2j3gs . poahfmj3s1 [ 0 ] ;
ono5ii4s3b_idx_1 = rtP . km2m_Gain * rtB . ls5qu2j3gs . poahfmj3s1 [ 1 ] ;
ono5ii4s3b_idx_2 = rtP . km2m_Gain * rtB . ls5qu2j3gs . poahfmj3s1 [ 2 ] ;
absxk = muDoubleScalarAtan2 ( ono5ii4s3b_idx_2 , muDoubleScalarSqrt (
ono5ii4s3b_idx_0 * ono5ii4s3b_idx_0 + ono5ii4s3b_idx_1 * ono5ii4s3b_idx_1 ) *
0.99664718933525254 ) ; m5crkrq425_idx_0 = muDoubleScalarAtan2 (
42841.311513313573 * muDoubleScalarSin ( absxk ) * muDoubleScalarSin ( absxk
) * muDoubleScalarSin ( absxk ) + ono5ii4s3b_idx_2 , muDoubleScalarSqrt (
ono5ii4s3b_idx_0 * ono5ii4s3b_idx_0 + ono5ii4s3b_idx_1 * ono5ii4s3b_idx_1 ) -
42697.672707179969 * muDoubleScalarCos ( absxk ) * muDoubleScalarCos ( absxk
) * muDoubleScalarCos ( absxk ) ) ; T = muDoubleScalarAtan2 (
0.99664718933525254 * muDoubleScalarSin ( m5crkrq425_idx_0 ) ,
muDoubleScalarCos ( m5crkrq425_idx_0 ) ) ; kmx = 0 ; while ( ( absxk != T )
&& ( kmx < 5 ) ) { absxk = T ; m5crkrq425_idx_0 = muDoubleScalarAtan2 (
42841.311513313573 * muDoubleScalarSin ( T ) * muDoubleScalarSin ( T ) *
muDoubleScalarSin ( T ) + ono5ii4s3b_idx_2 , muDoubleScalarSqrt (
ono5ii4s3b_idx_0 * ono5ii4s3b_idx_0 + ono5ii4s3b_idx_1 * ono5ii4s3b_idx_1 ) -
42697.672707179969 * muDoubleScalarCos ( T ) * muDoubleScalarCos ( T ) *
muDoubleScalarCos ( T ) ) ; T = muDoubleScalarAtan2 ( 0.99664718933525254 *
muDoubleScalarSin ( m5crkrq425_idx_0 ) , muDoubleScalarCos ( m5crkrq425_idx_0
) ) ; kmx ++ ; } T = muDoubleScalarAbs ( m5crkrq425_idx_0 ) ; g5zew52spt =
m5crkrq425_idx_0 ; oqmv0ahkug = muDoubleScalarAtan2 ( ono5ii4s3b_idx_1 ,
ono5ii4s3b_idx_0 ) ; if ( T > 3.1415926535897931 ) { g5zew52spt =
muDoubleScalarMod ( m5crkrq425_idx_0 + 3.1415926535897931 ,
6.2831853071795862 ) - 3.1415926535897931 ; T = muDoubleScalarAbs (
g5zew52spt ) ; } if ( T > 1.5707963267948966 ) { oqmv0ahkug =
muDoubleScalarAtan2 ( ono5ii4s3b_idx_1 , ono5ii4s3b_idx_0 ) +
3.1415926535897931 ; g5zew52spt = ( 1.5707963267948966 - ( T -
1.5707963267948966 ) ) * muDoubleScalarSign ( g5zew52spt ) ; } if (
muDoubleScalarAbs ( oqmv0ahkug ) > 3.1415926535897931 ) { oqmv0ahkug =
muDoubleScalarRem ( oqmv0ahkug , 6.2831853071795862 ) - trunc (
muDoubleScalarRem ( oqmv0ahkug , 6.2831853071795862 ) / 3.1415926535897931 )
* 6.2831853071795862 ; } rtB . a5ald3g22i [ 0 ] = g5zew52spt * 180.0 /
3.1415926535897931 ; rtB . a5ald3g22i [ 1 ] = oqmv0ahkug * 180.0 /
3.1415926535897931 ; rtB . mpca01r2m2 = ( ( ( 6.378137E+6 /
muDoubleScalarSqrt ( 1.0 - muDoubleScalarSin ( m5crkrq425_idx_0 ) *
muDoubleScalarSin ( m5crkrq425_idx_0 ) * 0.0066943799901413165 ) *
0.0066943799901413165 * muDoubleScalarSin ( m5crkrq425_idx_0 ) +
ono5ii4s3b_idx_2 ) * muDoubleScalarSin ( m5crkrq425_idx_0 ) +
muDoubleScalarSqrt ( ono5ii4s3b_idx_0 * ono5ii4s3b_idx_0 + ono5ii4s3b_idx_1 *
ono5ii4s3b_idx_1 ) * muDoubleScalarCos ( m5crkrq425_idx_0 ) ) - 6.378137E+6 /
muDoubleScalarSqrt ( 1.0 - muDoubleScalarSin ( m5crkrq425_idx_0 ) *
muDoubleScalarSin ( m5crkrq425_idx_0 ) * 0.0066943799901413165 ) ) * rtP .
m2km_Gain ; ajln0dl4w5 ( rtB . mpca01r2m2 , rtP . earth_radius , & rtB .
dd2g34vqpy ) ; T = ( jkvgcfu3cx - 2.451545E+6 ) / 36525.0 ; absxk = ( (
481267.88088 * T + 218.31617 ) - T * T * 1.3972 ) * 0.017453292519943295 ;
oqmv0ahkug = ( 477198.86753 * T + 134.96292 ) * 0.017453292519943295 ;
ono5ii4s3b_idx_0 = ( 35999.04944 * T + 357.52543 ) * 0.017453292519943295 ;
dk2rjxlhn5 = ( 483202.01873 * T + 93.27283 ) * 0.017453292519943295 ;
g5zew52spt = ( 445267.11135 * T + 279.85027 ) * 0.017453292519943295 ;
m5crkrq425_idx_0 = ( ( ( ( ( ( ( ( ( ( ( ( ( ( absxk / 4.84813681109536E-6 +
22640.0 * muDoubleScalarSin ( oqmv0ahkug ) ) + muDoubleScalarSin ( 2.0 *
oqmv0ahkug ) * 769.0 ) - muDoubleScalarSin ( oqmv0ahkug - 2.0 * g5zew52spt )
* 4586.0 ) + muDoubleScalarSin ( 2.0 * g5zew52spt ) * 2370.0 ) - 668.0 *
muDoubleScalarSin ( ono5ii4s3b_idx_0 ) ) - muDoubleScalarSin ( 2.0 *
dk2rjxlhn5 ) * 412.0 ) - muDoubleScalarSin ( ( oqmv0ahkug - g5zew52spt ) *
2.0 ) * 212.0 ) - muDoubleScalarSin ( ( oqmv0ahkug + ono5ii4s3b_idx_0 ) - 2.0
* g5zew52spt ) * 206.0 ) + muDoubleScalarSin ( 2.0 * g5zew52spt + oqmv0ahkug
) * 192.0 ) - muDoubleScalarSin ( ono5ii4s3b_idx_0 - 2.0 * g5zew52spt ) *
165.0 ) + muDoubleScalarSin ( oqmv0ahkug - ono5ii4s3b_idx_0 ) * 148.0 ) -
125.0 * muDoubleScalarSin ( g5zew52spt ) ) - muDoubleScalarSin ( oqmv0ahkug +
ono5ii4s3b_idx_0 ) * 110.0 ) - muDoubleScalarSin ( ( dk2rjxlhn5 - g5zew52spt
) * 2.0 ) * 55.0 ) * 4.84813681109536E-6 ; absxk = ( ( ( ( ( ( (
muDoubleScalarSin ( ( muDoubleScalarSin ( 2.0 * dk2rjxlhn5 ) * 412.0 + 541.0
* muDoubleScalarSin ( oqmv0ahkug ) ) * 4.84813681109536E-6 + ( ( dk2rjxlhn5 +
m5crkrq425_idx_0 ) - absxk ) ) * 18520.0 - muDoubleScalarSin ( dk2rjxlhn5 -
2.0 * g5zew52spt ) * 526.0 ) + muDoubleScalarSin ( ( oqmv0ahkug + dk2rjxlhn5
) - 2.0 * g5zew52spt ) * 44.0 ) - muDoubleScalarSin ( ( - oqmv0ahkug +
dk2rjxlhn5 ) - 2.0 * g5zew52spt ) * 31.0 ) - muDoubleScalarSin ( - 2.0 *
oqmv0ahkug + dk2rjxlhn5 ) * 25.0 ) - muDoubleScalarSin ( ( ono5ii4s3b_idx_0 +
dk2rjxlhn5 ) - 2.0 * g5zew52spt ) * 23.0 ) + muDoubleScalarSin ( - oqmv0ahkug
+ dk2rjxlhn5 ) * 21.0 ) + muDoubleScalarSin ( ( - ono5ii4s3b_idx_0 +
dk2rjxlhn5 ) - 2.0 * g5zew52spt ) * 11.0 ) * 4.84813681109536E-6 ; dk2rjxlhn5
= ( ( ( ( ( ( ( 385000.0 - 20905.0 * muDoubleScalarCos ( oqmv0ahkug ) ) -
muDoubleScalarCos ( 2.0 * g5zew52spt - oqmv0ahkug ) * 3699.0 ) -
muDoubleScalarCos ( 2.0 * g5zew52spt ) * 2956.0 ) - muDoubleScalarCos ( 2.0 *
oqmv0ahkug ) * 570.0 ) + muDoubleScalarCos ( ( oqmv0ahkug - g5zew52spt ) *
2.0 ) * 246.0 ) - muDoubleScalarCos ( ono5ii4s3b_idx_0 - 2.0 * g5zew52spt ) *
205.0 ) - muDoubleScalarCos ( 2.0 * g5zew52spt + oqmv0ahkug ) * 171.0 ) -
muDoubleScalarCos ( ( oqmv0ahkug + ono5ii4s3b_idx_0 ) - 2.0 * g5zew52spt ) *
152.0 ; T = muDoubleScalarSin ( m5crkrq425_idx_0 ) ; g5zew52spt =
muDoubleScalarCos ( absxk ) ; oqmv0ahkug = muDoubleScalarSin ( absxk ) ;
ono5ii4s3b_idx_0 = dk2rjxlhn5 * muDoubleScalarCos ( m5crkrq425_idx_0 ) *
g5zew52spt - hqbmtiz1ck [ 0 ] ; ono5ii4s3b_idx_1 = ( 0.91748206207689575 * T
* g5zew52spt - 0.39777715591412138 * oqmv0ahkug ) * dk2rjxlhn5 - hqbmtiz1ck [
1 ] ; ono5ii4s3b_idx_2 = ( 0.39777715591412138 * T * g5zew52spt +
0.91748206207689575 * oqmv0ahkug ) * dk2rjxlhn5 - hqbmtiz1ck [ 2 ] ;
dk2rjxlhn5 = ( ono5ii4s3b_idx_0 * ono5ii4s3b_idx_0 + ono5ii4s3b_idx_1 *
ono5ii4s3b_idx_1 ) + ono5ii4s3b_idx_2 * ono5ii4s3b_idx_2 ; if ( dk2rjxlhn5 <
0.0 ) { dk2rjxlhn5 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( dk2rjxlhn5 )
) ; } else { dk2rjxlhn5 = muDoubleScalarSqrt ( dk2rjxlhn5 ) ; } if (
dk2rjxlhn5 > rtP . NormalizeVector_maxzero_jad2sd3ugf ) { m5crkrq425_idx_0 =
dk2rjxlhn5 ; } else { ono5ii4s3b_idx_0 *= 0.0 ; ono5ii4s3b_idx_1 *= 0.0 ;
ono5ii4s3b_idx_2 *= 0.0 ; m5crkrq425_idx_0 = rtP . Constant_Value_kg1gkk2nel
; } ono5ii4s3b_idx_0 /= m5crkrq425_idx_0 ; ono5ii4s3b_idx_1 /=
m5crkrq425_idx_0 ; ono5ii4s3b_idx_2 /= m5crkrq425_idx_0 ; g5zew52spt =
muDoubleScalarSqrt ( ( ( delta * delta + ovpn3bsi5w * ovpn3bsi5w ) +
hakul2mmal_idx_1 * hakul2mmal_idx_1 ) + M * M ) ; dk2rjxlhn5 =
hakul2mmal_idx_1 / g5zew52spt ; m5crkrq425_idx_0 = M / g5zew52spt ; T =
ovpn3bsi5w / g5zew52spt ; g5zew52spt = delta / g5zew52spt ; mjbycp0jir = ( (
( rtP . Constant_Value_ckqmocsjmk - dk2rjxlhn5 * dk2rjxlhn5 ) -
m5crkrq425_idx_0 * m5crkrq425_idx_0 ) * rtP . Gain2_Gain_bprrd5rgzt *
ono5ii4s3b_idx_0 + ( T * dk2rjxlhn5 + g5zew52spt * m5crkrq425_idx_0 ) * rtP .
Gain_Gain_p0g5ioz0tt * ono5ii4s3b_idx_1 ) + ( T * m5crkrq425_idx_0 -
g5zew52spt * dk2rjxlhn5 ) * rtP . Gain1_Gain_l1syl1i1nc * ono5ii4s3b_idx_2 ;
gvlvah3pa0 = ( ( ( rtP . Constant_Value_jdq04jy3wj - T * T ) -
m5crkrq425_idx_0 * m5crkrq425_idx_0 ) * rtP . Gain2_Gain_inxlw0u2vd *
ono5ii4s3b_idx_1 + ( T * dk2rjxlhn5 - g5zew52spt * m5crkrq425_idx_0 ) * rtP .
Gain_Gain_cdekolw0kh * ono5ii4s3b_idx_0 ) + ( g5zew52spt * T + dk2rjxlhn5 *
m5crkrq425_idx_0 ) * rtP . Gain1_Gain_mbywpxkyv2 * ono5ii4s3b_idx_2 ;
a0ueoyvf4v = ( ( T * m5crkrq425_idx_0 + g5zew52spt * dk2rjxlhn5 ) * rtP .
Gain_Gain_gnbof3p2ih * ono5ii4s3b_idx_0 + ( dk2rjxlhn5 * m5crkrq425_idx_0 -
g5zew52spt * T ) * rtP . Gain1_Gain_ai10xj1huz * ono5ii4s3b_idx_1 ) + ( ( rtP
. Constant_Value_mydahigf2l - T * T ) - dk2rjxlhn5 * dk2rjxlhn5 ) * rtP .
Gain2_Gain_aryjtg3qqc * ono5ii4s3b_idx_2 ; llkwb1gopr ( rtB . ghrb02xtti ,
mjbycp0jir , gvlvah3pa0 , a0ueoyvf4v , & rtB . axrlvoalzz ) ;
ono5ii4s3b_idx_0 = ( rtB . hiok3cyxgg . osxy5zocx5 [ 0 ] * rtP .
Constant2_Value_gqzethcbdt [ 0 ] + rtB . hiok3cyxgg . osxy5zocx5 [ 1 ] * rtP
. Constant2_Value_gqzethcbdt [ 1 ] ) + rtB . hiok3cyxgg . osxy5zocx5 [ 2 ] *
rtP . Constant2_Value_gqzethcbdt [ 2 ] ; ono5ii4s3b_idx_1 = ( rtP .
Constant2_Value_gqzethcbdt [ 0 ] * rtB . fe4ousljhv . osxy5zocx5 [ 0 ] + rtP
. Constant2_Value_gqzethcbdt [ 1 ] * rtB . fe4ousljhv . osxy5zocx5 [ 1 ] ) +
rtP . Constant2_Value_gqzethcbdt [ 2 ] * rtB . fe4ousljhv . osxy5zocx5 [ 2 ]
; ono5ii4s3b_idx_2 = ( rtP . Constant2_Value_gqzethcbdt [ 0 ] * rtB .
axrlvoalzz . osxy5zocx5 [ 0 ] + rtP . Constant2_Value_gqzethcbdt [ 1 ] * rtB
. axrlvoalzz . osxy5zocx5 [ 1 ] ) + rtP . Constant2_Value_gqzethcbdt [ 2 ] *
rtB . axrlvoalzz . osxy5zocx5 [ 2 ] ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
dk2rjxlhn5 = muDoubleScalarSin ( rtP . Constant_Value_i11k1gefwq [ 0 ] / 2.0
) ; m5crkrq425_idx_0 = muDoubleScalarSin ( rtP . Constant_Value_i11k1gefwq [
1 ] / 2.0 ) ; T = muDoubleScalarSin ( rtP . Constant_Value_i11k1gefwq [ 2 ] /
2.0 ) ; rtB . bqbim0ae4p [ 0 ] = dk2rjxlhn5 * dk2rjxlhn5 ; rtB . bqbim0ae4p [
1 ] = 0.0 ; rtB . bqbim0ae4p [ 2 ] = 0.0 ; rtB . bqbim0ae4p [ 3 ] =
m5crkrq425_idx_0 * m5crkrq425_idx_0 ; rtB . bqbim0ae4p [ 4 ] = 0.0 ; rtB .
bqbim0ae4p [ 5 ] = T * T ; } rtB . asykhtld2n [ 0 ] = - hmyegtxsdh_idx_1 ;
rtB . asykhtld2n [ 1 ] = - hmyegtxsdh_idx_2 ; rtB . asykhtld2n [ 2 ] = -
hmyegtxsdh_idx_3 ; if ( ono5ii4s3b_idx_0 > 1.0 ) { ono5ii4s3b_idx_0 = 1.0 ; }
else if ( ono5ii4s3b_idx_0 < - 1.0 ) { ono5ii4s3b_idx_0 = - 1.0 ; } if (
ono5ii4s3b_idx_1 > 1.0 ) { ono5ii4s3b_idx_1 = 1.0 ; } else if (
ono5ii4s3b_idx_1 < - 1.0 ) { ono5ii4s3b_idx_1 = - 1.0 ; } if (
ono5ii4s3b_idx_2 > 1.0 ) { ono5ii4s3b_idx_2 = 1.0 ; } else if (
ono5ii4s3b_idx_2 < - 1.0 ) { ono5ii4s3b_idx_2 = - 1.0 ; } rtB . asykhtld2n [
4 ] = ( ( rtB . ff5nefkxhm != 0 ) || ( muDoubleScalarAcos ( ono5ii4s3b_idx_0
) < rtP . STT_sun_ang_limit ) || ( muDoubleScalarAcos ( ono5ii4s3b_idx_1 ) <=
rtP . STT_FOV * 1.4142135623730951 + rtB . dd2g34vqpy . a4ujzgnsun ) || (
muDoubleScalarAcos ( ono5ii4s3b_idx_2 ) < rtP . STT_moon_ang_limit ) ) ; for
( i = 0 ; i < 6 ; i ++ ) { rtB . asykhtld2n [ i + 5 ] = rtB . bqbim0ae4p [ i
] ; } rtB . asykhtld2n [ 11 ] = rtP . Constant6_Value ; { SimStruct * rts =
ssGetSFunction ( rtS , 5 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:523" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } rtB . ilq2khdcgh [ 0 ] = rtP .
TransferFcn_C [ 0 ] * rtX . i1iguten22 [ 0 ] + rtP . TransferFcn_C [ 1 ] *
rtX . i1iguten22 [ 1 ] ; rtB . ilq2khdcgh [ 1 ] = rtP .
TransferFcn1_C_dr34rukazf [ 0 ] * rtX . pkf1lgikiz [ 0 ] + rtP .
TransferFcn1_C_dr34rukazf [ 1 ] * rtX . pkf1lgikiz [ 1 ] ; rtB . ilq2khdcgh [
2 ] = rtP . TransferFcn2_C [ 0 ] * rtX . f3jtaj41sb [ 0 ] + rtP .
TransferFcn2_C [ 1 ] * rtX . f3jtaj41sb [ 1 ] ; rtB . ilq2khdcgh [ 3 ] = rtP
. Constant5_Value ; { SimStruct * rts = ssGetSFunction ( rtS , 6 ) ; { static
const char * blockSIDForSFcnLoader = "SILS_20241709:517" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 0 <= 1 ) && gbl_raccel_tid01eq ? 0 : 0 ) ; } } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . lizdm2xqna = rtDW . ldpiguzau3 ; }
n4mcthnbsb ( rtP . NSAS1_b2c , drd0rcd33w , lgn4rji20w , ebdsqxa0pr , & rtB .
ab0dpslgku ) ; absxk = rtB . lizdm2xqna + muDoubleScalarAtan2 ( rtB .
ab0dpslgku . owg3qz0vb0 [ 0 ] , rtB . ab0dpslgku . owg3qz0vb0 [ 2 ] ) ; c_sp
= muDoubleScalarTan ( absxk ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB .
laz0gn3eus = rtDW . jx2njiskco ; } b_sp = muDoubleScalarAtan2 ( rtB .
ab0dpslgku . owg3qz0vb0 [ 1 ] , rtB . ab0dpslgku . owg3qz0vb0 [ 2 ] ) + rtB .
laz0gn3eus ; dk2rjxlhn5 = muDoubleScalarTan ( b_sp ) ; c_cp = ( c_sp * c_sp +
dk2rjxlhn5 * dk2rjxlhn5 ) + rtP . Constant_Value_hmchyhprrs * rtP .
Constant_Value_hmchyhprrs ; if ( c_cp < 0.0 ) { c_cp = - muDoubleScalarSqrt (
muDoubleScalarAbs ( c_cp ) ) ; } else { c_cp = muDoubleScalarSqrt ( c_cp ) ;
} if ( c_cp > rtP . NormalizeVector_maxzero_pk2yr3b0h2 ) { ono5ii4s3b_idx_0 =
c_sp ; ono5ii4s3b_idx_1 = dk2rjxlhn5 ; ono5ii4s3b_idx_2 = rtP .
Constant_Value_hmchyhprrs ; m5crkrq425_idx_0 = c_cp ; } else {
ono5ii4s3b_idx_0 = c_sp * 0.0 ; ono5ii4s3b_idx_1 = dk2rjxlhn5 * 0.0 ;
ono5ii4s3b_idx_2 = rtP . Constant_Value_hmchyhprrs * 0.0 ; m5crkrq425_idx_0 =
rtP . Constant_Value_lxzojy1yts ; } n4mcthnbsb ( rtP . NSAS1_b2c , c2y5dtcawp
, bcyok1fmxf , lmhgznz12o , & rtB . gwin1pepam ) ; ajln0dl4w5 ( rtB .
mpca01r2m2 , rtP . earth_radius , & rtB . jhrf4npwtn ) ; ono5ii4s3b_idx_1 = (
ono5ii4s3b_idx_0 / m5crkrq425_idx_0 * rtP . Constant1_Value_abguselunm [ 0 ]
+ ono5ii4s3b_idx_1 / m5crkrq425_idx_0 * rtP . Constant1_Value_abguselunm [ 1
] ) + ono5ii4s3b_idx_2 / m5crkrq425_idx_0 * rtP . Constant1_Value_abguselunm
[ 2 ] ; ono5ii4s3b_idx_0 = ( rtB . ab0dpslgku . owg3qz0vb0 [ 0 ] * rtB .
gwin1pepam . owg3qz0vb0 [ 0 ] + rtB . ab0dpslgku . owg3qz0vb0 [ 1 ] * rtB .
gwin1pepam . owg3qz0vb0 [ 1 ] ) + rtB . ab0dpslgku . owg3qz0vb0 [ 2 ] * rtB .
gwin1pepam . owg3qz0vb0 [ 2 ] ; if ( ono5ii4s3b_idx_1 > 1.0 ) {
ono5ii4s3b_idx_1 = 1.0 ; } else if ( ono5ii4s3b_idx_1 < - 1.0 ) {
ono5ii4s3b_idx_1 = - 1.0 ; } if ( ono5ii4s3b_idx_0 > 1.0 ) { ono5ii4s3b_idx_0
= 1.0 ; } else if ( ono5ii4s3b_idx_0 < - 1.0 ) { ono5ii4s3b_idx_0 = - 1.0 ; }
hreqnea3pv = ( ( muDoubleScalarAcos ( ono5ii4s3b_idx_1 ) < rtP .
NSAS_ang_limit ) && ( muDoubleScalarAcos ( ono5ii4s3b_idx_0 ) >= rtB .
jhrf4npwtn . a4ujzgnsun ) && ( rtB . ab0dpslgku . owg3qz0vb0 [ 2 ] > rtP .
z0_const ) ) ; if ( hreqnea3pv ) { rtB . fdbl5l21n42 [ 2 ] = rtP .
rad2deg_Gain * absxk ; rtB . fdbl5l21n42 [ 3 ] = rtP . rad2deg_Gain * b_sp ;
} else { rtB . fdbl5l21n42 [ 2 ] = rtP . Constant2_Value_gegmpg2rvu [ 0 ] ;
rtB . fdbl5l21n42 [ 3 ] = rtP . Constant2_Value_gegmpg2rvu [ 1 ] ; } rtB .
fdbl5l21n42 [ 0 ] = hreqnea3pv ; rtB . fdbl5l21n42 [ 1 ] = rtP .
Constant2_Value ; { SimStruct * rts = ssGetSFunction ( rtS , 7 ) ; { static
const char * blockSIDForSFcnLoader = "SILS_20241709:519" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 0 <= 1 ) && gbl_raccel_tid01eq ? 0 : 0 ) ; } } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . ggo5omtwrw = rtDW . fg3gr5w1yf ; }
n4mcthnbsb ( rtP . NSAS2_b2c , drd0rcd33w , lgn4rji20w , ebdsqxa0pr , & rtB .
awovp5grnq ) ; c_cp = rtB . ggo5omtwrw + muDoubleScalarAtan2 ( rtB .
awovp5grnq . owg3qz0vb0 [ 0 ] , rtB . awovp5grnq . owg3qz0vb0 [ 2 ] ) ; absxk
= muDoubleScalarTan ( c_cp ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB .
gu0xyts5qt = rtDW . l0mqdwlhk0 ; } c_sp = muDoubleScalarAtan2 ( rtB .
awovp5grnq . owg3qz0vb0 [ 1 ] , rtB . awovp5grnq . owg3qz0vb0 [ 2 ] ) + rtB .
gu0xyts5qt ; b_sp = muDoubleScalarTan ( c_sp ) ; dn2nlybx4r = ( absxk * absxk
+ b_sp * b_sp ) + rtP . Constant_Value_hupkchseos * rtP .
Constant_Value_hupkchseos ; if ( dn2nlybx4r < 0.0 ) { dn2nlybx4r = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( dn2nlybx4r ) ) ; } else { dn2nlybx4r
= muDoubleScalarSqrt ( dn2nlybx4r ) ; } if ( dn2nlybx4r > rtP .
NormalizeVector_maxzero_mjhj4dvvo1 ) { ono5ii4s3b_idx_0 = absxk ;
ono5ii4s3b_idx_1 = b_sp ; ono5ii4s3b_idx_2 = rtP . Constant_Value_hupkchseos
; m5crkrq425_idx_0 = dn2nlybx4r ; } else { ono5ii4s3b_idx_0 = absxk * 0.0 ;
ono5ii4s3b_idx_1 = b_sp * 0.0 ; ono5ii4s3b_idx_2 = rtP .
Constant_Value_hupkchseos * 0.0 ; m5crkrq425_idx_0 = rtP .
Constant_Value_m2hdvkft2v ; } n4mcthnbsb ( rtP . NSAS2_b2c , c2y5dtcawp ,
bcyok1fmxf , lmhgznz12o , & rtB . n3omup2lzv ) ; ajln0dl4w5 ( rtB .
mpca01r2m2 , rtP . earth_radius , & rtB . jrtx1iz4hz ) ; ono5ii4s3b_idx_1 = (
ono5ii4s3b_idx_0 / m5crkrq425_idx_0 * rtP . Constant1_Value_ej0jppt02k [ 0 ]
+ ono5ii4s3b_idx_1 / m5crkrq425_idx_0 * rtP . Constant1_Value_ej0jppt02k [ 1
] ) + ono5ii4s3b_idx_2 / m5crkrq425_idx_0 * rtP . Constant1_Value_ej0jppt02k
[ 2 ] ; ono5ii4s3b_idx_0 = ( rtB . awovp5grnq . owg3qz0vb0 [ 0 ] * rtB .
n3omup2lzv . owg3qz0vb0 [ 0 ] + rtB . awovp5grnq . owg3qz0vb0 [ 1 ] * rtB .
n3omup2lzv . owg3qz0vb0 [ 1 ] ) + rtB . awovp5grnq . owg3qz0vb0 [ 2 ] * rtB .
n3omup2lzv . owg3qz0vb0 [ 2 ] ; if ( ono5ii4s3b_idx_1 > 1.0 ) {
ono5ii4s3b_idx_1 = 1.0 ; } else if ( ono5ii4s3b_idx_1 < - 1.0 ) {
ono5ii4s3b_idx_1 = - 1.0 ; } if ( ono5ii4s3b_idx_0 > 1.0 ) { ono5ii4s3b_idx_0
= 1.0 ; } else if ( ono5ii4s3b_idx_0 < - 1.0 ) { ono5ii4s3b_idx_0 = - 1.0 ; }
hreqnea3pv = ( ( muDoubleScalarAcos ( ono5ii4s3b_idx_1 ) < rtP .
NSAS_ang_limit ) && ( muDoubleScalarAcos ( ono5ii4s3b_idx_0 ) >= rtB .
jrtx1iz4hz . a4ujzgnsun ) && ( rtB . awovp5grnq . owg3qz0vb0 [ 2 ] > rtP .
z0_const_m1oeisvxny ) ) ; if ( hreqnea3pv ) { rtB . pktfet50kq [ 2 ] = rtP .
rad2deg_Gain_lqcbchbdpx * c_cp ; rtB . pktfet50kq [ 3 ] = rtP .
rad2deg_Gain_lqcbchbdpx * c_sp ; } else { rtB . pktfet50kq [ 2 ] = rtP .
Constant2_Value_cthnum5wwf [ 0 ] ; rtB . pktfet50kq [ 3 ] = rtP .
Constant2_Value_cthnum5wwf [ 1 ] ; } rtB . pktfet50kq [ 0 ] = hreqnea3pv ;
rtB . pktfet50kq [ 1 ] = rtP . Constant12_Value ; { SimStruct * rts =
ssGetSFunction ( rtS , 8 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:520" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
rtB . cpp1cmyksa = rtDW . b5i1u5nxk5 ; } n4mcthnbsb ( rtP . NSAS3_b2c ,
drd0rcd33w , lgn4rji20w , ebdsqxa0pr , & rtB . gzwxmb2zl2 ) ; dn2nlybx4r =
rtB . cpp1cmyksa + muDoubleScalarAtan2 ( rtB . gzwxmb2zl2 . owg3qz0vb0 [ 0 ]
, rtB . gzwxmb2zl2 . owg3qz0vb0 [ 2 ] ) ; c_cp = muDoubleScalarTan (
dn2nlybx4r ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . necosqfbva = rtDW
. ik23rulsvu ; } absxk = muDoubleScalarAtan2 ( rtB . gzwxmb2zl2 . owg3qz0vb0
[ 1 ] , rtB . gzwxmb2zl2 . owg3qz0vb0 [ 2 ] ) + rtB . necosqfbva ; c_sp =
muDoubleScalarTan ( absxk ) ; kl0gyfxice = ( c_cp * c_cp + c_sp * c_sp ) +
rtP . Constant_Value_ndyne2tsni * rtP . Constant_Value_ndyne2tsni ; if (
kl0gyfxice < 0.0 ) { kl0gyfxice = - muDoubleScalarSqrt ( muDoubleScalarAbs (
kl0gyfxice ) ) ; } else { kl0gyfxice = muDoubleScalarSqrt ( kl0gyfxice ) ; }
if ( kl0gyfxice > rtP . NormalizeVector_maxzero_hdshd0fhdt ) {
ono5ii4s3b_idx_0 = c_cp ; ono5ii4s3b_idx_1 = c_sp ; ono5ii4s3b_idx_2 = rtP .
Constant_Value_ndyne2tsni ; m5crkrq425_idx_0 = kl0gyfxice ; } else {
ono5ii4s3b_idx_0 = c_cp * 0.0 ; ono5ii4s3b_idx_1 = c_sp * 0.0 ;
ono5ii4s3b_idx_2 = rtP . Constant_Value_ndyne2tsni * 0.0 ; m5crkrq425_idx_0 =
rtP . Constant_Value_iqckjhnrkz ; } n4mcthnbsb ( rtP . NSAS3_b2c , c2y5dtcawp
, bcyok1fmxf , lmhgznz12o , & rtB . ddwcgokc4u ) ; ajln0dl4w5 ( rtB .
mpca01r2m2 , rtP . earth_radius , & rtB . d3edomwivh ) ; ono5ii4s3b_idx_1 = (
ono5ii4s3b_idx_0 / m5crkrq425_idx_0 * rtP . Constant1_Value_la1yhx1hao [ 0 ]
+ ono5ii4s3b_idx_1 / m5crkrq425_idx_0 * rtP . Constant1_Value_la1yhx1hao [ 1
] ) + ono5ii4s3b_idx_2 / m5crkrq425_idx_0 * rtP . Constant1_Value_la1yhx1hao
[ 2 ] ; ono5ii4s3b_idx_0 = ( rtB . gzwxmb2zl2 . owg3qz0vb0 [ 0 ] * rtB .
ddwcgokc4u . owg3qz0vb0 [ 0 ] + rtB . gzwxmb2zl2 . owg3qz0vb0 [ 1 ] * rtB .
ddwcgokc4u . owg3qz0vb0 [ 1 ] ) + rtB . gzwxmb2zl2 . owg3qz0vb0 [ 2 ] * rtB .
ddwcgokc4u . owg3qz0vb0 [ 2 ] ; if ( ono5ii4s3b_idx_1 > 1.0 ) {
ono5ii4s3b_idx_1 = 1.0 ; } else if ( ono5ii4s3b_idx_1 < - 1.0 ) {
ono5ii4s3b_idx_1 = - 1.0 ; } if ( ono5ii4s3b_idx_0 > 1.0 ) { ono5ii4s3b_idx_0
= 1.0 ; } else if ( ono5ii4s3b_idx_0 < - 1.0 ) { ono5ii4s3b_idx_0 = - 1.0 ; }
hreqnea3pv = ( ( muDoubleScalarAcos ( ono5ii4s3b_idx_1 ) < rtP .
NSAS_ang_limit ) && ( muDoubleScalarAcos ( ono5ii4s3b_idx_0 ) >= rtB .
d3edomwivh . a4ujzgnsun ) && ( rtB . gzwxmb2zl2 . owg3qz0vb0 [ 2 ] > rtP .
z0_const_gejhxxdnvf ) ) ; if ( hreqnea3pv ) { rtB . cyayszgojz [ 2 ] = rtP .
rad2deg_Gain_asjrxybn0x * dn2nlybx4r ; rtB . cyayszgojz [ 3 ] = rtP .
rad2deg_Gain_asjrxybn0x * absxk ; } else { rtB . cyayszgojz [ 2 ] = rtP .
Constant2_Value_gn4fk3d1lp [ 0 ] ; rtB . cyayszgojz [ 3 ] = rtP .
Constant2_Value_gn4fk3d1lp [ 1 ] ; } rtB . cyayszgojz [ 0 ] = hreqnea3pv ;
rtB . cyayszgojz [ 1 ] = rtP . Constant15_Value ; { SimStruct * rts =
ssGetSFunction ( rtS , 9 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:521" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
rtB . mo4pqo22zy = rtDW . ia3ohifukf ; } n4mcthnbsb ( rtP . NSAS4_b2c ,
drd0rcd33w , lgn4rji20w , ebdsqxa0pr , & rtB . fovozsjxj1 ) ; kl0gyfxice =
rtB . mo4pqo22zy + muDoubleScalarAtan2 ( rtB . fovozsjxj1 . owg3qz0vb0 [ 0 ]
, rtB . fovozsjxj1 . owg3qz0vb0 [ 2 ] ) ; dn2nlybx4r = muDoubleScalarTan (
kl0gyfxice ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . ooktctrg5d = rtDW
. ewzxpp1cyz ; } c_cp = muDoubleScalarAtan2 ( rtB . fovozsjxj1 . owg3qz0vb0 [
1 ] , rtB . fovozsjxj1 . owg3qz0vb0 [ 2 ] ) + rtB . ooktctrg5d ; absxk =
muDoubleScalarTan ( c_cp ) ; hmyegtxsdh_idx_2 = ( dn2nlybx4r * dn2nlybx4r +
absxk * absxk ) + rtP . Constant_Value_ghgnj1qkgx * rtP .
Constant_Value_ghgnj1qkgx ; if ( hmyegtxsdh_idx_2 < 0.0 ) { hmyegtxsdh_idx_2
= - muDoubleScalarSqrt ( muDoubleScalarAbs ( hmyegtxsdh_idx_2 ) ) ; } else {
hmyegtxsdh_idx_2 = muDoubleScalarSqrt ( hmyegtxsdh_idx_2 ) ; } if (
hmyegtxsdh_idx_2 > rtP . NormalizeVector_maxzero_ngb4rhu5uq ) {
ono5ii4s3b_idx_0 = dn2nlybx4r ; ono5ii4s3b_idx_1 = absxk ; ono5ii4s3b_idx_2 =
rtP . Constant_Value_ghgnj1qkgx ; m5crkrq425_idx_0 = hmyegtxsdh_idx_2 ; }
else { ono5ii4s3b_idx_0 = dn2nlybx4r * 0.0 ; ono5ii4s3b_idx_1 = absxk * 0.0 ;
ono5ii4s3b_idx_2 = rtP . Constant_Value_ghgnj1qkgx * 0.0 ; m5crkrq425_idx_0 =
rtP . Constant_Value_fvwnrwg2d1 ; } n4mcthnbsb ( rtP . NSAS4_b2c , c2y5dtcawp
, bcyok1fmxf , lmhgznz12o , & rtB . o05svadaty ) ; ajln0dl4w5 ( rtB .
mpca01r2m2 , rtP . earth_radius , & rtB . fxdnyd3caz ) ; ono5ii4s3b_idx_1 = (
ono5ii4s3b_idx_0 / m5crkrq425_idx_0 * rtP . Constant1_Value_j0a4ub2khm [ 0 ]
+ ono5ii4s3b_idx_1 / m5crkrq425_idx_0 * rtP . Constant1_Value_j0a4ub2khm [ 1
] ) + ono5ii4s3b_idx_2 / m5crkrq425_idx_0 * rtP . Constant1_Value_j0a4ub2khm
[ 2 ] ; ono5ii4s3b_idx_0 = ( rtB . fovozsjxj1 . owg3qz0vb0 [ 0 ] * rtB .
o05svadaty . owg3qz0vb0 [ 0 ] + rtB . fovozsjxj1 . owg3qz0vb0 [ 1 ] * rtB .
o05svadaty . owg3qz0vb0 [ 1 ] ) + rtB . fovozsjxj1 . owg3qz0vb0 [ 2 ] * rtB .
o05svadaty . owg3qz0vb0 [ 2 ] ; if ( ono5ii4s3b_idx_1 > 1.0 ) {
ono5ii4s3b_idx_1 = 1.0 ; } else if ( ono5ii4s3b_idx_1 < - 1.0 ) {
ono5ii4s3b_idx_1 = - 1.0 ; } if ( ono5ii4s3b_idx_0 > 1.0 ) { ono5ii4s3b_idx_0
= 1.0 ; } else if ( ono5ii4s3b_idx_0 < - 1.0 ) { ono5ii4s3b_idx_0 = - 1.0 ; }
hreqnea3pv = ( ( muDoubleScalarAcos ( ono5ii4s3b_idx_1 ) < rtP .
NSAS_ang_limit ) && ( muDoubleScalarAcos ( ono5ii4s3b_idx_0 ) >= rtB .
fxdnyd3caz . a4ujzgnsun ) && ( rtB . fovozsjxj1 . owg3qz0vb0 [ 2 ] > rtP .
z0_const_otzh2whnvs ) ) ; if ( hreqnea3pv ) { rtB . oucj4k4y2qy [ 2 ] = rtP .
rad2deg_Gain_okxkrd2arw * kl0gyfxice ; rtB . oucj4k4y2qy [ 3 ] = rtP .
rad2deg_Gain_okxkrd2arw * c_cp ; } else { rtB . oucj4k4y2qy [ 2 ] = rtP .
Constant2_Value_aeurx5t4ck [ 0 ] ; rtB . oucj4k4y2qy [ 3 ] = rtP .
Constant2_Value_aeurx5t4ck [ 1 ] ; } rtB . oucj4k4y2qy [ 0 ] = hreqnea3pv ;
rtB . oucj4k4y2qy [ 1 ] = rtP . Constant4_Value ; { SimStruct * rts =
ssGetSFunction ( rtS , 10 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:630" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
rtB . onbsvxszlu = rtDW . hdjjo4r4gm ; } n4mcthnbsb ( rtP . NSAS5_b2c ,
drd0rcd33w , lgn4rji20w , ebdsqxa0pr , & rtB . jacwaaufsl ) ;
hmyegtxsdh_idx_2 = rtB . onbsvxszlu + muDoubleScalarAtan2 ( rtB . jacwaaufsl
. owg3qz0vb0 [ 0 ] , rtB . jacwaaufsl . owg3qz0vb0 [ 2 ] ) ; kl0gyfxice =
muDoubleScalarTan ( hmyegtxsdh_idx_2 ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) )
{ rtB . ljv1mgpbcd = rtDW . coji3apumi ; } dn2nlybx4r = muDoubleScalarAtan2 (
rtB . jacwaaufsl . owg3qz0vb0 [ 1 ] , rtB . jacwaaufsl . owg3qz0vb0 [ 2 ] ) +
rtB . ljv1mgpbcd ; c_cp = muDoubleScalarTan ( dn2nlybx4r ) ; hmyegtxsdh_idx_3
= ( kl0gyfxice * kl0gyfxice + c_cp * c_cp ) + rtP . Constant_Value_ejbbt4py2k
* rtP . Constant_Value_ejbbt4py2k ; if ( hmyegtxsdh_idx_3 < 0.0 ) {
hmyegtxsdh_idx_3 = - muDoubleScalarSqrt ( muDoubleScalarAbs (
hmyegtxsdh_idx_3 ) ) ; } else { hmyegtxsdh_idx_3 = muDoubleScalarSqrt (
hmyegtxsdh_idx_3 ) ; } if ( hmyegtxsdh_idx_3 > rtP .
NormalizeVector_maxzero_lt2ddtxhuf ) { ono5ii4s3b_idx_0 = kl0gyfxice ;
ono5ii4s3b_idx_1 = c_cp ; ono5ii4s3b_idx_2 = rtP . Constant_Value_ejbbt4py2k
; m5crkrq425_idx_0 = hmyegtxsdh_idx_3 ; } else { ono5ii4s3b_idx_0 =
kl0gyfxice * 0.0 ; ono5ii4s3b_idx_1 = c_cp * 0.0 ; ono5ii4s3b_idx_2 = rtP .
Constant_Value_ejbbt4py2k * 0.0 ; m5crkrq425_idx_0 = rtP .
Constant_Value_fnhawrwcfw ; } n4mcthnbsb ( rtP . NSAS5_b2c , c2y5dtcawp ,
bcyok1fmxf , lmhgznz12o , & rtB . jw1hn4rp4t ) ; ajln0dl4w5 ( rtB .
mpca01r2m2 , rtP . earth_radius , & rtB . puqqfcdyyx ) ; ono5ii4s3b_idx_1 = (
ono5ii4s3b_idx_0 / m5crkrq425_idx_0 * rtP . Constant1_Value_g3xactptzz [ 0 ]
+ ono5ii4s3b_idx_1 / m5crkrq425_idx_0 * rtP . Constant1_Value_g3xactptzz [ 1
] ) + ono5ii4s3b_idx_2 / m5crkrq425_idx_0 * rtP . Constant1_Value_g3xactptzz
[ 2 ] ; ono5ii4s3b_idx_0 = ( rtB . jacwaaufsl . owg3qz0vb0 [ 0 ] * rtB .
jw1hn4rp4t . owg3qz0vb0 [ 0 ] + rtB . jacwaaufsl . owg3qz0vb0 [ 1 ] * rtB .
jw1hn4rp4t . owg3qz0vb0 [ 1 ] ) + rtB . jacwaaufsl . owg3qz0vb0 [ 2 ] * rtB .
jw1hn4rp4t . owg3qz0vb0 [ 2 ] ; if ( ono5ii4s3b_idx_1 > 1.0 ) {
ono5ii4s3b_idx_1 = 1.0 ; } else if ( ono5ii4s3b_idx_1 < - 1.0 ) {
ono5ii4s3b_idx_1 = - 1.0 ; } if ( ono5ii4s3b_idx_0 > 1.0 ) { ono5ii4s3b_idx_0
= 1.0 ; } else if ( ono5ii4s3b_idx_0 < - 1.0 ) { ono5ii4s3b_idx_0 = - 1.0 ; }
hreqnea3pv = ( ( muDoubleScalarAcos ( ono5ii4s3b_idx_1 ) < rtP .
NSAS_ang_limit ) && ( muDoubleScalarAcos ( ono5ii4s3b_idx_0 ) >= rtB .
puqqfcdyyx . a4ujzgnsun ) && ( rtB . jacwaaufsl . owg3qz0vb0 [ 2 ] > rtP .
z0_const_h3tpk4wmcz ) ) ; if ( hreqnea3pv ) { rtB . ktlu1ekw1mg [ 2 ] = rtP .
rad2deg_Gain_cmtkrwe5gj * hmyegtxsdh_idx_2 ; rtB . ktlu1ekw1mg [ 3 ] = rtP .
rad2deg_Gain_cmtkrwe5gj * dn2nlybx4r ; } else { rtB . ktlu1ekw1mg [ 2 ] = rtP
. Constant2_Value_kj0dkshoay [ 0 ] ; rtB . ktlu1ekw1mg [ 3 ] = rtP .
Constant2_Value_kj0dkshoay [ 1 ] ; } rtB . ktlu1ekw1mg [ 0 ] = hreqnea3pv ;
rtB . ktlu1ekw1mg [ 1 ] = rtP . Constant1_Value ; { SimStruct * rts =
ssGetSFunction ( rtS , 11 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:631" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
rtB . lfncg5pvng = rtDW . m2ylj5cu2h ; } n4mcthnbsb ( rtP . NSAS6_b2c ,
drd0rcd33w , lgn4rji20w , ebdsqxa0pr , & rtB . ajpyzlqqkx ) ;
hmyegtxsdh_idx_3 = rtB . lfncg5pvng + muDoubleScalarAtan2 ( rtB . ajpyzlqqkx
. owg3qz0vb0 [ 0 ] , rtB . ajpyzlqqkx . owg3qz0vb0 [ 2 ] ) ; hmyegtxsdh_idx_2
= muDoubleScalarTan ( hmyegtxsdh_idx_3 ) ; if ( ssIsSampleHit ( rtS , 1 , 0 )
) { rtB . kfpd0jse5u = rtDW . dbnkttelok ; } kl0gyfxice = muDoubleScalarAtan2
( rtB . ajpyzlqqkx . owg3qz0vb0 [ 1 ] , rtB . ajpyzlqqkx . owg3qz0vb0 [ 2 ] )
+ rtB . kfpd0jse5u ; dn2nlybx4r = muDoubleScalarTan ( kl0gyfxice ) ;
m5crkrq425_idx_0 = ( hmyegtxsdh_idx_2 * hmyegtxsdh_idx_2 + dn2nlybx4r *
dn2nlybx4r ) + rtP . Constant_Value_iba131uo1r * rtP .
Constant_Value_iba131uo1r ; if ( m5crkrq425_idx_0 < 0.0 ) { m5crkrq425_idx_0
= - muDoubleScalarSqrt ( muDoubleScalarAbs ( m5crkrq425_idx_0 ) ) ; } else {
m5crkrq425_idx_0 = muDoubleScalarSqrt ( m5crkrq425_idx_0 ) ; } if (
m5crkrq425_idx_0 > rtP . NormalizeVector_maxzero_bj3cfn3har ) {
ono5ii4s3b_idx_0 = hmyegtxsdh_idx_2 ; ono5ii4s3b_idx_1 = dn2nlybx4r ;
ono5ii4s3b_idx_2 = rtP . Constant_Value_iba131uo1r ; } else {
ono5ii4s3b_idx_0 = hmyegtxsdh_idx_2 * 0.0 ; ono5ii4s3b_idx_1 = dn2nlybx4r *
0.0 ; ono5ii4s3b_idx_2 = rtP . Constant_Value_iba131uo1r * 0.0 ;
m5crkrq425_idx_0 = rtP . Constant_Value_k3ehwbv3db ; } n4mcthnbsb ( rtP .
NSAS6_b2c , c2y5dtcawp , bcyok1fmxf , lmhgznz12o , & rtB . eosebepeyc ) ;
ajln0dl4w5 ( rtB . mpca01r2m2 , rtP . earth_radius , & rtB . odjpekassu ) ;
ono5ii4s3b_idx_1 = ( ono5ii4s3b_idx_0 / m5crkrq425_idx_0 * rtP .
Constant1_Value_nc5rt4jowx [ 0 ] + ono5ii4s3b_idx_1 / m5crkrq425_idx_0 * rtP
. Constant1_Value_nc5rt4jowx [ 1 ] ) + ono5ii4s3b_idx_2 / m5crkrq425_idx_0 *
rtP . Constant1_Value_nc5rt4jowx [ 2 ] ; ono5ii4s3b_idx_0 = ( rtB .
ajpyzlqqkx . owg3qz0vb0 [ 0 ] * rtB . eosebepeyc . owg3qz0vb0 [ 0 ] + rtB .
ajpyzlqqkx . owg3qz0vb0 [ 1 ] * rtB . eosebepeyc . owg3qz0vb0 [ 1 ] ) + rtB .
ajpyzlqqkx . owg3qz0vb0 [ 2 ] * rtB . eosebepeyc . owg3qz0vb0 [ 2 ] ; if (
ono5ii4s3b_idx_1 > 1.0 ) { ono5ii4s3b_idx_1 = 1.0 ; } else if (
ono5ii4s3b_idx_1 < - 1.0 ) { ono5ii4s3b_idx_1 = - 1.0 ; } if (
ono5ii4s3b_idx_0 > 1.0 ) { ono5ii4s3b_idx_0 = 1.0 ; } else if (
ono5ii4s3b_idx_0 < - 1.0 ) { ono5ii4s3b_idx_0 = - 1.0 ; } hreqnea3pv = ( (
muDoubleScalarAcos ( ono5ii4s3b_idx_1 ) < rtP . NSAS_ang_limit ) && (
muDoubleScalarAcos ( ono5ii4s3b_idx_0 ) >= rtB . odjpekassu . a4ujzgnsun ) &&
( rtB . ajpyzlqqkx . owg3qz0vb0 [ 2 ] > rtP . z0_const_pdn2lzrjdp ) ) ; if (
hreqnea3pv ) { rtB . innw5sywzgy [ 2 ] = rtP . rad2deg_Gain_ncnor3j1vi *
hmyegtxsdh_idx_3 ; rtB . innw5sywzgy [ 3 ] = rtP . rad2deg_Gain_ncnor3j1vi *
kl0gyfxice ; } else { rtB . innw5sywzgy [ 2 ] = rtP .
Constant2_Value_nqgiw5gjgz [ 0 ] ; rtB . innw5sywzgy [ 3 ] = rtP .
Constant2_Value_nqgiw5gjgz [ 1 ] ; } rtB . innw5sywzgy [ 0 ] = hreqnea3pv ;
rtB . innw5sywzgy [ 1 ] = rtP . Constant3_Value ; { SimStruct * rts =
ssGetSFunction ( rtS , 12 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:632" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
rtB . hcpvpoawqx [ 0 ] = rtDW . fzlqp4iexm [ 0 ] ; rtB . hcpvpoawqx [ 1 ] =
rtDW . fzlqp4iexm [ 1 ] ; rtB . hcpvpoawqx [ 2 ] = rtDW . fzlqp4iexm [ 2 ] ;
} rtB . jihpm3q5gs [ 0 ] = ( rtP . TransferFcn_C_ciybxys4sn * rtX .
ae0okdyidm + rtB . hcpvpoawqx [ 0 ] ) + rtP . GAS_Vref ; rtB . jihpm3q5gs [ 1
] = ( rtP . TransferFcn1_C_b2uz52ggce * rtX . cok521zc4f + rtB . hcpvpoawqx [
1 ] ) + rtP . GAS_Vref ; rtB . jihpm3q5gs [ 2 ] = ( rtP .
TransferFcn2_C_f5zsdduuzq * rtX . pf4hzftljn + rtB . hcpvpoawqx [ 2 ] ) + rtP
. GAS_Vref ; rtB . jihpm3q5gs [ 3 ] = rtP . GAS_Vref ; { SimStruct * rts =
ssGetSFunction ( rtS , 13 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:518" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
rtB . gs0kzoznkl [ 0 ] = rtDW . hsxmncoiha [ 0 ] ; rtB . gs0kzoznkl [ 1 ] =
rtDW . hsxmncoiha [ 1 ] ; rtB . gs0kzoznkl [ 2 ] = rtDW . hsxmncoiha [ 2 ] ;
} ono5ii4s3b_idx_0 = rtP . km2m_Gain_c3udq35tim * rtB . ls5qu2j3gs .
poahfmj3s1 [ 0 ] + rtB . gs0kzoznkl [ 0 ] ; ono5ii4s3b_idx_1 = rtP .
km2m_Gain_c3udq35tim * rtB . ls5qu2j3gs . poahfmj3s1 [ 1 ] + rtB . gs0kzoznkl
[ 1 ] ; ono5ii4s3b_idx_2 = rtP . km2m_Gain_c3udq35tim * rtB . ls5qu2j3gs .
poahfmj3s1 [ 2 ] + rtB . gs0kzoznkl [ 2 ] ; absxk = muDoubleScalarAtan2 (
ono5ii4s3b_idx_2 , muDoubleScalarSqrt ( ono5ii4s3b_idx_0 * ono5ii4s3b_idx_0 +
ono5ii4s3b_idx_1 * ono5ii4s3b_idx_1 ) * 0.99664718933525254 ) ;
m5crkrq425_idx_0 = muDoubleScalarAtan2 ( 42841.311513313573 *
muDoubleScalarSin ( absxk ) * muDoubleScalarSin ( absxk ) * muDoubleScalarSin
( absxk ) + ono5ii4s3b_idx_2 , muDoubleScalarSqrt ( ono5ii4s3b_idx_0 *
ono5ii4s3b_idx_0 + ono5ii4s3b_idx_1 * ono5ii4s3b_idx_1 ) - 42697.672707179969
* muDoubleScalarCos ( absxk ) * muDoubleScalarCos ( absxk ) *
muDoubleScalarCos ( absxk ) ) ; T = muDoubleScalarAtan2 ( 0.99664718933525254
* muDoubleScalarSin ( m5crkrq425_idx_0 ) , muDoubleScalarCos (
m5crkrq425_idx_0 ) ) ; kmx = 0 ; while ( ( absxk != T ) && ( kmx < 5 ) ) {
absxk = T ; m5crkrq425_idx_0 = muDoubleScalarAtan2 ( 42841.311513313573 *
muDoubleScalarSin ( T ) * muDoubleScalarSin ( T ) * muDoubleScalarSin ( T ) +
ono5ii4s3b_idx_2 , muDoubleScalarSqrt ( ono5ii4s3b_idx_0 * ono5ii4s3b_idx_0 +
ono5ii4s3b_idx_1 * ono5ii4s3b_idx_1 ) - 42697.672707179969 *
muDoubleScalarCos ( T ) * muDoubleScalarCos ( T ) * muDoubleScalarCos ( T ) )
; T = muDoubleScalarAtan2 ( 0.99664718933525254 * muDoubleScalarSin (
m5crkrq425_idx_0 ) , muDoubleScalarCos ( m5crkrq425_idx_0 ) ) ; kmx ++ ; } T
= muDoubleScalarAbs ( m5crkrq425_idx_0 ) ; g5zew52spt = m5crkrq425_idx_0 ;
oqmv0ahkug = muDoubleScalarAtan2 ( ono5ii4s3b_idx_1 , ono5ii4s3b_idx_0 ) ; if
( T > 3.1415926535897931 ) { g5zew52spt = muDoubleScalarMod (
m5crkrq425_idx_0 + 3.1415926535897931 , 6.2831853071795862 ) -
3.1415926535897931 ; T = muDoubleScalarAbs ( g5zew52spt ) ; } if ( T >
1.5707963267948966 ) { oqmv0ahkug = muDoubleScalarAtan2 ( ono5ii4s3b_idx_1 ,
ono5ii4s3b_idx_0 ) + 3.1415926535897931 ; g5zew52spt = ( 1.5707963267948966 -
( T - 1.5707963267948966 ) ) * muDoubleScalarSign ( g5zew52spt ) ; } if (
muDoubleScalarAbs ( oqmv0ahkug ) > 3.1415926535897931 ) { oqmv0ahkug =
muDoubleScalarRem ( oqmv0ahkug , 6.2831853071795862 ) - trunc (
muDoubleScalarRem ( oqmv0ahkug , 6.2831853071795862 ) / 3.1415926535897931 )
* 6.2831853071795862 ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB .
jkg4capamp = rtDW . bpg2iofpcz ; } n4kwubetr3 = jkvgcfu3cx + rtB . jkg4capamp
; bjzuls4oiv ( n4kwubetr3 , & rtB . g5opol5dur ) ; rtB . cbjdhhra0o [ 0 ] =
g5zew52spt * 180.0 / 3.1415926535897931 ; rtB . cbjdhhra0o [ 1 ] = oqmv0ahkug
* 180.0 / 3.1415926535897931 ; rtB . cbjdhhra0o [ 2 ] = ( ( 6.378137E+6 /
muDoubleScalarSqrt ( 1.0 - muDoubleScalarSin ( m5crkrq425_idx_0 ) *
muDoubleScalarSin ( m5crkrq425_idx_0 ) * 0.0066943799901413165 ) *
0.0066943799901413165 * muDoubleScalarSin ( m5crkrq425_idx_0 ) +
ono5ii4s3b_idx_2 ) * muDoubleScalarSin ( m5crkrq425_idx_0 ) +
muDoubleScalarSqrt ( ono5ii4s3b_idx_0 * ono5ii4s3b_idx_0 + ono5ii4s3b_idx_1 *
ono5ii4s3b_idx_1 ) * muDoubleScalarCos ( m5crkrq425_idx_0 ) ) - 6.378137E+6 /
muDoubleScalarSqrt ( 1.0 - muDoubleScalarSin ( m5crkrq425_idx_0 ) *
muDoubleScalarSin ( m5crkrq425_idx_0 ) * 0.0066943799901413165 ) ; rtB .
cbjdhhra0o [ 3 ] = ono5ii4s3b_idx_0 ; rtB . cbjdhhra0o [ 4 ] =
ono5ii4s3b_idx_1 ; rtB . cbjdhhra0o [ 5 ] = ono5ii4s3b_idx_2 ; rtB .
cbjdhhra0o [ 6 ] = rtB . g5opol5dur . crs3vbajbr ; rtB . cbjdhhra0o [ 7 ] =
rtB . g5opol5dur . pyqwe5rsse ; rtB . cbjdhhra0o [ 8 ] = rtB . g5opol5dur .
agveekqpqv ; rtB . cbjdhhra0o [ 9 ] = rtB . g5opol5dur . le233aiaq5 ; rtB .
cbjdhhra0o [ 10 ] = rtB . g5opol5dur . b2jeeweznc ; rtB . cbjdhhra0o [ 11 ] =
muDoubleScalarFloor ( rtB . g5opol5dur . cnte5pmho4 ) ; { SimStruct * rts =
ssGetSFunction ( rtS , 14 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:522" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * , int ) =
rts -> modelMethods . sFcn . mdlOutputs . level2 ;
sfcnLoader_separateComplexHandler_withTID ( rts , sfcnMethodPtr , ( 0 <= 1 )
&& gbl_raccel_tid01eq ? 0 : 0 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
{ if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtDW . lqwrbhd21x . AQHandles
&& ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . lqwrbhd21x . AQHandles
, ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . jhikopnu5c + 0 ) ; } } } {
if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtDW . ko5el0avio . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . ko5el0avio . AQHandles ,
ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . kimclls5ui + 0 ) ; } } } { if
( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtDW . d11ycakunl . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . d11ycakunl . AQHandles ,
ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . gv3z4rzpl5 [ 0 ] + 0 ) ; } } }
} if ( rtB . mx32imycyi . h0dxk1yimp > 0.5 ) { rtB . edgmu1taic [ 0 ] = - rtB
. mx32imycyi . jeak4pqr3j ; } else { rtB . edgmu1taic [ 0 ] = rtB .
mx32imycyi . jeak4pqr3j ; } if ( rtB . gszk3bc3vp . h0dxk1yimp > 0.5 ) { rtB
. edgmu1taic [ 1 ] = - rtB . gszk3bc3vp . jeak4pqr3j ; } else { rtB .
edgmu1taic [ 1 ] = rtB . gszk3bc3vp . jeak4pqr3j ; } if ( rtB . df0oudwkj0 .
h0dxk1yimp > 0.5 ) { rtB . edgmu1taic [ 2 ] = - rtB . df0oudwkj0 . jeak4pqr3j
; } else { rtB . edgmu1taic [ 2 ] = rtB . df0oudwkj0 . jeak4pqr3j ; } if (
rtB . iroofsivyk . h0dxk1yimp > 0.5 ) { rtB . edgmu1taic [ 3 ] = - rtB .
iroofsivyk . jeak4pqr3j ; } else { rtB . edgmu1taic [ 3 ] = rtB . iroofsivyk
. jeak4pqr3j ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssGetLogOutput (
rtS ) ) { StructLogVar * svar = ( StructLogVar * ) rtDW . hflxu4olzs .
LoggedData [ 0 ] ; LogVar * var = svar -> signals . values ; { double locTime
= ssGetTaskTime ( rtS , 1 ) ; rt_UpdateLogVar ( ( LogVar * ) svar -> time , &
locTime , 0 ) ; } { real_T up0 [ 1 ] ; up0 [ 0 ] = rtB . edgmu1taic [ 0 ] ;
rt_UpdateLogVar ( ( LogVar * ) var , up0 , 0 ) ; var = var -> next ; } {
real_T up1 [ 1 ] ; up1 [ 0 ] = rtB . edgmu1taic [ 1 ] ; rt_UpdateLogVar ( (
LogVar * ) var , up1 , 0 ) ; var = var -> next ; } { real_T up2 [ 1 ] ; up2 [
0 ] = rtB . edgmu1taic [ 2 ] ; rt_UpdateLogVar ( ( LogVar * ) var , up2 , 0 )
; var = var -> next ; } { real_T up3 [ 1 ] ; up3 [ 0 ] = rtB . edgmu1taic [ 3
] ; rt_UpdateLogVar ( ( LogVar * ) var , up3 , 0 ) ; } } } e3r1b51sa5 ( rtB .
mx32imycyi . jeak4pqr3j , rtB . mx32imycyi . h0dxk1yimp , & rtB . d3cawecdgq
) ; e3r1b51sa5 ( rtB . gszk3bc3vp . jeak4pqr3j , rtB . gszk3bc3vp .
h0dxk1yimp , & rtB . ka15ybowc1 ) ; e3r1b51sa5 ( rtB . df0oudwkj0 .
jeak4pqr3j , rtB . df0oudwkj0 . h0dxk1yimp , & rtB . gz3hxniyg2 ) ;
e3r1b51sa5 ( rtB . iroofsivyk . jeak4pqr3j , rtB . iroofsivyk . h0dxk1yimp ,
& rtB . ejln4gh0kq ) ; ono5ii4s3b_idx_0 = rtP . rpm2rad_Gain * rtB .
d3cawecdgq . fkae5wqtcb ; ono5ii4s3b_idx_1 = rtP . rpm2rad1_Gain * rtB .
ka15ybowc1 . fkae5wqtcb ; ono5ii4s3b_idx_2 = rtP . rpm2rad2_Gain * rtB .
gz3hxniyg2 . fkae5wqtcb ; m5crkrq425_idx_0 = rtP . rpm2rad3_Gain * rtB .
ejln4gh0kq . fkae5wqtcb ; for ( i = 0 ; i < 3 ; i ++ ) { rtB . oqvw4bmbeg [ i
] = 0.0 ; rtB . oqvw4bmbeg [ i ] += rtP . three_one_skew_matrix [ i ] * rtP .
RW_J * ono5ii4s3b_idx_0 ; rtB . oqvw4bmbeg [ i ] += rtP .
three_one_skew_matrix [ i + 3 ] * rtP . RW_J * ono5ii4s3b_idx_1 ; rtB .
oqvw4bmbeg [ i ] += rtP . three_one_skew_matrix [ i + 6 ] * rtP . RW_J *
ono5ii4s3b_idx_2 ; rtB . oqvw4bmbeg [ i ] += rtP . three_one_skew_matrix [ i
+ 9 ] * rtP . RW_J * m5crkrq425_idx_0 ; } if ( ssIsSampleHit ( rtS , 1 , 0 )
) { } bjzuls4oiv ( jkvgcfu3cx , & rtB . e1zykr3jbv ) ; if ( ssIsSampleHit (
rtS , 1 , 0 ) && ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtP . ADSW > 0.0 ) {
if ( ! rtDW . lqozsqepug ) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart (
rtS ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW .
lqozsqepug = true ; } } else if ( rtDW . lqozsqepug ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . lqozsqepug =
false ; } } if ( rtDW . lqozsqepug ) { rtB . jn52bjhkjf = ( ( real_T ) ( ( (
( ! ( muDoubleScalarRem ( rtB . e1zykr3jbv . crs3vbajbr , 4.0 ) != 0.0 ) ) &&
( muDoubleScalarRem ( rtB . e1zykr3jbv . crs3vbajbr , 100.0 ) != 0.0 ) ) || (
! ( muDoubleScalarRem ( rtB . e1zykr3jbv . crs3vbajbr , 400.0 ) != 0.0 ) ) )
&& ( rtB . e1zykr3jbv . pyqwe5rsse > 2.0 ) ) + ( real_T ) b_m [ ( int32_T )
rtB . e1zykr3jbv . pyqwe5rsse - 1 ] ) + rtB . e1zykr3jbv . agveekqpqv ; rtB .
chrkykmk4n = ( rtP . hour2sec_Gain * rtB . e1zykr3jbv . le233aiaq5 + rtP .
min2sec_Gain * rtB . e1zykr3jbv . b2jeeweznc ) + rtB . e1zykr3jbv .
cnte5pmho4 ; rtB . i2mlgup0vd = rtB . chrkykmk4n / 3600.0 + rtB . a5ald3g22i
[ 1 ] / 15.0 ; { SimStruct * rts = ssGetSFunction ( rtS , 0 ) ; { static
const char * blockSIDForSFcnLoader = "SILS_20241709:424:2443:1728" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 0 <= 1 ) && gbl_raccel_tid01eq ? 0 : 0 ) ; } } fsnekqmcuz (
rtP . wE , hqbmtiz1ck , & rtB . aav5pusdkp ) ; kclbezm4gf [ 0 ] = ( ( cW * cu
- sW * su * ci ) * r_dot + ( - cW * su - sW * cu * ci ) * ( e * h ) ) - rtB .
aav5pusdkp . aupbtlrqjk [ 0 ] ; kclbezm4gf [ 1 ] = ( ( cW * su * ci + sW * cu
) * r_dot + ( cW * cu * ci + - sW * su ) * ( e * h ) ) - rtB . aav5pusdkp .
aupbtlrqjk [ 1 ] ; kclbezm4gf [ 2 ] = ( e * h * cu * u + r_dot * su * u ) -
rtB . aav5pusdkp . aupbtlrqjk [ 2 ] ; dk2rjxlhn5 = 3.3121686421112381E-170 ;
absxk = muDoubleScalarAbs ( kclbezm4gf [ 0 ] ) ; if ( absxk >
3.3121686421112381E-170 ) { hmyegtxsdh_idx_1 = 1.0 ; dk2rjxlhn5 = absxk ; }
else { T = absxk / 3.3121686421112381E-170 ; hmyegtxsdh_idx_1 = T * T ; }
absxk = muDoubleScalarAbs ( kclbezm4gf [ 1 ] ) ; if ( absxk > dk2rjxlhn5 ) {
T = dk2rjxlhn5 / absxk ; hmyegtxsdh_idx_1 = hmyegtxsdh_idx_1 * T * T + 1.0 ;
dk2rjxlhn5 = absxk ; } else { T = absxk / dk2rjxlhn5 ; hmyegtxsdh_idx_1 += T
* T ; } absxk = muDoubleScalarAbs ( kclbezm4gf [ 2 ] ) ; if ( absxk >
dk2rjxlhn5 ) { T = dk2rjxlhn5 / absxk ; hmyegtxsdh_idx_1 = hmyegtxsdh_idx_1 *
T * T + 1.0 ; dk2rjxlhn5 = absxk ; } else { T = absxk / dk2rjxlhn5 ;
hmyegtxsdh_idx_1 += T * T ; } hmyegtxsdh_idx_1 = dk2rjxlhn5 *
muDoubleScalarSqrt ( hmyegtxsdh_idx_1 ) ; su = rtP . gcm3kgm3_Gain * rtB .
bfrpnyoemv * - 0.5 * rtP . CD * rtP . area * hmyegtxsdh_idx_1 ; kclbezm4gf [
0 ] = su * kclbezm4gf [ 0 ] * 1.0E+6 ; kclbezm4gf [ 1 ] = su * kclbezm4gf [ 1
] * 1.0E+6 ; su = su * kclbezm4gf [ 2 ] * 1.0E+6 ; m5crkrq425_idx_0 =
muDoubleScalarSqrt ( ( ( delta * delta + ovpn3bsi5w * ovpn3bsi5w ) +
hakul2mmal_idx_1 * hakul2mmal_idx_1 ) + M * M ) ; hmyegtxsdh_idx_1 = delta /
m5crkrq425_idx_0 ; u = ovpn3bsi5w / m5crkrq425_idx_0 ; h = hakul2mmal_idx_1 /
m5crkrq425_idx_0 ; m5crkrq425_idx_0 = M / m5crkrq425_idx_0 ; bmxglekqjv = ( (
( rtP . Constant_Value - h * h ) - m5crkrq425_idx_0 * m5crkrq425_idx_0 ) *
rtP . Gain2_Gain * kclbezm4gf [ 0 ] + ( u * h + hmyegtxsdh_idx_1 *
m5crkrq425_idx_0 ) * rtP . Gain_Gain * kclbezm4gf [ 1 ] ) + ( u *
m5crkrq425_idx_0 - hmyegtxsdh_idx_1 * h ) * rtP . Gain1_Gain * su ;
fuaqyhzuaf = ( ( ( rtP . Constant_Value_kjzrxx2pwp - u * u ) -
m5crkrq425_idx_0 * m5crkrq425_idx_0 ) * rtP . Gain2_Gain_lev0onxthq *
kclbezm4gf [ 1 ] + ( u * h - hmyegtxsdh_idx_1 * m5crkrq425_idx_0 ) * rtP .
Gain_Gain_dkxjnn2goq * kclbezm4gf [ 0 ] ) + ( hmyegtxsdh_idx_1 * u + h *
m5crkrq425_idx_0 ) * rtP . Gain1_Gain_ewxpcgxoho * su ; dlemuqwiz2 = ( ( u *
m5crkrq425_idx_0 + hmyegtxsdh_idx_1 * h ) * rtP . Gain_Gain_kwo0jnespy *
kclbezm4gf [ 0 ] + ( h * m5crkrq425_idx_0 - hmyegtxsdh_idx_1 * u ) * rtP .
Gain1_Gain_oz4csetmxu * kclbezm4gf [ 1 ] ) + ( ( rtP .
Constant_Value_a2453xvslr - u * u ) - h * h ) * rtP . Gain2_Gain_ekmxnyjdgq *
su ; lkjrchjyiy ( rtP . arm , bmxglekqjv , fuaqyhzuaf , dlemuqwiz2 , & rtB .
l15tbbx15x ) ; if ( ssIsModeUpdateTimeStep ( rtS ) ) { srUpdateBC ( rtDW .
icv4qsjrec ) ; } } muDoubleScalarSinCos ( 0.017453292519943295 * rtB .
a5ald3g22i [ 0 ] , & T3 , & sp ) ; muDoubleScalarSinCos (
0.017453292519943295 * rtB . a5ald3g22i [ 1 ] , & lnr42yo3kc_idx_1 , &
luilsch3m0_idx_1 ) ; hmyegtxsdh_idx_1 = T3 * luilsch3m0_idx_1 ; h1gu4wqhux [
0 ] = - ( T3 * luilsch3m0_idx_1 ) ; h1gu4wqhux [ 3 ] = - ( T3 *
lnr42yo3kc_idx_1 ) ; h1gu4wqhux [ 1 ] = - lnr42yo3kc_idx_1 ; h1gu4wqhux [ 2 ]
= - ( sp * luilsch3m0_idx_1 ) ; h1gu4wqhux [ 5 ] = - ( sp * lnr42yo3kc_idx_1
) ; h1gu4wqhux [ 8 ] = - T3 ; h1gu4wqhux [ 4 ] = luilsch3m0_idx_1 ;
h1gu4wqhux [ 6 ] = sp ; h1gu4wqhux [ 7 ] = rtP . Constant_Value_ns0uhctphf ;
cu = ( ( ( ( ( real_T ) ( jd5umm0a5g ( rtB . e1zykr3jbv . crs3vbajbr ) && (
rtB . e1zykr3jbv . pyqwe5rsse > 2.0 ) ) + ( real_T ) b_m [ ( int32_T ) rtB .
e1zykr3jbv . pyqwe5rsse - 1 ] ) + rtB . e1zykr3jbv . agveekqpqv ) + ( ( 60.0
* rtB . e1zykr3jbv . b2jeeweznc + rtB . e1zykr3jbv . cnte5pmho4 ) + 3600.0 *
rtB . e1zykr3jbv . le233aiaq5 ) / 86400.0 ) - 1.0 ) / ( ( real_T ) jd5umm0a5g
( rtB . e1zykr3jbv . crs3vbajbr ) + 365.0 ) + rtB . e1zykr3jbv . crs3vbajbr ;
if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsModeUpdateTimeStep ( rtS ) ) { if (
rtP . GPperturbationSW > 0.0 ) { if ( ! rtDW . odkn5lgudq ) { if (
ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . odkn5lgudq =
true ; } } else if ( rtDW . odkn5lgudq ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . odkn5lgudq =
false ; } } if ( rtDW . odkn5lgudq ) { hmyegtxsdh_idx_3 = d22ngtbkmu [ 4 ] +
ea ; su = e * e ; ci = 3.0 * rtP . J2 * rtP . GE * rtP . earth_radius * rtP .
earth_radius / su / su ; u = muDoubleScalarSin ( d22ngtbkmu [ 2 ] ) ; su =
muDoubleScalarSin ( hmyegtxsdh_idx_3 ) ; rtB . hm15o25lmb [ 0 ] = ( 3.0 * u *
u * su * su - 1.0 ) * ( ci / 2.0 ) ; rtB . hm15o25lmb [ 1 ] = - ci * u * u *
su * muDoubleScalarCos ( hmyegtxsdh_idx_3 ) ; rtB . hm15o25lmb [ 2 ] = - ci *
u * muDoubleScalarCos ( d22ngtbkmu [ 2 ] ) * su ; if ( ssIsModeUpdateTimeStep
( rtS ) ) { srUpdateBC ( rtDW . ggsva4qu4a ) ; } } if ( ssIsSampleHit ( rtS ,
1 , 0 ) && ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtP . GGSW > 0.0 ) { if (
! rtDW . bdwu52mmaq ) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS )
) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . bdwu52mmaq
= true ; } } else if ( rtDW . bdwu52mmaq ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . bdwu52mmaq =
false ; } } if ( rtDW . bdwu52mmaq ) { ci = muDoubleScalarSqrt ( ( ( delta *
delta + ovpn3bsi5w * ovpn3bsi5w ) + hakul2mmal_idx_1 * hakul2mmal_idx_1 ) + M
* M ) ; su = hakul2mmal_idx_1 / ci ; u = M / ci ; hmyegtxsdh_idx_3 =
ovpn3bsi5w / ci ; ci = delta / ci ; ono5ii4s3b_idx_0 = ( ( ( rtP .
Constant_Value_p1jiuwoh41 - su * su ) - u * u ) * rtP . Gain2_Gain_nbadgk3cn2
* hqbmtiz1ck [ 0 ] + ( hmyegtxsdh_idx_3 * su + ci * u ) * rtP .
Gain_Gain_eirpwpy25e * hqbmtiz1ck [ 1 ] ) + ( hmyegtxsdh_idx_3 * u - ci * su
) * rtP . Gain1_Gain_o0zodm4wod * hqbmtiz1ck [ 2 ] ; ono5ii4s3b_idx_1 = ( ( (
rtP . Constant_Value_boboxxtlqz - hmyegtxsdh_idx_3 * hmyegtxsdh_idx_3 ) - u *
u ) * rtP . Gain2_Gain_jw4ny4s1oi * hqbmtiz1ck [ 1 ] + ( hmyegtxsdh_idx_3 *
su - ci * u ) * rtP . Gain_Gain_cng034c550 * hqbmtiz1ck [ 0 ] ) + ( ci *
hmyegtxsdh_idx_3 + su * u ) * rtP . Gain1_Gain_kzqbx21odb * hqbmtiz1ck [ 2 ]
; ono5ii4s3b_idx_2 = ( ( hmyegtxsdh_idx_3 * u + ci * su ) * rtP .
Gain_Gain_lv4xtg4q1g * hqbmtiz1ck [ 0 ] + ( su * u - ci * hmyegtxsdh_idx_3 )
* rtP . Gain1_Gain_pmepj0f34k * hqbmtiz1ck [ 1 ] ) + ( ( rtP .
Constant_Value_gtgl4kppkk - hmyegtxsdh_idx_3 * hmyegtxsdh_idx_3 ) - su * su )
* rtP . Gain2_Gain_nafalxbj3s * hqbmtiz1ck [ 2 ] ; dk2rjxlhn5 =
3.3121686421112381E-170 ; absxk = muDoubleScalarAbs ( ono5ii4s3b_idx_0 ) ; if
( absxk > 3.3121686421112381E-170 ) { su = 1.0 ; dk2rjxlhn5 = absxk ; } else
{ T = absxk / 3.3121686421112381E-170 ; su = T * T ; } absxk =
muDoubleScalarAbs ( ono5ii4s3b_idx_1 ) ; if ( absxk > dk2rjxlhn5 ) { T =
dk2rjxlhn5 / absxk ; su = su * T * T + 1.0 ; dk2rjxlhn5 = absxk ; } else { T
= absxk / dk2rjxlhn5 ; su += T * T ; } absxk = muDoubleScalarAbs (
ono5ii4s3b_idx_2 ) ; if ( absxk > dk2rjxlhn5 ) { T = dk2rjxlhn5 / absxk ; su
= su * T * T + 1.0 ; dk2rjxlhn5 = absxk ; } else { T = absxk / dk2rjxlhn5 ;
su += T * T ; } su = dk2rjxlhn5 * muDoubleScalarSqrt ( su ) ;
ono5ii4s3b_idx_0 /= su ; ono5ii4s3b_idx_1 /= su ; u = ono5ii4s3b_idx_2 / su ;
for ( i = 0 ; i < 3 ; i ++ ) { kclbezm4gf [ i ] = ( rtP . I [ i + 3 ] *
ono5ii4s3b_idx_1 + rtP . I [ i ] * ono5ii4s3b_idx_0 ) + rtP . I [ i + 6 ] * u
; } su = 3.0 * rtP . GE / su / su / su ; rtB . b5ehs0zt32 [ 0 ] = (
ono5ii4s3b_idx_1 * kclbezm4gf [ 2 ] - kclbezm4gf [ 1 ] * u ) * su ; rtB .
b5ehs0zt32 [ 1 ] = ( kclbezm4gf [ 0 ] * u - ono5ii4s3b_idx_0 * kclbezm4gf [ 2
] ) * su ; rtB . b5ehs0zt32 [ 2 ] = ( ono5ii4s3b_idx_0 * kclbezm4gf [ 1 ] -
kclbezm4gf [ 0 ] * ono5ii4s3b_idx_1 ) * su ; if ( ssIsModeUpdateTimeStep (
rtS ) ) { srUpdateBC ( rtDW . kddtry4ekq ) ; } } for ( i = 0 ; i < 13 ; i ++
) { cl [ i ] = ( rtNaN ) ; sl [ i ] = ( rtNaN ) ; } u = 0.0 ; g5zew52spt =
0.0 ; m5crkrq425_idx_0 = 0.0 ; if ( cu < 2010.0 ) { T = ( cu - 1900.0 ) * 0.2
; hmyegtxsdh_idx_3 = muDoubleScalarFloor ( T ) ; T -= hmyegtxsdh_idx_3 ; if (
cu < 1995.0 ) { nc = 120 ; hmyegtxsdh_idx_3 *= 120.0 ; kmx = 65 ; } else { nc
= 195 ; hmyegtxsdh_idx_3 = muDoubleScalarFloor ( ( cu - 1995.0 ) * 0.2 ) *
195.0 + 2280.0 ; kmx = 104 ; } cu = 1.0 - T ; } else { T = cu - 2010.0 ; cu =
1.0 ; hmyegtxsdh_idx_3 = 2865.0 ; nc = 195 ; kmx = 104 ; } hmyegtxsdh_idx_2 =
( 90.0 - rtB . a5ald3g22i [ 0 ] ) * 0.017453292 ; ci = muDoubleScalarCos (
hmyegtxsdh_idx_2 ) ; cW = muDoubleScalarSin ( hmyegtxsdh_idx_2 ) ;
hmyegtxsdh_idx_2 = rtB . a5ald3g22i [ 1 ] * 0.017453292 ; cl [ 0 ] =
muDoubleScalarCos ( hmyegtxsdh_idx_2 ) ; sl [ 0 ] = muDoubleScalarSin (
hmyegtxsdh_idx_2 ) ; oqmv0ahkug = 1.0 ; sW = 1.0 ; su = 0.0 ;
hmyegtxsdh_idx_2 = 4.06806316E+7 * cW * cW ; c_sp = 4.0408296E+7 * ci * ci ;
b_sp = hmyegtxsdh_idx_2 + c_sp ; h = muDoubleScalarSqrt ( b_sp ) ; dk2rjxlhn5
= muDoubleScalarSqrt ( ( 2.0 * h + rtB . mpca01r2m2 ) * rtB . mpca01r2m2 + (
4.06806316E+7 * hmyegtxsdh_idx_2 + 4.0408296E+7 * c_sp ) / b_sp ) ; r_dot = (
rtB . mpca01r2m2 + h ) / dk2rjxlhn5 ; h = 272335.60000000149 / h * ci * cW /
dk2rjxlhn5 ; hmyegtxsdh_idx_2 = ci ; ci = ci * r_dot - cW * h ; cW = cW *
r_dot + hmyegtxsdh_idx_2 * h ; kl0gyfxice = 6371.2 / dk2rjxlhn5 ; dn2nlybx4r
= kl0gyfxice * kl0gyfxice ; for ( i = 0 ; i <= kmx ; i ++ ) { p_data [ i ] =
( rtNaN ) ; q_data [ i ] = ( rtNaN ) ; } c_cp = 0.0 ; absxk = 0.0 ; p_data [
0 ] = 1.0 ; p_data [ 2 ] = cW ; q_data [ 0 ] = 0.0 ; q_data [ 2 ] = ci ; for
( i = 0 ; i < kmx ; i ++ ) { if ( su < sW ) { sW = 0.0 ; su ++ ; dn2nlybx4r
*= kl0gyfxice ; c_cp = su ; absxk = su - 1.0 ; } if ( ( sW == su ) && ( i + 2
!= 3 ) ) { hmyegtxsdh_idx_2 = muDoubleScalarSqrt ( 1.0 - 0.5 / sW ) ;
dk2rjxlhn5 = ( ( ( real_T ) i + 2.0 ) - su ) - 1.0 ; p_data [ i + 1 ] =
hmyegtxsdh_idx_2 * cW * p_data [ ( int32_T ) dk2rjxlhn5 - 1 ] ; q_data [ i +
1 ] = ( q_data [ ( int32_T ) dk2rjxlhn5 - 1 ] * cW + p_data [ ( int32_T )
dk2rjxlhn5 - 1 ] * ci ) * hmyegtxsdh_idx_2 ; cl [ ( int32_T ) sW - 1 ] = cl [
( int32_T ) sW - 2 ] * cl [ 0 ] - sl [ ( int32_T ) sW - 2 ] * sl [ 0 ] ; sl [
( int32_T ) sW - 1 ] = sl [ ( int32_T ) sW - 2 ] * cl [ 0 ] + cl [ ( int32_T
) sW - 2 ] * sl [ 0 ] ; } if ( ( sW != su ) && ( i + 2 != 3 ) ) { c_sp = sW *
sW ; hmyegtxsdh_idx_2 = muDoubleScalarSqrt ( c_cp * c_cp - c_sp ) ; c_sp =
muDoubleScalarSqrt ( absxk * absxk - c_sp ) / hmyegtxsdh_idx_2 ; b_sp = (
c_cp + absxk ) / hmyegtxsdh_idx_2 ; hmyegtxsdh_idx_2 = ( ( real_T ) i + 2.0 )
- su ; dk2rjxlhn5 = ( hmyegtxsdh_idx_2 - su ) + 1.0 ; p_data [ i + 1 ] = b_sp
* ci * p_data [ ( int32_T ) hmyegtxsdh_idx_2 - 1 ] - p_data [ ( int32_T )
dk2rjxlhn5 - 1 ] * c_sp ; q_data [ i + 1 ] = ( q_data [ ( int32_T )
hmyegtxsdh_idx_2 - 1 ] * ci - p_data [ ( int32_T ) hmyegtxsdh_idx_2 - 1 ] *
cW ) * b_sp - q_data [ ( int32_T ) dk2rjxlhn5 - 1 ] * c_sp ; } c_sp =
hmyegtxsdh_idx_3 + oqmv0ahkug ; hmyegtxsdh_idx_2 = ( c_p [ ( int32_T ) ( c_sp
+ ( real_T ) nc ) - 1 ] * T + c_p [ ( int32_T ) c_sp - 1 ] * cu ) *
dn2nlybx4r ; if ( sW != 0.0 ) { c_sp = ( c_p [ ( int32_T ) ( ( c_sp + (
real_T ) nc ) + 1.0 ) - 1 ] * T + c_p [ ( int32_T ) ( c_sp + 1.0 ) - 1 ] * cu
) * dn2nlybx4r ; b_sp = cl [ ( int32_T ) sW - 1 ] * hmyegtxsdh_idx_2 + sl [ (
int32_T ) sW - 1 ] * c_sp ; u += q_data [ i + 1 ] * b_sp ; m5crkrq425_idx_0
-= ( c_cp + 1.0 ) * b_sp * p_data [ i + 1 ] ; if ( cW != 0.0 ) { g5zew52spt
+= ( sl [ ( int32_T ) sW - 1 ] * hmyegtxsdh_idx_2 - cl [ ( int32_T ) sW - 1 ]
* c_sp ) * sW * p_data [ i + 1 ] / cW ; } else { g5zew52spt += ( sl [ (
int32_T ) sW - 1 ] * hmyegtxsdh_idx_2 - cl [ ( int32_T ) sW - 1 ] * c_sp ) *
q_data [ i + 1 ] * ci ; } oqmv0ahkug += 2.0 ; } else { u += q_data [ i + 1 ]
* hmyegtxsdh_idx_2 ; m5crkrq425_idx_0 -= ( c_cp + 1.0 ) * hmyegtxsdh_idx_2 *
p_data [ i + 1 ] ; oqmv0ahkug ++ ; } sW ++ ; } ouoayp2yxm [ 0 ] = u * r_dot +
m5crkrq425_idx_0 * h ; ouoayp2yxm [ 2 ] = m5crkrq425_idx_0 * r_dot - u * h ;
ouoayp2yxm [ 1 ] = g5zew52spt ; rtB . mmxfckfrxp = ( ( ( ( afmdwca1nj [ 0 ] *
afmdwca1nj [ 4 ] * afmdwca1nj [ 8 ] - afmdwca1nj [ 0 ] * afmdwca1nj [ 5 ] *
afmdwca1nj [ 7 ] ) - afmdwca1nj [ 1 ] * afmdwca1nj [ 3 ] * afmdwca1nj [ 8 ] )
+ afmdwca1nj [ 2 ] * afmdwca1nj [ 3 ] * afmdwca1nj [ 7 ] ) + afmdwca1nj [ 1 ]
* afmdwca1nj [ 5 ] * afmdwca1nj [ 6 ] ) - afmdwca1nj [ 2 ] * afmdwca1nj [ 4 ]
* afmdwca1nj [ 6 ] ; if ( ssIsSampleHit ( rtS , 1 , 0 ) && ( ! ( rtB .
mmxfckfrxp != 0.0 ) ) ) { S = rtS ; diag = CreateDiagnosticAsVoidPtr (
"Simulink:blocks:AssertionAssert" , 2 , 5 ,
"SILS_20241709/Environment&Dynamics/Invert  3x3 Matrix/Assertion" , 2 ,
ssGetT ( rtS ) ) ; rt_ssSet_slErrMsg ( S , diag ) ; ssSetStopRequested ( rtS
, ( int ) ssGetT ( rtS ) ) ; } rt_invd3x3_snf ( afmdwca1nj , dw412mfedm ) ;
rtB . ovvyrfj4qq = ( ( ( ( - hmyegtxsdh_idx_1 * luilsch3m0_idx_1 * - T3 - - (
sp * lnr42yo3kc_idx_1 ) * - hmyegtxsdh_idx_1 * h1gu4wqhux [ 7 ] ) - - ( T3 *
lnr42yo3kc_idx_1 ) * - lnr42yo3kc_idx_1 * - T3 ) + h1gu4wqhux [ 2 ] *
h1gu4wqhux [ 3 ] * h1gu4wqhux [ 7 ] ) + - lnr42yo3kc_idx_1 * h1gu4wqhux [ 5 ]
* sp ) - - ( sp * luilsch3m0_idx_1 ) * luilsch3m0_idx_1 * sp ; if (
ssIsSampleHit ( rtS , 1 , 0 ) && ( ! ( rtB . ovvyrfj4qq != 0.0 ) ) ) { S =
rtS ; diag = CreateDiagnosticAsVoidPtr ( "Simulink:blocks:AssertionAssert" ,
2 , 5 , "SILS_20241709/Environment&Dynamics/Invert  3x3 Matrix1/Assertion" ,
2 , ssGetT ( rtS ) ) ; rt_ssSet_slErrMsg ( S , diag ) ; ssSetStopRequested (
rtS , ( int ) ssGetT ( rtS ) ) ; } rt_invd3x3_snf ( h1gu4wqhux , o1gf1sn0wj )
; balzhvtkpr = d22ngtbkmu [ 4 ] + ea ; su = muDoubleScalarSqrt ( rtP . GE / (
d22ngtbkmu [ 0 ] * d22ngtbkmu [ 0 ] * d22ngtbkmu [ 0 ] ) ) ; m5crkrq425_idx_0
= ( 1.0 - d22ngtbkmu [ 1 ] * d22ngtbkmu [ 1 ] ) * d22ngtbkmu [ 0 ] ; h =
muDoubleScalarSqrt ( rtP . GE * m5crkrq425_idx_0 ) ; u = d22ngtbkmu [ 4 ] +
ea ; T = muDoubleScalarCos ( ea ) ; ea = muDoubleScalarSin ( ea ) ; ci = e *
muDoubleScalarSin ( u ) / ( h * muDoubleScalarSin ( d22ngtbkmu [ 2 ] ) ) *
rtB . hm15o25lmb [ 2 ] ; if ( muDoubleScalarAbs ( d22ngtbkmu [ 1 ] ) > 1.0E-6
) { rtB . gs20g4hobc [ 4 ] = ( T * rtB . hm15o25lmb [ 0 ] - ( e /
m5crkrq425_idx_0 + 1.0 ) * ea * rtB . hm15o25lmb [ 1 ] ) * ( -
m5crkrq425_idx_0 / ( d22ngtbkmu [ 1 ] * h ) ) - ci * muDoubleScalarCos (
d22ngtbkmu [ 2 ] ) ; rtB . gs20g4hobc [ 5 ] = ( ( m5crkrq425_idx_0 * T - 2.0
* d22ngtbkmu [ 1 ] * e ) * rtB . hm15o25lmb [ 0 ] - ( m5crkrq425_idx_0 + e )
* ea * rtB . hm15o25lmb [ 1 ] ) * ( 1.0 / ( su * d22ngtbkmu [ 0 ] *
d22ngtbkmu [ 0 ] * d22ngtbkmu [ 1 ] ) ) + su ; } else { rtB . gs20g4hobc [ 4
] = - ci * muDoubleScalarCos ( d22ngtbkmu [ 2 ] ) ; rtB . gs20g4hobc [ 5 ] =
su - 2.0 * e / su / d22ngtbkmu [ 0 ] / d22ngtbkmu [ 0 ] * rtB . hm15o25lmb [
0 ] ; } rtB . gs20g4hobc [ 0 ] = 2.0 * d22ngtbkmu [ 0 ] * d22ngtbkmu [ 0 ] /
h * ( d22ngtbkmu [ 1 ] * ea * rtB . hm15o25lmb [ 0 ] + m5crkrq425_idx_0 / e *
rtB . hm15o25lmb [ 1 ] ) ; rtB . gs20g4hobc [ 1 ] = ( ( ( d22ngtbkmu [ 1 ] +
T ) / ( d22ngtbkmu [ 1 ] * T + 1.0 ) + T ) * rtB . hm15o25lmb [ 1 ] + ea *
rtB . hm15o25lmb [ 0 ] ) * ( m5crkrq425_idx_0 / h ) ; rtB . gs20g4hobc [ 2 ]
= e * muDoubleScalarCos ( u ) / h * rtB . hm15o25lmb [ 2 ] ; rtB . gs20g4hobc
[ 3 ] = ci ; e = muDoubleScalarSqrt ( ( ( delta * delta + ovpn3bsi5w *
ovpn3bsi5w ) + hakul2mmal_idx_1 * hakul2mmal_idx_1 ) + M * M ) ; T = delta /
e ; ea = ovpn3bsi5w / e ; ci = hakul2mmal_idx_1 / e ; e = M / e ; ivx0j3mj3l
( o1gf1sn0wj , ouoayp2yxm , & rtB . hdgmktoixc ) ; ivx0j3mj3l ( dw412mfedm ,
rtB . hdgmktoixc . poahfmj3s1 , & rtB . ca53m05hej ) ; i3r45wjfj2 = ( ( ( rtP
. Constant_Value_amoommf0mg - ci * ci ) - e * e ) * rtP .
Gain2_Gain_mjvcbm4pqd * rtB . ca53m05hej . poahfmj3s1 [ 0 ] + ( ea * ci + T *
e ) * rtP . Gain_Gain_kyqyxgfjjc * rtB . ca53m05hej . poahfmj3s1 [ 1 ] ) + (
ea * e - T * ci ) * rtP . Gain1_Gain_jdzh1vayht * rtB . ca53m05hej .
poahfmj3s1 [ 2 ] ; lit5wfpqiy = ( ( ( rtP . Constant_Value_mq4m5be1k3 - ea *
ea ) - e * e ) * rtP . Gain2_Gain_bob4otocpt * rtB . ca53m05hej . poahfmj3s1
[ 1 ] + ( ea * ci - T * e ) * rtP . Gain_Gain_ag50armt4q * rtB . ca53m05hej .
poahfmj3s1 [ 0 ] ) + ( T * ea + ci * e ) * rtP . Gain1_Gain_hahbyfhvn1 * rtB
. ca53m05hej . poahfmj3s1 [ 2 ] ; mu3v2yavfb = ( ( ea * e + T * ci ) * rtP .
Gain_Gain_du1axyb1td * rtB . ca53m05hej . poahfmj3s1 [ 0 ] + ( ci * e - T *
ea ) * rtP . Gain1_Gain_cjxo0bvxyl * rtB . ca53m05hej . poahfmj3s1 [ 1 ] ) +
( ( rtP . Constant_Value_kcvsynl3gu - ea * ea ) - ci * ci ) * rtP .
Gain2_Gain_cyuruau31y * rtB . ca53m05hej . poahfmj3s1 [ 2 ] ; if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtP
. rem_magSW > 0.0 ) { if ( ! rtDW . kc0x0orqmh ) { if ( ssGetTaskTime ( rtS ,
1 ) != ssGetTStart ( rtS ) ) { ssSetBlockStateForSolverChangedAtMajorStep (
rtS ) ; } rtDW . kc0x0orqmh = true ; } } else if ( rtDW . kc0x0orqmh ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . kc0x0orqmh =
false ; } } if ( rtDW . kc0x0orqmh ) { h3zuftpwti [ 0 ] = rtP . nT2T_Gain *
i3r45wjfj2 ; h3zuftpwti [ 1 ] = rtP . nT2T_Gain * lit5wfpqiy ; h3zuftpwti [ 2
] = rtP . nT2T_Gain * mu3v2yavfb ; fsnekqmcuz ( rtP . rem_mag , h3zuftpwti ,
& rtB . jclektca5o ) ; if ( ssIsModeUpdateTimeStep ( rtS ) ) { srUpdateBC (
rtDW . gxgp4hskcm ) ; } } if ( ( rtDW . mmkouxeune == ( rtMinusInf ) ) || (
rtDW . mmkouxeune == ssGetTaskTime ( rtS , 0 ) ) ) { rtDW . mmkouxeune =
ssGetTaskTime ( rtS , 0 ) ; rtB . jr21nlhhbn [ 0 ] = rtP . IC_Value [ 0 ] ;
rtB . jr21nlhhbn [ 1 ] = rtP . IC_Value [ 1 ] ; rtB . jr21nlhhbn [ 2 ] = rtP
. IC_Value [ 2 ] ; rtB . jr21nlhhbn [ 3 ] = rtP . IC_Value [ 3 ] ; } else {
rtB . jr21nlhhbn [ 0 ] = delta ; rtB . jr21nlhhbn [ 1 ] = ovpn3bsi5w ; rtB .
jr21nlhhbn [ 2 ] = hakul2mmal_idx_1 ; rtB . jr21nlhhbn [ 3 ] = M ; } if ( (
rtDW . jeeaiz3533 == ( rtMinusInf ) ) || ( rtDW . jeeaiz3533 == ssGetTaskTime
( rtS , 0 ) ) ) { rtDW . jeeaiz3533 = ssGetTaskTime ( rtS , 0 ) ; rtB .
gyoxzzwqiz [ 0 ] = rtP . IC1_Value [ 0 ] ; rtB . gyoxzzwqiz [ 1 ] = rtP .
IC1_Value [ 1 ] ; rtB . gyoxzzwqiz [ 2 ] = rtP . IC1_Value [ 2 ] ; } else {
rtB . gyoxzzwqiz [ 0 ] = irzywnigjr_idx_0 ; rtB . gyoxzzwqiz [ 1 ] =
irzywnigjr_idx_1 ; rtB . gyoxzzwqiz [ 2 ] = irzywnigjr_idx_2 ; } T = rtP .
RW_kT * g2acauyoyt - rtP . losstorquepropotionto_Gain * k50kzncrsl ; ea = rtP
. RW_kT * i4jz3egckp - rtP . losstorquepropotionto_Gain_hahtzed0yk *
otiigwfvqy ; ci = rtP . RW_kT * hxeyppvwpl - rtP .
losstorquepropotionto_Gain_ftpubwm50g * jwppuzxlko ; e = rtP . RW_kT *
j4xyasklvt - rtP . losstorquepropotionto_Gain_k3z3t2gd1a * gomxyom0vc ;
k50kzncrsl = rtP . nT_2_T_Gain * i3r45wjfj2 ; jwppuzxlko = rtP . nT_2_T_Gain
* lit5wfpqiy ; gomxyom0vc = rtP . nT_2_T_Gain * mu3v2yavfb ; ono5ii4s3b_idx_0
= rtP . TransferFcn_C_kwbfsnl1hg * rtX . ek1dcgndv4 ; ono5ii4s3b_idx_1 = rtP
. TransferFcn_C_n45ccaftaw * rtX . iyvywkyjkt ; ono5ii4s3b_idx_2 = rtP .
TransferFcn_C_c3yi1bxnht * rtX . cscwx5acjj ; for ( i = 0 ; i < 3 ; i ++ ) {
kclbezm4gf [ i ] = ( ( ( rtP . three_one_skew_matrix [ i + 3 ] * ea + rtP .
three_one_skew_matrix [ i ] * T ) + rtP . three_one_skew_matrix [ i + 6 ] *
ci ) + rtP . three_one_skew_matrix [ i + 9 ] * e ) * rtP .
reactiontorque_Gain ; lyw5zuxpkh [ i ] -= hqbmtiz1ck [ i ] ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtP
. SRPSW > 0.0 ) { if ( ! rtDW . hp42fr3fka ) { if ( ssGetTaskTime ( rtS , 1 )
!= ssGetTStart ( rtS ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; } rtDW . hp42fr3fka = true ; } } else if ( rtDW . hp42fr3fka ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . hp42fr3fka =
false ; } } if ( rtDW . hp42fr3fka ) { otiigwfvqy = ( lyw5zuxpkh [ 0 ] *
lyw5zuxpkh [ 0 ] + lyw5zuxpkh [ 1 ] * lyw5zuxpkh [ 1 ] ) + lyw5zuxpkh [ 2 ] *
lyw5zuxpkh [ 2 ] ; if ( otiigwfvqy < 0.0 ) { u = - muDoubleScalarSqrt (
muDoubleScalarAbs ( otiigwfvqy ) ) ; } else { u = muDoubleScalarSqrt (
otiigwfvqy ) ; } if ( u > rtP . NormalizeVector_maxzero ) { h = lyw5zuxpkh [
0 ] ; hmyegtxsdh_idx_1 = lyw5zuxpkh [ 1 ] ; hmyegtxsdh_idx_2 = lyw5zuxpkh [ 2
] ; hmyegtxsdh_idx_3 = u ; } else { h = lyw5zuxpkh [ 0 ] * 0.0 ;
hmyegtxsdh_idx_1 = lyw5zuxpkh [ 1 ] * 0.0 ; hmyegtxsdh_idx_2 = lyw5zuxpkh [ 2
] * 0.0 ; hmyegtxsdh_idx_3 = rtP . Constant_Value_n0n1a4zdn2 ; } cu =
muDoubleScalarSqrt ( ( ( delta * delta + ovpn3bsi5w * ovpn3bsi5w ) +
hakul2mmal_idx_1 * hakul2mmal_idx_1 ) + M * M ) ; u = delta / cu ; ovpn3bsi5w
/= cu ; otiigwfvqy = hakul2mmal_idx_1 / cu ; cu = M / cu ; if ( rtB .
kimclls5ui == 1.0 ) { su = - rtP . pSR * rtP . CR * rtP . area ; lyw5zuxpkh [
0 ] = h / hmyegtxsdh_idx_3 * su ; lyw5zuxpkh [ 1 ] = hmyegtxsdh_idx_1 /
hmyegtxsdh_idx_3 * su ; lyw5zuxpkh [ 2 ] = hmyegtxsdh_idx_2 /
hmyegtxsdh_idx_3 * su ; } else { lyw5zuxpkh [ 0 ] = 0.0 ; lyw5zuxpkh [ 1 ] =
0.0 ; lyw5zuxpkh [ 2 ] = 0.0 ; } myjibr0vt0 = ( ( ( rtP .
Constant_Value_ckovqqesxd - otiigwfvqy * otiigwfvqy ) - cu * cu ) * rtP .
Gain2_Gain_pyvsmmmr0o * lyw5zuxpkh [ 0 ] + ( ovpn3bsi5w * otiigwfvqy + u * cu
) * rtP . Gain_Gain_kpmqxdzy5m * lyw5zuxpkh [ 1 ] ) + ( ovpn3bsi5w * cu - u *
otiigwfvqy ) * rtP . Gain1_Gain_k3bjbhd2mm * lyw5zuxpkh [ 2 ] ; omrvjcewtk =
( ( ( rtP . Constant_Value_og0eeytiqd - ovpn3bsi5w * ovpn3bsi5w ) - cu * cu )
* rtP . Gain2_Gain_gvo2u1fvu1 * lyw5zuxpkh [ 1 ] + ( ovpn3bsi5w * otiigwfvqy
- u * cu ) * rtP . Gain_Gain_bsruw13utp * lyw5zuxpkh [ 0 ] ) + ( u *
ovpn3bsi5w + otiigwfvqy * cu ) * rtP . Gain1_Gain_gox4r1jkwy * lyw5zuxpkh [ 2
] ; bf1axylr5a = ( ( ovpn3bsi5w * cu + u * otiigwfvqy ) * rtP .
Gain_Gain_b0hzjatx0r * lyw5zuxpkh [ 0 ] + ( otiigwfvqy * cu - u * ovpn3bsi5w
) * rtP . Gain1_Gain_i30g2qbzrq * lyw5zuxpkh [ 1 ] ) + ( ( rtP .
Constant_Value_dxdbvme4z2 - ovpn3bsi5w * ovpn3bsi5w ) - otiigwfvqy *
otiigwfvqy ) * rtP . Gain2_Gain_p5meiylvde * lyw5zuxpkh [ 2 ] ; lkjrchjyiy (
rtP . arm , myjibr0vt0 , omrvjcewtk , bf1axylr5a , & rtB . c5rolz011g ) ; if
( ssIsModeUpdateTimeStep ( rtS ) ) { srUpdateBC ( rtDW . azyx1ts0yu ) ; } }
memcpy ( & h1gu4wqhux [ 0 ] , & rtP . I [ 0 ] , 9U * sizeof ( real_T ) ) ;
elhmhs4fto [ 0 ] = ( ono5ii4s3b_idx_1 * gomxyom0vc - jwppuzxlko *
ono5ii4s3b_idx_2 ) + kclbezm4gf [ 0 ] ; elhmhs4fto [ 1 ] = ( k50kzncrsl *
ono5ii4s3b_idx_2 - ono5ii4s3b_idx_0 * gomxyom0vc ) + kclbezm4gf [ 1 ] ;
elhmhs4fto [ 2 ] = ( ono5ii4s3b_idx_0 * jwppuzxlko - k50kzncrsl *
ono5ii4s3b_idx_1 ) + kclbezm4gf [ 2 ] ; b [ 0 ] = 0.0 ; b [ 3 ] = - rtB .
gyoxzzwqiz [ 2 ] ; b [ 6 ] = rtB . gyoxzzwqiz [ 1 ] ; b [ 1 ] = rtB .
gyoxzzwqiz [ 2 ] ; b [ 4 ] = 0.0 ; b [ 7 ] = - rtB . gyoxzzwqiz [ 0 ] ; b [ 2
] = - rtB . gyoxzzwqiz [ 1 ] ; b [ 5 ] = rtB . gyoxzzwqiz [ 0 ] ; b [ 8 ] =
0.0 ; for ( i = 0 ; i < 3 ; i ++ ) { kclbezm4gf [ i ] = ( ( rtP . I [ i + 3 ]
* rtB . gyoxzzwqiz [ 1 ] + rtP . I [ i ] * rtB . gyoxzzwqiz [ 0 ] ) + rtP . I
[ i + 6 ] * rtB . gyoxzzwqiz [ 2 ] ) + rtB . oqvw4bmbeg [ i ] ; } for ( i = 0
; i < 3 ; i ++ ) { lyw5zuxpkh [ i ] = ( ( ( ( rtB . c5rolz011g . c1nd5nsrgs [
i ] + rtB . jclektca5o . aupbtlrqjk [ i ] ) + rtB . b5ehs0zt32 [ i ] ) + rtB
. l15tbbx15x . c1nd5nsrgs [ i ] ) + elhmhs4fto [ i ] ) - ( ( b [ i + 3 ] *
kclbezm4gf [ 1 ] + b [ i ] * kclbezm4gf [ 0 ] ) + b [ i + 6 ] * kclbezm4gf [
2 ] ) ; } kmx = 0 ; i = 1 ; r3 = 2 ; u = muDoubleScalarAbs ( rtP . I [ 0 ] )
; cu = muDoubleScalarAbs ( rtP . I [ 1 ] ) ; if ( cu > u ) { u = cu ; kmx = 1
; i = 0 ; } if ( muDoubleScalarAbs ( rtP . I [ 2 ] ) > u ) { kmx = 2 ; i = 1
; r3 = 0 ; } h1gu4wqhux [ i ] = rtP . I [ i ] / rtP . I [ kmx ] ; h1gu4wqhux
[ r3 ] /= h1gu4wqhux [ kmx ] ; h1gu4wqhux [ i + 3 ] -= h1gu4wqhux [ kmx + 3 ]
* h1gu4wqhux [ i ] ; h1gu4wqhux [ r3 + 3 ] -= h1gu4wqhux [ kmx + 3 ] *
h1gu4wqhux [ r3 ] ; h1gu4wqhux [ i + 6 ] -= h1gu4wqhux [ kmx + 6 ] *
h1gu4wqhux [ i ] ; h1gu4wqhux [ r3 + 6 ] -= h1gu4wqhux [ kmx + 6 ] *
h1gu4wqhux [ r3 ] ; if ( muDoubleScalarAbs ( h1gu4wqhux [ r3 + 3 ] ) >
muDoubleScalarAbs ( h1gu4wqhux [ i + 3 ] ) ) { nc = i ; i = r3 ; r3 = nc ; }
h1gu4wqhux [ r3 + 3 ] /= h1gu4wqhux [ i + 3 ] ; h1gu4wqhux [ r3 + 6 ] -=
h1gu4wqhux [ r3 + 3 ] * h1gu4wqhux [ i + 6 ] ; rtB . a5ybxummfl [ 1 ] =
lyw5zuxpkh [ i ] - lyw5zuxpkh [ kmx ] * h1gu4wqhux [ i ] ; rtB . a5ybxummfl [
2 ] = ( lyw5zuxpkh [ r3 ] - lyw5zuxpkh [ kmx ] * h1gu4wqhux [ r3 ] ) -
h1gu4wqhux [ r3 + 3 ] * rtB . a5ybxummfl [ 1 ] ; rtB . a5ybxummfl [ 2 ] /=
h1gu4wqhux [ r3 + 6 ] ; rtB . a5ybxummfl [ 0 ] = lyw5zuxpkh [ kmx ] -
h1gu4wqhux [ kmx + 6 ] * rtB . a5ybxummfl [ 2 ] ; rtB . a5ybxummfl [ 1 ] -=
h1gu4wqhux [ i + 6 ] * rtB . a5ybxummfl [ 2 ] ; rtB . a5ybxummfl [ 1 ] /=
h1gu4wqhux [ i + 3 ] ; rtB . a5ybxummfl [ 0 ] -= h1gu4wqhux [ kmx + 3 ] * rtB
. a5ybxummfl [ 1 ] ; rtB . a5ybxummfl [ 0 ] /= h1gu4wqhux [ kmx ] ; tmp [ 0 ]
= 0.0 ; tmp [ 4 ] = 0.5 * - rtB . gyoxzzwqiz [ 0 ] ; tmp [ 8 ] = 0.5 * - rtB
. gyoxzzwqiz [ 1 ] ; tmp [ 12 ] = 0.5 * - rtB . gyoxzzwqiz [ 2 ] ; tmp [ 1 ]
= 0.5 * rtB . gyoxzzwqiz [ 0 ] ; tmp [ 5 ] = 0.0 ; tmp [ 9 ] = 0.5 * rtB .
gyoxzzwqiz [ 2 ] ; tmp [ 13 ] = 0.5 * - rtB . gyoxzzwqiz [ 1 ] ; tmp [ 2 ] =
0.5 * rtB . gyoxzzwqiz [ 1 ] ; tmp [ 6 ] = 0.5 * - rtB . gyoxzzwqiz [ 2 ] ;
tmp [ 10 ] = 0.0 ; tmp [ 14 ] = 0.5 * rtB . gyoxzzwqiz [ 0 ] ; tmp [ 3 ] =
0.5 * rtB . gyoxzzwqiz [ 2 ] ; tmp [ 7 ] = 0.5 * rtB . gyoxzzwqiz [ 1 ] ; tmp
[ 11 ] = 0.5 * - rtB . gyoxzzwqiz [ 0 ] ; tmp [ 15 ] = 0.0 ; for ( i = 0 ; i
<= 2 ; i += 2 ) { _mm_storeu_pd ( & rtB . eij4bqg1qu [ i ] , _mm_set1_pd (
0.0 ) ) ; tmp_p = _mm_loadu_pd ( & tmp [ i ] ) ; tmp_e = _mm_loadu_pd ( & rtB
. eij4bqg1qu [ i ] ) ; _mm_storeu_pd ( & rtB . eij4bqg1qu [ i ] , _mm_add_pd
( _mm_mul_pd ( tmp_p , _mm_set1_pd ( rtB . jr21nlhhbn [ 0 ] ) ) , tmp_e ) ) ;
tmp_p = _mm_loadu_pd ( & tmp [ i + 4 ] ) ; tmp_e = _mm_loadu_pd ( & rtB .
eij4bqg1qu [ i ] ) ; _mm_storeu_pd ( & rtB . eij4bqg1qu [ i ] , _mm_add_pd (
_mm_mul_pd ( tmp_p , _mm_set1_pd ( rtB . jr21nlhhbn [ 1 ] ) ) , tmp_e ) ) ;
tmp_p = _mm_loadu_pd ( & tmp [ i + 8 ] ) ; tmp_e = _mm_loadu_pd ( & rtB .
eij4bqg1qu [ i ] ) ; _mm_storeu_pd ( & rtB . eij4bqg1qu [ i ] , _mm_add_pd (
_mm_mul_pd ( tmp_p , _mm_set1_pd ( rtB . jr21nlhhbn [ 2 ] ) ) , tmp_e ) ) ;
tmp_p = _mm_loadu_pd ( & tmp [ i + 12 ] ) ; tmp_e = _mm_loadu_pd ( & rtB .
eij4bqg1qu [ i ] ) ; _mm_storeu_pd ( & rtB . eij4bqg1qu [ i ] , _mm_add_pd (
_mm_mul_pd ( tmp_p , _mm_set1_pd ( rtB . jr21nlhhbn [ 3 ] ) ) , tmp_e ) ) ; }
if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . nljkudwtrt [ 0 ] = rtDW .
i3rfdszits [ 0 ] ; rtB . nljkudwtrt [ 1 ] = rtDW . i3rfdszits [ 1 ] ; rtB .
nljkudwtrt [ 2 ] = rtDW . i3rfdszits [ 2 ] ; } for ( i = 0 ; i < 3 ; i ++ ) {
rtB . ht411kslhv [ i ] = ( ( ( rtP . GYRO_b2c [ i + 3 ] * irzywnigjr_idx_1 +
rtP . GYRO_b2c [ i ] * irzywnigjr_idx_0 ) + rtP . GYRO_b2c [ i + 6 ] *
irzywnigjr_idx_2 ) * rtP . rad2deg_Gain_i0zxrskrml + rtB . nljkudwtrt [ i ] )
+ ( rtP . b0degsec_Value [ i ] + rtX . l0nfea2luh [ i ] ) ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . ikgewnxpow [ 0 ] = rtDW . achzjspzj0
[ 0 ] ; rtB . ikgewnxpow [ 1 ] = rtDW . achzjspzj0 [ 1 ] ; rtB . ikgewnxpow [
2 ] = rtDW . achzjspzj0 [ 2 ] ; } n4mcthnbsb ( rtP . GAS_b2c , i3r45wjfj2 ,
lit5wfpqiy , mu3v2yavfb , & rtB . py0l0jdlqp ) ; if ( rtB . lrdfz5anhg [ 2 ]
>= rtP . Switch_Threshold ) { otiigwfvqy = g2acauyoyt ; } else { otiigwfvqy =
rtP . Constant_Value_g3sjkewgl1 ; } rtB . geuyf21jdw = rtP . RW_Rsc *
otiigwfvqy * rtP . RW_Gamp ; rtB . hfnierhiih = 1.0 / rtP . RW_J * T ; if (
rtB . d2nlp5u0iz [ 2 ] >= rtP . Switch_Threshold_a5rkjww04l ) { otiigwfvqy =
i4jz3egckp ; } else { otiigwfvqy = rtP . Constant_Value_ovuyhiuyim ; } rtB .
ahgjrqaame = rtP . RW_Rsc * otiigwfvqy * rtP . RW_Gamp ; rtB . e3dq3kgfi1 =
1.0 / rtP . RW_J * ea ; if ( rtB . cvndu2lgp0 [ 2 ] >= rtP .
Switch_Threshold_eczahcudx1 ) { otiigwfvqy = hxeyppvwpl ; } else { otiigwfvqy
= rtP . Constant_Value_br1klnkrdq ; } rtB . lyqxqxi2xc = rtP . RW_Rsc *
otiigwfvqy * rtP . RW_Gamp ; rtB . jbyqlkik0e = 1.0 / rtP . RW_J * ci ; if (
rtB . mslzotztaf [ 2 ] >= rtP . Switch_Threshold_mxo352pg2c ) { otiigwfvqy =
j4xyasklvt ; } else { otiigwfvqy = rtP . Constant_Value_kibc2xmwm0 ; } rtB .
owuvzpfz25 = rtP . RW_Rsc * otiigwfvqy * rtP . RW_Gamp ; rtB . ddje2kvmhp =
1.0 / rtP . RW_J * e ; rtB . gsio300bjg = ssGetT ( rtS ) ; if (
ssIsSpecialSampleHit ( rtS , 2 , 0 , 0 ) ) { rtB . i34t1ktiub = rtB .
gsio300bjg ; } } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { MdlOutputsTID2 ( tid
) ; } UNUSED_PARAMETER ( tid ) ; } void MdlOutputsTID2 ( int_T tid ) { {
SimStruct * rts = ssGetSFunction ( rtS , 15 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:537" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 2 <= 1 ) && gbl_raccel_tid01eq ? 0 : 2 ) ; } }
UNUSED_PARAMETER ( tid ) ; } void MdlOutputsTID3 ( int_T tid ) { real_T
b0qmo3mcfw ; real_T blb31xqtpm ; real_T laz05qfqpg ; real_T ow02ipltxm ;
int32_T i ; rtB . p4vsv1mu0t = rtP . F107_Value ; for ( i = 0 ; i < 7 ; i ++
) { rtB . blzsybl1pb [ i ] = rtP . aph_Value [ i ] ; } memcpy ( & rtB .
nspxciplv0 [ 0 ] , & rtP . flag_Value [ 0 ] , 23U * sizeof ( real_T ) ) ; if
( ssIsModeUpdateTimeStep ( rtS ) ) { srUpdateBC ( rtDW . icv4qsjrec ) ;
srUpdateBC ( rtDW . ggsva4qu4a ) ; srUpdateBC ( rtDW . kddtry4ekq ) ; } for (
i = 0 ; i < 6 ; i ++ ) { rtB . lzmaq0diab [ i ] = rtP . ele [ i ] ; } if (
ssIsModeUpdateTimeStep ( rtS ) ) { srUpdateBC ( rtDW . azyx1ts0yu ) ; } {
SimStruct * rts = ssGetSFunction ( rtS , 16 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:541" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 3 <= 1 ) && gbl_raccel_tid01eq ? 0 : 3 ) ; } } rtB .
jg4a0jn2o1 [ 0 ] = rtB . j3kezx3yvk [ 0 ] * rtP . MTQ_c2b [ 0 ] ; rtB .
jg4a0jn2o1 [ 1 ] = rtB . j3kezx3yvk [ 1 ] * rtP . MTQ_c2b [ 1 ] ; rtB .
jg4a0jn2o1 [ 2 ] = rtB . j3kezx3yvk [ 2 ] * rtP . MTQ_c2b [ 2 ] ; { SimStruct
* rts = ssGetSFunction ( rtS , 17 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:542" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 3 <= 1 ) && gbl_raccel_tid01eq ? 0 : 3 ) ; } } { SimStruct
* rts = ssGetSFunction ( rtS , 18 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:543" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 3 <= 1 ) && gbl_raccel_tid01eq ? 0 : 3 ) ; } } { SimStruct
* rts = ssGetSFunction ( rtS , 19 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:544" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 3 <= 1 ) && gbl_raccel_tid01eq ? 0 : 3 ) ; } } { SimStruct
* rts = ssGetSFunction ( rtS , 20 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:545" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * , int ) = rts -> modelMethods . sFcn .
mdlOutputs . level2 ; sfcnLoader_separateComplexHandler_withTID ( rts ,
sfcnMethodPtr , ( 3 <= 1 ) && gbl_raccel_tid01eq ? 0 : 3 ) ; } } ow02ipltxm =
muDoubleScalarSqrt ( ( ( rtP . STT1_b2c_quat [ 0 ] * rtP . STT1_b2c_quat [ 0
] + rtP . STT1_b2c_quat [ 1 ] * rtP . STT1_b2c_quat [ 1 ] ) + rtP .
STT1_b2c_quat [ 2 ] * rtP . STT1_b2c_quat [ 2 ] ) + rtP . STT1_b2c_quat [ 3 ]
* rtP . STT1_b2c_quat [ 3 ] ) ; blb31xqtpm = rtP . STT1_b2c_quat [ 3 ] /
ow02ipltxm ; b0qmo3mcfw = rtP . STT1_b2c_quat [ 2 ] / ow02ipltxm ; laz05qfqpg
= rtP . STT1_b2c_quat [ 1 ] / ow02ipltxm ; ow02ipltxm = rtP . STT1_b2c_quat [
0 ] / ow02ipltxm ; rtB . ghrb02xtti [ 0 ] = ( ( ow02ipltxm * ow02ipltxm +
laz05qfqpg * laz05qfqpg ) - b0qmo3mcfw * b0qmo3mcfw ) - blb31xqtpm *
blb31xqtpm ; rtB . ghrb02xtti [ 1 ] = ( laz05qfqpg * b0qmo3mcfw - blb31xqtpm
* ow02ipltxm ) * rtP . Gain_Gain_o54eldgojd ; rtB . ghrb02xtti [ 2 ] = (
ow02ipltxm * b0qmo3mcfw + laz05qfqpg * blb31xqtpm ) * rtP .
Gain_Gain_jzbglr3iwn ; rtB . ghrb02xtti [ 3 ] = ( blb31xqtpm * ow02ipltxm +
laz05qfqpg * b0qmo3mcfw ) * rtP . Gain_Gain_jiwysirinb ; rtB . ghrb02xtti [ 4
] = ( ( ow02ipltxm * ow02ipltxm - laz05qfqpg * laz05qfqpg ) + b0qmo3mcfw *
b0qmo3mcfw ) - blb31xqtpm * blb31xqtpm ; rtB . ghrb02xtti [ 5 ] = (
b0qmo3mcfw * blb31xqtpm - ow02ipltxm * laz05qfqpg ) * rtP .
Gain_Gain_ijnc3iled3 ; rtB . ghrb02xtti [ 6 ] = ( laz05qfqpg * blb31xqtpm -
ow02ipltxm * b0qmo3mcfw ) * rtP . Gain_Gain_gueaxs1w4d ; rtB . ghrb02xtti [ 7
] = ( ow02ipltxm * laz05qfqpg + b0qmo3mcfw * blb31xqtpm ) * rtP .
Gain_Gain_gdjmrybomw ; rtB . ghrb02xtti [ 8 ] = ( ( ow02ipltxm * ow02ipltxm -
laz05qfqpg * laz05qfqpg ) - b0qmo3mcfw * b0qmo3mcfw ) + blb31xqtpm *
blb31xqtpm ; if ( rtB . lrdfz5anhg [ 1 ] >= rtP . Switch2_Threshold ) {
ow02ipltxm = rtP . Constant2_Value_jyuv2gy0ao ; } else { ow02ipltxm = rtP .
Constant3_Value_axvubao2wd ; } rtB . llfqz3cih1 = ow02ipltxm * rtB .
lrdfz5anhg [ 3 ] ; if ( rtB . d2nlp5u0iz [ 1 ] >= rtP .
Switch2_Threshold_hj15nt1i3x ) { ow02ipltxm = rtP .
Constant2_Value_pdtexc4kgl ; } else { ow02ipltxm = rtP .
Constant3_Value_ds1jzpwkjt ; } rtB . euwsxn4aph = ow02ipltxm * rtB .
d2nlp5u0iz [ 3 ] ; if ( rtB . cvndu2lgp0 [ 1 ] >= rtP .
Switch2_Threshold_f3oy1s34eo ) { ow02ipltxm = rtP .
Constant2_Value_lepgnru1ev ; } else { ow02ipltxm = rtP .
Constant3_Value_pq0io1rx2d ; } rtB . kiyg1swe1h = ow02ipltxm * rtB .
cvndu2lgp0 [ 3 ] ; if ( rtB . mslzotztaf [ 1 ] >= rtP .
Switch2_Threshold_fnlhdgazir ) { ow02ipltxm = rtP .
Constant2_Value_oaj3bo5322 ; } else { ow02ipltxm = rtP .
Constant3_Value_ihqrcdemxt ; } rtB . el4rhtecud = ow02ipltxm * rtB .
mslzotztaf [ 3 ] ; UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T tid )
{ if ( ssIsContinuousTask ( rtS , 0 ) ) { rtDW . cu35sqihey = 0 ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . bya5fxrz4g = ( rtP .
UniformRandomNumber_Maximum - rtP . UniformRandomNumber_Minimum ) *
rt_urand_Upu32_Yd_f_pw_snf ( & rtDW . mc4jx3i45v ) + rtP .
UniformRandomNumber_Minimum ; rtDW . ldpiguzau3 = muDoubleScalarSqrt ( rtP .
NSAS_x_noise * rtP . NSAS_x_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
eqyhiq4b21 ) + rtP . noise_Mean ; rtDW . jx2njiskco = muDoubleScalarSqrt (
rtP . NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( &
rtDW . pvrk0p3rm1 ) + rtP . noise1_Mean_gvm1mdzxhn ; rtDW . fg3gr5w1yf =
muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP . NSAS_x_noise ) *
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . jlc5fbv0er ) + rtP .
noise_Mean_ieihuy3dfl ; rtDW . l0mqdwlhk0 = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
mcbywo0nsz ) + rtP . noise1_Mean_dss5wuzq4c ; rtDW . b5i1u5nxk5 =
muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP . NSAS_x_noise ) *
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . izuwdoquaq ) + rtP .
noise_Mean_frav3j55dx ; rtDW . ik23rulsvu = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
iy3vcqbba5 ) + rtP . noise1_Mean_mtptilkq10 ; rtDW . ia3ohifukf =
muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP . NSAS_x_noise ) *
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . inevc2d42p ) + rtP .
noise_Mean_gbwkny3l3m ; rtDW . ewzxpp1cyz = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
omztnckksa ) + rtP . noise1_Mean_k2frfueqdx ; rtDW . hdjjo4r4gm =
muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP . NSAS_x_noise ) *
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . peboqqfifh ) + rtP .
noise_Mean_fjgbzgisby ; rtDW . coji3apumi = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
hjlfer4jb5 ) + rtP . noise1_Mean_jkwutj3nv4 ; rtDW . m2ylj5cu2h =
muDoubleScalarSqrt ( rtP . NSAS_x_noise * rtP . NSAS_x_noise ) *
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . bhy4lqzamt ) + rtP .
noise_Mean_hueo1gemyg ; rtDW . dbnkttelok = muDoubleScalarSqrt ( rtP .
NSAS_y_noise * rtP . NSAS_y_noise ) * rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW .
l3fdu4jify ) + rtP . noise1_Mean_m2yixhjiff ; rtDW . bpg2iofpcz = ( rtP .
GPS_time_noise - rtP . noise3_Minimum ) * rt_urand_Upu32_Yd_f_pw_snf ( & rtDW
. eh3i2huuk3 ) + rtP . noise3_Minimum ; rtDW . hrquh23lee [ 0 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjzrcidvjf [ 0 ] ) * rtP .
noise1_StdDev [ 0 ] + rtP . noise1_Mean [ 0 ] ; rtDW . fzlqp4iexm [ 0 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dplhf1lj21 [ 0 ] ) * rtP . noise_StdDev
[ 0 ] + rtP . noise_Mean_m211emgdl3 [ 0 ] ; rtDW . hsxmncoiha [ 0 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjjgprkxtu [ 0 ] ) * rtP .
RandomNumber_StdDev [ 0 ] + rtP . RandomNumber_Mean [ 0 ] ; rtDW . i3rfdszits
[ 0 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dslhvlg4ym [ 0 ] ) * rtP .
nvdegsec_StdDev [ 0 ] + rtP . nvdegsec_Mean [ 0 ] ; rtDW . achzjspzj0 [ 0 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . czp4qnh0py [ 0 ] ) * rtP .
nudegsec2_StdDev [ 0 ] + rtP . nudegsec2_Mean [ 0 ] ; rtDW . hrquh23lee [ 1 ]
= rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjzrcidvjf [ 1 ] ) * rtP .
noise1_StdDev [ 1 ] + rtP . noise1_Mean [ 1 ] ; rtDW . fzlqp4iexm [ 1 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dplhf1lj21 [ 1 ] ) * rtP . noise_StdDev
[ 1 ] + rtP . noise_Mean_m211emgdl3 [ 1 ] ; rtDW . hsxmncoiha [ 1 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjjgprkxtu [ 1 ] ) * rtP .
RandomNumber_StdDev [ 1 ] + rtP . RandomNumber_Mean [ 1 ] ; rtDW . i3rfdszits
[ 1 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dslhvlg4ym [ 1 ] ) * rtP .
nvdegsec_StdDev [ 1 ] + rtP . nvdegsec_Mean [ 1 ] ; rtDW . achzjspzj0 [ 1 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . czp4qnh0py [ 1 ] ) * rtP .
nudegsec2_StdDev [ 1 ] + rtP . nudegsec2_Mean [ 1 ] ; rtDW . hrquh23lee [ 2 ]
= rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjzrcidvjf [ 2 ] ) * rtP .
noise1_StdDev [ 2 ] + rtP . noise1_Mean [ 2 ] ; rtDW . fzlqp4iexm [ 2 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dplhf1lj21 [ 2 ] ) * rtP . noise_StdDev
[ 2 ] + rtP . noise_Mean_m211emgdl3 [ 2 ] ; rtDW . hsxmncoiha [ 2 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kjjgprkxtu [ 2 ] ) * rtP .
RandomNumber_StdDev [ 2 ] + rtP . RandomNumber_Mean [ 2 ] ; rtDW . i3rfdszits
[ 2 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dslhvlg4ym [ 2 ] ) * rtP .
nvdegsec_StdDev [ 2 ] + rtP . nvdegsec_Mean [ 2 ] ; rtDW . achzjspzj0 [ 2 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . czp4qnh0py [ 2 ] ) * rtP .
nudegsec2_StdDev [ 2 ] + rtP . nudegsec2_Mean [ 2 ] ; } } UNUSED_PARAMETER (
tid ) ; } void MdlUpdateTID2 ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; }
void MdlUpdateTID3 ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void
MdlDerivatives ( void ) { XDot * _rtXdot ; int32_T i ; _rtXdot = ( ( XDot * )
ssGetdX ( rtS ) ) ; _rtXdot -> hjkn3n4lly [ 0 ] = rtB . a5ybxummfl [ 0 ] ;
_rtXdot -> hjkn3n4lly [ 1 ] = rtB . a5ybxummfl [ 1 ] ; _rtXdot -> hjkn3n4lly
[ 2 ] = rtB . a5ybxummfl [ 2 ] ; for ( i = 0 ; i < 6 ; i ++ ) { _rtXdot ->
oxovzkyrgp [ i ] = rtB . gs20g4hobc [ i ] ; } _rtXdot -> pcdkwn41rb [ 0 ] =
rtB . eij4bqg1qu [ 0 ] ; _rtXdot -> pcdkwn41rb [ 1 ] = rtB . eij4bqg1qu [ 1 ]
; _rtXdot -> pcdkwn41rb [ 2 ] = rtB . eij4bqg1qu [ 2 ] ; _rtXdot ->
pcdkwn41rb [ 3 ] = rtB . eij4bqg1qu [ 3 ] ; _rtXdot -> l50b0cuk2h = rtP .
TransferFcn1_A * rtX . l50b0cuk2h ; _rtXdot -> l50b0cuk2h += rtB . ahgjrqaame
; _rtXdot -> b4ena3lr0n = rtB . e3dq3kgfi1 ; _rtXdot -> lbdfwq1i3y = rtP .
TransferFcn1_A_dpe12qdgeu * rtX . lbdfwq1i3y ; _rtXdot -> lbdfwq1i3y += rtB .
geuyf21jdw ; _rtXdot -> fnheb54sgb = rtB . hfnierhiih ; _rtXdot -> muv5xwjpjd
= rtP . TransferFcn1_A_iljtckl0vf * rtX . muv5xwjpjd ; _rtXdot -> muv5xwjpjd
+= rtB . lyqxqxi2xc ; _rtXdot -> argwmtgb5v = rtB . jbyqlkik0e ; _rtXdot ->
bxdhuzrxz2 = rtP . TransferFcn1_A_bf2c2hk3jc * rtX . bxdhuzrxz2 ; _rtXdot ->
bxdhuzrxz2 += rtB . owuvzpfz25 ; _rtXdot -> cmyui1ww54 = rtB . ddje2kvmhp ;
_rtXdot -> i1iguten22 [ 0 ] = rtP . TransferFcn_A [ 0 ] * rtX . i1iguten22 [
0 ] ; _rtXdot -> i1iguten22 [ 0 ] += rtP . TransferFcn_A [ 1 ] * rtX .
i1iguten22 [ 1 ] ; _rtXdot -> i1iguten22 [ 1 ] = rtX . i1iguten22 [ 0 ] ;
_rtXdot -> i1iguten22 [ 0 ] += rtB . ht411kslhv [ 0 ] ; _rtXdot -> pkf1lgikiz
[ 0 ] = rtP . TransferFcn1_A_if5catdafx [ 0 ] * rtX . pkf1lgikiz [ 0 ] ;
_rtXdot -> pkf1lgikiz [ 0 ] += rtP . TransferFcn1_A_if5catdafx [ 1 ] * rtX .
pkf1lgikiz [ 1 ] ; _rtXdot -> pkf1lgikiz [ 1 ] = rtX . pkf1lgikiz [ 0 ] ;
_rtXdot -> pkf1lgikiz [ 0 ] += rtB . ht411kslhv [ 1 ] ; _rtXdot -> f3jtaj41sb
[ 0 ] = rtP . TransferFcn2_A [ 0 ] * rtX . f3jtaj41sb [ 0 ] ; _rtXdot ->
f3jtaj41sb [ 0 ] += rtP . TransferFcn2_A [ 1 ] * rtX . f3jtaj41sb [ 1 ] ;
_rtXdot -> f3jtaj41sb [ 1 ] = rtX . f3jtaj41sb [ 0 ] ; _rtXdot -> f3jtaj41sb
[ 0 ] += rtB . ht411kslhv [ 2 ] ; _rtXdot -> ae0okdyidm = rtP .
TransferFcn_A_c34clvpx4a * rtX . ae0okdyidm ; _rtXdot -> ae0okdyidm += rtB .
py0l0jdlqp . owg3qz0vb0 [ 0 ] ; _rtXdot -> cok521zc4f = rtP .
TransferFcn1_A_lrz1uxhxld * rtX . cok521zc4f ; _rtXdot -> cok521zc4f += rtB .
py0l0jdlqp . owg3qz0vb0 [ 1 ] ; _rtXdot -> pf4hzftljn = rtP .
TransferFcn2_A_pnihap0iyy * rtX . pf4hzftljn ; _rtXdot -> pf4hzftljn += rtB .
py0l0jdlqp . owg3qz0vb0 [ 2 ] ; _rtXdot -> ek1dcgndv4 = rtP .
TransferFcn_A_aashwww0mz * rtX . ek1dcgndv4 ; _rtXdot -> ek1dcgndv4 += rtB .
jg4a0jn2o1 [ 0 ] ; _rtXdot -> iyvywkyjkt = rtP . TransferFcn_A_gmkfu1bp5e *
rtX . iyvywkyjkt ; _rtXdot -> iyvywkyjkt += rtB . jg4a0jn2o1 [ 1 ] ; _rtXdot
-> cscwx5acjj = rtP . TransferFcn_A_axh3uxseti * rtX . cscwx5acjj ; _rtXdot
-> cscwx5acjj += rtB . jg4a0jn2o1 [ 2 ] ; _rtXdot -> l0nfea2luh [ 0 ] = rtB .
ikgewnxpow [ 0 ] ; _rtXdot -> l0nfea2luh [ 1 ] = rtB . ikgewnxpow [ 1 ] ;
_rtXdot -> l0nfea2luh [ 2 ] = rtB . ikgewnxpow [ 2 ] ; } void MdlProjection (
void ) { } void MdlTerminate ( void ) { { SimStruct * rts = ssGetSFunction (
rtS , 0 ) ; { static const char * blockSIDForSFcnLoader =
"SILS_20241709:424:2443:1728" ; sfcnLoader_setCurrentSFcnBlockSID (
blockSIDForSFcnLoader ) ; void ( * sfcnMethodPtr ) ( SimStruct * ) = rts ->
modelMethods . sFcn . mdlTerminate ; sfcnLoader_separateComplexHandler ( rts
, sfcnMethodPtr ) ; } } { SimStruct * rts = ssGetSFunction ( rtS , 16 ) ; {
static const char * blockSIDForSFcnLoader = "SILS_20241709:541" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 17 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:542" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 18 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:543" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 19 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:544" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 20 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:545" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 1 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:552" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 2 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:549" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 3 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:555" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 4 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:558" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 5 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:523" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 6 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:517" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 7 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:519" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 8 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:520" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 9 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:521" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 10 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:630" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 11 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:631" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 12 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:632" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 13 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:518" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 14 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:522" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { SimStruct *
rts = ssGetSFunction ( rtS , 15 ) ; { static const char *
blockSIDForSFcnLoader = "SILS_20241709:537" ;
sfcnLoader_setCurrentSFcnBlockSID ( blockSIDForSFcnLoader ) ; void ( *
sfcnMethodPtr ) ( SimStruct * ) = rts -> modelMethods . sFcn . mdlTerminate ;
sfcnLoader_separateComplexHandler ( rts , sfcnMethodPtr ) ; } } { if ( rtDW .
lqwrbhd21x . AQHandles ) { sdiTerminateStreaming ( & rtDW . lqwrbhd21x .
AQHandles ) ; } } { if ( rtDW . ko5el0avio . AQHandles ) {
sdiTerminateStreaming ( & rtDW . ko5el0avio . AQHandles ) ; } } { if ( rtDW .
d11ycakunl . AQHandles ) { sdiTerminateStreaming ( & rtDW . d11ycakunl .
AQHandles ) ; } } } static void mr_SILS_20241709_cacheDataAsMxArray ( mxArray
* destArray , mwIndex i , int j , const void * srcData , size_t numBytes ) ;
static void mr_SILS_20241709_cacheDataAsMxArray ( mxArray * destArray ,
mwIndex i , int j , const void * srcData , size_t numBytes ) { mxArray *
newArray = mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes ,
mxUINT8_CLASS , mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , (
const uint8_T * ) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i ,
j , newArray ) ; } static void mr_SILS_20241709_restoreDataFromMxArray ( void
* destData , const mxArray * srcArray , mwIndex i , int j , size_t numBytes )
; static void mr_SILS_20241709_restoreDataFromMxArray ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( (
uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber (
srcArray , i , j ) ) , numBytes ) ; } static void
mr_SILS_20241709_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i ,
int j , uint_T bitVal ) ; static void mr_SILS_20241709_cacheBitFieldToMxArray
( mxArray * destArray , mwIndex i , int j , uint_T bitVal ) {
mxSetFieldByNumber ( destArray , i , j , mxCreateDoubleScalar ( ( double )
bitVal ) ) ; } static uint_T mr_SILS_20241709_extractBitFieldFromMxArray (
const mxArray * srcArray , mwIndex i , int j , uint_T numBits ) ; static
uint_T mr_SILS_20241709_extractBitFieldFromMxArray ( const mxArray * srcArray
, mwIndex i , int j , uint_T numBits ) { const uint_T varVal = ( uint_T )
mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( (
1u << numBits ) - 1u ) ; } static void
mr_SILS_20241709_cacheDataToMxArrayWithOffset ( mxArray * destArray , mwIndex
i , int j , mwIndex offset , const void * srcData , size_t numBytes ) ;
static void mr_SILS_20241709_cacheDataToMxArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_SILS_20241709_restoreDataFromMxArrayWithOffset ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) ; static void mr_SILS_20241709_restoreDataFromMxArrayWithOffset (
void * destData , const mxArray * srcArray , mwIndex i , int j , mwIndex
offset , size_t numBytes ) { const uint8_T * varData = ( const uint8_T * )
mxGetData ( mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T *
) destData , ( const uint8_T * ) & varData [ offset * numBytes ] , numBytes )
; } static void mr_SILS_20241709_cacheBitFieldToCellArrayWithOffset ( mxArray
* destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static
void mr_SILS_20241709_cacheBitFieldToCellArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) {
mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset ,
mxCreateDoubleScalar ( ( double ) fieldVal ) ) ; } static uint_T
mr_SILS_20241709_extractBitFieldFromCellArrayWithOffset ( const mxArray *
srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static
uint_T mr_SILS_20241709_extractBitFieldFromCellArrayWithOffset ( const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) {
const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell (
mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( (
1u << numBits ) - 1u ) ; } mxArray * mr_SILS_20241709_GetDWork ( ) { static
const char * ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" , "NULL_PrevZCX" , } ;
mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_SILS_20241709_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & ( rtB
) , sizeof ( rtB ) ) ; { static const char * rtdwDataFieldNames [ 53 ] = {
"rtDW.hrquh23lee" , "rtDW.bya5fxrz4g" , "rtDW.ldpiguzau3" , "rtDW.jx2njiskco"
, "rtDW.fg3gr5w1yf" , "rtDW.l0mqdwlhk0" , "rtDW.b5i1u5nxk5" ,
"rtDW.ik23rulsvu" , "rtDW.ia3ohifukf" , "rtDW.ewzxpp1cyz" , "rtDW.hdjjo4r4gm"
, "rtDW.coji3apumi" , "rtDW.m2ylj5cu2h" , "rtDW.dbnkttelok" ,
"rtDW.fzlqp4iexm" , "rtDW.hsxmncoiha" , "rtDW.bpg2iofpcz" , "rtDW.gvdcwkyokb"
, "rtDW.ip0upbstfm" , "rtDW.mmkouxeune" , "rtDW.jeeaiz3533" ,
"rtDW.i3rfdszits" , "rtDW.achzjspzj0" , "rtDW.kjzrcidvjf" , "rtDW.mc4jx3i45v"
, "rtDW.eqyhiq4b21" , "rtDW.pvrk0p3rm1" , "rtDW.jlc5fbv0er" ,
"rtDW.mcbywo0nsz" , "rtDW.izuwdoquaq" , "rtDW.iy3vcqbba5" , "rtDW.inevc2d42p"
, "rtDW.omztnckksa" , "rtDW.peboqqfifh" , "rtDW.hjlfer4jb5" ,
"rtDW.bhy4lqzamt" , "rtDW.l3fdu4jify" , "rtDW.dplhf1lj21" , "rtDW.kjjgprkxtu"
, "rtDW.eh3i2huuk3" , "rtDW.dslhvlg4ym" , "rtDW.czp4qnh0py" ,
"rtDW.cu35sqihey" , "rtDW.azyx1ts0yu" , "rtDW.gxgp4hskcm" , "rtDW.kddtry4ekq"
, "rtDW.ggsva4qu4a" , "rtDW.icv4qsjrec" , "rtDW.hp42fr3fka" ,
"rtDW.kc0x0orqmh" , "rtDW.bdwu52mmaq" , "rtDW.odkn5lgudq" , "rtDW.lqozsqepug"
, } ; mxArray * rtdwData = mxCreateStructMatrix ( 1 , 1 , 53 ,
rtdwDataFieldNames ) ; mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 0
, ( const void * ) & ( rtDW . hrquh23lee ) , sizeof ( rtDW . hrquh23lee ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void * ) & (
rtDW . bya5fxrz4g ) , sizeof ( rtDW . bya5fxrz4g ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const void * ) & (
rtDW . ldpiguzau3 ) , sizeof ( rtDW . ldpiguzau3 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void * ) & (
rtDW . jx2njiskco ) , sizeof ( rtDW . jx2njiskco ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void * ) & (
rtDW . fg3gr5w1yf ) , sizeof ( rtDW . fg3gr5w1yf ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void * ) & (
rtDW . l0mqdwlhk0 ) , sizeof ( rtDW . l0mqdwlhk0 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void * ) & (
rtDW . b5i1u5nxk5 ) , sizeof ( rtDW . b5i1u5nxk5 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 7 , ( const void * ) & (
rtDW . ik23rulsvu ) , sizeof ( rtDW . ik23rulsvu ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 8 , ( const void * ) & (
rtDW . ia3ohifukf ) , sizeof ( rtDW . ia3ohifukf ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 9 , ( const void * ) & (
rtDW . ewzxpp1cyz ) , sizeof ( rtDW . ewzxpp1cyz ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 10 , ( const void * ) &
( rtDW . hdjjo4r4gm ) , sizeof ( rtDW . hdjjo4r4gm ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 11 , ( const void * ) &
( rtDW . coji3apumi ) , sizeof ( rtDW . coji3apumi ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 12 , ( const void * ) &
( rtDW . m2ylj5cu2h ) , sizeof ( rtDW . m2ylj5cu2h ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 13 , ( const void * ) &
( rtDW . dbnkttelok ) , sizeof ( rtDW . dbnkttelok ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 14 , ( const void * ) &
( rtDW . fzlqp4iexm ) , sizeof ( rtDW . fzlqp4iexm ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 15 , ( const void * ) &
( rtDW . hsxmncoiha ) , sizeof ( rtDW . hsxmncoiha ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 16 , ( const void * ) &
( rtDW . bpg2iofpcz ) , sizeof ( rtDW . bpg2iofpcz ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 17 , ( const void * ) &
( rtDW . gvdcwkyokb ) , sizeof ( rtDW . gvdcwkyokb ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 18 , ( const void * ) &
( rtDW . ip0upbstfm ) , sizeof ( rtDW . ip0upbstfm ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 19 , ( const void * ) &
( rtDW . mmkouxeune ) , sizeof ( rtDW . mmkouxeune ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 20 , ( const void * ) &
( rtDW . jeeaiz3533 ) , sizeof ( rtDW . jeeaiz3533 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 21 , ( const void * ) &
( rtDW . i3rfdszits ) , sizeof ( rtDW . i3rfdszits ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 22 , ( const void * ) &
( rtDW . achzjspzj0 ) , sizeof ( rtDW . achzjspzj0 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 23 , ( const void * ) &
( rtDW . kjzrcidvjf ) , sizeof ( rtDW . kjzrcidvjf ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 24 , ( const void * ) &
( rtDW . mc4jx3i45v ) , sizeof ( rtDW . mc4jx3i45v ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 25 , ( const void * ) &
( rtDW . eqyhiq4b21 ) , sizeof ( rtDW . eqyhiq4b21 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 26 , ( const void * ) &
( rtDW . pvrk0p3rm1 ) , sizeof ( rtDW . pvrk0p3rm1 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 27 , ( const void * ) &
( rtDW . jlc5fbv0er ) , sizeof ( rtDW . jlc5fbv0er ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 28 , ( const void * ) &
( rtDW . mcbywo0nsz ) , sizeof ( rtDW . mcbywo0nsz ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 29 , ( const void * ) &
( rtDW . izuwdoquaq ) , sizeof ( rtDW . izuwdoquaq ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 30 , ( const void * ) &
( rtDW . iy3vcqbba5 ) , sizeof ( rtDW . iy3vcqbba5 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 31 , ( const void * ) &
( rtDW . inevc2d42p ) , sizeof ( rtDW . inevc2d42p ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 32 , ( const void * ) &
( rtDW . omztnckksa ) , sizeof ( rtDW . omztnckksa ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 33 , ( const void * ) &
( rtDW . peboqqfifh ) , sizeof ( rtDW . peboqqfifh ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 34 , ( const void * ) &
( rtDW . hjlfer4jb5 ) , sizeof ( rtDW . hjlfer4jb5 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 35 , ( const void * ) &
( rtDW . bhy4lqzamt ) , sizeof ( rtDW . bhy4lqzamt ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 36 , ( const void * ) &
( rtDW . l3fdu4jify ) , sizeof ( rtDW . l3fdu4jify ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 37 , ( const void * ) &
( rtDW . dplhf1lj21 ) , sizeof ( rtDW . dplhf1lj21 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 38 , ( const void * ) &
( rtDW . kjjgprkxtu ) , sizeof ( rtDW . kjjgprkxtu ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 39 , ( const void * ) &
( rtDW . eh3i2huuk3 ) , sizeof ( rtDW . eh3i2huuk3 ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 40 , ( const void * ) &
( rtDW . dslhvlg4ym ) , sizeof ( rtDW . dslhvlg4ym ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 41 , ( const void * ) &
( rtDW . czp4qnh0py ) , sizeof ( rtDW . czp4qnh0py ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 42 , ( const void * ) &
( rtDW . cu35sqihey ) , sizeof ( rtDW . cu35sqihey ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 43 , ( const void * ) &
( rtDW . azyx1ts0yu ) , sizeof ( rtDW . azyx1ts0yu ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 44 , ( const void * ) &
( rtDW . gxgp4hskcm ) , sizeof ( rtDW . gxgp4hskcm ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 45 , ( const void * ) &
( rtDW . kddtry4ekq ) , sizeof ( rtDW . kddtry4ekq ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 46 , ( const void * ) &
( rtDW . ggsva4qu4a ) , sizeof ( rtDW . ggsva4qu4a ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 47 , ( const void * ) &
( rtDW . icv4qsjrec ) , sizeof ( rtDW . icv4qsjrec ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 48 , ( const void * ) &
( rtDW . hp42fr3fka ) , sizeof ( rtDW . hp42fr3fka ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 49 , ( const void * ) &
( rtDW . kc0x0orqmh ) , sizeof ( rtDW . kc0x0orqmh ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 50 , ( const void * ) &
( rtDW . bdwu52mmaq ) , sizeof ( rtDW . bdwu52mmaq ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 51 , ( const void * ) &
( rtDW . odkn5lgudq ) , sizeof ( rtDW . odkn5lgudq ) ) ;
mr_SILS_20241709_cacheDataAsMxArray ( rtdwData , 0 , 52 , ( const void * ) &
( rtDW . lqozsqepug ) , sizeof ( rtDW . lqozsqepug ) ) ; mxSetFieldByNumber (
ssDW , 0 , 1 , rtdwData ) ; } return ssDW ; } void mr_SILS_20241709_SetDWork
( const mxArray * ssDW ) { ( void ) ssDW ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW , 0 , 0
, sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber ( ssDW ,
0 , 1 ) ; mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW .
hrquh23lee ) , rtdwData , 0 , 0 , sizeof ( rtDW . hrquh23lee ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . bya5fxrz4g )
, rtdwData , 0 , 1 , sizeof ( rtDW . bya5fxrz4g ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . ldpiguzau3 )
, rtdwData , 0 , 2 , sizeof ( rtDW . ldpiguzau3 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . jx2njiskco )
, rtdwData , 0 , 3 , sizeof ( rtDW . jx2njiskco ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . fg3gr5w1yf )
, rtdwData , 0 , 4 , sizeof ( rtDW . fg3gr5w1yf ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . l0mqdwlhk0 )
, rtdwData , 0 , 5 , sizeof ( rtDW . l0mqdwlhk0 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . b5i1u5nxk5 )
, rtdwData , 0 , 6 , sizeof ( rtDW . b5i1u5nxk5 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . ik23rulsvu )
, rtdwData , 0 , 7 , sizeof ( rtDW . ik23rulsvu ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . ia3ohifukf )
, rtdwData , 0 , 8 , sizeof ( rtDW . ia3ohifukf ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . ewzxpp1cyz )
, rtdwData , 0 , 9 , sizeof ( rtDW . ewzxpp1cyz ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . hdjjo4r4gm )
, rtdwData , 0 , 10 , sizeof ( rtDW . hdjjo4r4gm ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . coji3apumi )
, rtdwData , 0 , 11 , sizeof ( rtDW . coji3apumi ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . m2ylj5cu2h )
, rtdwData , 0 , 12 , sizeof ( rtDW . m2ylj5cu2h ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . dbnkttelok )
, rtdwData , 0 , 13 , sizeof ( rtDW . dbnkttelok ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . fzlqp4iexm )
, rtdwData , 0 , 14 , sizeof ( rtDW . fzlqp4iexm ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . hsxmncoiha )
, rtdwData , 0 , 15 , sizeof ( rtDW . hsxmncoiha ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . bpg2iofpcz )
, rtdwData , 0 , 16 , sizeof ( rtDW . bpg2iofpcz ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . gvdcwkyokb )
, rtdwData , 0 , 17 , sizeof ( rtDW . gvdcwkyokb ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . ip0upbstfm )
, rtdwData , 0 , 18 , sizeof ( rtDW . ip0upbstfm ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . mmkouxeune )
, rtdwData , 0 , 19 , sizeof ( rtDW . mmkouxeune ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . jeeaiz3533 )
, rtdwData , 0 , 20 , sizeof ( rtDW . jeeaiz3533 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . i3rfdszits )
, rtdwData , 0 , 21 , sizeof ( rtDW . i3rfdszits ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . achzjspzj0 )
, rtdwData , 0 , 22 , sizeof ( rtDW . achzjspzj0 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . kjzrcidvjf )
, rtdwData , 0 , 23 , sizeof ( rtDW . kjzrcidvjf ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . mc4jx3i45v )
, rtdwData , 0 , 24 , sizeof ( rtDW . mc4jx3i45v ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . eqyhiq4b21 )
, rtdwData , 0 , 25 , sizeof ( rtDW . eqyhiq4b21 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . pvrk0p3rm1 )
, rtdwData , 0 , 26 , sizeof ( rtDW . pvrk0p3rm1 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . jlc5fbv0er )
, rtdwData , 0 , 27 , sizeof ( rtDW . jlc5fbv0er ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . mcbywo0nsz )
, rtdwData , 0 , 28 , sizeof ( rtDW . mcbywo0nsz ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . izuwdoquaq )
, rtdwData , 0 , 29 , sizeof ( rtDW . izuwdoquaq ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . iy3vcqbba5 )
, rtdwData , 0 , 30 , sizeof ( rtDW . iy3vcqbba5 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . inevc2d42p )
, rtdwData , 0 , 31 , sizeof ( rtDW . inevc2d42p ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . omztnckksa )
, rtdwData , 0 , 32 , sizeof ( rtDW . omztnckksa ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . peboqqfifh )
, rtdwData , 0 , 33 , sizeof ( rtDW . peboqqfifh ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . hjlfer4jb5 )
, rtdwData , 0 , 34 , sizeof ( rtDW . hjlfer4jb5 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . bhy4lqzamt )
, rtdwData , 0 , 35 , sizeof ( rtDW . bhy4lqzamt ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . l3fdu4jify )
, rtdwData , 0 , 36 , sizeof ( rtDW . l3fdu4jify ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . dplhf1lj21 )
, rtdwData , 0 , 37 , sizeof ( rtDW . dplhf1lj21 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . kjjgprkxtu )
, rtdwData , 0 , 38 , sizeof ( rtDW . kjjgprkxtu ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . eh3i2huuk3 )
, rtdwData , 0 , 39 , sizeof ( rtDW . eh3i2huuk3 ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . dslhvlg4ym )
, rtdwData , 0 , 40 , sizeof ( rtDW . dslhvlg4ym ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . czp4qnh0py )
, rtdwData , 0 , 41 , sizeof ( rtDW . czp4qnh0py ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . cu35sqihey )
, rtdwData , 0 , 42 , sizeof ( rtDW . cu35sqihey ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . azyx1ts0yu )
, rtdwData , 0 , 43 , sizeof ( rtDW . azyx1ts0yu ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . gxgp4hskcm )
, rtdwData , 0 , 44 , sizeof ( rtDW . gxgp4hskcm ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . kddtry4ekq )
, rtdwData , 0 , 45 , sizeof ( rtDW . kddtry4ekq ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . ggsva4qu4a )
, rtdwData , 0 , 46 , sizeof ( rtDW . ggsva4qu4a ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . icv4qsjrec )
, rtdwData , 0 , 47 , sizeof ( rtDW . icv4qsjrec ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . hp42fr3fka )
, rtdwData , 0 , 48 , sizeof ( rtDW . hp42fr3fka ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . kc0x0orqmh )
, rtdwData , 0 , 49 , sizeof ( rtDW . kc0x0orqmh ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . bdwu52mmaq )
, rtdwData , 0 , 50 , sizeof ( rtDW . bdwu52mmaq ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . odkn5lgudq )
, rtdwData , 0 , 51 , sizeof ( rtDW . odkn5lgudq ) ) ;
mr_SILS_20241709_restoreDataFromMxArray ( ( void * ) & ( rtDW . lqozsqepug )
, rtdwData , 0 , 52 , sizeof ( rtDW . lqozsqepug ) ) ; } } mxArray *
mr_SILS_20241709_GetSimStateDisallowedBlocks ( ) { mxArray * data =
mxCreateCellMatrix ( 6 , 3 ) ; mwIndex subs [ 2 ] , offset ; { static const
char * blockType [ 6 ] = { "Scope" , "Scope" , "Scope" , "Scope" , "Scope" ,
"Scope" , } ; static const char * blockPath [ 6 ] = { "SILS_20241709/-Z&S" ,
"SILS_20241709/rate" , "SILS_20241709/rate_xyz" , "SILS_20241709/rw_rate2" ,
"SILS_20241709/wheels" , "SILS_20241709/qd" , } ; static const int reason [ 6
] = { 0 , 0 , 0 , 0 , 0 , 0 , } ; for ( subs [ 0 ] = 0 ; subs [ 0 ] < 6 ; ++
( subs [ 0 ] ) ) { subs [ 1 ] = 0 ; offset = mxCalcSingleSubscript ( data , 2
, subs ) ; mxSetCell ( data , offset , mxCreateString ( blockType [ subs [ 0
] ] ) ) ; subs [ 1 ] = 1 ; offset = mxCalcSingleSubscript ( data , 2 , subs )
; mxSetCell ( data , offset , mxCreateString ( blockPath [ subs [ 0 ] ] ) ) ;
subs [ 1 ] = 2 ; offset = mxCalcSingleSubscript ( data , 2 , subs ) ;
mxSetCell ( data , offset , mxCreateDoubleScalar ( ( double ) reason [ subs [
0 ] ] ) ) ; } } return data ; } void MdlInitializeSizes ( void ) {
ssSetNumContStates ( rtS , 36 ) ; ssSetNumPeriodicContStates ( rtS , 0 ) ;
ssSetNumY ( rtS , 5 ) ; ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS
, 0 ) ; ssSetNumSampleTimes ( rtS , 3 ) ; ssSetNumBlocks ( rtS , 1287 ) ;
ssSetNumBlockIO ( rtS , 161 ) ; ssSetNumBlockParams ( rtS , 628 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.01 ) ; ssSetSampleTime ( rtS , 2 , 0.05 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 0.0 ) ;
ssSetOffsetTime ( rtS , 2 , 0.0 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 2405234056U ) ; ssSetChecksumVal ( rtS , 1 ,
151909971U ) ; ssSetChecksumVal ( rtS , 2 , 1794605402U ) ; ssSetChecksumVal
( rtS , 3 , 3767048926U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; static struct _ssBlkInfo2 blkInfo2 ;
static struct _ssBlkInfoSLSize blkInfoSLSize ; ( void ) memset ( ( char * )
rtS , 0 , sizeof ( SimStruct ) ) ; ( void ) memset ( ( char * ) & mdlInfo , 0
, sizeof ( struct _ssMdlInfo ) ) ; ( void ) memset ( ( char * ) & blkInfo2 ,
0 , sizeof ( struct _ssBlkInfo2 ) ) ; ( void ) memset ( ( char * ) &
blkInfoSLSize , 0 , sizeof ( struct _ssBlkInfoSLSize ) ) ; ssSetBlkInfo2Ptr (
rtS , & blkInfo2 ) ; ssSetBlkInfoSLSizePtr ( rtS , & blkInfoSLSize ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; ssSetExecutionInfo ( rtS ,
executionInfo ) ; slsaAllocOPModelData ( rtS ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; } } mdlSampleHits [ 0 ] = 1 ; ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; } {
static int_T mdlPerTaskSampleHits [ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; ( void
) memset ( ( void * ) & mdlPerTaskSampleHits [ 0 ] , 0 , 3 * 3 * sizeof (
int_T ) ) ; ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] )
; } ssSetSolverMode ( rtS , SOLVER_MODE_MULTITASKING ) ; { ssSetBlockIO ( rtS
, ( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 ,
sizeof ( B ) ) ; } { ssSetY ( rtS , & rtY ) ; ( void ) memset ( & rtY , 0 ,
sizeof ( ExtY ) ) ; ssSetWorkSizeInBytes ( rtS , sizeof ( rtY ) , "YOut" ) ;
} { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ; ( void )
memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = ( void * ) &
rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork , 0 , sizeof
( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset ( ( char_T *
) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS , & dtInfo
) ; dtInfo . numDataTypes = 23 ; dtInfo . dataTypeSizes = & rtDataTypeSizes [
0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ; dtInfo . BTransTable
= & rtBTransTable ; dtInfo . PTransTable = & rtPTransTable ; dtInfo .
dataTypeInfoTable = rtDataTypeInfoTable ; }
SILS_20241709_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS
, true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "SILS_20241709" ) ;
ssSetPath ( rtS , "SILS_20241709" ) ; ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal
( rtS , 10000.0 ) ; ssSetStepSize ( rtS , 0.01 ) ; ssSetFixedStepSize ( rtS ,
0.01 ) ; { static RTWLogInfo rt_DataLoggingInfo ; rt_DataLoggingInfo .
loggingInterval = ( NULL ) ; ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ;
} { { static int_T rt_LoggedStateWidths [ ] = { 3 , 6 , 4 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 3 } ; static int_T
rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static int_T
rt_LoggedStateDimensions [ ] = { 3 , 6 , 4 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
2 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 3 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ;
static int_T rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static
RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) } ; static
const char_T * rt_LoggedStateLabels [ ] = { "CSTATE" , "CSTATE" , "CSTATE" ,
"CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" ,
"CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" ,
"CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" } ; static const char_T *
rt_LoggedStateBlockNames [ ] = {
"SILS_20241709/Environment&Dynamics/RigidBodyDynamics/Integrator1" ,
"SILS_20241709/Environment&Dynamics/OrbitalDynamics/OE_integ" ,
"SILS_20241709/Environment&Dynamics/RigidBodyDynamics/Integrator" ,
"SILS_20241709/three_one_skew/RW2/Transfer Fcn1" ,
"SILS_20241709/three_one_skew/RW2/Integrator" ,
"SILS_20241709/three_one_skew/RW1/Transfer Fcn1" ,
"SILS_20241709/three_one_skew/RW1/Integrator" ,
"SILS_20241709/three_one_skew/RW3/Transfer Fcn1" ,
"SILS_20241709/three_one_skew/RW3/Integrator" ,
"SILS_20241709/three_one_skew/RW4/Transfer Fcn1" ,
"SILS_20241709/three_one_skew/RW4/Integrator" ,
"SILS_20241709/Sensors/GYRO/Transfer Fcn" ,
"SILS_20241709/Sensors/GYRO/Transfer Fcn1" ,
"SILS_20241709/Sensors/GYRO/Transfer Fcn2" ,
"SILS_20241709/Sensors/GAS/Transfer Fcn" ,
"SILS_20241709/Sensors/GAS/Transfer Fcn1" ,
"SILS_20241709/Sensors/GAS/Transfer Fcn2" ,
"SILS_20241709/MTQs/MTQ_1/Transfer Fcn" ,
"SILS_20241709/MTQs/MTQ_2/Transfer Fcn" ,
"SILS_20241709/MTQs/MTQ_3/Transfer Fcn" ,
"SILS_20241709/Sensors/GYRO/Integrator" } ; static const char_T *
rt_LoggedStateNames [ ] = { "" , "" , "" , "" , "" , "" , "" , "" , "" , "" ,
"" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" } ; static boolean_T
rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static RTWLogDataTypeConvert
rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 ,
1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } ,
{ 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } } ; static int_T rt_LoggedStateIdxList [ ] = { 0 , 1 , 2 , 3 , 4 , 5 ,
6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15 , 16 , 17 , 18 , 19 , 20 } ;
static RTWLogSignalInfo rt_LoggedStateSignalInfo = { 21 ,
rt_LoggedStateWidths , rt_LoggedStateNumDimensions , rt_LoggedStateDimensions
, rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 21 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . hjkn3n4lly [ 0 ] ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . oxovzkyrgp [ 0 ] ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtX . pcdkwn41rb [ 0 ] ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtX . l50b0cuk2h ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtX . b4ena3lr0n ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) & rtX . lbdfwq1i3y ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) & rtX . fnheb54sgb ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) & rtX . muv5xwjpjd ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtX . argwmtgb5v ;
rt_LoggedStateSignalPtrs [ 9 ] = ( void * ) & rtX . bxdhuzrxz2 ;
rt_LoggedStateSignalPtrs [ 10 ] = ( void * ) & rtX . cmyui1ww54 ;
rt_LoggedStateSignalPtrs [ 11 ] = ( void * ) & rtX . i1iguten22 [ 0 ] ;
rt_LoggedStateSignalPtrs [ 12 ] = ( void * ) & rtX . pkf1lgikiz [ 0 ] ;
rt_LoggedStateSignalPtrs [ 13 ] = ( void * ) & rtX . f3jtaj41sb [ 0 ] ;
rt_LoggedStateSignalPtrs [ 14 ] = ( void * ) & rtX . ae0okdyidm ;
rt_LoggedStateSignalPtrs [ 15 ] = ( void * ) & rtX . cok521zc4f ;
rt_LoggedStateSignalPtrs [ 16 ] = ( void * ) & rtX . pf4hzftljn ;
rt_LoggedStateSignalPtrs [ 17 ] = ( void * ) & rtX . ek1dcgndv4 ;
rt_LoggedStateSignalPtrs [ 18 ] = ( void * ) & rtX . iyvywkyjkt ;
rt_LoggedStateSignalPtrs [ 19 ] = ( void * ) & rtX . cscwx5acjj ;
rt_LoggedStateSignalPtrs [ 20 ] = ( void * ) & rtX . l0nfea2luh [ 0 ] ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "tmp_raccel_xout" ) ; rtliSetLogXFinal (
ssGetRTWLogInfo ( rtS ) , "xFinal" ) ; rtliSetLogVarNameModifier (
ssGetRTWLogInfo ( rtS ) , "none" ) ; rtliSetLogFormat ( ssGetRTWLogInfo ( rtS
) , 2 ) ; rtliSetLogMaxRows ( ssGetRTWLogInfo ( rtS ) , 1000 ) ;
rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS ) , 1 ) ; { static void *
rt_LoggedOutputSignalPtrs [ ] = { & rtY . jwku2vbe0w , & rtY . fudrm4x01v , &
rtY . nza55qah0g [ 0 ] } ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) ,
( ( LogSignalPtrsType ) rt_LoggedOutputSignalPtrs ) ) ; } { static int_T
rt_LoggedOutputWidths [ ] = { 1 , 1 , 3 } ; static int_T
rt_LoggedOutputNumDimensions [ ] = { 1 , 1 , 1 } ; static int_T
rt_LoggedOutputDimensions [ ] = { 1 , 1 , 3 } ; static boolean_T
rt_LoggedOutputIsVarDims [ ] = { 0 , 0 , 0 } ; static void *
rt_LoggedCurrentSignalDimensions [ ] = { ( NULL ) , ( NULL ) , ( NULL ) } ;
static int_T rt_LoggedCurrentSignalDimensionsSize [ ] = { 4 , 4 , 4 } ;
static BuiltInDTypeId rt_LoggedOutputDataTypeIds [ ] = { SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE } ; static int_T rt_LoggedOutputComplexSignals [ ] = {
0 , 0 , 0 } ; static RTWPreprocessingFcnPtr rt_LoggingPreprocessingFcnPtrs [
] = { ( NULL ) , ( NULL ) , ( NULL ) } ; static const char_T *
rt_LoggedOutputLabels_0 [ ] = { "outAngularRate" } ; static const char_T *
rt_LoggedOutputBlockNames_0 [ ] = { "SILS_20241709/outAngularRate" } ; static
const char_T * rt_LoggedOutputLabels_1 [ ] = { "sun_flag" } ; static const
char_T * rt_LoggedOutputBlockNames_1 [ ] = { "SILS_20241709/sun_flag_#_#_1" }
; static const char_T * rt_LoggedOutputLabels_2 [ ] = { "w_b_rad_s" } ;
static const char_T * rt_LoggedOutputBlockNames_2 [ ] = {
"SILS_20241709/w_b_rad//s" } ; static RTWLogDataTypeConvert
rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 ,
1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } ,
{ 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static
RTWLogSignalInfo rt_LoggedOutputSignalInfo [ ] = { { 1 ,
rt_LoggedOutputWidths , rt_LoggedOutputNumDimensions ,
rt_LoggedOutputDimensions , rt_LoggedOutputIsVarDims ,
rt_LoggedCurrentSignalDimensions , rt_LoggedCurrentSignalDimensionsSize ,
rt_LoggedOutputDataTypeIds , rt_LoggedOutputComplexSignals , ( NULL ) ,
rt_LoggingPreprocessingFcnPtrs , { rt_LoggedOutputLabels_0 } , ( NULL ) , (
NULL ) , ( NULL ) , { rt_LoggedOutputBlockNames_0 } , { ( NULL ) } , ( NULL )
, rt_RTWLogDataTypeConvert , ( NULL ) } , { 1 , rt_LoggedOutputWidths + 1 ,
rt_LoggedOutputNumDimensions + 1 , rt_LoggedOutputDimensions + 1 ,
rt_LoggedOutputIsVarDims + 1 , rt_LoggedCurrentSignalDimensions + 1 ,
rt_LoggedCurrentSignalDimensionsSize + 1 , rt_LoggedOutputDataTypeIds + 1 ,
rt_LoggedOutputComplexSignals + 1 , ( NULL ) , rt_LoggingPreprocessingFcnPtrs
+ 1 , { rt_LoggedOutputLabels_1 } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedOutputBlockNames_1 } , { ( NULL ) } , ( NULL ) ,
rt_RTWLogDataTypeConvert + 1 , ( NULL ) } , { 1 , rt_LoggedOutputWidths + 2 ,
rt_LoggedOutputNumDimensions + 2 , rt_LoggedOutputDimensions + 2 ,
rt_LoggedOutputIsVarDims + 2 , rt_LoggedCurrentSignalDimensions + 2 ,
rt_LoggedCurrentSignalDimensionsSize + 2 , rt_LoggedOutputDataTypeIds + 2 ,
rt_LoggedOutputComplexSignals + 2 , ( NULL ) , rt_LoggingPreprocessingFcnPtrs
+ 2 , { rt_LoggedOutputLabels_2 } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedOutputBlockNames_2 } , { ( NULL ) } , ( NULL ) ,
rt_RTWLogDataTypeConvert + 2 , ( NULL ) } } ; rtliSetLogYSignalInfo (
ssGetRTWLogInfo ( rtS ) , rt_LoggedOutputSignalInfo ) ;
rt_LoggedCurrentSignalDimensions [ 0 ] = & rt_LoggedOutputWidths [ 0 ] ;
rt_LoggedCurrentSignalDimensions [ 1 ] = & rt_LoggedOutputWidths [ 1 ] ;
rt_LoggedCurrentSignalDimensions [ 2 ] = & rt_LoggedOutputWidths [ 2 ] ; }
rtliSetLogY ( ssGetRTWLogInfo ( rtS ) ,
"tmp_raccel_yout1,tmp_raccel_yout2,tmp_raccel_yout3" ) ; } { static struct
_ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 ) ; } {
static ssPeriodicStatesInfo periodicStatesInfo ; ssSetPeriodicStatesInfo (
rtS , & periodicStatesInfo ) ; } { static ssJacobianPerturbationBounds
jacobianPerturbationBounds ; ssSetJacobianPerturbationBounds ( rtS , &
jacobianPerturbationBounds ) ; } { static ssSolverInfo slvrInfo ; static
boolean_T contStatesDisabled [ 36 ] ; static ssNonContDerivSigInfo
nonContDerivSigInfo [ 2 ] = { { 3 * sizeof ( real_T ) , ( char * ) ( & rtB .
ikgewnxpow [ 0 ] ) , ( NULL ) } , { 3 * sizeof ( real_T ) , ( char * ) ( &
rtB . nljkudwtrt [ 0 ] ) , ( NULL ) } } ; ssSetNumNonContDerivSigInfos ( rtS
, 2 ) ; ssSetNonContDerivSigInfos ( rtS , nonContDerivSigInfo ) ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS , "ode4" ) ;
ssSetVariableStepSolver ( rtS , 0 ) ; ssSetSolverConsistencyChecking ( rtS ,
0 ) ; ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ;
ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetSolverStateProjection ( rtS ,
0 ) ; ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetTNextTid ( rtS , INT_MIN ) ; ssSetTNext ( rtS ,
rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ; ssSetNumNonsampledZCs ( rtS ,
0 ) ; ssSetContStateDisabled ( rtS , contStatesDisabled ) ; }
ssSetChecksumVal ( rtS , 0 , 2405234056U ) ; ssSetChecksumVal ( rtS , 1 ,
151909971U ) ; ssSetChecksumVal ( rtS , 2 , 1794605402U ) ; ssSetChecksumVal
( rtS , 3 , 3767048926U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 108 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = & rtAlwaysEnabled ;
systemRan [ 2 ] = ( sysRanDType * ) & rtDW . icv4qsjrec ; systemRan [ 3 ] = (
sysRanDType * ) & rtDW . icv4qsjrec ; systemRan [ 4 ] = ( sysRanDType * ) &
rtDW . icv4qsjrec ; systemRan [ 5 ] = ( sysRanDType * ) & rtDW . icv4qsjrec ;
systemRan [ 6 ] = ( sysRanDType * ) & rtDW . icv4qsjrec ; systemRan [ 7 ] = (
sysRanDType * ) & rtDW . icv4qsjrec ; systemRan [ 8 ] = & rtAlwaysEnabled ;
systemRan [ 9 ] = & rtAlwaysEnabled ; systemRan [ 10 ] = & rtAlwaysEnabled ;
systemRan [ 11 ] = & rtAlwaysEnabled ; systemRan [ 12 ] = & rtAlwaysEnabled ;
systemRan [ 13 ] = & rtAlwaysEnabled ; systemRan [ 14 ] = & rtAlwaysEnabled ;
systemRan [ 15 ] = & rtAlwaysEnabled ; systemRan [ 16 ] = ( sysRanDType * ) &
rtDW . ggsva4qu4a ; systemRan [ 17 ] = ( sysRanDType * ) & rtDW . ggsva4qu4a
; systemRan [ 18 ] = ( sysRanDType * ) & rtDW . kddtry4ekq ; systemRan [ 19 ]
= ( sysRanDType * ) & rtDW . kddtry4ekq ; systemRan [ 20 ] = &
rtAlwaysEnabled ; systemRan [ 21 ] = & rtAlwaysEnabled ; systemRan [ 22 ] = &
rtAlwaysEnabled ; systemRan [ 23 ] = & rtAlwaysEnabled ; systemRan [ 24 ] = &
rtAlwaysEnabled ; systemRan [ 25 ] = & rtAlwaysEnabled ; systemRan [ 26 ] = &
rtAlwaysEnabled ; systemRan [ 27 ] = & rtAlwaysEnabled ; systemRan [ 28 ] = &
rtAlwaysEnabled ; systemRan [ 29 ] = ( sysRanDType * ) & rtDW . gxgp4hskcm ;
systemRan [ 30 ] = ( sysRanDType * ) & rtDW . gxgp4hskcm ; systemRan [ 31 ] =
& rtAlwaysEnabled ; systemRan [ 32 ] = ( sysRanDType * ) & rtDW . azyx1ts0yu
; systemRan [ 33 ] = ( sysRanDType * ) & rtDW . azyx1ts0yu ; systemRan [ 34 ]
= ( sysRanDType * ) & rtDW . azyx1ts0yu ; systemRan [ 35 ] = ( sysRanDType *
) & rtDW . azyx1ts0yu ; systemRan [ 36 ] = & rtAlwaysEnabled ; systemRan [ 37
] = & rtAlwaysEnabled ; systemRan [ 38 ] = & rtAlwaysEnabled ; systemRan [ 39
] = & rtAlwaysEnabled ; systemRan [ 40 ] = & rtAlwaysEnabled ; systemRan [ 41
] = & rtAlwaysEnabled ; systemRan [ 42 ] = & rtAlwaysEnabled ; systemRan [ 43
] = & rtAlwaysEnabled ; systemRan [ 44 ] = & rtAlwaysEnabled ; systemRan [ 45
] = & rtAlwaysEnabled ; systemRan [ 46 ] = & rtAlwaysEnabled ; systemRan [ 47
] = & rtAlwaysEnabled ; systemRan [ 48 ] = & rtAlwaysEnabled ; systemRan [ 49
] = & rtAlwaysEnabled ; systemRan [ 50 ] = & rtAlwaysEnabled ; systemRan [ 51
] = & rtAlwaysEnabled ; systemRan [ 52 ] = & rtAlwaysEnabled ; systemRan [ 53
] = & rtAlwaysEnabled ; systemRan [ 54 ] = & rtAlwaysEnabled ; systemRan [ 55
] = & rtAlwaysEnabled ; systemRan [ 56 ] = & rtAlwaysEnabled ; systemRan [ 57
] = & rtAlwaysEnabled ; systemRan [ 58 ] = & rtAlwaysEnabled ; systemRan [ 59
] = & rtAlwaysEnabled ; systemRan [ 60 ] = & rtAlwaysEnabled ; systemRan [ 61
] = & rtAlwaysEnabled ; systemRan [ 62 ] = & rtAlwaysEnabled ; systemRan [ 63
] = & rtAlwaysEnabled ; systemRan [ 64 ] = & rtAlwaysEnabled ; systemRan [ 65
] = & rtAlwaysEnabled ; systemRan [ 66 ] = & rtAlwaysEnabled ; systemRan [ 67
] = & rtAlwaysEnabled ; systemRan [ 68 ] = & rtAlwaysEnabled ; systemRan [ 69
] = & rtAlwaysEnabled ; systemRan [ 70 ] = & rtAlwaysEnabled ; systemRan [ 71
] = & rtAlwaysEnabled ; systemRan [ 72 ] = & rtAlwaysEnabled ; systemRan [ 73
] = & rtAlwaysEnabled ; systemRan [ 74 ] = & rtAlwaysEnabled ; systemRan [ 75
] = & rtAlwaysEnabled ; systemRan [ 76 ] = & rtAlwaysEnabled ; systemRan [ 77
] = & rtAlwaysEnabled ; systemRan [ 78 ] = & rtAlwaysEnabled ; systemRan [ 79
] = & rtAlwaysEnabled ; systemRan [ 80 ] = & rtAlwaysEnabled ; systemRan [ 81
] = & rtAlwaysEnabled ; systemRan [ 82 ] = & rtAlwaysEnabled ; systemRan [ 83
] = & rtAlwaysEnabled ; systemRan [ 84 ] = & rtAlwaysEnabled ; systemRan [ 85
] = & rtAlwaysEnabled ; systemRan [ 86 ] = & rtAlwaysEnabled ; systemRan [ 87
] = & rtAlwaysEnabled ; systemRan [ 88 ] = & rtAlwaysEnabled ; systemRan [ 89
] = & rtAlwaysEnabled ; systemRan [ 90 ] = & rtAlwaysEnabled ; systemRan [ 91
] = & rtAlwaysEnabled ; systemRan [ 92 ] = & rtAlwaysEnabled ; systemRan [ 93
] = & rtAlwaysEnabled ; systemRan [ 94 ] = & rtAlwaysEnabled ; systemRan [ 95
] = & rtAlwaysEnabled ; systemRan [ 96 ] = & rtAlwaysEnabled ; systemRan [ 97
] = & rtAlwaysEnabled ; systemRan [ 98 ] = & rtAlwaysEnabled ; systemRan [ 99
] = & rtAlwaysEnabled ; systemRan [ 100 ] = & rtAlwaysEnabled ; systemRan [
101 ] = & rtAlwaysEnabled ; systemRan [ 102 ] = & rtAlwaysEnabled ; systemRan
[ 103 ] = & rtAlwaysEnabled ; systemRan [ 104 ] = & rtAlwaysEnabled ;
systemRan [ 105 ] = & rtAlwaysEnabled ; systemRan [ 106 ] = & rtAlwaysEnabled
; systemRan [ 107 ] = & rtAlwaysEnabled ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; }
slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_SILS_20241709_GetSimStateDisallowedBlocks ) ; slsaGetWorkFcnForSimTargetOP
( rtS , mr_SILS_20241709_GetDWork ) ; slsaSetWorkFcnForSimTargetOP ( rtS ,
mr_SILS_20241709_SetDWork ) ; rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if
( ssGetErrorStatus ( rtS ) ) { return rtS ; } ssSetNumSFunctions ( rtS , 21 )
; { static SimStruct childSFunctions [ 21 ] ; static SimStruct *
childSFunctionPtrs [ 21 ] ; ( void ) memset ( ( void * ) & childSFunctions [
0 ] , 0 , sizeof ( childSFunctions ) ) ; ssSetSFunctions ( rtS , &
childSFunctionPtrs [ 0 ] ) ; { int_T i ; for ( i = 0 ; i < 21 ; i ++ ) {
ssSetSFunction ( rtS , i , & childSFunctions [ i ] ) ; } } { SimStruct * rts
= ssGetSFunction ( rtS , 0 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 11 ) ; static struct _ssPortInputs inputPortInfo
[ 11 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 11 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ;
ssSetInputPortUnit ( rts , 1 , 0 ) ; ssSetInputPortUnit ( rts , 2 , 0 ) ;
ssSetInputPortUnit ( rts , 3 , 0 ) ; ssSetInputPortUnit ( rts , 4 , 0 ) ;
ssSetInputPortUnit ( rts , 5 , 0 ) ; ssSetInputPortUnit ( rts , 6 , 0 ) ;
ssSetInputPortUnit ( rts , 7 , 0 ) ; ssSetInputPortUnit ( rts , 8 , 0 ) ;
ssSetInputPortUnit ( rts , 9 , 0 ) ; ssSetInputPortUnit ( rts , 10 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 11 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 1 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 2 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 3 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 4 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 5 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 6 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 7 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 8 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 9 , 0 ) ;
ssSetInputPortIsContinuousQuantity ( rts , 10 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , & rtB . a5ald3g22i [ 0 ] ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1
) ; ssSetInputPortWidthAsInt ( rts , 0 , 1 ) ; } {
ssSetInputPortRequiredContiguous ( rts , 1 , 1 ) ; ssSetInputPortSignal ( rts
, 1 , & rtB . a5ald3g22i [ 1 ] ) ; _ssSetInputPortNumDimensions ( rts , 1 , 1
) ; ssSetInputPortWidthAsInt ( rts , 1 , 1 ) ; } {
ssSetInputPortRequiredContiguous ( rts , 2 , 1 ) ; ssSetInputPortSignal ( rts
, 2 , & rtB . mpca01r2m2 ) ; _ssSetInputPortNumDimensions ( rts , 2 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 2 , 1 ) ; } {
ssSetInputPortRequiredContiguous ( rts , 3 , 1 ) ; ssSetInputPortSignal ( rts
, 3 , & rtB . e1zykr3jbv . crs3vbajbr ) ; _ssSetInputPortNumDimensions ( rts
, 3 , 1 ) ; ssSetInputPortWidthAsInt ( rts , 3 , 1 ) ; } {
ssSetInputPortRequiredContiguous ( rts , 4 , 1 ) ; ssSetInputPortSignal ( rts
, 4 , & rtB . jn52bjhkjf ) ; _ssSetInputPortNumDimensions ( rts , 4 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 4 , 1 ) ; } {
ssSetInputPortRequiredContiguous ( rts , 5 , 1 ) ; ssSetInputPortSignal ( rts
, 5 , & rtB . chrkykmk4n ) ; _ssSetInputPortNumDimensions ( rts , 5 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 5 , 1 ) ; } {
ssSetInputPortRequiredContiguous ( rts , 6 , 1 ) ; ssSetInputPortSignal ( rts
, 6 , & rtB . i2mlgup0vd ) ; _ssSetInputPortNumDimensions ( rts , 6 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 6 , 1 ) ; } {
ssSetInputPortRequiredContiguous ( rts , 7 , 1 ) ; ssSetInputPortSignal ( rts
, 7 , & rtB . p4vsv1mu0t ) ; _ssSetInputPortNumDimensions ( rts , 7 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 7 , 1 ) ; } {
ssSetInputPortRequiredContiguous ( rts , 8 , 1 ) ; ssSetInputPortSignal ( rts
, 8 , & rtB . p4vsv1mu0t ) ; _ssSetInputPortNumDimensions ( rts , 8 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 8 , 1 ) ; } { static int_T dimensions [ 2 ]
; ssSetInputPortRequiredContiguous ( rts , 9 , 1 ) ; ssSetInputPortSignal (
rts , 9 , rtB . blzsybl1pb ) ; dimensions [ 0 ] = 1 ; dimensions [ 1 ] = 7 ;
_ssSetInputPortDimensionsPtrAsInt ( rts , 9 , dimensions ) ;
_ssSetInputPortNumDimensions ( rts , 9 , 2 ) ; ssSetInputPortWidthAsInt ( rts
, 9 , 7 ) ; } { static int_T dimensions [ 2 ] ;
ssSetInputPortRequiredContiguous ( rts , 10 , 1 ) ; ssSetInputPortSignal (
rts , 10 , rtB . nspxciplv0 ) ; dimensions [ 0 ] = 1 ; dimensions [ 1 ] = 23
; _ssSetInputPortDimensionsPtrAsInt ( rts , 10 , dimensions ) ;
_ssSetInputPortNumDimensions ( rts , 10 , 2 ) ; ssSetInputPortWidthAsInt (
rts , 10 , 23 ) ; } } { static struct _ssPortOutputs outputPortInfo [ 2 ] ;
ssSetPortInfoForOutputs ( rts , & outputPortInfo [ 0 ] ) ;
_ssSetNumOutputPorts ( rts , 2 ) ; { static struct _ssOutPortUnit
outputPortUnits [ 2 ] ; _ssSetPortInfo2ForOutputUnits ( rts , &
outputPortUnits [ 0 ] ) ; } ssSetOutputPortUnit ( rts , 0 , 0 ) ;
ssSetOutputPortUnit ( rts , 1 , 0 ) ; { static struct
_ssOutPortCoSimAttribute outputPortCoSimAttribute [ 2 ] ;
_ssSetPortInfo2ForOutputCoSimAttribute ( rts , & outputPortCoSimAttribute [ 0
] ) ; } ssSetOutputPortIsContinuousQuantity ( rts , 0 , 0 ) ;
ssSetOutputPortIsContinuousQuantity ( rts , 1 , 0 ) ; {
_ssSetOutputPortNumDimensions ( rts , 0 , 1 ) ; ssSetOutputPortWidthAsInt (
rts , 0 , 1 ) ; ssSetOutputPortSignal ( rts , 0 , ( ( real_T * ) & rtB .
nevppfxrse ) ) ; } { _ssSetOutputPortNumDimensions ( rts , 1 , 1 ) ;
ssSetOutputPortWidthAsInt ( rts , 1 , 1 ) ; ssSetOutputPortSignal ( rts , 1 ,
( ( real_T * ) & rtB . bfrpnyoemv ) ) ; } } ssSetModelName ( rts ,
"sfunc_nrlmsise00" ) ; ssSetPath ( rts ,
 "SILS_20241709/Environment&Dynamics/Air Drag/nrlmsise-00 simple/nrlmsise-00 full/S-Function"
) ; if ( ssGetRTModel ( rtS ) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ;
ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts ,
ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts
, rts ) ; } ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; {
raccelLoadSFcnMexFile ( "sfunc_nrlmsise00" , "SILS_20241709:424:2443:1728" ,
rts , 0 ) ; if ( ssGetErrorStatus ( rtS ) ) { return rtS ; } }
sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0 ) ;
ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; _ssSetInputPortConnected ( rts , 1 , 1 ) ; _ssSetInputPortConnected (
rts , 2 , 1 ) ; _ssSetInputPortConnected ( rts , 3 , 1 ) ;
_ssSetInputPortConnected ( rts , 4 , 1 ) ; _ssSetInputPortConnected ( rts , 5
, 1 ) ; _ssSetInputPortConnected ( rts , 6 , 1 ) ; _ssSetInputPortConnected (
rts , 7 , 1 ) ; _ssSetInputPortConnected ( rts , 8 , 1 ) ;
_ssSetInputPortConnected ( rts , 9 , 1 ) ; _ssSetInputPortConnected ( rts ,
10 , 1 ) ; _ssSetOutputPortConnected ( rts , 0 , 1 ) ;
_ssSetOutputPortConnected ( rts , 1 , 1 ) ; _ssSetOutputPortBeingMerged ( rts
, 0 , 0 ) ; _ssSetOutputPortBeingMerged ( rts , 1 , 0 ) ;
ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; ssSetInputPortBufferDstPort (
rts , 1 , - 1 ) ; ssSetInputPortBufferDstPort ( rts , 2 , - 1 ) ;
ssSetInputPortBufferDstPort ( rts , 3 , - 1 ) ; ssSetInputPortBufferDstPort (
rts , 4 , - 1 ) ; ssSetInputPortBufferDstPort ( rts , 5 , - 1 ) ;
ssSetInputPortBufferDstPort ( rts , 6 , - 1 ) ; ssSetInputPortBufferDstPort (
rts , 7 , - 1 ) ; ssSetInputPortBufferDstPort ( rts , 8 , - 1 ) ;
ssSetInputPortBufferDstPort ( rts , 9 , - 1 ) ; ssSetInputPortBufferDstPort (
rts , 10 , - 1 ) ; } { SimStruct * rts = ssGetSFunction ( rtS , 1 ) ; static
time_T sfcnPeriod [ 1 ] ; static time_T sfcnOffset [ 1 ] ; static int_T
sfcnTsMap [ 1 ] ; ( void ) memset ( ( void * ) sfcnPeriod , 0 , sizeof (
time_T ) * 1 ) ; ( void ) memset ( ( void * ) sfcnOffset , 0 , sizeof (
time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , & sfcnPeriod [ 0 ] ) ;
ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr (
rts , sfcnTsMap ) ; { static struct _ssBlkInfo2 _blkInfo2 ; struct
_ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr ( rts , blkInfo2 ) ;
} { static struct _ssPortInfo2 _portInfo2 ; struct _ssPortInfo2 * portInfo2 =
& _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts , portInfo2 ) ; }
ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static struct
_ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2 ) ; } {
static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 ( rts , &
methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . fdbl5l21n4 ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 8 ) ; } } ssSetModelName ( rts ,
"sfunc_RW_RX" ) ; ssSetPath ( rts , "SILS_20241709/S-Function2" ) ; if (
ssGetRTModel ( rtS ) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ;
ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts ,
ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts
, rts ) ; } ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static
mxArray * sfcnParams [ 1 ] ; ssSetSFcnParamsCount ( rts , 1 ) ;
ssSetSFcnParamsPtr ( rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 ,
( mxArray * ) rtP . SFunction2_P1_Size ) ; } { raccelLoadSFcnMexFile (
"sfunc_RW_RX" , "SILS_20241709:552" , rts , 1 ) ; if ( ssGetErrorStatus ( rtS
) ) { return rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime (
rts , 0 , 0.0 ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 2 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . oucj4k4y2q ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 8 ) ; } } ssSetModelName ( rts ,
"sfunc_RW_RX" ) ; ssSetPath ( rts , "SILS_20241709/S-Function7" ) ; if (
ssGetRTModel ( rtS ) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ;
ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts ,
ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts
, rts ) ; } ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static
mxArray * sfcnParams [ 1 ] ; ssSetSFcnParamsCount ( rts , 1 ) ;
ssSetSFcnParamsPtr ( rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 ,
( mxArray * ) rtP . SFunction7_P1_Size ) ; } { raccelLoadSFcnMexFile (
"sfunc_RW_RX" , "SILS_20241709:549" , rts , 2 ) ; if ( ssGetErrorStatus ( rtS
) ) { return rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime (
rts , 0 , 0.0 ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 3 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . ktlu1ekw1m ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 8 ) ; } } ssSetModelName ( rts ,
"sfunc_RW_RX" ) ; ssSetPath ( rts , "SILS_20241709/S-Function8" ) ; if (
ssGetRTModel ( rtS ) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ;
ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts ,
ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts
, rts ) ; } ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static
mxArray * sfcnParams [ 1 ] ; ssSetSFcnParamsCount ( rts , 1 ) ;
ssSetSFcnParamsPtr ( rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 ,
( mxArray * ) rtP . SFunction8_P1_Size ) ; } { raccelLoadSFcnMexFile (
"sfunc_RW_RX" , "SILS_20241709:555" , rts , 3 ) ; if ( ssGetErrorStatus ( rtS
) ) { return rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime (
rts , 0 , 0.0 ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 4 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . innw5sywzg ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 8 ) ; } } ssSetModelName ( rts ,
"sfunc_RW_RX" ) ; ssSetPath ( rts , "SILS_20241709/S-Function9" ) ; if (
ssGetRTModel ( rtS ) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ;
ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts ,
ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts
, rts ) ; } ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static
mxArray * sfcnParams [ 1 ] ; ssSetSFcnParamsCount ( rts , 1 ) ;
ssSetSFcnParamsPtr ( rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 ,
( mxArray * ) rtP . SFunction9_P1_Size ) ; } { raccelLoadSFcnMexFile (
"sfunc_RW_RX" , "SILS_20241709:558" , rts , 4 ) ; if ( ssGetErrorStatus ( rtS
) ) { return rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime (
rts , 0 , 0.0 ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 5 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . asykhtld2n ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 12 ) ; } } ssSetModelName ( rts ,
"sfunc_STT" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function6" ) ; if ( ssGetRTModel ( rtS
) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 2 ] ; ssSetSFcnParamsCount ( rts , 2 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction6_P1_Size ) ; ssSetSFcnParam ( rts , 1 , ( mxArray * ) rtP .
SFunction6_P2_Size ) ; } { raccelLoadSFcnMexFile ( "sfunc_STT" ,
"SILS_20241709:523" , rts , 5 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0
) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 6 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . ilq2khdcgh ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 4 ) ; } } ssSetModelName ( rts ,
"sfunc_FOG" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function" ) ; if ( ssGetRTModel ( rtS )
== ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts , ssGetRootSS
( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) ) ;
ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; } ssSetVersion
( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray * sfcnParams [ 2 ] ;
ssSetSFcnParamsCount ( rts , 2 ) ; ssSetSFcnParamsPtr ( rts , & sfcnParams [
0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP . SFunction_P1_Size ) ;
ssSetSFcnParam ( rts , 1 , ( mxArray * ) rtP . SFunction_P2_Size ) ; } {
raccelLoadSFcnMexFile ( "sfunc_FOG" , "SILS_20241709:517" , rts , 6 ) ; if (
ssGetErrorStatus ( rtS ) ) { return rtS ; } } sfcnInitializeSampleTimes ( rts
) ; ssSetSampleTime ( rts , 0 , 0.0 ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ;
sfcnTsMap [ 0 ] = 0 ; ssSetNumNonsampledZCsAsInt ( rts , 0 ) ;
_ssSetInputPortConnected ( rts , 0 , 1 ) ; ssSetInputPortBufferDstPort ( rts
, 0 , - 1 ) ; } { SimStruct * rts = ssGetSFunction ( rtS , 7 ) ; static
time_T sfcnPeriod [ 1 ] ; static time_T sfcnOffset [ 1 ] ; static int_T
sfcnTsMap [ 1 ] ; ( void ) memset ( ( void * ) sfcnPeriod , 0 , sizeof (
time_T ) * 1 ) ; ( void ) memset ( ( void * ) sfcnOffset , 0 , sizeof (
time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , & sfcnPeriod [ 0 ] ) ;
ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr (
rts , sfcnTsMap ) ; { static struct _ssBlkInfo2 _blkInfo2 ; struct
_ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr ( rts , blkInfo2 ) ;
} { static struct _ssPortInfo2 _portInfo2 ; struct _ssPortInfo2 * portInfo2 =
& _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts , portInfo2 ) ; }
ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static struct
_ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2 ) ; } {
static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 ( rts , &
methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . fdbl5l21n42 ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 4 ) ; } } ssSetModelName ( rts ,
"sfunc_NSAS" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function2" ) ; if ( ssGetRTModel ( rtS
) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 2 ] ; ssSetSFcnParamsCount ( rts , 2 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction2_P1_Size_aqgqx4ctqe ) ; ssSetSFcnParam ( rts , 1 , ( mxArray * )
rtP . SFunction2_P2_Size ) ; } { raccelLoadSFcnMexFile ( "sfunc_NSAS" ,
"SILS_20241709:519" , rts , 7 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0
) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 8 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . pktfet50kq ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 4 ) ; } } ssSetModelName ( rts ,
"sfunc_NSAS" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function3" ) ; if ( ssGetRTModel ( rtS
) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 2 ] ; ssSetSFcnParamsCount ( rts , 2 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction3_P1_Size ) ; ssSetSFcnParam ( rts , 1 , ( mxArray * ) rtP .
SFunction3_P2_Size ) ; } { raccelLoadSFcnMexFile ( "sfunc_NSAS" ,
"SILS_20241709:520" , rts , 8 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0
) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 9 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . cyayszgojz ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 4 ) ; } } ssSetModelName ( rts ,
"sfunc_NSAS" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function4" ) ; if ( ssGetRTModel ( rtS
) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 2 ] ; ssSetSFcnParamsCount ( rts , 2 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction4_P1_Size ) ; ssSetSFcnParam ( rts , 1 , ( mxArray * ) rtP .
SFunction4_P2_Size ) ; } { raccelLoadSFcnMexFile ( "sfunc_NSAS" ,
"SILS_20241709:521" , rts , 9 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0
) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 10 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . oucj4k4y2qy ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 4 ) ; } } ssSetModelName ( rts ,
"sfunc_NSAS" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function7" ) ; if ( ssGetRTModel ( rtS
) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 2 ] ; ssSetSFcnParamsCount ( rts , 2 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction7_P1_Size_buxc0ymhsr ) ; ssSetSFcnParam ( rts , 1 , ( mxArray * )
rtP . SFunction7_P2_Size ) ; } { raccelLoadSFcnMexFile ( "sfunc_NSAS" ,
"SILS_20241709:630" , rts , 10 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0
) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 11 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . ktlu1ekw1mg ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 4 ) ; } } ssSetModelName ( rts ,
"sfunc_NSAS" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function8" ) ; if ( ssGetRTModel ( rtS
) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 2 ] ; ssSetSFcnParamsCount ( rts , 2 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction8_P1_Size_otc42vq3fz ) ; ssSetSFcnParam ( rts , 1 , ( mxArray * )
rtP . SFunction8_P2_Size ) ; } { raccelLoadSFcnMexFile ( "sfunc_NSAS" ,
"SILS_20241709:631" , rts , 11 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0
) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 12 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . innw5sywzgy ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 4 ) ; } } ssSetModelName ( rts ,
"sfunc_NSAS" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function9" ) ; if ( ssGetRTModel ( rtS
) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 2 ] ; ssSetSFcnParamsCount ( rts , 2 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction9_P1_Size_ncpscvdwkx ) ; ssSetSFcnParam ( rts , 1 , ( mxArray * )
rtP . SFunction9_P2_Size ) ; } { raccelLoadSFcnMexFile ( "sfunc_NSAS" ,
"SILS_20241709:632" , rts , 12 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0
) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 13 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . jihpm3q5gs ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 4 ) ; } } ssSetModelName ( rts ,
"sfunc_GAS" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function1" ) ; if ( ssGetRTModel ( rtS
) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 1 ] ; ssSetSFcnParamsCount ( rts , 1 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction1_P1_Size ) ; } { raccelLoadSFcnMexFile ( "sfunc_GAS" ,
"SILS_20241709:518" , rts , 13 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0
) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 14 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , rtB . cbjdhhra0o ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 12 ) ; } } ssSetModelName ( rts ,
"sfunc_GPS" ) ; ssSetPath ( rts ,
"SILS_20241709/SensorDataConversion/S-Function5" ) ; if ( ssGetRTModel ( rtS
) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 1 ] ; ssSetSFcnParamsCount ( rts , 1 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction5_P1_Size ) ; } { raccelLoadSFcnMexFile ( "sfunc_GPS" ,
"SILS_20241709:522" , rts , 14 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0
) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
1 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct * rts =
ssGetSFunction ( rtS , 15 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , & rtB . i34t1ktiub ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 1 ) ; } } { static struct _ssPortOutputs
outputPortInfo [ 5 ] ; ssSetPortInfoForOutputs ( rts , & outputPortInfo [ 0 ]
) ; _ssSetNumOutputPorts ( rts , 5 ) ; { static struct _ssOutPortUnit
outputPortUnits [ 5 ] ; _ssSetPortInfo2ForOutputUnits ( rts , &
outputPortUnits [ 0 ] ) ; } ssSetOutputPortUnit ( rts , 0 , 0 ) ;
ssSetOutputPortUnit ( rts , 1 , 0 ) ; ssSetOutputPortUnit ( rts , 2 , 0 ) ;
ssSetOutputPortUnit ( rts , 3 , 0 ) ; ssSetOutputPortUnit ( rts , 4 , 0 ) ; {
static struct _ssOutPortCoSimAttribute outputPortCoSimAttribute [ 5 ] ;
_ssSetPortInfo2ForOutputCoSimAttribute ( rts , & outputPortCoSimAttribute [ 0
] ) ; } ssSetOutputPortIsContinuousQuantity ( rts , 0 , 0 ) ;
ssSetOutputPortIsContinuousQuantity ( rts , 1 , 0 ) ;
ssSetOutputPortIsContinuousQuantity ( rts , 2 , 0 ) ;
ssSetOutputPortIsContinuousQuantity ( rts , 3 , 0 ) ;
ssSetOutputPortIsContinuousQuantity ( rts , 4 , 0 ) ; {
_ssSetOutputPortNumDimensions ( rts , 0 , 1 ) ; ssSetOutputPortWidthAsInt (
rts , 0 , 1 ) ; ssSetOutputPortSignal ( rts , 0 , ( ( real_T * ) & rtB .
ozbqnpwmeu ) ) ; } { _ssSetOutputPortNumDimensions ( rts , 1 , 1 ) ;
ssSetOutputPortWidthAsInt ( rts , 1 , 1 ) ; ssSetOutputPortSignal ( rts , 1 ,
( ( real_T * ) & rtB . gbjcwtpbjf ) ) ; } { _ssSetOutputPortNumDimensions (
rts , 2 , 1 ) ; ssSetOutputPortWidthAsInt ( rts , 2 , 1 ) ;
ssSetOutputPortSignal ( rts , 2 , ( ( real_T * ) & rtB . ogbf133q1z ) ) ; } {
_ssSetOutputPortNumDimensions ( rts , 3 , 1 ) ; ssSetOutputPortWidthAsInt (
rts , 3 , 1 ) ; ssSetOutputPortSignal ( rts , 3 , ( ( real_T * ) & rtB .
ocfpzffbzh ) ) ; } { _ssSetOutputPortNumDimensions ( rts , 4 , 1 ) ;
ssSetOutputPortWidthAsInt ( rts , 4 , 1 ) ; ssSetOutputPortSignal ( rts , 4 ,
( ( real_T * ) & rtB . pzuqvdky0w ) ) ; } } ssSetModelName ( rts ,
"sfunc_AOBC" ) ; ssSetPath ( rts , "SILS_20241709/OBC/S-Function" ) ; if (
ssGetRTModel ( rtS ) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ;
ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts ,
ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts
, rts ) ; } ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; {
raccelLoadSFcnMexFile ( "sfunc_AOBC" , "SILS_20241709:537" , rts , 15 ) ; if
( ssGetErrorStatus ( rtS ) ) { return rtS ; } } sfcnInitializeSampleTimes (
rts ) ; ssSetSampleTime ( rts , 0 , 0.05 ) ; ssSetOffsetTime ( rts , 0 , 0.0
) ; sfcnTsMap [ 0 ] = 2 ; ssSetNumNonsampledZCsAsInt ( rts , 0 ) ;
_ssSetInputPortConnected ( rts , 0 , 1 ) ; _ssSetOutputPortConnected ( rts ,
0 , 1 ) ; _ssSetOutputPortConnected ( rts , 1 , 1 ) ;
_ssSetOutputPortConnected ( rts , 2 , 1 ) ; _ssSetOutputPortConnected ( rts ,
3 , 1 ) ; _ssSetOutputPortConnected ( rts , 4 , 1 ) ;
_ssSetOutputPortBeingMerged ( rts , 0 , 0 ) ; _ssSetOutputPortBeingMerged (
rts , 1 , 0 ) ; _ssSetOutputPortBeingMerged ( rts , 2 , 0 ) ;
_ssSetOutputPortBeingMerged ( rts , 3 , 0 ) ; _ssSetOutputPortBeingMerged (
rts , 4 , 0 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } { SimStruct
* rts = ssGetSFunction ( rtS , 16 ) ; static time_T sfcnPeriod [ 1 ] ; static
time_T sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( (
void * ) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void
* ) sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; { static struct _ssBlkInfo2
_blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = & _blkInfo2 ; ssSetBlkInfo2Ptr (
rts , blkInfo2 ) ; } { static struct _ssPortInfo2 _portInfo2 ; struct
_ssPortInfo2 * portInfo2 = & _portInfo2 ; _ssSetBlkInfo2PortInfo2Ptr ( rts ,
portInfo2 ) ; } ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; { static
struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , & methods2
) ; } { static struct _ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 (
rts , & methods3 ) ; } { static struct _ssSFcnModelMethods4 methods4 ;
ssSetModelMethods4 ( rts , & methods4 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; static ssPeriodicStatesInfo periodicStatesInfo ; static
ssJacobianPerturbationBounds jacPerturbationBounds ; ssSetStatesInfo2 ( rts ,
& statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; { static real_T
const * sfcnUPtrs [ 1 ] ; sfcnUPtrs [ 0 ] = ( ( const real_T * ) &
SILS_20241709_RGND ) ; ssSetInputPortSignalPtrs ( rts , 0 , ( InputPtrsType )
& sfcnUPtrs [ 0 ] ) ; _ssSetInputPortNumDimensions ( rts , 0 , 1 ) ;
ssSetInputPortWidthAsInt ( rts , 0 , 1 ) ; } } { static struct _ssPortOutputs
outputPortInfo [ 1 ] ; ssSetPortInfoForOutputs ( rts , & outputPortInfo [ 0 ]
) ; _ssSetNumOutputPorts ( rts , 1 ) ; { static struct _ssOutPortUnit
outputPortUnits [ 1 ] ; _ssSetPortInfo2ForOutputUnits ( rts , &
outputPortUnits [ 0 ] ) ; } ssSetOutputPortUnit ( rts , 0 , 0 ) ; { static
struct _ssOutPortCoSimAttribute outputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForOutputCoSimAttribute ( rts , & outputPortCoSimAttribute [ 0
] ) ; } ssSetOutputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
_ssSetOutputPortNumDimensions ( rts , 0 , 1 ) ; ssSetOutputPortWidthAsInt (
rts , 0 , 3 ) ; ssSetOutputPortSignal ( rts , 0 , ( ( real_T * ) rtB .
j3kezx3yvk ) ) ; } } ssSetModelName ( rts , "sfunc_MTQ" ) ; ssSetPath ( rts ,
"SILS_20241709/S-Function1" ) ; if ( ssGetRTModel ( rtS ) == ( NULL ) ) {
ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; }
else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , (
NULL ) ) ; ssSetRootSS ( rts , rts ) ; } ssSetVersion ( rts ,
SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray * sfcnParams [ 1 ] ;
ssSetSFcnParamsCount ( rts , 1 ) ; ssSetSFcnParamsPtr ( rts , & sfcnParams [
0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction1_P1_Size_oju10to1ph ) ; } { raccelLoadSFcnMexFile ( "sfunc_MTQ" ,
"SILS_20241709:541" , rts , 16 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 ,
rtInf ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 3 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
0 ) ; _ssSetOutputPortConnected ( rts , 0 , 1 ) ; _ssSetOutputPortBeingMerged
( rts , 0 , 0 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } {
SimStruct * rts = ssGetSFunction ( rtS , 17 ) ; static time_T sfcnPeriod [ 1
] ; static time_T sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void )
memset ( ( void * ) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void )
memset ( ( void * ) sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ;
ssSetSampleTimePtr ( rts , & sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts ,
& sfcnOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; {
static struct _ssBlkInfo2 _blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = &
_blkInfo2 ; ssSetBlkInfo2Ptr ( rts , blkInfo2 ) ; } { static struct
_ssPortInfo2 _portInfo2 ; struct _ssPortInfo2 * portInfo2 = & _portInfo2 ;
_ssSetBlkInfo2PortInfo2Ptr ( rts , portInfo2 ) ; } ssSetMdlInfoPtr ( rts ,
ssGetMdlInfoPtr ( rtS ) ) ; { static struct _ssSFcnModelMethods2 methods2 ;
ssSetModelMethods2 ( rts , & methods2 ) ; } { static struct
_ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 ( rts , & methods3 ) ; } {
static struct _ssSFcnModelMethods4 methods4 ; ssSetModelMethods4 ( rts , &
methods4 ) ; } { static struct _ssStatesInfo2 statesInfo2 ; static
ssPeriodicStatesInfo periodicStatesInfo ; static ssJacobianPerturbationBounds
jacPerturbationBounds ; ssSetStatesInfo2 ( rts , & statesInfo2 ) ;
ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , ( ( const real_T * ) & SILS_20241709_RGND ) ) ;
_ssSetInputPortNumDimensions ( rts , 0 , 1 ) ; ssSetInputPortWidthAsInt ( rts
, 0 , 1 ) ; } } { static struct _ssPortOutputs outputPortInfo [ 1 ] ;
ssSetPortInfoForOutputs ( rts , & outputPortInfo [ 0 ] ) ;
_ssSetNumOutputPorts ( rts , 1 ) ; { static struct _ssOutPortUnit
outputPortUnits [ 1 ] ; _ssSetPortInfo2ForOutputUnits ( rts , &
outputPortUnits [ 0 ] ) ; } ssSetOutputPortUnit ( rts , 0 , 0 ) ; { static
struct _ssOutPortCoSimAttribute outputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForOutputCoSimAttribute ( rts , & outputPortCoSimAttribute [ 0
] ) ; } ssSetOutputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
_ssSetOutputPortNumDimensions ( rts , 0 , 1 ) ; ssSetOutputPortWidthAsInt (
rts , 0 , 4 ) ; ssSetOutputPortSignal ( rts , 0 , ( ( real_T * ) rtB .
lrdfz5anhg ) ) ; } } ssSetModelName ( rts , "sfunc_RW_TX" ) ; ssSetPath ( rts
, "SILS_20241709/S-Function3" ) ; if ( ssGetRTModel ( rtS ) == ( NULL ) ) {
ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; }
else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , (
NULL ) ) ; ssSetRootSS ( rts , rts ) ; } ssSetVersion ( rts ,
SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray * sfcnParams [ 1 ] ;
ssSetSFcnParamsCount ( rts , 1 ) ; ssSetSFcnParamsPtr ( rts , & sfcnParams [
0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction3_P1_Size_esjea1ngwl ) ; } { raccelLoadSFcnMexFile ( "sfunc_RW_TX" ,
"SILS_20241709:542" , rts , 17 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 ,
rtInf ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 3 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
0 ) ; _ssSetOutputPortConnected ( rts , 0 , 1 ) ; _ssSetOutputPortBeingMerged
( rts , 0 , 0 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } {
SimStruct * rts = ssGetSFunction ( rtS , 18 ) ; static time_T sfcnPeriod [ 1
] ; static time_T sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void )
memset ( ( void * ) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void )
memset ( ( void * ) sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ;
ssSetSampleTimePtr ( rts , & sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts ,
& sfcnOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; {
static struct _ssBlkInfo2 _blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = &
_blkInfo2 ; ssSetBlkInfo2Ptr ( rts , blkInfo2 ) ; } { static struct
_ssPortInfo2 _portInfo2 ; struct _ssPortInfo2 * portInfo2 = & _portInfo2 ;
_ssSetBlkInfo2PortInfo2Ptr ( rts , portInfo2 ) ; } ssSetMdlInfoPtr ( rts ,
ssGetMdlInfoPtr ( rtS ) ) ; { static struct _ssSFcnModelMethods2 methods2 ;
ssSetModelMethods2 ( rts , & methods2 ) ; } { static struct
_ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 ( rts , & methods3 ) ; } {
static struct _ssSFcnModelMethods4 methods4 ; ssSetModelMethods4 ( rts , &
methods4 ) ; } { static struct _ssStatesInfo2 statesInfo2 ; static
ssPeriodicStatesInfo periodicStatesInfo ; static ssJacobianPerturbationBounds
jacPerturbationBounds ; ssSetStatesInfo2 ( rts , & statesInfo2 ) ;
ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , ( ( const real_T * ) & SILS_20241709_RGND ) ) ;
_ssSetInputPortNumDimensions ( rts , 0 , 1 ) ; ssSetInputPortWidthAsInt ( rts
, 0 , 1 ) ; } } { static struct _ssPortOutputs outputPortInfo [ 1 ] ;
ssSetPortInfoForOutputs ( rts , & outputPortInfo [ 0 ] ) ;
_ssSetNumOutputPorts ( rts , 1 ) ; { static struct _ssOutPortUnit
outputPortUnits [ 1 ] ; _ssSetPortInfo2ForOutputUnits ( rts , &
outputPortUnits [ 0 ] ) ; } ssSetOutputPortUnit ( rts , 0 , 0 ) ; { static
struct _ssOutPortCoSimAttribute outputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForOutputCoSimAttribute ( rts , & outputPortCoSimAttribute [ 0
] ) ; } ssSetOutputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
_ssSetOutputPortNumDimensions ( rts , 0 , 1 ) ; ssSetOutputPortWidthAsInt (
rts , 0 , 4 ) ; ssSetOutputPortSignal ( rts , 0 , ( ( real_T * ) rtB .
d2nlp5u0iz ) ) ; } } ssSetModelName ( rts , "sfunc_RW_TX" ) ; ssSetPath ( rts
, "SILS_20241709/S-Function4" ) ; if ( ssGetRTModel ( rtS ) == ( NULL ) ) {
ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; }
else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , (
NULL ) ) ; ssSetRootSS ( rts , rts ) ; } ssSetVersion ( rts ,
SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray * sfcnParams [ 1 ] ;
ssSetSFcnParamsCount ( rts , 1 ) ; ssSetSFcnParamsPtr ( rts , & sfcnParams [
0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction4_P1_Size_odtljxchme ) ; } { raccelLoadSFcnMexFile ( "sfunc_RW_TX" ,
"SILS_20241709:543" , rts , 18 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 ,
rtInf ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 3 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
0 ) ; _ssSetOutputPortConnected ( rts , 0 , 1 ) ; _ssSetOutputPortBeingMerged
( rts , 0 , 0 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } {
SimStruct * rts = ssGetSFunction ( rtS , 19 ) ; static time_T sfcnPeriod [ 1
] ; static time_T sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void )
memset ( ( void * ) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void )
memset ( ( void * ) sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ;
ssSetSampleTimePtr ( rts , & sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts ,
& sfcnOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; {
static struct _ssBlkInfo2 _blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = &
_blkInfo2 ; ssSetBlkInfo2Ptr ( rts , blkInfo2 ) ; } { static struct
_ssPortInfo2 _portInfo2 ; struct _ssPortInfo2 * portInfo2 = & _portInfo2 ;
_ssSetBlkInfo2PortInfo2Ptr ( rts , portInfo2 ) ; } ssSetMdlInfoPtr ( rts ,
ssGetMdlInfoPtr ( rtS ) ) ; { static struct _ssSFcnModelMethods2 methods2 ;
ssSetModelMethods2 ( rts , & methods2 ) ; } { static struct
_ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 ( rts , & methods3 ) ; } {
static struct _ssSFcnModelMethods4 methods4 ; ssSetModelMethods4 ( rts , &
methods4 ) ; } { static struct _ssStatesInfo2 statesInfo2 ; static
ssPeriodicStatesInfo periodicStatesInfo ; static ssJacobianPerturbationBounds
jacPerturbationBounds ; ssSetStatesInfo2 ( rts , & statesInfo2 ) ;
ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , ( ( const real_T * ) & SILS_20241709_RGND ) ) ;
_ssSetInputPortNumDimensions ( rts , 0 , 1 ) ; ssSetInputPortWidthAsInt ( rts
, 0 , 1 ) ; } } { static struct _ssPortOutputs outputPortInfo [ 1 ] ;
ssSetPortInfoForOutputs ( rts , & outputPortInfo [ 0 ] ) ;
_ssSetNumOutputPorts ( rts , 1 ) ; { static struct _ssOutPortUnit
outputPortUnits [ 1 ] ; _ssSetPortInfo2ForOutputUnits ( rts , &
outputPortUnits [ 0 ] ) ; } ssSetOutputPortUnit ( rts , 0 , 0 ) ; { static
struct _ssOutPortCoSimAttribute outputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForOutputCoSimAttribute ( rts , & outputPortCoSimAttribute [ 0
] ) ; } ssSetOutputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
_ssSetOutputPortNumDimensions ( rts , 0 , 1 ) ; ssSetOutputPortWidthAsInt (
rts , 0 , 4 ) ; ssSetOutputPortSignal ( rts , 0 , ( ( real_T * ) rtB .
cvndu2lgp0 ) ) ; } } ssSetModelName ( rts , "sfunc_RW_TX" ) ; ssSetPath ( rts
, "SILS_20241709/S-Function5" ) ; if ( ssGetRTModel ( rtS ) == ( NULL ) ) {
ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; }
else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , (
NULL ) ) ; ssSetRootSS ( rts , rts ) ; } ssSetVersion ( rts ,
SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray * sfcnParams [ 1 ] ;
ssSetSFcnParamsCount ( rts , 1 ) ; ssSetSFcnParamsPtr ( rts , & sfcnParams [
0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction5_P1_Size_fiagzwfsx1 ) ; } { raccelLoadSFcnMexFile ( "sfunc_RW_TX" ,
"SILS_20241709:544" , rts , 19 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 ,
rtInf ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 3 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
0 ) ; _ssSetOutputPortConnected ( rts , 0 , 1 ) ; _ssSetOutputPortBeingMerged
( rts , 0 , 0 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } {
SimStruct * rts = ssGetSFunction ( rtS , 20 ) ; static time_T sfcnPeriod [ 1
] ; static time_T sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void )
memset ( ( void * ) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void )
memset ( ( void * ) sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ;
ssSetSampleTimePtr ( rts , & sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts ,
& sfcnOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; {
static struct _ssBlkInfo2 _blkInfo2 ; struct _ssBlkInfo2 * blkInfo2 = &
_blkInfo2 ; ssSetBlkInfo2Ptr ( rts , blkInfo2 ) ; } { static struct
_ssPortInfo2 _portInfo2 ; struct _ssPortInfo2 * portInfo2 = & _portInfo2 ;
_ssSetBlkInfo2PortInfo2Ptr ( rts , portInfo2 ) ; } ssSetMdlInfoPtr ( rts ,
ssGetMdlInfoPtr ( rtS ) ) ; { static struct _ssSFcnModelMethods2 methods2 ;
ssSetModelMethods2 ( rts , & methods2 ) ; } { static struct
_ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 ( rts , & methods3 ) ; } {
static struct _ssSFcnModelMethods4 methods4 ; ssSetModelMethods4 ( rts , &
methods4 ) ; } { static struct _ssStatesInfo2 statesInfo2 ; static
ssPeriodicStatesInfo periodicStatesInfo ; static ssJacobianPerturbationBounds
jacPerturbationBounds ; ssSetStatesInfo2 ( rts , & statesInfo2 ) ;
ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ;
ssSetJacobianPerturbationBounds ( rts , & jacPerturbationBounds ) ; } {
_ssSetNumInputPorts ( rts , 1 ) ; static struct _ssPortInputs inputPortInfo [
1 ] ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
struct _ssInPortUnit inputPortUnits [ 1 ] ; _ssSetPortInfo2ForInputUnits (
rts , & inputPortUnits [ 0 ] ) ; } ssSetInputPortUnit ( rts , 0 , 0 ) ; {
static struct _ssInPortCoSimAttribute inputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForInputCoSimAttribute ( rts , & inputPortCoSimAttribute [ 0 ]
) ; } ssSetInputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
ssSetInputPortRequiredContiguous ( rts , 0 , 1 ) ; ssSetInputPortSignal ( rts
, 0 , ( ( const real_T * ) & SILS_20241709_RGND ) ) ;
_ssSetInputPortNumDimensions ( rts , 0 , 1 ) ; ssSetInputPortWidthAsInt ( rts
, 0 , 1 ) ; } } { static struct _ssPortOutputs outputPortInfo [ 1 ] ;
ssSetPortInfoForOutputs ( rts , & outputPortInfo [ 0 ] ) ;
_ssSetNumOutputPorts ( rts , 1 ) ; { static struct _ssOutPortUnit
outputPortUnits [ 1 ] ; _ssSetPortInfo2ForOutputUnits ( rts , &
outputPortUnits [ 0 ] ) ; } ssSetOutputPortUnit ( rts , 0 , 0 ) ; { static
struct _ssOutPortCoSimAttribute outputPortCoSimAttribute [ 1 ] ;
_ssSetPortInfo2ForOutputCoSimAttribute ( rts , & outputPortCoSimAttribute [ 0
] ) ; } ssSetOutputPortIsContinuousQuantity ( rts , 0 , 0 ) ; {
_ssSetOutputPortNumDimensions ( rts , 0 , 1 ) ; ssSetOutputPortWidthAsInt (
rts , 0 , 4 ) ; ssSetOutputPortSignal ( rts , 0 , ( ( real_T * ) rtB .
mslzotztaf ) ) ; } } ssSetModelName ( rts , "sfunc_RW_TX" ) ; ssSetPath ( rts
, "SILS_20241709/S-Function6" ) ; if ( ssGetRTModel ( rtS ) == ( NULL ) ) {
ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts , ssGetRootSS ( rtS ) ) ; }
else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) ) ; ssSetParentSS ( rts , (
NULL ) ) ; ssSetRootSS ( rts , rts ) ; } ssSetVersion ( rts ,
SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray * sfcnParams [ 1 ] ;
ssSetSFcnParamsCount ( rts , 1 ) ; ssSetSFcnParamsPtr ( rts , & sfcnParams [
0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
SFunction6_P1_Size_nugnt25utq ) ; } { raccelLoadSFcnMexFile ( "sfunc_RW_TX" ,
"SILS_20241709:545" , rts , 20 ) ; if ( ssGetErrorStatus ( rtS ) ) { return
rtS ; } } sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 ,
rtInf ) ; ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 3 ;
ssSetNumNonsampledZCsAsInt ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 ,
0 ) ; _ssSetOutputPortConnected ( rts , 0 , 1 ) ; _ssSetOutputPortBeingMerged
( rts , 0 , 0 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } } return
rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 3 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID3 ( tid ) ; }
