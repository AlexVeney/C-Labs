# A simple Makefile
# Alex Veney
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc
CFLAGS=-g -Wall -O2
TARGET = Encrypt_DecryptAVeney
all = $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c -lm


clean:
	rm $(TARGET)
