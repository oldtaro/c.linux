#include <stdio.h>
#include <stdlib.h>

int main() {
	int a[1001], i;
	for (i = 0; i < 1000; i++) {
		a[i] = i + 1;
	}
	a[1000] = 45;//��������������
	int sum1=0,sum=0;
	for (i = 1; i <= 1000; i++) {
		sum1 += i;
	}
	for (i = 0; i < 1001; i++) {
		sum += a[i];
	}
	printf("1001��Ԫ����Ψһ�����������ε�Ԫ����%3d", sum - sum1);
	system("pause");
	return 0;
}