/*
	静态顺序表
*/

#pragma once
#define Maxsize 100		// 定义最大长度
#define ElemType int	// 数据类型设置为int 注意修改Print()函数中的输出控制符
#define DefaultValue 0	// 初始化元素默认值设置为0

typedef struct {
	ElemType data[Maxsize];
	int length;
}SSqList;

// 初始化操作，将所有元素设置为默认初始值，长度设置为0
void InitList(SSqList &L) {
	for(int i=0; i<Maxsize; i++)
		L.data[i] = DefaultValue;
	L.length = 0;	 
}

// 判断L是否为空表
bool ListEmpty(SSqList& L) {
	return L.length == 0; // 长度为0，则为空表返回True；否则返回False
}

// 插入操作，在L的位序i处插入元素e
bool ListInsert(SSqList& L, int i, int e) {
	// 位序违法或表已满，则插入失败
	// i == L.length+1 此时，在最后一个元素后插入，或插入第一个元素
	if ( i<=0 || i > L.length+1 || L.length >= Maxsize) {
		return false;
	}
	for (int j = L.length; j >= i; j--)
		L.data[j] = L.data[j - 1];
	L.data[i - 1] = e;
	L.length++;
	return true;
}

// 按位查找，返回位序为i的元素值
ElemType GetElem(SSqList L, int i) {
	return L.data[i - 1];
}

// 按值查找，返回第一个元素值等于e的位序
int LocateElem(SSqList L, ElemType e) {
	for (int i = 0; i < Maxsize; i++) {
		if (L.data[i] == e)
			return i + 1;
	}
	return 0; // 没有找到，返回0
}

// 删除操作，删除位序为i的元素
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

// 删除操作，删除第一个元素值为e的元素
bool DeleteElem(SSqList &L, ElemType e) {
	int i = LocateElem(L, e);
	if (i == 0) return false;
	return DeleteLocate(L, i);
}

// 输出所有元素值
void Print(SSqList L) {
	if (ListEmpty(L))
		printf("空表\n");
	else {
		for (int i = 0; i < L.length; i++) {
			printf("%d", L.data[i]);
			i < L.length - 1 ? printf(" ") : printf("\n");
		}
	}
}


