#include <stdio.h>
#include "SSqList.h"

int main()
{
	SSqList L;
	InitList(L);
	Print(L);
	ListInsert(L, 2, 1);
	Print(L);

	for (int i = 1; i <= Maxsize; i++) {
		ListInsert(L, i, i);
	}
	Print(L);

	for (int i = 1; i <= L.length; i++) {
		printf("��%dλԪ����%d\n", i, GetElem(L, i));
	}

	for (int i = 1; i <= L.length; i++) {
		printf("%d�ǵ�%dλԪ��\n", i, LocateElem(L, i));
	}

	DeleteLocate(L, 99);
	DeleteElem(L, 56);
	Print(L);

	for (int i = 1; i <= L.length; i++) {
		printf("��%dλԪ����%d\n", i, GetElem(L, i));
	}

	for (int i = 1; i <=Maxsize; i++) {
		printf("%d�ǵ�%dλԪ��\n", i, LocateElem(L, i));
	}
	return 0;
}
