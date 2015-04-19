//
//  harness.c
//  assign1
//
//  Created by LiuXin on 4/18/15.
//  Copyright (c) 2015 apepkuss. All rights reserved.
//

#define ListSize 100
#include <stdio.h>
#include <stdlib.h>
#include "sut.h"

int nondet_int(); // returns a non-deterministic integer value
unsigned int nondet_unsigned_int(); // returns a non-deterministic unsigned integer value

int main(int argc, const char * argv[])
{
    struct Seqlist *SEQA;
    int i, x, size;
    
    SEQA = (struct Seqlist *)malloc(sizeof(struct Seqlist));
    Initlist(SEQA);
    
    size = nondet_unsigned_int();
    
    for (i=0;i<size;i++)
    {
        x = nondet_int();
        InsertList (SEQA,x,i);
        
        printf("SEQA->data[%d] = %d\n", i, SEQA->data[i]);
    }
    
    DeleteList (SEQA,size-1);
    
    for (i=0;i<size-1;i++)
    {
        printf("SEQA->data[%d] = %d\n", i, SEQA->data[i]);
    }
}
