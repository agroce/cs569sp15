
#include <stdio.h>
#include <stdlib.h>
#include "seqlist.h"

void Error(char * message)
{
    printf("Error:%s\n",message);
    exit(1);
}


void InsertList(struct Seqlist *L, int x, int i)
{
    int j;
    if (i < 0 || i > L->length)
        Error("position error");
    
    if ( L->length >= ListSize )
        Error("overflow");
    
    for (j = L->length - 1; j >= i; j--)
        L->data[j+1] = L->data[j];
    
    L->data[i]=x;
    L->length++ ;
}


void DeleteList ( struct Seqlist *L, int i )
{
    int j;
    
    if (i < 0 || i > L->length-1)
        Error("position error");
    
    // Injected Bug: when key == size holds, here is a position error.
    // Correct: j < L->length
    // Found by --memory-leak-check option. --bounds-check option
    // can also detect here is a bug, but points that the bug is
    // in the body of for-loop.
    for (j = i+1; j <= L->length; j++)
        L->data[j-1] = L->data[j];
    
    L->length--;
}


void Initlist(struct Seqlist *L)
{
    L->length = 0;
}






