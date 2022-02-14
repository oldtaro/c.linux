#include "ftp.h"

static char* file_type(mode_t md)
{
	if(S_ISREG(md))
	{
		return "-";	
	}else if(S_ISDIR(md))
	{
		return "d";
	}else if(S_ISFIFO(md))
	{
		return "p";
	}else 
	{
		return "o" ;
	}
}
//执行ls -l得到的数据传递给客户端
static void do_ls(psession_t ps) 
{
	DIR* pdir = opendir("./");
	if(pdir == NULL)
	{
		int flag = -1 ;
		send(ps ->sess_sfd, &flag, sizeof(int), 0);
	}else
	{
		struct dirent* mydir ;
		int len ;
		while( (mydir = readdir(pdir)) != NULL)//读取目录
		{
			if(strncmp(mydir->d_name, ".", 1) == 0 || strncmp(mydir->d_name,"..", 2) == 0)
			{
				continue ;
			}
			struct stat mystat;
			bzero(&mystat, sizeof(stat));
			stat(mydir->d_name, &mystat);//获取某个文件的信息
			bzero(ps ->sess_buf, 1024);
			sprintf(ps ->sess_buf, "%-2s%-20s %10ldB", file_type(mystat.st_mode),mydir->d_name, mystat.st_size );
			len =  strlen(ps ->sess_buf);
			send(ps ->sess_sfd, &len, sizeof(int), 0);//发送数据给客户端
			sendn(ps ->sess_sfd, ps ->sess_buf, len);
		}
		len = 0 ;
		send(ps ->sess_sfd, &len, sizeof(int), 0);
	}

}
//直接通过chdir改变路径,通过getcwd把当前路径传会给客户端
static void do_cd(psession_t ps) 
{
	char dir[128]= "";
	sscanf(ps ->sess_buf +3, "%s", dir);
	chdir(dir);
	getcwd(dir, 128);
	int len = strlen(dir);
	send(ps ->sess_sfd, &len, sizeof(int), 0);
	sendn(ps ->sess_sfd, dir, strlen(dir));
}
//通过getcwd拿到当前路径，并发送给客户端
static void do_pwd(psession_t ps) 
{
	bzero(ps ->sess_buf, BUF_SIZE);
	getcwd(ps ->sess_buf, BUF_SIZE);
	int len = strlen(ps ->sess_buf);
	send(ps ->sess_sfd, &len, sizeof(int), 0);
	sendn(ps ->sess_sfd, ps ->sess_buf, len);

}
//服务器传文件给客户端
static void do_gets(psession_t ps) 
{
	char file_name[256];
	int file_pos = 5 ;
	while(bzero(file_name, 256),sscanf(ps ->sess_buf + file_pos,"%s", file_name ) == 1)
	{
		file_pos += strlen(file_name) + 1; 
		if(upload(ps ->sess_sfd, file_name) == 0)
		{
			printf(" file-> %s upload success\n", file_name);
		}else 
		{
			printf(" file-> %s upload failed\n", file_name);
		}

	}

}
//上传文件
static void do_puts(psession_t ps) //puts a.txt b.txt
{
	char file_name[256];
	int file_pos = 5 ;
	//puts file,文件名在file_name中
	while(bzero(file_name, 256), sscanf(ps ->sess_buf + file_pos,"%s", file_name) == 1)
	{
		file_pos += strlen(file_name) + 1 ;//为了puts后面跟多个文件名
		if(download(ps -> sess_sfd, file_name) == 0)
		{
			printf("file -> %s download success \n", file_name);
		}else
		{

			printf("file -> %s download failed \n", file_name);
		}
	}
}
//使用脚本的rm命令来删除文件，目前只能删除普通文件
static void do_remove(psession_t ps)// remove file 
{
	char cmd[256] ="" ;
	sprintf(cmd, "rm -f %s", ps ->sess_buf + 7);
	system(cmd);
	bzero(ps ->sess_buf, BUF_SIZE);
	sprintf(ps ->sess_buf, "%s removed", ps ->sess_buf + 7);
	int len = strlen(ps ->sess_buf);
	send(ps ->sess_sfd, &len, sizeof(int),0);
	sendn(ps ->sess_sfd, ps ->sess_buf, len);
}
void client_handle(psession_t ps)
{

	socket_t fd_client = ps -> sess_sfd ;
	int cmd_len = 0 ;
	int recv_ret ;
	while(1)
	{
		bzero(ps -> sess_buf, BUF_SIZE);
		recv_ret = recv(fd_client, &cmd_len, sizeof(int),0);//收到客户端的火车头
		if(cmd_len == 0 || recv_ret == 0)
		{
			printf("client exit !\n");
			close(ps ->sess_sfd);
			free(ps);
			exit(1);
		}
		recvn(fd_client, ps->sess_buf, cmd_len);//收火车车厢
		if(strncmp("cd", ps ->sess_buf, 2) == 0)
		{
			do_cd(ps);
		}else if(strncmp("ls", ps ->sess_buf, 2) == 0)
		{
			do_ls(ps);
		}else if( strncmp("puts", ps ->sess_buf, 4)== 0)
		{
			do_puts(ps);
		}else if( strncmp("gets", ps ->sess_buf, 4)== 0)
		{
			do_gets(ps);

		}else if( strncmp("remove", ps ->sess_buf, 6)== 0)
		{
			do_remove(ps);

		}else if(strncmp("pwd", ps ->sess_buf, 3) == 0) 
		{
			do_pwd(ps);

		}else 
		{
			continue ;
		}


	}
}
