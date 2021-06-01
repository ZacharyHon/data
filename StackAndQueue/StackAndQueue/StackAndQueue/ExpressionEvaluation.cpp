#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
/*
测试案例
11
1*(2+3)-6/2
15
(2+3)/5*9-4*2+2
17
2+3-4+3*2-2*(1+2)
*/

// 因为对字符转换数字的简单处理，原表达式中每个数字仅能有一位(0-9)
char* InfixToSuffix(char infix[], int length, int &len);	// 将中缀表达式转换为后缀表达式
char* InfixToPrefix(char infix[], int length, int& len);	// 将中缀表达式转换为前缀表达式
char* Reverse(char ch[], int len);		// 将字符数组反转
int ComputeSuffix(char infix[], int length);		// 通过中缀表达式计算后缀表达式的值
int ComputePrefix(char infix[], int length);		// 通过中缀表达式计算前缀表达式的值
int Compute(char infix[], int length);		// 中缀表达式的计算，通过中缀转后缀、后缀求值两个算法的结合实现。

int Calculation(int numL, int numR, char currentOperator);		// 通过操作符计算两个操作数的值

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
	printf("中-后:%s = %d\n", infix, ans1);
	printf("中-前:%s = %d\n", infix, ans2);
	printf("中:%s = %d\n", infix, ans3);
	return 0;
}

/*
*	理解运算符栈弹出的是已经确定运算顺序的符号，将其直接加入到表达式中。
	后缀表达式的转换：
		将中缀表达式从左到右扫描：(从左到右扫描的特点，先出现的+-的优先级必定高于后出现的+-)
			case1：如果是数字直接加入到表示中；
			case2：如果是左括号也直接加入表达式中；
			case3：如果是加、减号，
						case a：运算符栈为空，则直接入栈；
						case b；运算符栈不为空，因为其优先级最低，故弹出栈中所有的运算符，直到栈空或者遇到“(”，然后将该运算符直接入栈。
			case4：如果是乘、除号，
						case a：运算符栈为空，则直接入栈；
						case b：运算符栈不为空，因为其优先级高于栈中的加减号，但低于栈中的乘除号,故弹出栈中的元素符，直到栈空或者遇到"("||"+"||"-,然后将运算符入栈
			case5：如果是右括号，弹出栈中所有的运算符，直到遇到“(”为止。
		最后，将栈中所有的运算符加入到表达式中。

*/
char* InfixToSuffix(char infix[],int length, int &len)
{
	char stack[MAXSIZE];		// 保存暂时还不能确定运算顺序的运算符
	char suffix[MAXSIZE];		// 后缀表达式
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
			--top;	// 弹出左括号
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
	char stack[MAXSIZE];		// 保存暂时还不能确定运算顺序的运算符
	char prefix[MAXSIZE];		// 后缀表达式
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
			--top;	// 弹出右括号括号
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
				int addR = stack[top--];		// 先出栈的是右操作数
				int addL = stack[top--];
				stack[++top] = addL + addR;
			}
			else if (suffix[i] == '-')
			{
				int minR = stack[top--];		// 先出栈的是右操作数
				int minL = stack[top--];
				stack[++top] = minL - minR;
			}
			else if (suffix[i] == '*')
			{
				int mulR = stack[top--];		// 先出栈的是右操作数
				int mulL = stack[top--];
				stack[++top] = mulL * mulR;
			}
			else if (suffix[i] == '/')
			{
				int divR = stack[top--];		// 先出栈的是右操作数
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
				int addL = stack[top--];		// 先出栈的是左操作数
				int addR = stack[top--];
				stack[++top] = addL + addR;
			}
			else if (prefix[i] == '-')
			{
				int minL = stack[top--];		// 先出栈的是左操作数
				int minR = stack[top--];
				stack[++top] = minL - minR;
			}
			else if (prefix[i] == '*')
			{
				int mulL = stack[top--];		// 先出栈的是左操作数
				int mulR = stack[top--];
				stack[++top] = mulL * mulR;
			}
			else if (prefix[i] == '/')
			{
				int divL = stack[top--];		// 先出栈的是左操作数
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
	int numStack[MAXSIZE];		// 操作数栈
	char operatorStack[MAXSIZE];		// 运算符栈
	int numTop = -1;
	int operatorTop = -1;
	for (int i = 0; i < length; i++)
	{
		// 如果是操作数则直接入操作数栈
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
				numStack[++numTop] = Calculation(numL, numR, currentOperator);		// 将运算结果压入栈中
			}
			--operatorTop;	// 弹出左括号
		}
		else if (infix[i] == '+' || infix[i] == '-')
		{
			while (operatorTop != -1 && operatorStack[operatorTop] != '(')
			{
				int numR = numStack[numTop--];
				int numL = numStack[numTop--];
				char currentOperator = operatorStack[operatorTop--];
				numStack[++numTop] = Calculation(numL, numR, currentOperator);		// 将运算结果压入栈中
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
				numStack[++numTop] = Calculation(numL, numR, currentOperator);		// 将运算结果压入栈中
			}
			operatorStack[++operatorTop] = infix[i];
		}
	}
	while (operatorTop != -1)
	{
		int numR = numStack[numTop--];
		int numL = numStack[numTop--];
		char currentOperator = operatorStack[operatorTop--];
		numStack[++numTop] = Calculation(numL, numR, currentOperator);		// 将运算结果压入栈中
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