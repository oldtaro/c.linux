#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("输入一串字符与数字\n");
	char c[50], b[50];
	while (gets(c)!=EOF) {
		int i = 0, j = 0;
		for (int n = 0; c[n] != 0; n++) {
			if (c[n] >= '0' && c[n] <= '9') {
				c[j++] = c[n];
			}
			else if (c[n] >= 'a' && c[n] <= 'z' || c[n] >= 'A' && c[n] <= 'Z') {
				b[i++] = c[n];
			}
		}
		for (int k=0; k<i; k++) {
			c[j++] = b[k];
		}
		puts(c);
	}
	system("pause");
	return 0;
}
