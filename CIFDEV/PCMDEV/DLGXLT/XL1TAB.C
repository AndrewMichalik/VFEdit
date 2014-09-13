/************************************************************************/
/* Dialogic ADPCM Conversion table computer: Xl1Tab.c   V1.3  07/15/91  */
/* Copyright (c) 1987-1991 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM conversion routine hdr   */
#include "xltsim.h"                     /* Translation simulator defs   */

#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <stdio.h>                      /* Standard I/O                 */

/************************************************************************/
/************************************************************************/
#define STPTABSIZ   49
#define DCFSMPCNT    1                  /* DC Filter multiplier >> 8    */

/************************************************************************/
/************************************************************************/
void main ()
{
    int i, j;
    extern short StpTab[];

    /********************************************************************/
    /********************************************************************/
    printf ("static WORD _based (_segname (\"_CODE\")) StpTab[] = {\n");
    for (j=0; j<4; j++) {
        for (i=0; i<16; i++) {
            printf ("\t%5d,", StpTab [16*j + i]);
            if (i == 7) printf ("\n");
        }
        printf ("\n");
    }
    printf ("};\n\n");

    /********************************************************************/
    /********************************************************************/
    printf ("static short _based (_segname (\"_CODE\")) DltTab[] = {\n");
    for (j=0; j<STPTABSIZ; j++) {
        for (i=0; i<16; i++) {
            printf ("\t%5d,", DltTab (j, i));
            if (i == 7) printf ("\n");
        }
        printf ("\n");
    }
    printf ("};\n\n");

    /********************************************************************/
    /********************************************************************/
    printf ("static WORD _based (_segname (\"_CODE\")) NxtStp[] = {\n");
    for (j=0; j<STPTABSIZ; j++) {
        for (i=0; i<16; i++) {
            printf ("\t%5d,", NxtStp (j, i) << 5);
            if (i == 7) printf ("\n");
        }
        printf ("\n");
    }
    printf ("};\n\n");

    /********************************************************************/
    /********************************************************************/
    printf ("static BYTE _based (_segname (\"_CODE\")) SmTab1[] = {\n");
    for (j=0; j<16; j++) {
        for (i=0; i<16; i++) {
            printf ("\t%2d,", j << 1);
            if (i == 7) printf ("\n");
        }
        printf ("\n");
    }
    printf ("};\n\n");

    /********************************************************************/
    /********************************************************************/
    printf ("static BYTE _based (_segname (\"_CODE\")) SmTab2[] = {\n");
    for (j=0; j<16; j++) {
        for (i=0; i<16; i++) {
            printf ("\t%2d,", i << 1);
            if (i == 7) printf ("\n");
        }
        printf ("\n");
    }
    printf ("};\n\n");

    /********************************************************************/
    /* short to signed, shifted nibble table                            */
    /********************************************************************/
    printf ("static BYTE _based (_segname (\"_CODE\")) SToSsn[] = {\n");
    for (j=0; j<16; j++) {
        for (i=0; i<16; i++) {
            if ((16*j + i) <= 0x7f) {               /* Positive byte    */
                if ((16*j + i) <= 0x07) printf ("\t0x%1x,", i << 1);
                else printf ("\t0x0e,");            /* Max pos shifted  */
            }
            else {                                  /* Negative byte    */
                if (((16*j + i) & 0x7f) == 0) printf ("\t0x10,");
                else {
                    if ((((16*j + i) & 0x7f) | 0xff80) >= -7)
                        printf ("\t0x%2x,", (0x08 | (-i & 0x7)) << 1);
                    else printf ("\t0x1e,");        /* Max neg shifted  */
                }    
            }
            if (i == 7) printf ("\n");
        }
        printf ("\n");
    }
    printf ("};\n\n");

    /********************************************************************/
    /* Adaptive DC Filter table:                                        */
    /*      Max signal delta = 1.875 * stepsize                         */
    /*      No distortion divisor = 10 * Max delta (worst case 10 samp) */
    /*                            = 18.75 * stepsize                    */
    /* Warning! divisor > 32K-1 will give IDIV overflow error!          */
    /********************************************************************/
    printf ("static WORD _based (_segname (\"_CODE\")) DCFDiv[] = {\n");
    for (j=0; j<STPTABSIZ; j++) {
        for (i=0; i<16; i++) {
            printf ("\t%5d,", (short) (DCFSMPCNT * StpTab [j]));
            if (i == 7) printf ("\n");
        }
        printf ("\n");
    }
    printf ("};\n\n");

    /********************************************************************/
    /********************************************************************/
    exit (0);

}

