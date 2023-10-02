CC := g++
CFLAGS ?= -D NDEBUG -std=c++20 -O2

EQUATION_SOLVER_PREFIX   ?=
EQUATION_SOLVER_BILD_DIR ?= build/equation_solver/

#--------------------------------------------------------------------------------------------------------------------------------

INCLUDES := $(DATA_STRUCTS_INCLUDES) $(EQUATION_SOLVER_INCLUDES)

#================================================================================================================================


all:


$(EQUATION_SOLVER_BUILD_DIR)equation_solver.o: $(EQUATION_SOLVER_PREFIX)src/equation_solver.cpp | $(EQUATION_SOLVER_BILD_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
all: $(EQUATION_SOLVER_BUILD_DIR)equation_solver.o

$(EQUATION_SOLVER_BILD_DIR):
	mkdir -p $@
