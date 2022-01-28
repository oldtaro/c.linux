#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10


typedef struct student {
	int num;
	char name[20];
	char sex[6];
	int score[3],total;
	struct student* next;
}stu,*pstu;

void list_sort_insert(pstu* phead, pstu* ptail, pstu* ppnew);//有序插入
void print(pstu head, const char* file_name);//打印到文件
