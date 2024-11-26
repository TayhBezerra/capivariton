CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g

TARGET = interpretador

SRCS = alloc.c definitivamente_um_grupo.c stdarch.c
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
