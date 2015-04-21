#include<stdio.h>
#include "sort.h"
void mysort(int a[],int size)
{
 int i=0,j=0,t=0,k=0;
 for (i=1;i<size;i++)
 {
  t=a[i];
  for(j=i-1;((j>=0)&&(t<a[j]));j--)
  a[j+1]=a[j];
  a[j+1]=t; 
 }
 printf("\n\nThe sorted list is : ");
 for(j=0;j<size;j++)
 printf("%d ",a[j]);
 return 0;

}
