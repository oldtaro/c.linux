#include "func.h"

int main() {
	lnode* phead=NULL, * ptail=NULL;
	lnode* phead1 = NULL, * ptail1 = NULL;
	int k;
	printf("输入第一个数组\n");
	while (scanf("%d", &k) != EOF) {
		/*head_insert(&phead, &ptail, k);
		tail_insert(&phead, &ptail, k);*/
		sort_insert(&phead, &ptail, k);
	}
	list_print(phead);
	/*printf("输入第二个数组\n");
	while (scanf("%d", &k) != EOF) {
		sort_insert(&phead1, &ptail1, k);
	}
	merger_two_list(&phead,&phead1,&ptail,&ptail1);
	printf("输入你要删除元素:\n");
	while (scanf("%d", &k) != EOF) {
		delete_elem(&phead, &ptail, k);
	}
	list_reserve(&phead, &ptail);
	list_print(phead);
	list_findlfour(phead, ptail);*/
	list_findmid(phead, ptail);
	system("pause");
	return 0;
}