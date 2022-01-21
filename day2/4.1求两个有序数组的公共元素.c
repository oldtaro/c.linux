
#include <stdio.h>
#include <stdlib.h>

int main() {
	int a[10] = { 1,2,3,5,6,7,9,12,16,19 };
	int b[10]={ 0,3,5,6,12,15,17,21,22,30 };
	int i = 0, j = 0;
	while (i < 10 && j < 10) {
		if (a[i] == b[j]) {
			printf("%3d", a[i++]);
			j++;
		}
		else if (a[i] > b[j]) {
			j++;
		}
		else {
			i++;
		}
	}
	
}