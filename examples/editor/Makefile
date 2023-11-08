CC := g++
CFLAGS_DEBUG   := -D _DEBUG -ggdb3 -std=c++20 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -pie -Wlarger-than=8192 -Wstack-usage=8192
CFLAGS_RELEASE := -D NDEBUG -D NVERIFY -D NLOG -std=c++20 -O2

ifeq ($(mode), debug)
CFLAGS := $(CFLAGS_DEBUG)
else
CFLAGS := $(CFLAGS_RELEASE)
endif

BUILD_DIR   := build/
ROOT_PREFIX := ../../
export CFLAGS BUILD_DIR ROOT_PREFIX

#================================================================================================================================

OBJS      := $(shell find $(BUILD_DIR) -name "*.o")
INCLUDES  := -I$(ROOT_PREFIX) -I$(ROOT_PREFIX)include/
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all
all:
	$(CC) $(CFLAGS) $(INCLUDES) src/application.cpp src/main.cpp $(OBJS) $(SFML_LIBS) -o $(BUILD_DIR)editor

.PHONY: components
components:
	$(MAKE) -f $(ROOT_PREFIX)makefiles/event/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/geometry/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/graphic/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/tool/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/widget/Makefile
ifeq ($(mode), debug)
	$(MAKE) -f $(ROOT_PREFIX)data_structs/Makefile mode=verify PREFIX=$(ROOT_PREFIX)data_structs/
else
	$(MAKE) -f $(ROOT_PREFIX)data_structs/Makefile mode=release PREFIX=$(ROOT_PREFIX)data_structs/
endif

.PHONY: objects
objects:
	$(MAKE) components
	$(CC) src/application.cpp $(CFLAGS) $(INCLUDES) -c -o $(BUILD_DIR)application.o
	$(CC) src/main.cpp        $(CFLAGS) $(INCLUDES) -c -o $(BUILD_DIR)main.o

.PHONY: compilation_database
compilation_database:
	$(MAKE) clean
	bear -- $(MAKE) objects -k
	rm $(BUILD_DIR)application.o
	rm $(BUILD_DIR)main.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
