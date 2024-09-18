#ifndef _AOCS_METHOD_H_
#define _AOCS_METHOD_H_

#include "AOCS_Vector.h"
#include "AOCS_Quaternion.h"

// Bdot Calculation
void Bdot(double *oldB, double *B, double dt, double *M){
	
    M[0] = (oldB[0] - B[0]) / dt;
    M[1] = (oldB[1] - B[1]) / dt;
    M[2] = (oldB[2] - B[2]) / dt;
}

// Sun_Acquisition mode
void Sun_Acquisition(double *old_S, double *S, double *old_B, double *B, double omega_ref, 
			  double k_ang, double k_vel, double k_spin, unsigned char sun_flg, double *M){
				  
	double T_safe[3];
	double T_sun[3];
	double T_ang[3];
	double T_vel[3];
	double T_spin[3];
	double vect[3], vect_sub[3];
	double norm_vect;
	double d_S[3];
	double d_B[3];
	double inner;
	double omega_det;
	double Zm[3] = { 0.0, 0.0, -1.0 };

	d_S[0] = (S[0] - old_S[0]);
	d_S[1] = (S[1] - old_S[1]);
	d_S[2] = (S[2] - old_S[2]);
		
	d_B[0] = (B[0] - old_B[0]);
	d_B[1] = (B[1] - old_B[1]);
	d_B[2] = (B[2] - old_B[2]);
	
	if(sun_flg){
		VectorOuterProduct(Zm, S, T_ang);
		VectorOuterProduct(d_S, S, T_vel);
		
		T_sun[0] = k_ang * T_ang[0] - k_vel * T_vel[0];
		T_sun[1] = k_ang * T_ang[1] - k_vel * T_vel[1];
		T_sun[2] = k_ang * T_ang[2] - k_vel * T_vel[2];
		
		VectorOuterProduct(B, S, vect);

		vect_sub[0] = vect[0];
		vect_sub[1] = vect[1];
		vect_sub[2] = vect[2];

		norm_vect = VectorNorm(vect_sub);

		if(norm_vect){
			inner = VectorInnerProduct(d_B,vect);
			
			omega_det = inner / norm_vect / norm_vect;
			T_spin[0] = k_spin * (omega_ref - omega_det) * S[0];
			T_spin[1] = k_spin * (omega_ref - omega_det) * S[1];
			T_spin[2] = k_spin * (omega_ref - omega_det) * S[2];
		}
		else{		
			T_spin[0] = 0.0;
			T_spin[1] = 0.0;
			T_spin[2] = 0.0;
		}

		T_safe[0] = T_sun[0] + T_spin[0];
		T_safe[1] = T_sun[1] + T_spin[1];
		T_safe[2] = T_sun[2] + T_spin[2];

		VectorOuterProduct(B, T_safe, M);	
	}
	else{
		M[0] = 0;
		M[1] = 0;
		M[2] = 0;
	}
}

//Sun Acquisition Mode with FOG
void Sun_Acquisition_FOG(double *old_S, double *S, double *B, double *w, unsigned char sun_flg, 
						 double k_ang, double k_vel, double k_rate, double *M){
	
	double Zm[3] = { 0.0, 0.0, -1.0 };
	double wt[3] = { 0.0, 0.0, 0.0 };
	double T_ang[3];
	double d_S[3];
	double T_req[3];
	double T_vel[3];
	
	if(sun_flg){
		VectorOuterProduct(Zm, S, T_ang);
		
		d_S[0] = S[0] - old_S[0];
		d_S[1] = S[1] - old_S[1];
		d_S[2] = S[2] - old_S[2];
		
		VectorOuterProduct(d_S, S, T_vel);
		
		T_req[0] = k_ang * T_ang[0] - k_vel * T_vel[0] + k_rate * (wt[0] - w[0]); 
		T_req[1] = k_ang * T_ang[1] - k_vel * T_vel[1] + k_rate * (wt[1] - w[1]); 
		T_req[2] = k_ang * T_ang[2] - k_vel * T_vel[2] + k_rate * (wt[2] - w[2]);
		
		NormalizeVector(T_req);
		VectorOuterProduct(B, T_req, M);
	}
	else {
		M[0] = 0.0;
		M[1] = 0.0;
		M[2] = 0.0;
	}	
}

//Coarse Sun Mode
void Coarse_Sun(double *S, unsigned char sun_flg, double *Tsun){
	double Z[3] = { 0.0, 0.0, -1.0 };
	
	if(sun_flg){
		VectorOuterProduct(Z, S, Tsun);
	}
	else {
		Tsun[0] = 0.0;
		Tsun[1] = 0.0;
		Tsun[2] = 0.0;
	}	
}

// convert the magnetic moment vector
void MTQ_Body2Comp(char MTQ1_b2c, char MTQ2_b2c, char MTQ3_b2c, double *MM_b, double *MM_c){
	
    MM_c[0] = (double)MTQ1_b2c * MM_b[0];
    MM_c[1] = (double)MTQ2_b2c * MM_b[1];
    MM_c[2] = (double)MTQ3_b2c * MM_b[2];
}

//Send a command
void MTQcontrol(double *M){
    unsigned char i, MTQ[3];

    for(i = 0; i < 3; i++){
        if(M[i] > 0.0)      MTQ[i] = 1;
        else if(M[i] < 0.0) MTQ[i] = 2;
        else                MTQ[i] = 3;
    }
    CmdSend_MTQ(MTQ[0], MTQ[1], MTQ[2]);
}

//turn OFF the MTQ 
void MTQoff(){   
    CmdSend_MTQ(3, 3, 3);  
}
  
#endif