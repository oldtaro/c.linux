#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10

typedef struct queue {
	int data[MaxSize];
	int front, rear;
}queue;

void init(queue* p);//��ʼ��
void enqueue(queue* p, int k);//���
int dequeue(queue* p);//����