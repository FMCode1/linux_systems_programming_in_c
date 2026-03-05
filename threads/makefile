# leads comments in a line 
# Build all: default target
all : demo

# Separate compilation to build object files
main.o : main.c functions.h 
	gcc -c -ggdb main.c

functions.o : functions.c functions.h 
	gcc -c -ggdb functions.c

# linking
#demo is a target which depends upon main.o and functions.o 
#"gcc main.o functions.o -o demo" is the command to produce the executable file
#You need to use a TAB before gcc 
demo : main.o functions.o
	gcc main.o functions.o -o demo -pthread

# Testing
check : all
	./demo

# Clean up all build targets so that one may get a clean build
clean :
	rm -f *.o demo
