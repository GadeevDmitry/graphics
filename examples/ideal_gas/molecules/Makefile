CC ?= g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

#==================================================================================================


all:


build/molecules/molecule.o: molecules/src/molecule.cpp | build/molecules
	$(CC) -c $(CFLAGS) $< -o $@
all: build/molecules/molecule.o

build/molecules/molecule_manager.o: molecules/src/molecule_manager.cpp | build/molecules
	$(CC) -c $(CFLAGS) $< -o $@
all: build/molecules/molecule_manager.o

build/molecules:
	mkdir -p $@
