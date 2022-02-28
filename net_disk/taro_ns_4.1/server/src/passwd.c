#include "factory.h"

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
int pwd_check(pwd_t* ppt,int cfd)
{
	cmd_train cur;
	cur.cmd_type=LOGIN;
	strcpy(cur.buf,ppt->salt);
	send_cmd(&cur,cfd);//发送盐值
	usrinfo_seek(ppt->usr_name,3,ppt->usr_pwd);
	recv_cmd(&cur,cfd);//接收密文
	if(!strcmp(cur.buf,ppt->usr_pwd))	
	{
		printf("%s登录成功\n",ppt->usr_name);
		return 1;
	}else{
		printf("%s登录失败\n",ppt->usr_name);
		return 0;
	}	
}
//用户注册
int usr_register(pwd_t* ppt,int cfd){
	cmd_train cur;
	cur.cmd_type=REGISTER;
	Makesalt(ppt->salt);
	strcpy(cur.buf,(ppt->salt));
	send_cmd(&cur,cfd);//发送盐值
	mysql_insert("usr_info","usr_name",ppt->usr_name);
	mysql_update("usr_info","usr_name",ppt->usr_name,"salt",ppt->salt);

	recv_cmd(&cur,cfd);//接收密文
	mysql_update("usr_info","usr_name",ppt->usr_name,"usr_pwd",cur.buf);
	printf("%s注册，登陆成功\n",ppt->usr_name);
}