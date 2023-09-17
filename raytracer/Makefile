CC ?= g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

RAYTRACER_PREFIX ?=

#==================================================================================================


all:


build/raytracer/material.o: $(RAYTRACER_PREFIX)/src/material.cpp | build/raytracer
	$(CC) -c $(CFLAGS) $< -o $@
all: build/raytracer/material.o

build/raytracer/raytracer.o: $(RAYTRACER_PREFIX)/src/raytracer.cpp | build/raytracer
	$(CC) -c $(CFLAGS) $< -o $@
all: build/raytracer/raytracer.o

build/raytracer/render_sphere.o: $(RAYTRACER_PREFIX)/src/render_sphere.cpp | build/raytracer
	$(CC) -c $(CFLAGS) $< -o $@
all: build/raytracer/render_sphere.o

build/raytracer/scene.o: $(RAYTRACER_PREFIX)/src/scene.cpp | build/raytracer
	$(CC) -c $(CFLAGS) $< -o $@
all: build/raytracer/scene.o

build/raytracer:
	mkdir -p $@
