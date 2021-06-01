#pragma once
#include <stdio.h>
#include <stdlib.h>
#define ElemType char
#define MAXSIZE 100 

typedef struct ThreadBiTNode {
	ElemType data;
	struct ThreadBiTNode* lchild, * rchild;
	int ltag, rtag;
}ThreadBiTNode, * ThreadBiTree;

void visit(ThreadBiTree T)
{
	printf("%c ", T->data);
}

//创建一棵二叉树，约定用户遵照前序遍历方式输入数据
void CreateThreadBiTree(ThreadBiTree& T) {
	ElemType data;
	scanf_s("%c", &data,1);
	if ('#' == data) 
		T = NULL;
	else 
	{
		T = (ThreadBiTree)malloc(sizeof(ThreadBiTNode));
		T ->data = data;
		T ->ltag = 0;
		T ->rtag = 0;
		CreateThreadBiTree(T->lchild);
		CreateThreadBiTree(T->rchild);
	}
}

// 通过中序遍历对二叉树线索化的递归算法
void InThread(ThreadBiTree p, ThreadBiTree& pre)		// 这里改变了pre指针的指向，所以对pre一定要引用
{
	if (p != NULL)
	{
		InThread(p->lchild, pre);		// 递归，线索化子树
		if (p->lchild == NULL)		// 左子树为空，建立前驱线索
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != NULL && pre->rchild == NULL)
		{
			pre->rchild = p;		// 建议前驱结点的后继线索
			pre->rtag = 1;
		}
		pre = p;		// 标记当前结点为刚刚访问过的结点
		InThread(p->rchild, pre);		// 递归，线索化右子树
	}
}

// 在函数调用时用指针或者引用做参数，表示把变量的地址传递给子函数，
// 但是子函数只能修改指针所指变量的值，并不能修改指针的指向。
// 如果想要修改指针的指向，就要用指针的指针，或者指针的引用。

// 通过中序遍历建立中序线索二叉树
void CreateInThread(ThreadBiTree T)		// 这里不需要改变指针的指向，所以不需要对指针进行引用
{
	ThreadBiTree pre = NULL;
	if (T != NULL)
	{
		InThread(T, pre);
		// 处理遍历的最后一个结点
		pre->rchild = NULL;
		pre->rtag = 1;
	}
}

// 中序线索二叉树中中序序列的第一个结点
ThreadBiTNode* InFirstNode(ThreadBiTNode* p)
{
 	while (p->ltag == 0)		// 找到最左下结点，不一定是叶节点
		p = p->lchild;		
	return p;
}

// 求中序线索二叉树中结点p在中序序列下的后继
ThreadBiTNode* InNextNode(ThreadBiTNode* p)
{
	if (p->rtag == 0)
		return InFirstNode(p->rchild);
	else 
		return p->rchild;		// tag=1,rchild直接指向后继
}

// 中序线索二叉树的中序遍历算法
void InOrderThread(ThreadBiTree T)
{
	for (ThreadBiTNode* p = InFirstNode(T); p != NULL; p = InNextNode(p))
		visit(p);
}

// 通过先序遍历对二叉树线索化的递归算法
void PreThread(ThreadBiTree p, ThreadBiTree& pre)		// 这里改变了pre指针的指向，所以对pre一定要引用
{
	if (p != NULL)
	{
		if (p->lchild == NULL)		// 左子树为空，建立前驱线索
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != NULL && pre->rchild == NULL)
		{
			pre->rchild = p;		// 建议前驱结点的后继线索
			pre->rtag = 1;
		}
		pre = p;		// 标记当前结点为刚刚访问过的结点
		if (p->ltag == 0)		// 确保lchild不是前驱线索，否则会导致死循环
			PreThread(p->lchild, pre);		// 递归，线索化左子树
		if (p->rtag == 0)
			PreThread(p->rchild, pre);		// 递归，线索化右子树
	}
}

// 通过先序遍历建立先序线索二叉树
void CreatePreThread(ThreadBiTree T)	
{
	ThreadBiTree pre = NULL;
	if (T != NULL)
	{
		PreThread(T, pre);
		// 处理遍历的最后一个结点
		if( pre->rchild == NULL)
			pre->rtag = 1;
	}
}

// 先序线索二叉树中先序序列的第一个结点
ThreadBiTNode* PreFirstNode(ThreadBiTNode* p)
{

	return p;
}

// 求先序线索二叉树中结点p在先序序列下的后继
// 如果该结点有左孩子，那么该结点的先序后继就是该结点的左孩子；
// 如果该结点没有左孩子，那么该结点的先序后继就是该结点的右孩子
// 如果没有右孩子，则右孩子指向的也是后继，就是rtag=1的情况
ThreadBiTNode* PreNextNode(ThreadBiTNode* p)
{
	if (p->rtag == 0)
		if (p->ltag == 0)
		{
			return p->lchild;
		}
		//如果该结点没有左孩子, 那么该结点的后继为右子树的树根
		else
		{
			return p->rchild;
		}
	else
		return p->rchild;		// tag=1,rchild直接指向后继
}

// 先序线索二叉树的先序遍历算法
void PreOrderThread(ThreadBiTree T)
{
	for (ThreadBiTNode* p = PreFirstNode(T); p != NULL; p = PreNextNode(p))
		visit(p);
}
