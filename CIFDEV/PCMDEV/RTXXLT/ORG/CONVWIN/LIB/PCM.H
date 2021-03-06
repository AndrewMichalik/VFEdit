/*浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*紺                                                                   虻*/
/*紺                            PCM.h                                  虻*/
/*紺                                                                   虻*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/

    #ifndef _CV_PCM_H_INCLUDED
    #define _CV_PCM_H_INCLUDED
    
    
/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�             Structure for PCM ALAW/ULAW Compress/Expand             �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/

    typedef int CVD_PCM_CB; 

    typedef enum tagCVD_PCMTYPE
    {
        CVT_ULAW_CMP, CVT_ULAW_EXP, CVT_ALAW_CMP, CVT_ALAW_EXP
    } CVD_PCMTYPE;

/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�    Function Prototypes                                              �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
    /*敖陳陳陳陳陳陳陳陳朕*/
    /*� Create Functions �*/
    /*青陳陳陳陳陳陳陳陳潰*/
extern  CVD_PCM_CB     *CVC_PCMCreate(CVD_PCMTYPE pt)                   ;
            
    /*敖陳陳陳陳陳陳陳陳朕*/
    /*� Destroy Function �*/
    /*青陳陳陳陳陳陳陳陳潰*/
extern  void        CVC_PCMDestroy(CVD_PCM_CB *PCMStrucPtr)             ;

    /*敖陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
    /*� Compress/Expand Functions �*/
    /*青陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
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
