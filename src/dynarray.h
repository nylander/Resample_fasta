// https://gist.githubusercontent.com/matugm/4708222/raw/ac5a5804c824e18c4ef1b1c760f54686adf602a1/array.h

#ifndef ARRAY_H_
#define ARRAY_H_

struct ArrayData *initArray();
int addElement(struct ArrayData *array, int number);
int getElement(struct ArrayData *array, int index);

struct ArrayData {
  int *pointer;
  int counter;
	int size;
};

#endif /* ARRAY_H_ */