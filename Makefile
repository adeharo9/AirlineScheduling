# OUTPUT FILE
EXE_FILE = AirlineScheduling$(EXE_EXT)

# DIRECTORIES
HDR_DIR = ./src
SRC_DIR = ./src

BIN_DIR = ./bin

# EXECUTABLES
CPL = g++-4.8
LNK = g++-4.8
RM = rm

# EXTENSIONS
HDR_EXT = .h
SRC_EXT = .cpp

BIN_EXT = .o
EXE_EXT = .exe

# COMPILATION OPTIONS
CPL_OPTIONS = -c -o

LNK_OPTIONS = -o $@
LNK_FLAGS = -D_JUDGE_ -DNDEBUG -D_GLIBCXX_DEBUG -O3 -Wall -Wextra -Werror -Wno-sign-compare -Wshadow -std=c++11

RM_OPTIONS = -rf

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
    [FILEPATH]/algorithms/EdmondsKarp.[EXT] \
    [FILEPATH]/algorithms/FordFulkerson.[EXT] \
    [FILEPATH]/algorithms/FordFulkersonDFS.[EXT] \
    [FILEPATH]/benchmark/Benchmark.[EXT] \
    [FILEPATH]/benchmark/Simulation.[EXT] \
	[FILEPATH]/structures/Edge.[EXT] \
	[FILEPATH]/structures/Graph.[EXT] \
	[FILEPATH]/structures/Vertex.[EXT] \
	[FILEPATH]/utils/Chrono.[EXT] \
	[FILEPATH]/utils/Debug.[EXT]

SOURCES = \
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
all: default

$(DIRECTORIES):
	mkdir -p $(DIRECTORIES)

$(BIN_FILES): $(HDR_FILES) $(SRC_FILES) | $(DIRECTORIES)
	$(foreach CPL_FILE, $(CPL_FILES), $(CPL) $(CPL_OPTIONS) $(BIN_DIR)$(CPL_FILE)$(BIN_EXT) $(SRC_DIR)$(CPL_FILE)$(SRC_EXT) $(LNK_FLAGS);)

$(EXE_FILE): $(BIN_FILES)
	$(LNK) $(LNK_OPTIONS) $^ $(LNK_FLAGS)

clean:
	$(RM) $(RM_OPTIONS) $(BIN_DIR)
	$(RM) $(RM_OPTIONS) $(EXE_FILE)

default: $(EXE_FILE)
