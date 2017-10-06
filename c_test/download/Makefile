################################################
# File Name: Makefile
# Description: prodtest.exe project Makefile
# Author: wanghan
# Created Time : 2017-08-19 18:53:07
################################################

# Compiler
CC := gcc

# CFLAG
CFLAG :=
CFLAG += -Wall
CFLAG += -O0
CFLAG += -g

# Source code
src_file := 
src_file += ./src/main.c
src_file += ./src/getopt.c
src_file += ./src/commands.c
src_file += ./src/uart_down.c 

# header file
header_path :=
header_path += -I./down_ram

# obj file
obj_file := $(subst .c,.o,${src_file}) 

# target
pro_target := download

# build
${pro_target} : ${obj_file}
	@echo [Link] ${pro_target}
	@${CC} ${CFLAG} $^ -o $@ ${header_path}

%.o : %.c
	@echo [CC] $@
	@${CC} ${CFLAG} -c $< -o $@ ${header_path}

# clean
.PHONY: clean
clean:
	@echo [CLEAN] ${obj_file}
	@rm ${obj_file}
