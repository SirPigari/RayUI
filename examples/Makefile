CC = gcc
CFLAGS = -I.. -std=c99
LDFLAGS = -lraylib -lgdi32 -lwinmm

SRCS = $(wildcard *.c)
EXES = $(SRCS:.c=.exe)

all: $(EXES)

%.exe: %.c
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	del /Q *.exe

.PHONY: all clean
