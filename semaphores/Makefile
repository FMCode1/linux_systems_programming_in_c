# Makefile for CS 330 concurrency labs

CC = gcc
CFLAGS = -Wall -pthread -g

# Targets
all: badcnt goodcnt PC

# Compile badcnt
badcnt: badcnt.c
	$(CC) $(CFLAGS) badcnt.c -o badcnt

# Compile goodcnt
goodcnt: goodcnt.c
	$(CC) $(CFLAGS) goodcnt.c -o goodcnt

# Compile Producer-Consumer
PC: PC.c
	$(CC) $(CFLAGS) PC.c -o PC

# Run tests
run_badcnt: badcnt
	./badcnt

run_goodcnt: goodcnt
	./goodcnt

run_PC: PC
	./PC

# Clean executables
clean:
	rm -f badcnt goodcnt PC *.o