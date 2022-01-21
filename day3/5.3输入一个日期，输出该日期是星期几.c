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

int DuringDays(int year,int mon, int day ) {//��2020-1-5�������գ�Ϊ��׼����
	int i, sum = 0;
		if ((year > 2020) || (year == 2020 && mon > 1) || (year == 2020 && mon == 1 && day > 5)) {
			for (i = 2020; i < year; i++) {
				sum += (365 + (i % 4 == 0 && i % 100 != 0 || i % 400 == 0));//������ݼ������������1
			}
			int days = Daysofyear(year, mon, day);//�������ڵ���������
			sum = sum + days - 5;                //��ݼ��������ȥС�����������ϴ���������  
		}
		else {
			for (i = year; i < 2020; i++) {
				sum += (365 + (i % 4 == 0 && i % 100 != 0 || i % 400 == 0));
			}
			int days = Daysofyear(year, mon, day);
			sum = sum + 5 - days;
		}
	return sum;
}
int main() {
	int year, mon, day;
	while (scanf("%d%d%d", &year, &mon, &day) != EOF) {
		int d = DuringDays(year, mon, day);//�����Ӻ��������׼�������
		if ((year > 2020) || (year == 2020 && mon > 1) || (year == 2020 && mon == 1 && day > 5)) {
			d = d % 7;
		}//���ڻ�׼֮��ֱ�Ӽ��ȡ��
		else {
			d = 7-d%7;
		}
		if (d != 0) {
				printf("%04d-%02d-%02d������%d\n", year, mon, day, d);
		}
			else {
			printf("%04d-%02d-%02d��������\n", year, mon, day);
		}
	}
	system("pause");
	return 0;
}