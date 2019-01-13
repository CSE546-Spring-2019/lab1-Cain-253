#makefile for count

COMPILER = gcc
FLAGS = -g -Wall
FILENAME = count

all: compile

compile: $(FILENAME).c
	$(COMPILER) $(FLAGS) -o $(FILENAME) $(FILENAME).c

clean:
	#throws error on Windows
	rm $(FILENAME)
