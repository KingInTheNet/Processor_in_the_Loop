function y=elements(fp,satname)
%#codegen

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                         %
%   This file read orbital elements from two line elements (TLE) file     %
%                                               2011/04/25 Kiku  (N/A)    %
%                                                                         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%   The orbital elements format:
%      a [km]   : semi-major axis
%      e     : eccentricity
%      i [deg] : inclination
%      W [deg] : longitude of the ascending node
%      w [deg] : argument of perigee
%      M [deg] : mean anomaly at EPOCH
%      P [s]    : Revolution Number at Epoch
% 

mu=2975536351779840.0;   %GE, in km^3/day^2. ----- */
% Pes=24*3600; % revolutions per solar day


% scan file until satname found
while ~feof(fp)
    line=fgetl(fp);
    found = strcmp(line,satname);
    if found
        break
    end   
end
if ~found
    error('Cannot find that sat')
end

% read two lines
line1=fgetl(fp); 
line2=fgetl(fp); 
fclose(fp);

% Information from LINE1
satid = line1(3:7);
launchYear = str2double(line1(10:11));
launchNumber     = str2double(line1(12:14));
launchpiece      = str2double(line1(15:17));
year=line1(19:20);
epochDayOfYear=str2double(line1(21:32));
if str2double(year(1))>4
      syear=['19' year];
else
      syear=['20' year];
end

epochYear=str2double(syear);
ep=datevec(datenum(epochYear,0,epochDayOfYear));
JD = jday(ep(1),ep(2),ep(3),ep(4),ep(5),ep(6));

OE=zeros(1,6);
% Information from LINE2
rpd=str2double(line2(53:63));           % rounds per day

OE(1)=(mu*(1/rpd/2/pi)^2)^(1/3);            % semimajor axis
OE(2)=str2double(['.' line2(27:33)]);   % eccentricity
OE(3)=str2double(line2(9:16));          % [deg] inclination
OE(4)=str2double(line2(18:25));         % [deg] longitude (or right ascension) of the ascending node 
OE(5)=str2double(line2(35:42));         % [deg] argument of periapsis (or perigee)
OE(6)=str2double(line2(44:51));         % [deg] mean anomaly at epoch

y=[JD,OE];

