#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	char c;
	while (rewind(stdin),scanf("%c", &c) != EOF) {
		if (c >= 97 && c <= 122)
			printf("%c\n", c - 32);//��ΪСд�������д
		else
			printf("error\n");//������Сд��ĸ�򷵻�error
	}
	system("pause");
	return 0;
}