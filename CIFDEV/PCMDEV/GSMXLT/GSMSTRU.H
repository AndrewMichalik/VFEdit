/*
 * Copyright 1992 by Jutta Degener and Carsten Bormann, Technische
 * Universitaet Berlin.  See the accompanying file "COPYRIGHT" for
 * details.  THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.
 */

/*$Header: /home/kbs/jutta/src/gsm/gsm-1.0/inc/RCS/private.h,v 1.2 1993/01/29 18:25:27 jutta Exp $*/

#ifndef GSMSTRU_H
#define GSMSTRU_H

typedef short                   word;           /* 16 bit signed int    */
/* JMS:  int was typedef'ed here */
typedef long                    longword;       /* 32 bit signed int    */

typedef unsigned short          uword;          /* unsigned word        */
/* JMS:  unsigned int was typedef'ed here */
typedef unsigned long            ulongword;      /* unsigned longword    */

struct gsm_state {

        word            dp0[ 280 ];

        word            z1;             /* preprocessing.c, Offset_com. */
        longword        L_z2;           /*                  Offset_com. */
        long            mp;             /*                  Preemphasis */

        word            u[8];           /* short_term_aly_filter.c      */
        word            LARpp[2][8];    /*                              */
        word            j;              /*                              */

        word            nrp; /* 40 */   /* long_term.c, synthesis       */
        word            v[9];           /* short_term.c, synthesis      */
        word            msr;            /* decoder.c,   Postprocessing  */

        char            verbose;        /* only used if !NDEBUG         */
        char            fast;           /* only used if FAST            */
	word		ecode[50];	/* JMS -- code.c -- init. to 0  */
};

#endif  /* PRIVATE_H */
