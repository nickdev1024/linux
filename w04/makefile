OBJS = main.o buffer_related.o lseek_related.o read_write_related.o
CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall
TARGET = main
FILE = alpha dest

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o  $@

.PHONY: clean
clean:
	-rm $(OBJS) $(TARGET) $(FILE) -f

