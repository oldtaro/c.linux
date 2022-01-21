#include <stdio.h>
#include <stdlib.h>

int main() {
	int i,j ;
	for(i=4;i>=0;i--){
		for (j=i;j>=0;j--)
			printf(" ");
		for(j=0;j<5-i;j++)
			printf("* ");
		printf("\n");
	}
	for (i = 1; i <= 4; i++) {
		for (j = i; j >= 0; j--)
			printf(" ");
		for (j = 0; j < 5 - i; j++)
			printf("* ");
		printf("\n");
	}
	system("pause");
	return 0;

}