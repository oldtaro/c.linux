#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10

typedef struct queue {
	int data[MaxSize];
	int front, rear;
}queue;

void init(queue* p);//初始化
void enqueue(queue* p, int k);//入队
int dequeue(queue* p);//出队