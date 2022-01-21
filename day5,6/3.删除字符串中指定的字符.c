
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("输入一组字符串\n");
	char c[50],a[50];
	while (gets(c) != EOF) {
		printf("输入你要删除的字符\n");
		gets(a);
		int i, j, k,l=0;
		for (i = 0; c[i]!=0; i++) {
			k = 0;
			for (j = 0; a[j] != 0; j++) {//源字符串字符与要删除字符串比较
				if (c[i] == a[j]) {
					k = 1; 
					break;
				}
			}
			if(k==0){                //若不是要删除的字符这i，l同时后移并赋值；若是则仅移动i
				c[l++] = c[i];
			}
		}
		for (i = l; c[i] != 0; i++) {//在保留字符串后添加'\0'
			c[i] = 0;
		}
		puts(c);
	}
	system("pause");
	return 0;
}