#include "student.h"

void list_sort_insert(pstu *phead,pstu *ptail,pstu pnew ){
	pstu ppre=*phead,pcur=*phead;
	if (pcur == NULL) { //ͷβָ��Ϊ�գ�ͷβָ��ָ���½ڵ�
		*phead = pnew;
		*ptail = pnew;
	}
	else {
		while(pcur!=NULL){//����ָ��total�����½ڵ�total��ָ�����
			if (pcur->total > pnew->total) {
				ppre = pcur;
				pcur = pcur->next;
			}
			else {
				break;
			}
		}
		if (pcur == ppre) { //����ʱǰָ���빤��ָ����ͬ��Ӧ����ͷ��
			pnew->next = *phead;
			*phead = pnew;
		}
		else if (pcur == NULL) {//������ָ��Ϊ�ջ�δ�ҵ�����λ�������β��
			(*ptail)->next = pnew;
			*ptail = pnew;
		}
		else {                //�ҵ�����λ�ã���������
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