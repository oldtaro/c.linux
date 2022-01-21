
#include <stdio.h>
#include <stdlib.h>

int main() {
	char c[50];
	while (gets(c)!=EOF) {
		for (int i = 0; c[i] != 0; i++) {
			if (c[i] != 32) {
				printf("%c", c[i]);
			}
			else {
				printf("%%020");
			}
		}
	}
	system("pause");
	return 0;
}