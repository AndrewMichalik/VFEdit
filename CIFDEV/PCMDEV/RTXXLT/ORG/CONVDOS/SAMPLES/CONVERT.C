/*---------------------------------------------------------------------------------*
 *  FILE      : Convert.c
 *  DATE      : 3/1/95
 *  DESCR     : main program file containing main() entry point;
 *                - calls ParseCommandLine() defined in parser.c to parse the
 *                  command line arguments,
 *                - for each chunk of input data read from input file, do:
 *                  - calls ConvertToLin() to convert original format to LIN
 *                  - calls ConvertRate() to convert to to destination rate
 *                  - calls ConvertFromLin() to convert to destination format
 *                  - writes the result data from output buffer to output file
 *---------------------------------------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#define  getch  getchar
#include <errno.h>
#include <malloc.h>
#include <math.h>
#include "parser.h"
#include "convert.h"
#include "waveutil.h"

#include "..\lib\wave.h"
#include "..\lib\pcm.h"
#include "..\lib\rateconv.h"
#include "..\lib\rhet32.h"
#include "..\lib\rhet24.h"

int inputBuffer[INPBUFLEN];
int outputBuffer[OUTBUFLEN];

/*---------------------------------------------------------------------------------*
   FUNCTION  : main
   Purpose   : program entry point
   Arguments : argc - argument count
   Globals   : none
   Return    : 0 for successful execution
               none-zero for any error
*---------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    CONVERT *cp=NULL;
    WAVEHEADER *whp1=NULL, *whp2=NULL;
    int fd1=0, fd2=0, i;
    long total_bytes_written=0;
    
    
    cp = ConvertCreate(inputBuffer, outputBuffer);  /* intialize the CONVERT structure */

    ParseCommandLine(argc,argv, cp);        /* parse the command line options */
    CheckFiles(cp);                         /* validate the input/output file */

    fd1=_open(cp->inputFilename,_O_RDONLY | _O_BINARY );
    if(fd1==-1)     Error("Opening INPUT FILE \"%s\" \n",cp->inputFilename);
    
    fd2=_open(cp->outputFilename,_O_WRONLY | _O_CREAT | _O_EXCL | _O_BINARY, _S_IREAD | _S_IWRITE);
    
    if( errno == EEXIST )       /* if OVERWRITE option not specified, give prompt */
    {
        char ch;
        if      (cp->overWrite == FALSE) 
        {
            fprintf(stderr, "Target %s exists. Overwrite? ", cp->outputFilename );
            ch = getch();
            if( (ch == 'y') || (ch == 'Y') )
                fd2 = _open( cp->outputFilename, _O_BINARY | _O_WRONLY |
                                _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE );
            else return 0;
            fprintf(stderr, "\n" );
        }
        else if (cp->overWrite == TRUE)
            fd2 = _open( cp->outputFilename, _O_BINARY | _O_WRONLY |
                            _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE );
    }
    else if(fd2==-1)     Error("Opening OUTPUT FILE \"%s\" \n",cp->outputFilename);
    

    /* if output type is specified as WAV 8/16 bit, set the WAV format header */
    if( (cp->outputType == WAV8) || (cp->outputType == WAV16) )
    {
        long nSamplesPerSec=11025;
        int  wBitsPerSample= (cp->outputType==WAV8)? 8: 16;
        
        switch(cp->outputSampleRate) {
            case 11: nSamplesPerSec = 11025; break;
            case 22: nSamplesPerSec = 22050; break;
            case 44: nSamplesPerSec = 44100; break;
        }
        whp2  = CreateWaveHeader( nSamplesPerSec, wBitsPerSample );
        if( _write(fd2, whp2, sizeof(WAVEHEADER)) == -1 ) Error("Writing OUTPUT FILE %s",cp->outputFilename);
    }

    /* this is done again for input type WAVxx, since we'll be checking the input file */
    /* if input type is specified as WAV 8/16 bit, set the WAV format header, check it against actual input file */    
    if( (cp->inputType == WAV8) || (cp->inputType == WAV16) )
    {
        whp1  = CreateWaveHeader( 0L, 0 );
        if( _read(fd1, whp1, sizeof(WAVEHEADER)) == -1 ) Error("Reading INPUT FILE %s",cp->inputFilename);
        CheckWaveHeader(whp1);
        
        cp->inputType = (whp1->wBitsPerSample==8)? WAV8: WAV16;
        cp->inputSampleRate = (int)(whp1->nSamplesPerSec/1000L);
        
        SetRateType(cp);
//        if (cp->convertRateCb) CVC_ConvertDestroy(cp->convertRateCb);
        
        if(cp->rateType != CVT_CONV01TO01)        
            cp->convertRateCb = CVC_ConvertCreate(cp->rateType);        
        
//        if (cp->inputTypeCb)  CVC_WaveDestroy(cp->inputTypeCb);
        if (cp->inputType == WAV8)
            { cp->inputTypeCb = CVC_WaveCreate(CVT_MONO08); cp->linInpRatio = 2.0; }   
        else if (cp->inputType == WAV16)                  
            { cp->inputTypeCb = CVC_WaveCreate(CVT_MONO16); cp->linInpRatio = 1.0; }  

    }          
        /* calculate the maximum size allow per conversion in the loop */
        cp->maxInpSize = min( (unsigned int)floor(INPBUFLEN/cp->linInpRatio),
                            (unsigned int)floor((double)INPBUFLEN/cp->outputSampleRate*cp->inputSampleRate));

    
    for (i=0; i < 24; i++) putchar('\n');
    printf("ษออออออออออออออออออออหอออออออออออออออออออออออออออออออออออหออออออออออออออออออออป\n");
    printf("บ RHETOREX           บ          CONVERT UTILITY          บ  Version: 1.00     บ\n");
    printf("ศออออออออออออออออออออสอออออออออออออออออออออออออออออออออออสออออออออออออออออออออผ\n");
    printf(" input  filename     :   %s\n",          cp->inputFilename       );
    printf(" input  type         :   %s\n",          TypeStr(cp->inputType)  );
    printf(" input  sample rate  :   %2d Khz\n",    cp->inputSampleRate     );
    printf("ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ\n");
    printf(" output filename     :   %s\n",          cp->outputFilename      );
    printf(" output type         :   %s\n",          TypeStr(cp->outputType) );  
    printf(" output sample rate  :   %2d Khz\n",    cp->outputSampleRate    );  
    printf("อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ\n");
    printf("\n                          CONVERTING PLEASE WAIT \n");  
                    
    /* read each block of data upto maxInpSize, do the conversion & write result to output file */
    while((cp->inpBufSize=_read(fd1, inputBuffer,cp->maxInpSize<<1)) > 0)
    {
        cp->inpBufSize >>=1;
        cp->inpBufPtr=inputBuffer;
        cp->outBufPtr=outputBuffer;
        ConvertToLin(cp);               /* 1st, convert it to LIN */

        cp->inpBufPtr=outputBuffer;     /* switch the input <-> output */
        cp->outBufPtr=inputBuffer;
        cp->inpBufSize = *cp->outBufLen;
        ConvertRate(cp);                /* 2nd, convert the LIN to appropriate rate */

        cp->inpBufPtr=inputBuffer;      /* switch the output <-> input */
        cp->outBufPtr=outputBuffer;
        cp->inpBufSize = *cp->outBufLen;
        ConvertFromLin(cp);             /* finally, convert LIN to destination format */
        
        /* write output buffer to file */
        total_bytes_written += _write(fd2, outputBuffer,sizeof(outputBuffer[0])*(*cp->outBufLen));
        putchar('.');
    }
    
    /* if ouput type is specified as WAV 8/16 bit, must update the  header file size */
    if( (cp->outputType == WAV8) || (cp->outputType == WAV16) )
        UpdateWaveHeaderSize(cp->outputFilename, total_bytes_written);

    printf("\n\n");
    printf("------------------------------------------------------------------------------\n");
    printf(" input  file length  :   %5ld bytes\n", _filelength(fd1) );  
    printf(" output file length  :   %5ld bytes\n", _filelength(fd2) );  
    printf("------------------------------------------------------------------------------\n");

    
    /* close file descriptors used and free all structures */
    _close(fd1); _close(fd2);    
 
    ConvertDestroy(cp);
    if (whp1) DestroyWaveHeader(whp1);
    if (whp2) DestroyWaveHeader(whp2);
    return 0; 
}   


/*---------------------------------------------------------------------------------*
   FUNCTION  : ConvertToLin
   Purpose   : calls CVC_xxxx() functions to convert to LIN format
   Arguments : cp - pointer to CONVERT structure
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void ConvertToLin(CONVERT *cp)           
{
    switch(cp->inputType)
    {
        case RHET24 :   CVC_ExpandRhet24(   cp->inputTypeCb,
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case RHET32 :   CVC_ExpandRhet32(   cp->inputTypeCb,
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case ULAW   :   CVC_ExpandULAW  (   cp->inputTypeCb,
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case ALAW   :   CVC_ExpandALAW  (   cp->inputTypeCb, 
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case WAV16  :   CVC_Wave16toLin (   cp->inputTypeCb,    
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case WAV8   :   CVC_Wave8toLin  (   cp->inputTypeCb,    
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case LIN    :   memcpy( cp->outBufPtr, cp->inpBufPtr, min(cp->inpBufSize, cp->outBufSize)*2 ); 
                        *cp->inpUsed = *cp->outBufLen = min(cp->inpBufSize, cp->outBufSize);
                        break;
    }    
}

/*---------------------------------------------------------------------------------*
   FUNCTION  : ConvertFromLin
   Purpose   : calls CVC_xxxx() functions to convert from LIN to destination format
   Arguments : cp - pointer to CONVERT structure
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void ConvertFromLin(CONVERT *cp)           
{
    switch(cp->outputType)
    {
         case RHET24 :   CVC_CompressRhet24(cp->outputTypeCb,
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
         case RHET32 :   CVC_CompressRhet32(cp->outputTypeCb,
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
         case ULAW   :   CVC_CompressULAW  (cp->outputTypeCb,
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case ALAW   :   CVC_CompressALAW  ( cp->outputTypeCb, 
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case WAV16  :   CVC_LintoWave16   ( cp->outputTypeCb, 
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case WAV8   :   CVC_LintoWave8    ( cp->outputTypeCb, 
                                            cp->inpBufPtr,
                                            cp->inpBufSize,
                                            cp->inpUsed,
                                            cp->outBufPtr,
                                            cp->outBufSize,
                                            cp->outBufLen   );  break;  
        case LIN    :   memcpy( cp->outBufPtr, cp->inpBufPtr, min(cp->inpBufSize, cp->outBufSize)*2 ); 
                        *cp->inpUsed = *cp->outBufLen = min(cp->inpBufSize, cp->outBufSize);
                        break;
    }    
}


/*---------------------------------------------------------------------------------*
   FUNCTION  : ConvertRate
   Purpose   : calls CVC_Convertxxxx() functions to convert to destination
               rate; call after originalformat is converted to LIN
   Arguments : cp - pointer to CONVERT structure
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void ConvertRate(CONVERT *cp)           
{
    switch(cp->rateType)
    {
        case CVT_CONV08TO11 :   CVC_Convert08to11 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV08TO22 :   CVC_Convert08to22 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV08TO44 :   CVC_Convert08to44 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV11TO08 :   CVC_Convert11to08 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV11TO22 :   CVC_Convert11to22 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV11TO44 :   CVC_Convert11to44 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV22TO08 :   CVC_Convert22to08 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV22TO11 :   CVC_Convert22to11 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV22TO44 :   CVC_Convert22to44 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV44TO08 :   CVC_Convert44to08 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV44TO11 :   CVC_Convert44to11 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV44TO22 :   CVC_Convert08to22 ( cp->convertRateCb,
                                                    cp->inpBufPtr,
                                                    cp->inpBufSize,
                                                    cp->inpUsed,
                                                    cp->outBufPtr,
                                                    cp->outBufSize,
                                                    cp->outBufLen   );  break;  
        case CVT_CONV01TO01 :   memcpy( cp->outBufPtr, cp->inpBufPtr, min(cp->inpBufSize, cp->outBufSize)*2 ); 
                                *cp->inpUsed = *cp->outBufLen = min(cp->inpBufSize, cp->outBufSize);
                                break;
    }    
}


/*---------------------------------------------------------------------------------*
   FUNCTION  : ConvertCreate
   Purpose   : create & initialialize CONVERT structure
   Arguments : inpBufferPtr - pointer to array of integer for input storage
               outBufferPtr - pointer to array of integer for output storage
   Globals   : none
   Return    : pointer to CONVERT structure
*---------------------------------------------------------------------------------*/
CONVERT *ConvertCreate(unsigned int *inpBufferPtr, unsigned int *outBufferPtr)
{
    CONVERT *cp;
    CONVERT convert     = {    "",            /*   inputFilename[]  */  
                               LIN,           /*   inputType        */ 
                               8,             /*   inputSampleRate  */ 
                               NULL,          /*  *inputTypeCb     */ 
                               "",            /*   outputFilename[] */ 
                               LIN,           /*   outputType       */ 
                               8,             /*   outputSampleRate */ 
                               NULL,          /*  *outputTypeCb    */ 
                               NULL,          /*  *convertRateCb   */ 
                               1.0,             /*   linInpRatio      */   
                               CVT_CONV01TO01,/*   rateType         */
                               FALSE,         /*   overWrite        */
                               0,             /*   maxInpSize       */
                               inpBufferPtr,     /*  *inpBufPtr        */ 
                               INPBUFLEN,    /*   inpBufSize       */ 
                               NULL,          /*  *inpUsed          */ 
                               outBufferPtr,     /*  *outBufPtr        */ 
                               OUTBUFLEN,    /*   outBufSize       */ 
                               NULL           /*  *outBufLen        */   
                                                };
                                        
    
    convert.inpUsed     = malloc(sizeof(*convert.inpUsed));
    *convert.inpUsed    = 0;
    convert.outBufLen   = malloc(sizeof(*convert.outBufLen));
    *convert.outBufLen  = 0;
    
    cp = malloc(sizeof(convert));
    *cp = convert;

    return(cp);
}

/*---------------------------------------------------------------------------------*
   FUNCTION  : ConvertDestroy
   Purpose   : frees the memory & structures used within the CONVERT members
   Arguments : cp - pointer to CONVERT structure
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void ConvertDestroy(CONVERT *cp)
{
    switch(cp->inputType)
    {
        case RHET32 : CVC_Rhet32Destroy(cp->inputTypeCb);              break; 
        case RHET24 : CVC_Rhet24Destroy(cp->inputTypeCb);              break;
        case ULAW   : CVC_PCMDestroy(cp->inputTypeCb);                 break; 
        case ALAW   : CVC_PCMDestroy(cp->inputTypeCb);                 break; 
        case WAV16  : CVC_WaveDestroy(cp->inputTypeCb);                break; 
        case WAV8   : CVC_WaveDestroy(cp->inputTypeCb);                break;   
        case LIN    :                                                  break;         
    }    
    switch(cp->outputType)
    {
        case RHET32 : CVC_Rhet32Destroy(cp->outputTypeCb);             break; 
        case RHET24 : CVC_Rhet24Destroy(cp->outputTypeCb);             break;
        case ULAW   : CVC_PCMDestroy(cp->outputTypeCb);                break; 
        case ALAW   : CVC_PCMDestroy(cp->outputTypeCb);                break; 
        case WAV16  : CVC_WaveDestroy(cp->outputTypeCb);               break; 
        case WAV8   : CVC_WaveDestroy(cp->outputTypeCb);               break;   
        case LIN    :                                                  break;         
    }    
    
    if (cp->rateType != CVT_CONV01TO01)
        CVC_ConvertDestroy(cp->convertRateCb);
            
    free(cp->inputFilename);
    free(cp->outputFilename);
    free(cp->inpUsed);  
    free(cp->outBufLen);
    free(cp);
}

/*---------------------------------------------------------------------------------*
   FUNCTION    CheckFiles
   Purpose   : if the output file name is not supply in the command line,
               constructs the output file name with appropriate extension
               associated the output type
   Arguments : cp - pointer to CONVERT structure containing the conversion
               information.
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void CheckFiles(CONVERT *cp)
{
    char *file_ext_table[] = { "R32", "R24", "ULW", "ALW", "WAV", "WAV", "LIN" };
    int n;
    
    if (strlen(cp->inputFilename) == 0 )
        Error("No input filename specified");
    if (strlen(cp->outputFilename) == 0)
    {
        n=strlen(cp->inputFilename)-strlen(strrchr(cp->inputFilename,'.'));
        sprintf(cp->outputFilename,"%.*s.%s",n,cp->inputFilename,file_ext_table[cp->outputType]);
    }   

}            

/*---------------------------------------------------------------------------------*
   FUNCTION  : TypeStr   
   Purpose   : associate the format type with a text string for display
   Arguments : it - the format type
   Globals   : none
   Return    : pointer to to the string of text
*---------------------------------------------------------------------------------*/
char *TypeStr(int it)
{
    char str[80];
    switch(it)
    {
        case RHET32:    strcpy(str,"RHETOREX          32 Kbit/sec");    break;
        case RHET24:    strcpy(str,"RHETOREX          24 Kbit/sec");    break;
        case ULAW:      strcpy(str,"ULAW PCM          64 Kbit/sec");    break;
        case ALAW:      strcpy(str,"ALAW PCM          64 Kbit/sec");    break;
        case WAV8:      strcpy(str,"WAVE MONO  8 bit  64 Kbit/sec");    break;
        case WAV16:     strcpy(str,"WAVE MONO 16 bit 128 Kbit/sec");    break;
        case LIN:       strcpy(str,"LINEAR           128 Kbit/sec");    break;
    }   
    return str;
}    