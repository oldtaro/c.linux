#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char a[50], b[50];
	printf("����������Ҫ��ӵĴ�����\n");
	gets(a); gets(b);
	int l1 = strlen(a), l2 = strlen(b);
	int n = (l1 > l2 ? l1 : l2)+1, k = 0, i;       //ȷ���Ǹ���λ���ಢ��ֵ����ʼ����λ��Ϣ
	memmove(&a[n - l1], &a[0], l1); memmove(&b[n - l2], &b[0], l2);//����
	memset(a, '0', n - l1); memset(b, '0', n - l2);   //�����ǰ��λ�ó�ʼ��Ϊ��0��
	char* c = (char*)malloc(n);
	for (i = n - 1; i >= 0; i--) {
		c[i] = a[i] + b[i] - 48 + k;
		if (c[i] > 57) {                 //������λ
			c[i] -= 10;
			k = 1;
		}
	}
	if (n == 51 && k == 1) {
		printf("���");
	}
	else {
		c[n] = 0;
		printf("���������ĺ�Ϊ");
		puts(c);
	}
	system("pause");
	return 0;
}
