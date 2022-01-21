#include <stdio.h>
#include <stdlib.h>

void FindOnlytwo(int a[],int n, int r1,int r2) {
	int split = r1 & -r1;
	int res1 = 0, res2 = 0,i;
	for ( i = 0; i < n; i++) {
		if ((split & a[i])>0) {
			res1 ^= a[i];
		}
		else {
			res2 ^= a[i];
		}
	}
	if ((split & r2)>0) {
		res1 ^= r2;
	}
	else {
		res2 ^= r2;
	}
	printf(",%d,%d\n", res1, res2);
}

int main() {
	int a[7] = { 8,6,4,3,2,6,8 };
	int i,j, t = 1;
	int count1, count2;
	int res1 = 0, res2 = 0;
	for (i = 0; i < 32; i++) {
		count1 = 0; count2 = 0;
		for (j =0 ; j < 7; j++) {
			if ((a[j] & t)>0) {
				res1 ^= a[j]; //不需要辅助数组，按位与结果相同直接异或，由count和异或结果判断是否划分完毕
				count1++;
			}
			else {
				res2 ^= a[j];
				count2++;
			}
		}
		if (count1 % 2 == 0 && res1 != 0) {
			printf("%d", res2);
			FindOnlytwo(a,7,res1,res2); //修改调用函数接口，划分好后奇数组的异或结果可直接确定一个数，直接将其添加到原数组即可运用找俩数方法
			break;
		}
		if (count2 % 2 == 0 && res2 != 0) {
			printf("%d", res1);
			FindOnlytwo(a, 7, res2, res1);
			break;
		}
		t = t << 1;              //若未分开，t则右移一位
	}
}