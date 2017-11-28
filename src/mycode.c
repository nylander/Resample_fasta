#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
#include "randsamp.h"

#define XFRAC 0.5

KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
{
    gzFile fp;
    kseq_t *seq;
    long int seqlength;
    int i;
    long int m;
    long int samplesize;
    long int *ar;

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
    printf("Seq length: %ld\n", seqlength);
    getchar();
    
    samplesize = (int)(seqlength * XFRAC);

    printf("Sample size: %ld\n", samplesize);
    getchar();

    srand(time(NULL));

    ar = randsamp(samplesize, 0, seqlength);
    for ( i = 0; i < samplesize; i++ ) {
        printf("Random nr: %ld\n", ar[i]);
    }
    

    getchar();

    //if (seq->name.s) printf(">%s\n", seq->name.s);
    //if (seq->seq.s) printf("Sequence: %s\n", seq->seq.s);
    //getchar();

    // Read the rest of the sequences
    while ((m = kseq_read(seq)) >= 0) {
        if (seq->name.s) printf(">%s\n", seq->name.s);
        //if (seq->seq.s) printf("Sequence: %s\n", seq->seq.s);
        printf("Seq length: %ld\n", m);
    }

    kseq_destroy(seq);
    gzclose(fp);
    free(ar);

    return 0;
}
