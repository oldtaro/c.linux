#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char a[50];
	gets(a);
	int i=0, count = 0,s=1;
	while(i<strlen(a)) {
		if (0!=a[i] && s == 1) {//sΪͳ�Ƶ��ʿ���
			count++;
			s = 0;
		}
		else if (a[i] ==' ') {
			s = 1;
		}
		i++;
	}
	printf("%d", count);
	system("pause");
	return 0;
}