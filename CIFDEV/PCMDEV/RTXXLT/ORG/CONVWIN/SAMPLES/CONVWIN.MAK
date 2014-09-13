# Microsoft Visual C++ generated build script - Do not modify

PROJ = CONVWIN
DEBUG = 1
PROGTYPE = 3
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = E:\BETDEV\VFEDEV\CIFDEV\PCMDEV\RTXXLT\ORG\CONVWIN\SAMPLES\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = CONVERT.C   
FIRSTCPP =             
RC = rc
CFLAGS_D_WTTY = /nologo /G2 /Mq /W3 /Zi /AL /Od /D "_DEBUG" /FR /Fd"CONVWIN.PDB"
CFLAGS_R_WTTY = /nologo /Gs /G2 /Mq /W3 /AM /Ox /D "NDEBUG" /FR 
LFLAGS_D_WTTY = /NOLOGO /NOD /PACKC:57344 /ALIGN:16 /ONERROR:NOEXE /CO 
LFLAGS_R_WTTY = /NOLOGO /NOD /PACKC:57344 /ALIGN:16 /ONERROR:NOEXE 
LIBS_D_WTTY = oldnames libw llibcewq 
LIBS_R_WTTY = oldnames libw mlibcewq 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = ..\LIB\CONVERT.LIB 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WTTY)
LFLAGS = $(LFLAGS_D_WTTY)
LIBS = $(LIBS_D_WTTY)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
DEFFILE=E:\C151\BIN\CL.DEF
!else
CFLAGS = $(CFLAGS_R_WTTY)
LFLAGS = $(LFLAGS_R_WTTY)
LIBS = $(LIBS_R_WTTY)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
DEFFILE=E:\C151\BIN\CL.DEF
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = CONVERT.SBR \
		PARSER.SBR \
		WAVEUTIL.SBR


CONVERT_DEP = 

CONVERT_DEP = e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\samples\parser.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\samples\convert.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\samples\waveutil.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\wave.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\pcm.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\rateconv.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\rhet32.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\rhet24.h


PARSER_DEP = e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\samples\parser.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\samples\convert.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\wave.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\pcm.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\rateconv.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\rhet32.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\lib\rhet24.h


WAVEUTIL_DEP = e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\samples\convert.h \
	e:\betdev\vfedev\cifdev\pcmdev\rtxxlt\org\convwin\samples\waveutil.h


all:	$(PROJ).EXE $(PROJ).BSC

CONVERT.OBJ:	CONVERT.C $(CONVERT_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c CONVERT.C

PARSER.OBJ:	PARSER.C $(PARSER_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c PARSER.C

WAVEUTIL.OBJ:	WAVEUTIL.C $(WAVEUTIL_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c WAVEUTIL.C


$(PROJ).EXE::	CONVERT.OBJ PARSER.OBJ WAVEUTIL.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
CONVERT.OBJ +
PARSER.OBJ +
WAVEUTIL.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
E:\C151\CDK16\LIB\+
e:\c151\lib\+
e:\c151\mfc\lib\+
..\LIB\CONVERT.LIB+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@


run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
