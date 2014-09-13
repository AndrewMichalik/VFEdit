/*���������������������������������������������������������������������ͻ*/
/*�����������������������������������������������������������������������*/
/*��                                                                   ��*/
/*��                            PCM.h                                  ��*/
/*��                                                                   ��*/
/*�����������������������������������������������������������������������*/
/*���������������������������������������������������������������������ͼ*/

    #ifndef _CV_PCM_H_INCLUDED
    #define _CV_PCM_H_INCLUDED
    
    
/*���������������������������������������������������������������������Ŀ*/
/*�             Structure for PCM ALAW/ULAW Compress/Expand             �*/
/*�����������������������������������������������������������������������*/

    typedef int CVD_PCM_CB; 

    typedef enum tagCVD_PCMTYPE
    {
        CVT_ULAW_CMP, CVT_ULAW_EXP, CVT_ALAW_CMP, CVT_ALAW_EXP
    } CVD_PCMTYPE;

/*���������������������������������������������������������������������Ŀ*/
/*�    Function Prototypes                                              �*/
/*�����������������������������������������������������������������������*/
    /*������������������Ŀ*/
    /*� Create Functions �*/
    /*��������������������*/
extern  CVD_PCM_CB     *CVC_PCMCreate(CVD_PCMTYPE pt)                   ;
            
    /*������������������Ŀ*/
    /*� Destroy Function �*/
    /*��������������������*/
extern  void        CVC_PCMDestroy(CVD_PCM_CB *PCMStrucPtr)             ;

    /*���������������������������Ŀ*/
    /*� Compress/Expand Functions �*/
    /*�����������������������������*/
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