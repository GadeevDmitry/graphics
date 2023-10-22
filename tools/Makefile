CC := g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

TOOLS_PREFIX   ?=
TOOLS_BILD_DIR ?= build/tools/

#--------------------------------------------------------------------------------------------------------------------------------

INCLUDES := $(DATA_STRUCTS_INCLUDES) $(TOOLS_INCLUDES) $(GEOMETRY_INCLUDES) $(GRAPHIC_INCLUDES) $(SFML_INCLUDES) $(WIDGET_INCLUDES)

#================================================================================================================================


all:

$(TOOLS_BILD_DIR)ellipse_tool.o: $(TOOLS_PREFIX)src/ellipse_tool.cpp | $(TOOLS_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(TOOLS_BUILD_DIR)ellipse_tool.o

$(TOOLS_BILD_DIR)line_tool.o: $(TOOLS_PREFIX)src/line_tool.cpp | $(TOOLS_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(TOOLS_BUILD_DIR)line_tool.o

$(TOOLS_BILD_DIR)rectangle_tool.o: $(TOOLS_PREFIX)src/rectangle_tool.cpp | $(TOOLS_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(TOOLS_BILD_DIR)rectangle_tool.o

$(TOOLS_BILD_DIR)shape_tool.o: $(TOOLS_PREFIX)src/shape_tool.cpp | $(TOOLS_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(TOOLS_BUILD_DIR)shape_tool.o

$(TOOLS_BILD_DIR):
	mkdir -p $@
