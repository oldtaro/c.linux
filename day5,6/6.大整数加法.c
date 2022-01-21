#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char a[50], b[50];
	printf("输入两个你要相加的大整数\n");
	gets(a); gets(b);
	int l1 = strlen(a), l2 = strlen(b);
	int n = (l1 > l2 ? l1 : l2)+1, k = 0, i;       //确定那个数位数多并赋值，初始化进位信息
	memmove(&a[n - l1], &a[0], l1); memmove(&b[n - l2], &b[0], l2);//对齐
	memset(a, '0', n - l1); memset(b, '0', n - l2);   //对齐后前面位置初始化为‘0’
	char* c = (char*)malloc(n);
	for (i = n - 1; i >= 0; i--) {
		c[i] = a[i] + b[i] - 48 + k;
		if (c[i] > 57) {                 //发生进位
			c[i] -= 10;
			k = 1;
		}
	}
	if (n == 51 && k == 1) {
		printf("溢出");
	}
	else {
		c[n] = 0;
		printf("这两个数的和为");
		puts(c);
	}
	system("pause");
	return 0;
}
