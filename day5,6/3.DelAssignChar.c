
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("����һ���ַ���\n");
	char c[50],a[50];
	while (gets(c) != EOF) {
		printf("������Ҫɾ�����ַ�\n");
		gets(a);
		int i, j, k,l=0;
		for (i = 0; c[i]!=0; i++) {
			k = 0;
			for (j = 0; a[j] != 0; j++) {//Դ�ַ����ַ���Ҫɾ���ַ����Ƚ�
				if (c[i] == a[j]) {
					k = 1; 
					break;
				}
			}
			if(k==0){                //������Ҫɾ�����ַ���i��lͬʱ���Ʋ���ֵ����������ƶ�i
				c[l++] = c[i];
			}
		}
		for (i = l; c[i] != 0; i++) {//�ڱ����ַ��������'\0'
			c[i] = 0;
		}
		puts(c);
	}
	system("pause");
	return 0;
}