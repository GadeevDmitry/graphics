CC ?= g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

EQUATION_PREFIX ?=

#================================================================================================================================


all:


build/equation_solver/equation_solver.o: $(EQUATION_PREFIX)/src/equation_solver.cpp | build/equation_solver
	$(CC) -c $(CFLAGS) $< -o $@
all: build/equation_solver/equation_solver.o

build/equation_solver:
	mkdir -p $@
