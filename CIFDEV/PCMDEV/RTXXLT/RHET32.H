/*���������������������������������������������������������������������ͻ*/
/*�����������������������������������������������������������������������*/
/*��                                                                   ��*/
/*��                        RHET32.h                                   ��*/
/*��                                                                   ��*/
/*�����������������������������������������������������������������������*/
/*���������������������������������������������������������������������ͼ*/
    
    #ifndef _CV_RHET32_H_INCLUDED
    #define _CV_RHET32_H_INCLUDED
    
/*���������������������������������������������������������������������Ŀ*/
/*�                 Structure for Compress32/Expand32                   �*/
/*�����������������������������������������������������������������������*/

typedef enum tagCVD_R32TYPE
{
    CVT_RHET32_CMP, CVT_RHET32_EXP
} CVD_R32TYPE;

typedef int CVD_RHET32_CB;
    
/*���������������������������������������������������������������������Ŀ*/
/*�                     Function Prototypes                             �*/
/*�����������������������������������������������������������������������*/

        /*������������������Ŀ*/
        /*� Create Function  �*/
        /*��������������������*/
extern  CVD_RHET32_CB*     CVC_Rhet32Create(CVD_R32TYPE r32t)           ;

        /*������������������Ŀ*/
        /*� Destroy Function �*/
        /*��������������������*/
extern  void    CVC_Rhet32Destroy(CVD_RHET32_CB *R32StrucPtr)           ;

        /*���������������������������Ŀ*/
        /*� Compress/Expand Functions �*/
        /*�����������������������������*/
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
    