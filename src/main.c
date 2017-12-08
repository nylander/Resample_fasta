/* 
 *
 * Description:
 *     Subsample a fraction (default 0.5)
 *     of an alignment in fasta format.
 *
 * Usage:
 *     ./prog infile.fas > outfile.fas
 *
 * Version:
 *    Fri 08 Dec 2017 06:28:44 PM CET 
 * 
 * By:
 *     Johan.Nylander@{nbis|nrm}.se
 *
 * TODO:
 *     Rewrite so user can ask for a specific
 *     sequence output length. Now I read the first
 *     sequence separately in order to get the length
 *     and the fraction.
 *
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include "dynarray.h"
#include "twister.h"
#include "quicksort.h"

#define XFRAC 0.5  // fraction to sample
#define WRAP 60    // line wrap for fasta seq
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) // N elemnts in array

int main(int argc, char *argv[]) {

	FILE * fp;
	struct ArrayData *seqarray;
    //long int seqlength;
    //long int samplesize;
    //long int *random;
	//int get;
	//int i;
    //long int c;
    //long int i;
    //long int j;
    //long int n;
    //long int r;
    //int k;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.fas>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == 0) {
        perror("fopen");
        exit(1);
    }

    // Here is where I wish to read input from file into an array
    // that may grow.
    //
	seqarray = initArray();

    //int state = 0;
    // figure out how the states should be set (1=in the sequence, 0=in the header)
    //while ((r = fgetc(file)) != EOF) {
    //    if (state == 1) {
    //        addElement(seqarray, (char) r);
    //    }
    //    else {
    //        printf("%s", (char) r);
    //    }
    //    if (r == '>') {
    //        state = 0;
	//		printf("%s", (char) r);
    //    }
    //    else if (r == '\n') {
    //        state = 1;

    //    }
    //    if (state == 1) {
    //        addElement(seqarray, (char) r);
    //    }
    //}
    //addElement(seqarray, '\0');

	//for (i = 0; i < 5000; i++) {
	//	addElement(seqarray, rand() % 50000);
	//	get = getElement(seqarray, i);
  	//	printf("%d\n", get);
	//}

    //// When I have the sequence in an array "seqarray", then
    //seqlength = NELEMS(seqarray);
    //samplesize = (long int)(seqlength * XFRAC);
    //seedMT(time(NULL)); //seedMT(4357U);
    //random = malloc(sizeof(long int) * samplesize);
    //    if (!random) {
    //    perror("Error allocating memory for random array");
    //    abort();
    //}

    //for(i=0; i < samplesize; i++) {
    //    random[i] = randomMT();
    //}

    //// sort random in place.
    //n = sizeof(random) / sizeof(random[0]);

    //quicksort(random, n);

    //// First sequence
    //for (j=c=0; c < samplesize; ++c) {
    //    for ( ; j < random[c] ; ++j) {
    //        get = getElement(seq, j);
    //    }
    //    printf("%c", seq[j]);
    //    j++;
    //    k++;
    //    if (k > 0) {
    //        if (k%WRAP==0) {
    //            printf("\n");
    //            k = 0;
    //        }
    //    }
    //}

	free(seqarray->pointer);
	free(seqarray);

	return 0;
}

