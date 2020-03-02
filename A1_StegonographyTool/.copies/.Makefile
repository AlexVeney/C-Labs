# A simple Makefile
# Alexandra Veney G00677630
# CS 262, Lab Section 201
# Project 2
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc
CFLAGS=-g -Wall -O2


Stego: Stego.o image.o
	$(CC) $(CFLAGS) -o Stego Stego.o image.o -lm

StegoExtract: StegoExtract.o image.o
	$(CC) $(CFLAGS) -o StegoExtract StegoExtract.o image.o -lm

image.o: image.c
	$(CC) -c image.c

Stego.o: Stego.c
	$(CC) -c Stego.c

StegoExtract.o: StegoExtract.c
	$(CC) -c StegoExtract.c

clean:
	rm Stego StegoExtract Stego.o StegoExtract.o image.o


