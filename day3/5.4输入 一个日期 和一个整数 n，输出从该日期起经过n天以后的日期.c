#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int Daysofyear(int year, int mon, int day) {//�Ӻ�������������ڸ��������������
	int a[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int days = 0;
	for (int i = 0; i < mon - 1; i++) {
		days += a[i];
	}
	if (mon > 2) {
		days += (day + (year % 4 == 0 && year % 100 != 0 || year % 400 == 0));
	}
	else {
		days += day;
	}
	return days;
}

int main() {
	printf("�������ڣ���֮������");
	int a[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int year, mon, day,n;
	while (scanf("%d%d%d%d", &year, &mon, &day,&n) != EOF) {
		int k = n + Daysofyear(year,mon,day);//�Ƚ����ڶ��䵽����1��1�գ������������
		int year1, mon1;
		for (year1 = year; k > (365+(year1%4==0&&year1%100!=0||year1%400==1)); year1++) {
			k -= (365 + (year1 % 4 == 0 && year1 % 100 != 0 || year1 % 400 == 1));
		}
		for (mon1 = 1; k > a[mon1 - 1]; mon++) {
			if (mon1 == 2) {
				k -= (a[mon1] + (year1 % 4 == 0 && year1 % 100 != 0 || year1 % 400 == 1));
			}
			else {
				k -= a[mon1];
			}
		}
		printf("%04d-%02d-%02d֮���%d����%04d-%02d-%02d", year, mon, day, n, year1, mon1, k);
	}
	system("pause");
	return 0;
}