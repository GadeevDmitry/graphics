CC := g++

CFLAGS_DEBUG   := -D _DEBUG -ggdb3 -std=c++20 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -pie -Wlarger-than=8192 -Wstack-usage=8192
CFLAGS_RELEASE := -D NDEBUG -std=c++20 -O2

ifdef debug
CFLAGS := $(CFLAGS_DEBUG)
else
CFLAGS := $(CFLAGS_RELEASE)
endif

SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

#--------------------------------------------------------------------------------------------------

ROOT_DIR := ../..

LOCAL_PATHS := buttons molecules scene
LOCAL_PATHS := $(foreach PATH, $(LOCAL_PATHS), -I$(PATH)/include)

GLOBAL_PATHS := geometry graphic
GLOBAL_PATHS := $(foreach PATH, $(GLOBAL_PATHS), -I$(ROOT_DIR)/$(PATH)/include) -I$(ROOT_DIR)/common -I$(ROOT_DIR)

CFLAGS += $(LOCAL_PATHS) $(GLOBAL_PATHS)

#--------------------------------------------------------------------------------------------------

GEOMETRY_PREFIX := $(ROOT_DIR)/geometry
GRAPHIC_PREFIX  := $(ROOT_DIR)/graphic
COMMON_PREFIX   := $(ROOT_DIR)/common

export CC CFLAGS GEOMETRY_PREFIX GRAPHIC_PREFIX COMMON_PREFIX

#==================================================================================================

GEOMETRY_OBJS := vec2d distance
GEOMETRY_OBJS := $(foreach OBJ, $(GEOMETRY_OBJS), build/geometry/$(OBJ).o)

GRAPHIC_OBJS := color draw
GRAPHIC_OBJS := $(foreach OBJ, $(GRAPHIC_OBJS), build/graphic/$(OBJ).o)

COMMON_OBJS := algorithm array logs stack trace
COMMON_OBJS := $(foreach OBJ, $(COMMON_OBJS), build/common/$(OBJ).o)

MOLECULE_OBJS := molecule molecule_manager
MOLECULE_OBJS := $(foreach OBJ, $(MOLECULE_OBJS), build/molecules/$(OBJ).o)

SCENE_OBJS := scene
SCENE_OBJS := $(foreach OBJ, $(SCENE_OBJS), build/scene/$(OBJ).o)

OBJS := $(GEOMETRY_OBJS) $(GRAPHIC_OBJS) $(COMMON_OBJS) $(MOLECULE_OBJS) $(SCENE_OBJS)

#==================================================================================================

.PHONY: all
all: | build
	$(MAKE) -f $(GEOMETRY_PREFIX)/Makefile
	$(MAKE) -f $(GRAPHIC_PREFIX)/Makefile
	$(MAKE) -f $(COMMON_PREFIX)/Makefile
	$(MAKE) -f molecules/Makefile
	$(MAKE) -f scene/Makefile
	$(CC) $(CFLAGS) main.cpp $(OBJS) $(SFML_LIBS) -o build/main

.PHONY: compilation_database
compilation_database:
	bear -- $(MAKE) all -k

build:
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf build
