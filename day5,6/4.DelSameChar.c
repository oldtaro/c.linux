#include <stdio.h>
#include <stdlib.h>

int main() {
	int a[10] = { 1,1,2,2,2,3,5,5,6,6 };
	int i, j=1,k=a[0];
	for (i = 1; i < 10; i++) {   //i����
		if (a[i] != k) {
			a[j++] = a[i];      //���������ظ�ֵʱ��j++������ֵ
			k = a[i];
		}
	}
	for (i = j; i < 10; i++) {
		a[i] = 0;
	}
	for (i = 0; i < j; i++) {
		printf("%3d", a[i]);
	}
	system("pause");
	return 0;
}