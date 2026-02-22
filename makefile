CC=gcc
CFLAGS=-Wall -Wextra -g -std=c99
TARGET=veeprom
SRCS=main.c veeprom.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) eeprom.bin

