# leads comments in a line 
# Build all: default target

DEBUG =  -ggdb

all : demo fork_demo

# Separate compilation to build object files
main.o : main.cpp HALmod.h 
	g++ -c $(DEBUG) main.cpp

HALmod.o : HALmod.cpp HALmod.h 
	g++ -c $(DEBUG) HALmod.cpp

# linking
#demo is a target which depends upon main.o and greet.o 
#"g++ main.o greet.o -o demo" is the command to produce the executable file
#You need to use a TAB before g++ 
demo : main.o HALmod.o
	g++ main.o HALmod.o -o demo

# Testing
check : all
	./demo

fork_demo : fork_demo.cpp
	g++ fork_demo.cpp $(DEBUG) -o fork_demo

# Clean up all build targets so that one may get a clean build
clean :
	rm -f *.o demo fork_demo
