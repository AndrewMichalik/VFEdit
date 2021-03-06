/*浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*紺                                                                   虻*/
/*紺                        WAVE.h                                     虻*/
/*紺                                                                   虻*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/
    
    #ifndef _CV_WAVE_H_INCLUDED
    #define _CV_WAVE_H_INCLUDED
    
/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�                         Definitions                                 �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/

    typedef enum tagCVD_WAVETYPE
    {
        CVT_MONO08, CVT_MONO16
    } CVD_WAVETYPE;
/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�             Structure  for WAVE                                     �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
    typedef int CVD_WAVE_CB;                                                                                                          

/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�    Function Prototypes                                              �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/

        /*敖陳陳陳陳陳陳陳陳陳�*/
        /*� Create Function   �*/
        /*青陳陳陳陳陳陳陳陳陳�*/
extern  CVD_WAVE_CB*     CVC_WaveCreate(CVD_WAVETYPE wt);

        /*敖陳陳陳陳陳陳陳陳陳�*/
        /*� Destroy Function  �*/
        /*青陳陳陳陳陳陳陳陳陳�*/
extern  void    CVC_WaveDestroy(CVD_WAVE_CB *WaveStrucPtr);    

        /*敖陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
        /*� Wave Functions            �*/
        /*青陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
extern  int     CVC_Wave16toLin(        CVD_WAVE_CB      *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_LintoWave16(        CVD_WAVE_CB      *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                                           
extern  int     CVC_Wave8toLin(         CVD_WAVE_CB      *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_LintoWave8(         CVD_WAVE_CB      *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
    #endif  /* _CV_WAVE_H_INCLUDED */
    
