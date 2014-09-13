IF "" == "%1" goto ErrEnd
REM                                             
REM  ***** Reset dates before copy *****
REM 
call setdat

REM 
REM  ***** Disk 1: Main program files *****
REM 
del                                             Dsk001\WinXxx\*.exe
del                                             Dsk001\WinXxx\*.dll
del                                             Dsk001\WinXxx\*.mdb
copy INSTALL.INS                                Dsk001/v
copy \Betdev\VFEDev\VFEDIT.EXE                  Dsk001\WinXxx/v

copy \Betdev\VFEDev\InsDev\ResDev\VFEIns.DLL    Dsk001\WinXxx/v
copy \Betdev\VFEDev\InsDev\ResDev\VFEIns.DLL    Dsk001\InsDir/v

copy \Betdev\VFEDev\CIFDev\%1CIF.DLL            Dsk001\WinXxx\vfecif.dll/v
copy \Betdev\VFEDev\exedev\%1PCM.DLL            Dsk001\WinXxx/v
copy \Betdev\VFEDev\exedev\%1TMI.DLL            Dsk001\WinXxx/v
copy \Betdev\VFEDev\exedev\%1EFF.DLL            Dsk001\WinXxx/v
copy \Betdev\VFEDev\exedev\DLGAMP.DLL           Dsk001\WinXxx/v
copy \Betdev\VFEDev\exedev\DLGFIO.DLL           Dsk001\WinXxx/v
copy \Betdev\VFEDev\exedev\WAVMCI.DLL           Dsk001\WinXxx/v
copy \Betdev\VFEDev\exedev\FILTYP.MDB           Dsk001\WinXxx/v
copy src001\%1\VFEdit.Ini                       Dsk001\WinXxx/v
                                                
copy \Betdev\VFEDev\exedev\DLGTIF.DLL           Dsk001\TIFDLL/v
copy \Betdev\VFEDev\exedev\DLGCTL.EXE           Dsk001\TIFDLL/v

REM  ***** Disk 3: Help and sample files *****
del                                             Dsk003\*.z
del                                             Dsk003\*.hlp
copy \Betdev\VFEDev\HlpDev\VFEDIT.HLP           Dsk003/v
Compress src003\sample\%1\*.*                   Dsk003\sample.z
Compress src003\brdsup\%1\*.*                   Dsk003\brdsup.z

REM  ***** Disk 2: These files rarely change *****
rem goto Exit

REM 
REM  ***** Note: check to insure that original date is maintained
REM 
del                                             Src002\MVB300\*.DLL
del                                             Src002\VBX300\*.VBX
copy \Betdev\VFEDev\exedev\MSAJT112.DLL         Src002\MVB300/v  
copy \Betdev\VFEDev\exedev\MSAJT200.DLL         Src002\MVB300/v  
copy \Betdev\VFEDev\exedev\TOOLHELP.DLL         Src002\MVB300/v
copy \Betdev\VFEDev\exedev\VBDB300.DLL          Src002\MVB300/v
copy \Betdev\VFEDev\exedev\VBRUN300.DLL         Src002\MVB300/v
copy \Betdev\VFEDev\exedev\VER.DLL              Src002\MVB300/v
                                                
copy \Betdev\VFEDev\exedev\DWSPYDLL.DLL         Src002\VBX300/v
copy \Betdev\VFEDev\exedev\MHRUN400.DLL         Src002\VBX300/v
                                                
copy \Betdev\VFEDev\exedev\CHART2FX.VBX         Src002\VBX300/v
copy \Betdev\VFEDev\exedev\MHGMUL.VBX           Src002\VBX300/v
copy \Betdev\VFEDev\exedev\MHSL200.VBX          Src002\VBX300/v
copy \Betdev\VFEDev\exedev\MHTIP.VBX            Src002\VBX300/v
copy \Betdev\VFEDev\exedev\MSOUTLIN.VBX         Src002\VBX300/v
copy \Betdev\VFEDev\exedev\SBC.VBX              Src002\VBX300/v
copy \Betdev\VFEDev\exedev\SPIN.VBX             Src002\VBX300/v
copy \Betdev\VFEDev\exedev\THREED.VBX           Src002\VBX300/v
                                                
REM                                             
REM  ***** Disk 2: Build compression sets *****
REM 
del                                             Dsk002\*.z
Compress src002\mvb300\*.*                      Dsk002\mvb300.z
Compress src002\vbx300\*.*                      Dsk002\vbx300.z
                                                
:Exit
REM                                             
REM  ***** Reset dates after compression *****
REM 
call setdat

:ErrEnd
