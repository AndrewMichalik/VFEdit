/*浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*紺                                                                   虻*/
/*紺                        RHET24.h                                   虻*/
/*紺                                                                   虻*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/
    
    #ifndef _CV_RHET24_H_INCLUDED
    #define _CV_RHET24_H_INCLUDED
    
/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�                 Structure for Compress24/Expand24                   �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/

typedef enum tagCVD_R24TYPE
{
    CVT_RHET24_CMP, CVT_RHET24_EXP
} CVD_R24TYPE;

typedef int CVD_RHET24_CB;
    
/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�                     Function Prototypes                             �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/

        /*敖陳陳陳陳陳陳陳陳朕*/
        /*� Create Function  �*/
        /*青陳陳陳陳陳陳陳陳潰*/
extern  CVD_RHET24_CB*     CVC_Rhet24Create(CVD_R24TYPE r24t)           ;

        /*敖陳陳陳陳陳陳陳陳朕*/
        /*� Destroy Function �*/
        /*青陳陳陳陳陳陳陳陳潰*/
extern  void    CVC_Rhet24Destroy(CVD_RHET24_CB *R24StrucPtr)           ;

        /*敖陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
        /*� Compress/Expand Functions �*/
        /*青陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
extern  int     CVC_CompressRhet24( CVD_RHET24_CB     *R24StrucPtr,
                                    unsigned int      *InpBufPtr,
                                    unsigned int       InpBufSize,
                                    unsigned int      *InpUsed,
                                    unsigned int      *OutBufPtr,
                                    unsigned int       OutBufSize,
                                    unsigned int      *OutBufLen   )    ;
extern  int     CVC_ExpandRhet24(   CVD_RHET24_CB     *R24StrucPtr,
                                    unsigned int      *InpBufPtr,
                                    unsigned int       InpBufSize,
                                    unsigned int      *InpUsed,
                                    unsigned int      *OutBufPtr,
                                    unsigned int       OutBufSize,
                                    unsigned int      *OutBufLen   )    ;

    #endif  /* _CV_RHET24_H_INCLUDED */
    