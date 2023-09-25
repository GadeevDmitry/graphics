CC ?= g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

#==================================================================================================


all:


build/scene/scene.o: scene/src/scene.cpp | build/scene
	$(CC) -c $(CFLAGS) $< -o $@
all: build/scene/scene.o

build/scene:
	mkdir -p $@
