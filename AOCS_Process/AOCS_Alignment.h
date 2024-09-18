// Information of Component alignment 

#ifndef _AOCS_ALIGNMENT_H_
#define _AOCS_ALIGNMENT_H_

#include "AOCS_Common.h"
#include "AOCS_Matrix.h"
#include "AOCS_Quaternion.h"

// GAS
double GAS_c2b_Z =   0.0 * DEG2RAD;
double GAS_c2b_Y =   0.0 * DEG2RAD;
double GAS_c2b_X = -90.0 * DEG2RAD;
double GAS_c2b_quat[4], GAS_c2b_DCM[3][3];

// GYRO
double GYRO_c2b_Z = -90.0 * DEG2RAD;
double GYRO_c2b_Y =   0.0 * DEG2RAD;
double GYRO_c2b_X =  90.0 * DEG2RAD;
double GYRO_c2b_quat[4], GYRO_c2b_DCM[3][3];

// NSAS
double NSAS1_c2b_Z = 180.0 * DEG2RAD;
double NSAS1_c2b_Y = -90.0 * DEG2RAD;
double NSAS1_c2b_X =   0.0 * DEG2RAD;
double NSAS1_c2b_quat[4], NSAS1_c2b_DCM[3][3];

double NSAS2_c2b_Z = 180.0 * DEG2RAD;
double NSAS2_c2b_Y = 180.0 * DEG2RAD;
double NSAS2_c2b_X =   0.0 * DEG2RAD;
double NSAS2_c2b_quat[4], NSAS2_c2b_DCM[3][3];

double NSAS3_c2b_Z = 0.0 * DEG2RAD;
double NSAS3_c2b_Y = 0.0 * DEG2RAD;
double NSAS3_c2b_X = 0.0 * DEG2RAD;
double NSAS3_c2b_quat[4], NSAS3_c2b_DCM[3][3];

double NSAS4_c2b_Z = -180.0 * DEG2RAD;
double NSAS4_c2b_Y =   90.0 * DEG2RAD;
double NSAS4_c2b_X =    0.0 * DEG2RAD;
double NSAS4_c2b_quat[4], NSAS4_c2b_DCM[3][3];

double NSAS5_c2b_Z = -90.0 * DEG2RAD;
double NSAS5_c2b_Y =   0.0 * DEG2RAD;
double NSAS5_c2b_X = -90.0 * DEG2RAD;
double NSAS5_c2b_quat[4], NSAS5_c2b_DCM[3][3];

double NSAS6_c2b_Z = 90.0 * DEG2RAD;
double NSAS6_c2b_Y =  0.0 * DEG2RAD;
double NSAS6_c2b_X = 90.0 * DEG2RAD;
double NSAS6_c2b_quat[4], NSAS6_c2b_DCM[3][3];

// MTQ
signed char MTQ1_c2b = 1;
signed char MTQ2_c2b = -1;
signed char MTQ3_c2b = -1;

// RW
double skew_alpha = PI / 4.0;
double skew_beta = 0.615480;
//double skew_beta = asin(1.0 / sqrt(3.0));
double cos_skew_alpha;
double sin_skew_alpha;
double cos_skew_beta;
double sin_skew_beta;
double three_one_skew_D[5][4][3];

// STT
// FOR MDG
double STT_c2b_Z = -90.0 * DEG2RAD;
double STT_c2b_Y =   0.0 * DEG2RAD;
double STT_c2b_X =  90.0 * DEG2RAD;
double STT_c2b_quat[4], STT_c2b_DCM[3][3];

// Calculate quaternion and DCM to convert from the component coordinate system in the body coordinate system
void set_alignment(){
    
    Angle2Quat(GAS_c2b_Z, GAS_c2b_Y, GAS_c2b_X, GAS_c2b_quat);
    Quat0Positive(GAS_c2b_quat);
    Quat2DCM(GAS_c2b_quat, GAS_c2b_DCM);
    
    Angle2Quat(GYRO_c2b_Z, GYRO_c2b_Y, GYRO_c2b_X, GYRO_c2b_quat);
    Quat0Positive(GYRO_c2b_quat);
    Quat2DCM(GYRO_c2b_quat, GYRO_c2b_DCM);
    
    Angle2Quat(NSAS1_c2b_Z, NSAS1_c2b_Y, NSAS1_c2b_X, NSAS1_c2b_quat);
    Quat0Positive(NSAS1_c2b_quat);
    Quat2DCM(NSAS1_c2b_quat, NSAS1_c2b_DCM);
    
    Angle2Quat(NSAS2_c2b_Z, NSAS2_c2b_Y, NSAS2_c2b_X, NSAS2_c2b_quat);
    Quat0Positive(NSAS2_c2b_quat);
    Quat2DCM(NSAS2_c2b_quat, NSAS2_c2b_DCM);
    
    Angle2Quat(NSAS3_c2b_Z, NSAS3_c2b_Y, NSAS3_c2b_X, NSAS3_c2b_quat);
    Quat0Positive(NSAS3_c2b_quat);
    Quat2DCM(NSAS3_c2b_quat, NSAS3_c2b_DCM);
	
	Angle2Quat(NSAS4_c2b_Z, NSAS4_c2b_Y, NSAS4_c2b_X, NSAS4_c2b_quat);
	Quat0Positive(NSAS4_c2b_quat);
	Quat2DCM(NSAS4_c2b_quat, NSAS4_c2b_DCM);
	
	Angle2Quat(NSAS5_c2b_Z, NSAS5_c2b_Y, NSAS5_c2b_X, NSAS5_c2b_quat);
	Quat0Positive(NSAS5_c2b_quat);
	Quat2DCM(NSAS5_c2b_quat, NSAS5_c2b_DCM);
	
	Angle2Quat(NSAS6_c2b_Z, NSAS6_c2b_Y, NSAS6_c2b_X, NSAS6_c2b_quat);
	Quat0Positive(NSAS6_c2b_quat);
	Quat2DCM(NSAS6_c2b_quat, NSAS6_c2b_DCM);

    Angle2Quat(STT_c2b_Z, STT_c2b_Y, STT_c2b_X, STT_c2b_quat);
    Quat0Positive(STT_c2b_quat);
    Quat2DCM(STT_c2b_quat, STT_c2b_DCM);
    
}

// Calculate the distribution matrix of RW
// 0: use all
// 1: rw1 failure
// 2: rw2 failure
// 3: rw3 failure
// 4: rw4 failure
void set_skew_param(){

    double A[3][4], B[3][3], C[3][3];
    unsigned char i, j, k;
    
    cos_skew_alpha = cos(skew_alpha);
    sin_skew_alpha = sin(skew_alpha);
    cos_skew_beta = cos(skew_beta);
    sin_skew_beta = sin(skew_beta);

    // all
    A[0][0] = 1.0; A[0][1] = 0.0; A[0][2] = 0.0; A[0][3] = cos_skew_alpha * cos_skew_beta;
    A[1][0] = 0.0; A[1][1] = 1.0; A[1][2] = 0.0; A[1][3] = sin_skew_alpha * cos_skew_beta;
    A[2][0] = 0.0; A[2][1] = 0.0; A[2][2] = 1.0; A[2][3] = sin_skew_beta;
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            B[i][j] = 0.0;
            for(k = 0; k < 4; k++){
                B[i][j] += A[i][k] * A[j][k];
            }
        }
    }
    MatrixInverse(B, C);

	for(i = 0; i < 4; i++){
		for(j = 0; j < 3; j++){
			three_one_skew_D[0][i][j] = 0.0;
			for(k = 0; k < 3; k++){
				three_one_skew_D[0][i][j] += A[k][i] * C[k][j];
			}
		}
	}

    // x failure
    A[0][0] = 0.0; A[0][1] = 0.0; A[0][2] = 0.0; A[0][3] = cos_skew_alpha * cos_skew_beta;
    A[1][0] = 0.0; A[1][1] = 1.0; A[1][2] = 0.0; A[1][3] = sin_skew_alpha * cos_skew_beta;
    A[2][0] = 0.0; A[2][1] = 0.0; A[2][2] = 1.0; A[2][3] = sin_skew_beta;
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            B[i][j] = 0.0;
            for(k = 0; k < 4; k++){
                B[i][j] += A[i][k] * A[j][k];
            }
        }
    }
    MatrixInverse(B, C);

	for(i = 0; i < 4; i++){
		for(j = 0; j < 3; j++){
			three_one_skew_D[1][i][j] = 0.0;
			for(k = 0; k < 3; k++){
				three_one_skew_D[1][i][j] += A[k][i] * C[k][j];
			}
		}
	}

    // y failure
    A[0][0] = 1.0; A[0][1] = 0.0; A[0][2] = 0.0; A[0][3] = cos_skew_alpha * cos_skew_beta;
    A[1][0] = 0.0; A[1][1] = 0.0; A[1][2] = 0.0; A[1][3] = sin_skew_alpha * cos_skew_beta;
    A[2][0] = 0.0; A[2][1] = 0.0; A[2][2] = 1.0; A[2][3] = sin_skew_beta;
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            B[i][j] = 0.0;
            for(k = 0; k < 4; k++){
                B[i][j] += A[i][k] * A[j][k];
            }
        }
    }
    MatrixInverse(B, C);

	for(i = 0; i < 4; i++){
		for(j = 0; j < 3; j++){
			three_one_skew_D[2][i][j] = 0.0;
			for(k = 0; k < 3; k++){
				three_one_skew_D[2][i][j] += A[k][i] * C[k][j];
			}
		}
	}
 
    // z failure
    A[0][0] = 1.0; A[0][1] = 0.0; A[0][2] = 0.0; A[0][3] = cos_skew_alpha * cos_skew_beta;
    A[1][0] = 0.0; A[1][1] = 1.0; A[1][2] = 0.0; A[1][3] = sin_skew_alpha * cos_skew_beta;
    A[2][0] = 0.0; A[2][1] = 0.0; A[2][2] = 0.0; A[2][3] = sin_skew_beta;
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            B[i][j] = 0.0;
            for(k = 0; k < 4; k++){
                B[i][j] += A[i][k] * A[j][k];
            }
        }
    }
    MatrixInverse(B, C);

	for(i = 0; i < 4; i++){
		for(j = 0; j < 3; j++){
			three_one_skew_D[3][i][j] = 0.0;
			for(k = 0; k < 3; k++){
				three_one_skew_D[3][i][j] += A[k][i] * C[k][j];
			}
		}
	}

    // skew failure
    A[0][0] = 1.0; A[0][1] = 0.0; A[0][2] = 0.0; A[0][3] = 0.0;
    A[1][0] = 0.0; A[1][1] = 1.0; A[1][2] = 0.0; A[1][3] = 0.0;
    A[2][0] = 0.0; A[2][1] = 0.0; A[2][2] = 1.0; A[2][3] = 0.0;
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            B[i][j] = 0.0;
            for(k = 0; k < 4; k++){
                B[i][j] += A[i][k] * A[j][k];
            }
        }
    }
    MatrixInverse(B, C);

	for(i = 0; i < 4; i++){
		for(j = 0; j < 3; j++){
			three_one_skew_D[4][i][j] = 0.0;
			for(k = 0; k < 3; k++){
				three_one_skew_D[4][i][j] += A[k][i] * C[k][j];
			}
		}
	}    
}


#endif