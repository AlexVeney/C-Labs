# A simple Makefile
# Alexandra Veney G00677630
# CS 262, Lab Section 201
# Project 1
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc
CFLAGS=-g -Wall -O2
TARGET = encrypt_decrypt_aveney2_201
all = $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c -lm


clean:
	rm $(TARGET)
