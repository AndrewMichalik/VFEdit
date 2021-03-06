/*����������������������������������������������������������������������ͻ*/
/*������������������������������������������������������������������������*/
/*��                                                                    ��*/
/*��                         CONVERT.h                                  ��*/
/*��                                                                    ��*/
/*������������������������������������������������������������������������*/
/*����������������������������������������������������������������������ͼ*/

    #ifndef _CV_CONVERT_H_INCLUDED
    #define _CV_CONVERT_H_INCLUDED

/*���������������������������������������������������������������������Ŀ*/
/*�                     Definitions                                     �*/
/*�����������������������������������������������������������������������*/
#define CVM_SIZEFILENAME     80
#define INPBUFLEN          4096
#define OUTBUFLEN          4096


typedef struct tagCONVERT
{
    char            inputFilename[CVM_SIZEFILENAME];
    int             inputType                       ;
    int             inputSampleRate                 ;
    void           *inputTypeCb                    ;
    char            outputFilename[CVM_SIZEFILENAME];
    int             outputType                      ;
    int             outputSampleRate                ;
    void           *outputTypeCb                   ;
    void           *convertRateCb                  ;
    double			linInpRatio                     ;
    unsigned int    rateType                        ;
    unsigned int    overWrite                       ;
    unsigned int    maxInpSize                      ;
    unsigned int   *inpBufPtr                       ;
    unsigned int    inpBufSize                      ;
    unsigned int   *inpUsed                         ;
    unsigned int   *outBufPtr                       ;
    unsigned int    outBufSize                      ;
    unsigned int   *outBufLen                       ;  
} CONVERT;
    
             
/*���������������������������������������������������������������������Ŀ*/
/*�                     Function Prototypes                             �*/
/*�����������������������������������������������������������������������*/
extern void CheckFiles(CONVERT *cp);
extern CONVERT *ConvertCreate(unsigned int *inpBufferPtr, unsigned int *outBufferPtr);
extern void ConvertDestroy(CONVERT *cp);
extern void ConvertToLin(CONVERT *cp);           
extern void ConvertFromLin(CONVERT *cp);
extern void ConvertRate(CONVERT *cp);           
extern char *TypeStr(int it);

    #endif  /* _CV_CONVERT_H_INCLUDED */
