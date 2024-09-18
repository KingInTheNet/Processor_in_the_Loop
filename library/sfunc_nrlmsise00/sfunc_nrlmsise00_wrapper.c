/*
  *
  *   --- THIS FILE GENERATED BY S-FUNCTION BUILDER: 3.0 ---
  *
  *   This file is a wrapper S-function produced by the S-Function
  *   Builder which only recognizes certain fields.  Changes made
  *   outside these fields will be lost the next time the block is
  *   used to load, edit, and resave this file. This file will be overwritten
  *   by the S-function Builder block. If you want to edit this file by hand, 
  *   you must change it only in the area defined as:  
  *
  *        %%%-SFUNWIZ_wrapper_XXXXX_Changes_BEGIN 
  *            Your Changes go here
  *        %%%-SFUNWIZ_wrapper_XXXXXX_Changes_END
  *
  *   For better compatibility with the Simulink Coder, the
  *   "wrapper" S-function technique is used.  This is discussed
  *   in the Simulink Coder User's Manual in the Chapter titled,
  *   "Wrapper S-functions".
  *
  *   Created: Tue Mar 11 10:18:54 2014
  */


/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include "nrlmsise-00.h"
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
 
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void sfunc_nrlmsise00_Outputs_wrapper(const real_T *lat,
                          const real_T *lon,
                          const real_T *alt,
                          const real_T *year,
                          const real_T *DOY,
                          const real_T *UT,
                          const real_T *LST,
                          const real_T *F107A,
                          const real_T *F107,
                          const real_T *aph,
                          const real_T *flags,
                          real_T *T,
                          real_T *rho)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
struct nrlmsise_output output;
struct nrlmsise_input input;
struct nrlmsise_flags strct_flags;
struct ap_array strct_aph;
int i;

for(i = 0; i < 7; i++){
    strct_aph.a[i] = aph[i];
}

strct_flags.switches[0] = 0;
for(i = 0; i < 23; i++){
    strct_flags.switches[i + 1] = (int)flags[i];
}

// check unit
input.g_lat  = *lat;
input.g_long = *lon;
input.alt    = *alt;
input.year   = (int)*year;
input.doy    = (int)*DOY;
input.sec    = *UT;
input.lst    = *LST;
input.f107A  = *F107A;
input.f107   = *F107;
input.ap     = aph[0];

gtd7(&input, &strct_flags, &output);

*T = output.t[0];
*rho = output.d[5];
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
