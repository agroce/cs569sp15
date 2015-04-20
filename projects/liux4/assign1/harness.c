//
//  harness.c
//  assign1
//
//  Created by LiuXin on 4/18/15.
//  Copyright (c) 2015 apepkuss. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "assert.h"
#include "sut.h"


int nondet_int(); // returns a non-deterministic integer value
unsigned int nondet_unsigned_int(); // returns a non-deterministic unsigned integer value

int main(int argc, const char * argv[])
{
    struct Seqlist *SEQA;
    
    // Initialize a list
    SEQA = (struct Seqlist *)malloc(sizeof(struct Seqlist));
    Initlist(SEQA);
    assert (SEQA->length == 0);
    printf("SEQA->length = %d\n", SEQA->length);
    
    /* Uncommented when use CBMC to check */
    // Set the size of the list
    unsigned int size = nondet_unsigned_int();
    __CPROVER_assume (size <= ListSize);

    /* Commented when use CBMC to check */
//    time_t t;
//    srand((unsigned) time(&t));
//    unsigned int size = rand() % ListSize;
    
    
    unsigned int key = rand() % size;
    //key = size; /* check upper bound */
    //key = 0;    /* check lower bound */

    int val=0, x, i;
    int vals[size-1];
    

    // Insert new data into the list
    for (i=0; i<size; i++)
    {
        /* Uncommented when use CBMC to check */
        x = nondet_int();
        
        /* Commented when use CBMC to check */
        //x = rand()%100;
        
        InsertList (SEQA,x,i);

        if (key == i) {
            val = x;
            printf("SEQA->data[%d]=%d\n", i, SEQA->data[i]);
        } else if (key > i) {
            vals[i] = x;
        } else if (key < i) {
            vals[i-1] = x;
        }
        
        printf("SEQA->data[%d]=%d\n", i, SEQA->data[i]);
    }
    
    for (i=0; i<size-1; i++) {
        printf("vals[%d]=%d\n", i, vals[i]);
    }

    assert(val == SEQA->data[key]);
    printf("key=%d, val=%d, SEQA->data[key]=%d\n", key, val, SEQA->data[key]);

    // Remove a data from the list by the specified index
    DeleteList (SEQA,key);
    assert(size-1 == SEQA->length);
    
    for (i=0;i<size-1;i++)
    {
        assert (vals[i] == SEQA->data[i]);
        printf("SEQA->data[%d]=%d\n", i, SEQA->data[i]);
    }
}
