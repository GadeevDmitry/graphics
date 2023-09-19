CC := g++

CFLAGS_DEBUG   := -D _DEBUG -ggdb3 -std=c++20 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -pie -Wlarger-than=8192 -Wstack-usage=8192
CFLAGS_RELEASE := -D NDEBUG -std=c++20 -O2

ROOT_DIR      := ../..
INCLUDE_PATHS := geometry graphic
INCLUDE_PATHS := $(foreach PATH, $(INCLUDE_PATHS), -I$(ROOT_DIR)/$(PATH)/include) -I$(ROOT_DIR)/common

SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system

ifdef debug
CFLAGS := $(CFLAGS_DEBUG)
else
CFLAGS := $(CFLAGS_RELEASE)
endif
CFLAGS += $(INCLUDE_PATHS)

#--------------------------------------------------------------------------------------------------

GEOMETRY_PREFIX := ../../geometry
GRAPHIC_PREFIX  := ../../graphic
COMMON_PREFIX   := ../../common

export CC CFLAGS GEOMETRY_PREFIX GRAPHIC_PREFIX COMMON_PREFIX

#==================================================================================================

GEOMETRY_OBJS := vec2d
GEOMETRY_OBJS := $(foreach OBJ, $(GEOMETRY_OBJS), build/geometry/$(OBJ).o)

GRAPHIC_OBJS := color draw
GRAPHIC_OBJS := $(foreach OBJ, $(GRAPHIC_OBJS), build/graphic/$(OBJ).o)

COMMON_OBJS := algorithm logs trace stack
COMMON_OBJS := $(foreach OBJ, $(COMMON_OBJS), build/common/$(OBJ).o)

OBJS := $(GEOMETRY_OBJS) $(GRAPHIC_OBJS) $(COMMON_OBJS)

#==================================================================================================

.PHONY: all
all: | build
	$(MAKE) -f $(GEOMETRY_PREFIX)/Makefile
	$(MAKE) -f $(GRAPHIC_PREFIX)/Makefile
	$(MAKE) -f $(COMMON_PREFIX)/Makefile
	$(CC) $(CFLAGS) main.cpp $(SFML_FLAGS) $(OBJS) -o build/main

.PHONY: compilation_database
compilation_database:
	bear -- $(MAKE) all -k

build:
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf build
