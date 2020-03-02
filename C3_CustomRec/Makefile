# A simple Makefile
# Alexandra Veney G00677630
# CS 262, Lab Section 201
# Lab 3
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc
CFLAGS=-g -Wall
TARGET = lab3_aveney2_201
all = $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c -lm


clean:
	rm $(TARGET)
