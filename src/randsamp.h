// Source: https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define MAX_ALLOC ((uint32_t)0x40000000)  //max allocated bytes, fix per platform
#define MAX_SAMPLES (MAX_ALLOC/sizeof(uint32_t))

long int * randsamp(uint32_t x, uint32_t min, uint32_t max);

int * getRandom();


