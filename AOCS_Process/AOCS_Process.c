#include "../others/Equipment_Instance.h"

#include "../CmdTlm/cmd_frame_aobc.h"
#include "../CmdTlm/cmd_action_aobc.h"

#include "AOCS_Alignment.h"
#include "AOCS_Vector.h"
#include "AOCS_Method.h"

#include "AOCS_Component.h"
#include "AOCS_Time.h"

#include "AOCS_Process.h"

RW_STRUCT   *rw[4];

unsigned char AOCS_mode;
unsigned char AOCS_mode_old;
unsigned char unloading_flag;
unsigned short mode_change_cycle;

unsigned char AOCS_MTQ;

double AOCS_wt_sun[3];

double AOCS_cont_trq[3];
double AOCS_gain_PSun[3];
double AOCS_gain_DSun[3];
double AOCS_inertia[3][3];

double AOCS_spin_wt;
double AOCS_Sun_Acqui_ang;
double AOCS_Sun_Acqui_vel;
double AOCS_Sun_Acqui_spin;

double AOCS_Sun_AcquiFOG_ang;
double AOCS_Sun_AcquiFOG_vel;
double AOCS_Sun_AcquiFOG_rate;

void mode_change();

//Calculate the difference quaternion
void calc_we(double *wt, double *w, double *we){
	
	we[0] = wt[0] - w[0];
    we[1] = wt[1] - w[1];
    we[2] = wt[2] - w[2];
}

//Calculate the torque required
void calc_trq_coarse_sun(double *Tsun, double *we, double *trq){
	
	trq[0] = -AOCS_inertia[0][0] * (Tsun[0] * AOCS_gain_PSun[0] + we[0] * AOCS_gain_DSun[0]);
	trq[1] = -AOCS_inertia[1][1] * (Tsun[1] * AOCS_gain_PSun[1] + we[1] * AOCS_gain_DSun[1]);
	trq[2] = -AOCS_inertia[2][2] * (Tsun[2] * AOCS_gain_PSun[2] + we[2] * AOCS_gain_DSun[2]);
}

void	AOCS_Init(void){
	
	rw[0] = &rw1;
	rw[1] = &rw2;
	rw[2] = &rw3;
	rw[3] = &rw4;
	
	AOCS_mode = 1;
	AOCS_mode_old = 0;
	mode_change_cycle = 0;
	unloading_flag = 0;
	
	AOCScounter = 0;
	
	set_alignment();
	
	set_RW_param();
	
	set_skew_param();
	
	AOCS_MTQ = 0;
	
	AOCS_wt_sun[0] = 0.0; //target angular velocity
	AOCS_wt_sun[1] = 0.0;
	AOCS_wt_sun[2] = 0.0;
	
	AOCS_cont_trq[0] = 1.2345;
	AOCS_cont_trq[1] = 2.3456;
	AOCS_cont_trq[2] = 3.4567;
	
	AOCS_gain_PSun[0] = 0.01; //for coarse sun mode 
	AOCS_gain_PSun[1] = 0.01;
	AOCS_gain_PSun[2] = 0.01;
	AOCS_gain_DSun[0] = 0.1;
	AOCS_gain_DSun[1] = 0.1;
	AOCS_gain_DSun[2] = 0.1;
	
	AOCS_Sun_Acqui_ang  = 1.0; 	//for Sun Acquisition mode
	AOCS_Sun_Acqui_vel  = 10.0;
	AOCS_Sun_Acqui_spin = 1.0;
	AOCS_spin_wt = 0.0 * DEG2RAD;
	
	AOCS_Sun_AcquiFOG_ang = 0.5;  //for Sun Acquisition mode with FOG
	AOCS_Sun_AcquiFOG_vel = 10.0;
	AOCS_Sun_AcquiFOG_rate = 1.5;
	
	AOCS_inertia[0][0] = 1.1825; //MOI for MDG
	AOCS_inertia[0][1] = 0.0380;
    AOCS_inertia[0][2] = 0.0097;
    AOCS_inertia[1][0] = 0.0380;
    AOCS_inertia[1][1] = 0.8803;
    AOCS_inertia[1][2] = 0.0501;
    AOCS_inertia[2][0] = 0.0097;
    AOCS_inertia[2][1] = 0.0501;
    AOCS_inertia[2][2] = 1.2204;
}

void	AOCS_Process(void){
	
	unsigned char i, j;
	
	//The variables related to the sun
	double SD1_c[3], SD2_c[3], SD3_c[3], SD4_c[3], SD5_c[3], SD6_c[3]; //Solar direction vector in comp CS
	double SD1_b[3], SD2_b[3], SD3_b[3], SD4_b[3], SD5_b[3], SD6_b[3];
	double aveSD_b[3];
	static double old_aveSD_b[3] = {0.0, 0.0, 0.0}; //previous above one
	static double aveaveSD_b[3] = {0.0, 0.0, 0.0};
	static double old_aveaveSD_b[3] = {0.0, 0.0, 0.0};
	static double old_old_aveaveSD_b[3] = {0.0, 0.0, 0.0};
	double TSun[3];
	unsigned char sun_flag = 0;
	
	//The variables related to the geomagnetic
	double EM_c[3];
	double EM_b[3];
	static double old_EM_b[3] = {0.0, 0.0, 0.0};
	static double aveEM_b[3] = {0.0, 0.0, 0.0};
	static double old_aveEM_b[3] = {0.0, 0.0, 0.0};
	static double old_old_aveEM_b[3] = {0.0, 0.0, 0.0};
	
	double MM_b[3];
	double MM_c[3];
	
	//The variables for the angular velocity vector
	double rate_c[3];
	double rate_b[3];
	
	double we[3];
	double RW_trq[4], RW_V[4];
	unsigned short RW_V_comm[4];
	double RW_rate[4];
	
	mode_change();
	
	if(AOCS_mode != 0 && AOCS_mode == AOCS_mode_old){
		
		if(AOCS_mode == 1 || AOCS_mode == 2 || AOCS_mode == 3 || AOCS_mode == 10){
			if(nsas1.driver_super.rx_count == nsas1_rx_count_old){
				nsas1.sun_flag = 0;
			}
			if(nsas2.driver_super.rx_count == nsas2_rx_count_old){
				nsas2.sun_flag = 0;
			}
			if(nsas3.driver_super.rx_count == nsas3_rx_count_old){
				nsas3.sun_flag = 0;
			}
			if(nsas4.driver_super.rx_count == nsas4_rx_count_old){
				nsas4.sun_flag = 0;
			}
			if(nsas5.driver_super.rx_count == nsas5_rx_count_old){
				nsas5.sun_flag = 0;
			}
			if(nsas6.driver_super.rx_count == nsas6_rx_count_old){
				nsas6.sun_flag = 0;
			}
			
			//Calculate the solar direction vector of the comp CS
			NSAS_Angle2Vector(nsas1.x, nsas1.y, SD1_c);
			NSAS_Angle2Vector(nsas2.x, nsas2.y, SD2_c);
			NSAS_Angle2Vector(nsas3.x, nsas3.y, SD3_c);
			NSAS_Angle2Vector(nsas4.x, nsas4.y, SD4_c);
			NSAS_Angle2Vector(nsas5.x, nsas5.y, SD5_c);
			NSAS_Angle2Vector(nsas6.x, nsas6.y, SD6_c);
			
			//Convert solar direction vector from comp CS to body CS
			MatrixVector(NSAS1_c2b_DCM, SD1_c, SD1_b);
			MatrixVector(NSAS2_c2b_DCM, SD2_c, SD2_b);
			MatrixVector(NSAS3_c2b_DCM, SD3_c, SD3_b);
			MatrixVector(NSAS4_c2b_DCM, SD4_c, SD4_b);
			MatrixVector(NSAS5_c2b_DCM, SD5_c, SD5_b);
			MatrixVector(NSAS6_c2b_DCM, SD6_c, SD6_b);
			
			//Combine six NSAS
			NSAS_Combine(SD1_b, SD2_b, SD3_b, SD4_b, SD5_b, SD6_b, aveSD_b, 
						 nsas1.sun_flag, nsas2.sun_flag, nsas3.sun_flag, 
						 nsas4.sun_flag, nsas5.sun_flag, nsas6.sun_flag, &sun_flag);
			
			//Calculate the geomagnetic vector
			GAS_AA2Vector(gas1.x, gas1.y, gas1.z, gas1.ref, EM_c);

			//Convert GAS in component CS into Body CS
			MatrixVector(GAS_c2b_DCM, EM_c, EM_b);
			
			//Take average of geomagnetic vector
			if(AOCScounter >= 0 && AOCScounter < AOCS_MTQ_start_count){
				
				aveEM_b[0] += EM_b[0] / 10.0;
				aveEM_b[1] += EM_b[1] / 10.0;
				aveEM_b[2] += EM_b[2] / 10.0;
				
				aveaveSD_b[0] = aveSD_b[0];
				aveaveSD_b[1] = aveSD_b[1];
				aveaveSD_b[2] = aveSD_b[2];
			}
			
			//Calculate the angular velocity vector
			GYRO_Bin2Vector(gyro1.del_x, gyro1.del_y, gyro1.del_z, rate_c);
			
			//Convert angular velocity
			MatrixVector(GYRO_c2b_DCM, rate_c, rate_b);
		}
		
		if(AOCS_mode == 1 || AOCS_mode == 2 || AOCS_mode == 10){
			//Use B-dot law for mode 1: detumbling mode
			Bdot(old_aveEM_b, aveEM_b, AOCS_MTQ_max_count*AOBC_dt, MM_b);
			
			//Use Spin-sun law for mode 2: Sun Acquisition mode
			if(AOCS_mode == 2){
				Sun_Acquisition(old_aveaveSD_b, aveaveSD_b, old_aveEM_b, aveEM_b, AOCS_spin_wt,
								AOCS_Sun_Acqui_ang, AOCS_Sun_Acqui_vel, AOCS_Sun_Acqui_spin, sun_flag, MM_b);
			}
			
			//Sun Acquisition mode with FOG
			if(AOCS_mode == 10){
				Sun_Acquisition_FOG(old_aveaveSD_b, aveaveSD_b, aveEM_b, rate_b, sun_flag, AOCS_Sun_AcquiFOG_ang, 
									AOCS_Sun_AcquiFOG_vel, AOCS_Sun_AcquiFOG_rate, MM_b);
			}
			
			//Convert magnetic momen vector from body CS into component CS
			MTQ_Body2Comp(MTQ1_c2b, MTQ2_c2b, MTQ3_c2b, MM_b, MM_c);
			
			//start control MTQ
            if(AOCScounter == AOCS_MTQ_start_count){
                MTQcontrol(MM_c);
            }
			//off MTQ
            if(AOCScounter == AOCS_MTQ_stop_count){
                MTQoff();
            }
		}
		
		if(AOCS_mode == 3 || AOCS_mode == 4){
			
			//Mode 3: Coarse sun pointing mode
			if(AOCS_mode == 3){
				
				Coarse_Sun(aveSD_b, sun_flag, TSun);
				
				//Calculate error angular velocity
				calc_we(AOCS_wt_sun, rate_b, we);
				
				//Calculate the torque required
				calc_trq_coarse_sun(TSun, we, AOCS_cont_trq);
			}
				
			// distributes the torque in the distribution law of RW
			for(i = 0; i < 4; i++){
				RW_trq[i] = 0.0;
				for(j = 0; j < 3; j++){
					RW_trq[i] += three_one_skew_D[4][i][j] * AOCS_cont_trq[j];
				}
				
				// The output torque of the individual RW up to 10 [mNm]
				if(RW_trq[i] > 0.01){
					RW_trq[i] = 0.01;
				}
				if(RW_trq[i] < -0.01){
					RW_trq[i] = -0.01;
				}
			}
			
			for(i = 0; i < 4; i++){
				// Calculating the integral term of RW
				RW_I[i] += RW_trq[i] * AOBC_dt;

				// Limit of the integral term
				if(RW_I[i] > RW_Integ_V_limit * RW_tau * RW_kT / RW_R){
					RW_I[i] = RW_Integ_V_limit * RW_tau * RW_kT / RW_R;
				}
				if(RW_I[i] < -RW_Integ_V_limit * RW_tau * RW_kT / RW_R){
					RW_I[i] = -RW_Integ_V_limit * RW_tau * RW_kT / RW_R;
				}
				
				// Calculating a voltage applied to RW
				RW_V[i] = RW_R / RW_kT * (RW_trq[i] + RW_I[i] / RW_tau);
				
				// Voltage limit of RW
				if(RW_V[i] > RW_V_limit){
					RW_V[i] = RW_V_limit;
				}
				if(RW_V[i] < -RW_V_limit){
					RW_V[i] = -RW_V_limit;
				}
				// Generation of voltage command to be sent to the RW of the driver
				RW_V_comm[i] = (unsigned short)(fabs(RW_V[i]) / 50.0 * 65536.0);
			}
			
			RW_V[3] = -1.5;
			RW_V_comm[3] = (unsigned short)(fabs(RW_V[3]) / 50.0 * 65536.0);
			
			for(i = 0; i < 4; i++){
				// Send a command to the RW driver
				RW_tx_comm(rw[i], 0, RW_V_comm[i], 0x0000);
				rw[i]->rw_tx_comm.comm1.bit.motor_drive = 1;
				if(RW_V[i] > 0.0){
					// If positive CW rotation voltage
					rw[i]->rw_tx_comm.comm1.bit.torque_output_direction = 0;
				}else{
					// Negative if CCW rotation voltage
					rw[i]->rw_tx_comm.comm1.bit.torque_output_direction = 1;
				}
			}
			
			for(i = 0; i < 4; i++){
				if(rw[i]->rw_rx_sts.sts1.bit.rotation_direction == 0){ //CW rotation
					RW_rate[i] = (double)rw[i]->rw_rx_sts.sts3;
				}else{ // CCW rotation
					// CCW rotation and negative rotation
					RW_rate[i] = -1.0 * (double)rw[i]->rw_rx_sts.sts3;
				}
			}
		}
		
		for(i = 0; i < 4; i++){
			if(rw[i]->rw_rx_sts.sts3 == 0){
				RW_I[i] = 0.0;
			}
		}
		
		AOCScounter++;
		
		if(AOCScounter == AOCS_MTQ_max_count){
			old_old_aveEM_b[0] = old_aveEM_b[0];
			old_old_aveEM_b[1] = old_aveEM_b[1];
			old_old_aveEM_b[2] = old_aveEM_b[2];
			old_aveEM_b[0] = aveEM_b[0];
			old_aveEM_b[1] = aveEM_b[1];
			old_aveEM_b[2] = aveEM_b[2];
			aveEM_b[0] = 0.0;
			aveEM_b[1] = 0.0;
			aveEM_b[2] = 0.0;
			
			old_old_aveaveSD_b[0] = old_aveaveSD_b[0];
			old_old_aveaveSD_b[1] = old_aveaveSD_b[1];
			old_old_aveaveSD_b[2] = old_aveaveSD_b[2];
			old_aveaveSD_b[0] = aveaveSD_b[0];
			old_aveaveSD_b[1] = aveaveSD_b[1];
			old_aveaveSD_b[2] = aveaveSD_b[2];
			aveaveSD_b[0] = 0.0;
			aveaveSD_b[1] = 0.0;
			aveaveSD_b[2] = 0.0;
			
			AOCScounter = 0;
		}
		
		gps1_rx_count_old = gps1.driver_super.rx_count;
		rw1_rx_count_old = rw1.driver_super.rx_count;
		rw2_rx_count_old = rw2.driver_super.rx_count;
		rw3_rx_count_old = rw3.driver_super.rx_count;
		rw4_rx_count_old = rw4.driver_super.rx_count;
		nsas1_rx_count_old = nsas1.driver_super.rx_count;
		nsas2_rx_count_old = nsas2.driver_super.rx_count;
		nsas3_rx_count_old = nsas3.driver_super.rx_count;
		nsas4_rx_count_old = nsas4.driver_super.rx_count;
		nsas5_rx_count_old = nsas5.driver_super.rx_count;
		nsas6_rx_count_old = nsas6.driver_super.rx_count;
		gyro1_rx_count_old = gyro1.driver_super.rx_count;
		stt1_rx_count_old = stt1.driver_super.rx_count;
	}
}

// change mode function 
void mode_change(){
	
	//mode 0: safe mode - non control
	//mode 1: detumbling mode
	//mode 2: sun acquisition mode
	//mode 3: coarse sun mode
	//mode 4: coarse nadir mode
	//mode 5: fine nadir pointing mode
	//mode 6: target pointing mode
	//mode 7: off-set target mode
	//mode 8: coastal scan mode
	//mode 9: fine sun pointing mode 
	//mode 10: Sun acquisition mode with FOG
	
	//any mode -> mode 1: detumbling mode
	if(AOCS_mode == 1 && AOCS_mode_old != 1){
		switch(mode_change_cycle){
			case 0: CmdSend_PowerOn(DCDC_SNS); break;
			case 20: CmdSend_PowerOn(DCDC_MTQ); break;
			case 40: CmdSend_PowerOff(MTQ_X_OFF); break;
			case 60: CmdSend_PowerOff(MTQ_Y_OFF); break;
			case 80: CmdSend_PowerOff(MTQ_Z_OFF); break;
			case 100: CmdSend_PowerOff(STT); break;
			case 120: CmdSend_PowerOff(RW1_OFF); break;
			case 140: CmdSend_PowerOff(RW2_OFF); break;
			case 160: CmdSend_PowerOff(RW3_OFF); break;
			case 180: CmdSend_PowerOff(RW4_OFF); break;
			case 200: CmdSend_PowerOff(DCDC_RW); break;
			case 220: CmdSend_PowerOff(GPSR); break;
			case 240: CmdSend_PowerOff(NSAS1); break;
			case 260: CmdSend_PowerOff(NSAS2); break;
			case 280: CmdSend_PowerOff(NSAS3); break;
			case 300: CmdSend_PowerOff(NSAS4); break;
			case 320: CmdSend_PowerOff(NSAS5); break;
			case 340: CmdSend_PowerOff(NSAS6); break;
			case 360: CmdSend_PowerOn(GAS); break;
			case 380: CmdSend_PowerOff(GYRO); break;
				
			case 400: 
				AOCS_mode_old = AOCS_mode;
				mode_change_cycle = -1;
				break;
			default: break;
		}
		mode_change_cycle++;
	}
	
	//mode 1 -> mode 2: sun acquisition mode
	if(AOCS_mode == 2 && AOCS_mode_old == 1){
		switch(mode_change_cycle){
			case 0: CmdSend_PowerOn(NSAS1); break;
			case 20: CmdSend_PowerOn(NSAS2); break;
			case 40: CmdSend_PowerOn(NSAS3); break;
			case 60: CmdSend_PowerOn(NSAS4); break;
			case 80: CmdSend_PowerOn(NSAS5); break;
			case 100: CmdSend_PowerOn(NSAS6); break;
				
			case 120:
				AOCS_mode_old = AOCS_mode;
				mode_change_cycle = -1;
				break;
			default: break;
		}
		mode_change_cycle++;
	}
	
	//mode 1 -> mode 10: Sun Acquisition mode - backup mode
	if(AOCS_mode == 10 && AOCS_mode_old == 1){
		switch(mode_change_cycle){
			case 0: CmdSend_PowerOn(NSAS1); break;
			case 20: CmdSend_PowerOn(NSAS2); break;
			case 40: CmdSend_PowerOn(NSAS3); break;
			case 60: CmdSend_PowerOn(NSAS4); break;
			case 80: CmdSend_PowerOn(NSAS5); break;
			case 100: CmdSend_PowerOn(NSAS6); break;
			case 120: CmdSend_PowerOn(GYRO); break;
				
			case 140: 
				AOCS_mode_old = AOCS_mode;
				mode_change_cycle = -1;
				break;
			default: break;
		}
		mode_change_cycle++;
	}
	
	//mode 2 -> mode 3: coarse sun mode
	if(AOCS_mode == 3 && AOCS_mode_old == 2){
		switch(mode_change_cycle){
			case 0: CmdSend_PowerOn(GYRO); break;
			case 20: CmdSend_PowerOn(DCDC_RW); break;
			case 40: CmdSend_PowerOn(RW1_ON); break;
			case 60: CmdSend_PowerOn(RW2_ON); break;
			case 80: CmdSend_PowerOn(RW3_ON); break;
			case 100: CmdSend_PowerOn(RW4_ON); break;
			case 120: MTQoff(); break;
			
			case 140:
				AOCS_mode_old = AOCS_mode;
				mode_change_cycle = -1;
				break;
			default: break;
		}
		mode_change_cycle++;
	}
	
	//mode 3 -> mode 2: sun acquisition mode
	if(AOCS_mode == 2 && AOCS_mode_old == 3){
		switch(mode_change_cycle){
			case 0: CmdSend_PowerOff(RW1_OFF); break;
			case 20: CmdSend_PowerOff(RW2_OFF); break;
			case 40: CmdSend_PowerOff(RW3_OFF); break;
			case 60: CmdSend_PowerOff(RW4_OFF); break;
			case 80: CmdSend_PowerOff(DCDC_RW); break;
			case 100: CmdSend_PowerOff(GYRO); break;
				
			case 120:
				AOCS_mode_old = AOCS_mode;
				mode_change_cycle = -1;
				break;
			default: break;
		}
		mode_change_cycle++;
	}
	
	//mode 10 -> mode 3: coarse sun mode
	if(AOCS_mode == 3 && AOCS_mode_old == 10){
		switch(mode_change_cycle){
			case 0: CmdSend_PowerOn(DCDC_RW); break;
			case 20: CmdSend_PowerOn(RW1_ON); break;
			case 40: CmdSend_PowerOn(RW2_ON); break;
			case 60: CmdSend_PowerOn(RW3_ON); break;
			case 80: CmdSend_PowerOn(RW4_ON); break;
			case 100: MTQoff(); break;
			
			case 120:
				AOCS_mode_old = AOCS_mode;
				mode_change_cycle = -1;
				break;
			default: break;
		}
		mode_change_cycle++;
	}
	
	//mode 3 -> mode 10: sun acquisition mode - backup mode
	if(AOCS_mode == 10 && AOCS_mode_old == 3){
		switch(mode_change_cycle){
			case 0: CmdSend_PowerOff(RW1_ON); break;
			case 20: CmdSend_PowerOff(RW2_ON); break;
			case 40: CmdSend_PowerOff(RW3_ON); break;
			case 60: CmdSend_PowerOff(RW4_ON); break;
			case 80: CmdSend_PowerOff(DCDC_RW); break;
				
			case 100:
				AOCS_mode_old = AOCS_mode;
				mode_change_cycle = -1;
				break;
			default: break;
		}
		mode_change_cycle++;
	}
}