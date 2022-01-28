#include <stdio.h>
#include <stdlib.h>

int main() {
	char a = ' ', b = '*';
	int i,j;
	for (i = 0; i <= 5; i++) {
		for (j = 5 - i; j >= 0; j--)
			printf("%c", a);
		printf("%c", b);
		for (j = 1; j <= 2 * i - 1; j++)
			printf("%c", a);
		if(i!=0)
		printf("%c", b);
		printf("\n");
	}
	for (i = 4; i >= 0; i--) {
		for (j = 5 - i; j >= 0; j--)
			printf("%c", a);
		printf("%c", b);
		for (j = 1; j <= 2 * i - 1; j++)
			printf("%c", a);
		if (i != 0)
			printf("%c", b);
		printf("\n");
	}
	system("pause");
	return 0;
}

	