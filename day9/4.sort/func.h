#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define swap(a,b) {int temp;temp=a;a=b;b=temp;} //∫Í∂®“Âswap
#define MaxSize 10
#define MaxNum 100

void print(int* a, int len);
void bubblesort(int* a, int len);//√∞≈›≈≈–Ú
void selectsort(int* a, int len);//—°‘Ò≈≈–Ú
void insertsort(int* a, int len);//≤Â»Î≈≈–Ú
void quicksort(int* a, int low, int high);//øÏ≈≈
int compare(const void* low, const void* high);
void heapsort(int* a);//∂—≈≈–Ú
void countsort(int* a);//º∆ ˝≈≈–Ú
void merge(int* a, int low, int high);//πÈ≤¢≈≈–Ú
