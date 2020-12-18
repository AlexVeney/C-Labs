# A simple Makefile
# Alex Veney 
# The compiler: gcc for C programs, q++ for C+ programs, etc.

CC = gcc
CFLAGS = -g -O0 -Wall -pedantic-errors
TARGET1 = AsciiToBinary
TARGET2 = BinaryToAscii




all:  $(TARGET1) $(TARGET2)

$(TARGET1): $(TARGET1).c
	$(CC) $(CFLAGS) -o $(TARGET1) $(TARGET1).c 

$(TARGET2): $(TARGET2).c
	$(CC) $(CFLAGS) -o $(TARGET2) $(TARGET2).c

clean:
	rm -f $(TARGET1) $(TARGET2)



