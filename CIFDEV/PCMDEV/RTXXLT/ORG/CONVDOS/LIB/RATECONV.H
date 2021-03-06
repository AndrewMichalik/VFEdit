/*浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*紺                                                                   虻*/
/*紺                        RATECONV.h                                 虻*/
/*紺                                                                   虻*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/
    
    #ifndef _CV_RATECONV_H_INCLUDED
    #define _CV_RATECONV_H_INCLUDED
    
/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�                         Definitions                                 �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
        
    
    typedef enum tagCVD_CONVERSIONTYPE
    {
        CVT_CONV08TO11, CVT_CONV08TO22, CVT_CONV08TO44, CVT_CONV11TO08,
        CVT_CONV11TO22, CVT_CONV11TO44, CVT_CONV22TO08, CVT_CONV22TO11,
        CVT_CONV22TO44, CVT_CONV44TO08, CVT_CONV44TO11, CVT_CONV44TO22, 
        CVT_CONV01TO01
    } CVD_CONVERSIONTYPE;
    
/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�             Structure  for CONVERSION                               �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
    typedef int   CVD_CONVERT_CB;                                                                                                          

/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�    Function Prototypes                                              �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/

        /*敖陳陳陳陳陳陳陳陳陳�*/
        /*� Create Function   �*/
        /*青陳陳陳陳陳陳陳陳陳�*/
extern  CVD_CONVERT_CB*     CVC_ConvertCreate(CVD_CONVERSIONTYPE ct);

        /*敖陳陳陳陳陳陳陳陳陳�*/
        /*� Destroy Function  �*/
        /*青陳陳陳陳陳陳陳陳陳�*/
extern  void    CVC_ConvertDestroy(CVD_CONVERT_CB *ConvertStrucPtr);    

        /*敖陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
        /*� Convert Functions         �*/
        /*青陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
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
    
