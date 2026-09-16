# Variables
CC=gcc
CFLAGS=-Iinclude

binary_parser: src/main.c src/errors.c
	$(CC) -o binary_parser src/main.c src/errors.c $(CFLAGS)
