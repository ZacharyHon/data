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
		// Æ¥Åäµ½×óÀ¨ºÅÖ±½ÓÈëÕ»
		if (sequence[i] == '(' || sequence[i] == '[' || sequence[i] == '{')
			stack[++top] = sequence[i];	

		else 
		{
			// Æ¥Åäµ½ÓÒÀ¨ºÅ£¬Õ»Îª¿Õ£¬ÔòÆ¥ÅäÊ§°Ü
			if (top == -1) 
			{
				printf("Æ¥ÅäÊ§°Ü¡£");
				return 0;
			}
			char temp = stack[top--];	// µ¯³öÒ»¸ö×óÀ¨ºÅ
			if( sequence[i] == ')' && temp != '(')
			{
				printf("Æ¥ÅäÊ§°Ü¡£");
				return 0;
			}
			if (sequence[i] == ']' && temp != '[')
			{
				printf("Æ¥ÅäÊ§°Ü¡£");
				return 0;
			}
			if (sequence[i] == '}' && temp != '{')
			{
				printf("Æ¥ÅäÊ§°Ü¡£");
				return 0;
			}

		}
	}
	// Æ¥ÅäÍêºó£¬ÈôÕ»¿Õ²ÅËµÃ÷Æ¥Åä³É¹¦
	if (top == -1)
		printf("Æ¥Åä³É¹¦");
	else
		printf("Æ¥ÅäÊ§°Ü¡£");
	return 0;    
}