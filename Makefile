# Variables
CC=gcc
CFLAGS=-Iinclude

main.out: main.c
  $(CC) -o main.out main.c $(CFLAGS)
