#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int Ways(int x,int y) {
	if (x == 0 || y ==0 ) {//递归出口，即有到达坐标轴时就仅一条路径
		return 1;
	}
	int w = Ways(x - 1, y) + Ways(x, y - 1);
	return w;
}

int main() {
	printf("输入要求路径数的坐标\n");
	int n, m,w;
	while (scanf("%d%d", &m,& n) != EOF) {
		w = Ways(m, n);
		printf("(0,0)→(%d,%d)有 %d 条路径", m, n, w);
	}
}