/************************************************************************/
/* VoxFnt User Registration Definitions: VxFReg.h       V2.00  12/20/92 */
/* Copyright (c) 1989-1993 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                  Demo Registration Definitions                       */
/************************************************************************/
#define REGDEMKEY   0                   /* Demo version key detected    */
#define REGEVLKEY   1                   /* Eval version key detected    */
#define REGFULKEY   2                   /* Full version key detected    */
#define REGMASKEY   3                   /* Mstr version key detected    */

/************************************************************************/
/* (36**4-1 = 1,679,616) Prime numbers above 1000:                      */
/*                                                                      */
/* 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319     */
/* 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429     */
/* 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489     */ 
/* 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571     */
/************************************************************************/

/************************************************************************/
/* Reg Key = strrev (BASE36 (App Key || Usr Key))                       */
/* Seq#: 1301 x 11 || xxxx = swap (j1b0 || xxxx)                        */ 
/* Eval: 1321 x 11 || xxxx = swap (n7b0 || xxxx)                        */ 
/* Full: 1373 x 11 || xxxx = swap (jnb0 || xxxx)                        */ 
/* Mstr: 1423 x 11 || xxxx = swap (t2c0 || xxxx)                        */ 
/* Mstr: 1423 x 99 || xxxx = swap (9p03 || xxxx)                        */ 
/************************************************************************/
#define KEYSEQAPP  "00001301"           /* Seq# version Appl key        */
#define KEYEVLAPP  "00001321"           /* Eval version Appl key        */
#define KEYFULAPP  "00001373"           /* Full version Appl key        */
#define KEYMASAPP  "00001423"           /* Mstr version Appl key        */

/************************************************************************/
/*                  Demo Registration Functions                         */
/************************************************************************/
#define         ChkRegKey CRK           /* Reduce for library exposure  */
static  WORD    ChkRegKey (char far *, char far *, WORD FAR *);
#define         GetEncKey CEK           /* Reduce for library exposure  */
static  WORD    GetEncKey (char far *, WORD, WORD FAR *);

/************************************************************************/
/*                  Hardware Key Access Functions                       */
/************************************************************************/
#define IDR_CODE        101                 // User Defined Resource Type
#define AZ_KECHK        1000                // User Defined Resource Id

typedef struct tagSCB
{
   short            return_code;
   short            return_status;
   short            return_function;
   char             function_code;
   char             id[5];
   char             product_name[9];
   char             fillerA;
   char             fillerB;
   char             fillerC;
   unsigned long    product_serial;
   unsigned long    pin_number;
   short            exec_limit;
   short            exp_days_limit;
   char             expire_date[9];
   unsigned char    user_data[16];
   unsigned char    lasered_id[6];
} SCB;

extern short far pascal KECHK (SCB FAR *);
