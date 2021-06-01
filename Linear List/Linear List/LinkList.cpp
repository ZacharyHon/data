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
			printf("在第%d个位置插入%d成功\n", i, 100 + i);
		else
			printf("在第%d个位置插入%d失败\n", i, 100 + i);
	}
	printf("插入后的链表为：\n");
	Print(L);
}
