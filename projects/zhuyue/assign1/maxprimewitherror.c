#include "prime.h"
#include <math.h>


int maxprime(int a)
{
	int i;
	if (1<a<4)
		return a;
	else if (a <= 1)
	{
		printf("there is no prime number under the given number");
	    return 0;
	}
	else
	for (i = a; i >= 1; i--)
	{

		if (odd(i) == 1)
		{
			if (prime(i) == 1)
				return i;		
		}

		else continue;
	}
}

int prime(int a)
{
	int i;
	int j = (int)sqrt(a);
	if (a <= 1)
		return 0;
	for (i = j; i > 1; i--)
	{
		if (a % i == 0)
			return 0;
		else continue;
	}
	return 1;
}

int odd(int a)
{
	if (a < 0||a % 2 == 0)
		return 0;

	else return 1;

}