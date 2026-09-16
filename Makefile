# Variables
SRC = src
OBJ = obj
INC = inc
LIB = lib
BIN = bin
BUILD = build
TESTS = tests

CC=gcc
CFLAGS=-I$(INC)

binary_parser: src/main.c src/errors.c
	$(CC) -o binary_parser src/main.c src/errors.c $(CFLAGS)
