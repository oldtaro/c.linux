#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	int num;
	char name[20];
	int score1;
	int score2;
	int score3;
	int totalscore;
}stu,*pstu;

int main() {
	 stu sarr[5];
	 printf("����5λѧ����ѧ�ţ����������ſη���\n");
	 int i;
	 for (i = 0; i < 5; i++) {
		 scanf("%d%s%d%d%d", &sarr[i].num, &sarr[i].name, &sarr[i].score1,
			 &sarr[i].score2, &sarr[i].score3);
		 sarr[i].totalscore = sarr[i].score1+ sarr[i].score2+ sarr[i].score3;
	 }
	 printf("------------------------------------------------------------------------------\n");
	 for (i = 0; i < 5; i++) {
		 stu temp;
		 for (int j = 0; j < 4 - i; j++) {
			 if (sarr[j].num > sarr[j + 1].num) {
				 temp = sarr[j + 1];
				 sarr[j + 1] = sarr[j];
				 sarr[j] = temp;
			 }
		 }
	 }
	 for (i = 0; i < 5; i++) {
		 printf("ѧ��%-2d����:%-9s����1:%-4d����2:%-4d����3:%-4d�ܷ�:%-3d\n", sarr[i].num, sarr[i].name,
			 sarr[i].score1, sarr[i].score2, sarr[i].score3, sarr[i].totalscore);
	 }//����ѧ�ŵ������ȫ��ѧ����Ϣ��ÿ��ѧ������Ϣһ��
	 printf("------------------------------------------------------------------------------\n");
	 stu max1= sarr[0], max2=sarr[0], max3= sarr[0];
	 for (i = 1; i < 5; i++) {
		 if (sarr[i].score1 > max1.score1) {
			 max1 = sarr[i];
		 }
		 if (sarr[i].score2 > max2.score2) {
			 max2 = sarr[i];
		 }
		 if (sarr[i].score3 > max3.score3) {
			 max3 = sarr[i];
		 }
	 }
	 printf("�γ�һ��߷�:%-4d%-2d��ͬѧ%-9s\n�γ̶���߷�:%-4d%-2d��ͬѧ%-9s\n�γ�����߷�:%-4d%-2d��ͬѧ%-9s\n",
		 max1.score1, max1.num, max1.name, max2.score2, max2.num, max2.name, max3.score3, max3.num, max3.name);
	 //���������߷�
	 printf("------------------------------------------------------------------------------\n");
	 int average1=0, average2=0, average3=0;
	 for (i = 0; i < 5; i++) {
		 average1 += sarr[i].score1;
		 average2 += sarr[i].score2;
		 average3 += sarr[i].score3;
	 }
	 printf("�γ�һƽ����:%-4d\n�γ̶�ƽ����:%-4d\n�γ���ƽ����:%-4d\n", average1 / 5, average2 / 5, average3 / 5);
	 //�������ƽ����
	 printf("------------------------------------------------------------------------------\n");
	 for (i = 0; i < 5; i++) {
		 stu temp;
		 for (int j = 0; j < 4 - i; j++) {
			 if (sarr[j].totalscore < sarr[j + 1].totalscore) {
				 temp = sarr[j + 1];
				 sarr[j + 1] = sarr[j];
				 sarr[j] = temp;
			 }
		 }
	 }
	 printf("�ܷ�������\n");
	 for (i = 0; i < 5; i++) {
		 printf("%-9s:%-4d\n",sarr[i].name, sarr[i].totalscore);
	 }//���ܷ�����
	 printf("------------------------------------------------------------------------------\n");
	 system("pause");
	 return 0;
}