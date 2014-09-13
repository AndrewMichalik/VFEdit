//ajm
#define WFAR far


/*
 * Copyright 1992 by Jutta Degener and Carsten Bormann, Technische
 * Universitaet Berlin.  See the accompanying file "COPYRIGHT" for
 * details.  THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.
 */

/*$Header: /home/kbs/jutta/src/gsm/gsm-1.0/inc/RCS/gsm.h,v 1.4 1993/01/29 20:07:38 jutta Exp $*/

#ifndef GSM_H
#define GSM_H

#define  NeedFunctionPrototypes  1

#ifdef __cplusplus
#       define  NeedFunctionPrototypes  1
#endif

#if __STDC__
#       define  NeedFunctionPrototypes  1
#endif

#ifdef _NO_PROTO
#       undef   NeedFunctionPrototypes
#endif

#undef  GSM_P   /* gnu stdio.h actually defines this...         */

#if NeedFunctionPrototypes
#       define  GSM_P( protos ) protos
#else
#       define  GSM_P( protos ) ( /* protos */ )
#endif

#ifdef NeedFunctionPrototypes
#   include     <stdio.h>               /* for FILE *   */
#endif

/* AUTO_SPARC_HACK added by John Walker.  If defined, USE_FLOAT_MUL   
   automatically set when compiling on a Sparc.  This lets most
   people avoid editing the Makefile. */

#ifdef AUTO_SPARC_HACK
#ifdef sparc
#define USE_FLOAT_MUL
#define FAST
#endif
#endif

/*
 *      Interface
 */

/* I kept the code structured so that clients never need to know the internals
*  of gsm_state.  However, VFEDIT prefers to so I reveal it here.  Otherwise
*  I would have kept gsm a private type. -- JMS
*/

/* JMS:  Added WFAR macros everywhere.  Please, please, forgive me,
*  Jutta!
*/
#include "gsmstru.h"					/* gsm_state */
typedef struct gsm_state WFAR *  gsm;			/* For GSM */
typedef short                   gsm_signal;             /* signed 16 bit */
typedef unsigned char           gsm_byte;
#define GSM_SAMPLE_BLOCK	160			/* Number of 16-bit samples / block */
#define GSM_CMP_BLOCK		33			/* Number of 8-bit quantities /cmp blk */
typedef gsm_byte                gsm_frame[GSM_CMP_BLOCK];          /* times 8 bits   */

#define GSM_MAGIC       0xD                             /* 13 kbit/s RPE-LTP */

#define GSM_PATCHLEVEL  2
#define GSM_MINOR       0
#define GSM_MAJOR       1

#define GSM_OPT_VERBOSE 1
#define GSM_OPT_FAST    2

extern gsm  gsm_create  GSM_P((void));
extern void gsm_destroy GSM_P((gsm));   
extern void gsm_init GSM_P((gsm));		/* JMS */

extern long gsm_option  GSM_P((gsm, long, long WFAR *));

extern void gsm_encode  GSM_P((gsm, gsm_signal WFAR *, gsm_byte  WFAR *));
extern long  gsm_decode  GSM_P((gsm, gsm_byte   WFAR *, gsm_signal WFAR *));

extern long  gsm_explode GSM_P((gsm, gsm_byte   WFAR *, gsm_signal WFAR *));
extern void gsm_implode GSM_P((gsm, gsm_signal WFAR *, gsm_byte   WFAR *));

#undef  GSM_P

#endif  /* GSM_H */
