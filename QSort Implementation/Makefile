# A simple Makefile
# Alex Veney
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc
CFLAGS=-g -Wall -pedantic-errors
TARGET = Sort_ImplementationAVeney
all = $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 


clean:
	rm $(TARGET)
