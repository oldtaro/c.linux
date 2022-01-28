#include "student.h"

void list_sort_insert(pstu *phead,pstu *ptail,pstu pnew ){
	pstu ppre=*phead,pcur=*phead;
	if (pcur == NULL) { //头尾指针为空，头尾指针指向新节点
		*phead = pnew;
		*ptail = pnew;
	}
	else {
		while(pcur!=NULL){//工作指针total大于新节点total，指针后移
			if (pcur->total > pnew->total) {
				ppre = pcur;
				pcur = pcur->next;
			}
			else {
				break;
			}
		}
		if (pcur == ppre) { //若此时前指针与工作指针相同则应插入头部
			pnew->next = *phead;
			*phead = pnew;
		}
		else if (pcur == NULL) {//若工作指针为空还未找到插入位置则插入尾部
			(*ptail)->next = pnew;
			*ptail = pnew;
		}
		else {                //找到插入位置，正常插入
			ppre -> next = pnew;
			pnew->next = pcur;
		}
	}
}

void print(pstu head, const char* file_name) {
	FILE* fp = fopen(file_name, "w");
	if (fp == NULL) {
		perror("fopen");
		fclose(fp);
		return;
	}
	pstu pcur = head;
	while (pcur != NULL) {
		fprintf(fp, "%d\t %s\t %9s\t %3d\t %3d\t %3d\n",
			pcur->num, pcur->name, pcur->sex, pcur->score[0],
			pcur->score[1], pcur->score[2]);
		pcur = pcur->next;
	}
	fclose(fp);
}