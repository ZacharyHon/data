// ĞòÁĞ×óÒÆP¸öÎ»ÖÃ
#include <stdio.h>
#define N 50

void Reverse(int num[], int l, int r)
{
	int temp;
	int i, j;
	for( i=l, j=r; i < j; i++, j--)
	{
		temp = num[i];
		num[i] = num[j];
		num[j] = temp;
	}
}

void MoveLeft(int num[], int n, int p)
{
	if( p <=0 || p > n)
		printf("ERROR\n");
	else
	{
		Reverse(num, 0, p-1);
		Reverse(num, p, n-1);
		Reverse(num, 0, n-1);
	}
} 
int main()
{
	int n[N], length = 0;
	int p;
	scanf_s("%d", &length);
	for(int i=0; i<length; i++)
		scanf_s("%d", &n[i]);
	scanf_s("%d", &p);
	MoveLeft(n, length, p);
	for(int i=0; i<length; i++)
		printf("%d ", n[i]);
	return 0;
}
