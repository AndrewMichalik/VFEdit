/*ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*º°                                                                   °º*/
/*º°                        RHET32.h                                   °º*/
/*º°                                                                   °º*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼*/
    
    #ifndef _CV_RHET32_H_INCLUDED
    #define _CV_RHET32_H_INCLUDED
    
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³                 Structure for Compress32/Expand32                   ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

typedef enum tagCVD_R32TYPE
{
    CVT_RHET32_CMP, CVT_RHET32_EXP
} CVD_R32TYPE;

typedef int CVD_RHET32_CB;
    
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³                     Function Prototypes                             ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Create Function  ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  CVD_RHET32_CB*     CVC_Rhet32Create(CVD_R32TYPE r32t)           ;

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Destroy Function ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  void    CVC_Rhet32Destroy(CVD_RHET32_CB *R32StrucPtr)           ;

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Compress/Expand Functions ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
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
    