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

//插入新行
int mysql_insert(char* table_name,char* column,char* ins_value)
{
	MYSQL *conn;
   // MYSQL_RES *res;
   // MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="insert into";
	sprintf(query,"%s %s(%s) values('%s')",query,table_name,column,ins_value);
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

//数据库数据查找
int mysql_seek(char* table_name,char* column,char* seek_info,int res_colum,char* res_info)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
	const char* server="localhost";//本地
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";//要访问的数据库名称
	char query[300]="select * from";
	//sprintf(query,"%s%s%s",query, argv[1],"'");
	sprintf(query,"%s %s where %s='%s'",query,table_name,column,seek_info);
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

//数据更新
int mysql_update(char* table_name,char* column,char* cond_info,char* update_column,char* update_info)
{
	MYSQL *conn;
	//MYSQL_RES *res;
	//MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="1234";
	const char* database="net_disk";
	char query[200]="update"; 
	sprintf(query,"%s %s set %s='%s' where %s='%s'",query,table_name,update_column,update_info,column,cond_info);
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