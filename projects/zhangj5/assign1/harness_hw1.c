//This harness_hw1.c is used to test the binarysearch.c program
//email: zhangj5@onid.oregonstate.edu

#include <stdio.h>
#include "sort.h"
#include <assert.h>

int array[SIZE];
int nondet_int();
//unsigned int nondet_uint();  // using for __CPROVER_assume()
   
int main(int argc, char *argv[]) {
  int size, value, i, flag, search;
  unsigned s;
  int size = nondet_int();

  __CPROVER_assume (size == SIZE);

  //generate size number desired integers from 1 to 30 and then store these integers into array
  for(i = 0; i < size; i++) {
    int result = nondet_int();
    __CPROVER_assume(result>=1 && result <= 30);
      array[i] = result;
  }

  //using bubble sort algorithm to sort these size number integers in ascending order before implement binary search algorithm.
  int j, k, temp;
  for (j = 0; j < size; j++) {
    for (k = j; k < size; k++) {
      if (array[j] > array[k]) {
        temp = array[j];
        array[j] = array[k];
        array[k] = temp;
      }
    }
  }

  //print size number sorted integers 
  for(i= 0; i < size; i++) 
    printf("Log: array[%d] = %d\n", i, array[i]);
   
  //random generate a wanted search integer range from 1 to 30
  int search = nondet_int();
  __CPROVER_assume(search>=1 && search <= 30);

  //call function binarysearch()
  printf("Log: After the binarysearch function be called\n");
  flag = binarysearch(array, search, size);
  if(flag == 0)
    printf("%d is not in array\n", search);
  else if (flag == 1)
    printf("%d is not in array\n", search);
}







