#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct snode {
	int data;
	struct snode* next;
}snode,*psnode;

typedef struct stack {
	snode* head; //栈顶
	int size;
}stack,*pstack;

void stack_init(stack* p);//栈的初始化
void stack_push(stack* p, int k);//压栈
int  stack_pop(stack* p);//弹栈
int topele(stack s);//返回栈顶元素值
int stack_size(stack s);//返回栈大小
int isempty(stack s);//判空