#include <stdio.h>
#include <stdlib.h>
 
int main() {
	int a[6] = { 8,6,3,2,8,6 };
	int k = a[0],i;
	for (i = 1; i < 6; i++)
		k ^= a[i];
	int split = k & -k;
	int r=0, t=0;
	for (i = 0; i < 6; i++) {
		if ((a[i] & split )== 0)
			r ^= a[i];
		else
			t ^= a[i];
		}
	printf("数组中两个只出现了一次的数是%d,%d", r, t);
		system("pause");
	return 0;
}