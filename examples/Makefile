CC = gcc
OPTFLAGS = -O2
CFLAGS = -I.. -std=c99 $(OPTFLAGS)

SRCS = $(wildcard *.c)
EXES = $(SRCS:.c=.exe)

UNAME_S := $(shell uname -s)

ifeq ($(OS),Windows_NT)
    LDFLAGS = -lraylib -lgdi32 -lwinmm
    EXE_EXT = .exe
    RM = del /Q
else ifeq ($(UNAME_S),Linux)
    LDFLAGS = -lraylib -lm -lpthread -ldl -lGL -lX11
    EXE_EXT =
    RM = rm -f
else
    $(error Unsupported OS)
endif

EXES := $(SRCS:.c=$(EXE_EXT))

all: $(EXES)

%$(EXE_EXT): %.c ../rayui.h
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) *$(EXE_EXT)

.PHONY: all clean
