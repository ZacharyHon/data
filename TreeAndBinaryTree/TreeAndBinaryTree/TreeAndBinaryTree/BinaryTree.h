  #pragma once
#include <stdio.h>
#include <stdlib.h>
#define ElemType char
#define MAXSIZE 100 


typedef struct BiTNode{
	ElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree& T)        // 先序创建二叉树
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

void PreOrder(BiTree T)     // 先序遍历
{
    if (T != NULL)
    {
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T)      // 中序遍历
{
    if (T != NULL) 
    {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T)        // 后序遍历
{
    if (T != NULL)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}
    
int TreeDepth(BiTree T)     // 树的深度
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

int NodeCount(BiTree T)     // 统计二叉树中结点的个数
{
    if (T == NULL) return 0;
    else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

int LeafCount(BiTree T)     // 统计二叉树中叶子结点的个数
{
    if (T == NULL) 
        return 0;
    if (!T->lchild && !T->rchild) {//如果二叉树左子树和右子树皆为空,说明该二叉树根节点为叶子节点,加1.
        return 1;
    }
    else {
        return LeafCount(T->lchild) + LeafCount(T->rchild);
    }
}

int Node_1_Count(BiTree T)      // 统计二叉树的度为1的结点个数
{
    if (T == NULL) return 0;
    if ((!T->lchild) && (T->rchild) || (T->lchild) && (!T->rchild))
        return 1 + Node_1_Count(T->lchild) + Node_1_Count(T->rchild);
    else
        return Node_1_Count(T->lchild) + Node_1_Count(T->rchild);
}

void PrintAllPath(BiTree T, char path[], int pathlen)       // 二叉树中从每个叶子结点到根结点的路径
{
    int i;
    if (T != NULL) {
        path[pathlen] = T->data; //将当前结点放入路径中
        if (T->lchild == NULL && T->rchild == NULL) {//叶子结点
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

void InOrderNoR(BiTree T)       // 中序遍历非递归
{
    BiTNode* stack[MAXSIZE];
    int top = -1;
    BiTree p = T;
    while (p || top != -1)
    {
        if (p)
        {
            stack[++top] = p;
            p = p->lchild;      // 左孩子不空一直向左走
        }
        else
        {
            p = stack[top--];
            visit(p);
            p = p->rchild;
        }
    }
}

void PreOrderNoR(BiTree T)       // 先序遍历非递归
{
    BiTNode* stack[MAXSIZE];
    int top = -1;
    BiTree p = T;
    while (p || top != -1)
    {
        if (p)
        {
            visit(p);           // 访问后再入栈
            stack[++top] = p;
            p = p->lchild;      // 左孩子不空一直向左走
        }
        else
        {
            p = stack[top--];
            p = p->rchild;
        }
    }
}

void PostOrderNoR1(BiTree T)    // 后序遍历非递归1
{
    BiTNode* stack[MAXSIZE];
    int top = -1;
    BiTree p = T;
    BiTNode* r = NULL;        // 指向最近访问过的结点
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
            if (p->rchild && p->rchild != r)        // 若右子树存在但并未被访问过，则先访问右子树
                p = p->rchild;
            else        // 否则弹出结点并访问
            {
                p = stack[top--];
                visit(p);
                r = p;      // 记录最近访问过的结点
                p = NULL;       // 结点访问完后，重置p指针
            }
            // 每次出栈访问完一个结点就相当于遍历完以该节点为根的子树，需将P置NULL
        }
    }
}

void PostOrderNoR2(BiTree T)    // 后序遍历非递归2
{
    /*
        后序遍历是左右根，我们将后序遍历逆置就可以得到根右左，
        所以可以在先序遍历方法的基础上稍加改正，即访问完根结点后先访问右子树再访问左子树，
        最后将得到的序列逆置即可。
    */
    BiTNode* stack[MAXSIZE];
    BiTNode* reStack[MAXSIZE];      // 将原本要访问的结点全部压入栈中，最后一次性弹出即可得到逆序序列
    int top = -1;
    int rTop = -1;
    BiTree p = T;
    while (p || top != -1)  // 根右左
    {
        if (p) 
        {
            // visit(p);    // 若访问后入栈，得到的是根右左的序列，可以作为验证
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

void LevelOrder(BiTree T)       // 层次遍历
{
    BiTNode* queue[MAXSIZE];
    BiTree p;
    int rear = -1, front = -1;
    queue[++rear] = T;      // 根节点入队
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