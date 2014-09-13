REM 
REM	Set the low-level DLL version numbers
REM 
bfr "2,12,0,00" "3,00,0,00"	*.rc -b
bfr "2,12,0,00" "3,00,0,00"	ampdev\*.rc -b
bfr "2,12,0,00" "3,00,0,00"	effdev\*.rc -b
bfr "2,12,0,00" "3,00,0,00"	fiodev\*.rc -b
bfr "2,12,0,00" "3,00,0,00"	mcidev\*.rc -b
bfr "2,12,0,00" "3,00,0,00"	pcmdev\*.rc -b
bfr "2,12,0,00" "3,00,0,00"	tmidev\*.rc -b

bfr "2.12.000"  "3.00.000"	*.rc -b
bfr "2.12.000"  "3.00.000"	ampdev\*.rc -b
bfr "2.12.000"  "3.00.000"	effdev\*.rc -b
bfr "2.12.000"  "3.00.000"	fiodev\*.rc -b
bfr "2.12.000"  "3.00.000"	mcidev\*.rc -b
bfr "2.12.000"  "3.00.000"	pcmdev\*.rc -b
bfr "2.12.000"  "3.00.000"	tmidev\*.rc -b

bfr "0x0212"	"0x0300"	gen*.h -b 
bfr "0x0212"	"0x0300"	ampdev\gen*.h -b 
bfr "0x0212"	"0x0300" 	effdev\gen*.h -b
bfr "0x0212"	"0x0300" 	fiodev\gen*.h -b
bfr "0x0212"	"0x0300" 	mcidev\gen*.h -b
bfr "0x0212"	"0x0300" 	pcmdev\gen*.h -b
bfr "0x0212"	"0x0300" 	tmidev\gen*.h -b
