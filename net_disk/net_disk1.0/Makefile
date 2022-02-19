#目前是最通用的Makefile
out:=my_server
SRCS:=$(wildcard *.c) #拿到当前目录下所有的c文件
OBJS:=$(patsubst %.c,%.o,$(SRCS))
#预定义变量
CC:=gcc
CFLAGS:=-g -I /usr/include/mysql
$(out):$(OBJS)
	gcc $^ -o $@ $(CFLAGS) -lmysqlclient -pthread -lcrypt

#.PHONY:clean rebuild
rebuild:clean $(out)
clean:
	rm -rf $(OBJS) $(out)
