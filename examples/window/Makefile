CC := g++
CFLAGS_DEBUG   := -D _DEBUG -ggdb3 -std=c++20 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -pie -Wlarger-than=8192 -Wstack-usage=8192
CFLAGS_RELEASE := -D NDEBUG -D NVERIFY -std=c++20 -O2

ifeq ($(mode), debug)
CFLAGS := $(CFLAGS_DEBUG)
else
CFLAGS := $(CFLAGS_RELEASE)
endif

export CFLAGS

#--------------------------------------------------------------------------------------------------------------------------------

ROOT_PREFIX := ../../
BUILD_DIR   := build/
include $(ROOT_PREFIX)include_paths.d

INCLUDES := $(DATA_STRUCTS_INCLUDES) $(GRAPHIC_INCLUDES) $(GEOMETRY_INCLUDES) $(WIDGET_INCLUDES) $(SFML_INCLUDES)

#--------------------------------------------------------------------------------------------------------------------------------

WIDGET_OBJS := widget widget_manager
WIDGET_OBJS := $(foreach OBJ, $(WIDGET_OBJS), $(WIDGET_BUILD_DIR)$(OBJ).o)

GRAPHIC_OBJS := color render_texture
GRAPHIC_OBJS := $(foreach OBJ, $(GRAPHIC_OBJS), $(GRAPHIC_BUILD_DIR)$(OBJ).o)

GEOMETRY_OBJS := vec2d
GEOMETRY_OBJS := $(foreach OBJ, $(GEOMETRY_OBJS), $(GEOMETRY_BUILD_DIR)$(OBJ).o)

DATA_STRUCTS_OBJS := algorithm array list log trace stack
DATA_STRUCTS_OBJS := $(foreach OBJ, $(DATA_STRUCTS_OBJS), $(DATA_STRUCTS_BUILD_DIR)$(OBJ).o)

OBJS := $(WIDGET_OBJS) $(GRAPHIC_OBJS) $(GEOMETRY_OBJS) $(DATA_STRUCTS_OBJS)

#--------------------------------------------------------------------------------------------------------------------------------

SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

#================================================================================================================================

all: | $(BUILD_DIR)
	@echo BUILDING WIDGET
	$(MAKE) -f $(WIDGET_PREFIX)Makefile
	@echo BUILDING GRAPHIC
	$(MAKE) -f $(GRAPHIC_PREFIX)Makefile
	@echo BUILDING GEOMETRY
	$(MAKE) -f $(GEOMETRY_PREFIX)Makefile
	@echo BUILDING DATA_STRUCTS
ifeq ($(mode), debug)
	$(MAKE) -f $(DATA_STRUCTS_PREFIX)Makefile mode=verify LIB_PREFIX=$(DATA_STRUCTS_PREFIX) LIB_BUILD_DIR=$(DATA_STRUCTS_BUILD_DIR)
else
	$(MAKE) -f $(DATA_STRUCTS_PREFIX)Makefile mode=release LIB_PREFIX=$(DATA_STRUCTS_PREFIX) LIB_BUILD_DIR=$(DATA_STRUCTS_BUILD_DIR)
endif
	$(CC) $(CFLAGS) $(INCLUDES) main.cpp $(OBJS) $(SFML_LIBS) -o $(BUILD_DIR)window

$(BUILD_DIR):
	mkdir -p $@

.PHONY: compilation_database
compilation_database:
	bear -- $(MAKE) -k

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
