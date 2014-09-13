/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป*/
/*บฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐบ*/
/*บฐ                                                                    ฐบ*/
/*บฐ                         PARSER.h                                   ฐบ*/
/*บฐ                                                                    ฐบ*/
/*บฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐบ*/
/*ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

    #ifndef _CV_PARSER_H_INCLUDED
    #define _CV_PARSER_H_INCLUDED

#include "convert.h"
/*ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ*/
/*ณ                     Definitions                                     ณ*/
/*ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู*/
#define FALSE 0
#define TRUE  1
#define CVM_SIZEFILENAME 80

typedef enum tagTOKEN_VALUE
{ 
    RHET32, RHET24, ULAW, ALAW, WAV8, WAV16, LIN,
    HELP='?', COMMANDFILE='@', FILENAME, SAMPLERATE, NODISPLAY, OVERWRITE, 
    END 
} TOKEN_VALUE;

typedef enum tagIO_DIRECTION { INPUT, OUTPUT } IO_DIRECTION;
                              
typedef struct tagTOKEN 
{
    TOKEN_VALUE     token_value                   ;
    IO_DIRECTION    io_direction                  ;
    char            filename[CVM_SIZEFILENAME]   ;
    int             number                        ;
} TOKEN;                            

/*ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ*/
/*ณ                     Function Prototypes                             ณ*/
/*ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู*/

extern TOKEN GetToken(const char *string);
extern void ExecuteToken(const TOKEN t, CONVERT *cp);     
extern void ParseCommandLine(const int argc, const char **argv, CONVERT *cp);
extern void ParseCommandFile(const char *filename, CONVERT *cp);
extern void SetRateType(CONVERT *cp);
extern void Help();
extern void Error(const char *fmt, ... );

    #endif  /* _CV_PARSER_H_INCLUDED */
