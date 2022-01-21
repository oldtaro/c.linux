#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int CMP(char a[], char b[]) {
	int i = 0;
	while (a[i] == b[i]) {
		if (a[i] != 0) {
			i++;
		}
		else {
			return 0;
			break;
		}
	}
	if (a[i] > b[i]) {
		return 1;
	}
	else {
		return -1;
	}
}
int main() {
	char a[20] = { 0 }, b[20] = { 0 };
	gets(a);
	gets(b);
	int k= CMP(a, b);
	printf("%d", k);
	 system("pause");
	 return 0;
}