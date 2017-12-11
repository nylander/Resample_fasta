/*
 * main.c
 *
 * Description:
 *     Subsample a fraction (default 0.5)
 *     of an alignment in fasta format.
 *
 * Usage:
 *     ./prog infile.fas > outfile.fas
 *
 * Version:
 *    Mon 11 dec 2017 17:11:10
 * 
 * By:
 *     Johan.Nylander@{nbis|nrm}.se
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dynarray.h"
#include "random.h"
#include "shuffle.h"
#include "quicksort.h"

#define XFRAC 0.5  // fraction to sample
#define WRAP 60    // line wrap for fasta seq


/*************************************************************
 * main
 *************************************************************/
int main(int argc, char *argv[]) {

	FILE * fp;
	struct ArrayData *seqarray;
    long int seqlength;
    long int samplesize;
    long int *random;
    int inheader;
    int ngts;
    int r;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.fas>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == 0) {
        perror("fopen");
        exit(1);
    }

	seqarray = initArray(); // Growable array to keep a sequence

    // Test to read the first sequence only
    inheader = 0;
    ngts = 0;
    seqlength = 0;
    while ((r = fgetc(fp)) != EOF) {
        if (inheader == 1) {
            if (r == '\n') { // print newline after header
                printf("%c", (char) r);
                inheader = 0;
            }
            else {           // print any character in header
                printf("%c", (char) r);
            }
        }
        else if (r == '>') {
            ++ngts;
            if (ngts > 1) {  // break on second fasta header
                break;
            }
            else {           // print '>' sign
                printf("\n%c", (char) r);
                inheader = 1;
            }
        }
        else {               // sequence characters (except newline)
            if (r != '\n') {
                //printf("%c", (char) r);
                seqlength++;
                addElement(seqarray, (char) r); // add char to array
            }
        }
    }

    // Do we have an array?
    //int i, get;
    //for(i = 0; i < seqlength; i++){
    //    get = getElement(seqarray, i);
  	//	printf("%c\n", (char) get);
    //}

    samplesize = (long int)(seqlength * XFRAC);

    // allocate for array 
    random = malloc(sizeof(long int) * samplesize);

    if (!random) {
        perror("Error allocating memory for array random");
        abort();
    }

    // fill array with 0,1,2,...,seglength-1
    //for(int i=0; i < seglength; i++) {
    //    random[i] = i;
    //}
    
    // then, shuffle the first samplesize entries of the array
    //part_shuffle(random, seglength, samplesize);

    // Alternatively, fill the whole array with random numbers
    // Need to make sure, however, that they are unique before sorting!
    //for(int i=0; i < samplesize; i++) {
    //    random[i] = randomAM(seqlength);
    //    //printf("in unsorted random:%ld\n", random[i]);
    //}

    // I only want to sort the first samplesize items of random

    // sort random in place. I need, however, to sort only 
    // the first samplesize items of random, not the whole array

    quicksort(random, samplesize);
    //for(int j=0; j < samplesize; j++) {
    //    printf("in sorted random:%ld\n", random[j]);
    //}

    //// Print first sequence
    //// Make sure to save sequence length
    //for (j=c=0; c < samplesize; ++c) {
    //    for ( ; j < random[c] ; ++j) {
    //        get = getElement(seqarray, j);
    //    }
    //    get = getElement(seq, j);
    //    printf("%c", (char) get);
    //    j++;
    //    k++;
    //    if (k > 0) {
    //        if (k%WRAP == 0) {
    //            printf("\n");
    //            k = 0;
    //        }
    //    }
    //}

    // Print the rest of the sequences


	free(seqarray->pointer);
	free(seqarray);

	return 0;
}

