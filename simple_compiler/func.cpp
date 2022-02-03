#include "compiler.h"
//颜色打印
void printcolor(string str,tokencode token) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (token >= TK_IDENT) { //函数灰色
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	}else if (token>=KW_IF) {//控制语句关键字紫色
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_RED);
	}else if (token >= KW_CHAR) { //数据类型关键字蓝色
        SetConsoleTextAttribute(h, FOREGROUND_BLUE| FOREGROUND_INTENSITY);
	}else if (token >= TK_CINT) { //常量褐色
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
	}else if (token >= TK_PLUS) {  //运算符红色
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
//elf哈希函数
int elf_hash(string key) {
	int h = 0, g,i=0;
	while (key[i]) {
		h = (h << 4) + key[i++];
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MAXKEY;
}
//初始化关键字哈希表，拉链法简单处理一下冲突
void InitHashTable(TkWord keywords[],int length,pTkWord hashtable[]) {
	int i, j;
	pTkWord p;
	for (i = 0; i < length; i++) {
		j = elf_hash(keywords[i].spelling);
		if (hashtable[j]==NULL) {
			hashtable[j] = &keywords[i];
		}
		else {
			p= hashtable[j];
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = &keywords[i];
		}
	}
}
//划分
int split(vector<string> &word,string str) {
	string temp;
	for (int i = 0; i < str.length(); i++) {
		if (isalpha(str[i])||str[i]=='_') {//变量名以字母或‘_’打头,关键字字母打头
			temp.clear();
			while (isalnum(str[i]) || str[i] == '_') {
				temp.push_back(str[i++]);
			}
			word.push_back(temp);
			i--;
		}
		else if (isdigit(str[i])) {//数字常量以数字打头
			temp.clear();
			while (isdigit(str[i])) {
				temp.push_back(str[i++]);
				}
			if(str[i]=='.'){
				temp.push_back(str[i++]);
				while (isdigit(str[i])) {
					temp.push_back(str[i++]);
				}
			}
			word.push_back(temp);
			i--;
		}
		else if (str[i]=='"') {//字符串常量
			temp.clear();
			temp.push_back(str[i++]);
			while (str[i] !='"') {
				temp.push_back(str[i++]);
			}
			temp.push_back(str[i]);
			word.push_back(temp);
		}
		else if (str[i] =='\'') {//字符常量
			temp.clear();
			temp.push_back(str[i++]);
			while (str[i] != '\'') {
				temp.push_back(str[i++]);
			}
			temp.push_back(str[i]);
			word.push_back(temp);
		}
		else if (str[i]=='/'&&str[i+1]=='/') {//备注
			temp.clear();
			while (str[i]) {
				temp.push_back(str[i++]);
			}
			word.push_back(temp);
		}
		else if (str[i]=='\t') {
			temp.clear();
			temp.insert(0,4,' ');
			word.push_back(temp);
		}
		else if(isprint(str[i])) {//其余可打印字符单个存储
			temp.clear();
			temp.push_back(str[i]);
			word.push_back(temp);
		}
	}
	return 0;
}