/*ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*º°                                                                   °º*/
/*º°                        RATECONV.h                                 °º*/
/*º°                                                                   °º*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼*/
    
    #ifndef _CV_RATECONV_H_INCLUDED
    #define _CV_RATECONV_H_INCLUDED
    
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³                         Definitions                                 ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        
    
    typedef enum tagCVD_CONVERSIONTYPE
    {
        CVT_CONV08TO11, CVT_CONV08TO22, CVT_CONV08TO44, CVT_CONV11TO08,
        CVT_CONV11TO22, CVT_CONV11TO44, CVT_CONV22TO08, CVT_CONV22TO11,
        CVT_CONV22TO44, CVT_CONV44TO08, CVT_CONV44TO11, CVT_CONV44TO22, 
        CVT_CONV01TO01
    } CVD_CONVERSIONTYPE;
    
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³             Structure  for CONVERSION                               ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    typedef int   CVD_CONVERT_CB;                                                                                                          

/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³    Function Prototypes                                              ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Create Function   ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  CVD_CONVERT_CB*     CVC_ConvertCreate(CVD_CONVERSIONTYPE ct);

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Destroy Function  ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  void    CVC_ConvertDestroy(CVD_CONVERT_CB *ConvertStrucPtr);    

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Convert Functions         ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
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
    
