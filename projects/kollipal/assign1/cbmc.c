#include <stdio.h>
#include "cbmc.h"

void merge(int a[], int b[], int size, int merged[])
{
	int i =0, j =0, k =0;
	while (i < size && j < size)
	{
    	if (a[i] <= b[j])
    	{
        	merged[k++] = a[i++];
    	}
    	else
    	{
        	merged[k++] = b[j++];
    	}
	}
	while (i < size)
	{
		merged[k++] = a[i++];
	}
	while (j < size)
	{
		merged[k++] = b[j++];
	}
}

int isSubset(int arr1[], int size1, int arr2[], int size2)
{
    int i = 0;
    int j = 0;
    for (i=0; i<size2; i++)
    {
        for (j = 0; j<size1; j++)
        {
        	if(arr2[i] == arr1[j])
            	break;
        }
         
/* If the above inner loop was not broken at all then arr2[i] is not present in arr1[] */
        if (j == size1)
        	return 0;
    }
     
/* If we reach here then all elements of arr2[] are present in arr1[] */
    return 1;
}
void mysort(int merged[], int size)
{
    int i, j, temp =0;
    for (i = 0; i < size; i++)
    {
        for (j = i; j < size; j++)
        {
            if (merged[i] > merged[j])
            {
                merged[i] = merged[i] + merged[j];
                merged[j] = merged[i] - merged[j];
                merged[i] = merged[i] - merged[j];
            }
        }
    }
}