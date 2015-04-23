#include <stdio.h>
#include "sort.h"
#include <assert.h>



int nondet_int();
unsigned int nondet_unsigned_int();

int array[SIZE];

int main(){
	

int i,j,x,y,v;

int rc=0, ac=0;
unsigned int s = nondet_unsigned_int();
__CPROVER_assume(s <+ SIZE);

int v=nondet_int();
printf("LOG: size = %u, value=%d\n", SIZE, v);
for(i=0; i<SIZE, i++){
	x=nondet_int();
	printf("LOG: array[%d] = %d\n", i, x);
	array[i] = x;

	if(x==v){
		rc++;
	}
}
sort(array,0,SIZE-1);
printf("LOG: sorted array A \n");

//make sure all elements are not the same value
	for (i=0;i<SIZE;i++)
	{
		for(j=i+1;j<SIZE;j++){
		if(array[i]==array[j])
		count++;
		}
		__CPROVER_assume(SIZE!=count);
	}

if(SIZE > 0){
	y=array[0];
	if(array[0] == v){
		ac++;
	}
}


for (i = 1; i < SIZE; i++)
	{
		assert(array[i] >= y)

		if(array[i]==v){
			ac++;
		}
		y=array[i];

	}	
	printf("LOG Ref count =%d, A.count = %d\n",rc,ac);
	assert(rc==ac);

}
