#include <stdio.h>
#include <stdlib.h>

int main() {
	char c[50];
	while (gets(c) != EOF) {
		int k = 0,i,j=0;
		for (i = 0; c[i] != 0; i++) {
			if (c[i] != 32) {
				c[j++]=c[i]; 
				k = 1;
			}
			else if (c[i] == 32 && k == 1) {
				c[j++]=c[i];
				k = 0;
			}
		}
		for (i = j; c[i] != 0; i++) {
			c[i] = 0;
		}
		puts(c);
	}
	system("pause");
	return 0;
}