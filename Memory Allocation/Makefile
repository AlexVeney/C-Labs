# A simple Makefile
# Alex Veney 
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc
CFLAGS=-g -O0 -Wall -pedantic-errors
TARGET = Auto_Memory_AllocationAVeney
all = $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 


clean:
	rm $(TARGET)
