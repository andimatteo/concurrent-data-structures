FLAGS			:= -Wall -Iinclude -pthread -fopenmp
LIB				:= include/lib.c
LIB_OBJ			:= include/lib.o
CC				:= gcc-15

all: build dot sum

build:
	mkdir -p build

dot:
	$(CC) $(FLAGS) 01/$@.c -o build/$@

sum:
	$(CC) $(FLAGS) 01/$@.c -o build/$@

clean:
	rm -rf build/

