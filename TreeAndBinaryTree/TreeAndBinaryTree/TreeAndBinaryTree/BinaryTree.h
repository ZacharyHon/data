  #pragma once
#include <stdio.h>
#include <stdlib.h>
#define ElemType char
#define MAXSIZE 100 


typedef struct BiTNode{
	ElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree& T)        // ���򴴽�������
{
    ElemType data; 
    scanf_s("%c", &data,1);
    if (data == '#')
        T = NULL;
    else {
        T = (BiTNode*)malloc(sizeof(BiTNode));
        T->data = data;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void visit(BiTree T) 
{
    printf("%c ", T->data);
}

void PreOrder(BiTree T)     // �������
{
    if (T != NULL)
    {
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T)      // �������
{
    if (T != NULL) 
    {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T)        // �������
{
    if (T != NULL)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}
    
int TreeDepth(BiTree T)     // �������
{
    if (T == NULL)
    {
        return 0;
    }
    else
    {
        int l = TreeDepth(T->lchild);
        int r = TreeDepth(T->rchild);
        return l > r ? l + 1 : r + 1;
    }
}   

int NodeCount(BiTree T)     // ͳ�ƶ������н��ĸ���
{
    if (T == NULL) return 0;
    else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

int LeafCount(BiTree T)     // ͳ�ƶ�������Ҷ�ӽ��ĸ���
{
    if (T == NULL) 
        return 0;
    if (!T->lchild && !T->rchild) {//�������������������������Ϊ��,˵���ö��������ڵ�ΪҶ�ӽڵ�,��1.
        return 1;
    }
    else {
        return LeafCount(T->lchild) + LeafCount(T->rchild);
    }
}

int Node_1_Count(BiTree T)      // ͳ�ƶ������Ķ�Ϊ1�Ľ�����
{
    if (T == NULL) return 0;
    if ((!T->lchild) && (T->rchild) || (T->lchild) && (!T->rchild))
        return 1 + Node_1_Count(T->lchild) + Node_1_Count(T->rchild);
    else
        return Node_1_Count(T->lchild) + Node_1_Count(T->rchild);
}

void PrintAllPath(BiTree T, char path[], int pathlen)       // �������д�ÿ��Ҷ�ӽ�㵽������·��
{
    int i;
    if (T != NULL) {
        path[pathlen] = T->data; //����ǰ������·����
        if (T->lchild == NULL && T->rchild == NULL) {//Ҷ�ӽ��
            for (i = pathlen; i >= 0; i--)
                printf("%c ", path[i]);
            printf("\n");
        }
        else {
            PrintAllPath(T->lchild, path, pathlen + 1);
            PrintAllPath(T->rchild, path, pathlen + 1);
        }
    }
}

void InOrderNoR(BiTree T)       // ��������ǵݹ�
{
    BiTNode* stack[MAXSIZE];
    int top = -1;
    BiTree p = T;
    while (p || top != -1)
    {
        if (p)
        {
            stack[++top] = p;
            p = p->lchild;      // ���Ӳ���һֱ������
        }
        else
        {
            p = stack[top--];
            visit(p);
            p = p->rchild;
        }
    }
}

void PreOrderNoR(BiTree T)       // ��������ǵݹ�
{
    BiTNode* stack[MAXSIZE];
    int top = -1;
    BiTree p = T;
    while (p || top != -1)
    {
        if (p)
        {
            visit(p);           // ���ʺ�����ջ
            stack[++top] = p;
            p = p->lchild;      // ���Ӳ���һֱ������
        }
        else
        {
            p = stack[top--];
            p = p->rchild;
        }
    }
}

void PostOrderNoR1(BiTree T)    // ��������ǵݹ�1
{
    BiTNode* stack[MAXSIZE];
    int top = -1;
    BiTree p = T;
    BiTNode* r = NULL;        // ָ��������ʹ��Ľ��
    while (p || top != -1) 
    {
        if (p)
        {
            stack[++top] = p;
            p = p->lchild;
        }
        else
        {
            p = stack[top];
            if (p->rchild && p->rchild != r)        // �����������ڵ���δ�����ʹ������ȷ���������
                p = p->rchild;
            else        // ���򵯳���㲢����
            {
                p = stack[top--];
                visit(p);
                r = p;      // ��¼������ʹ��Ľ��
                p = NULL;       // �������������pָ��
            }
            // ÿ�γ�ջ������һ�������൱�ڱ������Ըýڵ�Ϊ�����������轫P��NULL
        }
    }
}

void PostOrderNoR2(BiTree T)    // ��������ǵݹ�2
{
    /*
        ������������Ҹ������ǽ�����������þͿ��Եõ�������
        ���Կ�����������������Ļ������ԼӸ�������������������ȷ����������ٷ�����������
        ��󽫵õ����������ü��ɡ�
    */
    BiTNode* stack[MAXSIZE];
    BiTNode* reStack[MAXSIZE];      // ��ԭ��Ҫ���ʵĽ��ȫ��ѹ��ջ�У����һ���Ե������ɵõ���������
    int top = -1;
    int rTop = -1;
    BiTree p = T;
    while (p || top != -1)  // ������
    {
        if (p) 
        {
            // visit(p);    // �����ʺ���ջ���õ����Ǹ���������У�������Ϊ��֤
            reStack[++rTop] = p;
            stack[++top] = p;
            p = p->rchild;
        }
        else
        {
            p = stack[top--];        
            p = p->lchild;
        }
    }
    while (rTop != -1)
        visit(reStack[rTop--]);
}

void LevelOrder(BiTree T)       // ��α���
{
    BiTNode* queue[MAXSIZE];
    BiTree p;
    int rear = -1, front = -1;
    queue[++rear] = T;      // ���ڵ����
    while (rear != front)
    {
        p = queue[++front];
        visit(p);
        if (p->lchild != NULL)
            queue[++rear] = p->lchild;
        if (p->rchild != NULL)
            queue[++rear] = p->rchild;
    }
}