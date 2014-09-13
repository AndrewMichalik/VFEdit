# Microsoft Visual C++ generated build script - Do not modify

PROJ = VFEINS
DEBUG = 0
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = E:\BETDEV\VFEDEV\INSDEV\RESDEV\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = VFEINS.CPP  
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /GD /Fd"TBXRES.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /GD 
LFLAGS_D_WDLL = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /CO /NOE /ALIGN:16 /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /NOE /ALIGN:16 /MAP:FULL
LIBS_D_WDLL = lafxdwd oldnames libw commdlg shell olecli olesvr ldllcew
LIBS_R_WDLL = lafxdw oldnames libw commdlg shell olecli olesvr ldllcew
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = VFEINS.DEF
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
SBRS = VFEINS.SBR


VFEINS_DEP = e:\betdev\vfedev\insdev\resdev\stdafx.h \
	e:\betdev\vfedev\insdev\resdev\vfeins.h


VFEINS_RCDEP = ..\\suprul\\dialogs.h \
	e:\betdev\vfedev\res\vfedit.ico


all:	$(PROJ).DLL

VFEINS.OBJ:	VFEINS.CPP $(VFEINS_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c VFEINS.CPP

VFEINS.RES:	VFEINS.RC $(VFEINS_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r VFEINS.RC


$(PROJ).DLL::	VFEINS.RES

$(PROJ).DLL::	VFEINS.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
VFEINS.OBJ +
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
	$(RC) $(RESFLAGS) VFEINS.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	VFEINS.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) VFEINS.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
