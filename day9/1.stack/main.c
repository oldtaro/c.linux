#include "func.h"

int main() {
	stack s;
	stack_init(&s);
	for (int i = 1; i < 9; i++) {
		stack_push(&s, i);
	}
	printf("ջ��Ԫ��Ϊ %2d\n", s.head->data);
	int t = stack_pop(&s);
	int x = topele(s);
	printf("ջ��Ԫ��Ϊ %2d\n", x);
	printf("����ջԪ��ֵ %2d\n", t);
	int y = stack_size(s);
	printf("��ǰջ��С %2d\n", y);
	for (int i = 0; i < 6; i++) {
		stack_pop(&s);
	}
	if (isempty(s)) {
		printf("��ǰջ��");
	}
	system("pause");
	return 0;
}