#include "func.h"

//��ʼ��
void stack_init(stack* p) {
	p->head = NULL;
	p->size = 0;
}

//ѹջ
void stack_push(stack* p,int k) {
	snode* pnew = (snode*)calloc(1, sizeof(snode));
	pnew->data = k;
	pnew->next = p->head;
	p->head = pnew;
	p->size++;
}

//��ջ
int  stack_pop(stack* p) {
	if (p->head == NULL) {
		return -1;
	}
	else {
		int t = p->head->data;
		snode* q = p->head;
		p->head = p->head->next;
		free(q);
		p->size--;
		return t;
	}
}

//����ջ��Ԫ��ֵ
int topele(stack s) {
	return s.head->data;
}

//����ջ��С
int stack_size(stack s) {
	return s.size;
}
//�п�
int isempty(stack s) {
	if (s.size == 0) {
		return 1;
	}
	else {
		return 0;
	}
}