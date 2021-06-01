/*
	��̬˳���
*/

#pragma once
#define Maxsize 100		// ������󳤶�
#define ElemType int	// ������������Ϊint ע���޸�Print()�����е�������Ʒ�
#define DefaultValue 0	// ��ʼ��Ԫ��Ĭ��ֵ����Ϊ0

typedef struct {
	ElemType data[Maxsize];
	int length;
}SSqList;

// ��ʼ��������������Ԫ������ΪĬ�ϳ�ʼֵ����������Ϊ0
void InitList(SSqList &L) {
	for(int i=0; i<Maxsize; i++)
		L.data[i] = DefaultValue;
	L.length = 0;	 
}

// �ж�L�Ƿ�Ϊ�ձ�
bool ListEmpty(SSqList& L) {
	return L.length == 0; // ����Ϊ0����Ϊ�ձ���True�����򷵻�False
}

// �����������L��λ��i������Ԫ��e
bool ListInsert(SSqList& L, int i, int e) {
	// λ��Υ����������������ʧ��
	// i == L.length+1 ��ʱ�������һ��Ԫ�غ���룬������һ��Ԫ��
	if ( i<=0 || i > L.length+1 || L.length >= Maxsize) {
		return false;
	}
	for (int j = L.length; j >= i; j--)
		L.data[j] = L.data[j - 1];
	L.data[i - 1] = e;
	L.length++;
	return true;
}

// ��λ���ң�����λ��Ϊi��Ԫ��ֵ
ElemType GetElem(SSqList L, int i) {
	return L.data[i - 1];
}

// ��ֵ���ң����ص�һ��Ԫ��ֵ����e��λ��
int LocateElem(SSqList L, ElemType e) {
	for (int i = 0; i < Maxsize; i++) {
		if (L.data[i] == e)
			return i + 1;
	}
	return 0; // û���ҵ�������0
}

// ɾ��������ɾ��λ��Ϊi��Ԫ��
bool DeleteLocate(SSqList& L, int i) {
	if (i >= L.length || i>L.length)
		return false;
	else
	{
		for (int j = i; j < L.length; j++) {
			L.data[j-1] = L.data[j];
		}
		L.data[--L.length] = DefaultValue;
		return true;
	}
}

// ɾ��������ɾ����һ��Ԫ��ֵΪe��Ԫ��
bool DeleteElem(SSqList &L, ElemType e) {
	int i = LocateElem(L, e);
	if (i == 0) return false;
	return DeleteLocate(L, i);
}

// �������Ԫ��ֵ
void Print(SSqList L) {
	if (ListEmpty(L))
		printf("�ձ�\n");
	else {
		for (int i = 0; i < L.length; i++) {
			printf("%d", L.data[i]);
			i < L.length - 1 ? printf(" ") : printf("\n");
		}
	}
}


