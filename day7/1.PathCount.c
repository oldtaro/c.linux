#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int Ways(int x,int y) {
	if (x == 0 || y ==0 ) {//�ݹ���ڣ����е���������ʱ�ͽ�һ��·��
		return 1;
	}
	int w = Ways(x - 1, y) + Ways(x, y - 1);
	return w;
}

int main() {
	printf("����Ҫ��·����������\n");
	int n, m,w;
	while (scanf("%d%d", &m,& n) != EOF) {
		w = Ways(m, n);
		printf("(0,0)��(%d,%d)�� %d ��·��", m, n, w);
	}
}