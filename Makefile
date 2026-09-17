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

bin/binary_parser.out: src/main.c src/errors.c src/binary.c
	$(CC) -o bin/binary_parser.out src/main.c src/errors.c src/binary.c $(CFLAGS)
