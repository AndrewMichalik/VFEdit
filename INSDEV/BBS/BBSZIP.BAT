echo Create "Working Demo": Use Demo executable disk 1 in a:
PAUSE
del   *.zip
pkzip VFE001.zip    -ex a:\*.*                  -rp
pkzip VFE002.zip    -ex ..\Dsk002\*.*           -rp
pkzip VFE003.zip    -ex ..\Dsk003\*.*           -rp
fd *.zip /t12:00/d01-15-99
pkzip DlgVFE3D.zip  -ex dlgvfe.txt      *.zip   -rp
echo Create "Junior Demo": Use Freeware Demo executable disk 1 in a:
PAUSE
pkzip VFEJD1.zip    -ex a:\*.*                  -rp
REM
fd *.zip /t12:00/d01-15-99

