#include "func.h"

void print(int* a, int len) {
	for (int i = 0; i < len; i++) {
		printf("%3d", a[i]);
	}
	printf("\n");
}

//ð��
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
//ѡ��
void selectsort(int* a,int len){
	int i, j,min,n;
	for (i = 0; i < len -1; i++) {
		 min=a[i];
		 n = i;
		for (j = i+1; j < len; j++) {//�ҵ���Сֵ
			if (a[j] < min) {
				min = a[j];
				n = j;
			}
		}
		swap(a[i], a[n]);//����Сֵ����
	}
}
//����
void insertsort(int* a, int len) {
	int i, j, temp;
	for (i = 0; i < len; i++) {
		temp = a[i];
		for (j = i - 1; j >= 0; j--) { //Ѱ�Ҳ���λ�ã�����temp����
			if (a[j] > temp) {
				a[j + 1] = a[j];
			}
			else break;
		}
		a[j + 1] = temp;
	}
}
//���Ż���1�ڿӷ�
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
//����
void quicksort(int* a, int low,int high){
	if (low < high) {
		int pivot = partition1(a, low, high);
		quicksort(a, low, pivot - 1);
		quicksort(a, pivot + 1, high);
	}
}
 //qsort �ȽϺ���
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

//����ѵĵ���
void adjustMaxheap(int* a, int len, int adjroot) {
	int dad = adjroot;
	int son = 2 * adjroot + 1;
	while (son < len) {
		if (son + 1 < len && a[son] < a[son + 1]) {//�����Һ�����ѡ�������һ��
			son++;
		}
		if (a[son] > a[dad]) {
			swap(a[son], a[dad]); //�����ڵ�Ԫ��С�ڶ���㣬�򽻻���Ԫ�ز����µ���
			dad = son;
			son = 2 * dad + 1;
		}
		else {
			break;
		}
	}
}

//���ţ������Ϊ��
void heapsort(int* a) {
	int i;
	for (i = MaxSize / 2 - 1; i >= 0; i--) {//��Ŵ��±�0��ʼ,��n/2����㿪ʼ��׹����Ϊ�����
		adjustMaxheap(a,MaxSize,i);
	}
	for (i = 0; i < MaxSize;i++) {        //�����Ѷ��Ͷѵ�Ԫ�أ������µ���Ϊ�����
		swap(a[0], a[MaxSize-1 - i]);
		adjustMaxheap(a,MaxSize-1-i,0);
	}
}

//��������
void countsort(int* a) {
	int count[MaxNum] = { 0 };
	int i, j, k=0;
	for (i = 0; i < MaxSize; i++) { //Ϊÿ��ֵ����
		count[a[i]]++;
	}
	for (i = 0; i < MaxNum; i++) {
		for (j = 0; j < count[i]; j++) { //����
			a[k++] = i;
		}
	}

}
//�鲢
void merge_a(int* a, int low, int mid, int high) {
	int b[MaxSize];
	int i, j, k;
	for (i = low; i <= high; i++) {//�����鸴�Ƶ�b��
		b[i] = a[i];
	}
	for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++) {
		if (b[i] < b[j]) {    //ǰ����������Ԫ�����αȽϣ�С�İ�������a��
			a[k] = b[i++];
		}
		else {
			a[k] = b[j++];
		}
	}
	while (i <= mid) {  //��forѭ���꣬һ�����黹��Ԫ��ʣ�࣬������a��ʣ��ռ�
		a[k++] = b[i++];
	}
	while (j <= high) {
		a[k++] = b[j++];
	}
}

//�鲢����
void merge(int* a,int low,int high) {
	if (low < high) {
		int mid = (low + high)/2;//�������Ϊ���Σ��ݹ�鲢
		merge(a, low, mid);        
		merge(a, mid + 1, high);
		merge_a(a, low, mid, high);
	}
}

