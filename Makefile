CC=gcc
CFLAGS=-O3 -Wall -Wextra -pthread -D_GNU_SOURCE -std=c11
LDFLAGS=-lm -lpthread
SRCDIR=src
SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRCS:.c=.o)
TARGET=code-scan
.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(SRCDIR)/*.o
distclean: clean
	rm -f $(TARGET)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
run: $(TARGET)
	./$(TARGET) .
