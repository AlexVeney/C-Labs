# A simple Makefile
# Alexandra Veney G00677630
# CS262, Lab Section 201
# Project 3
# The compiler: gcc for C programs, g++ for C++ programs, etc


CC = gcc
CFLAGS = -g -Wall -O0 -pedantic-errors
TARGET = RadixSort

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET) -lm

clean: 
	rm -f $(TARGET)
