#ifndef	AOCS_PROCESS_INCLUDE_
#define	AOCS_PROCESS_INCLUDE_

//#include "AOCS_Quaternion.h"
//#include "AOCS_Kalman_max.h"

void	AOCS_Init(void);
void	AOCS_Process(void);

extern unsigned char AOCS_mode;
extern unsigned char unloading_flag;

extern unsigned char AOCS_mode;
extern unsigned char unloading_flag;
extern unsigned char AOCS_mode_old;
extern unsigned short mode_change_cycle;

extern unsigned short AOCScounter;
extern unsigned short AOCS_MTQ_max_count;
extern unsigned short AOCS_MTQ_start_count;
extern unsigned short AOCS_MTQ_stop_count;

extern double aveEM_b[3];
extern double old_aveEM_b[3];
extern double old_old_aveEM_b[3];

extern double aveSD_b[3];
extern double aveaveSD_b[3];
extern double old_aveaveSD_b[3];
extern double old_old_aveaveSD_b[3];

extern unsigned char AOCS_MTQ;

extern double AOCS_qd[4];
extern double AOCS_qt[4];
extern double AOCS_qt_old[4];
extern double AOCS_wd[3];
extern double AOCS_wt[3];
extern double AOCS_wt_old[3];
extern double AOCS_wt_sun[3]; //for coarse sun mode 

extern double AOCS_gain_PSun[3];
extern double AOCS_gain_DSun[3];

extern double AOCS_inertia[3][3];

extern double AOCS_spin_wt;			//for Sun Acquisition mode without FOG
extern double AOCS_Sun_Acqui_ang;
extern double AOCS_Sun_Acqui_vel;
extern double AOCS_Sun_Acqui_spin;

extern double AOCS_Sun_AcquiFOG_ang;  //for Sun Acquisition mode with FOG
extern double AOCS_Sun_AcquiFOG_vel;
extern double AOCS_Sun_AcquiFOG_rate;

extern double RW_I[4];
extern double RW_R, RW_tau, RW_kE, RW_kT, RW_J;
extern double RW_V_limit;
extern double RW_Integ_V_limit;
extern double RW_rate_limit;

extern double SD1_b[3], SD2_b[3], SD3_b[3], SD4_b[3], SD5_b[3], SD6_b[3];
extern unsigned char sun_flag;
extern double EM_b[3], rate_b[3];


extern double GAS_c2b_quat[4], GAS_c2b_DCM[3][3];
extern double GYRO_c2b_quat[4], GYRO_c2b_DCM[3][3];
extern double NSAS1_c2b_quat[4], NSAS1_c2b_DCM[3][3];
extern double NSAS2_c2b_quat[4], NSAS2_c2b_DCM[3][3];
extern double NSAS3_c2b_quat[4], NSAS3_c2b_DCM[3][3];
extern double NSAS4_c2b_quat[4], NSAS4_c2b_DCM[3][3];
extern double NSAS5_c2b_quat[4], NSAS5_c2b_DCM[3][3];
extern double NSAS6_c2b_quat[4], NSAS6_c2b_DCM[3][3];
extern signed char MTQ1_c2b, MTQ2_c2b, MTQ3_c2b;
extern double STT_c2b_quat[4], STT_c2b_DCM[3][3];

extern double skew_alpha;
extern double skew_beta;
extern double cos_skew_alpha;
extern double sin_skew_alpha;
extern double cos_skew_beta;
extern double sin_skew_beta;
extern double three_one_skew_D[5][4][3];

extern void Quat2DCM(double *q, double DCM[][3]);
extern void set_skew_param();

#endif // AOCS_PROCESS_INCLUDE_
