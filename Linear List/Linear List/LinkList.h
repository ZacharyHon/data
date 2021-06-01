/*
	带头结点的单链表
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#define ElemType int

typedef struct LNode {
	ElemType data;			
	struct LNode* next;		// 指针指向下一个结点
}LNode, *LinkList;

bool EmptyList(LinkList L) {
	return (L->next == NULL);
}

// 初始化链表
bool InitList(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));		//分配一个头结点
	if (L == NULL) {
		return false;		// 内存不足，分配失败
	}
	L->next = NULL;
	return true;
}

// 用头插法建立单链表
LinkList List_HeadInset(LinkList& L) {		// 你想建立单链表
	LNode* s;
	int x;
	L = (LNode*)malloc(sizeof(LNode));	// 创建头结点
	if (L == NULL)
		return L;
	L -> next = NULL;		// 初始为空链表
	scanf_s("%d", &x);	// 输入结点的值
	while (x != 520) {
		s = (LNode*)malloc(sizeof(LNode));	// 创建新结点
		if (s == NULL)
			return NULL;
		s->data = x;
		s->next = L->next;
		L->next = s;
		scanf_s("%d", &x);
	}
	return L;
}

// 在第i个位置插入元素e
bool ListInsert(LinkList& L, int i, int e) {
	if (i < 1)
		return false;
	LNode* p;
	int j = 0;
	p = L;
	while (p != NULL && j < i - 1) {		// 循环找到第i-1个结点
		p = p->next;
		j++;
	}

	if (p == NULL)
		return false;

	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

void Print(LinkList L) {
	int num = 1;
	while (L->next != NULL) {
		L = L->next;
		printf("第%d个节点，值为%d\n", num++, L->data);
	}
}