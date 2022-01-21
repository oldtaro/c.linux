#include "func.h"

int main() {
	int* a = (int*)malloc(MaxSize * sizeof(int));
	int i;
	srand(time(NULL));
	for ( i = 0; i < MaxSize; i++){
		a[i] = rand() % 100;
	}                        //Ëæ»úÊý
	time_t start, end;
	start = time(NULL);
	print(a,MaxSize);
	/*bubblesort(a,MaxSize);
	selectsort(a,MaxSize);
	insertsort(a, MaxSize);
	quicksort(a, 0, MaxSize-1);
	qsort(a,MaxSize,sizeof(int),compare);
	heapsort(a);
	countsort(a);*/
	merge(a, 0, MaxSize - 1);
	end = time(NULL);
	printf("start=%lld,end=%lld,use time=%lld\n", start, end, end - start);
	print(a, MaxSize);
}