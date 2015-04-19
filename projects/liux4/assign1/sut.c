
#define ListSize 100

#include <stdio.h>
#include <stdlib.h>
#include "sut.h"

void Error(char * message)
{
    printf("Error:%s\n",message);
    exit(1);
}


void InsertList(struct Seqlist *L, int x, int i)
{
    /* 将新结点x插入L所指的顺序表的第i个结点ai的位置上 */
    int j;
    if ( i < 0 || i > L -> length )
        Error("position error");/* 非法位置，退出 */
    
    if ( L->length>=ListSize )
        Error("overflow");
    
    for ( j=L->length-1 ; j >= i ; j --)
        L->data[j+1]=L->data [j];
    
    L->data[i]=x ;
    L->length++ ;
}


void DeleteList ( struct Seqlist *L, int i )
{
    /* 从L所指的顺序表中删除第i个结点ai */
    int j;
    
    if ( i< 0 || i > L-> length-1)
        Error( " position error" ) ;
    
    // Injected Bug
    // Correct: j < L->length
    // Found by --memory-leak-check option. --bounds-check option
    // can also detect here is a bug, but points that the bug is
    // in the body of for-loop.
    for ( j = i+1 ; j <= L-> length ; j++ )
        L->data [ j-1 ]=L->data [ j]; /* 结点前移 */
    
    L-> length-- ; /* 表长减小 */
}


void Initlist(struct Seqlist *L)
{
    L->length=0;
}






