#include <stdio.h>
#include <stdlib.h>

int main() {
	int a[11] = { 4,4,2,3,5,4,6,7,12,4,4 };
	int vote = 1, condidate = a[0];
	for (int i = 1; i < 11; i++) {
		if (a[i] == condidate) vote++;//a[i]Ԫ��ͬ��ѡ�ߣ�Ʊ����1
		else {
			if (vote > 0) vote--;//���Ǻ�ѡ��ʱ��Ʊ������0��Ʊ����һ
			else {
				condidate = a[i];//Ʊ��Ϊ0����ѡ�ߣ������Լ�һƱ
				vote = 1;
			}
		}
	}
	printf("�������г��ִ�������n/2�ε�Ԫ����%d", condidate);
}