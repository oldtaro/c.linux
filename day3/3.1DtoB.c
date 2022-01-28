#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(){
	int k,t,r=0,i=1;
scanf("%d", &k);
while (k != 0) {
	t = k % 2;
	k = k / 2;
	int j;
	for (j = 1; j < i; j++)
		t *= 10;
	r += t;
	i++;
   }
printf("%d", r);
system("pause");
return 0;
}