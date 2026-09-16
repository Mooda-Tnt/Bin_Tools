# Variables
CC=gcc
CFLAGS=-Iinclude

main.out: src/main.c
	$(CC) -o main.out src/main.c $(CFLAGS)
