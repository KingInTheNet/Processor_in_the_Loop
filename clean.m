clc
clear all;

delete *.mexw32;
delete *.mexw64;

cd AOCS_Process
delete *.mexw32 *.mexw64
cd ..

cd component_communication
delete *.mexw32 *.mexw64
cd ..

cd library\sfunc_nrlmsise00
delete *.mexw32 *.mexw64
cd ..\..

rmdir('slprj', 's')