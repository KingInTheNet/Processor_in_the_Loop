% component?ﾀ標系からbody?ﾀ標系(c2b)に変換するスクリプト
% Z?ｨY?ｨXの?№ﾉ回すこと
% 角度はdegreeで入力すること
deg2rad = pi / 180;

% GAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
GAS_c2b_Z =   0 * deg2rad;
GAS_c2b_Y =   0 * deg2rad;
GAS_c2b_X = -90 * deg2rad;

GAS_c2b_quat = angle2quat(GAS_c2b_Z, GAS_c2b_Y, GAS_c2b_X, 'ZYX');
GAS_c2b      = quat2dcm(GAS_c2b_quat);
GAS_b2c_quat = quatinv(GAS_c2b_quat);
GAS_b2c      = quat2dcm(GAS_b2c_quat);

clear GAS_c2b_Z
clear GAS_c2b_Y
clear GAS_c2b_X

% GYRO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
GYRO_c2b_Z = -90 * deg2rad;
GYRO_c2b_Y =   0 * deg2rad;
GYRO_c2b_X =  90 * deg2rad;

GYRO_c2b_quat = angle2quat(GYRO_c2b_Z, GYRO_c2b_Y, GYRO_c2b_X, 'ZYX');
GYRO_c2b      = quat2dcm(GYRO_c2b_quat);
GYRO_b2c_quat = quatinv(GYRO_c2b_quat);
GYRO_b2c      = quat2dcm(GYRO_b2c_quat);

clear GYRO_c2b_Z
clear GYRO_c2b_Y
clear GYRO_c2b_X

% NSAS1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% NSAS1 be located on +X surface
NSAS1_c2b_Z = 180 * deg2rad;
NSAS1_c2b_Y = -90 * deg2rad;
NSAS1_c2b_X =   0 * deg2rad;

NSAS1_c2b_quat = angle2quat(NSAS1_c2b_Z, NSAS1_c2b_Y, NSAS1_c2b_X, 'ZYX');
NSAS1_c2b      = quat2dcm(NSAS1_c2b_quat);
NSAS1_b2c_quat = quatinv(NSAS1_c2b_quat);
NSAS1_b2c      = quat2dcm(NSAS1_b2c_quat);

clear NSAS1_c2b_Z
clear NSAS1_c2b_Y
clear NSAS1_c2b_X

% NSAS2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\
% NSAS2 be located on -Z surface
NSAS2_c2b_Z = 180 * deg2rad;
NSAS2_c2b_Y = 180 * deg2rad;
NSAS2_c2b_X =   0 * deg2rad;

NSAS2_c2b_quat = angle2quat(NSAS2_c2b_Z, NSAS2_c2b_Y, NSAS2_c2b_X, 'ZYX');
NSAS2_c2b      = quat2dcm(NSAS2_c2b_quat);
NSAS2_b2c_quat = quatinv(NSAS2_c2b_quat);
NSAS2_b2c      = quat2dcm(NSAS2_b2c_quat);

clear NSAS2_c2b_Z
clear NSAS2_c2b_Y
clear NSAS2_c2b_X

% NSAS3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% NSAS3 be located on +Z surface
NSAS3_c2b_Z = 0 * deg2rad;
NSAS3_c2b_Y = 0 * deg2rad;
NSAS3_c2b_X = 0 * deg2rad;

NSAS3_c2b_quat = angle2quat(NSAS3_c2b_Z, NSAS3_c2b_Y, NSAS3_c2b_X, 'ZYX');
NSAS3_c2b      = quat2dcm(NSAS3_c2b_quat);
NSAS3_b2c_quat = quatinv(NSAS3_c2b_quat);
NSAS3_b2c      = quat2dcm(NSAS3_b2c_quat);

clear NSAS3_c2b_Z
clear NSAS3_c2b_Y
clear NSAS3_c2b_X

% NSAS4 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% NSAS4 be located on -X surface
NSAS4_c2b_Z = -180 * deg2rad;
NSAS4_c2b_Y =   90 * deg2rad;
NSAS4_c2b_X =    0 * deg2rad;

NSAS4_c2b_quat = angle2quat(NSAS4_c2b_Z, NSAS4_c2b_Y, NSAS4_c2b_X, 'ZYX');
NSAS4_c2b      = quat2dcm(NSAS4_c2b_quat);
NSAS4_b2c_quat = quatinv(NSAS4_c2b_quat);
NSAS4_b2c      = quat2dcm(NSAS4_b2c_quat);

clear NSAS4_c2b_Z
clear NSAS4_c2b_Y
clear NSAS4_c2b_X

% NSAS5 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% NSAS5 be located on -Y surface
NSAS5_c2b_Z =  -90 * deg2rad;
NSAS5_c2b_Y =    0 * deg2rad;
NSAS5_c2b_X =  -90 * deg2rad;

NSAS5_c2b_quat = angle2quat(NSAS5_c2b_Z, NSAS5_c2b_Y, NSAS5_c2b_X, 'ZYX');
NSAS5_c2b      = quat2dcm(NSAS5_c2b_quat);
NSAS5_b2c_quat = quatinv(NSAS5_c2b_quat);
NSAS5_b2c      = quat2dcm(NSAS5_b2c_quat);

clear NSAS5_c2b_Z
clear NSAS5_c2b_Y
clear NSAS5_c2b_X

% NSAS6 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% NSAS6 be located on +Y surface
NSAS6_c2b_Z =  90 * deg2rad;
NSAS6_c2b_Y =   0 * deg2rad;
NSAS6_c2b_X =  90 * deg2rad;

NSAS6_c2b_quat = angle2quat(NSAS6_c2b_Z, NSAS6_c2b_Y, NSAS6_c2b_X, 'ZYX');
NSAS6_c2b      = quat2dcm(NSAS6_c2b_quat);
NSAS6_b2c_quat = quatinv(NSAS6_c2b_quat);
NSAS6_b2c      = quat2dcm(NSAS6_b2c_quat);

clear NSAS6_c2b_Z
clear NSAS6_c2b_Y
clear NSAS6_c2b_X


% STT1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
STT1_c2b_Z = -90 * deg2rad;
STT1_c2b_Y =   0 * deg2rad;
STT1_c2b_X =  90 * deg2rad;

STT1_c2b_quat = angle2quat(STT1_c2b_Z, STT1_c2b_Y, STT1_c2b_X, 'ZYX');
STT1_c2b      = quat2dcm(STT1_c2b_quat);
STT1_b2c_quat = quatinv(STT1_c2b_quat);
STT1_b2c      = quat2dcm(STT1_b2c_quat);

clear STT1_c2b_Z
clear STT1_c2b_Y
clear STT1_c2b_X

% STT2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%STT2_c2b_Z = 90 * deg2rad;
%STT2_c2b_Y = 135 * deg2rad;
%STT2_c2b_X = 0 * deg2rad;

%STT2_c2b_quat = angle2quat(STT2_c2b_Z, STT2_c2b_Y, STT2_c2b_X, 'ZYX');
%STT2_c2b      = quat2dcm(STT2_c2b_quat);
%STT2_b2c_quat = quatinv(STT2_c2b_quat);
%STT2_b2c      = quat2dcm(STT2_b2c_quat);

%clear STT2_c2b_Z
%clear STT2_c2b_Y
%clear STT2_c2b_X

% MTQ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
MTQ_c2b = [1; -1; -1];
MTQ_b2c = MTQ_c2b;

% FOUR_SKEW_PARAM %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
four_skew_gamma = asin(1.0 / sqrt(3.0));
four_skew_cos = cos(four_skew_gamma);
four_skew_sin = sin(four_skew_gamma);
four_skew_Dc = sqrt(2.0) / 2.0 / four_skew_cos;
four_skew_Ds = 1.0 / 2.0 / four_skew_sin;

four_skew_D0 = [[four_skew_Dc/2.0 four_skew_Ds/2.0  four_skew_Dc/2.0]; ...
               [ four_skew_Dc/2.0 four_skew_Ds/2.0 -four_skew_Dc/2.0]; ...
               [-four_skew_Dc/2.0 four_skew_Ds/2.0 -four_skew_Dc/2.0]; ...
               [-four_skew_Dc/2.0 four_skew_Ds/2.0  four_skew_Dc/2.0]];

four_skew_D1 = [[0.0          0.0           0.0]; ...
               [ four_skew_Dc four_skew_Ds  0.0]; ...
               [-four_skew_Dc 0.0          -four_skew_Dc]; ...
               [ 0.0          four_skew_Ds  four_skew_Dc]];

four_skew_D2 = [[four_skew_Dc four_skew_Ds  0.0]; ...
               [ 0.0          0.0           0.0]; ...
               [ 0.0          four_skew_Ds -four_skew_Dc]; ...
               [-four_skew_Dc 0.0           four_skew_Dc]];

four_skew_D3 = [[four_skew_Dc 0.0           four_skew_Dc]; ...
               [ 0.0          four_skew_Ds -four_skew_Dc]; ...
               [ 0.0          0.0           0.0]; ...
               [-four_skew_Dc four_skew_Ds  0.0]];
           
four_skew_D4 = [[0.0          four_skew_Ds four_skew_Dc]; ...
               [ four_skew_Dc 0.0         -four_skew_Dc]; ...
               [-four_skew_Dc four_skew_Ds 0.0]; ...
               [ 0.0          0.0          0.0]];

% 3+1_SKEW_PARAM %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
skew_alpha = pi / 4;%[rad]
skew_beta  = asin(1.0 / sqrt(3.0));%[rad]

three_one_skew_matrix = [1 0 0 cos(skew_alpha) * cos(skew_beta); ...
                         0 1 0 sin(skew_alpha) * cos(skew_beta); ...
                         0 0 1 sin(skew_beta)];
                    
three_one_skew_D0 = three_one_skew_matrix' / (three_one_skew_matrix * three_one_skew_matrix');

three_one_skew_matrix1 = [0 0 0 cos(skew_alpha) * cos(skew_beta); ...
                          0 1 0 sin(skew_alpha) * cos(skew_beta); ...
                          0 0 1 sin(skew_beta)];
                    
three_one_skew_D1 = three_one_skew_matrix1' / (three_one_skew_matrix1 * three_one_skew_matrix1');

three_one_skew_matrix2 = [1 0 0 cos(skew_alpha) * cos(skew_beta); ...
                          0 0 0 sin(skew_alpha) * cos(skew_beta); ...
                          0 0 1 sin(skew_beta)];
                    
three_one_skew_D2 = three_one_skew_matrix2' / (three_one_skew_matrix2 * three_one_skew_matrix2');

three_one_skew_matrix3 = [1 0 0 cos(skew_alpha) * cos(skew_beta); ...
                          0 1 0 sin(skew_alpha) * cos(skew_beta); ...
                          0 0 0 sin(skew_beta)];
                    
three_one_skew_D3 = three_one_skew_matrix3' / (three_one_skew_matrix3 * three_one_skew_matrix3');

three_one_skew_matrix4 = [1 0 0 0; ...
                          0 1 0 0; ...
                          0 0 1 0];
                    
three_one_skew_D4 = three_one_skew_matrix4' / (three_one_skew_matrix4 * three_one_skew_matrix4');