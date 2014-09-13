/*---------------------------------------------------------------------------------*
 *  FILE      : Parser.c
 *  DATE      : 3/1/95
 *  DESCR     : contains functions to parse the command line arguments or 
 *              command file:
 *                - ParseCommandLine() calls GetToken() to read each argument,
 *                  and then calls ExecuteToken() to sets the approriate values
 *                  in the CONVERT structure passed in as an argument
 *---------------------------------------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef _WINDOWS
#define _WINDOWS
#include <conio.h>
#undef  _WINDOWS
#endif
#define getch getchar

#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "parser.h"

#include "..\lib\wave.h"
#include "..\lib\pcm.h"
#include "..\lib\rateconv.h"
#include "..\lib\rhet32.h"
#include "..\lib\rhet24.h"
             
/*---------------------------------------------------------------------------------*
   FUNCTION  : GetToken
   Purpose   : search the input string (command line arguments) for the next token;
               sets the token value to constants defined in "parser.h"
   Arguments : string - pointer to constant characters containing the command line
   Globals   : none
   Return    : a TOKEN structure containing the token and its symbolic constant value
*---------------------------------------------------------------------------------*/

TOKEN GetToken(const char *string)
{   
    TOKEN t= { END, INPUT, "" };     
    
    if (string[0] == '/')   /* this means continuation of command line on nexe line */ 
    {
        string++;
        if      (strnicmp(string,   "NO",2) == 0)   t.token_value=NODISPLAY;
        else if (strnicmp(string,   "OV",2) == 0)   t.token_value=OVERWRITE;
        else if (strcmp(string,     "?")    == 0)   t.token_value=HELP;
        else if (string[2] ==       ':')
        { 
            /* check if this current option applies to input or output */
            if(toupper(string[0]) ==        'I')  
                t.io_direction=INPUT;
            else if(toupper(string[0]) ==   'O')  
                t.io_direction=OUTPUT;
            else
                Error("Unknown OPTION \"/%s\"\n",string); 
                
            /* advance to next char and look for the actual option paramater */
            string++;    
            if      (strnicmp(string,   "S:",2) == 0)   /* it's a sample rate option */
            {
                t.token_value =SAMPLERATE;
                string+=2;
                t.number=(int)strtol(string,NULL,10);   /* read in the sample rate*/
                if( (t.number != 8)  && 
                    (t.number != 11) && 
                    (t.number != 22) && 
                    (t.number != 44) )          
                    Error("In OPTION \"/%cS:xx\", rate xx must be 8, 11, 22, or 44!\n",
                        (t.io_direction==INPUT)?'I':'O');
            }
            else if (strnicmp(string,   "T:",2) == 0)   /* it's a format type option */
            {
                string+=2;
                if     (stricmp(string,"RHET32") == 0)   t.token_value=RHET32;
                else if(stricmp(string,"RHET24") == 0)   t.token_value=RHET24;
                else if(stricmp(string,"ULAW") == 0)     t.token_value=ULAW;
                else if(stricmp(string,"ALAW") == 0)     t.token_value=ALAW;
                else if(stricmp(string,"WAV8") == 0)     t.token_value=WAV8;
                else if(stricmp(string,"WAV16")== 0)     t.token_value=WAV16;
                else if(stricmp(string,"LIN")  == 0)     t.token_value=LIN;
                else Error("In OPTION \"/%cT:xx\", type xx must be: \n"   
                           "RHET24, RHET32, ULAW, ALAW, WAV8, WAV16 or LIN!\n",
                           (t.io_direction==INPUT)?'I':'O');
            }
        }        
        else Error("Unknown OPTION \"/%s\"\n",string); 
    }
    else if (string[0] == '@') /* the command line options are contained in a command file */
    {
        string++;
        t.token_value = COMMANDFILE;
        strncpy(t.filename, string, CVM_SIZEFILENAME);
    }    
    else   /* if all else filtered, then it's an input/output FILE NAME */
    {
        t.token_value = FILENAME;    
        strncpy(t.filename, string, CVM_SIZEFILENAME);
    }     

    return t;            
}        
     
/*---------------------------------------------------------------------------------*
   FUNCTION  : ExecuteToken
   Purpose   : for each value of token passed in, store appropriate value in
               the CONVERT structure's associate members: formats, input file,
               output file, sample rate ...
   Arguments : t - a current token return from GetToken() above.
               cp - pointer to CONVERT structure for update te values
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void ExecuteToken(const TOKEN t, CONVERT *cp)     
{
    switch(t.token_value)
    {
        case NODISPLAY      :   fclose(stdout);                     break;
        case OVERWRITE      :   cp->overWrite=TRUE;                 break;
        case HELP           :   Help();                             break;
        case COMMANDFILE    :   ParseCommandFile(t.filename, cp);   break;
        case RHET32         : 
        case RHET24         :
        case ULAW           :
        case ALAW           :
        case WAV16          : 
        case WAV8           :   
        case LIN            :   if (t.io_direction == INPUT)
                                    cp->inputType = t.token_value;
                                else  /* (t.io_direction == OUTPUT) */                    
                                    cp->outputType = t.token_value;
                                break;
        case SAMPLERATE     :   if (t.io_direction == INPUT)
                                    cp->inputSampleRate = t.number;
                                else  /* (t.io_direction == OUTPUT) */                    
                                    cp->outputSampleRate = t.number;
                                break;
        case FILENAME       :   if (strlen(cp->inputFilename) == 0) 
                                    strcpy(cp->inputFilename, t.filename);
                                else if (strlen(cp->outputFilename) ==0)
                                    strcpy(cp->outputFilename, t.filename);
                                else Error("FILENAME \"%s\" there are already input and "
                                    "output filenames specified!\n", t.filename);
    }
}

/*---------------------------------------------------------------------------------*
   FUNCTION  : ParseCommandFile
   Purpose   : reads the command file as input commands to program instead 
               of command line arguments
   Arguments : filename - pointer to string containing name of command file
               cp - pointer CONVERT structure for update
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void ParseCommandFile(const char *filename, CONVERT *cp)
{
    TOKEN t;
    FILE *command_file;
    char string[80];
        
    command_file = fopen(filename,"rb"); 
    if (command_file == NULL) Error("The COMMANDFILE \"%s\" does not exist!",filename);
    /* for each command string in the command file, read it and act on it just like the command line */
    while(fscanf(command_file,"%s",string)!=EOF)
    {
        t=GetToken(string);
        ExecuteToken(t,cp);
    } 
    fclose(command_file);
}

/*---------------------------------------------------------------------------------*
   FUNCTION  : ParseCommandLine
   Purpose   : parse the command line argument by calling GetToken() to get 
               next token and sets the appropriate values in the CONVERT structure 
               byt calling ExecutingToken()
   Arguments : argc - integer count of number of arguments
               argv - pointer to array of strings containing the arguments
   Globals   : cp - pointer to CONVERT structure for storing the command values
   Return    : none
*---------------------------------------------------------------------------------*/
void ParseCommandLine(const int argc, const char **argv, CONVERT *cp)
{
    TOKEN t;
    int arg_count = argc;         
    const char **arg_vector = argv; 

    if(arg_count == 1)
    {
        printf("\nUsage: for HELP please type CONVERT /?\n");
        exit(0);
    }

    /* look at each argument and set the appropriate fields in the CONVERT structure */        
    while(--arg_count)
    {
        t=GetToken(*++arg_vector);
        ExecuteToken(t,cp);
    }

    /* create the input/output type structure that will be needed for convertion */    
    switch(cp->inputType)
    {
        case RHET24 : cp->inputTypeCb = CVC_Rhet24Create(CVT_RHET24_EXP);  cp->linInpRatio = 16.0/3.0; break; 
        case RHET32 : cp->inputTypeCb = CVC_Rhet32Create(CVT_RHET32_EXP);  cp->linInpRatio = 4.0;      break; 
        case ULAW   : cp->inputTypeCb = CVC_PCMCreate(CVT_ULAW_EXP);       cp->linInpRatio = 2.0;      break; 
        case ALAW   : cp->inputTypeCb = CVC_PCMCreate(CVT_ALAW_EXP);       cp->linInpRatio = 2.0;      break; 
        case WAV16  : cp->inputTypeCb = CVC_WaveCreate(CVT_MONO16);        cp->linInpRatio = 1.0;      break; 
        case WAV8   : cp->inputTypeCb = CVC_WaveCreate(CVT_MONO08);        cp->linInpRatio = 2.0;      break;   
        case LIN    :                                                      cp->linInpRatio = 1.0;      break;         
    }    
    
    switch(cp->outputType)
    {
        case RHET24 : cp->outputTypeCb = CVC_Rhet24Create(CVT_RHET24_CMP); break; 
        case RHET32 : cp->outputTypeCb = CVC_Rhet32Create(CVT_RHET32_CMP); break; 
        case ULAW   : cp->outputTypeCb = CVC_PCMCreate(CVT_ULAW_CMP);      break; 
        case ALAW   : cp->outputTypeCb = CVC_PCMCreate(CVT_ALAW_CMP);      break; 
        case WAV16  : cp->outputTypeCb = CVC_WaveCreate(CVT_MONO16);       break; 
        case WAV8   : cp->outputTypeCb = CVC_WaveCreate(CVT_MONO08);       break;   
        case LIN    :                                                      break;         
    }    
    
    /* set the rate type, rate structure, and maximum input size allowed */
    SetRateType(cp);
    
    if(cp->rateType != CVT_CONV01TO01)        
        cp->convertRateCb= CVC_ConvertCreate(cp->rateType);        

    cp->maxInpSize = min( (unsigned int)floor(INPBUFLEN/cp->linInpRatio),
                          (unsigned int)floor((double)INPBUFLEN/cp->outputSampleRate*cp->inputSampleRate));
    
}        

/*---------------------------------------------------------------------------------*
   FUNCTION  : SetRateType
   Purpose   : looks at the outputType,inputSampleRate & outputSampleRate
               in the CONVERT structure to set the constant conversion rate 
               type value to be used later to for rate conversion; 
   Arguments : cp - pointer to CONVERT structure that stores these values
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void SetRateType(CONVERT *cp)
{
    if     ( ((cp->outputType == WAV8) || (cp->outputType == WAV16))
             && 
             (  (cp->outputSampleRate != 11 ) &&
                (cp->outputSampleRate != 22 ) &&
                (cp->outputSampleRate != 44 )    )                   )
        cp->outputSampleRate = 11;
        
    if     ((cp->inputSampleRate == 8) && (cp->outputSampleRate == 11))
        cp->rateType = CVT_CONV08TO11;
    else if((cp->inputSampleRate == 8) && (cp->outputSampleRate == 22))
        cp->rateType = CVT_CONV08TO22;
    else if((cp->inputSampleRate == 8) && (cp->outputSampleRate == 44))
        cp->rateType = CVT_CONV08TO44;
    else if((cp->inputSampleRate == 11) && (cp->outputSampleRate == 8))
        cp->rateType = CVT_CONV11TO08;
    else if((cp->inputSampleRate == 11) && (cp->outputSampleRate == 22))
        cp->rateType = CVT_CONV11TO22;
    else if((cp->inputSampleRate == 11) && (cp->outputSampleRate == 44))
        cp->rateType = CVT_CONV11TO44;
    else if((cp->inputSampleRate == 22) && (cp->outputSampleRate == 8))
        cp->rateType = CVT_CONV22TO08;
    else if((cp->inputSampleRate == 22) && (cp->outputSampleRate == 11))
        cp->rateType = CVT_CONV22TO11;
    else if((cp->inputSampleRate == 22) && (cp->outputSampleRate == 44))
        cp->rateType = CVT_CONV22TO44;
    else if((cp->inputSampleRate == 44) && (cp->outputSampleRate == 8))
        cp->rateType = CVT_CONV44TO08;
    else if((cp->inputSampleRate == 44) && (cp->outputSampleRate == 11))
        cp->rateType = CVT_CONV44TO11;
    else if((cp->inputSampleRate == 44) && (cp->outputSampleRate == 22))
        cp->rateType = CVT_CONV44TO22;
    else
        cp->rateType = CVT_CONV01TO01;     
       
}
        
/*---------------------------------------------------------------------------------*
   FUNCTION  : Help
   Purpose   : display the usage if the user enters option '/?' without the
               quotes in the command line and then exits program.
   Arguments : none
   Globals   : none
   Return    : exits program with error code 0.
*---------------------------------------------------------------------------------*/
void Help()
{

    
    printf("\n                                                                               ");
    printf("\nษออออออออออออออออออออหอออออออออออออออออออออออออออออออออออหออออออออออออออออออออป");
    printf("\nบ RHETOREX           บ          CONVERT UTILITY          บ  Version: 1.00     บ");
    printf("\nฬออออออออออออออออออออสอออออออออออออออออออออออออออออออออออสออออออออออออออออออออน");
    printf("\nบ usage: CONVERT [@<command file>] [options]  <input file>  <output file>     บ");
    printf("\nวฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ");
    printf("\nบ [options] :                                                                 บ");
    printf("\nบ                            - FILE FORMAT TYPE -                             บ");
    printf("\nบ   /IT:<type>: Input file type           /OT:<type>: Output file type        บ");
    printf("\nบ   where <type> is one of the following:                                     บ");
    printf("\nบ    RHET32:    Rhetorex 32 Kbit/Sec      RHET24:    Rhetorex 24 KBit/Sec     บ");
    printf("\nบ    ULAW  :    U-LAW PCM 64 Kbit/Sec     ALAW  :    A-LAW PCM 64 Kbit/Sec    บ");
    printf("\nบ    WAV8  :    Windows .WAV format 8BIT  WAV16 :    Windows .WAV format 16BITบ");
    printf("\nบ    LIN   :    Linear 128 Kbit/Sec                                           บ");
    printf("\nบ                                                                             บ");
    printf("\nบ                               - SAMPLE RATE -                               บ");
    printf("\nบ   /IS:<samplerate>: Input Sample Rate   /OS:<samplerate>: Output Sample Rateบ");
    printf("\nบ   where <samplerate> is one of the following KHZ rates:  8, 11, 22, 44      บ");
    printf("\nบ                                                                             บ");
    printf("\nบ                              - MISCELLANEOUS -                              บ");
    printf("\nบ   /NODISPLAY:   suspend display           /?:   help screen                 บ");
    printf("\nบ   /OVERWRITE:   overwrite output file without prompting user                บ");
    printf("\nศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ");
    printf("\n                                                                               ");
    printf(  "                    hit any key to continue ...");
    getch();
    printf("\r");
    exit(0);
} 

/*---------------------------------------------------------------------------------*
   FUNCTION  : Error
   Purpose   : prints the error message to standard error output device:
               screen or a file depending on the system mapping.
   Arguments : variable number of arguments including a format string and 
               format argument as in a printf() statement.
   Globals   : none
   Return    : exits program with error code of 1.
*---------------------------------------------------------------------------------*/
void Error(const char *fmt, ... )
{
    va_list args;
    
    va_start(args, fmt);
    fprintf(stderr,"\nCONVERT error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

