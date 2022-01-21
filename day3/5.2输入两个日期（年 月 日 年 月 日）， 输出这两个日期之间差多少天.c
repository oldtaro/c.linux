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
	int year1, mon1, day1, year2, mon2, day2;
	while (scanf("%d%d%d%d%d%d",&year1,&mon1,&day1,&year2,&mon2,&day2) != EOF){
		int i,sum=0;
		if ((year1 > year2) || (year1 == year2 && mon1 > mon2) || (year1 == year2 && mon1 == mon2 && day1 > day2)) {
			for (i = year2; i < year1; i++) {
				sum += (365 + (i % 4 == 0 && i % 100 != 0 || i % 400 == 0));//������ݼ������������1
			}
			int days1 = Daysofyear(year1, mon1, day1);//�ֱ������������ڵ���������
			int days2 = Daysofyear(year2, mon2, day2);
			sum = sum + days1 - days2;                //��ݼ��������ȥС�����������ϴ���������  
		}
		else {
			for (i = year1; i < year2; i++) {
				sum += (365 + (i % 4 == 0 && i % 100 != 0 || i % 400 == 0));
			}
			int days1 = Daysofyear(year1, mon1, day1);
			int days2 = Daysofyear(year2, mon2, day2);
			sum = sum + days2 - days1;
		}
		printf("%04d-%02d-%02d��%04d-%02d-%02d���%d��", year1, mon1, day1, year2, mon2, day2, sum);
}
	system("pause");
	return 0;
}