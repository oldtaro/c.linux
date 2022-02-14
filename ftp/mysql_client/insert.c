#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[])
{
	MYSQL *conn;
   // MYSQL_RES *res;
   // MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="123";
	const char* database="test";
	char query[200]="insert into Person(FirstName,LastName,Age,score) values('luo','laoshi',35,96.9)";
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
