#include <stdio.h>
#include <stdlib.h>

int FindSameElem(int *a, int n1, int* b, int n2,int *c){
	int i = 0, j = 0,k=0;
	while (i < n1 && j < n2) {
		if (a[i] == b[j]) {
			c[k++] = a[i++];
			j++;
		}
		else if (a[i] > b[j]) {
			j++;
		}
		else {
			i++;
		}
	}
	return k;
}

int main() {
	int a[10] = { 1,2,3,5,6,7,9,12,16,19 };
	int b[10] = { 0,3,5,6,12,15,17,21,22,30 };
	int c[10] = { 3,5,6,7,8,9,13,16,19,23 };
	int d[10],i;
	int n1 = FindSameElem(a, 10, b, 10, d);
	int n2=FindSameElem(c, 10, d, n1, d);
	for (i = 0; i < n2; i++) {
		printf("%3d", d[i]);
	}
	system("pause");
	return 0;
}