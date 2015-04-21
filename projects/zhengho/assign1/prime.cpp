#include "stdio.h"
#include "malloc.h"
#include "prime.h"


int isPrime(int number)
{
	unsigned int i;	
	if(number==1||number<=0) 
		return 0;	
	for(i=2;i<number;i++)	
	{		
		if(number%i==0) 
			return 0;	
	}	
	return 1;
}


void jsValue(int initial_no, int size,int xx[])
{	
	int i,j;	
	int temp;	
	for(i=0;i<size;i++)	
	{		
		while(!isPrime(initial_no))
		{
			initial_no++;
		}
		xx[i]=initial_no;
		initial_no++;	

	}
	//reverse the value
	for(i=size-1;i>=0;i--)
		for(j=i;j>=0;j--) //here is the bug the right should be j>=0
		{
			if(xx[j]<xx[i])
			{
				temp=xx[i];				
				xx[i]=xx[j];
				xx[j]=temp;
			}
		}

		i=0;
		while(i<size)
		{
			printf("a[%d]=%d\n",i,xx[i]);
			i++;
		}
	return;
}



void writeDat()
{	
	int *array;	
	int i;
	int initial_no=-10;
	int size=5;	
	array=(int *)malloc(sizeof(int)*size);	
	jsValue(initial_no,size,array);	
	for(i=0;i<size;i++)	
	{		
		printf("%d ",array[i]);	
	}	
	printf("\n");	
	return;
}


void main()
{
		
	writeDat();

}


