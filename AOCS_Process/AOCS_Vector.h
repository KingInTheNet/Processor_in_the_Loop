// ベクトルの計算 Calculation of vector

#ifndef _AOCS_VECTOR_H_
#define _AOCS_VECTOR_H_

#define DIM 3

// ベクトルのノルムの計算 Calculation of the norm of the vector
double VectorNorm(double *a){
    double norm = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    return norm;
}

// ベクトルを規格化 The normalized vector
void NormalizeVector(double *a){
    double norm = VectorNorm(a);
    
    a[0] = a[0] / norm;
    a[1] = a[1] / norm;
    a[2] = a[2] / norm;
}

// ベクトルの内?ﾏ Inner product of vector
double VectorInnerProduct(double *a, double *b){
    double c = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    return c;
}

// ベクトルの外?ﾏ Cross product of the vector
void VectorOuterProduct(double *a, double *b, double *c){
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

#endif