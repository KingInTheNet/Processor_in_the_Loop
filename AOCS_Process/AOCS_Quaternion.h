// クオ?[タニオンの計算

#ifndef _AOCS_QUATERNION_H_
#define _AOCS_QUATERNION_H_

#include <math.h>

void Quat2DCM(double *q, double DCM[][3]){
    
    DCM[0][0] = q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
    DCM[0][1] = 2.0 * (q[1] * q[2] + q[0] * q[3]);
    DCM[0][2] = 2.0 * (q[1] * q[3] - q[0] * q[2]);
    
    DCM[1][0] = 2.0 * (q[1] * q[2] - q[0] * q[3]);
    DCM[1][1] = q[0] * q[0] - q[1] * q[1] + q[2] * q[2] - q[3] * q[3];
    DCM[1][2] = 2.0 * (q[2] * q[3] + q[0] * q[1]);
    
    DCM[2][0] = 2.0 * (q[1] * q[3] + q[0] * q[2]);
    DCM[2][1] = 2.0 * (q[2] * q[3] - q[0] * q[1]);
    DCM[2][2] = q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]; 
}

void DCM2Quat(double DCM[][3], double *q){

    q[0] = sqrt(DCM[0][0] + DCM[1][1] + DCM[2][2] + 1.0) * 0.5;
    
    if(q[0] < 1.0e-8){
        q[0] = 0.0;
        q[1] = sqrt((DCM[0][0] + 1.0) * 2.0);
        q[2] = sqrt((DCM[1][1] + 1.0) * 2.0);
        q[3] = sqrt((DCM[2][2] + 1.0) * 2.0);
    }else{
        q[1] = (DCM[1][2] - DCM[2][1]) / (4.0 * q[0]);
        q[2] = (DCM[2][0] - DCM[0][2]) / (4.0 * q[0]);
        q[3] = (DCM[0][1] - DCM[1][0]) / (4.0 * q[0]);
    }
}

void QuatMul(double *a, double *b, double *c){
    
    c[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
    c[1] = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
    c[2] = a[0] * b[2] + a[2] * b[0] + a[3] * b[1] - a[1] * b[3];
    c[3] = a[0] * b[3] + a[3] * b[0] + a[1] * b[2] - a[2] * b[1];
}

void Angle2Quat(double Z, double Y, double X, double *q){

    double qX[4], qY[4], qZ[4];
    double q_temp[4];
    
    qX[0] = cos(X / 2.0);
    qX[1] = sin(X / 2.0);
    qX[2] = 0.0;
    qX[3] = 0.0;
    
    qY[0] = cos(Y / 2.0);
    qY[1] = 0.0;
    qY[2] = sin(Y / 2.0);
    qY[3] = 0.0;
    
    qZ[0] = cos(Z / 2.0);
    qZ[1] = 0.0;
    qZ[2] = 0.0;
    qZ[3] = sin(Z / 2.0);
    
    QuatMul(qZ, qY, q_temp);
    QuatMul(q_temp, qX, q);
}

void Angle2Quat_1axis(unsigned char i, double theta, double *q){
    theta = theta / 2.0;
    
    if(i == 0){
        q[0] = cos(theta);
        q[1] = sin(theta);
        q[2] = 0.0;
        q[3] = 0.0;
    }
    if(i == 1){
        q[0] = cos(theta);
        q[1] = 0.0;
        q[2] = sin(theta);
        q[3] = 0.0;
    }
    if(i == 2){
        q[0] = cos(theta);
        q[1] = 0.0;
        q[2] = 0.0;
        q[3] = sin(theta);
    }
}

void NormalizeQuat(double *a){

    double norm;
    norm = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3]);
    
    a[0] = a[0] / norm;
    a[1] = a[1] / norm;
    a[2] = a[2] / norm;
    a[3] = a[3] / norm; 
}

// スカラ?[?ｬ分を?ｳにする
void Quat0Positive(double *a){
    if(a[0] < 0.0){
        a[0] *= -1.0;
        a[1] *= -1.0;
        a[2] *= -1.0;
        a[3] *= -1.0;
    }  
}

// 規格化されていること
void QuatInverse(double *a, double *b){
    b[0] = a[0];
    b[1] = -a[1];
    b[2] = -a[2];
    b[3] = -a[3];   
}

void QuatVector(double *q, double *r, double *rd){
    
    double qd[4], qr[4], qrd[4], qtemp1[4];
    QuatInverse(q, qd);
    
    qr[0] = 0.0;
    qr[1] = r[0];
    qr[2] = r[1];
    qr[3] = r[2];
    
    QuatMul(q, qr, qtemp1);
    QuatMul(qtemp1, qd, qrd);
    
    rd[0] = qrd[1];
    rd[1] = qrd[2];
    rd[2] = qrd[3];
}

#endif