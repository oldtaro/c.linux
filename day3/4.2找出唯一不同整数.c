#include <stdio.h>
#include <stdlib.h>

int main() {
	int a[5] = { 8,6,2,6,8 };
	int k = a[0];
	for (int i = 1; i < 5; i++) {
		k ^= a[i];
	}
	printf("%d", k);
	system("pause");
	return 0;
}