ECHO OFF
del    err.txt
del ???xlt.lib
REM
REM  Go to each directory and perform build
REM
call mak001 DlgXlt        
call mak001 G11Xlt        
call mak001 G21Xlt        
call mak001 HarXlt        
call mak001 MSWXlt        
call mak001 NwVXlt        
call mak001 PTCXlt        
call mak001 RtxXlt        
ECHO ON
