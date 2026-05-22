FLAGS			:= -Wall -Iinclude -pthread -fopenmp
LIB				:= include/lib.c
CC				:= gcc-15

all: build dot sum list ring-buffer blocking-ring-buffer lock-free-list

build:
	mkdir -p build

dot:
	$(CC) $(FLAGS) 01/$@.c -o build/$@

sum:
	$(CC) $(FLAGS) 01/$@.c -o build/$@

list:
	$(CC) $(FLAGS) 02/$@.c -o build/$@

ring-buffer:
	$(CC) $(FLAGS) 03/$@.c -o build/$@

blocking-ring-buffer:
	$(CC) $(FLAGS) 03/$@.c -o build/$@

lock-free-list:
	$(CC) $(FLAGS) 05/$@.c -o build/$@


clean:
	rm -rf build/

