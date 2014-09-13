/*ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*º°                                                                   °º*/
/*º°                        WAVE.h                                     °º*/
/*º°                                                                   °º*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼*/
    
    #ifndef _CV_WAVE_H_INCLUDED
    #define _CV_WAVE_H_INCLUDED
    
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³                         Definitions                                 ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

    typedef enum tagCVD_WAVETYPE
    {
        CVT_MONO08, CVT_MONO16
    } CVD_WAVETYPE;
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³             Structure  for WAVE                                     ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    typedef int CVD_WAVE_CB;                                                                                                          

/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³    Function Prototypes                                              ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Create Function   ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  CVD_WAVE_CB*     CVC_WaveCreate(CVD_WAVETYPE wt);

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Destroy Function  ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  void    CVC_WaveDestroy(CVD_WAVE_CB *WaveStrucPtr);    

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Wave Functions            ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
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
    
