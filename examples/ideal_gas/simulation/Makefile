CC ?= g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

#==================================================================================================


all:


build/simulation/molecule.o: simulation/src/molecule.cpp | build/simulation
	$(CC) -c $(CFLAGS) $< -o $@
all: build/simulation/molecule.o

build/simulation/scene.o: simulation/src/scene.cpp | build/simulation
	$(CC) -c $(CFLAGS) $< -o $@
all: build/simulation/scene.o

build/simulation:
	mkdir -p $@
