CC = gcc
OPTFLAGS = -O2
CFLAGS = -I.. -std=c99 $(OPTFLAGS)
LDFLAGS = -lraylib -lgdi32 -lwinmm

SRCS = $(wildcard *.c)
EXES = $(SRCS:.c=.exe)

all: $(EXES)

%.exe: %.c ../rayui.h
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	del /Q *.exe

.PHONY: all clean
