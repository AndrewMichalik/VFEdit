del object\*.obj
nmake g21= deb=
cd \betdev\tbxdev\pcmcvt\libdev
del g21*.lib
nmake g21= deb= mle=
copy g21*.lib ..\cvtlib
cd ..
nmake g21= deb= mle=
cd \usrsub\g721
call tst bw.721
fc tst001.wav tst001.sav/b
