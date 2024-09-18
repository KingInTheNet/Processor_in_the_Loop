#include "ext_types.h"
static DataTypeInfo rtDataTypeInfoTable [ ] = { { "real_T" , 0 , 8 } , {
"real32_T" , 1 , 4 } , { "int8_T" , 2 , 1 } , { "uint8_T" , 3 , 1 } , {
"int16_T" , 4 , 2 } , { "uint16_T" , 5 , 2 } , { "int32_T" , 6 , 4 } , {
"uint32_T" , 7 , 4 } , { "boolean_T" , 8 , 1 } , { "fcn_call_T" , 9 , 0 } , {
"int_T" , 10 , 4 } , { "pointer_T" , 11 , 8 } , { "action_T" , 12 , 8 } , {
"timer_uint32_pair_T" , 13 , 8 } , { "physical_connection" , 14 , 8 } , {
"int64_T" , 15 , 8 } , { "uint64_T" , 16 , 8 } , { "uint64_T" , 17 , 8 } , {
"int64_T" , 18 , 8 } , { "uint_T" , 19 , 32 } , { "char_T" , 20 , 8 } , {
"uchar_T" , 21 , 8 } , { "time_T" , 22 , 8 } } ; static uint_T
rtDataTypeSizes [ ] = { sizeof ( real_T ) , sizeof ( real32_T ) , sizeof (
int8_T ) , sizeof ( uint8_T ) , sizeof ( int16_T ) , sizeof ( uint16_T ) ,
sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof ( boolean_T ) , sizeof (
fcn_call_T ) , sizeof ( int_T ) , sizeof ( pointer_T ) , sizeof ( action_T )
, 2 * sizeof ( uint32_T ) , sizeof ( int32_T ) , sizeof ( int64_T ) , sizeof
( uint64_T ) , sizeof ( uint64_T ) , sizeof ( int64_T ) , sizeof ( uint_T ) ,
sizeof ( char_T ) , sizeof ( uchar_T ) , sizeof ( time_T ) } ; static const
char_T * rtDataTypeNames [ ] = { "real_T" , "real32_T" , "int8_T" , "uint8_T"
, "int16_T" , "uint16_T" , "int32_T" , "uint32_T" , "boolean_T" ,
"fcn_call_T" , "int_T" , "pointer_T" , "action_T" , "timer_uint32_pair_T" ,
"physical_connection" , "int64_T" , "uint64_T" , "uint64_T" , "int64_T" ,
"uint_T" , "char_T" , "uchar_T" , "time_T" } ; static DataTypeTransition
rtBTransitions [ ] = { { ( char_T * ) ( & rtB . gv3z4rzpl5 [ 0 ] ) , 0 , 0 ,
274 } , { ( char_T * ) ( & rtB . ff5nefkxhm ) , 3 , 0 , 1 } , { ( char_T * )
( & rtB . iroofsivyk . jeak4pqr3j ) , 0 , 0 , 2 } , { ( char_T * ) ( & rtB .
aomn2ihkzv . nd52bn25fb ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . jjm2phe1us
. ozezoxky3t ) , 0 , 0 , 3 } , { ( char_T * ) ( & rtB . df0oudwkj0 .
jeak4pqr3j ) , 0 , 0 , 2 } , { ( char_T * ) ( & rtB . fovau4dl3r . nd52bn25fb
) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . a4nohvrqys . ozezoxky3t ) , 0 , 0
, 3 } , { ( char_T * ) ( & rtB . gszk3bc3vp . jeak4pqr3j ) , 0 , 0 , 2 } , {
( char_T * ) ( & rtB . k4gpt5xlei . nd52bn25fb ) , 0 , 0 , 1 } , { ( char_T *
) ( & rtB . mzrdmi3ngp . ozezoxky3t ) , 0 , 0 , 3 } , { ( char_T * ) ( & rtB
. mx32imycyi . jeak4pqr3j ) , 0 , 0 , 2 } , { ( char_T * ) ( & rtB .
nbdejsvdft . nd52bn25fb ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . dbik3caean
. ozezoxky3t ) , 0 , 0 , 3 } , { ( char_T * ) ( & rtB . ejln4gh0kq .
fkae5wqtcb ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . gz3hxniyg2 . fkae5wqtcb
) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . ka15ybowc1 . fkae5wqtcb ) , 0 , 0
, 1 } , { ( char_T * ) ( & rtB . d3cawecdgq . fkae5wqtcb ) , 0 , 0 , 1 } , {
( char_T * ) ( & rtB . fe4ousljhv . osxy5zocx5 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . hiok3cyxgg . osxy5zocx5 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . py0l0jdlqp . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . ddwcgokc4u . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . gzwxmb2zl2 . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . n3omup2lzv . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . awovp5grnq . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . eosebepeyc . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . ajpyzlqqkx . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . jw1hn4rp4t . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . jacwaaufsl . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . o05svadaty . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . fovozsjxj1 . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . axrlvoalzz . osxy5zocx5 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . gwin1pepam . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . ab0dpslgku . owg3qz0vb0 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . dd2g34vqpy . a4ujzgnsun ) , 0 , 0 , 1 } , { ( char_T * )
( & rtB . odjpekassu . a4ujzgnsun ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB .
puqqfcdyyx . a4ujzgnsun ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . fxdnyd3caz
. a4ujzgnsun ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . d3edomwivh .
a4ujzgnsun ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . jrtx1iz4hz . a4ujzgnsun
) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . jhrf4npwtn . a4ujzgnsun ) , 0 , 0
, 1 } , { ( char_T * ) ( & rtB . g5opol5dur . crs3vbajbr ) , 0 , 0 , 6 } , {
( char_T * ) ( & rtB . ca53m05hej . poahfmj3s1 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . hdgmktoixc . poahfmj3s1 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . ls5qu2j3gs . poahfmj3s1 [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . c5rolz011g . c1nd5nsrgs [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . jclektca5o . aupbtlrqjk [ 0 ] ) , 0 , 0 , 3 } , { (
char_T * ) ( & rtB . e1zykr3jbv . crs3vbajbr ) , 0 , 0 , 6 } , { ( char_T * )
( & rtB . l15tbbx15x . c1nd5nsrgs [ 0 ] ) , 0 , 0 , 3 } , { ( char_T * ) ( &
rtB . aav5pusdkp . aupbtlrqjk [ 0 ] ) , 0 , 0 , 3 } , { ( char_T * ) ( & rtDW
. hrquh23lee [ 0 ] ) , 0 , 0 , 49 } , { ( char_T * ) ( & rtDW . fkrgzvbnng .
LoggedData [ 0 ] ) , 11 , 0 , 15 } , { ( char_T * ) ( & rtDW . kjzrcidvjf [ 0
] ) , 7 , 0 , 29 } , { ( char_T * ) ( & rtDW . cu35sqihey ) , 10 , 0 , 1 } ,
{ ( char_T * ) ( & rtDW . azyx1ts0yu ) , 2 , 0 , 5 } , { ( char_T * ) ( &
rtDW . hp42fr3fka ) , 8 , 0 , 5 } } ; static DataTypeTransitionTable
rtBTransTable = { 56U , rtBTransitions } ; static DataTypeTransition
rtPTransitions [ ] = { { ( char_T * ) ( & rtP . ADSW ) , 0 , 0 , 628 } } ;
static DataTypeTransitionTable rtPTransTable = { 1U , rtPTransitions } ;
