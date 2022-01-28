#include <stdio.h>
#include <stdlib.h>

int main() {
	int a[10] = { 0,6,5,4,56,71,12,45,31,654 };
	int max1, max2,i;
	if (a[0] > a[1]) {
		max1 = a[0];
		max2 = a[1];
	}
	else {
		max1 = a[1];
		max2 = a[2];
	}
	for (i = 2; i < 10; i++) {
		if (a[i] > max1) {
			max2 = max1;
			max1 = a[i];
		}
		else if (a[i] > max2) {
			max2 = a[i];
		}
	}
	printf("×î´óÖµÊÇ%d,´Î´óÖµÊÇ%d", max1, max2);
	system("pause");
	return 0;
}