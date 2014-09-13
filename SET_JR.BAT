REM 
REM Use more secure re-compile for working demo; Set REGKEYSTR to "00000000"
REM REM Set working demo 
REM bfr "9u239u23" "00000000"           VFEdit.Exe  VFE_D.Exe
REM 
REM Set evaluation until 09/01/97 (Date: 10105 x 1 || p7c0) 
REM bfr "9u239u23" "ps70p7c0"           VFEdit.Exe  VFE_E.Exe   -d
REM Set evaluation until 03/01/98 (Date: 10286 x 1 || p7c0) 
REM bfr "9u239u23" "qx70p7c0"           VFEdit.Exe  VFE_E.Exe   -d
REM Set evaluation until 04/01/98 (Date: 10317 x 1 || p7c0) 
REM bfr "9u239u23" "ly70p7c0"           VFEdit.Exe  VFE_E.Exe   -d
REM Set evaluation until 08/01/98 (Date: 10439 x 1 || p7c0) 
bfr "9u239u23" "z180p7c0"           VFEdit.Exe  VFE_E.Exe   -d
REM Set Junior 
bfr "VFEditJr" "00000001"           VFEdit.Exe  VFE_J.Exe   -d
REM Set working demo junior 
bfr "VFEditJr" "00000001"           VFE_D.Exe   VFE_DJ.Exe  -d
