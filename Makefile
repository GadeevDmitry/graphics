CC := g++
CFLAGS_DEBUG   := -D _DEBUG -ggdb3 -std=c++20 -O0 -Wall -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -pie -Wlarger-than=8192 -Wstack-usage=8192
CFLAGS_RELEASE := -Wl,--export-dynamic -fPIE -D NDEBUG -D NVERIFY -std=c++20 -O2

ifeq ($(mode), debug)
CFLAGS := $(CFLAGS_DEBUG)
else
CFLAGS := $(CFLAGS_RELEASE)
endif

BUILD_DIR   := build/
ROOT_PREFIX := ./
export CFLAGS BUILD_DIR ROOT_PREFIX

#================================================================================================================================

OBJS      := $(shell find $(BUILD_DIR) -name "*.o")
INCLUDES  := -I$(ROOT_PREFIX) -I$(ROOT_PREFIX)include/
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all
all:
	$(CC) $(CFLAGS) $(INCLUDES) main/application.cpp main/main.cpp $(OBJS) $(SFML_LIBS) -o $(BUILD_DIR)editor

.PHONY: components
components:
	$(MAKE) -f $(ROOT_PREFIX)makefiles/event/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/filter/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/geometry/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/graphic/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/plugin/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/tool/Makefile
	$(MAKE) -f $(ROOT_PREFIX)makefiles/widget/Makefile
ifeq ($(mode), debug)
	$(MAKE) -f $(ROOT_PREFIX)data_structs/Makefile mode=verify PREFIX=$(ROOT_PREFIX)data_structs/
else
	$(MAKE) -f $(ROOT_PREFIX)data_structs/Makefile mode=release PREFIX=$(ROOT_PREFIX)data_structs/
endif

.PHONY: compilation_database_rule
compilation_database_rule:
	$(MAKE) components
	$(CC) main/application.cpp $(CFLAGS) $(INCLUDES) -c -o $(BUILD_DIR)application.o
	$(CC) main/main.cpp        $(CFLAGS) $(INCLUDES) -c -o $(BUILD_DIR)main.o

.PHONY: compilation_database
compilation_database:
	$(MAKE) clean
	bear -- $(MAKE) compilation_database_rule -k
	rm $(BUILD_DIR)application.o
	rm $(BUILD_DIR)main.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
