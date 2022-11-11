


.PHONY:RPO_COPY


CC=gcc
TARGET=COPY            #用于存储目标名
INCLUDE_PATH=../include    #存储头文件路径
INSTALL_PATH=/user/bin/    #安装位置
LIBRARY_PATH=../library    #存放静态库过着共享库位置
CFLAGS=-I$(INCLUDE_PATH) -c -g -Wall#编译选项
CPPFLAGS=
LDFLAGS=-L$(LIBRARY_PATH) -llibraryName
SRCFILE=$(wildcard *.c)
DESFILE=$(patsubst %.c,%.o,$(SRCFILE))
RM=sudo rm -rf
COPY=sudo cp


$(TARGET):$(DESFILE)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $<

clean:
	rm $(DESFILE) -rf
	rm $(TARGET) -rf

install:


distclean:





