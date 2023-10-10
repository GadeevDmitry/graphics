CC := g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

GEOMETRY_PREFIX   ?=
GEOMETRY_BILD_DIR ?= build/geometry/

#--------------------------------------------------------------------------------------------------------------------------------

INCLUDES := $(DATA_STRUCTS_INCLUDES) $(GEOMETRY_INCLUDES) $(SFML_INCLUDES)

#================================================================================================================================


all:


$(GEOMETRY_BUILD_DIR)vec2d.o: $(GEOMETRY_PREFIX)src/vec2d.cpp | $(GEOMETRY_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(GEOMETRY_BUILD_DIR)vec2d.o

$(GEOMETRY_BILD_DIR)vec3d.o: $(GEOMETRY_PREFIX)src/vec3d.cpp | $(GEOMETRY_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(GEOMETRY_BILD_DIR)vec3d.o

$(GEOMETRY_BUILD_DIR)intersect.o: $(GEOMETRY_PREFIX)src/intersect.cpp | $(GEOMETRY_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(GEOMETRY_BUILD_DIR)intersect.o

$(GEOMETRY_BILD_DIR)rectangle.o: $(GEOMETRY_PREFIX)src/rectangle.cpp | $(GEOMETRY_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(GEOMETRY_BILD_DIR)rectangle.o

$(GEOMETRY_BILD_DIR):
	mkdir -p $@
