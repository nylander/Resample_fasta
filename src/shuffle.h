/*
 * shuffle.h
 * Mon 11 dec 2017 15:31:45
 * Johan.Nylander@{nbis|nrm}.se
*/

#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>

void part_shuffle(int *array, size_t array_size, size_t shuff_size);

/* 
 * part_shuffle
 * Shuffles only part (shuff_size) of an array of length (array_size) in place.
 * Use no more than shuff_size from array after calling the function.
 * Source: https://stackoverflow.com/questions/19362167/generating-unique-random-numbers-in-an-array-using-loop
*/
void part_shuffle(int *array, size_t array_size, size_t shuff_size) {
    if (array_size > 1) {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < shuff_size - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (array_size - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}
//int main(int argc, char * argv[]) {
//    int a[100];
//    int i;
//    int shufsize = 25;
//    for(i=0; i<100; ++i) {
//        a[i] = i;
//    }
//    part_shuffle(a,100,shufsize);
//    // Print only the first shufsize elements!
//    for(i=0; i < shufsize; ++i) {
//        printf("%i\n", a[i]);
//    }
//}   


#endif /* !RANDOM_H */
