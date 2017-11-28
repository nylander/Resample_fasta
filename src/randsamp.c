// Returns an array containing x unique random ints between min and max. (caller must free).
// Works by generating x sequential random integers in the range, then 
// shuffling them. Add a seed(time) somewhere in caller if you don't want the same 
// results every run.
// Source: https://codegolf.stackexchange.com/questions/4772/random-sampling-without-replacement
// See also: https://stackoverflow.com/questions/14297169/how-to-make-an-array-return-type-from-c-function

#include "randsamp.h" 

long int * randsamp(uint32_t x, uint32_t min, uint32_t max) {

   uint32_t r, i=x, *a;

   if (!x || x>MAX_SAMPLES || x>(max - min+1)) return NULL;

   a = malloc(x * sizeof(uint32_t));

   while (i--) {
      r = (max - min+1 - i);
      a[i] = min += (r ? rand()%r : 0);
      min++;
   }

   while (x>1) {
      r = a[i = rand()%x--];
      a[i] = a[x];
      a[x] = r;
   }

   return a;

}


int * getRandom( ) {

   static int r[10];
   int i;

   /* set the seed */
   srand( (unsigned)time( NULL ) );

   for ( i = 0; i < 10; ++i) {
      r[i] = rand();
      //printf( "r[%d] = %d\n", i, r[i]);
   }

   return r;
}

