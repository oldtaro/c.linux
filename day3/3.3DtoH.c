#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int k, t,j, i = 0;
	char a[100];
	scanf("%d", &k);
	while (k != 0) {
		t = k % 16;
		k = k / 16;
		if (t >= 0 && t <= 9)
			a[i] = t + 48;
		else
			a[i] = t + 55;
		i++;
	}
	for (j = i-1; j >= 0; j--)
		printf("%c", a[j]);
	system("pause");
	return 0;
}