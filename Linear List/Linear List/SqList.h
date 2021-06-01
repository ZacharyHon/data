/*
	动态顺序表
*/
#pragma once
#include <stdlib.h>
#include <stdio.h>
#define InitSize 10		// 定义初始长度
#define IncreaseSize 5  // 增大长度
#define ElemType int	// 数据类型设置为int 注意修改Print()函数中的输出控制符
#define DefaultValue 0	// 初始化元素默认值设置为0

typedef struct {
	int *data;		// 指向动态分配数组的指针
	int MaxSize;		// 顺序表的最大容量
	int length;			// 顺序表的当前长度
}SqList;

// 初始化
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

// 动态增加数组长度
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

// 判断L是否为空表
bool ListEmpty(SqList& L) {
	return L.length == 0; // 长度为0，则为空表返回True；否则返回False
}

// 插入操作，在L的位序i处插入元素e
bool ListInsert(SqList& L, int i, int e) {
	// 位序违法或表已满，则插入失败
	// i == L.length+1 此时，在最后一个元素后插入，或插入第一个元素
	if (i <= 0 || i > L.length + 1 ) {
		return false;
	}
	// 动态增加数组长度
	if (L.length >= L.MaxSize) {
		IncreaseList(L);
	}
	for (int j = L.length; j >= i; j--)
		L.data[j] = L.data[j - 1];
	L.data[i - 1] = e;
	L.length++;
	return true;
}

// 按位查找，返回位序为i的元素值
ElemType GetElem(SqList L, int i) {
	return L.data[i - 1];
}

// 按值查找，返回第一个元素值等于e的位序
int LocateElem(SqList L, ElemType e) {
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] == e)
			return i + 1;
	}
	return 0; // 没有找到，返回0
}

// 删除操作，删除位序为i的元素
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

// 删除操作，删除第一个元素值为e的元素
bool DeleteElem(SqList& L, ElemType e) {
	int i = LocateElem(L, e);
	if (i == 0) return false;
	return DeleteLocate(L, i);
}

// 输出所有元素值
void Print(SqList L) {
	if (ListEmpty(L))
		printf("空表\n");
	else {
		for (int i = 0; i < L.length; i++) {
			printf("%d", L.data[i]);
			i < L.length - 1 ? printf(" ") : printf("\n");
		}
	}
}


