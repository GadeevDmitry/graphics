CC := g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

GRAPHIC_PREFIX   ?=
GRAPHIC_BILD_DIR ?= build/graphic/

#--------------------------------------------------------------------------------------------------------------------------------

INCLUDES := $(DATA_STRUCTS_INCLUDES) $(GEOMETRY_INCLUDES) $(GRAPHIC_INCLUDES) $(SFML_INCLUDES) $(WIDGET_INCLUDES)

#================================================================================================================================


all:


$(GRAPHIC_BUILD_DIR)color.o: $(GRAPHIC_PREFIX)src/color.cpp | $(GRAPHIC_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(GRAPHIC_BUILD_DIR)color.o

$(GRAPHIC_BILD_DIR)render_texture.o: $(GRAPHIC_PREFIX)src/render_texture.cpp | $(GRAPHIC_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(GRAPHIC_BILD_DIR)render_texture.o

$(GRAPHIC_BILD_DIR):
	mkdir -p $@
