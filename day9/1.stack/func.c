#include "func.h"

//≥ı ºªØ
void stack_init(stack* p) {
	p->head = NULL;
	p->size = 0;
}

//—π’ª
void stack_push(stack* p,int k) {
	snode* pnew = (snode*)calloc(1, sizeof(snode));
	pnew->data = k;
	pnew->next = p->head;
	p->head = pnew;
	p->size++;
}

//µØ’ª
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

//∑µªÿ’ª∂•‘™Àÿ÷µ
int topele(stack s) {
	return s.head->data;
}

//∑µªÿ’ª¥Û–°
int stack_size(stack s) {
	return s.size;
}
//≈–ø’
int isempty(stack s) {
	if (s.size == 0) {
		return 1;
	}
	else {
		return 0;
	}
}