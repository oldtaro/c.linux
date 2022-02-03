/*参考了课上的模板增加了一些新功能和改进：
* 1.增加备注着色
* 2.区别了数据类型关键字和控制语句关键字着色
* 3.简单处理了hash冲突 "]"和文件结束符,其他未发现
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
	/* 运算符及分隔符 */
	TK_PLUS,		// + 加号
	TK_MINUS,		// - 减号
	TK_STAR,		// * 星号
	TK_DIVIDE,		// / 除号
	TK_MOD,			// % 求余运算符
	TK_EQ,			// == 等于号
	TK_NEQ,			// != 不等于号
	TK_LT,			// < 小于号
	TK_LEQ,			// <= 小于等于号
	TK_GT,			// > 大于号
	TK_GEQ,			// >= 大于等于号
	TK_ASSIGN,		// = 赋值运算符 
	TK_POINTSTO,	// -> 指向结构体成员运算符
	TK_DOT,			// . 结构体成员运算符
	TK_AND,         // & 地址与运算符
	TK_OPENPA,		// ( 左圆括号
	TK_CLOSEPA,		// ) 右圆括号
	TK_OPENBR,		// [ 左中括号
	TK_CLOSEBR,		// ] 右中括号
	TK_BEGIN,		// { 左大括号
	TK_END,			// } 右大括号
	TK_SEMICOLON,	// ; 分号    
	TK_COMMA,		// , 逗号
	TK_ELLIPSIS,	// ... 省略号
	TK_EOF,			// 文件结束符

	/* 常量 */
	TK_CINT,		// 整型常量
	TK_CFLOAT,		// 浮点型常量
	TK_CCHAR,		// 字符常量
	TK_CSTR,		// 字符串常量

	/* 关键字 */
	KW_CHAR,		// char关键字
	KW_SHORT,		// short关键字
	KW_INT,			// int关键字
	KW_FLOAT,		//float关键字
	KW_DOUBLE,		//double关键字
	KW_VOID,		// void关键字  
	KW_STRUCT,		// struct关键字   
	KW_IF,			// if关键字
	KW_ELSE,		// else关键字
	KW_FOR,			// for关键字
	KW_CONTINUE,	// continue关键字
	KW_BREAK,		// break关键字   
	KW_RETURN,		// return关键字

	/* 标识符 */
	TK_IDENT
};

typedef enum e_TokenCode tokencode;

typedef struct TkWord {
	int tkcode;
	string spelling;
	struct TkWord* next;
}TkWord,*pTkWord;


void printcolor(string str, tokencode token);//颜色打印
int elf_hash(string key);//哈希函数
void InitHashTable(TkWord keywords[], int length, pTkWord hashtable[]);//哈希表初始化
int split(vector<string>& word, string str);//划分
