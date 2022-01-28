#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	char c;
	while (rewind(stdin),scanf("%c", &c) != EOF) {
		if (c >= 97 && c <= 122)
			printf("%c\n", c - 32);//若为小写则输出大写
		else
			printf("error\n");//若不是小写字母则返回error
	}
	system("pause");
	return 0;
}