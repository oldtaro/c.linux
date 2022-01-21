#include <stdio.h>
#include <stdlib.h>
int Partition(int a[], int low, int high) {
	int pivot = a[low];
	while (low < high) {
		while (low < high && a[high] >= pivot) high--;
		a[low] = a[high];
		while (low < high && a[low] <= pivot) low++;
		a[high] = a[low];
	}
	a[low] = pivot;
	return low;
}
void QuickSort(int a[], int low, int high) {
	if (low < high) {
		int temp = Partition(a, low, high);
		QuickSort(a, low, temp - 1);
		QuickSort(a, temp + 1, high);
	}
	else return;
}

int main() {
	int a[10] = { 99,87,52,32,1,12,2,20,23,17 };
	QuickSort(a, 0, 9);
	int i=1,x=a[0],y=a[1],r=abs(x-y);
	while (i<9) {
		if ((a[i + 1] - a[i]) < r) {
			r = a[i + 1] - a[i];
			y = a[i + 1];
			x = a[i++];
		}
		else i++;
     }
	printf("数组中两元素差绝对值最小的是%2d和%2d", x, y);
	system("pause");
	return 0;
}