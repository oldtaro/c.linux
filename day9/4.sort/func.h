#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define swap(a,b) {int temp;temp=a;a=b;b=temp;} //�궨��swap
#define MaxSize 10
#define MaxNum 100

void print(int* a, int len);
void bubblesort(int* a, int len);//ð������
void selectsort(int* a, int len);//ѡ������
void insertsort(int* a, int len);//��������
void quicksort(int* a, int low, int high);//����
int compare(const void* low, const void* high);
void heapsort(int* a);//������
void countsort(int* a);//��������
void merge(int* a, int low, int high);//�鲢����
