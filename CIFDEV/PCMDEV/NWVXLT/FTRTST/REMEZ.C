/************************************************************************/
/* Remez exchange FIR Filter Design                     V2.00  07/03/93 */
/* Copyright (c) 1987-1993 Andrew J. Michalik                           */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
  
#include <math.h>                       /* Math library defs            */

/************************************************************************/
/************************************************************************/
#define PI 3.14159265
#define TWO_PI  6.2831853
#define real    double

/**********************************/
/*                                */
/*   Listing 12.1                 */
/*                                */
/*   fsDesign()                   */
/*                                */
/**********************************/

int fsDesign(	int N, 
				int firType,
				real A[],
				real h[])
{
int n,k, status;
real x, M;

M = (N-1.0)/2.0;
status = 0;
switch (firType) {
	case 1:
		if(N%2) {
			for(n=0; n<N; n++) {
				h[n] = A[0];
				x = TWO_PI * (n-M)/N;
				for(k=1; k<=M; k++) {
					h[n] = h[n] + 2.0*A[k]*cos(x*k);
					}
				h[n] = h[n]/N;
				}
			}
		else 
			{status = 1;}
		break;
	/*---------------------------------------*/
	case 2:
		if(N%2)
			{status = 2;}
		else {
			for(n=0; n<N; n++) {
				h[n] = A[0];
				x = TWO_PI * (n-M)/N;
				for(k=1; k<=(N/2-1); k++) {
					h[n] = h[n] + 2.0*A[k]*cos(x*k);
					}
				h[n] = h[n]/N;
				}
			}
		break;
	/*---------------------------------------*/
	case 3:
		if(N%2) {
			for(n=0; n<N; n++) {
				h[n] = 0;
				x = TWO_PI * (M-n)/N;
				for(k=1; k<=M; k++) {
					h[n] = h[n] + 2.0*A[k]*sin(x*k);
					}
				h[n] = h[n]/N;
				}
			}
		else
			{status = 3;}
		break;
	/*---------------------------------------*/
	case 4:
		if(N%2)
			{status = 4;}
		else {
			for(n=0; n<N; n++) {
				h[n] = A[N/2]*sin(PI*(M-n));
				x = TWO_PI * (n-M)/N;
				for(k=1; k<=(N/2-1); k++) {
					h[n] = h[n] + 2.0*A[k]*sin(x*k);
					}
				h[n] = h[n]/N;
				}
			}
		break;
	}
return(status);
}

/**********************************/
/*                                */
/*   Lisitng 13.1                 */
/*                                */
/*   gridFreq()                   */
/*                                */
/**********************************/

real gridFreq(	real gridParam[],
				int gI)
{
real work;
static real incP, incS, freqP, freqS;
static int r, gridDensity, mP, mS, gP;

if(gridParam[0] == 1.0) {
	gridParam[0] = (real) 0.0;
	freqP = gridParam[1];
	freqS = gridParam[2];
	r = (int) gridParam[3];
	gridDensity = (int) gridParam[4];
	work = (real) (0.5 + freqP - freqS)/r;
	mP = (int) floor(0.5 + freqP/work);
	gridParam[5] = mP;
	gP = mP * gridDensity;
	gridParam[7] = gP;
	mS = r +1 - mP;
	gridParam[6] = mS;
	incP = freqP / gP;
	incS = (0.5-freqS) / ((mS-1) * gridDensity);
	}
else {
	work = (gI<=gP) ? (gI*incP) : (freqS+(gI-(gP+1))*incS);
	}
return(work);
}

/**********************************/
/*                                */
/*   Listing 13.2                 */
/*                                */
/*   desLpfResp()                 */
/*                                */
/**********************************/

real desLpfResp( real freqP, real freq)
{
real result;
result = 0.0;
if(freq <= freqP) result = 1.0;
return(result);
}


/**********************************/
/*                                */
/*   Listing 13.3                 */
/*                                */
/*   weightLp()                   */
/*                                */
/**********************************/

real weightLp( real kk, real freqP, real freq)
{
real result;

result = 1.0;
if(freq <= freqP) result = 1.0/kk;
return(result);
}

/**********************************/
/*                                */
/*   Listing 13.5                 */
/*                                */
/*   computeRemezA()              */
/*                                */
/**********************************/

real computeRemezA(	real gridParam[],
					int gridMax,
					int r,
					real kk,
					real freqP,
					int iFF[],
					int initFlag,
					real contFreq)
{
static int i, j, k, sign;
static real freq, denom, numer, alpha, delta;
static real absDelta, xCont, term;
static real x[50], beta[50], gamma[50];
real aa;

if(initFlag) {
	for(j=0; j<=r; j++) {
		freq = gridFreq(gridParam,iFF[j]);
		x[j] = cos(TWO_PI * freq);
		}
	
	/*  compute delta  */
	denom = 0.0;
	numer = 0.0;
	sign = -1;
	for( k=0; k<=r; k++) {
		sign = -sign;
		alpha = 1.0;
			for( i=0; i<=(r-1); i++) {
			if(i==k) continue;
			alpha = alpha / (x[k] - x[i]);
			}
		beta[k] = alpha;
		if( k != r ) alpha = alpha/(x[k] - x[r]);
		freq =  gridFreq(gridParam,iFF[k]);
		numer = numer + alpha * desLpfResp(freqP,freq);
		denom = denom + sign*(alpha/ 
							weightLp(kk, freqP, freq));
		}
	delta = numer/denom;
	absDelta = fabs(delta);
	
	sign = -1;
	for( k=0; k<=r-1; k++) {
		sign = -sign;
		freq = gridFreq(gridParam,iFF[k]);
		gamma[k] = desLpfResp(freqP, freq) - sign * delta / 
						weightLp(kk,freqP,freq);
		}
	
	}
else {
	xCont = cos(TWO_PI * contFreq);
	numer = 0.0;
	denom = 0.0;
	for( k=0; k<r; k++) {
		term = xCont - x[k];
		if(fabs(term)<1.0e-7) {
			aa = gamma[k];
			goto done;
			}
		else {
			term = beta[k]/(xCont - x[k]);
			denom += term;
			numer += gamma[k]*term;
			}
		}
	aa = numer/denom;
	}
done:
return(aa);
}
/**********************************/
/*                                */
/*   Listing 13.4                 */
/*                                */
/*   remezError()                 */
/*                                */
/**********************************/

void remezError(	real gridParam[],
					int gridMax,
					int r,
					real kk,
					real freqP,
					int iFF[],
					real ee[])
{
int j;
real freq,aa;

aa = computeRemezA(	gridParam, gridMax, r, kk, 
					freqP, iFF, 1, 0.0);

for( j=0; j<=gridMax; j++) {
	freq = gridFreq(gridParam,j);
	aa = computeRemezA(	gridParam, 
						gridMax, r, kk, freqP, 
						iFF, 0,freq);
	ee[j] = weightLp(kk,freqP,freq) * 
				(desLpfResp(freqP,freq) - aa);
	}
return;
}

/**********************************/
/*                                */
/*   Listing 13.6                 */
/*                                */
/*   remezSearch()                */
/*                                */
/**********************************/

void remezSearch(	real ee[],
					real absDelta,
					int gP,
					int iFF[],
					int gridMax,
					int r,
					real gridParam[])
{
int i,j,k,extras,indexOfSmallest;
real smallestVal;

k=0;

/* test for extremum at f=0  */
if(	( (ee[0]>0.0) && (ee[0]>ee[1]) && (fabs(ee[0])>=absDelta) ) ||
	( (ee[0]<0.0) && (ee[0]<ee[1]) && (fabs(ee[0])>=absDelta) ) ) { 
	iFF[k]=0;
	k++;
	}

/*  search for extrema in passband  */
for(j=1; j<gP; j++) {
	if( ( (ee[j]>=ee[j-1]) && (ee[j]>ee[j+1]) && (ee[j]>0.0) ) ||
		( (ee[j]<=ee[j-1]) && (ee[j]<ee[j+1]) && (ee[j]<0.0) )) {
		iFF[k] = j;
		k++;
		}
	}

/* pick up an extremal frequency at passband edge  */
	iFF[k]=gP;
	k++;

/* pick up an extremal frequency at stopband edge  */
j=gP+1;
	iFF[k]=j;
	k++;

/*  search for extrema in stopband  */
     
for(j=gP+2; j<gridMax; j++) {
	if( ( (ee[j]>=ee[j-1]) && (ee[j]>ee[j+1]) && (ee[j]>0.0) ) ||
		( (ee[j]<=ee[j-1]) && (ee[j]<ee[j+1]) && (ee[j]<0.0) )) {
		iFF[k] = j;
		k++;
		}
	}
/* test for extremum at f=0.5  */
j = gridMax;
if(	( (ee[j]>0.0) && (ee[j]>ee[j-1]) && (fabs(ee[j])>=absDelta) ) ||
	( (ee[j]<0.0) && (ee[j]<ee[j-1]) && (fabs(ee[j])>=absDelta) ) ) { 
	iFF[k]=gridMax;
	k++;
	}
/*----------------------------------------------------*/
/*  find and remove superfluous extremal frequencies  */
if( k>r+1) {
	extras = k - (r+1);
	for(i=1; i<=extras; i++) {
		smallestVal = fabs(ee[iFF[0]]);
		indexOfSmallest = 0;
		for(j=1; j< k; j++) {
			if(fabs(ee[iFF[j]]) >= smallestVal) continue;
			smallestVal = fabs(ee[iFF[j]]);
			indexOfSmallest = j;
			}
		k--;
		for(j=indexOfSmallest; j<k; j++) iFF[j] = iFF[j+1];
		}
	}
return;
}
/**********************************/
/*                                */
/*   Listing 13.7                 */
/*                                */
/*   remezStop()                  */
/*                                */
/**********************************/

int remezStop(	int iFF[],
				int r)
{
static int oldIFF[50];
int j,result;

result = 1;
for(j=0; j<=r; j++) {
	if(iFF[j] != oldIFF[j]) result = 0;
	oldIFF[j] = iFF[j];
	}
return(result);
}

/**********************************/
/*                                */
/*   Listing 13.8                 */
/*                                */
/*   remezStop2()                 */
/*                                */
/**********************************/

int remezStop2(	real ee[],
				int iFF[],
				int r)
{
real biggestVal, smallestVal,qq;
int j,result;

result = 0;
biggestVal = fabs(ee[iFF[0]]);
smallestVal = fabs(ee[iFF[0]]);
for(j=1; j<=r; j++) {
	if(fabs(ee[iFF[j]]) < smallestVal) smallestVal = fabs(ee[iFF[j]]);
	if(fabs(ee[iFF[j]]) > biggestVal) biggestVal = fabs(ee[iFF[j]]);
	}
qq = (biggestVal - smallestVal)/biggestVal;
if(qq<0.01) result=1;
return(result);
}

/**********************************/
/*                                */
/*   Listing 13.9                 */
/*                                */
/*   remezFinish()                */
/*                                */
/**********************************/

void remezFinish(	real extFreq[],
					int nn,
					int r,
					real freqP,
					real kk,
					real aa[],
					real h[])
{
int k, gridMax, iFF[1]; //ajm int k,n, gridMax, iFF[1];
real freq; //ajm real freq,sum;
static real gridParam[1];

for(k=0; k<r; k++) {
	freq = (real) k/ (real) nn;
	aa[k] = computeRemezA(	gridParam, gridMax, r, kk, 
							freqP, iFF, 0,freq);
	}
fsDesign( nn, 1, aa, h);
return;
}

/**********************************/
/*                                */
/*   Listing 13.10                */
/*                                */
/*   remez()                      */
/*                                */
/**********************************/

void remez(	int nn,
			int r,
			int gridDensity,
			real kk,
			real freqP,
			real freqS,
			real extFreq[],
			real h[])
{
int m, gridMax, j, mP, gP, mS;
real absDelta,freq;
static real gridParam[10];
static int iFF[50];
static real ee[1024];

/*--------------------------------*/
/*  set up frequency grid         */
gridParam[0] = 1.0;
gridParam[1] = freqP;
gridParam[2] = freqS;
gridParam[3] = r;
gridParam[4] = gridDensity;
freq = gridFreq(gridParam,0);
mP = (int) gridParam[5];
mS = (int) gridParam[6];
gP = (int) gridParam[7];
freqP = freqP + (freqP/(2.0*gP));
gridMax = 1 + gridDensity*(mP+mS-1);

/*----------------------------------------------*/
/*  make initial guess of extremal frequencies  */

for(j=0; j<mP; j++) iFF[j] = (j+1)* gridDensity;

for(j=0; j<mS; j++) iFF[j+mP] = gP + 1 + j * gridDensity;

/*----------------------------------------------------*/
/*  find optimal locations for extremal frequencies   */

for(m=1;m<=20;m++) {

	remezError(	gridParam, gridMax, r, kk, freqP, iFF, ee);

	remezSearch( ee, absDelta, gP, iFF, gridMax, r, gridParam);
	
	remezStop2(ee,iFF,r);
	if(remezStop(iFF,r)) break;
	}

for(j=0; j<=r; j++) {
	extFreq[j] = gridFreq(gridParam,iFF[j]);
	}
remezFinish( extFreq, nn, r, freqP,kk, ee, h);
return;
}

/************************************************************************/
/************************************************************************/
#include <stdio.h>

main ()
{
//    #define NN  25
    #define NN  5
    #define RR  13

    int     nn = NN;
    int     r = RR;
    int     gridDensity = 16;
    real    kk = 500.;
//    real    freqP = .215;
//    real    freqS = .315;
    real    freqP = 3.5/32;
    real    freqS = 5.0/32;
    static  real    extFreq[RR+1];
    static  real    h[NN];
    WORD    usi;
    
    /********************************************************************/
    /********************************************************************/
    remez (nn, r, gridDensity, kk, freqP, freqS, extFreq, h);

    printf ("freqP: %f\tfreqS: %f\n", freqP, freqS);
    printf ("r: %d\tgrid: %d\tkk: %f\n", r, gridDensity, kk);
    printf ("\nExtrema Frequencies\n");
    for (usi=0; usi<RR+1; usi++) printf ("%d\t%.6f\n", usi, extFreq[usi]);
    printf ("\nCoefficients\n");
    for (usi=0; usi<(NN+1)/2; usi++) printf ("%d=%d\t%.6f\n", usi, NN-usi-1, h[usi]);

    /********************************************************************/
    /********************************************************************/
    return (0);
}
