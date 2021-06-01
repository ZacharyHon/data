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
		if (L == NULL) {	// ����Ϊ�ձ�����Ľ��Ϊ��һ�����
			s->next = NULL;
			L = s;
			return true;
		}
		else{		// ����Ľ�����ԭ���ĵ�һ������Ϊ�µĵ�һ����㣬ԭ����һ������Ϊ�ڶ�����㡣
			s->next = L;
			L = s;
			return true;
		}
	}
	LNodeNHN* p;
	int j = 1;
	p = L;
	while (p != NULL && j < i - 1) {	// ѭ���ҵ���i-1���ڵ�
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
		printf("��%d���ڵ㣬ֵΪ%d\n", num++, L->data);
		L = L->next;
	}
}
