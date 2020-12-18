# A simple Makefile
# Alex Veney
# The compiler: gcc for C programs, g++ for C++ programs, etc


CC = gcc
CFLAGS = -g -Wall -O0 -pedantic-errors
TARGET = RadixSort

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET) -lm

clean: 
	rm -f $(TARGET)
