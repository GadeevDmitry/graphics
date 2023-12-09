CC := g++

#--------------------------------------------------------------------------------------------------------------------------------

CFLAGS_DEBUG    := -D _DEBUG -std=c++20 -ggdb3 -Wall -O0 -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -pie -Wstack-usage=8192
CFLAGS_RELEASE  := -D NDEBUG -D NVERIFY -std=c++20 -O2
CFLAGS_SANITIZE := -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

CFLAGS_PLUGIN      := -fPIC
CFLAGS_APPLICATION := -fPIE

ifeq ($(debug), 1)
CFLAGS := $(CFLAGS_DEBUG)
else
CFLAGS := $(CFLAGS_RELEASE)
endif

ifeq ($(sanitize), 1)
CFLAGS += $(CFLAGS_SANITIZE)
endif

ifeq ($(plugin), 1)
CFLAGS += $(CFLAGS_PLUGIN)
else
CFLAGS += $(CFLAGS_APPLICATION)
endif

export CFLAGS

#--------------------------------------------------------------------------------------------------------------------------------

ROOT_PREFIX := ./
export ROOT_PREFIX

#--------------------------------------------------------------------------------------------------------------------------------

ROOT_BUILD_DIR       := build/
MAIN_BUILD_DIR       := $(ROOT_BUILD_DIR)main/
PLUGINS_BUILD_DIR    := $(ROOT_BUILD_DIR)plugins/
COMPONENTS_BUILD_DIR := $(ROOT_BUILD_DIR)components/

#--------------------------------------------------------------------------------------------------------------------------------

SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

#================================================================================================================================

.PHONY: all
all:;

#--------------------------------------------------------------------------------------------------------------------------------

.PHONY: components
components:
	$(MAKE) BUILD_DIR:='$(COMPONENTS_BUILD_DIR)' -f makefiles/components/event/Makefile
	$(MAKE) BUILD_DIR:='$(COMPONENTS_BUILD_DIR)' -f makefiles/components/filter/Makefile
	$(MAKE) BUILD_DIR:='$(COMPONENTS_BUILD_DIR)' -f makefiles/components/geometry/Makefile
	$(MAKE) BUILD_DIR:='$(COMPONENTS_BUILD_DIR)' -f makefiles/components/graphic/Makefile
	$(MAKE) BUILD_DIR:='$(COMPONENTS_BUILD_DIR)' -f makefiles/components/plugin/Makefile
	$(MAKE) BUILD_DIR:='$(COMPONENTS_BUILD_DIR)' -f makefiles/components/tool/Makefile
	$(MAKE) BUILD_DIR:='$(COMPONENTS_BUILD_DIR)' -f makefiles/components/widget/Makefile
ifeq ($(debug), 1)
	$(MAKE) BUILD_DIR:='$(COMPONENTS_BUILD_DIR)' PREFIX:='$(ROOT_PREFIX)data_structs/' -f $(ROOT_PREFIX)data_structs/Makefile mode=verify
else
	$(MAKE) BUILD_DIR:='$(COMPONENTS_BUILD_DIR)' PREFIX:='$(ROOT_PREFIX)data_structs/' -f $(ROOT_PREFIX)data_structs/Makefile mode=release
endif

#--------------------------------------------------------------------------------------------------------------------------------

.PHONY: plugins_compile
plugins_compile:
	$(MAKE) BUILD_DIR:='$(PLUGINS_BUILD_DIR)' -f makefiles/plugins/filter_russian/Makefile

.PHONY: plugins_shared
plugins_shared:;

FILTER_RUSSIAN_OBJS := $(shell find $(PLUGINS_BUILD_DIR)plugin_examples/src/filter_russian/ -name "*.o" 2>/dev/null)
FILTER_RUSSIAN_OBJS += $(shell find $(COMPONENTS_BUILD_DIR)                                 -name "*.o" 2>/dev/null)

.PHONY: filter_russian_shared
filter_russian_shared:
	gcc -shared $(FILTER_RUSSIAN_OBJS) -o plugin_examples/so/filter_russian.so
plugins_shared: filter_russian_shared

.PHONY: plugins
plugins:
	$(MAKE) plugin=1 components
	$(MAKE) plugin=1 plugins_compile
	$(MAKE) plugin=1 plugins_shared
all: plugins

#--------------------------------------------------------------------------------------------------------------------------------

.PHONY: main
main:
	$(MAKE) BUILD_DIR:='$(MAIN_BUILD_DIR)' -f makefiles/main/Makefile

APPLICATION_OBJS := $(shell find $(MAIN_BUILD_DIR)       -name "*.o" 2>/dev/null)
APPLICATION_OBJS += $(shell find $(COMPONENTS_BUILD_DIR) -name "*.o" 2>/dev/null)

.PHONY: application_linkage
application_linkage:
	$(CC) $(CFLAGS) $(APPLICATION_OBJS) $(SFML_LIBS) -o $(ROOT_BUILD_DIR)editor

.PHONY: application
application:
	$(MAKE) plugin=0 components
	$(MAKE) plugin=0 main
	$(MAKE) plugin=0 application_linkage
all: application

#--------------------------------------------------------------------------------------------------------------------------------

.PHONY: clean
clean:
	rm -rf $(ROOT_BUILD_DIR)

.PHONY: clean_components
clean_components:
	rm -rf $(COMPONENTS_BUILD_DIR)

.PHONY: clean_plugins
clean_plugins:
	rm -rf $(PLUGINS_BUILD_DIR)

.PHONY: clean_main
clean_main:
	rm -rf $(MAIN_BUILD_DIR)

#--------------------------------------------------------------------------------------------------------------------------------

.PHONY: compilation_database_rule
compilation_database_rule:
	$(MAKE) components
	$(MAKE) plugins
	$(MAKE) main

.PHONY: compilation_database
compilation_database:
	$(MAKE) clean
	bear -- $(MAKE) compilation_database_rule -k
