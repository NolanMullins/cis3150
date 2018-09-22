/****************************************
 * Nolan Mullins
 * 0939720
 * 2018-09-22
 * cis3150 - A1
 ****************************************/

#include <stdio.h>
#include <stdlib.h>

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
	binTree(str, 0, n, k, m);
}

void printBS(char* str, int len, int n) {
	for (int i=len; i<n; i++)
		str[i]='0';
	printf("%s\n", str);
}

void binTree(char* str, int len, int n, int k, int m) 
{
	int sT=0,sK=0;
	for (int i=0; i<len; i++)
		if (str[i]=='1')
			if (++sK<=k)
				sT+=i+1;
			else 
				break;
	if(sK==k && sT==m)
		printBS(str, len, n);
	if (len == n || sK >= k)
		return;
	str[len]='0';
	binTree(str, len+1, n, k, m);
	str[len]='1';
	binTree(str, len+1, n, k, m);
}