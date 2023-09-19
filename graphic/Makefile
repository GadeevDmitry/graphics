CC ?= g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

GRAPHIC_PREFIX ?=

#==================================================================================================


all:


build/graphic/color.o: $(GRAPHIC_PREFIX)/src/color.cpp | build/graphic
	$(CC) -c $(CFLAGS) $< -o $@
all: build/graphic/color.o

build/graphic/draw.o: $(GRAPHIC_PREFIX)/src/draw.cpp | build/graphic
	$(CC) -c $(CFLAGS) $< -o $@
all: build/graphic/draw.o

build/graphic:
	mkdir -p $@
