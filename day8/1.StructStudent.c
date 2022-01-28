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
	 printf("输入5位学生的学号，姓名，三门课分数\n");
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
		 printf("学号%-2d姓名:%-9s分数1:%-4d分数2:%-4d分数3:%-4d总分:%-3d\n", sarr[i].num, sarr[i].name,
			 sarr[i].score1, sarr[i].score2, sarr[i].score3, sarr[i].totalscore);
	 }//按照学号递增输出全部学生信息，每个学生的信息一行
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
	 printf("课程一最高分:%-4d%-2d号同学%-9s\n课程二最高分:%-4d%-2d号同学%-9s\n课程三最高分:%-4d%-2d号同学%-9s\n",
		 max1.score1, max1.num, max1.name, max2.score2, max2.num, max2.name, max3.score3, max3.num, max3.name);
	 //输出各课最高分
	 printf("------------------------------------------------------------------------------\n");
	 int average1=0, average2=0, average3=0;
	 for (i = 0; i < 5; i++) {
		 average1 += sarr[i].score1;
		 average2 += sarr[i].score2;
		 average3 += sarr[i].score3;
	 }
	 printf("课程一平均分:%-4d\n课程二平均分:%-4d\n课程三平均分:%-4d\n", average1 / 5, average2 / 5, average3 / 5);
	 //输出各课平均分
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
	 printf("总分排名：\n");
	 for (i = 0; i < 5; i++) {
		 printf("%-9s:%-4d\n",sarr[i].name, sarr[i].totalscore);
	 }//按总分排名
	 printf("------------------------------------------------------------------------------\n");
	 system("pause");
	 return 0;
}