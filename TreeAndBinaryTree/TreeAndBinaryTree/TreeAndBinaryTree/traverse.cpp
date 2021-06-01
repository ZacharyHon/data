#include "BinaryTree.h"

// 测试例子AB#CD##E##F#GH###

int main()
{
    BiTree T;
    printf("先序遍历输入(以#结束):\n");
    CreateBiTree(T);
    printf("\n先序遍历输出:\n");
    PreOrder(T);
    printf("\n中序遍历输出:\n");
    InOrder(T);
    printf("\n后序遍历输出:\n");
    PostOrder(T);
    printf("\n树的深度为:%d\n", TreeDepth(T));
    printf("\n树的结点个数为:%d\n", NodeCount(T));
    printf("\n树的叶子结点个数为:%d\n", LeafCount(T));
    printf("\n树的度为1的结点个数为:%d\n", Node_1_Count(T));
    printf("二叉树中从每个叶子结点到根结点的所有路径：\n");
    char path[256];
    int pathlen = 0;
    PrintAllPath(T, path, pathlen);
    printf("\n先序非递归遍历输出:\n");
    PreOrderNoR(T);
    printf("\n中序非递归遍历输出:\n");
    InOrderNoR(T);
    printf("\n后序非递归遍历输出1:\n");
    PostOrderNoR1(T);
    printf("\n后序非递归遍历输出2:\n");
    PostOrderNoR2(T);
    printf("\n层次遍历遍历输出:\n");
    LevelOrder(T);
    return 0;
}