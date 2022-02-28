#目前是最通用的Makefile
out:=main
SRCS:=$(wildcard *.c) #拿到当前目录下所有的c文件
OBJS:=$(patsubst %.c,%.o,$(SRCS))
#预定义变量
CC:=gcc
CFLAGS:=-g -I ../include
$(out):$(OBJS)
	gcc $^ -o $@ $(CFLAGS) -lcrypt
	rm -rf $(OBJS)
#.PHONY:clean rebuild
rebuild:clean $(out)
clean:
	rm -rf $(OBJS) $(out)
