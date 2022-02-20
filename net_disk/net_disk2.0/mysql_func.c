#include "head.h"

int msql_delete(int argc,char* argv[])
{
	MYSQL *conn;
	const char* server="localhost";
	const char* user="root";
	const char* password="123";
	const char* database="test";
	char query[200]="delete from Person where FirstName='xiong'";
	int t;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("delete success,delete row=%ld\n",(long)mysql_affected_rows(conn));
	}
	mysql_close(conn);
	return 0;
}

//用户表插入新用户
int usrinfo_insert(char* usr_name)
{
	MYSQL *conn;
   // MYSQL_RES *res;
   // MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="insert into usr_info(usr_name)";
	sprintf(query,"%s values('%s')",query,usr_name);
	puts(query);
	int t;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);//执行sql
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("insert success,insert row=%ld\n",(long)mysql_affected_rows(conn));
	}
	mysql_close(conn);
	return 0;
}

//用户信息查找
int usrinfo_seek(char* usr_name,int res_colum,char* res_info)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
	const char* server="localhost";//本地
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";//要访问的数据库名称
	char query[300]="select * from usr_info where usr_name=";
	//sprintf(query,"%s%s%s",query, argv[1],"'");
	sprintf(query,"%s'%s'",query,usr_name);
	// strcpy(query,"select * from Person");//不传参
	puts(query);
	unsigned int t;
	conn=mysql_init(NULL);//要初始化连接
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);//执行sql语句
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));//sql的语法出错
	}else{
	//	printf("Query made...\n");
		res=mysql_use_result(conn);//获取结果
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL){
			//printf("num=%d\n",mysql_num_fields(res));//列数
			//mysql_num_fields获取一行有几列
			sprintf(res_info,"%s",row[res_colum]);
			}
		}else{
			printf("Don't find data\n");
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}

//用户信息更新
int usrinfo_update(char* usr_name,char* update_column,char* update_info)
{
	MYSQL *conn;
	//MYSQL_RES *res;
	//MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="update usr_info set"; 
	sprintf(query,"%s %s='%s' where usr_name='%s'",query,update_column,update_info,usr_name);
	puts(query);
	int t;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("update success,update row=%ld\n",(long)mysql_affected_rows(conn));
	}
	mysql_close(conn);
	return 0;
}

//查找子文件
int seek_child_file(int code,int usr_id,int res_colum,char* res_info)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
	const char* server="localhost";//本地
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";//要访问的数据库名称
	char query[300]="select * from file_info where precode=";
	//sprintf(query,"%s%s%s",query, argv[1],"'");
	sprintf(query,"%s%d and usr_id=%d",query,code,usr_id);
	// strcpy(query,"select * from Person");//不传参
	puts(query);
	unsigned int t;
	conn=mysql_init(NULL);//要初始化连接
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);//执行sql语句
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));//sql的语法出错
	}else{
	//	printf("Query made...\n");
		res=mysql_use_result(conn);//获取结果
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL){
			//printf("num=%d\n",mysql_num_fields(res));//列数
			//mysql_num_fields获取一行有几列
			sprintf(res_info,"%s%s ",res_info,row[res_colum]);
			}
		}else{
			printf("Don't find data\n");
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	puts(res_info);
	return 0;
}
//查文件信息
int seek_file_info(char* cond_column,int code,int res_colum,char* res_info)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
	const char* server="localhost";//本地
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";//要访问的数据库名称
	char query[300]="select * from file_info where";
	//sprintf(query,"%s%s%s",query, argv[1],"'");
	sprintf(query,"%s %s=%d",query,cond_column,code);
	// strcpy(query,"select * from Person");//不传参
	puts(query);
	unsigned int t;
	conn=mysql_init(NULL);//要初始化连接
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);//执行sql语句
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));//sql的语法出错
	}else{
	//	printf("Query made...\n");
		res=mysql_use_result(conn);//获取结果
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL){
			//printf("num=%d\n",mysql_num_fields(res));//列数
			//mysql_num_fields获取一行有几列
			sprintf(res_info,"%s",row[res_colum]);
			}
		}else{
			printf("Don't find data\n");
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
//查询下一级文件code
int next_level_file(int code,char* file_name,int res_colum,char* res_info)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
	const char* server="localhost";//本地
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";//要访问的数据库名称
	char query[300]="select * from file_info where precode=";
	//sprintf(query,"%s%s%s",query, argv[1],"'");
	sprintf(query,"%s%d and file_name='%s'",query,code,file_name);
	// strcpy(query,"select * from Person");//不传参
	puts(query);
	unsigned int t;
	conn=mysql_init(NULL);//要初始化连接
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);//执行sql语句
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));//sql的语法出错
	}else{
	//	printf("Query made...\n");
		res=mysql_use_result(conn);//获取结果
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL){
			//printf("num=%d\n",mysql_num_fields(res));//列数
			//mysql_num_fields获取一行有几列
			sprintf(res_info,"%s",row[res_colum]);
			}
		}else{
			printf("Don't find data\n");
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}		
//插入新文件信息
int insert_new_file(int precode,char type,int usr_id,char* file_name,int file_size,char* md5){
	MYSQL *conn;
    // MYSQL_RES *res;
    // MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="insert into file_info(precode,type,usr_id,file_name,file_size,md5)";
	sprintf(query,"%s values(%d,'%c',%d,'%s',%d,'%s')",query,precode,type,usr_id,file_name,file_size,md5);
	puts(query);
	int t;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);//执行sql
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("insert success,insert row=%ld\n",(long)mysql_affected_rows(conn));
	}
	mysql_close(conn);
	return 0;
}