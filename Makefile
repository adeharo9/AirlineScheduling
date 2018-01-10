# OUTPUT FILE
EXE_FILE = AirlineScheduling$(EXE_EXT)

OUT1_FILE = Output1.txt
OUT2_FILE = Output2.txt

RES1_FILE = Resultado1.txt
RES2_FILE = Resultado2.txt

MAKE_FILE = Makefile

ZIP_FILE = G15$(ZIP_EXT)

# DIRECTORIES
DOC_DIR = ./docs
DATA_DIR = ./data

HDR_DIR = ./src
SRC_DIR = ./src

RES_DIR = ./results

BIN_DIR = ./bin

BMK_DIR = ./results/benchmark
OUT_DIR = ./results/output
SIM_DIR = ./results/simulations

# EXECUTABLES
CPL = g++
LNK = g++
RM = rm
ZIP = zip

# EXTENSIONS
HDR_EXT = .h
SRC_EXT = .cpp

BIN_EXT = .o
EXE_EXT = .exe

ZIP_EXT = .zip

# COMPILATION OPTIONS
CPL_OPTIONS = -c -o

LNK_OPTIONS = -o $@
CPL_FLAGS = -D_JUDGE_ -DNDEBUG -D_GLIBCXX_DEBUG -O3 -Wall -Wextra -Werror -Wno-sign-compare -Wshadow -std=c++11

RM_OPTIONS = -rf

ZOPTIONS = -r

# FILES
HDR_FILES_AUX = $(HEADERS:[FILEPATH]%=$(HDR_DIR)%)
HDR_FILES = $(HDR_FILES_AUX:.[EXT]=$(HDR_EXT))

SRC_FILES_AUX = $(SOURCES:[FILEPATH]%=$(SRC_DIR)%)
SRC_FILES = $(SRC_FILES_AUX:.[EXT]=$(SRC_EXT))

BIN_FILES_AUX = $(SOURCES:[FILEPATH]%=$(BIN_DIR)%)
BIN_FILES = $(BIN_FILES_AUX:.[EXT]=$(BIN_EXT))

CPL_FILES_AUX = $(SOURCES:[FILEPATH]%=%)
CPL_FILES = $(CPL_FILES_AUX:.[EXT]=)

# FILE STRUCTURE
HEADERS = \
    [FILEPATH]/algorithms/Algorithm.[EXT] \
    [FILEPATH]/algorithms/DinicBlockingFlow.[EXT] \
    [FILEPATH]/algorithms/EdmondsKarp.[EXT] \
    [FILEPATH]/algorithms/FordFulkerson.[EXT] \
    [FILEPATH]/algorithms/FordFulkersonDFS.[EXT] \
    [FILEPATH]/benchmark/Benchmark.[EXT] \
    [FILEPATH]/benchmark/Mode.[EXT] \
    [FILEPATH]/benchmark/Simulation.[EXT] \
	[FILEPATH]/structures/Edge.[EXT] \
	[FILEPATH]/structures/Graph.[EXT] \
	[FILEPATH]/structures/Vertex.[EXT] \
	[FILEPATH]/utils/Chrono.[EXT] \
	[FILEPATH]/utils/Debug.[EXT]

SOURCES = \
    [FILEPATH]/algorithms/DinicBlockingFlow.[EXT] \
    [FILEPATH]/algorithms/EdmondsKarp.[EXT] \
    [FILEPATH]/algorithms/FordFulkerson.[EXT] \
    [FILEPATH]/algorithms/FordFulkersonDFS.[EXT] \
    [FILEPATH]/benchmark/Benchmark.[EXT] \
    [FILEPATH]/benchmark/Simulation.[EXT] \
	[FILEPATH]/structures/Edge.[EXT] \
	[FILEPATH]/structures/Graph.[EXT] \
	[FILEPATH]/structures/Vertex.[EXT] \
	[FILEPATH]/utils/Debug.[EXT] \
	[FILEPATH]/AirlineScheduling.[EXT]

# DIRECTORY STRUCTURE
DIRECTORIES = \
    bin/algorithms \
    bin/benchmark \
	bin/structures \
	bin/utils

# COMMANDS

.PHONY: default
default: $(EXE_FILE)

$(DIRECTORIES):
	mkdir -p $(DIRECTORIES)

$(BIN_FILES): $(HDR_FILES) $(SRC_FILES) | $(DIRECTORIES)
	$(foreach CPL_FILE, $(CPL_FILES), $(CPL) $(CPL_OPTIONS) $(BIN_DIR)$(CPL_FILE)$(BIN_EXT) $(SRC_DIR)$(CPL_FILE)$(SRC_EXT) $(CPL_FLAGS);)

$(EXE_FILE): $(BIN_FILES)
	$(LNK) $(LNK_OPTIONS) $^ $(CPL_FLAGS)

.PHONY: all
all: default

.PHONY: clean
clean:
	$(RM) $(RM_OPTIONS) $(BIN_DIR)
	$(RM) $(RM_OPTIONS) $(EXE_FILE)
	$(RM) $(RM_OPTIONS) $(OUT1_FILE)
	$(RM) $(RM_OPTIONS) $(OUT2_FILE)
	$(RM) $(RM_OPTIONS) $(ZIP_FILE)

.PHONY: purge
purge: clean
	$(RM) $(RM_OPTIONS) $(BMK_DIR)/*
	$(RM) $(RM_OPTIONS) $(OUT_DIR)/*
	$(RM) $(RM_OPTIONS) $(SIM_DIR)/*

.PHONY: $(ZIP)
$(ZIP):
	$(ZIP) $(ZOPTIONS) $(ZIP_FILE) $(DATA_DIR) $(DOC_DIR) $(RES_DIR) $(SRC_DIR) $(RES1_FILE) $(RES2_FILE) $(MAKE_FILE)
