#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int FindMax(int a, int b, int c) {
	if (a >=c && a >=b) return 0;    //优先级abc，确保相等是三个函数返回值不同
	else if (b > a && b >=c) return 1;
	else if(c>a&&c>b) return 2;
}
int FindMid(int a, int b, int c) {   //优先级bca
	if (a > c && a < b||a>b&&a<c) return 0;
	else if (b >=a && b <=c|| b >= c && b <=a) return 1;
	else if(a>=c && c > b|| c >=a && c < b) return 2;
}
int FindMin(int a, int b, int c) {  //优先级cab
	if (a < c && a <=b) return 0;
	else if (b < a && b < c) return 1;
	else if (c<=a && c <= b) return 2;
}
int main() {
	char c[50];
	gets(c);
	int alp = 0, num = 0, oth = 0;
	for (int i = 0; c[i]!=0; i++) {
		if (c[i] >= '0' && c[i] <= '9') {
			num++;
		}
		else if (c[i] >= 'a' && c[i] <= 'z' || c[i] >= 'A' && c[i] <= 'Z') {
			alp++;
		}
		else {
			oth++;
		}
	}
	char a[18] = " alp   num   oth  ";
	int b[3] = { alp,num,oth },j;
	int n1 = FindMax(alp,num,oth);
	int n2 = FindMid(alp, num, oth);
	int n3 = FindMin(alp, num, oth);//将最大值，次大值，最小值与齐各自相对应
	for (j = b[n1]+1; j >0; j--) {
		if (b[n1] != b[n2] && b[n2] != b[n3]) { //将统计值相等与不相等是分开讨论
			if (j == b[n1] + 1) {
				printf("%3d\n", b[n1]);
			}
			else if (b[n1] >= j && j > b[n2] + 1) {
				printf("*****\n");
			}
			else if (j == b[n2] + 1) {
				printf("***** %3d\n", b[n2]);
			}
			else if (j <= b[n2] && j > b[n3] + 1) {
				printf("***** *****\n");
			}
			else if (j == b[n3] + 1) {
				printf("***** ***** %3d\n", b[n3]);
			}
			else {
				printf("***** ***** *****\n");
			}
		}
		else if (b[n1] == b[n2] && b[n2] != b[n3]) {
			if (j == b[n1] + 1) {
				printf("%3d   %3d\n", b[n1],b[n2]);
			}
			else if (b[n1] >= j && j > b[n3] + 1) {
				printf("***** *****\n");
			}
			else if (j == b[n3] + 1) {
				printf("***** ***** %3d\n", b[n3]);
			}
			else {
				printf("***** ***** *****\n");
			}
		}
		else if (b[n1] != b[n2] && b[n2] == b[n3]) {
			if (j == b[n1] + 1) {
				printf("%3d\n", b[n1]);
			}
			else if (b[n1] >= j && j > b[n2] + 1) {
				printf("*****\n");
			}
			else if (j == b[n2] + 1) {
				printf("***** %3d   %3d\n", b[n2],b[n3]);
			}
			else {
				printf("***** ***** *****\n");
			}
		}
		else {
			if (j == b[n1] + 1) {
				printf("%3d   %3d   %3d\n", b[n1],b[n2],b[n3]);
			}
			else {
				printf("***** ***** *****\n");
			}
		}
	}
	for (j = n1 * 6; j < (n1+1) * 6; j++) printf("%c", a[j]);//打印对应统计量名
	for (j = n2 * 6; j < (n2 + 1) * 6; j++) printf("%c", a[j]);
	for (j = n3 * 6; j < (n3 + 1)*6; j++) printf("%c", a[j]);
	printf("\n");
	system("pause");
	return 0;
}