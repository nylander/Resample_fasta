/*
 * resample_fasta.c
 *
 * Description:
 *     Subsample a fraction (default 0.5) of a
 *     multiple-sequence alignment in fasta format.
 *     Reads a file, prints to STDOUT.
 *     Change fraction to sample ("XFRAC") below.
 *     Reminder: sequences need to be aligned
 *     (same length).
 *     No extensive error checking: Caveat emptor!
 *
 * Compile:
 *     gcc -Wall -O3 -o refas resample_fasta.c
 *
 * Usage:
 *     ./refas infile > outfile.fas
 *
 * By:
 *     Johan.Nylander@{nbis|nrm}.se
 *
 * Version:
 *    12/12/2017 09:41:15 AM
 * 
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
    long int j, c;
    int inheader;
    int ngts;
    int r, k;

    if (argc == 1) {
        printf("Usage: %s <infle>\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    fp = fopen(argv[1], "r");

    if(fp == 0) {
        perror("Error: failed in opening file");
        exit(EXIT_FAILURE);
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
                break;
            }
            else {
                inheader = 1;
            }
        }
        else {
            if (r != '\n') {// should also ignore white space: r != '\n' && r != ' '?
                seqlength++;
            }
        }
    }

    rewind(fp);

    samplesize = (long int)(seqlength * XFRAC);

    // Allocate for array. Possible for how large data?
    random = malloc(sizeof(long int) * samplesize);

    if (!random) {
        perror("Error allocating memory for array random");
        exit(EXIT_FAILURE);
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
                printf("\n");
                if (seqlen != seqlength) { // test if equal length to first seq
                    printf("Error! Seq length not equal (%li vs %li).\nAborting\n", seqlen, seqlength);
                    free(random);
                    exit(EXIT_FAILURE);
                }
                ngts = 0;
            }
            printf("%c", (char) r);
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
    printf("\n");
    
    fclose(fp);
    free(random);

    exit(EXIT_SUCCESS);
}

