#include "head.h"

int Makesalt(char *str)
{
    int i,flag;
    str[0] = '$';
    str[1] = '6';
    str[2] = '$';
    srand(time(NULL));//通过时间函数设置随机数种子，使得每次运行结果随机。 for(i = 0; i < STR_LEN; i ++)
    for(i = 3; i < 11; i++)
    {
        flag = rand()%3; switch(flag)
        {
        case 0:
            str[i] = rand()%26 + 'a';
            break; 
        case 1:
            str[i] = rand()%26 + 'A';
            break; 
        case 2:
            str[i] = rand()%10 + '0';
            break;
        }
    }
    return 0; 
}

void getsalt(char *salt,char* passwd)
{
	int i,j;
	for(i=0,j=0;passwd[i]&&j!=3;i++)
	{
		if(passwd[i]=='$')
		{
			++j;
		}
	}
	strncpy(salt,passwd,i-1);
}

//密码验证
int pwd_check(char* usr_name,char* usr_pwd,char* salt)
{
	char pwd[200]={0};
	mysql_seek("usr_info","usr_name",usr_name,3,pwd);
	puts(pwd);
	if(!strcmp(pwd,crypt(usr_pwd,salt)))	
	{
		printf("%s登录成功\n",usr_name);
		return 1;
	}else{
		printf("%s登录失败\n",usr_name);
		return 0;
	}	
}
//用户注册
int usr_register(char* usr_name,char* usr_pwd){
	mysql_insert("usr_info","usr_name",usr_name);
	char salt[15],*pwd;
	Makesalt(salt);
	pwd=crypt(usr_pwd,salt);
	puts(pwd);
	mysql_update("usr_info","usr_name",usr_name,"salt",salt);
	mysql_update("usr_info","usr_name",usr_name,"usr_pwd",pwd);
	printf("%s注册，登陆成功\n",usr_name);
}