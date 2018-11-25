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

int binTree(int* bin, int len, int size, int ones, int max, int **m);

int main(int argc, char* argv[])
{
    return 0;
}

int binTree(int* bin, int len, int size, int ones, int max, int **m)
{
	//if there are the correct amount of 1s check for dom set
	if (max == ones)
		if (isDomSet(bin, len, size, m))
		{
			printSet(bin, len, size, ones);
			return 1;
		}

	if (len == size || ones >= max || (size - len) < (max - ones))
		return 0;

	int matches = 0;
	bin[len] = 0;
	if((matches=binTree(bin, len + 1, size, ones, max, m))==1)
		return 1;
	
	bin[len] = 1;
	if ((matches=binTree(bin, len + 1, size, ones + 1, max, m))==1)
		return 1;

	return matches;
}
