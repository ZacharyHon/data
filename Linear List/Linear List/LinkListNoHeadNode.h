#pragma once
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LNodeNHN {
	ElemType data;
	struct LNodeNHN* next;
}LNodeNHN, *LinkListNHN;

bool InitListNHN(LinkListNHN& L) {
	L = NULL;
	return true;
}

bool EmptyListNHN(LinkListNHN& L) {
	return L == NULL;
}

bool ListInsert(LinkListNHN& L, int i, int e) {
	if (i < 1) {
		return false;
	}
	if (i == 1) {
		LNodeNHN* s = (LNodeNHN*)malloc(sizeof(LNodeNHN));
		if (s == NULL) {
			return false;
		}
		s->data = e;
		if (L == NULL) {	// 链表为空表，插入的结点为第一个结点
			s->next = NULL;
			L = s;
			return true;
		}
		else{		// 插入的结点代替原来的第一个结点成为新的第一个结点，原来第一个结点成为第二个结点。
			s->next = L;
			L = s;
			return true;
		}
	}
	LNodeNHN* p;
	int j = 1;
	p = L;
	while (p != NULL && j < i - 1) {	// 循环找到第i-1个节点
		p = p->next;
		j++;
	}
	if (p == NULL) {
		return false;
	}
	LNodeNHN* s = (LNodeNHN*)malloc(sizeof(LNodeNHN));
	if (s == NULL) {
		return false;
	}
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
void Print(LinkListNHN& L) {
	int num = 1;
	while (L != NULL) {
		printf("第%d个节点，值为%d\n", num++, L->data);
		L = L->next;
	}
}
