// listing 1, lfnames.h
#ifdef __cplusplus
extern "C" {
#endif
#define LFN_MAX_PATH 260
#define SFN_MAX_PATH 80
int lfn_api( const char *rootname );
unsigned GetShortPathName( const char *filename,
              const char *shortname, unsigned size );
unsigned GetLongPathName( const char *filename,
              const char *longname, unsigned size );
int lfn_mkdir( const char *path );
int lfn_rmdir( const char *path );
int lfn_chdir( const char *path );
int lfn_unlink( const char *path );
int lfn_rename( const char *oldname, const char *newname );
int lfn_access( const char *path, int amode );
int lfn_open( const char *path, int mode, int smode );
FILE *lfn_fopen( const char *filename, const char *mode );
int lfn_findfirst( const char *path, int attrib, struct lfn_find_t *finfo );
int lfn_findnext( struct lfn_find_t *finfo );
void lfn_findclose( struct lfn_find_t *finfo );

struct lfn_find_t
{
    char     attrib;            /* attribute byte for matched file */
    unsigned wr_time;           /* time of last write to file */
    unsigned wr_date;           /* date of last write to file */
    unsigned long size;         /* size of file */
    char     name[LFN_MAX_PATH]; /* asciiz name of matched file */
    int      findhandle;
};

#ifdef __cplusplus
}
#endif
