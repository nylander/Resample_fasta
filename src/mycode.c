/* 
 *
 * Description: Subsample a fraction (default 0.5)
 * of an alignment in fasta format.
 *
 * Usage: ./prog infile.fas > outfile.fas
 *
 * Version: Thu 07 Dec 2017 12:44:34 PM CET
 * By: Johan.Nylander@{nbis|nrm}.se
 *
 * TODO: rewrite so user can ask for a specific
 * sequence output length. Now I read the first
 * sequence separately in order to get the length
 * and the fraction.
 *
 *
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <zlib.h>
#include "kseq.h"
#include "twister.h"
#include "quicksort.h"

#define XFRAC 0.5  // fraction to sample
#define WRAP 60    // line wrap for fasta seq

KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[]) {

    gzFile fp;
    kseq_t *seq;
    long int seqlength;
    long int c, i, j, n;
    //int k;
    long int samplesize;
    long int *random;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.fas>\n", argv[0]);
        return 1;
    }

    fp = gzopen(argv[1], "r");
    if(fp == 0) {
        perror("fopen");
        exit(1);
    }

    // Read the first sequence and get the length
    seq = kseq_init(fp);
    seqlength = kseq_read(seq); // does kseq read in the whole seq or only provide a stream?

    samplesize = (long int)(seqlength * XFRAC);

    // Generate sorted array of random integers of size=sample size
    seedMT(time(NULL)); //seedMT(4357U);

    random = malloc(sizeof(long int) * samplesize);

    if (!random) {
        perror("Error allocating memory for random array");
        abort();
    }

    for(i=0; i < samplesize; i++) {
        random[i] = randomMT();
    }

    // sort random in place.
    n = sizeof(random) / sizeof(random[0]);

    quicksort(random, n);

    // Print first sequence
    if (seq->name.s) printf(">%s\n", seq->name.s);
    if (seq->seq.s) {
        //k=0;
        for (j=c=0; c < samplesize; ++c) {
            for ( ; j < random[c] ; ++j) {
                scanf(seq->seq.s[j]); // what is correct function xxx to use?
            }
            printf("%c", seq->seq.s[j]);
            j++;
            //k++;
            //if (k > 0) {
            //     if (k%WRAP==0) printf("\n");
            //     k = 0;
            //}
        }
    }
    printf("did first sequence\n");
    getchar();
    // Read the rest of the sequences
    while ((kseq_read(seq)) >= 0) {
        if (seq->name.s) printf(">%s\n", seq->name.s);
        if (seq->seq.s) {
            //k=0;
            for (j=c=0; c < samplesize; ++c) {
                for ( ; j < random[c] ; ++j) {
                    //xxx(seq->seq.s[j]); // what is correct function xxx to use?
                }
                printf("%c", seq->seq.s[j]);
                j++;
                //k++;
                //if (k > 0) {
                //    if (k%WRAP==0) {
                //        printf("\n");
                //        k = 0;
                //    }
                //}
            }
        }
        printf("\n");
    }

    kseq_destroy(seq);
    gzclose(fp);
    free(random);

    return(EXIT_SUCCESS);
}

