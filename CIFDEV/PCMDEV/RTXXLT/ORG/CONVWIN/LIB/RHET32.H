/*浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*紺                                                                   虻*/
/*紺                        RHET32.h                                   虻*/
/*紺                                                                   虻*/
/*紺旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�*/
/*藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�*/
    
    #ifndef _CV_RHET32_H_INCLUDED
    #define _CV_RHET32_H_INCLUDED
    
/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�                 Structure for Compress32/Expand32                   �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/

typedef enum tagCVD_R32TYPE
{
    CVT_RHET32_CMP, CVT_RHET32_EXP
} CVD_R32TYPE;

typedef int CVD_RHET32_CB;
    
/*敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
/*�                     Function Prototypes                             �*/
/*青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�*/

        /*敖陳陳陳陳陳陳陳陳朕*/
        /*� Create Function  �*/
        /*青陳陳陳陳陳陳陳陳潰*/
extern  CVD_RHET32_CB*     CVC_Rhet32Create(CVD_R32TYPE r32t)           ;

        /*敖陳陳陳陳陳陳陳陳朕*/
        /*� Destroy Function �*/
        /*青陳陳陳陳陳陳陳陳潰*/
extern  void    CVC_Rhet32Destroy(CVD_RHET32_CB *R32StrucPtr)           ;

        /*敖陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
        /*� Compress/Expand Functions �*/
        /*青陳陳陳陳陳陳陳陳陳陳陳陳陳�*/
extern  int     CVC_CompressRhet32( CVD_RHET32_CB     *R32StrucPtr,
                                    unsigned int      *InpBufPtr,
                                    unsigned int       InpBufSize,
                                    unsigned int      *InpUsed,
                                    unsigned int      *OutBufPtr,
                                    unsigned int       OutBufSize,
                                    unsigned int      *OutBufLen   )    ;
extern  int     CVC_ExpandRhet32(   CVD_RHET32_CB     *R32StrucPtr,
                                    unsigned int      *InpBufPtr,
                                    unsigned int       InpBufSize,
                                    unsigned int      *InpUsed,
                                    unsigned int      *OutBufPtr,
                                    unsigned int       OutBufSize,
                                    unsigned int      *OutBufLen   )    ;

    #endif  /* _CV_RHET32_H_INCLUDED */
    