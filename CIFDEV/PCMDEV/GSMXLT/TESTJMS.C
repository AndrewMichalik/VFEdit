/* testjms -- Adapted by JMS from testgsm */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gsm.h"

/* Generate the first 3 args of fread and fwrite */
#define FP(arr) (arr), sizeof((arr)[0]), sizeof(arr)/sizeof((arr)[0])

void fail (const char* message) {
	(void) fprintf (stderr, "Fatal error:  %s\n", message);
	exit (EXIT_FAILURE);
}

void fail2 (const char* message, const char* m2) {
	(void) fprintf (stderr, "Fatal error:  %s%s\n", message, m2);
	exit (EXIT_FAILURE);
}

FILE* mustOpen (const char* filename, const char* mode) {
	FILE* f = fopen(filename, mode);
	(void) printf ("Opening %s with mode %s\n", filename, mode);
	if (!f)
		fail2 ("Cannot open ", filename);
	return f;
}

int main(int argc, char** argv)
{
    gsm gsmh;
    gsm_signal src[GSM_SAMPLE_BLOCK], dec[GSM_SAMPLE_BLOCK];
    gsm_frame dst;
    const char* inFN;
    FILE* inFile;
    const char* encFN;
    FILE* encFile;
    const char* decFN; 
    FILE* decFile;
    int n;      /* For status dots */
    
    if (4 != argc)
		fail ("Usage:  testjms input encode decode");
    inFN = argv[1];
    inFile = mustOpen(inFN, "rb");
    encFN = argv[2];
    encFile = mustOpen(encFN, "wb");
    decFN = argv[3];
    decFile = mustOpen(decFN, "wb");
    gsmh = gsm_create();
    if (! gsmh)
		fail ("Can't create gsm\n");
    
    while (fread(FP(src), inFile) == GSM_SAMPLE_BLOCK) {
		if ((n++) % 100) {
			(void) printf (".");
			n = 0;
		}       
		gsm_encode(gsmh, src, dst);
		fwrite(FP(dst), encFile);
		gsm_decode(gsmh, dst, dec);
		fwrite(FP(dec), decFile);
    }

    fclose (inFile);
    fclose (encFile);
    fclose (decFile);
    (void) puts ("\ndone");
    return 0;
}
