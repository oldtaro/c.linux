#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reserve(char a[],int low, int high) {
	char temp;
	while (low < high) {
		temp = a[low];
		a[low++] = a[high];
		a[high--] = temp;
	} 
}

int main() {
	char a[50];
	gets(a);
	int n = strlen(a);
	reserve(a, 0, n - 1);
	a[n] = ' '; a[n + 1] = '\0';
	int i,s=1,low;
	for (i = 0; i <=n;i++) {
		if (a[i] == ' '&&s==0) {  //Ϊ����sΪ0Ϊ���ʽ�β����¼high
			s = 1;
			reserve(a, low, i-1);
		}
		else if (a[i] != ' ' && s == 1) { //���ǿո���sΪ1�������ʿ�ͷ��¼low
			low = i;
			s = 0;
		}
	}
	puts(a);
	system("pause");
	return 0;
}