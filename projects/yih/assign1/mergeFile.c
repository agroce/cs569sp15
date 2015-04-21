#include <stdio.h>
//Give you two files A and B, both have several characters
//1. Merge these two files to a new file C.
//2. The letters in file C should be in alphabet order.

int MergeFile(FILE *fa, FILE *fb, FILE *fc)
{
	int i, j, aNum,cNum;
	char c[160], t, ch;

	if ((fa = fopen("A.txt", "r")) == NULL)
	{
		printf("\n\nFile A cannot be opened\n");
		exit(0);
	}
	printf("\n\nFile A content is :\n");
	for (i = 0; (ch = fgetc(fa)) != EOF; i++)
	{
		c[i] = ch;
		putchar(c[i]);
	}
	fclose(fa);
	aNum = i;
	printf("\naNum = %d", aNum);

	if ((fb = fopen("B.txt", "r")) == NULL)
	{
		printf("\n\nFile B cannot be opened\n");
		exit(0);
	}
	printf("\n\nFile B content is :\n");
	for (i = aNum; (ch = fgetc(fb)) != EOF; i++)
	{
		c[i] = ch;
		putchar(c[i]);
	}
	fclose(fb);
	cNum = i;
	printf("\nbNum = %d", cNum - aNum);


	for (i = 0; i < cNum; i++)
	{
		for (j = i + 1; j < cNum; j++)
		{
			if (c[i] > c[j])
			{
				t = c[i];
				c[i] = c[j];
				c[j] = t;
			}
		}
	}

	printf("\n\nFile C content is:\n");
	fc = fopen("C.txt", "w");
	for (i = 0; i < cNum; i++)
	{
		putc(c[i], fc);
		putchar(c[i]);
	}
	fclose(fc);
	printf("\ncNum = %d", cNum);
	return 1;
}



