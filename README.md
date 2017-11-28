# Resample FASTA alignments

- Tue 28 Nov 2017 12:21:56 PM CET
- JN

## Description

Sample random columns from a set of aligned fasta formatted sequences.
That is, sample positions in one sequence, then make sure to sample the same
potitions in all consequtive seuences as well.

Note: Reservoir sampling doesn't seem to fit well for several sequences if sequence file is read as a stream.
Try to look at hashes instead:

http://troydhanson.github.io/uthash/index.html

https://github.com/attractivechaos/klib


On approach that seems fit is ["reservoire sampling"](http://en.wikipedia.org/wiki/Reservoir_sampling): 

>Reservoir sampling is a family of randomized algorithms for randomly choosing k 
>samples from a list of n items, where n is either a very large or unknown 
>number. Typically n is large enough that the list doesn’t fit into main 
>memory.

Another approach might be the ["inside-out version of the Fisher-Yates shuffle"](https://en.wikipedia.org/wiki/Reservoir_sampling#Relation_to_Fisher-Yates_shuffle):

## Links

- [http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Randomization.html](http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Randomization.html)
- [https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement](https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement)
- [http://www.geeksforgeeks.org/reservoir-sampling/](http://www.geeksforgeeks.org/reservoir-sampling/)
- [https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement](https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement)
- [https://gregable.com/2007/10/reservoir-sampling.html](https://gregable.com/2007/10/reservoir-sampling.html)
- [http://man7.org/linux/man-pages/man3/hsearch.3.html](http://man7.org/linux/man-pages/man3/hsearch.3.html)
- [https://lemire.me/blog/2013/08/16/picking-n-distinct-numbers-at-random-how-to-do-it-fast/](https://lemire.me/blog/2013/08/16/picking-n-distinct-numbers-at-random-how-to-do-it-fast/)


## Some code

    char* array[19];
    #define ARR_SIZE(arr) ( sizeof((arr)) / sizeof((arr[0])) )
    arr[rand() % ARR_SIZE(arr)]

    int n = rand()%20; // But, "% 20 can yield non-uniform results"
    printf("%s\n", array[n]);



    // Returns an array containing x unique random ints between min and max. (caller must free).
    // Works by generating x sequential random integers in the range, then 
    // shuffling them. Add a seed(time) somewhere in caller if you don't want the same 
    // results every run.
    // Source: https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement

    #include <stdlib.h>
    #include <stdint.h>
    #define MAX_ALLOC ((uint32_t)0x40000000)  //max allocated bytes, fix per platform
    #define MAX_SAMPLES (MAX_ALLOC/sizeof(uint32_t))

    int* randsamp(uint32_t x, uint32_t min, uint32_t max)
    {
       uint32_t r,i=x,*a;
       if (!x||x>MAX_SAMPLES||x>(max-min+1)) return NULL;
       a=malloc(x*sizeof(uint32_t));
       while (i--) {
          r= (max-min+1-i);
          a[i]=min+=(r ? rand()%r : 0);
          min++;
       }
       while (x>1) {
          r=a[i=rand()%x--];
          a[i]=a[x];
          a[x]=r;
       }
       return a;
    }
