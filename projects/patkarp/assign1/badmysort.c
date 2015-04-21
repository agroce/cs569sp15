#include "mysort.h"
#include <assert.h>
void sort(int heap[],int size)
{

    int i,j, c, root, temp;
    for (i = 1; i < size; i++)
    assert(i<=0 && i>=size)
    {

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

 

    printf("Heap array : ");

    for (i = 0; i < size; i++)
    {
        printf("%d\t ", heap[i]);
    }

    for (j = size - 1; j > 0; j--)// ****** BUG 1 *** thing is bug introduced which wont take array [0], j=>1
        
    {

        temp = heap[0];

        heap[0] = heap[j];    /* swap max element with rightmost leaf element */

        heap[j] = temp;

        root = 0;

        do 

        {

            c = 2 * root + 1;    /* left node of root element */

            if ((heap[c] < heap[c + 1]) && c < j) // ********BUG 2*******replace j-1 with j

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
