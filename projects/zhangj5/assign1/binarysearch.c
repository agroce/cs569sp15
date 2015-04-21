//CS569 Homework1
//the purpose of this program is using binary seach method to search a desired number within a given array
//This program comes from http://www.programmingsimplified.com/c/source-code/c-program-binary-search
//email: zhangj5@onid.oregonstate.edu

#include <stdio.h>
#include "sort.h"

/**

int binsearch(int a[], int search, int n);
 
int main(int argc,char *argv[])
{
  int c,  n, search, array[100];
  int flag;
  printf("Enter number of elements\n");
  scanf("%d", &n);

  //assuming the input numbers are in ascending order.
  printf("Enter sorted %d integers\n", n);
  
  for (c = 0; c < n; c++)
    scanf("%d",&array[c]);
 
  printf("Enter value to find\n");
  scanf("%d", &search);

  flag = binsearch(array, search, n);
  printf("The flag number is %d\n", flag);
  return 0;   
}

**/

int binsearch(int array[], int search, int n)
{
  int first;
  int last;
  int middle;
  int m;
  
  first = 0;
  // 0 1 2 3 4 5 
  // !!! bug.  The variable last should equal to (n - 1)
  last = n;
  middle = (first+last)/2;

  while (first <= last) 
    {
//if desired number is greater than the middle of array, it impossible belong in the left half array. 
      if (array[middle] < search) 
	first = middle;  //!!! bug, the variable first should equal to (middle + 1)

      else if (array[middle] == search) 
	{
	  printf("%d found at location %d.\n", search, middle+1);
	  return 1;  //founded, return 1
	}
      //if desired number is less than the middle of array, it impossible belong in the right half array.
 
     else
       last = middle ;  //!! bug, the variable last should equal to (middle -1) 

      middle = (first + last)/2;
    }
  if (first > last)
    {
      printf("Not found! %d is not present in the list.\n", search);     
      return 0; // not found, return 0
    }

}

