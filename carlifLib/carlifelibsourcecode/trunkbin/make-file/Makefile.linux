#Author:
#	Liu CaiQuan
#Date:
#	7th Semptember 2015
#CarLife Protocol version:
#	V0.15
#
#rule for Linux
#
#                   Copyright (C) Under BaiDu, Inc.

#TOPDIR:=~/EddyWorkSpace/CarLifeLibSourceCode/trunk
TOPDIR:=$(shell pwd)
export TOPDIR

CROSS_COMPILE=
LD=$(CROSS_COMPILE)ld
CC=$(CROSS_COMPILE)g++

CP=cp

export LD CC 

CFLAGS:=-g -Wall -W -fPIC
CFLAGS+=-I protobuf/cc/include
CFLAGS+=-I $(TOPDIR)/include
CFLAGS+=-I $(TOPDIR)/protobuf/cc/include
CFLAGS+=-I /usr/local/include
CFLAGS+=-I /usr/local/include/google/protobuf
CFLAGS+=-I /usr/local/include/google/protobuf/io
CFLAGS+=-I /usr/local/include/google/protobuf/stubs
CFLAGS+=-I /usr/include
CFLAGS+=-I /usr/include/libxml2

#LFLAGS:=-fPIC -shared
LFLAGS+=-L/usr/local/lib -lprotobuf

export CFLAGS LFLAGS

OBJDIR=obj

#obj-y+=CarLifeLibTest.o
obj-y+=core/
obj-y+=libwrapper/
obj-y+=modules/
obj-y+=protobuf/
obj-y+=utility/

TARGET-LIB=libcarlifevehicle.so
TARGET-APP=libtest

all: carlifelib libtest

carlifelib: 
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) -shared -o $(TARGET-LIB) built-in.o
	$(CP) $(TARGET-LIB) $(OBJDIR)	

libtest:CarLifeLibTest.cpp
	$(CC) -o $(TARGET-APP) $< -Iinclude -L./ -lcarlifevehicle -lpthread $(LFLAGS)
	$(CP) $(TARGET-APP) $(OBJDIR)

protoBuf:
	rm -f ./protobuf/pbGen/*
	protoc --proto_path=./protobuf/proto/ --cpp_out=./protobuf/pbGen ./protobuf/proto/*.proto
	rm -f ./protobuf/cc/src/*.cc
	rm -f ./protobuf/cc/include/*.h
	mv ./protobuf/pbGen/*.cc ./protobuf/cc/src/
	mv ./protobuf/pbGen/*.h ./protobuf/cc/include/

clean:
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET-LIB)
	rm -f $(TARGET-APP)
	rm -f $(OBJDIR)/*

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET-LIB)
	rm -f $(TARGET-APP)
	rm -f $(OBJDIR)/*
