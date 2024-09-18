%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% simulation condition
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% attitude

q_ini=[1/sqrt(2) 0 0 -1/sqrt(2) ];
w_ini=[1/180*pi -1/180*pi -1in/180*pi];%[rad/s]

% sim_dt

sim_dt = 0.01;%[sec]
AOBC_dt = 0.05;%[sec]
STT_dt = 1;%[sec]
GPS_dt = 1;%[sec]