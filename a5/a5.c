/****************************************
 * Nolan Mullins
 * 0939720
 * 2018-10-29
 * cis3150 - A3
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define display 1 

int binTree(int* bin, int len, int size, int ones);
int isSumSet(int* bin, int len, int size);
void printBS(int* bin, int len, int n);
void printSet(int* bin, int len, int n);

int* arr;
int tmp2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int tmp3[] = {7,9,11,15,24,72,90,107,125};
int tmp[] = {1, 2, 3, 4};

int main(int argc, char* argv[])
{
	int size, matches = 0;
	if (argc > 1)
	{
		size = atoi(argv[1]);
		arr = malloc(sizeof(int)*size);
		time_t t;
		srand((unsigned)time(&t));
		for (int a = 0; a < size; a++)
			arr[a] = rand() % size + 1;
	}
	else {
		size = 4;
		arr = malloc(sizeof(int)*size);
		for (int a = 0; a < size; a++)
			arr[a] = tmp[a];
	}
	int* bin = malloc(sizeof(int)*size);
	memset(bin, 0, sizeof(bin));
	//if (display)
		//printSet(bin, size, size);
	//Timing
	struct timeval  start, finish;
    double elapsed;

    gettimeofday(&start, NULL);	

	int preCheck = 0;
	for (int a = 0; a < size; a++)
		preCheck += arr[a];
	if (preCheck % 2 == 1)
		printf("odd sum\n");
	else
		matches = binTree(bin, 1, size, 0);

	gettimeofday(&finish, NULL);
    elapsed = (double) (finish.tv_sec - start.tv_sec);
    elapsed += (double) (finish.tv_usec - start.tv_usec) / 1000000.0 ;
    //elapsed *= 1000;

    printf("time taken: %.5lfs\n", elapsed);
	printf("matches: %d\n", matches);
	free(arr);
	free(bin);
    return 0;
}

int isSumSet(int* bin, int len, int size)
{
	int a, sumA=0, sumB=0;
	for (a = 0; a < size; a++)
	{
		if (bin[a] == 1 && a < len)
			sumA += arr[a];
		else 
			sumB += arr[a];
	}
	if (sumB == sumA)
		return 1;
	else if (sumA > sumB)
		return -1;
	return 0;
}

void printBS(int* bin, int len, int n)
{
	for (int i = 0; i < len; i++)
		printf("%d",bin[i]);
	for (int i = len; i < n; i++)
		printf("0");
	printf("\n");
}

void printSet(int* bin, int len, int n)
{
	printf("{");
	for (int i = 0; i < n; i++)
		if (bin[i] == 1 && i < len)
			printf(" %d",arr[i]);
	printf("} == {");
	for (int i = 0; i < n; i++)
		if (bin[i] == 0 || i >= len)
			printf(" %d",arr[i]);
	printf("}\n");
}

int binTree(int* bin, int len, int size, int ones)
{
	//if there are the correct amount of 1s check for dom set
	int test = isSumSet(bin, len, size);
	if (test == 1)
	{
		//printBS(bin, len, size);
		if (display)
		{
			printBS(bin, len, size);
			printSet(bin, len, size);
		}
		return 1;
	}
	
	if (len == size || test < 0 || ones == size/2)
		return 0;

	int matches = 0;
	bin[len] = 0;
	matches+=binTree(bin, len + 1, size, ones);
	
	bin[len] = 1;
	matches+=binTree(bin, len + 1, size, ones + 1);

	return matches;
}
