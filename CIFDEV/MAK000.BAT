del 	*.obj
del   	vfecif.dll
bfr   	"DEBUG = 1" "DEBUG = 0" vfecif.mak -b
nmake 	vfecif.mak >>err.txt
bfr   	"DEBUG = 0" "DEBUG = 1" vfecif.mak -b
