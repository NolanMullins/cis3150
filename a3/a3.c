/****************************************
 * Nolan Mullins
 * 0939720
 * 2018-10-07
 * cis3150 - A2
 ****************************************/

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define display 1 
//typedef int (*fptr)(int* bin, int len, int n, int ones);

int binTree(int* bin, int len, int size, int ones, int max, int **m, int* sets);
void printBS(int* bin, int len, int n);

int isDomSet(int* bin, int len, int size, int** m);
int isClique(int* bin, int len, int size, int** m);
int isIndependent(int* bin, int len, int size, int** m);
int isVertexCover(int* bin, int len, int size, int** m);

int (*func[4])(int* bin, int len, int size, int** m) = {isDomSet, isClique, isIndependent, isVertexCover};

void error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

int* e;

int main(int argc, char *argv[])
{
	if (argc < 2)
		error("Need filename");
	FILE *f;
	if ((f = fopen(argv[1], "r")) == NULL)
		error("Could not open file");

	int n, m, k;
	fscanf(f, "%d %d %d", &n, &m, &k);

	int **matrix = malloc(n * sizeof(int *));
	for (int a = 0; a < n; a++)
		matrix[a] = malloc(n * sizeof(int));

	int v1, v2;
	for (int a = 0; a < m; a++)
	{
		fscanf(f, "%d", &v1);
		fscanf(f, "%d", &v2);
		matrix[v1 - 1][v2 - 1] = 1;
		matrix[v2 - 1][v1 - 1] = 1;
	}
	fclose(f);
	
	if (display)
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
				printf("%d ", matrix[a][b]);
			printf("\n");
		}
	
	//Dominating, independent, clique, cover
	int sets[4];
	memset(sets, 0, sizeof(int)*4);

	int bin[n];
	e = malloc(n*sizeof(int));
	int numEmpty = 0;

	struct timespec start, finish;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);
	//calc empty vertices
	for (int a = 0; a < n; a++)
	{
		e[a] = 1;
		for (int b = 0; b < n; b++) 
			if (matrix[a][b] == 1)
			{
				e[a] = 0;
				break;
			}
		if (e[a]==1)
			numEmpty++;
	}

	if (numEmpty > k)
	{
		sets[0] = -1;
		sets[2] = -1;
	}

	binTree(bin, 0, n, 0, k, matrix, sets);
	clock_gettime(CLOCK_MONOTONIC, &finish);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	//printf("No dominating set of size k=%d:    ", k);
	for (int i = 0; i < 4; i++)
	{
		printf("(%c) ", 'a'+i);
		if (sets[i])
			printf(" yes\t");
		else
			printf(" no\t");
	}
	printf("\n");
	printf("Completed in %.5lfs\n", elapsed);

	for (int a = 0; a < n; a++)
		free(matrix[a]);
	free(matrix);
	free(e);
	return 0;
}

int isDomSet(int* bin, int len, int size, int **m)
{
	for (int a = size-1; a >= 0; a--)
	{
		//check if it is part of set
		if (a < len && bin[a] == 1)
			continue;
		//is vert empty
		if (e[a]==1)
			return 0;
		int inSet = 0;
		//check for edges into dom set
		for (int b = 0; b < size; b++)
		{
			if (a == b)
				continue;
			if (b >= len || bin[b] == 0)
				continue;
			if (m[a][b] == 1)
			{
				inSet = 1;
				break;
			}
		}
		if (inSet == 0)
			return 0;
	}
	return 1;
}

int isClique(int* bin, int len, int size, int** m)
{
	for (int a = 0; a < size; a++)
	{
		if (a >= len || bin[a] == 0)
			continue;
		for (int b = 0; b < size; b++)
		{
			if (b >= len || bin[b] == 0 || a==b)
				continue;
			//check if 2 verticies are connected
			if (m[a][b] != 1)
				return 0;
		}
	}
	return 1;
}

int isIndependent(int* bin, int len, int size, int** m)
{
	return 0;
}

int isVertexCover(int* bin, int len, int size, int** m)
{
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

void printSet(int* bin, int len, int n, int ones, int type)
{
	printf("(%c) size k=%d {", 'a'+type ,ones);
	int a = 0;
	while(a < len)
		if (bin[a++]==1)
		{
			printf("%d",a-1);
			break;
		}
	for (a; a < len; a++)
		if (bin[a]==1)
			printf(",%d",a);
	printf("}\n");
}

int binTree(int* bin, int len, int size, int ones, int max, int **m, int* sets)
{
	//if there are the correct amount of 1s check for dom set
	if (max == ones)
		for (int i = 0; i < 4; i++)
			if (sets[i] == 0)
			{
				sets[i] = (*func[i])(bin, len, size, m);
				if (sets[i] == 1)
					printSet(bin, len, size, ones, i);
			}

	if (len == size || ones >= max || (size - len) < (max - ones))
		return 0;

	bin[len] = 0;
	if(binTree(bin, len + 1, size, ones, max, m, sets))
		return 1;
	bin[len] = 1;
	if (binTree(bin, len + 1, size, ones + 1, max, m, sets))
		return 1;
	return 0;
}
