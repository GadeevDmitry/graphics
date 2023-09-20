CC ?= g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

CLASSES_PREFIX := classes

#==================================================================================================


all:


build/classes/molecule.o: $(CLASSES_PREFIX)/src/molecule.cpp | build/classes
	$(CC) -c $(CFLAGS) $< -o $@
all: build/classes/molecule.o

build/classes/gas_scene.o: $(CLASSES_PREFIX)/src/gas_scene.cpp | build/classes
	$(CC) -c $(CFLAGS) $< -o $@
all: build/classes/gas_scene.o

build/classes:
	mkdir -p $@
