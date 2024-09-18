#ifndef RTW_HEADER_SILS_20241709_h_
#define RTW_HEADER_SILS_20241709_h_
#ifndef SILS_20241709_COMMON_INCLUDES_
#define SILS_20241709_COMMON_INCLUDES_
#include <stdlib.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "SILS_20241709_types.h"
#include <stddef.h>
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include <string.h>
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#define MODEL_NAME SILS_20241709
#define NSAMPLE_TIMES (4) 
#define NINPUTS (0)       
#define NOUTPUTS (5)     
#define NBLOCKIO (161) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (36)   
#elif NCSTATES != 36
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T aupbtlrqjk [ 3 ] ; } oct3g4vhoh ; typedef struct {
real_T c1nd5nsrgs [ 3 ] ; } pigla2omys ; typedef struct { real_T crs3vbajbr ;
real_T pyqwe5rsse ; real_T agveekqpqv ; real_T le233aiaq5 ; real_T b2jeeweznc
; real_T cnte5pmho4 ; } cyjo4x5ck1 ; typedef struct { real_T poahfmj3s1 [ 3 ]
; } d5mabmixx5 ; typedef struct { real_T a4ujzgnsun ; } oxebiebxcs ; typedef
struct { real_T owg3qz0vb0 [ 3 ] ; } haq3dksarh ; typedef struct { real_T
osxy5zocx5 [ 3 ] ; } bmt3ngprbx ; typedef struct { real_T fkae5wqtcb ; }
gacwgjuhge ; typedef struct { real_T ozezoxky3t ; real_T g5m2irbsxw ; real_T
h5cyove4ef ; } fbvoxbsppm ; typedef struct { real_T nd52bn25fb ; } fuwz32fyfq
; typedef struct { real_T jeak4pqr3j ; real_T h0dxk1yimp ; } hdyhizuepg ;
typedef struct { real_T gv3z4rzpl5 [ 3 ] ; real_T pmkqoqavmi ; real_T
fdbl5l21n4 [ 8 ] ; real_T chofn13vqp ; real_T oucj4k4y2q [ 8 ] ; real_T
c5lfdegv0p ; real_T ktlu1ekw1m [ 8 ] ; real_T ju0zmrtbs0 ; real_T innw5sywzg
[ 8 ] ; real_T a5ald3g22i [ 2 ] ; real_T mpca01r2m2 ; real_T asykhtld2n [ 12
] ; real_T ilq2khdcgh [ 4 ] ; real_T lizdm2xqna ; real_T laz0gn3eus ; real_T
fdbl5l21n42 [ 4 ] ; real_T ggo5omtwrw ; real_T gu0xyts5qt ; real_T pktfet50kq
[ 4 ] ; real_T cpp1cmyksa ; real_T necosqfbva ; real_T cyayszgojz [ 4 ] ;
real_T mo4pqo22zy ; real_T ooktctrg5d ; real_T oucj4k4y2qy [ 4 ] ; real_T
onbsvxszlu ; real_T ljv1mgpbcd ; real_T ktlu1ekw1mg [ 4 ] ; real_T lfncg5pvng
; real_T kfpd0jse5u ; real_T innw5sywzgy [ 4 ] ; real_T hcpvpoawqx [ 3 ] ;
real_T jihpm3q5gs [ 4 ] ; real_T gs0kzoznkl [ 3 ] ; real_T jkg4capamp ;
real_T cbjdhhra0o [ 12 ] ; real_T mmxfckfrxp ; real_T ovvyrfj4qq ; real_T
jr21nlhhbn [ 4 ] ; real_T gyoxzzwqiz [ 3 ] ; real_T nljkudwtrt [ 3 ] ; real_T
ht411kslhv [ 3 ] ; real_T ikgewnxpow [ 3 ] ; real_T geuyf21jdw ; real_T
hfnierhiih ; real_T ahgjrqaame ; real_T e3dq3kgfi1 ; real_T lyqxqxi2xc ;
real_T jbyqlkik0e ; real_T owuvzpfz25 ; real_T ddje2kvmhp ; real_T gsio300bjg
; real_T i34t1ktiub ; real_T ozbqnpwmeu ; real_T gbjcwtpbjf ; real_T
ogbf133q1z ; real_T ocfpzffbzh ; real_T pzuqvdky0w ; real_T lzmaq0diab [ 6 ]
; real_T j3kezx3yvk [ 3 ] ; real_T jg4a0jn2o1 [ 3 ] ; real_T lrdfz5anhg [ 4 ]
; real_T d2nlp5u0iz [ 4 ] ; real_T cvndu2lgp0 [ 4 ] ; real_T mslzotztaf [ 4 ]
; real_T ghrb02xtti [ 9 ] ; real_T llfqz3cih1 ; real_T euwsxn4aph ; real_T
kiyg1swe1h ; real_T el4rhtecud ; real_T oqvw4bmbeg [ 3 ] ; real_T ndtffugziw
[ 12 ] ; real_T bqbim0ae4p [ 6 ] ; real_T edgmu1taic [ 4 ] ; real_T
a3fezsr2vw ; real_T kimclls5ui ; real_T eij4bqg1qu [ 4 ] ; real_T a5ybxummfl
[ 3 ] ; real_T gs20g4hobc [ 6 ] ; real_T b5ehs0zt32 [ 3 ] ; real_T hm15o25lmb
[ 3 ] ; real_T chrkykmk4n ; real_T nevppfxrse ; real_T bfrpnyoemv ; real_T
p4vsv1mu0t ; real_T blzsybl1pb [ 7 ] ; real_T nspxciplv0 [ 23 ] ; real_T
i2mlgup0vd ; real_T jn52bjhkjf ; real_T jhikopnu5c ; uint8_T ff5nefkxhm ;
hdyhizuepg iroofsivyk ; fuwz32fyfq aomn2ihkzv ; fbvoxbsppm jjm2phe1us ;
hdyhizuepg df0oudwkj0 ; fuwz32fyfq fovau4dl3r ; fbvoxbsppm a4nohvrqys ;
hdyhizuepg gszk3bc3vp ; fuwz32fyfq k4gpt5xlei ; fbvoxbsppm mzrdmi3ngp ;
hdyhizuepg mx32imycyi ; fuwz32fyfq nbdejsvdft ; fbvoxbsppm dbik3caean ;
gacwgjuhge ejln4gh0kq ; gacwgjuhge gz3hxniyg2 ; gacwgjuhge ka15ybowc1 ;
gacwgjuhge d3cawecdgq ; bmt3ngprbx fe4ousljhv ; bmt3ngprbx hiok3cyxgg ;
haq3dksarh py0l0jdlqp ; haq3dksarh ddwcgokc4u ; haq3dksarh gzwxmb2zl2 ;
haq3dksarh n3omup2lzv ; haq3dksarh awovp5grnq ; haq3dksarh eosebepeyc ;
haq3dksarh ajpyzlqqkx ; haq3dksarh jw1hn4rp4t ; haq3dksarh jacwaaufsl ;
haq3dksarh o05svadaty ; haq3dksarh fovozsjxj1 ; bmt3ngprbx axrlvoalzz ;
haq3dksarh gwin1pepam ; haq3dksarh ab0dpslgku ; oxebiebxcs dd2g34vqpy ;
oxebiebxcs odjpekassu ; oxebiebxcs puqqfcdyyx ; oxebiebxcs fxdnyd3caz ;
oxebiebxcs d3edomwivh ; oxebiebxcs jrtx1iz4hz ; oxebiebxcs jhrf4npwtn ;
cyjo4x5ck1 g5opol5dur ; d5mabmixx5 ca53m05hej ; d5mabmixx5 hdgmktoixc ;
d5mabmixx5 ls5qu2j3gs ; pigla2omys c5rolz011g ; oct3g4vhoh jclektca5o ;
cyjo4x5ck1 e1zykr3jbv ; pigla2omys l15tbbx15x ; oct3g4vhoh aav5pusdkp ; } B ;
typedef struct { real_T hrquh23lee [ 3 ] ; real_T bya5fxrz4g ; real_T
ldpiguzau3 ; real_T jx2njiskco ; real_T fg3gr5w1yf ; real_T l0mqdwlhk0 ;
real_T b5i1u5nxk5 ; real_T ik23rulsvu ; real_T ia3ohifukf ; real_T ewzxpp1cyz
; real_T hdjjo4r4gm ; real_T coji3apumi ; real_T m2ylj5cu2h ; real_T
dbnkttelok ; real_T fzlqp4iexm [ 3 ] ; real_T hsxmncoiha [ 3 ] ; real_T
bpg2iofpcz ; real_T gvdcwkyokb [ 9 ] ; real_T ip0upbstfm [ 9 ] ; real_T
mmkouxeune ; real_T jeeaiz3533 ; real_T i3rfdszits [ 3 ] ; real_T achzjspzj0
[ 3 ] ; struct { void * LoggedData [ 2 ] ; } fkrgzvbnng ; struct { void *
AQHandles ; } lqwrbhd21x ; struct { void * AQHandles ; } ko5el0avio ; struct
{ void * AQHandles ; } d11ycakunl ; struct { void * LoggedData [ 2 ] ; }
gfupvo0drt ; struct { void * LoggedData [ 2 ] ; } dygea0idgb ; struct { void
* LoggedData [ 4 ] ; } hflxu4olzs ; struct { void * LoggedData ; } o3ta01udts
; struct { void * LoggedData ; } kelxgbj5f2 ; uint32_T kjzrcidvjf [ 3 ] ;
uint32_T mc4jx3i45v ; uint32_T eqyhiq4b21 ; uint32_T pvrk0p3rm1 ; uint32_T
jlc5fbv0er ; uint32_T mcbywo0nsz ; uint32_T izuwdoquaq ; uint32_T iy3vcqbba5
; uint32_T inevc2d42p ; uint32_T omztnckksa ; uint32_T peboqqfifh ; uint32_T
hjlfer4jb5 ; uint32_T bhy4lqzamt ; uint32_T l3fdu4jify ; uint32_T dplhf1lj21
[ 3 ] ; uint32_T kjjgprkxtu [ 3 ] ; uint32_T eh3i2huuk3 ; uint32_T dslhvlg4ym
[ 3 ] ; uint32_T czp4qnh0py [ 3 ] ; int_T cu35sqihey ; int8_T azyx1ts0yu ;
int8_T gxgp4hskcm ; int8_T kddtry4ekq ; int8_T ggsva4qu4a ; int8_T icv4qsjrec
; boolean_T hp42fr3fka ; boolean_T kc0x0orqmh ; boolean_T bdwu52mmaq ;
boolean_T odkn5lgudq ; boolean_T lqozsqepug ; } DW ; typedef struct { real_T
hjkn3n4lly [ 3 ] ; real_T oxovzkyrgp [ 6 ] ; real_T pcdkwn41rb [ 4 ] ; real_T
l50b0cuk2h ; real_T b4ena3lr0n ; real_T lbdfwq1i3y ; real_T fnheb54sgb ;
real_T muv5xwjpjd ; real_T argwmtgb5v ; real_T bxdhuzrxz2 ; real_T cmyui1ww54
; real_T i1iguten22 [ 2 ] ; real_T pkf1lgikiz [ 2 ] ; real_T f3jtaj41sb [ 2 ]
; real_T ae0okdyidm ; real_T cok521zc4f ; real_T pf4hzftljn ; real_T
ek1dcgndv4 ; real_T iyvywkyjkt ; real_T cscwx5acjj ; real_T l0nfea2luh [ 3 ]
; } X ; typedef struct { real_T hjkn3n4lly [ 3 ] ; real_T oxovzkyrgp [ 6 ] ;
real_T pcdkwn41rb [ 4 ] ; real_T l50b0cuk2h ; real_T b4ena3lr0n ; real_T
lbdfwq1i3y ; real_T fnheb54sgb ; real_T muv5xwjpjd ; real_T argwmtgb5v ;
real_T bxdhuzrxz2 ; real_T cmyui1ww54 ; real_T i1iguten22 [ 2 ] ; real_T
pkf1lgikiz [ 2 ] ; real_T f3jtaj41sb [ 2 ] ; real_T ae0okdyidm ; real_T
cok521zc4f ; real_T pf4hzftljn ; real_T ek1dcgndv4 ; real_T iyvywkyjkt ;
real_T cscwx5acjj ; real_T l0nfea2luh [ 3 ] ; } XDot ; typedef struct {
boolean_T hjkn3n4lly [ 3 ] ; boolean_T oxovzkyrgp [ 6 ] ; boolean_T
pcdkwn41rb [ 4 ] ; boolean_T l50b0cuk2h ; boolean_T b4ena3lr0n ; boolean_T
lbdfwq1i3y ; boolean_T fnheb54sgb ; boolean_T muv5xwjpjd ; boolean_T
argwmtgb5v ; boolean_T bxdhuzrxz2 ; boolean_T cmyui1ww54 ; boolean_T
i1iguten22 [ 2 ] ; boolean_T pkf1lgikiz [ 2 ] ; boolean_T f3jtaj41sb [ 2 ] ;
boolean_T ae0okdyidm ; boolean_T cok521zc4f ; boolean_T pf4hzftljn ;
boolean_T ek1dcgndv4 ; boolean_T iyvywkyjkt ; boolean_T cscwx5acjj ;
boolean_T l0nfea2luh [ 3 ] ; } XDis ; typedef struct { real_T jwku2vbe0w ;
real_T fudrm4x01v ; real_T nza55qah0g [ 3 ] ; } ExtY ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T ADSW ;
real_T CD ; real_T CR ; real_T GAS_Vref ; real_T GAS_b2c [ 9 ] ; real_T
GAS_seed1 [ 3 ] ; real_T GE ; real_T GGSW ; real_T GPS_position_seed [ 3 ] ;
real_T GPS_time_noise ; real_T GPS_time_seed ; real_T GPperturbationSW ;
real_T GYRO_b2c [ 9 ] ; real_T GYRO_seed1 [ 3 ] ; real_T GYRO_seed2 [ 3 ] ;
real_T I [ 9 ] ; real_T J2 ; real_T MTQ_c2b [ 3 ] ; real_T NSAS1_b2c [ 9 ] ;
real_T NSAS2_b2c [ 9 ] ; real_T NSAS3_b2c [ 9 ] ; real_T NSAS4_b2c [ 9 ] ;
real_T NSAS5_b2c [ 9 ] ; real_T NSAS6_b2c [ 9 ] ; real_T NSAS_ang_limit ;
real_T NSAS_seed1 ; real_T NSAS_seed2 ; real_T NSAS_x_noise ; real_T
NSAS_y_noise ; real_T RW_Gamp ; real_T RW_J ; real_T RW_Rsc ; real_T RW_kE ;
real_T RW_kT ; real_T SRPSW ; real_T STT1_b2c_quat [ 4 ] ; real_T STT_AD_prob
; real_T STT_FOV ; real_T STT_moon_ang_limit ; real_T STT_seed1 [ 3 ] ;
real_T STT_sun_ang_limit ; real_T TOLERANCE ; real_T UT1_UTC ; real_T area ;
real_T arm [ 3 ] ; real_T earth_radius ; real_T ele [ 6 ] ; real_T jd ;
real_T pSR ; real_T q_ini [ 4 ] ; real_T rem_mag [ 3 ] ; real_T rem_magSW ;
real_T three_one_skew_matrix [ 12 ] ; real_T wE [ 3 ] ; real_T w_ini [ 3 ] ;
real_T z0_const ; real_T z0_const_m1oeisvxny ; real_T z0_const_gejhxxdnvf ;
real_T z0_const_otzh2whnvs ; real_T z0_const_h3tpk4wmcz ; real_T
z0_const_pdn2lzrjdp ; real_T NormalizeVector_maxzero ; real_T
NormalizeVector_maxzero_lpqo5h1ax3 ; real_T
NormalizeVector_maxzero_p5fqgxj0sr ; real_T
NormalizeVector_maxzero_jad2sd3ugf ; real_T
NormalizeVector_maxzero_pk2yr3b0h2 ; real_T
NormalizeVector_maxzero_mjhj4dvvo1 ; real_T
NormalizeVector_maxzero_hdshd0fhdt ; real_T
NormalizeVector_maxzero_ngb4rhu5uq ; real_T
NormalizeVector_maxzero_lt2ddtxhuf ; real_T
NormalizeVector_maxzero_bj3cfn3har ; real_T hour2sec_Gain ; real_T
min2sec_Gain ; real_T gcm3kgm3_Gain ; real_T Gain_Gain ; real_T Gain1_Gain ;
real_T Gain2_Gain ; real_T Gain_Gain_dkxjnn2goq ; real_T
Gain1_Gain_ewxpcgxoho ; real_T Gain2_Gain_lev0onxthq ; real_T
Gain_Gain_kwo0jnespy ; real_T Gain1_Gain_oz4csetmxu ; real_T
Gain2_Gain_ekmxnyjdgq ; real_T Constant_Value ; real_T
Constant_Value_kjzrxx2pwp ; real_T Constant_Value_a2453xvslr ; real_T
F107_Value ; real_T aph_Value [ 7 ] ; real_T flag_Value [ 23 ] ; real_T
GPperturbation_RSW_kms2_3_Y0 [ 3 ] ; real_T deg2rad_Gain ; real_T
GG_b_Nm_3_Y0 [ 3 ] ; real_T Gain2_Gain_nbadgk3cn2 ; real_T
Gain_Gain_eirpwpy25e ; real_T Gain1_Gain_o0zodm4wod ; real_T
Gain_Gain_cng034c550 ; real_T Gain2_Gain_jw4ny4s1oi ; real_T
Gain1_Gain_kzqbx21odb ; real_T Gain_Gain_lv4xtg4q1g ; real_T
Gain1_Gain_pmepj0f34k ; real_T Gain2_Gain_nafalxbj3s ; real_T
Constant_Value_p1jiuwoh41 ; real_T Constant_Value_boboxxtlqz ; real_T
Constant_Value_gtgl4kppkk ; real_T remmag_b_Nm_3_Y0 [ 3 ] ; real_T nT2T_Gain
; real_T SRP_b_Nm_3_Y0 [ 3 ] ; real_T Gain_Gain_kpmqxdzy5m ; real_T
Gain1_Gain_k3bjbhd2mm ; real_T Gain2_Gain_pyvsmmmr0o ; real_T
Gain_Gain_bsruw13utp ; real_T Gain1_Gain_gox4r1jkwy ; real_T
Gain2_Gain_gvo2u1fvu1 ; real_T Gain_Gain_b0hzjatx0r ; real_T
Gain1_Gain_i30g2qbzrq ; real_T Gain2_Gain_p5meiylvde ; real_T
Constant_Value_n0n1a4zdn2 ; real_T Constant_Value_ckovqqesxd ; real_T
Constant_Value_og0eeytiqd ; real_T Constant_Value_dxdbvme4z2 ; real_T
rad2deg_Gain ; real_T rad2deg_Gain_lqcbchbdpx ; real_T
rad2deg_Gain_asjrxybn0x ; real_T rad2deg_Gain_okxkrd2arw ; real_T
rad2deg_Gain_cmtkrwe5gj ; real_T rad2deg_Gain_ncnor3j1vi ; real_T
sec_per_day_Gain ; real_T Gain_Gain_itrtl3m3mg ; real_T Gain2_Gain_ckacseigw1
; real_T Gain_Gain_l1oovl4sve ; real_T Gain1_Gain_bysm1h5wxu ; real_T
Gain_Gain_iduukqmyr5 ; real_T Gain2_Gain_kdxyjqh15k ; real_T
Gain1_Gain_bv1sce1ofn ; real_T Gain_Gain_py1ocxtdbg ; real_T
Gain1_Gain_jhnqeojsbu ; real_T Gain2_Gain_dmh23oivep ; real_T TransferFcn1_A
; real_T TransferFcn1_C ; real_T Integrator_IC ; real_T motor_D ; real_T
Switch1_Threshold ; real_T rad2rpm_Gain ; real_T SFunction2_P1_Size [ 2 ] ;
real_T SFunction2_P1 ; real_T TransferFcn1_A_dpe12qdgeu ; real_T
TransferFcn1_C_mq40l21bd4 ; real_T Integrator_IC_mzfuiafljt ; real_T
motor_D_c2y52zc0tt ; real_T Switch1_Threshold_gkzjd52v3i ; real_T
rad2rpm_Gain_l4jmsoyq2v ; real_T SFunction7_P1_Size [ 2 ] ; real_T
SFunction7_P1 ; real_T TransferFcn1_A_iljtckl0vf ; real_T
TransferFcn1_C_e5t3t2za0w ; real_T Integrator_IC_hzjgu55ip5 ; real_T
motor_D_p4qvhshwgu ; real_T Switch1_Threshold_lagl2moogx ; real_T
rad2rpm_Gain_nwcckeryhk ; real_T SFunction8_P1_Size [ 2 ] ; real_T
SFunction8_P1 ; real_T TransferFcn1_A_bf2c2hk3jc ; real_T
TransferFcn1_C_exc4t4wdx0 ; real_T Integrator_IC_ly1tqocwk2 ; real_T
motor_D_ngzzpzruyi ; real_T Switch1_Threshold_nalfp5zuzj ; real_T
rad2rpm_Gain_pceq0ixqio ; real_T SFunction9_P1_Size [ 2 ] ; real_T
SFunction9_P1 ; real_T noise1_Mean [ 3 ] ; real_T noise1_StdDev [ 3 ] ;
real_T UniformRandomNumber_Minimum ; real_T UniformRandomNumber_Maximum ;
real_T UniformRandomNumber_Seed ; real_T Gain_Gain_c5svou2zai ; real_T
Gain2_Gain_fbbevcwdu4 ; real_T Gain_Gain_fso4j4ph32 ; real_T
Gain1_Gain_c2qfvofd2q ; real_T Gain_Gain_cuyfsgurxk ; real_T
Gain2_Gain_o2m2nfo04s ; real_T Gain1_Gain_p0weipavif ; real_T
Gain_Gain_mtzedpzgxf ; real_T Gain1_Gain_fpivyqdmyd ; real_T
Gain2_Gain_eknqknt03s ; real_T km2m_Gain ; real_T ECEFPositiontoLLA_F ;
real_T ECEFPositiontoLLA_R ; real_T m2km_Gain ; real_T Gain2_Gain_bprrd5rgzt
; real_T Gain_Gain_p0g5ioz0tt ; real_T Gain1_Gain_l1syl1i1nc ; real_T
Gain_Gain_cdekolw0kh ; real_T Gain2_Gain_inxlw0u2vd ; real_T
Gain1_Gain_mbywpxkyv2 ; real_T Gain_Gain_gnbof3p2ih ; real_T
Gain1_Gain_ai10xj1huz ; real_T Gain2_Gain_aryjtg3qqc ; real_T
Constant_Value_i11k1gefwq [ 3 ] ; real_T SFunction6_P1_Size [ 2 ] ; real_T
SFunction6_P1 ; real_T SFunction6_P2_Size [ 2 ] ; real_T SFunction6_P2 ;
real_T TransferFcn_A [ 2 ] ; real_T TransferFcn_C [ 2 ] ; real_T
TransferFcn1_A_if5catdafx [ 2 ] ; real_T TransferFcn1_C_dr34rukazf [ 2 ] ;
real_T TransferFcn2_A [ 2 ] ; real_T TransferFcn2_C [ 2 ] ; real_T
Constant5_Value ; real_T SFunction_P1_Size [ 2 ] ; real_T SFunction_P1 ;
real_T SFunction_P2_Size [ 2 ] ; real_T SFunction_P2 ; real_T noise_Mean ;
real_T noise1_Mean_gvm1mdzxhn ; real_T SFunction2_P1_Size_aqgqx4ctqe [ 2 ] ;
real_T SFunction2_P1_psdu2cwwwx ; real_T SFunction2_P2_Size [ 2 ] ; real_T
SFunction2_P2 ; real_T noise_Mean_ieihuy3dfl ; real_T noise1_Mean_dss5wuzq4c
; real_T SFunction3_P1_Size [ 2 ] ; real_T SFunction3_P1 ; real_T
SFunction3_P2_Size [ 2 ] ; real_T SFunction3_P2 ; real_T
noise_Mean_frav3j55dx ; real_T noise1_Mean_mtptilkq10 ; real_T
SFunction4_P1_Size [ 2 ] ; real_T SFunction4_P1 ; real_T SFunction4_P2_Size [
2 ] ; real_T SFunction4_P2 ; real_T noise_Mean_gbwkny3l3m ; real_T
noise1_Mean_k2frfueqdx ; real_T SFunction7_P1_Size_buxc0ymhsr [ 2 ] ; real_T
SFunction7_P1_c0oipohs5p ; real_T SFunction7_P2_Size [ 2 ] ; real_T
SFunction7_P2 ; real_T noise_Mean_fjgbzgisby ; real_T noise1_Mean_jkwutj3nv4
; real_T SFunction8_P1_Size_otc42vq3fz [ 2 ] ; real_T
SFunction8_P1_ddvmotdhun ; real_T SFunction8_P2_Size [ 2 ] ; real_T
SFunction8_P2 ; real_T noise_Mean_hueo1gemyg ; real_T noise1_Mean_m2yixhjiff
; real_T SFunction9_P1_Size_ncpscvdwkx [ 2 ] ; real_T
SFunction9_P1_nunfwxzwxg ; real_T SFunction9_P2_Size [ 2 ] ; real_T
SFunction9_P2 ; real_T noise_Mean_m211emgdl3 [ 3 ] ; real_T noise_StdDev [ 3
] ; real_T TransferFcn_A_c34clvpx4a ; real_T TransferFcn_C_ciybxys4sn ;
real_T TransferFcn1_A_lrz1uxhxld ; real_T TransferFcn1_C_b2uz52ggce ; real_T
TransferFcn2_A_pnihap0iyy ; real_T TransferFcn2_C_f5zsdduuzq ; real_T
SFunction1_P1_Size [ 2 ] ; real_T SFunction1_P1 ; real_T km2m_Gain_c3udq35tim
; real_T RandomNumber_Mean [ 3 ] ; real_T RandomNumber_StdDev [ 3 ] ; real_T
ECEFPositiontoLLA_F_h5d2qe30it ; real_T ECEFPositiontoLLA_R_dv1fhj4bwm ;
real_T noise3_Minimum ; real_T SFunction5_P1_Size [ 2 ] ; real_T
SFunction5_P1 ; real_T rpm2rad_Gain ; real_T rpm2rad1_Gain ; real_T
rpm2rad2_Gain ; real_T rpm2rad3_Gain ; real_T Gain_Gain_kyqyxgfjjc ; real_T
Gain1_Gain_jdzh1vayht ; real_T Gain2_Gain_mjvcbm4pqd ; real_T
Gain_Gain_ag50armt4q ; real_T Gain1_Gain_hahbyfhvn1 ; real_T
Gain2_Gain_bob4otocpt ; real_T Gain_Gain_du1axyb1td ; real_T
Gain1_Gain_cjxo0bvxyl ; real_T Gain2_Gain_cyuruau31y ; real_T IC_Value [ 4 ]
; real_T IC1_Value [ 3 ] ; real_T losstorquepropotionto_Gain ; real_T
losstorquepropotionto_Gain_hahtzed0yk ; real_T
losstorquepropotionto_Gain_ftpubwm50g ; real_T
losstorquepropotionto_Gain_k3z3t2gd1a ; real_T reactiontorque_Gain ; real_T
TransferFcn_A_aashwww0mz ; real_T TransferFcn_C_kwbfsnl1hg ; real_T
TransferFcn_A_gmkfu1bp5e ; real_T TransferFcn_C_n45ccaftaw ; real_T
TransferFcn_A_axh3uxseti ; real_T TransferFcn_C_c3yi1bxnht ; real_T
nT_2_T_Gain ; real_T Integrator_IC_fuz2mronvk ; real_T
rad2deg_Gain_i0zxrskrml ; real_T nvdegsec_Mean [ 3 ] ; real_T nvdegsec_StdDev
[ 3 ] ; real_T nudegsec2_Mean [ 3 ] ; real_T nudegsec2_StdDev [ 3 ] ; real_T
Switch_Threshold ; real_T Switch_Threshold_a5rkjww04l ; real_T
Switch_Threshold_eczahcudx1 ; real_T Switch_Threshold_mxo352pg2c ; real_T
Constant6_Value ; real_T Constant2_Value ; real_T Constant12_Value ; real_T
Constant15_Value ; real_T Constant4_Value ; real_T Constant1_Value ; real_T
Constant3_Value ; real_T Constant1_Value_iq2e102mi0 ; real_T
Constant2_Value_fgyxvvitry ; real_T Constant3_Value_mtqeqchjq3 ; real_T
Constant6_Value_oipnu5fd53 ; real_T Constant_Value_ns0uhctphf ; real_T
Constant_Value_icfwmptllg ; real_T Constant1_Value_oqvdx5zpsu ; real_T
Constant2_Value_e1f4g20e1v ; real_T Constant_Value_amoommf0mg ; real_T
Constant_Value_mq4m5be1k3 ; real_T Constant_Value_kcvsynl3gu ; real_T
Constant_Value_ggebjt2fys ; real_T Constant_Value_kblt0a3uql ; real_T
Constant_Value_hgvjimspu2 ; real_T Constant_Value_jyoylqpxtd ; real_T
Constant_Value_kxh4uvpty4 ; real_T Constant_Value_czynuf313b ; real_T
Constant_Value_h4xungkdn0 ; real_T Constant_Value_but5tairxf ; real_T
Constant_Value_kg1gkk2nel ; real_T Constant_Value_ckqmocsjmk ; real_T
Constant_Value_jdq04jy3wj ; real_T Constant_Value_mydahigf2l ; real_T
SFunction1_P1_Size_oju10to1ph [ 2 ] ; real_T SFunction1_P1_ku32nmmjfh ;
real_T SFunction3_P1_Size_esjea1ngwl [ 2 ] ; real_T SFunction3_P1_jzwtpm1uma
; real_T SFunction4_P1_Size_odtljxchme [ 2 ] ; real_T
SFunction4_P1_edpc41wy4o ; real_T SFunction5_P1_Size_fiagzwfsx1 [ 2 ] ;
real_T SFunction5_P1_brpnppqifr ; real_T SFunction6_P1_Size_nugnt25utq [ 2 ]
; real_T SFunction6_P1_edgmn5fq4g ; real_T Constant_Value_hmchyhprrs ; real_T
Constant1_Value_abguselunm [ 3 ] ; real_T Constant2_Value_gegmpg2rvu [ 2 ] ;
real_T Constant_Value_lxzojy1yts ; real_T Constant_Value_hupkchseos ; real_T
Constant1_Value_ej0jppt02k [ 3 ] ; real_T Constant2_Value_cthnum5wwf [ 2 ] ;
real_T Constant_Value_m2hdvkft2v ; real_T Constant_Value_ndyne2tsni ; real_T
Constant1_Value_la1yhx1hao [ 3 ] ; real_T Constant2_Value_gn4fk3d1lp [ 2 ] ;
real_T Constant_Value_iqckjhnrkz ; real_T Constant_Value_ghgnj1qkgx ; real_T
Constant1_Value_j0a4ub2khm [ 3 ] ; real_T Constant2_Value_aeurx5t4ck [ 2 ] ;
real_T Constant_Value_fvwnrwg2d1 ; real_T Constant_Value_ejbbt4py2k ; real_T
Constant1_Value_g3xactptzz [ 3 ] ; real_T Constant2_Value_kj0dkshoay [ 2 ] ;
real_T Constant_Value_fnhawrwcfw ; real_T Constant_Value_iba131uo1r ; real_T
Constant1_Value_nc5rt4jowx [ 3 ] ; real_T Constant2_Value_nqgiw5gjgz [ 2 ] ;
real_T Constant_Value_k3ehwbv3db ; real_T Gain_Gain_jiwysirinb ; real_T
Gain_Gain_gueaxs1w4d ; real_T Gain_Gain_o54eldgojd ; real_T
Gain_Gain_gdjmrybomw ; real_T Gain_Gain_jzbglr3iwn ; real_T
Gain_Gain_ijnc3iled3 ; real_T Constant2_Value_gqzethcbdt [ 3 ] ; real_T
b0degsec_Value [ 3 ] ; real_T Constant_Value_g3sjkewgl1 ; real_T
Constant1_Value_hlcqpzkeg5 ; real_T Constant2_Value_jyuv2gy0ao ; real_T
Constant3_Value_axvubao2wd ; real_T Switch2_Threshold ; real_T
Constant_Value_ovuyhiuyim ; real_T Constant1_Value_oxbz4wjuse ; real_T
Constant2_Value_pdtexc4kgl ; real_T Constant3_Value_ds1jzpwkjt ; real_T
Switch2_Threshold_hj15nt1i3x ; real_T Constant_Value_br1klnkrdq ; real_T
Constant1_Value_jbsud0br1l ; real_T Constant2_Value_lepgnru1ev ; real_T
Constant3_Value_pq0io1rx2d ; real_T Switch2_Threshold_f3oy1s34eo ; real_T
Constant_Value_kibc2xmwm0 ; real_T Constant1_Value_bvl32d0cmp ; real_T
Constant2_Value_oaj3bo5322 ; real_T Constant3_Value_ihqrcdemxt ; real_T
Switch2_Threshold_fnlhdgazir ; } ; extern const real_T SILS_20241709_RGND ;
extern const char * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX
; extern DW rtDW ; extern ExtY rtY ; extern P rtP ; extern mxArray *
mr_SILS_20241709_GetDWork ( ) ; extern void mr_SILS_20241709_SetDWork ( const
mxArray * ssDW ) ; extern mxArray *
mr_SILS_20241709_GetSimStateDisallowedBlocks ( ) ; extern void MdlUpdateTID2
( int_T tid ) ; extern void MdlOutputsTID2 ( int_T tid ) ; extern const
rtwCAPI_ModelMappingStaticInfo * SILS_20241709_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern
const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern const int_T gblNumRootInportBlks ; extern const int_T
gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ; extern
const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [ ] ;
extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model (
ssExecutionInfo * executionInfo ) ;
#endif
