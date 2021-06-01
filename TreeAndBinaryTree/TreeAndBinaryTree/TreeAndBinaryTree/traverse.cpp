#include "BinaryTree.h"

// ��������AB#CD##E##F#GH###

int main()
{
    BiTree T;
    printf("�����������(��#����):\n");
    CreateBiTree(T);
    printf("\n����������:\n");
    PreOrder(T);
    printf("\n����������:\n");
    InOrder(T);
    printf("\n����������:\n");
    PostOrder(T);
    printf("\n�������Ϊ:%d\n", TreeDepth(T));
    printf("\n���Ľ�����Ϊ:%d\n", NodeCount(T));
    printf("\n����Ҷ�ӽ�����Ϊ:%d\n", LeafCount(T));
    printf("\n���Ķ�Ϊ1�Ľ�����Ϊ:%d\n", Node_1_Count(T));
    printf("�������д�ÿ��Ҷ�ӽ�㵽����������·����\n");
    char path[256];
    int pathlen = 0;
    PrintAllPath(T, path, pathlen);
    printf("\n����ǵݹ�������:\n");
    PreOrderNoR(T);
    printf("\n����ǵݹ�������:\n");
    InOrderNoR(T);
    printf("\n����ǵݹ�������1:\n");
    PostOrderNoR1(T);
    printf("\n����ǵݹ�������2:\n");
    PostOrderNoR2(T);
    printf("\n��α����������:\n");
    LevelOrder(T);
    return 0;
}