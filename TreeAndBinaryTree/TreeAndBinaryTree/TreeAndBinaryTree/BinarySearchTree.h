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
	if (T == NULL)		// 原树为空，新插入的记录为根节点
	{
		T = (BiSTree)malloc(sizeof(BiSTNode));
		T->data = e;
		T->rchild = T->lchild = NULL;
		return true;		// 插入成功
	}
	else if (e == T->data)
		return 0;
	else if (e < T->data)
		return BST_Insert(T->lchild, e);
	else
		return BST_Insert(T->rchild, e);
}
