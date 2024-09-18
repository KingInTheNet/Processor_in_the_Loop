tlef='uniform.txt'; % tle file name
satname ='uniform';
fp=fopen(tlef,'r');
if(fp == -1)
    error('Cannot open file');
end

ele=orbital_elements(elements(fp,satname));

jd=ele(1,1);
ele=ele(1,2:7);