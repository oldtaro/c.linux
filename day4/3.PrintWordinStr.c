#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char a[50];
	gets(a);
	int i = 0,s=1;
	while (i < strlen(a)) {
		if (a[i] != ' ') {
			printf("%c", a[i]);
			s = 1;
		}
		else if (a[i] == ' ' && s == 1) {
			printf("\n");
			s = 0;
		}
		i++;
	}
	system("pause");
	return 0;
}
