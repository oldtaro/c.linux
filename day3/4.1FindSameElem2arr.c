#include <stdio.h>
#include <stdlib.h>

int main() {
	int a[10] = { 1,2,3,6,7,9,12,15,16,19 };
	int b[10] = { 1,5,6,10,12,15,17,19,20,21 };
	int reslut[10];
	int i=0, j=0,k=0;
	while (i < 10 && j < 10) {
		if (a[i] == b[j]) {
			reslut[k++] = a[i];
			i++;
			j++;
		}
		else if (a[i] < b[j]) {
			i++;
		}
		else {
			j++;
		}
    }
	for (int n = 0; n < k; n++) {
		printf("%3d", reslut[n]);
	}
	system("pause");
	return 0;
}