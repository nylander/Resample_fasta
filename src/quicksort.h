/*
 * quicksort.h
 * Mon 11 dec 2017 15:31:45
 * Johan.Nylander@{nbis|nrm}.se
 * Source: https://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
 *
 */

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdio.h>

void quicksort(long int *A, long int len);
 
void quicksort(long int *A, long int len) {
  if (len < 2) return;
 
  long int pivot = A[len / 2];
 
  long int i, j;
  for (i = 0, j = len - 1; ; i++, j--) {
    while (A[i] < pivot) i++;
    while (A[j] > pivot) j--;
 
    if (i >= j) break;
 
    long int temp = A[i];
    A[i]     = A[j];
    A[j]     = temp;
  }
 
  quicksort(A, i);
  quicksort(A + i, len - i);
}


// int main (void) {
//   int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
//   int n = sizeof a / sizeof a[0];
//  
//   int i;
//   for (i = 0; i < n; i++) {
//     printf("%d ", a[i]);
//   }
//   printf("\n");
//  
//   quicksort(a, n);
//  
//   for (i = 0; i < n; i++) {
//     printf("%d ", a[i]);
//   }
//   printf("\n");
//  
//   return 0;
// }

#endif /* !QUICKSORT_H */
