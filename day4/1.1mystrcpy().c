#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void CPY(char a[], char b[]) {
	int i;
	for (i =0;b[i]!=0; i++) {  
		a[i] = b[i];
	}
}

int main() {
	char a[20] = { 0 }, b[20] = {0};
	gets(a); 
	gets(b);
	CPY(a, b);
	puts(a);
}