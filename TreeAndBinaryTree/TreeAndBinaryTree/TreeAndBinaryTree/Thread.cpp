#include "ThreadedBinaryTree.h"

// 测试例子AB#CD##E##F#GH###
//         ABD##E##C#G##

int main()
{
	ThreadBiTree T1, T2, T3;

	printf("先序遍历输入(以#结束):\n");
	CreateThreadBiTree(T1);
	CreateInThread(T1);		// 使用中序遍历线索化二叉树
	printf("\n中序线索二叉树中序遍历输出:\n");
	InOrderThread(T1);

	if(getchar()=='\n')
		printf("\n罪魁祸首抓住了\n");

	printf("\n\n先序遍历输入(以#结束):\n");
	CreateThreadBiTree(T2);
	CreatePreThread(T2);
	printf("\n先序线索二叉树先序遍历输出:\n");
	PreOrderThread(T2);

	return 0;
}