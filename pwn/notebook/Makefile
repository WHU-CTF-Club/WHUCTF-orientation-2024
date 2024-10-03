CC = gcc
CFLAGS = -std=c89 -fno-stack-protector
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
TARGET = pwn

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
