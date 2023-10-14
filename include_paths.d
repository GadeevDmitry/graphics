BUILD_DIR   ?= build/
ROOT_PREFIX ?=

#--------------------------------------------------------------------------------------------------------------------------------

TOOLS_PREFIX           := $(ROOT_PREFIX)tools/
WIDGET_PREFIX          := $(ROOT_PREFIX)widget/
GRAPHIC_PREFIX         := $(ROOT_PREFIX)graphic/
GEOMETRY_PREFIX        := $(ROOT_PREFIX)geometry/
DATA_STRUCTS_PREFIX    := $(ROOT_PREFIX)data_structs/
EQUATION_SOLVER_PREFIX := $(ROOT_PREFIX)equation_solver/

export TOOLS_PREFIX WIDGET_PREFIX GRAPHIC_PREFIX GEOMETRY_PREFIX EQUATION_SOLVER_PREFIX

#--------------------------------------------------------------------------------------------------------------------------------

SFML_INCLUDES            := -I$(ROOT_PREFIX)
TOOLS_INCLUDES           := -I$(TOOLS_PREFIX)
WIDGET_INCLUDES          := -I$(WIDGET_PREFIX)include/
GRAPHIC_INCLUDES         := -I$(GRAPHIC_PREFIX)include/
GEOMETRY_INCLUDES        := -I$(GEOMETRY_PREFIX)include/
DATA_STRUCTS_INCLUDES    := -I$(DATA_STRUCTS_PREFIX)include/
EQUATION_SOLVER_INCLUDES := -I$(EQUATION_SOLVER_PREFIX)include/

export SFML_INCLUDES TOOLS_INCLUDES WIDGET_INCLUDES GRAPHIC_INCLUDES GEOMETRY_INCLUDES DATA_STRUCTS_INCLUDES EQUATION_SOLVER_INCLUDES

#--------------------------------------------------------------------------------------------------------------------------------

TOOLS_BUILD_DIR           := $(BUILD_DIR)tools/
WIDGET_BUILD_DIR          := $(BUILD_DIR)widget/
GRAPHIC_BUILD_DIR         := $(BUILD_DIR)graphic/
GEOMETRY_BUILD_DIR        := $(BUILD_DIR)geometry/
DATA_STRUCTS_BUILD_DIR    := $(BUILD_DIR)data_structs/
EQUATION_SOLVER_BUILD_DIR := $(BUILD_DIR)equation_solver/

export TOOLS_BUILD_DIR WIDGET_BUILD_DIR GRAPHIC_BUILD_DIR GEOMETRY_BUILD_DIR EQUATION_SOLVER_BUILD_DIR
