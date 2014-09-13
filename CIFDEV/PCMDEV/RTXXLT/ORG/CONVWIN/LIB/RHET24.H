/*ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*º°                                                                   °º*/
/*º°                        RHET24.h                                   °º*/
/*º°                                                                   °º*/
/*º°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°º*/
/*ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼*/
    
    #ifndef _CV_RHET24_H_INCLUDED
    #define _CV_RHET24_H_INCLUDED
    
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³                 Structure for Compress24/Expand24                   ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

typedef enum tagCVD_R24TYPE
{
    CVT_RHET24_CMP, CVT_RHET24_EXP
} CVD_R24TYPE;

typedef int CVD_RHET24_CB;
    
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³                     Function Prototypes                             ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Create Function  ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  CVD_RHET24_CB*     CVC_Rhet24Create(CVD_R24TYPE r24t)           ;

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Destroy Function ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
extern  void    CVC_Rhet24Destroy(CVD_RHET24_CB *R24StrucPtr)           ;

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
        /*³ Compress/Expand Functions ³*/
        /*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
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
    