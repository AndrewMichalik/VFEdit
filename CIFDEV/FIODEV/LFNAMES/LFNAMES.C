// listing 2, lfnames.c
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <string.h>
#include <errno.h>

#include "lfnames.h"

#define TEST  // defines main to make test program

#ifdef _MSC_VER
#if (_MSC_VER>=600)
#define SREGS _SREGS
#define REGS  _REGS
#define intdosx _intdosx
#undef FP_OFF
#undef FP_SEG
// need to do this for MSC, because the MSC version requires
// an Lvalue for the pointer!
#define FP_OFF(p) (unsigned short)(p)
#define FP_SEG(p) (unsigned short)((unsigned long)(void __far *)(p)>>16)
#endif
#endif

static int DoDosCall( unsigned func, union REGS *r, struct SREGS *s )
// helper function to call DOS interrupt
{
   r->x.ax = func;
   intdosx(r,r,s);
   if(r->x.cflag)
      _doserrno = r->x.ax;
   else
      _doserrno = 0;
   return r->x.cflag;
}

#define SETPTR(seg,off,ptr) s.seg = FP_SEG((ptr)), r.x.off = FP_OFF((ptr))

int lfn_api( const char *rootname )
// returns non-zero if volume supports long file names
{
   union REGS r; struct SREGS s;
   char filesystem[40];
   memset(&s,0,sizeof(s));
   SETPTR(es,di,filesystem);
   r.x.cx = sizeof(filesystem);
   SETPTR(ds,dx,rootname);
   if(DoDosCall(0x71a0,&r,&s))
      return 0;
   return r.x.bx & 0x4000;  // check for FS_LFN_APIS flag
}

unsigned GetShortPathName( const char *filename,
              const char *shortname, unsigned size )
{
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   if(size<SFN_MAX_PATH)  // path too small?
      return 0;
   SETPTR(ds,si,filename);
   SETPTR(es,di,shortname);
   r.x.cx = 1;
   if(DoDosCall(0x7160,&r,&s))
      return 0;
   return strlen(shortname);
}

unsigned GetLongPathName( const char *filename,
              const char *longname, unsigned size )
{
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   if(size<LFN_MAX_PATH)  // path too small?
      return 0;
   SETPTR(ds,si,filename);
   SETPTR(es,di,longname);
   r.x.cx = 2;
   if(DoDosCall(0x7160,&r,&s))
      return 0;
   return strlen(longname);
}

int lfn_mkdir( const char *path )
{
   union REGS r; struct SREGS s;
   SETPTR(ds,dx,path);
   if(DoDosCall(0x7139,&r,&s))
     return -1;
   return 0;
}

int lfn_rmdir( const char *path )
{
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   SETPTR(ds,dx,path);
   if(DoDosCall(0x713a,&r,&s))
     return -1;
   return 0;
}

int lfn_chdir( const char *path )
{
   union REGS r; struct SREGS s;
   SETPTR(ds,dx,path);
   if(DoDosCall(0x713b,&r,&s))
      return -1;
   return 0;
}

int lfn_unlink( const char *path )
{
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   SETPTR(ds,dx,path);
   r.h.cl = _A_ARCH|_A_SYSTEM|_A_RDONLY;
   r.h.ch = 0; // must match
   r.x.si = 0; // no wild cards
   if(DoDosCall(0x7141,&r,&s))
     return -1;
   return 0;
}

int lfn_rename( const char *oldname, const char *newname )
{
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   SETPTR(ds,dx,oldname);
   SETPTR(es,di,newname);
   if(DoDosCall(0x7156,&r,&s))
      return -1;
   return 0;
}

int lfn_access( const char *path, int amode )
{
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   r.x.bx = 0;       // get extended attributes
   SETPTR(ds,dx,path);
   if(DoDosCall(0x7143,&r,&s))
      return -1;
   if(!(amode&0x02) || !(r.x.cx & _A_RDONLY) )
      return 0;
   errno = EACCES;
   return -1;
}

typedef unsigned long DWORD;

typedef struct _FILETIME {
   DWORD dwLowDateTime;
   DWORD dwHighDateTime;
} FILETIME;

typedef struct _WIN32_FIND_DATA { // wfd
   DWORD dwFileAttributes;
   FILETIME ftCreationTime;
   FILETIME ftLastAccessTime;
   FILETIME ftLastWriteTime;
   DWORD    nFileSizeHigh;
   DWORD    nFileSizeLow;
   DWORD    dwReserved0;
   DWORD    dwReserved1;
   char     cFileName[ LFN_MAX_PATH ];
   char    cAlternateFileName[ 14 ];
} WIN32_FIND_DATA;

int lfn_findfirst( const char *path, int attrib, struct lfn_find_t *finfo )
{
   WIN32_FIND_DATA finddata;
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   SETPTR(ds,dx,path);
   SETPTR(es,di,&finddata);
   r.x.cx = attrib;
   r.x.si = 1; // MS-DOS format time/date
   if(DoDosCall(0x714e,&r,&s))
      return -1;
   finfo->findhandle = r.x.ax;  // save find handle
   strcpy(finfo->name,finddata.cFileName);
   finfo->size = finddata.nFileSizeLow;
   finfo->wr_date =
      (unsigned)(finddata.ftLastWriteTime.dwLowDateTime >> 16 );
   finfo->wr_time =
      (unsigned)(finddata.ftLastWriteTime.dwLowDateTime & 0xffff );
   finfo->attrib = finddata.dwFileAttributes & 0x7f;
   return 0;
}

int lfn_findnext( struct lfn_find_t *finfo )
{
   WIN32_FIND_DATA finddata;
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   SETPTR(es,di,&finddata);
   r.x.si = 1; // use dos time
   r.x.bx = finfo->findhandle;
   if(DoDosCall(0x714f,&r,&s))
      return -1;
   strcpy(finfo->name,finddata.cFileName);
   finfo->size = finddata.nFileSizeLow;
   finfo->wr_date =
      (unsigned)(finddata.ftLastWriteTime.dwLowDateTime >> 16);
   finfo->wr_time =
      (unsigned)(finddata.ftLastWriteTime.dwLowDateTime & 0xffff );
   finfo->attrib = finddata.dwFileAttributes & 0x7f;
   return 0;
}

void lfn_findclose( struct lfn_find_t *finfo )
{
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   r.x.bx = finfo->findhandle;
   DoDosCall(0x71a1,&r,&s);
}

int lfn_open( const char *path, int mode, int smode )
{
   union REGS r; struct SREGS s;
   memset(&s,0,sizeof(s));
   SETPTR(ds,si,path);
   r.x.bx = mode & 0x3; // read/write flags
   if(mode & O_CREAT) {
      switch(smode&(S_IREAD|S_IWRITE)) {
         case 0:
            r.x.bx |= 0x0010; // deny read/write
            break;
         case S_IREAD:
            r.x.bx |= 0x0020; // deny write
            break;
         case S_IWRITE:
            r.x.bx |= 0x0030; // deny read
            break;
         case S_IWRITE|S_IREAD:
            r.x.bx |= 0x0040; // deny none
            break;
      }
   }
   r.x.cx = _A_NORMAL;
   r.x.dx = 0;
   if(mode & O_CREAT ) r.x.dx |= 0x0010;
   if(mode & O_TRUNC ) r.x.dx |= 0x0002;
   if(mode & O_EXCL ) r.x.dx |= 0x0001;  // file must exist
   if(DoDosCall(0x716c,&r,&s))
      return -1;
   return r.x.ax;  // return file handle
}

FILE *lfn_fopen( const char *filename, const char *mode )
{
   char shortname[LFN_MAX_PATH];
   if( strchr(mode,'a') || strchr(mode,'w') ) {
      // if the file doesn't exist - create it
      if( lfn_access(filename,00) ) {
         int hf = lfn_open(filename,O_CREAT|O_TRUNC|O_WRONLY,0);
         close(hf);
      }
   } // convert a long name to a short name, if needed
   GetShortPathName(filename,shortname,sizeof(shortname));
   return fopen(shortname,mode);
}

#ifdef TEST
int main( int argc, char **argv )
{
   if(argc>2) {
      if( strcmpi(argv[1],"api")==0 ) {
         printf("Long filenames are %savailable for \"%s\".\n",
            lfn_api(argv[2])?"":"not ",argv[2]);
      } else if( strcmpi(argv[1],"shortname")==0 ) {
         char buf[SFN_MAX_PATH];
         if( GetShortPathName(argv[2],buf,sizeof(buf)) ) {
            printf("The short name of %s is %s.\n",argv[2],buf);
            {
               int i;
               for(i=0;i<strlen(buf);i++)
                  printf("'%c' %02x ",buf[i],buf[i]);
            }
         } else
            printf("Unable to convert to %s to a short name.\n",
               argv[2]);
      } else if( strcmpi(argv[1],"longname")==0 ) {
         char buf[LFN_MAX_PATH];
         if( GetLongPathName(argv[2],buf,sizeof(buf)) )
            printf("The long name of \"%s\" is \"%s\".\n",argv[2],buf);
         else
            printf("Unable to convert to \"%s\" to a long name.\n",
               argv[2]);
      } else if( strcmpi(argv[1],"mkdir")==0) {
         if( lfn_mkdir(argv[2]) )
            printf("dos error %d\n",_doserrno);
      } else if( strcmpi(argv[1],"chdir")==0) {
         if( lfn_chdir(argv[2]) )
            printf("dos error %d\n",_doserrno);
      } else if( strcmpi(argv[1],"rmdir")==0) {
         if( lfn_rmdir(argv[2]) )
            printf("dos error %d\n",_doserrno);
      } else if( strcmpi(argv[1],"exist")==0) {
         printf("The file \"%s\" does %sexist.\n",
            argv[2],lfn_access(argv[2],0)?"not ":"");
      } else if( strcmpi(argv[1],"del")==0) {
         if( lfn_unlink(argv[2]) )
            printf("dos error %d\n",_doserrno);
      } else if( strcmpi(argv[1],"readfile")==0 ) {
         FILE *f = lfn_fopen(argv[2],"rb");
         if(f) {
            fseek(f,0,SEEK_END);
            printf("The size of \"%s\" is %ld.\n",argv[2],ftell(f));
            fclose(f);
         } else
            printf("Failed to open \"%s\".\n",argv[2]);
      } else if( strcmpi(argv[1],"writefile")==0 ) {
          FILE *f = lfn_fopen(argv[2],"w");
          if(f) {
             fprintf(f,"This file is named \"%s\"\n",argv[2]);
             fclose(f);
          } else
             printf("Failed to open \"%s\".\n",argv[2]);
      } else if( strcmpi(argv[1],"dir")==0 ) {
         struct lfn_find_t f; int i;
         for(i=lfn_findfirst(argv[2],_A_NORMAL,&f); i==0; i=lfn_findnext(&f) )
             printf("%s %d/%d/%d %02d:%02d:%02d %lu\n",f.name,
                   (f.wr_date>>5)&0xf,f.wr_date&0x1f,(f.wr_date>>9)+1980,
                   f.wr_time>>11,(f.wr_time>>5)&0x3f,(f.wr_time&0x1f)*2,
                   f.size);
         lfn_findclose(&f);
      } else
         printf("unrecognized command %s\n",argv[1]);
   } else
      printf("syntax: longname cmd filename\n");
   return 0;
}
#endif
