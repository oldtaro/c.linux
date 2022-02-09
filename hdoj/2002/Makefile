#目前是最通用的Makefile,c++
PP:=g++
SRCS:=$(wildcard *.cpp) #拿到当前目录下所有的c文件
TARGETS:=$(SRCS:%.cpp=%)
all:$(TARGETS)
%:%.cpp
	$(PP) -g $< -o $@ 

clean:
	rm -rf $(TARGETS)
