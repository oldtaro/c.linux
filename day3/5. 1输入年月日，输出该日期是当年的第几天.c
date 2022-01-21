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
		if (mon > 2) {//闰年大于二月份要多加上一天
			days += (day + (year % 4 == 0 && year % 100 != 0 || year % 400 == 0));
		}
		else {
			days += day;
		}
		printf("%04d-%02d-%02d是该年第%3d天", year, mon, day, days);
     }
	system("pause");
	return 0;
}