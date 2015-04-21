#include<stdio.h>
#include "mybinsearch.h"

int mybinsearch(int a[], int size, unsigned int m){

     int l, u, mid, temp;

     for(int i=0; i<size;i++){

        for(int j=i+1;j<size;j++){

	if(a[i]>a[j]){
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;

	}

        }

     }


     l=0,u=size-1;

     while(l<=u){
         mid=(l+u)/2;
         if(m==a[mid]){
             return 1;
             break;
         }
         else if(m<a[mid]){
             u=mid-1;
         }
         else if(m>a[mid])
             l=mid+1;
	
    }

return 0;
}



