#include "func.h"

void print(int* a, int len) {
	for (int i = 0; i < len; i++) {
		printf("%3d", a[i]);
	}
	printf("\n");
}

//冒泡
void bubblesort(int* a, int len) {
	int i, j, flag;
	for (i = 0; i < len; i++) {
		flag = 0;
		for (j = 0; j < len - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				flag = 1;
			}
		}
		if (flag == 0) return;
	}
}
//选择
void selectsort(int* a,int len){
	int i, j,min,n;
	for (i = 0; i < len -1; i++) {
		 min=a[i];
		 n = i;
		for (j = i+1; j < len; j++) {//找到最小值
			if (a[j] < min) {
				min = a[j];
				n = j;
			}
		}
		swap(a[i], a[n]);//与最小值交换
	}
}
//插入
void insertsort(int* a, int len) {
	int i, j, temp;
	for (i = 0; i < len; i++) {
		temp = a[i];
		for (j = i - 1; j >= 0; j--) { //寻找插入位置，大于temp后移
			if (a[j] > temp) {
				a[j + 1] = a[j];
			}
			else break;
		}
		a[j + 1] = temp;
	}
}
//快排划分1挖坑法
int partition1(int* a, int low, int high) {
	    int pivotkey = a[low];
		while (low < high) {
			while (low < high && a[high] >= pivotkey) high--;
			a[low] = a[high];
			while (low < high && a[low] <= pivotkey) low++;
			a[high] = a[low];
		}
		a[low] = pivotkey;
		return low;
}
//快排
void quicksort(int* a, int low,int high){
	if (low < high) {
		int pivot = partition1(a, low, high);
		quicksort(a, low, pivot - 1);
		quicksort(a, pivot + 1, high);
	}
}
 //qsort 比较函数
int compare(const void* low, const void* high) {
	int* x = (int*)low;
	int* y = (int*)high;
	if (*x > *y) {
		return 1;
	} 
	else if (*x < *y) {
		return -1;
	}
	else {
		return 0;
	}
 }

//大根堆的调整
void adjustMaxheap(int* a, int len, int adjroot) {
	int dad = adjroot;
	int son = 2 * adjroot + 1;
	while (son < len) {
		if (son + 1 < len && a[son] < a[son + 1]) {//在左右孩子中选出大的那一个
			son++;
		}
		if (a[son] > a[dad]) {
			swap(a[son], a[dad]); //若父节点元素小于儿结点，则交换两元素并向下调整
			dad = son;
			son = 2 * dad + 1;
		}
		else {
			break;
		}
	}
}

//堆排，大根堆为例
void heapsort(int* a) {
	int i;
	for (i = MaxSize / 2 - 1; i >= 0; i--) {//编号从下标0开始,从n/2个结点开始下坠调整为大根堆
		adjustMaxheap(a,MaxSize,i);
	}
	for (i = 0; i < MaxSize;i++) {        //交换堆顶和堆底元素，并重新调整为大根堆
		swap(a[0], a[MaxSize-1 - i]);
		adjustMaxheap(a,MaxSize-1-i,0);
	}
}

//计数排序
void countsort(int* a) {
	int count[MaxNum] = { 0 };
	int i, j, k=0;
	for (i = 0; i < MaxSize; i++) { //为每个值计数
		count[a[i]]++;
	}
	for (i = 0; i < MaxNum; i++) {
		for (j = 0; j < count[i]; j++) { //回填
			a[k++] = i;
		}
	}

}
//归并
void merge_a(int* a, int low, int mid, int high) {
	int b[MaxSize];
	int i, j, k;
	for (i = low; i <= high; i++) {//将数组复制到b中
		b[i] = a[i];
	}
	for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++) {
		if (b[i] < b[j]) {    //前后两段数组元素依次比较，小的按序填入a中
			a[k] = b[i++];
		}
		else {
			a[k] = b[j++];
		}
	}
	while (i <= mid) {  //若for循环完，一段数组还有元素剩余，则填入a中剩余空间
		a[k++] = b[i++];
	}
	while (j <= high) {
		a[k++] = b[j++];
	}
}

//归并排序
void merge(int* a,int low,int high) {
	if (low < high) {
		int mid = (low + high)/2;//将数组分为两段，递归归并
		merge(a, low, mid);        
		merge(a, mid + 1, high);
		merge_a(a, low, mid, high);
	}
}

