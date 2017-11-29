#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <zlib.h>
#include "kseq.h"
#include "dict.h"
#include "twister.h"
//#include "khash.h"
//#include "SFMT.h"
//#include "mt19937-64.h"

#define XFRAC 0.5  // fraction to sample
#define WRAP 60    // line wrap for fasta seq

KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[]) {

    gzFile fp;
    kseq_t *seq;
    Dict d;
    long int seqlength; // sizeof( long int ) is 8 bytes
    long int i;
    long int j;
    long int m;
    long int samplesize;
    long int *seqnrarray;
    //long int *samplenrarray;

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
    seqlength = kseq_read(seq);

    samplesize = (long int)(seqlength * XFRAC);

    // Generate array of random integers for the whole seq 
    //seedMT(4357U);
    seedMT(time(NULL));

    seqnrarray = malloc(sizeof(long int) * seqlength);
    if (!seqnrarray) {
        perror("Error allocating memory");
        abort();
    }

    for(j=0; j < seqlength; j++) {
        seqnrarray[j] = randomMT();
    }
    getchar();

    // create a dictionary
    d = DictCreate();

    for (i=0; i < seqlength; i++) {
        DictInsert(d, seqnrarray[i], seq->seq.s[i]);
    }


    //samplenrarray = malloc(sizeof(long int) * samplesize);
    //if (!samplenrarray) {
    //    perror("Error allocating memory");
    //    abort();
    //}

    // Print first sequence
    if (seq->name.s) printf(">%s\n", seq->name.s);
    if (seq->seq.s) {
        for (i=0; i < seqlength; i++) {
            printf("%c", seq->seq.s[i]);
            if (i > 0) {
                if (i%WRAP==0) printf("\n");
            }
        }
        printf("\n");
    }

    // Read the rest of the sequences
    while ((m = kseq_read(seq)) >= 0) {
        if (seq->name.s) printf(">%s\n", seq->name.s);
        for (i=0; i < seqlength; i++) {
            printf("%c", seq->seq.s[i]);
            if (i > 0) {
                if (i%WRAP==0) printf("\n");
            }
        }
        printf("\n");
    }

    kseq_destroy(seq);
    gzclose(fp);
    free(seqnrarray);
    //free(samplenrarray);

    return(EXIT_SUCCESS);
}

