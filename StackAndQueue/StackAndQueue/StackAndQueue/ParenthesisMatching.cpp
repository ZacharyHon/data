#include <stdio.h>
#define MAXSIZE 100

int main() 
{	
	char stack[MAXSIZE];
	int top = -1;
	char sequence[MAXSIZE];
	int length;
	scanf_s("%d", &length);
	scanf_s("%s", sequence, MAXSIZE);
	printf("%s", sequence);
	for (int i = 0; i < length; i++)
	{
		// ƥ�䵽������ֱ����ջ
		if (sequence[i] == '(' || sequence[i] == '[' || sequence[i] == '{')
			stack[++top] = sequence[i];	

		else 
		{
			// ƥ�䵽�����ţ�ջΪ�գ���ƥ��ʧ��
			if (top == -1) 
			{
				printf("ƥ��ʧ�ܡ�");
				return 0;
			}
			char temp = stack[top--];	// ����һ��������
			if( sequence[i] == ')' && temp != '(')
			{
				printf("ƥ��ʧ�ܡ�");
				return 0;
			}
			if (sequence[i] == ']' && temp != '[')
			{
				printf("ƥ��ʧ�ܡ�");
				return 0;
			}
			if (sequence[i] == '}' && temp != '{')
			{
				printf("ƥ��ʧ�ܡ�");
				return 0;
			}

		}
	}
	// ƥ�������ջ�ղ�˵��ƥ��ɹ�
	if (top == -1)
		printf("ƥ��ɹ�");
	else
		printf("ƥ��ʧ�ܡ�");
	return 0;    
}