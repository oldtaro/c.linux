#include "func.h"
//打印链表
void list_print(linklist phead) {
	while (phead != NULL) {
		printf("%3d", phead->data);
		phead = phead->next;
	}
	printf("\n");
}
//头插法
void head_insert(lnode** pphead, lnode** pptail, int k) {
	lnode* pnew;
	pnew = (lnode*)malloc(sizeof(lnode));
	memset(pnew,0,sizeof(lnode));
	pnew->data = k;
	if (*pphead == NULL) {
		*pphead = pnew;
		*pptail = pnew;
	}
	else {
		pnew->next = *pphead;
		*pphead = pnew;
	}
}
//尾插法
void tail_insert(lnode** pphead, lnode** pptail, int k) {
	lnode* pnew;
	pnew = (lnode*)malloc(sizeof(lnode));
	memset(pnew, 0, sizeof(lnode));
	pnew->data = k;
	if (*pptail == NULL) {
		*pphead = pnew;
		*pptail = pnew;
	}
	else {
		(*pptail)->next= pnew;
		*pptail = pnew;
	}
}

// 用有序插入建立链表
void sort_insert(lnode** pphead,lnode** pptail, int k) {
	lnode* pnew = (lnode*)malloc(sizeof(lnode));
	lnode* temp = *pphead,*ppre = *pphead;
	memset(pnew,0,sizeof(lnode));
	pnew->data = k;
	if (*pphead == NULL) {
		*pphead = pnew;
		*pptail = pnew;
	}
	else if (k < temp->data) {
		pnew->next = *pphead;
		*pphead = pnew;
	}
	else {
		while (temp!=NULL) {
			if (temp->data > k) {
				pnew->next = temp;
				ppre->next = pnew;
				return;
			}
			ppre = temp;
			temp = temp->next;
		}
		if (temp == NULL) {
			(*pptail)->next = pnew;
			*pptail = pnew;
		}
	}
}
//删除某个元素的节点
void delete_elem(lnode** pphead, lnode** pptail, int k) {
	lnode* ptemp = *pphead, * ppre = *pphead;
	while (ptemp != NULL) {
		if (ptemp == *pphead && ptemp->data == k) {
			*pphead = (*pphead)->next;
			free(ptemp);
			if (*pphead == NULL) {
				*pptail = NULL;
				return;
			}
			else {
				ptemp = *pphead;
				ppre = ptemp;
			}
		}
		else if (ptemp == *pptail && ptemp->data == k) {
			*pptail = ppre;
			(*pptail)->next = NULL;
			free(ptemp);
			return;
		}
		else if(ptemp->data == k) {
			ppre->next = ptemp->next;
			free(ptemp);
			ptemp = ppre->next;
		}
		ppre = ptemp;
		ptemp = ptemp->next;
	}
}
//6归并两链表
void merger_two_list(linklist* pphead1, linklist* pphead2, linklist* pptail1, linklist* pptail2) {
	lnode* h = (lnode*)malloc(sizeof(lnode)), * t;
	memset(h, 0, sizeof(lnode));
	if ((*pphead1)->data <= (*pphead2)->data) {
		h->next = *pphead1;
		(*pphead1) = (*pphead1)->next;
	}
	else {
		h->next = *pphead2;
		(*pphead2) = (*pphead2)->next;
	}
	t = h->next;
	while (*pphead1 != NULL && *pphead2 != NULL) {
		if ((*pphead1)->data <= (*pphead2)->data) {
			t->next = *pphead1;
			(*pphead1) = (*pphead1)->next;
		}
		else {
			t->next = *pphead2;
			(*pphead2) = (*pphead2)->next;
		}
		t = t->next;
	}
	if (*pphead1 == NULL) {
		t->next = *pphead2;
		*pptail1=*pptail2;
	}
	else if (*pphead2 == NULL) {
		t->next = *pphead1;
		*pptail2 = *pptail1;
	}
	*pphead1 = h->next;
	*pphead2 = h->next;
	free(h);
}
//7链表逆转
void list_reserve(linklist* pphead, linklist* pptail) {
	lnode* h = (lnode*)malloc(sizeof(lnode));
	memset(h, 0, sizeof(lnode));//申请一个头结点
	lnode* p= *pphead, * ptemp;
	while (p != NULL) {          //逆置链表
		ptemp = p->next;
		p->next = h->next;
		h->next = p;
		p = ptemp;
	}
	ptemp = *pphead;       //交换头尾指针
	*pphead = *pptail;
	*pptail = ptemp;
	free(h);
}
//8找出链表的倒数第四个节点
void list_findlfour(linklist phead, linklist ptail){
	lnode* p1=phead, *p2=phead;
	int i;
	for (i = 1; i < 4; i++) {
		p1 = p1->next;
	}
	if (p1 == NULL) {
			printf("无倒数第四个结点\n");
			return;
		};
	while (p1 != ptail) {
		p1 = p1->next;
		p2 = p2->next;
	}
		printf("倒数第四个节点的值是%3d\n", p2->data);
}
//9找出中间结点
void list_findmid(linklist phead, linklist ptail) {
	lnode* p = phead, * q = phead;
	while (q != ptail && q != NULL) {
		q = q->next->next;
		p = p->next;
	}
	printf("中间结点元素值为%3d\n", p->data);
}