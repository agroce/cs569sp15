#include <stdio.h>
#include <math.h>
#include "primes.h"


int ex(int *a, int n, int cp) {
	int i;
	for(i = 0; i < n; i++) {
		if(cp == a[i]) return 0;
	}
	return 1;
}

void markCom(int *comArray, int n, int pn) {
	int i;
	for(i = 2*pn; i <= n; i += pn) {
		if(ex(comArray, n, i)) comArray[i-1] = i;
	}
}

int primes(int p[], int n) {
	printf("1 is a special number that is neither prime nor composite...\n");
	int k = 1;
	int pos = 0;
	int m;
	int c[n];
	int i;
	for(i = 0; i < n; c[i++] = 0);
	while(k <= sqrt(n)) {
		for(i = 2; i <= n; i++) {
			if(i > k && ex(c, n, i)) {
				m = i;
				p[pos++] = m;
				markCom(c, n, m);
			}
		}
		k = m;
	}
	return pos;
}

// int main (int argc, char const *argv[])
// {
// 	int n, i;
// 	printf("Please input a number: ");
// 	scanf("%d", &n);
// 	int p[n];
// 	int num = primes(p, n);
// 	printf("All primes are as following: ");
// 	for(i = 0; i < num; printf("%d ", p[i++]));
// 	printf("\n\n");
// 	return 0;
// }
