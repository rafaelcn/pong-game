CXX = clang++

# Name of the executable
EXEC = pong-game.out

# Build directories
BUILD		= build
OBJ_DIR		= obj
SRCDIR		= src
SUBDIRS		:= $(shell find ${SRCDIR} -type d)

CXXFLAGS   := -Wall -Wextra -O3 -std=c++14 $(addprefix -I, ${SUBDIRS})
CXXFLAGS_D := -Wall -Wextra -O1 -fsanitize=address -g -std=c++14 $(addprefix -I, ${SUBDIRS})

LIBS := -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

SOURCES = $(shell find ${SRCDIR} -name "*.cpp")

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
OBJECTS := $(notdir $(OBJECTS))
OBJECTS := $(addprefix $(BUILD)/$(OBJ_DIR)/, $(OBJECTS))

all: release

release:
	$(CXX) $(CXXFLAGS) -c $(SOURCES)
	@mv -f *.o  $(BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(LIBS)
	@mv -f $(EXEC) $(BUILD)

debug:
	$(CXX) $(CXXFLAGS_D) -c $(SOURCES)
	@mv -f *.o  $(BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS_D) -o $(EXEC) $(OBJECTS) $(LIBS)
	@mv -f $(EXEC) $(BUILD)

vars:
	@echo "sources: ${SOURCES}"
	@echo "objects: ${OBJECTS}"
	@echo "flags:   ${CXXFLAGS}"

clean:
	rm -f $(wildcard $(RELEASE_BUILD)/$(OBJ_DIR)/*.o)
	rm -f $(wildcard $(DEBUG_BUILD)/$(OBJ_DIR)/*.o)
