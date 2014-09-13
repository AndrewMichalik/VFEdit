/*���������������������������������������������������������������������ͻ*/
/*�����������������������������������������������������������������������*/
/*��                                                                   ��*/
/*��                        WAVE.h                                     ��*/
/*��                                                                   ��*/
/*�����������������������������������������������������������������������*/
/*���������������������������������������������������������������������ͼ*/
    
    #ifndef _CV_WAVE_H_INCLUDED
    #define _CV_WAVE_H_INCLUDED
    
/*���������������������������������������������������������������������Ŀ*/
/*�                         Definitions                                 �*/
/*�����������������������������������������������������������������������*/

    typedef enum tagCVD_WAVETYPE
    {
        CVT_MONO08, CVT_MONO16
    } CVD_WAVETYPE;
/*���������������������������������������������������������������������Ŀ*/
/*�             Structure  for WAVE                                     �*/
/*�����������������������������������������������������������������������*/
    typedef int CVD_WAVE_CB;                                                                                                          

/*���������������������������������������������������������������������Ŀ*/
/*�    Function Prototypes                                              �*/
/*�����������������������������������������������������������������������*/

        /*�������������������Ŀ*/
        /*� Create Function   �*/
        /*���������������������*/
extern  CVD_WAVE_CB*     CVC_WaveCreate(CVD_WAVETYPE wt);

        /*�������������������Ŀ*/
        /*� Destroy Function  �*/
        /*���������������������*/
extern  void    CVC_WaveDestroy(CVD_WAVE_CB *WaveStrucPtr);    

        /*���������������������������Ŀ*/
        /*� Wave Functions            �*/
        /*�����������������������������*/
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
    