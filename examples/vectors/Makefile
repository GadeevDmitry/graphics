CC := g++

ifeq ($(target), debug)
CFLAGS := -D _DEBUG -ggdb3 -std=c++20 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -pie -Wlarger-than=8192 -Wstack-usage=8192
else
CFLAGS := -std=c++20 -O2
endif

SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS     += -I../../libs/include

OBJS := main.o
OBJS := $(foreach OBJ, $(OBJS), build/$(OBJ))

LIB_OBJS := draw.o vec.o
LIB_OBJS := $(foreach OBJ, $(LIB_OBJS), build/libs/$(OBJ))

#================================================================================================================================

.PHONY: all
all: $(OBJS) build_libs
	g++ $(OBJS) $(LIB_OBJS) $(CFLAGS) $(SFML_FLAGS) -o build/main

build/main.o: main.cpp | build
	$(CC) $< -c $(CFLAGS) -o $@

.PHONY: build_libs
build_libs:
	$(MAKE) -f ../../libs/Makefile

build:
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf build
