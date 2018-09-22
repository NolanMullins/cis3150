/****************************************
 * Nolan Mullins
 * 0939720
 * 2018-09-22
 * cis3150 - A1
 ****************************************/

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 
  9.[6 marks]Program in C. Write a simple recursive function (as outlined in class) 
  that generates(lists) all binary strings of lengthnwith exactly k 1s in lexicographic 
  order.  Use your functionto determine how many subsets off {1,2,3,...,n} of size k 
  have elements that sum to exactlym. For instance when n=6, k=3, and m=8, the subset 
  {1,3,4} (which corresponds tothe length n=6 binary string 101100) has k=3 elements 
  and sums to m=8
*/

void binTree(char* str, int len, int n, int k, int m );

int main(int argc, char* argv[]) 
{
	if (argc < 4) 
		return 0;

	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	int m = atoi(argv[3]);

	char str[n+1];
	str[n]='\0';

	struct timespec start, finish;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);
	binTree(str, 0, n, k, m);
	clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	printf("time taken: %lf\n", elapsed);
}

void printBS(char* str, int len, int n) {
	for (int i=len; i<n; i++)
		str[i]='0';
	printf("%s\n", str);
}

void binTree(char* str, int len, int n, int k, int m) 
{
	int sT=0,sK=0;
	if (len >= k)
		for (int i=0; i<len; i++)
			if (str[i]=='1')
				if (++sK<=k)
					sT+=i+1;
				else 
					break;
	if(sK==k && sT==m)
		printBS(str, len, n);
	if (len == n || sK >= k || (n-len)<(k-sK))
		return;
	str[len]='0';
	binTree(str, len+1, n, k, m);
	str[len]='1';
	binTree(str, len+1, n, k, m);
}
