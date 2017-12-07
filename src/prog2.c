// Based on https://rosettacode.org/wiki/FASTA_format#C
// Thu 07 Dec 2017 01:12:17 PM CET
// compile: gcc -o prog2 prog2.c 
// run: ./prog2 infile

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "twister.h"
//#include "quicksort.h"

//#define XFRAC 0.5  // fraction to sample
//#define WRAP 60    // line wrap for fasta seq

int main(int argc, char *argv[])
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

    long int seqlength;
    long int c, i, j, n;
    //int k;
    long int samplesize;
    long int *random;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.fas>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
 
	int state = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		/* Delete trailing newline */
		if (line[read - 1] == '\n')
			line[read - 1] = 0;
		/* Handle comment lines*/
		if (line[0] == '>') {
			if (state == 1)
				printf("\n");
			printf(">%s\n", line+1);
			state = 1;
		}
        else {
			/* Print everything else */
			printf("%s", line);
            for(i=0; i < samplesize; i++) {
                random[i] = randomMT();
            }

		}
	}
	printf("\n");
 
	fclose(fp);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}
