#include <stdio.h>
#include <stdlib.h>

int mystrlen(char a[]) {
	int i,count=0;
	for (i = 0; a[i] != 0; i++) {
		count++;
	}
	return count;
}

int main() {
	char a[20] = { 0 };
	gets(a);
	int k=mystrlen(a);
	printf("%d", k);
	system("pause");
	return 0;
}