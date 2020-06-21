BIN = ./bin/avl_test.out
CC=g++
CCFLAGS = -I ./include -c -Wall -Wextra -m64 -O0 -g -pedantic 
LDFLAGS = -m64

SRCS=$(wildcard ./src/*.cpp)
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(BIN)

$(BIN):$(OBJS)
						$(CC) $(OBJS) -o $@ $(LDFLAGS)
						
%.o:%.cpp
						$(CC) $(CCFLAGS) -o $@ -c $<

.PHONY: valgrind 
valgrind:				# check for memory leak
						$(info -- Checking For Memory Leaks --)
						make
						valgrind --leak-check=full --show-leak-kinds=all ./bin/avl_test.out

.PHONY: debug
debug:					# GNU debugger
						$(info -- Debugging --)
						gdb ./bin/avl_test.out

.PHONY: clean
clean:					# clean the directory
						$(info -- Cleaning The Directory --)
						rm -rf ./src/*.o ./bin/avl_test.out
.PHONY: run
run:					# run the program as follows
						$(info -- Running Program --)
						make
						./bin/avl_test.out
