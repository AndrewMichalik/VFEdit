Rhetorex Conversion Library for DOS & Windows
Release 0.1 BETA Release Notes


A. Summary

Speech can be digitized and stored in PC files in a number of different formats.  
Most popular sound board speech file formats combine three elements: sampling 
rate, encoding method and file header.  Speech files created by voice processing 
boards (like Rhetorex) are similar, but do not include a file header.

The Conversion Library is designed for the development of speech file conversion 
programs.  It converts speech files between the several popular formats, including 
PCM, WAVE and Rhetorex.  A Rhetorex board is not required to use the Conversion 
Library: the conversion is performed on the host processor.

Formats supported:
				u-Law PCM
				A-Law PCM
				Wave 8-bit
				Wave 16-bit
				Rhetorex 24K ADPCM
				Rhetorex 32K ADPCM

Sampling rates supported:
				8000
				11025
				22059
				44100


B. What's Included

This release package includes a Conversion Library Disk for DOS and Windows
and these release notes.

In order to speed up application development two sample programs, CONVDOS.EXE and 
CONVWIN.EXE, have been included to illustrate the usage of the library functions. You 
can use either sample to convert speech files to another format.  In fact, you may 
find the samples are adequate for the job and thus never need to learn the Conversion 
Library and write your own conversion application.


C. Installation

Use the Windows File Manager or the DOS XCOPY command to copy the files to 
your hard disk.

These files are delivered on the diskette:

\CONVDOS
	\LIB
		CONVERT.LIB	Conversion library for DOS
		PCM.H		Header file for conversions to/from PCM
		RATECONV.H	Header file for rate conversions
		RHET24.H	For conversions to/from Rhetorex 24K ADPCM
		RHET32.H	For conversions to/from Rhetorex 32K ADPCM
		WAVE.H		For conversions to/from WAVE
	\SAMPLES
		CONVDOS.EXE	Sample program for DOS, plus source files
		CONVDOS.MAK
		CONVERT.C
		CONVERT.H
		PARSER.C
		PARSER.H
		WAVUTIL.C
		WAVUTIL.H
\CONVWIN
	\LIB
		CONVERT.LIB	Conversion library for Windows 3.1
		PCM.H		Header file for conversions to/from PCM
		RATECONV.H	Header file for rate conversions
		RHET24.H	For conversions to/from Rhetorex 24K ADPCM
		RHET32.H	For conversions to/from Rhetorex 32K ADPCM
		WAVE.H		For conversions to/from WAVE
	\SAMPLES
		CONVERT.C 	Sample program for Win 3.1, plus source files
		CONVERT.H
		CONVWIN.EXE
		CONVWIN.MAK
		PARSER.C
		PARSER.H
		WAVUTIL.C
		WAVUTIL.H
\README.TXT			Release Notes
\RELNOTES.DOC			Release Notes in Microsoft Word 6.0 format


D. Limitations

Both the DOS and Windows versions of CONVERT.LIB support large models programs only.  
The DOS library supports versions 7.0 and later of the Microsoft C Compiler.  The
Windows library supports version 1.5 and later of the Microsoft Visual C++ compiler.

The CONVWIN sample for Windows is based on the CONVDOS sample for DOS.  It 
was compiled using the QuickWin (.EXE) option of Visual C++, version 1.5 and 
uses the same text user interface as the DOS sample.


E. Documentation

The Conversion Library Manual is still under development at the time of this 
software release.  This section describes the use of the Library.

GENERAL THEORY
The Conversion Library is designed to convert a speech file in ‘chunks’, a buffer at a 
time.  Accordingly, each library function acts on an integer array of speech data.  
Since information about the preceding buffer in needed to correctly convert certain 
formats, such as ADPCM, the Conversion Library makes use of a structure to 
consolidate the information required for the conversion.

The conversion of sampling rates, encoding methods and file headers are each 
performed separately.  In general, each buffer is first converted to the linear format, 
then a rate conversion (if needed) is performed, then the buffer is converted to the 
target format.

The procedure to perform a conversion is as follows:

	1.  Create the format-specific conversion structure.
	2.  Open the source file.
	3.  Create the target file.  Write a file header if required.
	4.  Read a buffer of data from the source file.  For each buffer:
		- Convert to Linear
		- Convert the rate, is required
		- Convert to target format
		- Write to target file
	5.  Close both files.
	6.  'Destroy' (de-allocate) the conversion structure.

FUNCTIONS
The Conversion Library functions belong to four groups:

	Create Structure Functions
	Rate Conversion Functions
	Encoding Method Conversion Functions
	Clean-Up Functions


Create Structure Functions
--------------------------
These functions create a format-specific conversion structure:

    CVC_PCMCreate()	    Used for u-Law PCM, A-Law PCM
    CVC_Rhet32Create()	    Used for Rhetorex 32K ADPCM
    CVC_Rhet24Create()	    Used for Rhetorex 24K ADPCM
    CVC_WaveCreate()	    Used for Wave 8-bit, Wave 16-bit
    CVC_ConvertCreate()     Used for sampling rate conversions

    Arguments:		    None
    Return Value:	    Returns a pointer to the structure

    Syntax Example:	    #define	    CVT_MONO08	    0
			    int 	    inputType;

			    inputTypeCb = CVC_WaveCreate(CVT_MONO8);


Encoding Method Conversion Functions
------------------------------------
Each of these functions converts between one of the supported encoding methods 
and a general format called Linear.

    Converting to Linear from Source Format
    CVC_ExpandULAW ()	    Used for u-Law PCM
    CVC_ExpandALAW ()	    Used for A-Law PCM
    CVC_ExpandRhet32 ()     Used for Rhetorex 32K ADPCM
    CVC_ExpandRhet24 ()     Used for Rhetorex 24K ADPCM
    CVC_Wave16toLin ()	    Used for Wave 16-bit
    CVC_Wave8toLin ()	    Used for Wave 8-bit

    Converting from Linear to Target Format
    CVC_CompressULAW ()     Used for u-Law PCM
    CVC_CompressALAW ()     Used for A-Law PCM
    CVC_CompressRhet32 ()   Used for Rhetorex 32K ADPCM
    CVC_CompressRhet24 ()   Used for Rhetorex 24K ADPCM
    CVC_LintoWave16 ()	    Used for Wave 16-bit
    CVC_LintoWave8 ()	    Used for Wave 8-bit

    Arguments:
    int *ptr		    Pointer to structure (See Create Structure Functions)
    unsigned int *InpBufPtr Pointer to integer array of speech data (input buffer)
    unsigned int InpBufSize Length of input buffer
    unsigned int *InpUsed   Holds actual input buffer length used in conversion
    unsigned int *OutBufPtr Pointer to integer array of speech data (output buffer)
    unsigned int OutBufSize Length of output buffer
    unsigned int *OutBufLen Holds actual output buffer length used in conversion

    Return Value:	    None

    Syntax Example:	    int 	    inputBuffer[4096];
			    int 	    outputBuffer[4096];

			    void	    *inputTypeCb;
			    unsigned int    *inpBufPtr;
			    unsigned int    inpBufSize;
			    unsigned int    *inpUsed;
			    unsigned int    *outBufPtr;
			    unsigned int    outBufSize;
			    unsigned int    *outBufLen;

			    inpBufPtr  =  inputBuffer;
			    outBufPtr  =  outputBuffer;

			    CVC_Wave8toLin (inputTypeCb, inpBufPtr,
					   inpBufSize, inpUsed, outBufPtr,
					   outBufSize, outBufLen   );


Rate Conversion Functions
-------------------------
Each function converts a the sampling rate of a ‘chunk’ of Linear speech data.  
Supported rates are 8000, 11025, 22050, and 44100 samples per second.

    CVC_Convert08to11 ()    Convert from 8000 to 11025 samples per second
    CVC_Convert08to22 ()    Convert from 8000 to 22050 samples per second
    CVC_Convert08to44 ()    Convert from 8000 to 44100 samples per second
    CVC_Convert11to08 ()    Convert from 11025 to 8000 samples per second
    CVC_Convert11to22 ()    Convert from 11025 to 22050 samples per second
    CVC_Convert11to44()     Convert from 11025 to 44100 samples per second
    CVC_Convert22to08 ()    Convert from 22050 to 8000 samples per second
    CVC_Convert22to11 ()    Convert from 22050 to 11025 samples per second
    CVC_Convert22to44 ()    Convert from 22050 to 44100 samples per second
    CVC_Convert44to08 ()    Convert from 44100 to 8000 samples per second
    CVC_Convert44to11 ()    Convert from 44100 to 11025 samples per second
    CVC_Convert44to22 ()    Convert from 44100 to 22050 samples per second

    Arguments:
    int *ptr		    Pointer to structure (See Create Structure Functions)
    unsigned int *InpBufPtr Pointer to integer array of speech data (input buffer)
    unsigned int InpBufSize Length of input buffer
    unsigned int *InpUsed   Holds actual input buffer length used in conversion
    unsigned int *OutBufPtr Pointer to integer array of speech data (output buffer)
    unsigned int OutBufSize Length of output buffer
    unsigned int *OutBufLen Holds actual output buffer length used in conversion

    Return Value:	    None

    Syntax Example:	    int 	    inputBuffer[4096];
			    int 	    outputBuffer[4096];

			    void	    *inputTypeCb;
			    unsigned int    *inpBufPtr;
			    unsigned int    inpBufSize;
			    unsigned int    *inpUsed;
			    unsigned int    *outBufPtr;
			    unsigned int    outBufSize;
			    unsigned int    *outBufLen;

			    inpBufPtr  =  inputBuffer;
			    outBufPtr  =  outputBuffer;

			    CVC_Convert22to11 (convertRateCb, inpBufPtr,
					  inpBufSize, inpUsed, outBufPtr,
					  outBufSize, outBufLen   );
	

Clean-Up Functions
------------------
These functions are used to de-allocate the structures created by the Create Structure 
functions.

    CVC_PCMDestroy()	    Used for u-Law PCM, A-Law PCM
    CVC_Rhet32Destroy()     Used for Rhetorex 32K ADPCM
    CVC_Rhet24Destroy()     Used for Rhetorex 24K ADPCM
    CVC_WaveDestroy()	    Used for Wave 8-bit, Wave 16-bit
    CVC_ConvertDestroy()    Used for sampling rate conversions

    Arguments:
    int *ptr		    Pointer to structure (See Create Structure Functions)

    Return Value:	    None

    Syntax Example:	    CVC_WaveDestroy(inputTypeCb);



Example
-------
Converting from Wave 22k 8-bit to Wave 11k 16-bit format:

/* constants & data definition  .......... */

#define 		INPBUFLEN 	4096
#define 		OUTBUFLEN 	4096

#define		CVT_MONO08	0
#define		CVT_MONO16	1

/* these types are pre-defined in WAVE.h & RATECONV.H */
typedef enum tagCVD_WAVETYPE
{
	CVT_MONO08, CVT_MONO16
} CVD_WAVETYPE;

typedef enum tagCVD_CONVERSIONTYPE
{
	CVT_CONV08TO11, CVT_CONV08TO22, CVT_CONV08TO44, CVT_CONV11TO08,
	CVT_CONV11TO22, CVT_CONV11TO44, CVT_CONV22TO08, CVT_CONV22TO11,
	CVT_CONV22TO44, CVT_CONV44TO08, CVT_CONV44TO11, CVT_CONV44TO22, 
	CVT_CONV01TO01
} CVD_CONVERSIONTYPE;

int 		inputBuffer[INPBUFLEN];
int 		outputBuffer[OUTBUFLEN];
unsigned int	maxInpSize;

int 		inputType;
int		inputSampleRate;
void		*inputTypeCb;
int		outputType;
int		outputSampleRate;
void		*outputTypeCb;
void		*convertRateCb;
unsigned int	linInpRatio;
unsigned int	rateType;
unsigned int	overWrite;
unsigned int	maxInpSize;
unsigned int	*inpBufPtr;
unsigned int	inpBufSize;
unsigned int	*inpUsed ;
unsigned int	*outBufPtr;
unsigned int	outBufSize;
unsigned int	*outBufLen;

/* sample code flow   .......... */

inputSampleRate = 22;
linInpRatio = 2;
outputSampleRate = 11;
rateType = CVT_CONV22TO11;

inputTypeCb = CVC_WaveCreate(CVT_MONO8);	/* create the necessary structure */
outputTypeCb  = CVC_WaveCreate(CVT_MONO16);
convertRateCb  = CVC_ConvertCreate(rateType);

/* calculate the maximun input/output size */
maxInpSize = min( INPBUFLEN_/ linInpRatio,
	(unsigned int) floor ((double)INPBUFLEN_/ outputSampleRate * inputSampleRate));

while ( more data to convert )
{

/* 	:
	:
	fill the InputBuffer array with the source data up to maxInpSize
	:
*/

inpBufPtr  =  inputBuffer;	/* set the pointer to the buffer */
outBufPtr  =  outputBuffer;

CVC_Wave8toLin (inputTypeCb,	/* convert to LIN */
		inpBufPtr,
	inpBufSize,
	inpUsed,
		outBufPtr,
		outBufSize,
		outBufLen   ); 
	
	inpBufPtr	   = outputBuffer;	/* swap the buffer: input <-> output */
	outBufPtr	   = inputBuffer;
	inpBufSize =  *outBufLen;

CVC_Convert22to11 (convertRateCb,	/* convert the rate */
	inpBufPtr,
	inpBufSize,
	inpUsed,
	outBufPtr,
	outBufSize,
	outBufLen );

	inpBufPtr   = inputBuffer;	/* again, swap the buffer: input <-> output */
	outBufPtr   = outputBuffer;
	inpBufSize  = *outBufLen;

CVC_LintoWave16   (outputTypeCb, 	/* convert from LIN to desired format */
	inpBufPtr,
	inpBufSize,
	inpUsed,
	outBufPtr,
	outBufSize,
	outBufLen   );

/* 	:
	:
	write  the OutputBuffer array to destination upto outBufLen
	:
*/
} /* more data */

CVC_WaveDestroy(inputTypeCb);	/* destroy the structures used in the conversion process */
CVC_WaveDestroy (outputTypeCb);
CVC_ConvertDestroy (convertRateCb);


Conversion Library for DOS and Windows, Release 0.1 BETA Release Notes, 5/12/95	9
