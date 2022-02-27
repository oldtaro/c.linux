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

//表插入新行
int mysql_insert(char* table_name,char* column,char* insert_info)
{
	MYSQL *conn;
   // MYSQL_RES *res;
   // MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="insert into";
	sprintf(query,"%s %s(%s) values('%s')",query,table_name,column,insert_info);
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

//信息更新
int mysql_update(char* table_name,char* cond_column,char* cond_info,char* update_column,char* update_info)
{
	MYSQL *conn;
	//MYSQL_RES *res;
	//MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="update"; 
	sprintf(query,"%s %s set %s='%s' where %s='%s'",query,table_name,update_column,update_info,cond_column,cond_info);
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
	return 0;
}
//查上级文件信息
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
//查询文件MD5
int seek_file_md5(int precode,char* file_name,char* md5)
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
	sprintf(query,"%s precode=%d and file_name='%s'",query,precode,file_name);
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
			if(row=mysql_fetch_row(res)){
				sprintf(md5,"%s",row[6]);
				mysql_free_result(res);
				mysql_close(conn);
				return 1;
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

//file_pool 文件索引计数更新
int index_add(char* md5)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	int index_count;
	char count[32]={0};
	char query[300]="select * from file_pool where md5";
	sprintf(query,"%s='%s'",query,md5);
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
		res=mysql_use_result(conn);//获取结果
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL){
			//printf("num=%d\n",mysql_num_fields(res));//列数
			//mysql_num_fields获取一行有几列
			sprintf(count,"%s",row[1]);
			}
		}else{
			printf("Don't find data\n");
		}
		mysql_free_result(res);
	}
	
	index_count=atoi(count)+1;
	char query1[200]="update file_pool set index_count"; 
	sprintf(query1,"%s=%d where md5='%s'",query1,index_count,md5);
	puts(query1);

	t=mysql_query(conn,query1);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("update success,update row=%ld\n",(long)mysql_affected_rows(conn));
	}
	mysql_close(conn);
	return 0;
}

//文件池中文件是否存在
int file_is_exist(char* md5)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	//MYSQL_ROW row;//一行的数据是存在row中间
	const char* server="localhost";//本地
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";//要访问的数据库名称
	char query[300]="select * from file_pool where md5";
	//sprintf(query,"%s%s%s",query, argv[1],"'");
	sprintf(query,"%s='%s'",query,md5);
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
			if(mysql_fetch_row(res)){
				mysql_free_result(res);
				mysql_close(conn);
				return 1;
			}else{
				mysql_free_result(res);
				mysql_close(conn);
				return 0;
			}
			
		}else{
			printf("Don't find data\n");
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}

//插入文件池
int insert_file_pool(char* md5,off_t file_size){
	MYSQL *conn;
    // MYSQL_RES *res;
    // MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="insert into file_pool(index_count,file_size,md5)";
	sprintf(query,"%s values(%d,%ld,'%s')",query,1,file_size,md5);
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

int file_size_inpool(char* md5,char* file_size)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
	const char* server="localhost";//本地
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";//要访问的数据库名称
	char query[300]="select * from file_pool where md5";
	//sprintf(query,"%s%s%s",query, argv[1],"'");
	sprintf(query,"%s='%s'",query,md5);
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
			sprintf(file_size,"%s",row[2]);
			}
		}else{
			printf("Don't find data\n");
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
//更新文件池文件大小信息
int update_size_inpool(char* md5,off_t file_size)
{
	MYSQL *conn;
	//MYSQL_RES *res;
	//MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="update file_pool set file_size"; 
	sprintf(query,"%s=%ld where md5='%s'",query,file_size,md5);
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
//更新文件大小信息
int update_file_size(int precode,char* file_name,off_t file_size)
{
	MYSQL *conn;
	//MYSQL_RES *res;
	//MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="update file_info set file_size"; 
	sprintf(query,"%s=%ld where precode=%d and file_name='%s'",query,file_size,precode,file_name);
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
