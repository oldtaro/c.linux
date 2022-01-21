#include "func.h"

int main() {
	queue q;
	init(&q);
	int i;
	for (i = 1; i < MaxSize; i++) {
		enqueue(&q, i);
	}
	printf("队头元素%2d\n",q.data[q.front]);
	enqueue(&q, i);
	int k;
	printf("出队元素为：");
	for (i = 1; i < MaxSize; i++) {
		k = dequeue(&q);
		printf("%2d", k);
	}
	dequeue(&q);
	system("pause");
	return 0;
}