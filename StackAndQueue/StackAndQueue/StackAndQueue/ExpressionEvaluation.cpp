#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
/*
���԰���
11
1*(2+3)-6/2
15
(2+3)/5*9-4*2+2
17
2+3-4+3*2-2*(1+2)
*/

// ��Ϊ���ַ�ת�����ֵļ򵥴���ԭ���ʽ��ÿ�����ֽ�����һλ(0-9)
char* InfixToSuffix(char infix[], int length, int &len);	// ����׺���ʽת��Ϊ��׺���ʽ
char* InfixToPrefix(char infix[], int length, int& len);	// ����׺���ʽת��Ϊǰ׺���ʽ
char* Reverse(char ch[], int len);		// ���ַ����鷴ת
int ComputeSuffix(char infix[], int length);		// ͨ����׺���ʽ�����׺���ʽ��ֵ
int ComputePrefix(char infix[], int length);		// ͨ����׺���ʽ����ǰ׺���ʽ��ֵ
int Compute(char infix[], int length);		// ��׺���ʽ�ļ��㣬ͨ����׺ת��׺����׺��ֵ�����㷨�Ľ��ʵ�֡�

int Calculation(int numL, int numR, char currentOperator);		// ͨ������������������������ֵ

int main()
{
	char infix[MAXSIZE];
	int length;
	int len;
	scanf_s("%d", &length);
	scanf_s("%s", infix, MAXSIZE);
	int ans1 = ComputeSuffix(infix, length);
	int ans2 = ComputePrefix(infix, length);
	int ans3 = Compute(infix, length);
	printf("��-��:%s = %d\n", infix, ans1);
	printf("��-ǰ:%s = %d\n", infix, ans2);
	printf("��:%s = %d\n", infix, ans3);
	return 0;
}

/*
*	��������ջ���������Ѿ�ȷ������˳��ķ��ţ�����ֱ�Ӽ��뵽���ʽ�С�
	��׺���ʽ��ת����
		����׺���ʽ������ɨ�裺(������ɨ����ص㣬�ȳ��ֵ�+-�����ȼ��ض����ں���ֵ�+-)
			case1�����������ֱ�Ӽ��뵽��ʾ�У�
			case2�������������Ҳֱ�Ӽ�����ʽ�У�
			case3������Ǽӡ����ţ�
						case a�������ջΪ�գ���ֱ����ջ��
						case b�������ջ��Ϊ�գ���Ϊ�����ȼ���ͣ��ʵ���ջ�����е��������ֱ��ջ�ջ���������(����Ȼ�󽫸������ֱ����ջ��
			case4������ǳˡ����ţ�
						case a�������ջΪ�գ���ֱ����ջ��
						case b�������ջ��Ϊ�գ���Ϊ�����ȼ�����ջ�еļӼ��ţ�������ջ�еĳ˳���,�ʵ���ջ�е�Ԫ�ط���ֱ��ջ�ջ�������"("||"+"||"-,Ȼ���������ջ
			case5������������ţ�����ջ�����е��������ֱ��������(��Ϊֹ��
		��󣬽�ջ�����е���������뵽���ʽ�С�

*/
char* InfixToSuffix(char infix[],int length, int &len)
{
	char stack[MAXSIZE];		// ������ʱ������ȷ������˳��������
	char suffix[MAXSIZE];		// ��׺���ʽ
	int top = -1;
	len = 0;
	for (int i = 0; i < length; i++)
	{
		if (infix[i] >= '0' && infix[i] <= '9')
			suffix[len++] = infix[i];
		else if (infix[i] == '(')
			stack[++top] = infix[i];
		else if (infix[i] == ')')
		{
			while ( stack[top] != '(' )
				suffix[len++] = stack[top--];
			--top;	// ����������
		}
		else if (infix[i] == '+' || infix[i] == '-')
		{
			while ( top != -1 &&  stack[top] != '(' )
			{
				suffix[len++] = stack[top--];
			}
			stack[++top] = infix[i];
		}
		else if (infix[i] == '*' || infix[i] == '/')
		{
			while (top != -1 && stack[top] != '(' && stack[top] != '+' && stack[top] != '-')
			{
				suffix[len++] = stack[top--];
			}
			stack[++top] = infix[i];
		}
	}
	while (top != -1)
	{
		suffix[len++] = stack[top--];
	}
	suffix[len] = '\0';
	// printf("%s", suffix);
	return suffix;
}

char* InfixToPrefix(char infix[], int length, int& len)
{
	char stack[MAXSIZE];		// ������ʱ������ȷ������˳��������
	char prefix[MAXSIZE];		// ��׺���ʽ
	int top = -1;
	len = 0;
	for (int i = length-1; i >= 0; i--)
	{
		if (infix[i] >= '0' && infix[i] <= '9')
			prefix[len++] = infix[i];
		else if (infix[i] == ')')
			stack[++top] = infix[i];
		else if (infix[i] == '(')
		{
			while (stack[top] != ')')
				prefix[len++] = stack[top--];
			--top;	// ��������������
		}
		else if (infix[i] == '+' || infix[i] == '-')
		{
			while (top != -1 && stack[top] != ')' && stack[top] != '+' && stack[top] != '-')
			{
				prefix[len++] = stack[top--];
			}
			stack[++top] = infix[i];
		}
		else if (infix[i] == '*' || infix[i] == '/')
		{
			stack[++top] = infix[i];
		}
	}
	while (top != -1)
	{
		prefix[len++] = stack[top--];
	}
	prefix[len] = '\0';
	char *prefixReal = Reverse(prefix, len);
	return prefixReal;
}

int ComputeSuffix(char infix[], int length)
{
	int len = 0;
	char* suffix = InfixToSuffix(infix, length, len);
	int stack[MAXSIZE];
	int top = -1;
	for (int i = 0; i < len; i++)
	{
		if (suffix[i] >= '0' && suffix[i] <= '9')
			stack[++top] = suffix[i] - '0';
		else
		{
			if (suffix[i] == '+')
			{
				int addR = stack[top--];		// �ȳ�ջ�����Ҳ�����
				int addL = stack[top--];
				stack[++top] = addL + addR;
			}
			else if (suffix[i] == '-')
			{
				int minR = stack[top--];		// �ȳ�ջ�����Ҳ�����
				int minL = stack[top--];
				stack[++top] = minL - minR;
			}
			else if (suffix[i] == '*')
			{
				int mulR = stack[top--];		// �ȳ�ջ�����Ҳ�����
				int mulL = stack[top--];
				stack[++top] = mulL * mulR;
			}
			else if (suffix[i] == '/')
			{
				int divR = stack[top--];		// �ȳ�ջ�����Ҳ�����
				if (divR == 0)
				{
					printf("ERROR-/0\n");
					return 0;
				}
				int divL = stack[top--];
				stack[++top] = int(divL / divR);
			}
			else
			{
				printf("%c,ERROR\n", suffix[i]);
				return 0;
			}
		}
	}
	return stack[top];
}

int ComputePrefix(char infix[], int length)
{
	int len = 0;
	char* prefix = InfixToPrefix(infix, length, len);
	int stack[MAXSIZE];
	int top = -1;
	for (int i = len-1; i >=0; i--)
	{
		if (prefix[i] >= '0' && prefix[i] <= '9')
			stack[++top] = prefix[i] - '0';
		else
		{
			if (prefix[i] == '+')
			{
				int addL = stack[top--];		// �ȳ�ջ�����������
				int addR = stack[top--];
				stack[++top] = addL + addR;
			}
			else if (prefix[i] == '-')
			{
				int minL = stack[top--];		// �ȳ�ջ�����������
				int minR = stack[top--];
				stack[++top] = minL - minR;
			}
			else if (prefix[i] == '*')
			{
				int mulL = stack[top--];		// �ȳ�ջ�����������
				int mulR = stack[top--];
				stack[++top] = mulL * mulR;
			}
			else if (prefix[i] == '/')
			{
				int divL = stack[top--];		// �ȳ�ջ�����������
				int divR = stack[top--];
				if (divR == 0)
				{
					printf("ERROR-/0\n");
					return 0;
				}
				stack[++top] = int(divL / divR);
			}
			else
			{
				printf("%c,ERROR\n", prefix[i]);
				return 0;
			}
		}
	}
	return stack[top];
}

int Compute(char infix[], int length)
{
	int numStack[MAXSIZE];		// ������ջ
	char operatorStack[MAXSIZE];		// �����ջ
	int numTop = -1;
	int operatorTop = -1;
	for (int i = 0; i < length; i++)
	{
		// ����ǲ�������ֱ���������ջ
		if (infix[i] >= '0' && infix[i] <= '9')
			numStack[++numTop] = infix[i] - '0';
		else if (infix[i] == '(')
			operatorStack[++operatorTop] = infix[i];
		else if (infix[i] == ')')
		{
			while (operatorStack[operatorTop] != '(')
			{
				int numR = numStack[numTop--];
				int numL = numStack[numTop--];
				char currentOperator = operatorStack[operatorTop--];
				numStack[++numTop] = Calculation(numL, numR, currentOperator);		// ��������ѹ��ջ��
			}
			--operatorTop;	// ����������
		}
		else if (infix[i] == '+' || infix[i] == '-')
		{
			while (operatorTop != -1 && operatorStack[operatorTop] != '(')
			{
				int numR = numStack[numTop--];
				int numL = numStack[numTop--];
				char currentOperator = operatorStack[operatorTop--];
				numStack[++numTop] = Calculation(numL, numR, currentOperator);		// ��������ѹ��ջ��
			}
			operatorStack[++operatorTop] = infix[i];
		}
		else if (infix[i] == '*' || infix[i] == '/')
		{
			while (operatorTop != -1 && operatorStack[operatorTop] != '(' && operatorStack[operatorTop] != '+' && operatorStack[operatorTop] != '-')
			{
				int numR = numStack[numTop--];
				int numL = numStack[numTop--];
				char currentOperator = operatorStack[operatorTop--];
				numStack[++numTop] = Calculation(numL, numR, currentOperator);		// ��������ѹ��ջ��
			}
			operatorStack[++operatorTop] = infix[i];
		}
	}
	while (operatorTop != -1)
	{
		int numR = numStack[numTop--];
		int numL = numStack[numTop--];
		char currentOperator = operatorStack[operatorTop--];
		numStack[++numTop] = Calculation(numL, numR, currentOperator);		// ��������ѹ��ջ��
	}
	return numStack[numTop];
}

int Calculation(int numL, int numR, char currentOperator)
{
	switch (currentOperator)
	{
	case '+':
		return numL + numR;
	case '-':
		return numL - numR;
	case '*':
		return numL * numR;
	case '/':
		if (numR == 0)
			exit(-1);
		else
			return numL / numR;
	default:
		exit(-1);
	}
}

char* Reverse(char ch[], int len)
{
	char temp;
	for (int i = 0, j = len - 1; i < j; i++, j--)
	{
		temp = ch[i];
		ch[i] = ch[j];
		ch[j] = temp;
	}
	return ch;
}