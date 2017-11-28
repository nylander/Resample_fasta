#include <zlib.h>
#include <stdio.h>
#include "kseq.h"

KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
{
    gzFile fp;
    kseq_t *seq;
    long int l;
    long int m;
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.seq>\n", argv[0]);
        return 1;
    }
    fp = gzopen(argv[1], "r");
    if(fp == 0) {
        perror("fopen");
        exit(1);
    }
    // Read the first sequence and get the length
    seq = kseq_init(fp);
    if (seq->name.s) printf("Header %s\n", seq->name.s);
    //if (seq->seq.s) printf("Sequence: %s\n", seq->seq.s);
    l = kseq_read(seq);
    printf("Seq length: %ld\n", l);
    //getchar();

    // Read the rest of the sequences
    while ((m = kseq_read(seq)) >= 0) {
        if (seq->name.s) printf("Header %s\n", seq->name.s);
        //if (seq->seq.s) printf("Sequence: %s\n", seq->seq.s);
        printf("Seq length: %ld\n", m);
    }
    kseq_destroy(seq);
    gzclose(fp);
    return 0;
}
