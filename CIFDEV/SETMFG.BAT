REM Setting %1 to %2 build type
IF "" == "%2" goto ErrEnd
bfr %1pcm %2pcm vfecif.mak -b
bfr %1tmi %2tmi vfecif.mak -b
bfr %1eff %2eff vfecif.mak -b
:ErrEnd
