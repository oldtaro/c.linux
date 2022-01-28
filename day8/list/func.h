#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct lnode {
	int data;
	struct lnode* next;
}lnode, * linklist;

void head_insert(linklist* pphead, linklist* pptail, int k);//头插法
void list_print(linklist head);//链表打印
void tail_insert(lnode** pphead, lnode** pptail, int k);//尾插法
void sort_insert(lnode** pphead, lnode** pptail, int k);//有序插入
void delete_elem(lnode** pphead, lnode** pptail, int k);//删除某个元素节点
//归并两个有序链表
void merger_two_list(linklist* pphead1, linklist* pphead2,linklist* pptail1, linklist* pptail2);
//逆置链表
void list_reserve(linklist* pphead, linklist* pptail);
//找到倒数第四个结点
void list_findlfour(linklist phead, linklist ptail);
//9找出中间结点
void list_findmid(linklist phead, linklist ptail);