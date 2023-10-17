CC := g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

WIDGET_PREFIX   ?=
WIDGET_BILD_DIR ?= build/widget/

#--------------------------------------------------------------------------------------------------------------------------------

INCLUDES := $(DATA_STRUCTS_INCLUDES) $(GEOMETRY_INCLUDES) $(GRAPHIC_INCLUDES) $(WIDGET_INCLUDES) $(TOOLS_INCLUDES) $(SFML_INCLUDES)

#================================================================================================================================


all:


$(WIDGET_BILD_DIR)button.o: $(WIDGET_PREFIX)src/button.cpp | $(WIDGET_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(WIDGET_BUILD_DIR)button.o

$(WIDGET_BILD_DIR)canvas.o: $(WIDGET_PREFIX)src/canvas.cpp | $(WIDGET_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(WIDGET_BUILD_DIR)canvas.o

$(WIDGET_BUILD_DIR)menu.o: $(WIDGET_PREFIX)src/menu.cpp | $(WIDGET_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(WIDGET_BILD_DIR)menu.o

$(WIDGET_BILD_DIR)widget_manager.o: $(WIDGET_PREFIX)src/widget_manager.cpp | $(WIDGET_BUILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(WIDGET_BILD_DIR)widget_manager.o

$(WIDGET_BUILD_DIR)widget.o: $(WIDGET_PREFIX)src/widget.cpp | $(WIDGET_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(WIDGET_BUILD_DIR)widget.o

$(WIDGET_BILD_DIR)window.o: $(WIDGET_PREFIX)src/window.cpp | $(WIDGET_BUILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(WIDGET_BILD_DIR)window.o

$(WIDGET_BILD_DIR):
	mkdir -p $@
