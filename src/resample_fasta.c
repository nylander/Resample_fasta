/*
 * resample_fasta.c
 *
 * Description:
 *     Subsample a fraction (default 0.5)
 *     of an alignment in fasta format.
 *
 * Compile:
 *     gcc -Wall -O3 -o resample_fasta resample_fasta.c
 *
 * Usage:
 *     ./resample_fasta infile.fas > outfile.fas
 *
 * Version:
 *    12/12/2017 01:31:43 AM
 * 
 * By:
 *     Johan.Nylander@{nbis|nrm}.se
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define XFRAC 0.5  // fraction to sample
#define WRAP 60    // line wrap for fasta seq


int main(int argc, char *argv[]) {

	FILE * fp;
    long int seqlength;
    long int seqlen;
    long int samplesize;
    long int *random;
    long int im, in;
    int inheader;
    int ngts;
    int r;
    int k;
    long int j, c;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.fas>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == 0) {
        perror("fopen");
        exit(1);
    }

    // Read the first sequence to get sequence length
    inheader = 0;
    ngts = 0;
    seqlength = 0;
    while ((r = fgetc(fp)) != EOF) {
        if (inheader == 1) {
            if (r == '\n') {
                inheader = 0;
            }
        }
        else if (r == '>') {
            ++ngts;
            if (ngts > 1) {
                ungetc(r, fp);
                break;
            }
            else {
                inheader = 1;
            }
        }
        else {
            if (r != '\n') {
                seqlength++;
            }
        }
    }

    rewind(fp);

    samplesize = (long int)(seqlength * XFRAC);

    // Allocate for array. Possible for large data? Limit?
    random = malloc(sizeof(long int) * samplesize);

    if (!random) {
        perror("Error allocating memory for array random");
        abort();
    }

    srand(time(NULL));

    // Use Knuth's algorithm to get sorted unique random numbers
    for (in = im = 0; in < seqlength && im < samplesize; ++in) {
        long int rn = seqlength - in;
        long int rm = samplesize - im;
        if (rand() % rn < rm) {
            random[im++] = in;
        }
    }

    // Read file again
    inheader = 0;
    ngts = 0;
    seqlen = 0;
    j = c = k = 0;
    while ((r = fgetc(fp)) != EOF) {
        if (inheader == 1) {
            if (r == '\n') { // print newline after header
                printf("%c", (char) r);
                inheader = 0;
            }
            else { // print any character in header
                printf("%c", (char) r);
            }
        }
        else if (r == '>') {
            ++ngts;
            if (ngts > 1) {
                if (seqlen != seqlength) { // test if equal length to first seq
                    printf("Error! Seq length not equal (%li vs %li).\nAborting\n", seqlen, seqlength);
                    free(random);
                    return 1;
                }
                ngts = 0;
            }
            printf("\n%c", (char) r);
            inheader = 1;
            j = c = k = 0;
            seqlen = 0;
        }
        else { // r is a sequence character, or a newline in the sequence
            if (r != '\n') {
                seqlen++;
                if (j == random[c]) {
                    printf("%c", (char) r);
                    if (k > 0) {
                        if (k%WRAP == 0) {
                            printf("\n");
                            k = 0;
                        }
                    }
                    k++;
                    c++;
                }
                j++;
            }
        }
    }

    free(random);

	return 0;
}

