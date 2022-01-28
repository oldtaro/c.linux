#include <stdio.h>
#include <stdlib.h>

int main() {
	int a[11] = { 4,4,2,3,5,4,6,7,12,4,4 };
	int vote = 1, condidate = a[0];
	for (int i = 1; i < 11; i++) {
		if (a[i] == condidate) vote++;//a[i]元素同候选者，票数加1
		else {
			if (vote > 0) vote--;//不是候选者时，票数大于0，票数减一
			else {
				condidate = a[i];//票数为0换候选者，并给自己一票
				vote = 1;
			}
		}
	}
	printf("该数组中出现次数大于n/2次的元素是%d", condidate);
}