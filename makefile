CC = gcc
CFLAGS = -std=c89 -pedantic -Wall -Wextra
TARGET = main
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

format:
	indent $(SRC)

clean:
	rm -f $(TARGET) *.c~ *.h~

.PHONY: all clean format
