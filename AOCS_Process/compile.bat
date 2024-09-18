com@set PATH=C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE;C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\BIN;C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\Tools;C:\Windows\Microsoft.NET\Framework\v3.5;C:\Windows\Microsoft.NET\Framework\v2.0.50727;C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\VCPackages;%PATH%
@set INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE;%INCLUDE%
@set LIB=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\LIB;%LIB%
@set LIBPATH=C:\Windows\Microsoft.NET\Framework\v3.5;C:\Windows\Microsoft.NET\Framework\v2.0.50727;C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\LIB;%LIBPATH%

@set PATH=C:\Program Files\Microsoft SDKs\Windows\v7.1\Bin;%PATH%
@set INCLUDE=C:\Program Files\Microsoft SDKs\Windows\v7.1\Include;%INCLUDE%
@set LIB=C:\Program Files\Microsoft SDKs\Windows\v7.1\Lib;%LIB%

cl /EHsc controlBPDU.c
cl /EHsc controlCMD.c

pause