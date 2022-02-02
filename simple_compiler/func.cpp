#include "compiler.h"
//��ɫ��ӡ
void printcolor(string str,tokencode token) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (token >= TK_IDENT) { //������ɫ
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	}else if (token >= KW_CHAR) { //�ؼ�����ɫ
        SetConsoleTextAttribute(h, FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	}else if (token >= TK_CINT) { //������ɫ
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
	}else if (token >= TK_PLUS) {  //�������ɫ
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	if (-1 == str[0]) {
		printf("\n  end of file");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE |
			FOREGROUND_INTENSITY);
	}else {
		cout<<str;
	}
}
//elf��ϣ����
int elf_hash(string key) {
	int h = 0, g,i=0;
	while (key[i]) {
		h = (h << 4) + key[i++];
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= -g;
	}
	return h % MAXKEY;
}
//��ʼ���ؼ��ֹ�ϣ��
void InitHashTable(TkWord keywords[],int length,pTkWord hashtable[]) {
	for (int i = 0; i < length; i++) {
		hashtable[elf_hash(keywords[i].spelling)] = &keywords[i];
	}
}
//����
int split(vector<string> &word,string str) {
	string temp;
	for (int i = 0; i < str.length(); i++) {
		if (isalnum(str[i])||str[i]=='_') {//����������ĸ��_����ͷ,�ؼ�����ĸ��ͷ
			temp.clear();
			while (isalnum(str[i]) || str[i] == '_') {
				temp.push_back(str[i++]);
			}
			word.push_back(temp);
			i--;
		}
		else if (isdigit(str[i])) {//���ֳ��������ִ�ͷ
			temp.clear();
			while (isdigit(str[i])) {
				temp.push_back(str[i++]);
				}
			if(str[i]=='.'){
				temp.push_back('.');
			}
			while (isdigit(str[i])) {
				temp.push_back(str[i++]);
			}
			word.push_back(temp);
			i--;
		}
		else if (str[i]=='"') {//�ַ�������
			temp.clear();
			temp.push_back(str[i++]);
			while (str[i] !='"') {
				temp.push_back(str[i++]);
			}
			temp.push_back(str[i]);
			word.push_back(temp);
		}
		else if (str[i] =='\'') {//�ַ�����
			temp.clear();
			temp.push_back(str[i++]);
			while (str[i] != '\'') {
				temp.push_back(str[i++]);
			}
			temp.push_back(str[i]);
			word.push_back(temp);
		}
		else if (str[i]=='/'&&str[i+1]=='/') {//��ע
			temp.clear();
			while (str[i]!='\n') {
				temp.push_back(str[i]);
			}
			word.push_back(temp);
			i--;
		}
		else if (str[i]=='\t') {
			temp.clear();
			temp.insert(0,4,' ');
			word.push_back(temp);
		}
		else if(isprint(str[i])) {//����ɴ�ӡ�ַ������洢
			temp.clear();
			temp.push_back(str[i]);
			word.push_back(temp);
		}
	}
	return 0;
}