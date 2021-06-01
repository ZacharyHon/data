#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct
{
	char* ch ;
	int length;
}string;

int strAssign(string& string, char* ch);		// 将一个常量字符串赋值给str，成功返回1，否则返回0
void GetNext(string T, int next[]);		// 求模式串的Next[]数组

int main()
{
	string T;
	char ch[] = "0abaabcac";
	strAssign(T, ch);
	int next[MAXSIZE] = { 0 };
	GetNext(T, next);
	for (int i = 1; i < T.length; i++)
		printf("%d ", next[i]);
	return 0;
}

int strAssign(string& string, char* ch)		// 将一个常量字符串赋值给str，成功返回1，否则返回0
{
	//if (string.ch)
	//	free(string.ch);	// 释放原串空间
	int len = 0;
	char* c = ch;
	while (*c)
	{
		++len;
		++c;
	}
	if (len == 0)
	{
		string.ch = NULL;
		string.length = 0;
		return 1;
	}
	else
	{
		string.ch = (char*)malloc(sizeof(char) * (len + 1));		// 多分配一个空间存放串结束字符'\0'
		if (string.ch == NULL)
			return 0;
		else
		{
			c = ch;
			for (int i = 0; i <= len; ++i, ++c)
				string.ch[i] = *c;		// 取等于len的原因是为了把c中最后的'\0'也复制过来
			string.length = len;
			return 1;
		}
	}
}

void GetNext(string T, int next[])		// 求模式串的Next[]数组
{
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T.length)
	{
		if (j == 0 || T.ch[i] == T.ch[j])
			next[++i] = ++j;
		else
			j = next[j];
	}
}

