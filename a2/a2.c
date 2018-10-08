/****************************************
 * Nolan Mullins
 * 0939720
 * 2018-10-07
 * cis3150 - A2
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binTree(char* str, int len, int size, int ones, int max, int** m);

void error(char* msg)
{
    printf("%s\n", msg);
    exit(1);
}

int main(int argc, char* argv[]) 
{
    if (argc < 2)
        error("Need filename");
    FILE* f;
    if ((f = fopen(argv[1], "r")) == NULL)
        return -1;

    int n,m,k;
    fscanf(f, "%d", &n);
    fscanf(f, "%d", &m);
    fscanf(f, "%d", &k);

    int** matrix = malloc(n * sizeof(int*));
    for (int a = 0; a < n; a++)
        matrix[a] = malloc(n * sizeof(int));
   
    for (int a = 0; a < m; a++)
    {
        int v1,v2;
        fscanf(f, "%d", &v1);
        fscanf(f, "%d", &v2);
        matrix[v1-1][v2-1] = 1;
        matrix[v2-1][v1-1] = 1;
    }

    fclose(f);

    char str[n+1];
	str[n]='\0';

    int sets = binTree(str, 0, n, 0, k, matrix);

    printf("Sets found: %d\n", sets);

    return 0;
}

int isDomSet(char* str, int len, int size, int** m)
{
    for (int a = 0; a < size; a++)
    {
        if (a < len && str[a] == '1')
            continue;
        int inSet = 0;
        for (int b = 0; b < size; b++)
        {
            if (a==b)
                continue;
            if (b >= len || str[b]=='0')
                continue;
            if (m[a][b]==1)
            {
                //printf("%d is in set since its connected to %d\n", a, b);
                inSet=1;
                break;
            }
        }
        if (inSet == 0)
            return 0;
    }
    return 1;
}

void printBS(char* str, int len, int n) {
	for (int i=len; i<n; i++)
		str[i]='0';
	printf("%s\n\n", str);
}

int binTree(char* str, int len, int size, int ones, int max, int** m)
{
	//if there are the correct amount of 1s checking the summation of the set
	if (max==ones)
    {
        /*printf("\n\n");
        if (isDomSet(str, len, size, m))
        {
            printBS(str,len,size);
            return 1;
        }*/
        return isDomSet(str, len, size, m);
    }

	if (len == size || ones >= max || (size-len)<(max-ones))
		return 0;
	
    int matches = 0;
	str[len]='0';
	matches += binTree(str, len+1, size, ones, max, m);
	str[len]='1';
	matches += binTree(str, len+1, size, ones+1, max, m);
	return matches;
}
