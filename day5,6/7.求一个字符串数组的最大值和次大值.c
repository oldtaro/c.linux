#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void big(char *a[], int size, char** big1, char** big2) {
	int i, j;
	char* c;
	for (i = 0; i < 2; i++) {
		for (j = size-1; j > i; j--) {
			if (strcmp(a[j], a[j - 1]) > 0) {
				c = a[j];
				a[j] = a[j-1];
				a[j-1] = c;
			}
		}                                                              
	}
	*big1= a[0];
	*big2 = a[1];
}

int main() {
	char c[5][6] = { "hello","world","how","are","you" };
	char* a[5];
	for (int i = 0; i < 5; i++) {
		a[i] = c[i];
	}
	char* big1, * big2;
	big(a, 5, &big1, &big2);
	printf("最大字符串是 %s,次大字符串是 %s\n", big1, big2);
	system("pause");
	return 0;
}