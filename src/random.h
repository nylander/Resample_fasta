/*
 * random.h
 * Mon 11 dec 2017 15:31:45
 * Johan.Nylander@{nbis|nrm}.se
*/

#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>

long randomAM(long max);

/*
 * randomAM
 * Assumes 0 <= max <= RAND_MAX
 * Returns in the closed interval [0, max]
 * Source: https://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range
*/
long randomAM(long max) {
  unsigned long
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = random();
  }
  while (num_rand - defect <= (unsigned long)x);

  return x/bin_size;
}

#endif /* !RANDOM_H */
