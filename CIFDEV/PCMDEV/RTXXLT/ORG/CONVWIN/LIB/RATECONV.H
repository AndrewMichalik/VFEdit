/*���������������������������������������������������������������������ͻ*/
/*�����������������������������������������������������������������������*/
/*��                                                                   ��*/
/*��                        RATECONV.h                                 ��*/
/*��                                                                   ��*/
/*�����������������������������������������������������������������������*/
/*���������������������������������������������������������������������ͼ*/
    
    #ifndef _CV_RATECONV_H_INCLUDED
    #define _CV_RATECONV_H_INCLUDED
    
/*���������������������������������������������������������������������Ŀ*/
/*�                         Definitions                                 �*/
/*�����������������������������������������������������������������������*/
        
    
    typedef enum tagCVD_CONVERSIONTYPE
    {
        CVT_CONV08TO11, CVT_CONV08TO22, CVT_CONV08TO44, CVT_CONV11TO08,
        CVT_CONV11TO22, CVT_CONV11TO44, CVT_CONV22TO08, CVT_CONV22TO11,
        CVT_CONV22TO44, CVT_CONV44TO08, CVT_CONV44TO11, CVT_CONV44TO22, 
        CVT_CONV01TO01
    } CVD_CONVERSIONTYPE;
    
/*���������������������������������������������������������������������Ŀ*/
/*�             Structure  for CONVERSION                               �*/
/*�����������������������������������������������������������������������*/
    typedef int   CVD_CONVERT_CB;                                                                                                          

/*���������������������������������������������������������������������Ŀ*/
/*�    Function Prototypes                                              �*/
/*�����������������������������������������������������������������������*/

        /*�������������������Ŀ*/
        /*� Create Function   �*/
        /*���������������������*/
extern  CVD_CONVERT_CB*     CVC_ConvertCreate(CVD_CONVERSIONTYPE ct);

        /*�������������������Ŀ*/
        /*� Destroy Function  �*/
        /*���������������������*/
extern  void    CVC_ConvertDestroy(CVD_CONVERT_CB *ConvertStrucPtr);    

        /*���������������������������Ŀ*/
        /*� Convert Functions         �*/
        /*�����������������������������*/
extern  int     CVC_Convert08to11(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_Convert08to22(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_Convert08to44(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_Convert11to08(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_Convert11to22(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_Convert11to44(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
                                    
                                    
extern  int     CVC_Convert22to08(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_Convert22to11(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_Convert22to44(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
                                    
extern  int     CVC_Convert44to08(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );

extern  int     CVC_Convert44to11(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );

extern  int     CVC_Convert44to22(      CVD_CONVERT_CB   *ConvertStrucPtr,
                                        unsigned int      *InpBufPtr,
                                        unsigned int       InpBufSize,
                                        unsigned int      *InpUsed,
                                        unsigned int      *OutBufPtr,
                                        unsigned int       OutBufSize,
                                        unsigned int      *OutBufLen        );
    #endif  /* _CV_RATECONV_H_INCLUDED */
    