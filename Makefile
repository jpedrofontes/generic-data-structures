###################################################
# MAKEFILE
# GENERIC DATA STRUCTURES IN C
###################################################

SHELL = /bin/sh

BIN_NAME = generic_data_structures

CXX = gcc
LD  = gcc

OP?=AVL
CXXFLAGS = -O2 -Wall -Wextra -Wno-unused-parameter -ansi -g #-ftree-vectorize -fopenmp

CXXFLAGS += -D$(OP)

SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build
INCLUDES = includes
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEPS = $(patsubst build/%.o,build/%.d,$(OBJ))
BIN = $(BIN_NAME)

vpath %.c $(SRC_DIR)

################################################################################
# RULES
################################################################################

.DEFAULT_GOAL = all

$(BUILD_DIR)/%.d: %.c
	$(CXX) -M $(CXXFLAGS) -I$(INCLUDES) $< -o $@

$(BUILD_DIR)/%.o: %.c
	$(CXX) -c $(CXXFLAGS) -I$(INCLUDES) $< -o $@

$(BIN_DIR)/$(BIN_NAME): $(DEPS) $(OBJ)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -o $@ $(OBJ)

checkdirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

all: checkdirs $(BIN_DIR)/$(BIN_NAME)

clean:
	rm -f $(BUILD_DIR)/* $(BIN_DIR)/*
