#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int year,mon,day;
	int a[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	while (scanf("%d%d%d", &year, &mon, &day) != EOF) {
		int days = 0;
		for (int i = 0; i < mon - 1; i++) {
			days += a[i];
		}
		if (mon > 2) {//������ڶ��·�Ҫ�����һ��
			days += (day + (year % 4 == 0 && year % 100 != 0 || year % 400 == 0));
		}
		else {
			days += day;
		}
		printf("%04d-%02d-%02d�Ǹ����%3d��", year, mon, day, days);
     }
	system("pause");
	return 0;
}