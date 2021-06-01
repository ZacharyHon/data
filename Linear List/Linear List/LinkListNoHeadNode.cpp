#include "LinkListNoHeadNode.h"

int main() {
	LinkListNHN L;
	InitListNHN(L);
	ListInsert(L, 1, 1);
	ListInsert(L, 2, 2);
	ListInsert(L, 1, 3);
	Print(L);
	return 0;
}