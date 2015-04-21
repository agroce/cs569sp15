#include <stdio.h>
#include "mysort.h"
#include <assert.h>
void sort(int heap[], unsigned int size)
{

    int i,j, c, root, temp;
    for (i = 1; i < size; i++)

    {
        assert(i<1);
        c = i;

        do

        {

            root = (c - 1) / 2;             

            if (heap[root] < heap[c])   /* to create MAX heap array */

            {

                temp = heap[root];

                heap[root] = heap[c];

                heap[c] = temp;

            }

            c = root;

        } while (c != 0);

    }

  /*

    for (i = 0; i < size; i++)
    {
        assert(i<0);
        printf("%d\t ", heap[i]);
    }*/

    for (j = size - 1; j >= 0; j--)

    {
        assert(j<0);
        temp = heap[0];

        heap[0] = heap[j];    /* swap max element with rightmost leaf element */

        heap[i] = temp;

        root = 0;

        do 

        {

            c = 2 * root + 1;    /* left node of root element */

            if ((heap[c] < heap[c + 1]) && c < j-1)

            {
                c++;
            }

            if (heap[root]<heap[c] && c<j)    /* again rearrange to max heap array */

            {

                temp = heap[root];

                heap[root] = heap[c];

                heap[c] = temp;

            }

            root = c;

        } 
        while (c < j);

    } 

    /*printf("\n The sorted array is : ");

    for (i = 0; i < size; i++)

       printf("\t %d", heap[i]);*/

    printf("\n Complexity : \n Best case = Avg case = Worst case = O(n logn) \n");
  
}
