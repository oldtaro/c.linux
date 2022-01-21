#include <stdio.h>
#include <stdlib.h>

int FindSameElem(int* a, int n1, int* b, int n2, int* c) {
	int i = 0, j = 0, k = 0;
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
	int a[5][5] = { {1,2,3,17},{2,3,4},{2,3,6,7} ,{1,2,3,9,10},{2,3,6,15,41} };
	int b[5];
	int n = FindSameElem(a[0], 5, a[1], 5, b);
	for (int i = 2; i < 5; i++) {
		n = FindSameElem(a[i], 5, b, n, b);
	}
	for (int j = 0; j < n; j++) {
		printf("%3d", b[j]);
	}
}