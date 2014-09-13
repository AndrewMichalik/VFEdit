# File: CONVDOS.MAK
# Conversion Library Make File
#
# COMPILER:  Microsoft C 7.0 or later
# OUTPUT:  convdos.exe
# USAGE:   nmake convdos.mak
#          or make convdos.mak
#

CONVDOS: convert.obj parser.obj waveutil.obj
            cl -o convdos.exe convert.obj parser.obj  waveutil.obj ..\lib\convert.lib

convert.obj : convert.c     convert.h   parser.h    waveutil.h
                cl /AL /Ot /c  convert.c
parser.obj  : parser.c                  parser.h    
                cl /AL /Ot /c  parser.c
waveutil.obj: waveutil.c    convert.h   waveutil.h  
                cl /AL /Ot /c  waveutil.c
