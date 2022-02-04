#include "compiler.h"

static TkWord keywords[] = {//��tokenֵ��ؼ��ֶ�Ӧ����
	{TK_PLUS,"+",NULL},
	{TK_MINUS,"-",NULL},
	{TK_STAR,"*",NULL},
	{TK_DIVIDE,"/",NULL},
	{TK_MOD,"%",NULL},
	{TK_EQ,"==",NULL},
	{TK_NEQ,"!=",NULL},
	{TK_LT,"<",NULL},
	{TK_LEQ,"<=",NULL},
	{TK_GT,">",NULL},
	{TK_GEQ,">=",NULL},
	{TK_ASSIGN,"=",NULL},
	{TK_POINTSTO,"->",NULL},
	{TK_DOT,".",NULL},
	{TK_AND,"&",NULL},
	{TK_OPENPA,"(",NULL},
	{TK_CLOSEPA,")",NULL},
	{TK_OPENBR,"[",NULL},
	{TK_CLOSEBR,"]",NULL},
	{TK_BEGIN,"{",NULL},
	{TK_END,"}",NULL},
	{TK_SEMICOLON,";",NULL},
	{TK_COMMA,",",NULL},
	{TK_ELLIPSIS,"...",NULL},
	{TK_EOF,"End Of File",NULL},
	{TK_NOTES,"//",NULL},

	{TK_CINT,"���γ���",NULL},
	{TK_CFLOAT,"�����ͳ���",NULL},
	{TK_CCHAR,"�ַ�����",NULL},
	{TK_CSTR,"�ַ�������",NULL},

	{KW_CHAR,"char",NULL},
	{KW_SHORT,"short",NULL},
	{KW_INT,"int",NULL},
	{KW_FLOAT,"float",NULL},
	{KW_DOUBLE,"double",NULL},
	{KW_VOID,"void",NULL},
	{KW_STRUCT,"struct",NULL},

	{KW_IF,"if",NULL},
	{KW_ELSE,"else",NULL},
	{KW_FOR,"for",NULL},
	{KW_WHILE,"while",NULL },
	{KW_CONTINUE,"continue",NULL},
	{KW_BREAK,"break",NULL},
	{KW_RETURN,"return",NULL},
	{TK_IDENT}//TK_IDENT
};

int main() {
	pTkWord hashtable[MAXKEY] = { 0 },cur;
	int keywords_length = sizeof(keywords) / sizeof(TkWord);
	InitHashTable(keywords, keywords_length,hashtable);
	ifstream file;
	file.open("test.txt",ios::in);
	string str,temp;
	int i, err_num, cur_token;
	vector<string> word;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	while (getline(file, str)) {
		word.clear();
		err_num = split(word, str);
		for (i = 0; i < word.size(); i++) {
			temp = word.at(i);
			cur = hashtable[elf_hash(temp)];
			int j = elf_hash(temp);
			if (cur != NULL) {//
				if ((cur->spelling).compare(temp) == 0) {
					printcolor(temp, (tokencode)cur->tkcode);
					continue;
				}else {
					cur = cur->next;
					while (cur!=NULL) {
						if ((cur->spelling).compare(temp) == 0) {
							printcolor(temp, (tokencode)cur->tkcode);
							break;
						}
						cur = cur->next;
					}
					if (cur != NULL) {
						continue;
					}
				}
			}
			if (temp[0] == '"' ) {//����
				cur_token = TK_CSTR;
			}else if(temp[0] == '\''){
				cur_token = TK_CCHAR;
			}else if (isdigit(temp[0])) {
				cur_token = TK_CINT;
			}else if (temp[0] == '/' && temp[1] == '/') {//��ע
				cur_token = TK_NOTES;
			}else {//��������������
				cur_token = TK_IDENT;
			}
			printcolor(temp,(tokencode)cur_token);
		}
		cout << endl;
	}
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	system("pause");
	return 0;
}
