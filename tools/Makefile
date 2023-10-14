CC := g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

TOOLS_PREFIX   ?=
TOOLS_BILD_DIR ?= build/tools/

#--------------------------------------------------------------------------------------------------------------------------------

INCLUDES := $(DATA_STRUCTS_INCLUDES) $(TOOLS_INCLUDES) $(GEOMETRY_INCLUDES) $(GRAPHIC_INCLUDES) $(SFML_INCLUDES) $(WIDGET_INCLUDES)

#================================================================================================================================


all:


$(TOOLS_BUILD_DIR)tool.o: $(TOOLS_PREFIX)src/tool.cpp | $(TOOLS_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(TOOLS_BUILD_DIR)tool.o

$(TOOLS_BILD_DIR):
	mkdir -p $@
