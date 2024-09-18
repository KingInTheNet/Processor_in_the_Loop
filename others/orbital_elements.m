function ele = orbital_elements(OE)
%#codegen
DEGtoPI=1/180.0*pi;
ele=zeros(1,7);

ele(1,1)=OE(1,1);         % Julian Day
ele(1,2)=OE(1,2);         % semimajor axis [km]
ele(1,3)=OE(1,3);         % eccentricity
ele(1,4)=OE(1,4)*DEGtoPI; % inclination [rad] 
ele(1,5)=OE(1,5)*DEGtoPI; % right ascension of the ascending node [rad] 
ele(1,6)=OE(1,6)*DEGtoPI; % argument of perigee [rad] 
ele(1,7)=OE(1,7)*DEGtoPI; % mean anomaly at epoch [rad]
