#include "func.h"

//初始化
void init(queue* p) {
	p->front = 0;
	p->rear = 0;
}

//入队
void enqueue(queue* p,int k) {
	if ((*p).front == ((*p).rear + 1) % MaxSize) {//队尾下一个是队头时已满
		printf("队列已满\n");
		return;
	}
	else {
		(*p).data[(*p).rear] = k;
		(*p).rear = ((*p).rear + 1) % MaxSize;
	}
}

//出队
int dequeue(queue* p) {
	if (p->front == p->rear) {
		printf("\n队列为空");
		return -1;
	}
	else {
		int k=(*p).data[p->front];
		(*p).front = ((*p).front + 1) % MaxSize;
		return k;
	}
}
