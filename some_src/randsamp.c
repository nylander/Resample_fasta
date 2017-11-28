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


