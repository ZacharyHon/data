/*
	��̬˳���
*/
#pragma once
#include <stdlib.h>
#include <stdio.h>
#define InitSize 10		// �����ʼ����
#define IncreaseSize 5  // ���󳤶�
#define ElemType int	// ������������Ϊint ע���޸�Print()�����е�������Ʒ�
#define DefaultValue 0	// ��ʼ��Ԫ��Ĭ��ֵ����Ϊ0

typedef struct {
	int *data;		// ָ��̬���������ָ��
	int MaxSize;		// ˳�����������
	int length;			// ˳���ĵ�ǰ����
}SqList;

// ��ʼ��
void InitList(SqList &L) {
	L.data = (ElemType*)malloc(InitSize * sizeof(int));
	L.length = 0;
	L.MaxSize = InitSize;
	if (L.data != NULL) {
		for (int i = 0; i < L.MaxSize; i++) {
			L.data[i] = DefaultValue;
		}
	}
	
}

// ��̬�������鳤��
void IncreaseList(SqList& L) {
	int* p = L.data;
	L.data = (ElemType*)malloc((L.MaxSize+IncreaseSize) * sizeof(int));
	if (L.data != NULL) {
		for (int i = 0; i < L.length; i++) {
			L.data[i] = p[i];
		}
		L.MaxSize += IncreaseSize;
		for (int i = L.length; i < L.MaxSize; i++) {
			L.data[i] = DefaultValue;
		}
		free(p);
	}
}

// �ж�L�Ƿ�Ϊ�ձ�
bool ListEmpty(SqList& L) {
	return L.length == 0; // ����Ϊ0����Ϊ�ձ���True�����򷵻�False
}

// �����������L��λ��i������Ԫ��e
bool ListInsert(SqList& L, int i, int e) {
	// λ��Υ����������������ʧ��
	// i == L.length+1 ��ʱ�������һ��Ԫ�غ���룬������һ��Ԫ��
	if (i <= 0 || i > L.length + 1 ) {
		return false;
	}
	// ��̬�������鳤��
	if (L.length >= L.MaxSize) {
		IncreaseList(L);
	}
	for (int j = L.length; j >= i; j--)
		L.data[j] = L.data[j - 1];
	L.data[i - 1] = e;
	L.length++;
	return true;
}

// ��λ���ң�����λ��Ϊi��Ԫ��ֵ
ElemType GetElem(SqList L, int i) {
	return L.data[i - 1];
}

// ��ֵ���ң����ص�һ��Ԫ��ֵ����e��λ��
int LocateElem(SqList L, ElemType e) {
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] == e)
			return i + 1;
	}
	return 0; // û���ҵ�������0
}

// ɾ��������ɾ��λ��Ϊi��Ԫ��
bool DeleteLocate(SqList& L, int i) {
	if (i > L.length)
		return false;
	else
	{
		for (int j = i; j < L.length; j++) {
			L.data[j - 1] = L.data[j];
		}
		L.data[--L.length] = DefaultValue;
		return true;
	}
}

// ɾ��������ɾ����һ��Ԫ��ֵΪe��Ԫ��
bool DeleteElem(SqList& L, ElemType e) {
	int i = LocateElem(L, e);
	if (i == 0) return false;
	return DeleteLocate(L, i);
}

// �������Ԫ��ֵ
void Print(SqList L) {
	if (ListEmpty(L))
		printf("�ձ�\n");
	else {
		for (int i = 0; i < L.length; i++) {
			printf("%d", L.data[i]);
			i < L.length - 1 ? printf(" ") : printf("\n");
		}
	}
}


