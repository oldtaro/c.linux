#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	MYSQL *conn;
	//MYSQL_RES *res;
	//MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="123";
	const char* database="test";
	char query[200]="update Person set LastName='"; 
	sprintf(query,"%s%s%s",query,argv[1],"' where id=3");
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
