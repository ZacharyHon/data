#include <stdio.h>

void f(int *&x) // ��ָ���ͱ���������
{
	++x;
} 
int main()
{
	 int a = 1;
	 int *b = &a;
	 printf("%d\n",*b);
	 f(b);
	 printf("%d\n",a);
	 printf("%d\n",*b);  // ִ��f(b)��b����ָ��a���������Ұָ�롣
	 return 0;
} 
