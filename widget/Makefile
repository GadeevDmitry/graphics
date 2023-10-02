CC := g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

WIDGET_PREFIX   ?=
WIDGET_BILD_DIR ?= build/widget/

#--------------------------------------------------------------------------------------------------------------------------------

INCLUDES := $(DATA_STRUCTS_INCLUDES) $(GEOMETRY_INCLUDES) $(GRAPHIC_INCLUDES) $(WIDGET_INCLUDES) $(SFML_INCLUDES)

#================================================================================================================================


all:


$(WIDGET_BUILD_DIR)widget.o: $(WIDGET_PREFIX)src/widget.cpp | $(WIDGET_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(WIDGET_BUILD_DIR)widget.o

$(WIDGET_BILD_DIR)window.o: $(WIDGET_PREFIX)src/window.cpp | $(WIDGET_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(WIDGET_BILD_DIR)window.o

$(WIDGET_BILD_DIR):
	mkdir -p $@
