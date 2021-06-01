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

//����һ�ö�������Լ���û�����ǰ�������ʽ��������
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

// ͨ����������Զ������������ĵݹ��㷨
void InThread(ThreadBiTree p, ThreadBiTree& pre)		// ����ı���preָ���ָ�����Զ�preһ��Ҫ����
{
	if (p != NULL)
	{
		InThread(p->lchild, pre);		// �ݹ飬����������
		if (p->lchild == NULL)		// ������Ϊ�գ�����ǰ������
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != NULL && pre->rchild == NULL)
		{
			pre->rchild = p;		// ����ǰ�����ĺ������
			pre->rtag = 1;
		}
		pre = p;		// ��ǵ�ǰ���Ϊ�ոշ��ʹ��Ľ��
		InThread(p->rchild, pre);		// �ݹ飬������������
	}
}

// �ں�������ʱ��ָ�������������������ʾ�ѱ����ĵ�ַ���ݸ��Ӻ�����
// �����Ӻ���ֻ���޸�ָ����ָ������ֵ���������޸�ָ���ָ��
// �����Ҫ�޸�ָ���ָ�򣬾�Ҫ��ָ���ָ�룬����ָ������á�

// ͨ���������������������������
void CreateInThread(ThreadBiTree T)		// ���ﲻ��Ҫ�ı�ָ���ָ�����Բ���Ҫ��ָ���������
{
	ThreadBiTree pre = NULL;
	if (T != NULL)
	{
		InThread(T, pre);
		// ������������һ�����
		pre->rchild = NULL;
		pre->rtag = 1;
	}
}

// �����������������������еĵ�һ�����
ThreadBiTNode* InFirstNode(ThreadBiTNode* p)
{
 	while (p->ltag == 0)		// �ҵ������½�㣬��һ����Ҷ�ڵ�
		p = p->lchild;		
	return p;
}

// �����������������н��p�����������µĺ��
ThreadBiTNode* InNextNode(ThreadBiTNode* p)
{
	if (p->rtag == 0)
		return InFirstNode(p->rchild);
	else 
		return p->rchild;		// tag=1,rchildֱ��ָ����
}

// ������������������������㷨
void InOrderThread(ThreadBiTree T)
{
	for (ThreadBiTNode* p = InFirstNode(T); p != NULL; p = InNextNode(p))
		visit(p);
}

// ͨ����������Զ������������ĵݹ��㷨
void PreThread(ThreadBiTree p, ThreadBiTree& pre)		// ����ı���preָ���ָ�����Զ�preһ��Ҫ����
{
	if (p != NULL)
	{
		if (p->lchild == NULL)		// ������Ϊ�գ�����ǰ������
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != NULL && pre->rchild == NULL)
		{
			pre->rchild = p;		// ����ǰ�����ĺ������
			pre->rtag = 1;
		}
		pre = p;		// ��ǵ�ǰ���Ϊ�ոշ��ʹ��Ľ��
		if (p->ltag == 0)		// ȷ��lchild����ǰ������������ᵼ����ѭ��
			PreThread(p->lchild, pre);		// �ݹ飬������������
		if (p->rtag == 0)
			PreThread(p->rchild, pre);		// �ݹ飬������������
	}
}

// ͨ���������������������������
void CreatePreThread(ThreadBiTree T)	
{
	ThreadBiTree pre = NULL;
	if (T != NULL)
	{
		PreThread(T, pre);
		// ������������һ�����
		if( pre->rchild == NULL)
			pre->rtag = 1;
	}
}

// �����������������������еĵ�һ�����
ThreadBiTNode* PreFirstNode(ThreadBiTNode* p)
{

	return p;
}

// �����������������н��p�����������µĺ��
// ����ý�������ӣ���ô�ý��������̾��Ǹý������ӣ�
// ����ý��û�����ӣ���ô�ý��������̾��Ǹý����Һ���
// ���û���Һ��ӣ����Һ���ָ���Ҳ�Ǻ�̣�����rtag=1�����
ThreadBiTNode* PreNextNode(ThreadBiTNode* p)
{
	if (p->rtag == 0)
		if (p->ltag == 0)
		{
			return p->lchild;
		}
		//����ý��û������, ��ô�ý��ĺ��Ϊ������������
		else
		{
			return p->rchild;
		}
	else
		return p->rchild;		// tag=1,rchildֱ��ָ����
}

// ������������������������㷨
void PreOrderThread(ThreadBiTree T)
{
	for (ThreadBiTNode* p = PreFirstNode(T); p != NULL; p = PreNextNode(p))
		visit(p);
}
