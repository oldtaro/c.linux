#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct BiNode {
	int data;
	struct BiNode* left, * right;
}BiNode,*BiTree;

typedef struct lnode {
	int data;
	struct lnode* next;
}lnode,*linklist;

typedef struct queue {
	lnode* front, * rear;
}queue;

void midOrder(BiTree p);//÷––Ú±È¿˙