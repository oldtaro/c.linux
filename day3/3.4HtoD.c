#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	char c[100];
	int i,j;
	while (rewind(stdin), scanf("%s", &c) != EOF) {
		int t = 1, r = 0;
		for (i = 0; c[i] != '\0'; i++);//�ȼ����ַ�����
		for(j=i-1;j>=0;j--)
		{
			for (int l = 1; l < i-j; l++)
				t *= 16;                //���λ16����Ȩ��
			if (c[j] >= '0' && c[j] <= '9')
				r += (c[j] - '0') * t;
			if (c[j] >= 'a' && c[j] <= 'z')
				r += (c[j] - 'a') * t;
			if (c[j] >= 'A' && c[j] <= 'Z')
				r += (c[j] - 'A') * t;      //ÿλ����10����
		}
	
		printf("%d", r);
	}
	system("pause");
	return 0;
}