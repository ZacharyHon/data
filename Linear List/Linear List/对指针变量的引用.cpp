#include <stdio.h>

void f(int *&x) // 对指针型变量的引用
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
	 printf("%d\n",*b);  // 执行f(b)后，b不再指向a，可能造成野指针。
	 return 0;
} 
