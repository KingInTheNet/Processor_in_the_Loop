noise_sampling_rate = 0.01; % sec

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% GAS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

GAS_k = 2.5e-5; % V/nT
GAS_tau = 0.016; % sec

GAS_Vref = 2.5; % V

GAS_Vnoise = 0.01 / 3.0; % V (noise level < 0.01 V)
%GAS_Vnoise = 2.5e-4 / 3; % V (noise level = 10nT PP)
GAS_Vnoise = 0.1/3.0; % V
GAS_seed1 = [1 2 3];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% GYRO
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

GYRO_nv = 2.0/3600.0;%0.1;%1.73/3600.0; % deg/sec (provisional)
GYRO_nu = 0.01/3600.0;%1.73/3600.0; % deg/sec^2 (provisional)
GYRO_bx = 1.0 / 3600.0; % deg/sec
GYRO_by = -2.0 / 3600.0; % deg/sec
GYRO_bz = 3.0 / 3600.0; % deg/sec
GYRO_bx = -0.001; % deg/sec
GYRO_by = 0.002; % deg/sec
GYRO_bz = -0.003; % deg/sec

GYRO_omega = 2.0 * pi * 40.0; % 1/sec
GYRO_zeta = 0.3; % no dimension

GYRO_sampling_time = 0.05; % sec

GYRO_seed1 = [1 2 3];
GYRO_seed2 = [4 5 6];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MTQ
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

MTQ_tau = 0.04; % sec
%MTQ_tau = 0.0; % sec
MTQ_k = 1.0; % Am^2/V
MTQ_out=5.0/5.0*5.0; 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% NSAS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

NSAS_x_noise = 1.0 / 180.0 * pi; % rad
NSAS_y_noise = 1.0 / 180.0 * pi; % rad
%NSAS_ang_limit = 0.872664626; % 50.0 / 180.0 * pi; % rad
NSAS_ang_limit = 55.0 / 180.0 * pi; % rad

NSAS_seed1 = 1;
NSAS_seed2 = 2;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% RW
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

RW_RM=6; % wire wound resistor ƒ¶
RW_LM=0;%1e-3; % wire wound inductance H
RW_kT=0.03; % torque coefficient Nm/A
RW_kE=0.03; % back electromotive force coefficient V/rad
RW_J=7.34e-4; % moment of inertia kgm^2
RW_Rsc=0.1; % ƒ¶
RW_TL=0.003; % loss torque Nm
RW_loss=0.003/5000*60/2/pi;
RW_limA=3.0;
RW_tau = RW_J * RW_RM / RW_kT / RW_kE;

RW_Gamp=60.0;
RW_kL=1.0; % phase compensation
RW_T1=0.0; %10.0/2.0/pi;
RW_T2=1.0/16.0/1000.0/2.0/pi;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% STT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

STT_rand = 20.0; % arcsec (3sigma)
STT_bias = 40.0; % arcsec (upper limit)
STT_x_att_noise = 3.0 * 60.0; % arcsec (3sigma)
STT_y_att_noise = 10.0; % arcsec (3sigma)
STT_z_att_noise = 10.0; % arcsec (3sigma)

STT_x_noise  = sqrt(STT_rand * STT_rand + STT_bias * STT_bias ...
    + STT_x_att_noise * STT_x_att_noise) / 3.0 / 3600.0 * pi / 180.0;
STT_y_noise  = sqrt(STT_rand * STT_rand + STT_bias * STT_bias ...
    + STT_y_att_noise * STT_y_att_noise) / 3.0 / 3600.0 * pi / 180.0;
STT_z_noise  = sqrt(STT_rand * STT_rand + STT_bias * STT_bias ...
    + STT_z_att_noise * STT_z_att_noise) / 3.0 / 3600.0 * pi / 180.0;

STT_AD_prob = 10.90; % Attitude Determination probability
STT_sun_ang_limit = 35 / 180 * pi;
%STT_earth_radius = 6378137.0; % (m)
%STT_satellite_alt = 628000.0; % (m)
%STT_earth_ang_limit = asin(STT_earth_radius ...
%    / (STT_earth_radius + STT_satellite_alt)) ...
%    + 4.0 / 180.0 * pi * sqrt(2);
STT_FOV = 4.0 / 180.0 * pi;
STT_moon_ang_limit = 1.0 / 180.0 * pi + STT_FOV * sqrt(2);

STT_dt = 1.0; % sec

STT_seed1 = [1 2 3];
STT_seed2 = [4 5 6];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% GPS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

GPS_position_noise = 3.24 / sqrt(3.0); % m
GPS_time_noise = 0.05 / 86400.0; % day

GPS_dt = 1.0; % sec

GPS_position_seed = [1 2 3];
GPS_time_seed = 4;