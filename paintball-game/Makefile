SOURCES=main.c packet.c recv.c utils.c
HEADERS=packet.h log.h recv.h global.h utils.h
FLAGS=-g

all: main 

build: $(SOURCES) $(HEADERS) Makefile
	mpicc $(SOURCES) -o main

clean:
	rm main 

run: build 
	mpirun -oversubscribe -np 8 ./main

build_debug: $(SOURCES) $(HEADERS) Makefile
	mpicc $(FLAGS) $(SOURCES) -o main -DDEBUG -Wall -Wextra -Werror -g

run_debug: build_debug
	mpirun -oversubscribe -np 4 ./main
