#include "ThreadedBinaryTree.h"

// ��������AB#CD##E##F#GH###
//         ABD##E##C#G##

int main()
{
	ThreadBiTree T1, T2, T3;

	printf("�����������(��#����):\n");
	CreateThreadBiTree(T1);
	CreateInThread(T1);		// ʹ���������������������
	printf("\n������������������������:\n");
	InOrderThread(T1);

	if(getchar()=='\n')
		printf("\n�������ץס��\n");

	printf("\n\n�����������(��#����):\n");
	CreateThreadBiTree(T2);
	CreatePreThread(T2);
	printf("\n������������������������:\n");
	PreOrderThread(T2);

	return 0;
}