#include "func.h"

int main() {
	queue q;
	init(&q);
	int i;
	for (i = 1; i < MaxSize; i++) {
		enqueue(&q, i);
	}
	printf("��ͷԪ��%2d\n",q.data[q.front]);
	enqueue(&q, i);
	int k;
	printf("����Ԫ��Ϊ��");
	for (i = 1; i < MaxSize; i++) {
		k = dequeue(&q);
		printf("%2d", k);
	}
	dequeue(&q);
	system("pause");
	return 0;
}