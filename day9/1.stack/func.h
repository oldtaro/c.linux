#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct snode {
	int data;
	struct snode* next;
}snode,*psnode;

typedef struct stack {
	snode* head; //ջ��
	int size;
}stack,*pstack;

void stack_init(stack* p);//ջ�ĳ�ʼ��
void stack_push(stack* p, int k);//ѹջ
int  stack_pop(stack* p);//��ջ
int topele(stack s);//����ջ��Ԫ��ֵ
int stack_size(stack s);//����ջ��С
int isempty(stack s);//�п�