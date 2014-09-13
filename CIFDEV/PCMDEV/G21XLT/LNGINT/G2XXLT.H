typedef long INT;
typedef long SHORT;

static  INT quan (INT val, SHORT *table, INT size);
static  INT fmult (INT an, INT srn);

extern  void g72x_init_state (struct g72x_state far *state_ptr);
extern  INT predictor_zero (struct g72x_state far *state_ptr);
extern  INT predictor_pole (struct g72x_state far *state_ptr);
extern  INT step_size (struct g72x_state far *state_ptr);
extern  INT quantize (INT d,INT y,SHORT *table,INT size);
extern  INT reconstruct (INT sign,INT dqln,INT y);
extern  void update (INT code_size, INT y, long wi, INT fi, INT dq, INT sr, INT dqsez, struct g72x_state far *state_ptr);
extern  INT tandem_adjust_alaw (INT sr, INT se, INT y, INT i, INT sign, SHORT *qtab);
extern  INT tandem_adjust_ulaw (INT sr, INT se, INT y, INT i, INT sign, SHORT *qtab);

