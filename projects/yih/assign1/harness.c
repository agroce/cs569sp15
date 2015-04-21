#include <stdio.h> 
#include <io.h>
#include <assert.h>

char a[SIZE1];
char b[SIZE2];

char nondet_char(); //function that returns an arbitrary char.
unsigned int nondet_unsigned_int(); //function that returns an arbitrary unsigned integer value.

int main()
{
	char xchar;
	char ychar;
	int i, j, k;
	char c[SIZE1 + SIZE2 + 5];
	int csize = SIZE1 + SIZE2 + 5;
	FILE *fa, *fb, *fc;
	unsigned int s1 = nondet_unsigned_int(); //s is an arbitrary unsigned_int
	unsigned int s2 = nondet_unsigned_int(); //s is an arbitrary unsigned_int
	__CPROVER_assume(s1 <= SIZE1); // s is used to loop for a[],so assume s<=SIZE
	__CPROVER_assume(s2 <= SIZE2); // s is used to loop for a[],so assume s<=SIZE

	printf("s1 = %d,s2 = %d", s1, s2);

	// randomly set characters to A.txt
	if ((fa = fopen("A.txt", "wt+")) == NULL)
	{
		printf("\n\nFile A cannot be opened\n");
		exit(0);
	}
	for (i = 0; i < s1; i++)
	{
		xchar = nondet_char(); //v is an arbitrary int
		a[i] = xchar;
		printf(" i= %d,xchar= %c\n", i, a[i]);
	}
	fputs(a, fa);

	// randomly set characters to B.txt
	if ((fb = fopen("B.txt", "wt+")) == NULL)
	{
		printf("\n\nFile B cannot be opened\n");
		exit(0);
	}
	for (j = 0; j < s2; j++)
	{
		ychar = nondet_char(); //v is an arbitrary int
		b[j] = ychar;
		printf(" j= %d,ychar= %c\n", j, b[j]);
	}
	fputs(b, fb);

	// set C.txt and Merge A and B to C
	if ((fc = fopen("C.txt", "wt+")) == NULL)
	{
		printf("\n\nFile C cannot be opened\n");
		exit(0);
	}
	fclose(fa);
	fclose(fb);

	MergeFile(fa, fb, fc);

	//open C.txt and check two things
	//1. The letters in file C should be in alphabet order.
	//2. The character number of C is sum of A and B
	if ((fc = fopen("C.txt", "r")) == NULL)
	{
		printf("\n\nFile C cannot be opened\n");
		exit(0);
	}
	fgets(c, csize, fc);
	char tail = c[0];
	for (k = 0; c[k] != '\0'; k++)
	{
		printf(" k= %d,cchar= %c,tail = %c\n", k, c[k], tail);
		assert(c[k] >= tail);//check whether in alphabet order.
		tail = c[k];
	}

	if (c[k] == '\0')
	{
		assert(k == SIZE1 + SIZE2);//check total number
	}

	fclose(fc);
	return 1;
}