CC = gcc
CFLAGS = -Wall -std=c99 -pedantic

TARGET = interpretador

SRCS = definitivamente_um_grupo.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean 
