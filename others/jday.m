%********************************  JD  ************************************
%   calender ->JD
% INPUT>>
%        (year): Year.
%       (month): Month.
%         (day): Day
%        (hour): Hour.
%         (min): Minute.
%         (sec): Second.
% OUTPUT>>
%         Julian Day number
% 
%    REFERENCES: Jean Meeus, "Astronomical Algorithms", p. 61.
% 
%**************************************************************************

function jd = jday(yr, mon, day, hr, min, sec)
day = day + hr / 24.0 + min / 1440.0 + sec / 86400.0;
  if  (mon < 3 )
    yr = yr - 1;
    mon = mon + 12;
  end
  
jd = floor(365.25*yr) + floor(30.6001*(mon+1)) - 15 + 1720996.5 + day; 
