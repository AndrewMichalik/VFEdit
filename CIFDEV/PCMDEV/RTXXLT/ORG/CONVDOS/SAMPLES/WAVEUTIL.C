/*---------------------------------------------------------------------------------*
 *  FILE      : WaveUtil.c
 *  DATE      : 3/1/95
 *  DESCR     : provide necessary functions for WAV format conversion management:
 *                - CreateWaveHeader()
 *                - CheckWaveHeader()
 *                - UpdateWaveHeaderSize()
 *                - DestroyWaveHeader()
 *              
 *---------------------------------------------------------------------------------*/

#include <sys\types.h>
#include <sys\stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include "convert.h"
#include "waveutil.h"

/*---------------------------------------------------------------------------------*
   FUNCTION  : CreateWaveHeader
   Purpose   : create & initialize a standard WAVE header structure for 
               input or output that is a WAV format
   Arguments : nSamplesPerSec - sample per second of WAV format
               wBitsPerSample - bits per second of WAV  format
   Globals   : none
   Return    : pointer to a WAVEHEADER structure containing the WAV info.
*---------------------------------------------------------------------------------*/


WAVEHEADER *CreateWaveHeader(long nSamplesPerSec, int wBitsPerSample) 
{
    WAVEHEADER *pwh;
    WAVEHEADER wave_header = {  { 'R','I','F','F' },                    /* RIFF[4]         */
                                { 0 },                                  /* size            */
                                { 'W','A','V','E','f','m','t',' ' },    /* WAVEfmt[8]      */
                                { 0x10 },                               /* dataoffset      */
                                { 1 },                                  /* wFormatTag      */
                                { 1 },                                  /* nChannels       */
                                { 11025 },                              /* nSamplesPerSec  */
                                { 11025 },                              /* nAvgBytesPerSec */
                                { 1 },                                  /* nBlockAlign     */
                                { 8 },                                  /* wBitsPerSample  */
                                {'d','a','t','a'},                      /* data[4]         */         
                                { 0 }                                   /* datasize        */         
                                                                        };
    wave_header.nSamplesPerSec   = nSamplesPerSec;
    wave_header.wBitsPerSample   = wBitsPerSample;
    wave_header.nAvgBytesPerSec  = wave_header.nChannels * wave_header.nSamplesPerSec * wave_header.wBitsPerSample/8;  
    wave_header.nBlockAlign      = wave_header.nChannels * wave_header.wBitsPerSample/8;   

    pwh = malloc(sizeof(WAVEHEADER));
    *pwh = wave_header;
    return(pwh);
}

/*---------------------------------------------------------------------------------*
   FUNCTION  : DestroyWaveHeader
   Purpose   : frees the WAV header structure from memory
   Arguments : wh - pointer to the WAV header structure to free
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void DestroyWaveHeader(WAVEHEADER *wh)            
{
    free(wh);
}

/*---------------------------------------------------------------------------------*
   FUNCTION  : CheckWaveHeader
   Purpose   : checks the WAV header for valid values in the members;
               displays error message for any invalid values
   Arguments : wh - pointer to the WAV header structure to check
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void CheckWaveHeader(WAVEHEADER *wh)            
{
    /* checks for valid format, sample bits, sample rate */
    if(wh == NULL)
        Error("Invalid Wave File Header");        
    else if (wh->wFormatTag != WAVE_FORMAT_PCM)
        Error("Invalid Wave File: File Must Have PCM type data");
    else if ( (wh->wBitsPerSample != 8) && (wh->wBitsPerSample !=16) )
        Error("Invalid Wave File: File Must Be Sampled at 8 or 16 " 
              "bits per sample");
    else if ( (wh->nChannels < 1) || (wh->nChannels > MAX_CHANNELS) )
        Error("Invalid Wave File: File Must Be Mono (1 Channel)");
    else if ( (wh->nSamplesPerSec != 44100) &&
              (wh->nSamplesPerSec != 22050) &&
              (wh->nSamplesPerSec != 11025)     )
        Error("Invalid Wave File: File Must Be Sample at 11025, 22050, or "
              "44100 Khz");
}

/*---------------------------------------------------------------------------------*
   FUNCTION  : UpdateWaveHeaderSize
   Purpose   : updates the WAV format file size in the file's header structures 
   Arguments : filename - pointer to string containing the name of file
               datasize - the running count of the actual WAV data in bytes
   Globals   : none
   Return    : none
*---------------------------------------------------------------------------------*/
void UpdateWaveHeaderSize(char *filename, long datasize )
{
    WAVEHEADER wh;
    int fd;
    
    /* open & read the WAV header */
    fd = _open(filename,_O_RDWR | _O_BINARY);
    _lseek( fd, 0L, SEEK_SET );
    _read( fd, &wh, sizeof(WAVEHEADER) ); 
    
    
    wh.size = datasize + sizeof(WAVEHEADER) - 8;    /* increment the overall size of the file */
    wh.datasize = datasize;                         /* WAV header contains new data size */
    
    /* rewind back to beginning of file and overwrite new WAV header to file */
    _lseek( fd, 0L, SEEK_SET );
    _write( fd, &wh, sizeof(WAVEHEADER) );
    _close(fd);
}

