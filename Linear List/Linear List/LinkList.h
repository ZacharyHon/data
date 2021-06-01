/*
	��ͷ���ĵ�����
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#define ElemType int

typedef struct LNode {
	ElemType data;			
	struct LNode* next;		// ָ��ָ����һ�����
}LNode, *LinkList;

bool EmptyList(LinkList L) {
	return (L->next == NULL);
}

// ��ʼ������
bool InitList(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));		//����һ��ͷ���
	if (L == NULL) {
		return false;		// �ڴ治�㣬����ʧ��
	}
	L->next = NULL;
	return true;
}

// ��ͷ�巨����������
LinkList List_HeadInset(LinkList& L) {		// ���뽨��������
	LNode* s;
	int x;
	L = (LNode*)malloc(sizeof(LNode));	// ����ͷ���
	if (L == NULL)
		return L;
	L -> next = NULL;		// ��ʼΪ������
	scanf_s("%d", &x);	// �������ֵ
	while (x != 520) {
		s = (LNode*)malloc(sizeof(LNode));	// �����½��
		if (s == NULL)
			return NULL;
		s->data = x;
		s->next = L->next;
		L->next = s;
		scanf_s("%d", &x);
	}
	return L;
}

// �ڵ�i��λ�ò���Ԫ��e
bool ListInsert(LinkList& L, int i, int e) {
	if (i < 1)
		return false;
	LNode* p;
	int j = 0;
	p = L;
	while (p != NULL && j < i - 1) {		// ѭ���ҵ���i-1�����
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
		printf("��%d���ڵ㣬ֵΪ%d\n", num++, L->data);
	}
}