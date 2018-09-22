/****************************************
 * Nolan Mullins
 * 0939720
 * 2018-09-22
 * cis3150 - A1
 ****************************************/

#define _POSIX_C_SOURCE 199309L
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* 
  9.[6 marks]Program in C. Write a simple recursive function (as outlined in class) 
  that generates(lists) all binary strings of lengthnwith exactly k 1s in lexicographic 
  order.  Use your functionto determine how many subsets off {1,2,3,...,n} of size k 
  have elements that sum to exactlym. For instance when n=6, k=3, and m=8, the subset 
  {1,3,4} (which corresponds tothe length n=6 binary string 101100) has k=3 elements 
  and sums to m=8
*/

typedef struct data 
{
	char* str;
	int len;
	int n;
	int k;
	int m;
	int sK;
	int* matches;
} BinData;

int binTree(char* str, int len, int n, int k, int m, int sK);

int threads = 16;
int threadsInUse = 1;

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
	int found = binTree(str, 0, n, k, m, 0);
	clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	printf("time taken: %lf\n", elapsed);
	printf("matches found: %d\n", found);
}

void printBS(char* str, int len, int n) {
	for (int i=len; i<n; i++)
		str[i]='0';
	printf("%s\n", str);
}

//helper functions allowing threads to start solving sub sections of the tree
void* threadBinStart(void* data) {
	BinData* d = (BinData*)data;
	*(d->matches) = binTree(d->str, d->len, d->n, d->k, d->m, d->sK);
}

int binTree(char* str, int len, int n, int k, int m, int sK) 
{
	int sT=0;
	//if there are the correct amount of 1s checking the summation of the set
	if (sK==k)
		for (int i=0; i<len; i++)
			if (str[i]=='1')
					sT+=i+1;
	//check if its the correct summation
	if(sK==k && sT==m) 
	{
		//printBS(str, len, n);
		return 1;
	}
	if (len == n || sK >= k || (n-len)<(k-sK))
		return 0;
	
	pthread_t thread;
	char str2[n+1];
	int flag = 0;
	int matches = 0;
	int threadMatches = 0;
	//if there is an extra thread available divide the work
	if (threadsInUse < threads) 
	{
		BinData data;
		strcpy(str2, str);
		str2[len]='0';
		data.str = str2;
		data.len = len+1;
		data.n = n;
		data.k = k;
		data.m = m;
		data.sK = sK;
		data.matches = &threadMatches;
		if(!pthread_create(&thread, NULL, threadBinStart, &data))
		{
			threadsInUse++;
			flag = 1;
		}
	} 
	else
	{
		str[len]='0';
		matches += binTree(str, len+1, n, k, m, sK);
	}
	//solve the other side of the tree
	str[len]='1';
	matches += binTree(str, len+1, n, k, m, sK+1);
	if (flag) 
	{
		pthread_join(thread, NULL);
		matches += threadMatches;
		threadsInUse--;
	}
	return matches;
}

