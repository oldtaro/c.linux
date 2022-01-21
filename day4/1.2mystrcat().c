#include <stdio.h>
#include <stdlib.h>

void mystrcat(char a[], char b[]) {
	int i,j;
	for (i = 0; a[i] !=0 ; i++);
	for (j = 0; b[j] != 0; j++) {
		a[i++] = b[j];
	}
	a[i] = 0;
}

int main() {
	char a[20] = { 0 }, b[20] = { 0 };
	gets(a);
	gets(b);
	mystrcat(a, b);
	puts(a);
}