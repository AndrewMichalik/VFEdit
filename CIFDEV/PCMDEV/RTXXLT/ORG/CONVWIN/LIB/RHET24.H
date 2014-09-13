/*���������������������������������������������������������������������ͻ*/
/*�����������������������������������������������������������������������*/
/*��                                                                   ��*/
/*��                        RHET24.h                                   ��*/
/*��                                                                   ��*/
/*�����������������������������������������������������������������������*/
/*���������������������������������������������������������������������ͼ*/
    
    #ifndef _CV_RHET24_H_INCLUDED
    #define _CV_RHET24_H_INCLUDED
    
/*���������������������������������������������������������������������Ŀ*/
/*�                 Structure for Compress24/Expand24                   �*/
/*�����������������������������������������������������������������������*/

typedef enum tagCVD_R24TYPE
{
    CVT_RHET24_CMP, CVT_RHET24_EXP
} CVD_R24TYPE;

typedef int CVD_RHET24_CB;
    
/*���������������������������������������������������������������������Ŀ*/
/*�                     Function Prototypes                             �*/
/*�����������������������������������������������������������������������*/

        /*������������������Ŀ*/
        /*� Create Function  �*/
        /*��������������������*/
extern  CVD_RHET24_CB*     CVC_Rhet24Create(CVD_R24TYPE r24t)           ;

        /*������������������Ŀ*/
        /*� Destroy Function �*/
        /*��������������������*/
extern  void    CVC_Rhet24Destroy(CVD_RHET24_CB *R24StrucPtr)           ;

        /*���������������������������Ŀ*/
        /*� Compress/Expand Functions �*/
        /*�����������������������������*/
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
    