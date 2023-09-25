CC ?= g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

#==================================================================================================


all:


build/buttons/button.o: buttons/src/button.cpp | build/buttons
	$(CC) -c $(CFLAGS) $< -o $@
all: build/buttons/button.o

build/buttons/button_manager.o: buttons/src/button_manager.cpp | build/buttons
	$(CC) -c $(CFLAGS) $< -o $@
all: build/buttons/button_manager.o

build/buttons:
	mkdir -p $@
