#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct lnode {
	int data;
	struct lnode* next;
}lnode, * linklist;

void head_insert(linklist* pphead, linklist* pptail, int k);//ͷ�巨
void list_print(linklist head);//�����ӡ
void tail_insert(lnode** pphead, lnode** pptail, int k);//β�巨
void sort_insert(lnode** pphead, lnode** pptail, int k);//�������
void delete_elem(lnode** pphead, lnode** pptail, int k);//ɾ��ĳ��Ԫ�ؽڵ�
//�鲢������������
void merger_two_list(linklist* pphead1, linklist* pphead2,linklist* pptail1, linklist* pptail2);
//��������
void list_reserve(linklist* pphead, linklist* pptail);
//�ҵ��������ĸ����
void list_findlfour(linklist phead, linklist ptail);
//9�ҳ��м���
void list_findmid(linklist phead, linklist ptail);