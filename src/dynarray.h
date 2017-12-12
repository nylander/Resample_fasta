/*
 * dynarray.h
 * Mon 11 dec 2017 15:31:45
 * Johan.Nylander@{nbis|nrm}.se
 * Source: https://gist.githubusercontent.com/matugm/4708222/raw/ac5a5804c824e18c4ef1b1c760f54686adf602a1/array.h
 *
 */


#ifndef DYNARRAY_H
#define DYNARRAY_H

struct ArrayData *initArray();
int addElement(struct ArrayData *array, long int number);
int getElement(struct ArrayData *array, long int index);

struct ArrayData {
    int *pointer;
    long int counter;
    long int size;
};

#endif /* DYNARRAY_H */
