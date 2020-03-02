# A simple Makefile
# Alexandra Veney
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc
CFLAGS=-g -O0 -Wall -pedantic-errors
TARGET = lab11_aveney2_201
all = $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 


clean:
	rm  $(TARGET)
