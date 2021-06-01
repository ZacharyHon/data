#include "LinkList.h"

void Test_ListInsert(LinkList& L);

int main() {
	LinkList L;

	List_HeadInset(L);
	Print(L);
	
	Test_ListInsert(L);
	

	return 0;
}

void Test_ListInsert(LinkList& L) {
	for (int i = 0; i < 10; i++) {
		if (ListInsert(L, i, 100 + i))
			printf("�ڵ�%d��λ�ò���%d�ɹ�\n", i, 100 + i);
		else
			printf("�ڵ�%d��λ�ò���%dʧ��\n", i, 100 + i);
	}
	printf("����������Ϊ��\n");
	Print(L);
}
