fd *.*/s                            /d01-15-99  /t12:00

REM                                             
REM  ***** Reset 3rd party distribution file dates *****
REM 
fd dsk001\SETUP.EXE                 /d07-11-94  /t15:35

fd dsk001\tifdll\DLGTIF.DLL         /d06-30-95  /t12:00
fd dsk001\tifdll\DLGCTL.EXE         /d06-30-95  /t12:00
    
fd src002\mvb300\MSAJT112.DLL       /d03-24-94  /t00:00
fd src002\mvb300\MSAJT200.DLL       /d11-20-94  /t00:00
fd src002\mvb300\VBDB300.DLL        /d03-24-94  /t00:00
fd src002\mvb300\VBRUN300.DLL       /d05-12-93  /t00:00

fd src002\vbx300\DWSPYDLL.DLL       /d08-18-96  /t13:16
fd src002\vbx300\MHRUN400.DLL       /d05-04-95  /t09:52
fd src002\vbx300\CHART2FX.VBX       /d02-03-95  /t00:00
fd src002\vbx300\MHGMUL.VBX         /d03-30-95  /t09:43
fd src002\vbx300\MHSL200.VBX        /d03-30-95  /t09:44
fd src002\vbx300\MHTIP.VBX          /d04-28-95  /t11:30
fd src002\vbx300\MSOUTLIN.VBX       /d04-28-93  /t00:00
fd src002\vbx300\SBC.VBX            /d07-24-96  /t01:30
fd src002\vbx300\SPIN.VBX           /d09-30-93  /t12:27
fd src002\vbx300\THREED.VBX         /d07-16-93  /t00:00
                                    
fd src003\brdsup\dlg\d40drv.exe     /d04-25-94  /t13:01
fd src003\brdsup\dlg\d40chk.exe     /d09-27-93  /t15:59
                                    
fd src003\brdsup\nwv\nv800drv.com   /d10-05-92  /t14:12
fd src003\brdsup\nwv\nvtest.exe     /d01-14-94  /t15:55
                                    
:Exit                               
