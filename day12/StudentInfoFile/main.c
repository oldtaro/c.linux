#include "student.h"


int main() {
	FILE* fp = fopen("student.txt", "r");
	int i=0;
	stu s[N];
	pstu head = NULL, tail = NULL;
	if (fp == NULL) {
		perror("fopen");
		return 1;
	}
	while (fscanf(fp, "%d%s%s%d%d%d", &s[i].num, &s[i].name,&s[i].sex,
		&s[i].score[0],&s[i].score[1], &s[i].score[2]) != EOF) {
		s[i].total = s[i].score[0]+s[i].score[1]+s[i].score[2];
		s[i].next = NULL;
		list_sort_insert(&head, &tail, &s[i]);
		i++;
	}
	fclose(fp);
	print(head, "student.txt");
	system("pause");
	return 0;
}