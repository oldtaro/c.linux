/*�ο��˿��ϵ�ģ��������һЩ�¹��ܺ͸Ľ���
* 1.���ӱ�ע��ɫ
* 2.�������������͹ؼ��ֺͿ������ؼ�����ɫ
* 3.�򵥴�����hash��ͻ "]"���ļ�������,����δ����
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <memory.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctype.h>
using namespace std;
#define MAXKEY 1000


enum e_TokenCode
{
	/* ��������ָ��� */
	TK_PLUS,		// + �Ӻ�
	TK_MINUS,		// - ����
	TK_STAR,		// * �Ǻ�
	TK_DIVIDE,		// / ����
	TK_MOD,			// % ���������
	TK_EQ,			// == ���ں�
	TK_NEQ,			// != �����ں�
	TK_LT,			// < С�ں�
	TK_LEQ,			// <= С�ڵ��ں�
	TK_GT,			// > ���ں�
	TK_GEQ,			// >= ���ڵ��ں�
	TK_ASSIGN,		// = ��ֵ����� 
	TK_POINTSTO,	// -> ָ��ṹ���Ա�����
	TK_DOT,			// . �ṹ���Ա�����
	TK_AND,         // & ��ַ�������
	TK_OPENPA,		// ( ��Բ����
	TK_CLOSEPA,		// ) ��Բ����
	TK_OPENBR,		// [ ��������
	TK_CLOSEBR,		// ] ��������
	TK_BEGIN,		// { �������
	TK_END,			// } �Ҵ�����
	TK_SEMICOLON,	// ; �ֺ�    
	TK_COMMA,		// , ����
	TK_ELLIPSIS,	// ... ʡ�Ժ�
	TK_EOF,			// �ļ�������

	/* ���� */
	TK_CINT,		// ���ͳ���
	TK_CFLOAT,		// �����ͳ���
	TK_CCHAR,		// �ַ�����
	TK_CSTR,		// �ַ�������

	/* �ؼ��� */
	KW_CHAR,		// char�ؼ���
	KW_SHORT,		// short�ؼ���
	KW_INT,			// int�ؼ���
	KW_FLOAT,		//float�ؼ���
	KW_DOUBLE,		//double�ؼ���
	KW_VOID,		// void�ؼ���  
	KW_STRUCT,		// struct�ؼ���   
	KW_IF,			// if�ؼ���
	KW_ELSE,		// else�ؼ���
	KW_FOR,			// for�ؼ���
	KW_CONTINUE,	// continue�ؼ���
	KW_BREAK,		// break�ؼ���   
	KW_RETURN,		// return�ؼ���

	/* ��ʶ�� */
	TK_IDENT
};

typedef enum e_TokenCode tokencode;

typedef struct TkWord {
	int tkcode;
	string spelling;
	struct TkWord* next;
}TkWord,*pTkWord;


void printcolor(string str, tokencode token);//��ɫ��ӡ
int elf_hash(string key);//��ϣ����
void InitHashTable(TkWord keywords[], int length, pTkWord hashtable[]);//��ϣ���ʼ��
int split(vector<string>& word, string str);//����
