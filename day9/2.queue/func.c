#include "func.h"

//��ʼ��
void init(queue* p) {
	p->front = 0;
	p->rear = 0;
}

//���
void enqueue(queue* p,int k) {
	if ((*p).front == ((*p).rear + 1) % MaxSize) {//��β��һ���Ƕ�ͷʱ����
		printf("��������\n");
		return;
	}
	else {
		(*p).data[(*p).rear] = k;
		(*p).rear = ((*p).rear + 1) % MaxSize;
	}
}

//����
int dequeue(queue* p) {
	if (p->front == p->rear) {
		printf("\n����Ϊ��");
		return -1;
	}
	else {
		int k=(*p).data[p->front];
		(*p).front = ((*p).front + 1) % MaxSize;
		return k;
	}
}
