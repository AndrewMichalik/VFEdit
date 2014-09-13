/*ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*º°                                                                   °º*/
/*º°                            PCM.h                                  °º*/
/*º°                                                                   °º*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼*/

    #ifndef _CV_PCM_H_INCLUDED
    #define _CV_PCM_H_INCLUDED
    
    
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³             Structure for PCM ALAW/ULAW Compress/Expand             ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

    typedef int CVD_PCM_CB; 

    typedef enum tagCVD_PCMTYPE
    {
        CVT_ULAW_CMP, CVT_ULAW_EXP, CVT_ALAW_CMP, CVT_ALAW_EXP
    } CVD_PCMTYPE;

/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³    Function Prototypes                                              ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
    /*³ Create Functions ³*/
    /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  CVD_PCM_CB     *CVC_PCMCreate(CVD_PCMTYPE pt)                   ;
            
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
    /*³ Destroy Function ³*/
    /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  void        CVC_PCMDestroy(CVD_PCM_CB *PCMStrucPtr)             ;

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
    /*³ Compress/Expand Functions ³*/
    /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern    int   CVC_CompressULAW(    CVD_PCM_CB       *PCMStrucPtr,
                                     unsigned int     *InpBufPtr,
                                     unsigned int      InpBufSize,
                                     unsigned int     *InpUsed,
                                     unsigned int     *OutBufPtr,
                                     unsigned int      OutBufSize,
                                     unsigned int     *OutBufLen    )   ;
    
extern    int   CVC_ExpandULAW  (    CVD_PCM_CB       *PCMStrucPtr,
                                     unsigned int     *InpBufPtr,
                                     unsigned int      InpBufSize,
                                     unsigned int     *InpUsed,
                                     unsigned int     *OutBufPtr,
                                     unsigned int      OutBufSize,
                                     unsigned int     *OutBufLen    )   ;
    
extern    int   CVC_CompressALAW(    CVD_PCM_CB       *PCMStrucPtr,
                                     unsigned int     *InpBufPtr,
                                     unsigned int      InpBufSize,
                                     unsigned int     *InpUsed,
                                     unsigned int     *OutBufPtr,
                                     unsigned int      OutBufSize,
                                     unsigned int     *OutBufLen    )   ;
    
extern    int   CVC_ExpandALAW  (    CVD_PCM_CB       *PCMStrucPtr,
                                     unsigned int     *InpBufPtr,
                                     unsigned int      InpBufSize,
                                     unsigned int     *InpUsed,
                                     unsigned int     *OutBufPtr,
                                     unsigned int      OutBufSize,
                                     unsigned int     *OutBufLen    )   ;
    
    #endif /* _CV_PCM_H_INCLUDED */
