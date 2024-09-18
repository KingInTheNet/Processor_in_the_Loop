#ifndef _AOCS_COMPONENT_H_
#define _AOCS_COMPONENT_H_

#include "AOCS_Vector.h"

int gps1_rx_count_old;
int rw1_rx_count_old, rw2_rx_count_old, rw3_rx_count_old, rw4_rx_count_old;
int nsas1_rx_count_old, nsas2_rx_count_old, nsas3_rx_count_old, nsas4_rx_count_old, nsas5_rx_count_old, nsas6_rx_count_old;
int gyro1_rx_count_old;
int stt1_rx_count_old;
unsigned short capture_id_old;

double RW_I[4];
double RW_R, RW_tau, RW_kE, RW_kT, RW_J;
double RW_V_limit;
double RW_Integ_V_limit;
double RW_rate_limit;

void set_RW_param(){ 
    RW_I[0] = 0.0;
    RW_I[1] = 0.0;
    RW_I[2] = 0.0;
    RW_I[3] = 0.0;
    
    RW_R = 6.0;
    RW_kT = 0.03;
    RW_kE = 0.03;
    RW_J = 7.34e-4;
    RW_tau = RW_J * RW_R / RW_kE / RW_kT;

    RW_V_limit = 16.0;
    RW_Integ_V_limit = RW_V_limit + 2.0;
    RW_rate_limit = 4000.0;
}

// Function to calculate the solar direction vector of the component coordinate system from the output of the NSAS
void NSAS_Angle2Vector(unsigned char binx, unsigned char biny, double *SD_c){
    // binx: x component of the output of the NSAS
    // biny: y component of the output of the NSAS
    // The output of the NSAS come out with 2 ^ 8 divide the -55 [degC] ~ + 55 [degC]
    
    double x, y;
    x = ((55.0 + 55.0) / 256.0 * (double)binx) - 55.0; // [deg]
    y = ((55.0 + 55.0) / 256.0 * (double)biny) - 55.0; // [deg]
    
    SD_c[0] = tan(x * DEG2RAD);
    SD_c[1] = tan(y * DEG2RAD);
    SD_c[2] = 1.0;
    
    // Standardize
    NormalizeVector(SD_c);  
}

// Six of the function that takes the average value of the solar direction vector of NSAS
void NSAS_Combine(double *SD1_b, double *SD2_b, double *SD3_b, double *SD4_b, double *SD5_b, double *SD6_b ,double *SD_b,
        unsigned char sun_flag1, unsigned char sun_flag2, unsigned char sun_flag3,
		unsigned char sun_flag4, unsigned char sun_flag5, unsigned char sun_flag6 ,unsigned char *sun_flag){
        
    SD_b[0] = 0.0;
    SD_b[1] = 0.0;
    SD_b[2] = 0.0;
    *sun_flag = 0;
    
    // when NSAS1 detected light
    if(sun_flag1){
        SD_b[0] += SD1_b[0];
        SD_b[1] += SD1_b[1];
        SD_b[2] += SD1_b[2];
        *sun_flag = 1;
    }
    
    // when NSAS2 detected light
    if(sun_flag2){
        SD_b[0] += SD2_b[0];
        SD_b[1] += SD2_b[1];
        SD_b[2] += SD2_b[2];
        *sun_flag = 1;
    }
    
    // when NSAS3 detected light
    if(sun_flag3){
        SD_b[0] += SD3_b[0];
        SD_b[1] += SD3_b[1];
        SD_b[2] += SD3_b[2];
        *sun_flag = 1;
    }
	
	// when NSAS4 detected light
	if(sun_flag4){
		SD_b[0] += SD4_b[0];
		SD_b[1] += SD4_b[1];
		SD_b[2] += SD4_b[2];
		*sun_flag = 1;
	}
	
	// when NSAS5 detected light
	if(sun_flag5){
		SD_b[0] += SD5_b[0];
		SD_b[1] += SD5_b[1];
		SD_b[2] += SD5_b[2];
		*sun_flag = 1;
	}
    
	// when NSAS6 detected light
	if(sun_flag6){
		SD_b[0] += SD6_b[0];
		SD_b[1] += SD6_b[1];
		SD_b[2] += SD6_b[2];
		*sun_flag = 1;
	}
	
    if(*sun_flag){
        // Normalize
        NormalizeVector(SD_b);
    }else{
        SD_b[0] = 4.0;
        SD_b[1] = 4.0;
        SD_b[2] = 4.0;
    }
}

// Function that computes the geomagnetic vector in the component coordinate system from the output of the GAS
void GAS_AA2Vector(short x, short y, short z, short ref, double *EM_c){
    // Draw the reference voltage from the output of each axis of the GAS
    EM_c[0] = (double)(x - ref);
    EM_c[1] = (double)(y - ref);
    EM_c[2] = (double)(z - ref);
}

// Function to calculate the angular velocity vector of the component coordinate system from the output of the GYRO
void GYRO_Bin2Vector(long x, long y, long z, double *rate_c){
    // Angular velocity output of GYRO from -10[deg/s] to +10[deg/s] is splitted into 32bit
    rate_c[0] = x * (10.0 / 0x80000000) * DEG2RAD;
    rate_c[1] = y * (10.0 / 0x80000000) * DEG2RAD;
    rate_c[2] = z * (10.0 / 0x80000000) * DEG2RAD;  
}

// Function that calculates the position vector of the ECEF system [km] from a GPS output
void GPS_Bin2Vector(long long x, long long y, long long z, double *pos){
    pos[0] = (double)x / 1000000.0;
    pos[1] = (double)y / 1000000.0;
    pos[2] = (double)z / 1000000.0;
}

#endif