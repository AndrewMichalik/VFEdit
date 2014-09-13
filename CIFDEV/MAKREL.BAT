ECHO OFF
del err.txt
REM
REM  Update PCM libraries
REM
cd   PCMDev
call makrel
cd   ..
REM  ********************************************
REM  ** Go to each directory and perform build **
REM  ********************************************
call mak001 AmpDev dlg         
call mak001 FIODev dlg         
call mak001 MCIDev dlg         
call mak001 PCMDev dlg         
call mak001 PCMDev g21         
call mak001 PCMDev har         
call mak001 PCMDev nwv         
call mak001 PCMDev ptc         
call mak001 PCMDev rtx         
call mak001 EffDev dlg         
call mak001 EffDev g21         
call mak001 EffDev har         
call mak001 EffDev nwv         
call mak001 EffDev ptc         
call mak001 EffDev rtx         
call mak001 TMIDev dlg         
call mak001 TMIDev nwv         
call mak001 TMIDev rtx         
REM  ********************************************
REM  ** Build for each manufacturer			   **
REM  ** Note: Force first manufacturer		   **
REM  ********************************************
call SetMfg dlg nwv
call SetMfg rtx nwv
call mak000
copy vfecif.dll nwvcif.dll
call SetMfg nwv rtx 
call mak000
copy vfecif.dll rtxcif.dll
call SetMfg rtx dlg 
call mak000
copy vfecif.dll dlgcif.dll
ECHO ON
