#pragma once
#include <stdio.h>
#include <stdlib.h>
#define ElemType char
#define MAXSIZE 100 


typedef struct BiSTNode {
	ElemType data;
	struct BiSTNode* lchild, * rchild;
}BiSTNode, * BiSTree;

bool BST_Insert(BiSTree& T, ElemType e)
{
	if (T == NULL)		// ԭ��Ϊ�գ��²���ļ�¼Ϊ���ڵ�
	{
		T = (BiSTree)malloc(sizeof(BiSTNode));
		T->data = e;
		T->rchild = T->lchild = NULL;
		return true;		// ����ɹ�
	}
	else if (e == T->data)
		return 0;
	else if (e < T->data)
		return BST_Insert(T->lchild, e);
	else
		return BST_Insert(T->rchild, e);
}
