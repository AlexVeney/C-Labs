# A simple Makefile
# Alexandra Veney G00677630
# CS 262, Lab Section 201
# Lab 10
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc
CFLAGS=-g -O0 -Wall -pedantic-errors
TARGET = lab10_aveney2_201
all = $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 


clean:
	rm $(TARGET)
