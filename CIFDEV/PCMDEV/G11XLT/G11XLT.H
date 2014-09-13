/************************************************************************/
/*              u-law, A-law and linear PCM conversions.                */
/************************************************************************/
#define SIGN_BIT        (0x80)          /* Sign bit for a A-law byte. */
#define QUANT_MASK      (0xf)           /* Quantization field mask. */
#define NSEGS           (8)             /* Number of A-law segments. */
#define SEG_SHIFT       (4)             /* Left shift for segment number. */
#define SEG_MASK        (0x70)          /* Segment field mask. */
  
/************************************************************************/
/************************************************************************/
static short seg_end[8] = {0x0FF, 0x01FF, 0x03FF, 0x07FF,
                           0xFFF, 0x1FFF, 0x3FFF, 0x7FFF};


