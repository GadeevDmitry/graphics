CC ?= g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

GEOMETRY_PREFIX ?=

#==================================================================================================


all:


build/geometry/vec2d.o: $(GEOMETRY_PREFIX)/src/vec2d.cpp | build/geometry
	$(CC) -c $(CFLAGS) $< -o $@
all: build/geometry/vec2d.o

build/geometry/vec3d.o: $(GEOMETRY_PREFIX)/src/vec3d.cpp | build/geometry
	$(CC) -c $(CFLAGS) $< -o $@
all: build/geometry/vec3d.o

build/geometry:
	mkdir -p $@
