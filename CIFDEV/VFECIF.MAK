# Microsoft Visual C++ generated build script - Do not modify

PROJ = VFECIF
DEBUG = 1
PROGTYPE = 1
CALLER = ..\vfedit.exe
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = E:\BETDEV\VFEDEV\CIFDEV\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = WINMEM.C    
FIRSTCPP = VFECIF.CPP  
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /YX /Od /D "_DEBUG" /D "_USRDLL" /GD /Fd"VFECIF.PDB"                 /Fp"VFECIF.PCH"
CFLAGS_R_WDLL = /nologo /W3 /ALw /YX /O2 /D "NDEBUG" /D "_USRDLL" /GD /Fp"VFECIF.PCH"
LFLAGS_D_WDLL = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /CO /NOE /ALIGN:16 /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = lafxdwd tmidev\dlgtmi oldnames libw ldllcew mcidev\wavmci ampdev\dlgamp fiodev\dlgfio effdev\dlgeff pcmdev\dlgpcm commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = lafxdw tmidev\dlgtmi oldnames libw ldllcew mcidev\wavmci ampdev\dlgamp fiodev\dlgfio effdev\dlgeff pcmdev\dlgpcm commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo /k /t 
RUNFLAGS = 
DEFFILE = VFECIF.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = VFECIF.SBR \
		AMPCHD.SBR \
		AMPDSP.SBR \
		AUDFIL.SBR \
		WINMEM.SBR \
		AUDDEV.SBR \
		WINMSG.SBR \
		TMPFIL.SBR \
		AUDEFF.SBR \
		UNDLST.SBR \
		SESFIL.SBR \
		SESEDT.SBR \
		SESEFF.SBR \
		EFFFRQ.SBR \
		EFFEQU.SBR


VFECIF_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\vfecif.h \
	e:\betdev\vfedev\cifdev\regdev\vfereg.h \
	e:\betdev\vfedev\cifdev\os_dev\winmsg.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\ampdev\genamp.h \
	e:\betdev\vfedev\cifdev\effdev\geneff.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\mcidev\genmci.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\tmidev\gentmi.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\tmpfil.h \
	e:\betdev\vfedev\cifdev\regdev\vfereg.c \
	e:\betdev\vfedev\cifdev\regdev\kescb.c


VFECIF_RCDEP = e:\betdev\vfedev\cifdev\regdev\\vfereg.h \
	e:\betdev\vfedev\cifdev\res\vislgo.ico \
	e:\betdev\vfedev\cifdev\res\arrptr.cur \
	e:\betdev\vfedev\cifdev\res\selmrk.cur


AMPCHD_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\ampdsp.h \
	e:\betdev\vfedev\cifdev\ampdev\genamp.h \
	e:\betdev\vfedev\cifdev\ampchd.h


AMPDSP_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\ampchd.h \
	e:\betdev\vfedev\cifdev\ampdsp.h \
	e:\betdev\vfedev\cifdev\ampdev\genamp.h


AUDFIL_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\tmpfil.h \
	e:\betdev\vfedev\cifdev\audeff.h \
	e:\betdev\vfedev\cifdev\effdev\geneff.h \
	e:\betdev\vfedev\cifdev\efffrq.h \
	e:\betdev\vfedev\cifdev\effequ.h \
	e:\betdev\vfedev\cifdev\ampdsp.h \
	e:\betdev\vfedev\cifdev\ampdev\genamp.h \
	e:\betdev\vfedev\cifdev\fiodev\filutl.h \
	e:\betdev\vfedev\cifdev\os_dev\winmsg.h


WINMEM_DEP = e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\os_dev\winmsg.h


AUDDEV_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\tmpfil.h \
	e:\betdev\vfedev\cifdev\audeff.h \
	e:\betdev\vfedev\cifdev\effdev\geneff.h \
	e:\betdev\vfedev\cifdev\efffrq.h \
	e:\betdev\vfedev\cifdev\effequ.h \
	e:\betdev\vfedev\cifdev\auddev.h \
	e:\betdev\vfedev\cifdev\mcidev\genmci.h \
	e:\betdev\vfedev\cifdev\tmidev\gentmi.h \
	e:\betdev\vfedev\cifdev\ampdsp.h \
	e:\betdev\vfedev\cifdev\ampdev\genamp.h


WINMSG_DEP = e:\betdev\vfedev\cifdev\os_dev\winmsg.h


TMPFIL_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\tmpfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\os_dev\winmsg.h


AUDEFF_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\audeff.h \
	e:\betdev\vfedev\cifdev\effdev\geneff.h \
	e:\betdev\vfedev\cifdev\efffrq.h \
	e:\betdev\vfedev\cifdev\effequ.h


UNDLST_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\tmpfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\undlst.h \
	e:\betdev\vfedev\cifdev\os_dev\winmsg.h


SESFIL_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\sesfil.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\tmpfil.h \
	e:\betdev\vfedev\cifdev\anotxt.h \
	e:\betdev\vfedev\cifdev\undlst.h \
	e:\betdev\vfedev\cifdev\audeff.h \
	e:\betdev\vfedev\cifdev\effdev\geneff.h \
	e:\betdev\vfedev\cifdev\efffrq.h \
	e:\betdev\vfedev\cifdev\effequ.h \
	e:\betdev\vfedev\cifdev\os_dev\winmsg.h


SESEDT_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\sesedt.h \
	e:\betdev\vfedev\cifdev\sesfil.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\tmpfil.h \
	e:\betdev\vfedev\cifdev\anotxt.h \
	e:\betdev\vfedev\cifdev\undlst.h \
	e:\betdev\vfedev\cifdev\audeff.h \
	e:\betdev\vfedev\cifdev\effdev\geneff.h \
	e:\betdev\vfedev\cifdev\efffrq.h \
	e:\betdev\vfedev\cifdev\effequ.h \
	e:\betdev\vfedev\cifdev\ampdsp.h \
	e:\betdev\vfedev\cifdev\ampdev\genamp.h \
	e:\betdev\vfedev\cifdev\os_dev\winmsg.h \
	e:\betdev\vfedev\cifdev\regdev\vfereg.h


SESEFF_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\sesedt.h \
	e:\betdev\vfedev\cifdev\sesfil.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\tmpfil.h \
	e:\betdev\vfedev\cifdev\anotxt.h \
	e:\betdev\vfedev\cifdev\undlst.h \
	e:\betdev\vfedev\cifdev\audeff.h \
	e:\betdev\vfedev\cifdev\effdev\geneff.h \
	e:\betdev\vfedev\cifdev\efffrq.h \
	e:\betdev\vfedev\cifdev\effequ.h


EFFFRQ_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\audeff.h \
	e:\betdev\vfedev\cifdev\effdev\geneff.h \
	e:\betdev\vfedev\cifdev\efffrq.h \
	e:\betdev\vfedev\cifdev\effequ.h


EFFEQU_DEP = e:\betdev\vfedev\cifdev\gencif.h \
	e:\betdev\vfedev\cifdev\stdafx.h \
	e:\betdev\vfedev\cifdev\audfil.h \
	e:\betdev\vfedev\cifdev\os_dev\winmem.h \
	e:\betdev\vfedev\cifdev\fiodev\genfio.h \
	e:\betdev\vfedev\cifdev\pcmdev\genpcm.h \
	e:\betdev\vfedev\cifdev\audeff.h \
	e:\betdev\vfedev\cifdev\effdev\geneff.h \
	e:\betdev\vfedev\cifdev\efffrq.h \
	e:\betdev\vfedev\cifdev\effequ.h


all:	$(PROJ).DLL

VFECIF.OBJ:	VFECIF.CPP $(VFECIF_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c VFECIF.CPP

VFECIF.RES:	VFECIF.RC $(VFECIF_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r VFECIF.RC

AMPCHD.OBJ:	AMPCHD.CPP $(AMPCHD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AMPCHD.CPP

AMPDSP.OBJ:	AMPDSP.CPP $(AMPDSP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AMPDSP.CPP

AUDFIL.OBJ:	AUDFIL.CPP $(AUDFIL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AUDFIL.CPP

WINMEM.OBJ:	OS_DEV\WINMEM.C $(WINMEM_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c OS_DEV\WINMEM.C

AUDDEV.OBJ:	AUDDEV.CPP $(AUDDEV_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AUDDEV.CPP

WINMSG.OBJ:	OS_DEV\WINMSG.C $(WINMSG_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c OS_DEV\WINMSG.C

TMPFIL.OBJ:	TMPFIL.CPP $(TMPFIL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TMPFIL.CPP

AUDEFF.OBJ:	AUDEFF.CPP $(AUDEFF_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AUDEFF.CPP

UNDLST.OBJ:	UNDLST.CPP $(UNDLST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c UNDLST.CPP

SESFIL.OBJ:	SESFIL.CPP $(SESFIL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SESFIL.CPP

SESEDT.OBJ:	SESEDT.CPP $(SESEDT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SESEDT.CPP

SESEFF.OBJ:	SESEFF.CPP $(SESEFF_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SESEFF.CPP

EFFFRQ.OBJ:	EFFFRQ.CPP $(EFFFRQ_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EFFFRQ.CPP

EFFEQU.OBJ:	EFFEQU.CPP $(EFFEQU_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EFFEQU.CPP


$(PROJ).DLL::	VFECIF.RES

$(PROJ).DLL::	VFECIF.OBJ AMPCHD.OBJ AMPDSP.OBJ AUDFIL.OBJ WINMEM.OBJ AUDDEV.OBJ WINMSG.OBJ \
	TMPFIL.OBJ AUDEFF.OBJ UNDLST.OBJ SESFIL.OBJ SESEDT.OBJ SESEFF.OBJ EFFFRQ.OBJ EFFEQU.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
VFECIF.OBJ +
AMPCHD.OBJ +
AMPDSP.OBJ +
AUDFIL.OBJ +
WINMEM.OBJ +
AUDDEV.OBJ +
WINMSG.OBJ +
TMPFIL.OBJ +
AUDEFF.OBJ +
UNDLST.OBJ +
SESFIL.OBJ +
SESEDT.OBJ +
SESEFF.OBJ +
EFFFRQ.OBJ +
EFFEQU.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
E:\C151\CDK16\LIB\+
e:\c151\lib\+
e:\c151\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) VFECIF.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	VFECIF.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) VFECIF.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
