CC = gcc

SRCS = $(wildcard src/*.c)

OBJS = $(SRCS:src/%.c=obj/%.o)

TARGET = main

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


