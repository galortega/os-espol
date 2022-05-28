all: build build/mycat

build:
	mkdir -p build

build/mycat: main.c 
	 g++ -g -Wall -o build/mycat main.c

clean:
	 rm build/*
