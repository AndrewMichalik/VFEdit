/************************************************************************/
/* CCITT G.72x Header: G2XXlt.g                         V2.00  04/15/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Convert sone int's and short's to long to maintain internal          */
/* calculation precision                                                */
/************************************************************************/
typedef long    INT;
typedef long    SHORT;

/************************************************************************/
/************************************************************************/
static  int     quan (INT val, short *table, int size);
static  int     fmult (int an, int srn);

/************************************************************************/
/************************************************************************/
extern  void    g72x_init_state (struct g72x_state far *state_ptr);
extern  int     predictor_zero (struct g72x_state far *state_ptr);
extern  int     predictor_pole (struct g72x_state far *state_ptr);
extern  int     step_size (struct g72x_state far *state_ptr);
extern  int     quantize (int d, int y, short *table, int size);
extern  int     reconstruct (int sign, int dqln, int y);
extern  void    update (int code_size, int y, INT wi, int fi, int dq, INT sr, int dqsez, struct g72x_state far *state_ptr);
extern  int     tandem_adjust_alaw (int sr, int se, int y, int i, int sign, short *qtab);
extern  int     tandem_adjust_ulaw (int sr, int se, int y, int i, int sign, short *qtab);

