# Resample FASTA alignments

- Wed 29 Nov 2017 09:28:25 AM CET 
- JN

## Description

Sample random columns from a set of aligned fasta formatted sequences.
That is, sample positions in one sequence, then make sure to sample the same
potitions in all consequtive seuences as well.

Note: Reservoir sampling doesn't seem to fit well for several sequences if sequence file is read as a stream.
Try to look at hashes instead:

- [http://troydhanson.github.io/uthash/index.html](http://troydhanson.github.io/uthash/index.html)
- [https://github.com/attractivechaos/klib](https://github.com/attractivechaos/klib)
- [https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm](https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm)



Note: `RAND_MAX`, The value of this macro is an integer constant representing the largest value the rand function can return. In the GNU C Library, it is 2147483647, which is the largest signed integer representable in 32 bits. [source](https://www.gnu.org/software/libc/manual/html_node/ISO-Random.html)




On approach that seems fit is ["reservoire sampling"](http://en.wikipedia.org/wiki/Reservoir_sampling): 

>Reservoir sampling is a family of randomized algorithms for randomly choosing k 
>samples from a list of n items, where n is either a very large or unknown 
>number. Typically n is large enough that the list doesn’t fit into main 
>memory.

Another approach might be the ["inside-out version of the Fisher-Yates shuffle"](https://en.wikipedia.org/wiki/Reservoir_sampling#Relation_to_Fisher-Yates_shuffle):

## Links

- [https://gist.github.com/matugm/4708222](https://gist.github.com/matugm/4708222)
- [http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Randomization.html](http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Randomization.html)
- [https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement](https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement)
- [http://www.geeksforgeeks.org/reservoir-sampling/](http://www.geeksforgeeks.org/reservoir-sampling/)
- [https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement](https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement)
- [https://gregable.com/2007/10/reservoir-sampling.html](https://gregable.com/2007/10/reservoir-sampling.html)
- [http://man7.org/linux/man-pages/man3/hsearch.3.html](http://man7.org/linux/man-pages/man3/hsearch.3.html)
- [https://lemire.me/blog/2013/08/16/picking-n-distinct-numbers-at-random-how-to-do-it-fast/](https://lemire.me/blog/2013/08/16/picking-n-distinct-numbers-at-random-how-to-do-it-fast/)
- [http://www.azillionmonkeys.com/qed/random.html](http://www.azillionmonkeys.com/qed/random.html)
- [https://www.gnu.org/software/libc/manual/html_node/ISO-Random.html](https://www.gnu.org/software/libc/manual/html_node/ISO-Random.html)
- []()




## Some code

To print line breaks after some length, use an iterator (i), and use the modulo operator:

    for (i=0; i<1000; i++) {
        printf("%20llu ", genrand64_int64());
        if (i%5==4) printf("\n");
    }





    int main(void)
    {
        int i;
        unsigned long long init[4]={0x12345ULL, 0x23456ULL, 0x34567ULL, 0x45678ULL}, length=4;
        init_by_array64(init, length);
        printf("1000 outputs of genrand64_int64()\n");
        for (i=0; i<1000; i++) {
          printf("%20llu ", genrand64_int64());
          if (i%5==4) printf("\n");
        }
        printf("\n1000 outputs of genrand64_real2()\n");
        for (i=0; i<1000; i++) {
          printf("%10.8f ", genrand64_real2());
          if (i%5==4) printf("\n");
        }
        return 0;
    }

