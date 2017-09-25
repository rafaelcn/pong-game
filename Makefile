#
# PongGame makefile.
# author: Rafael Campos Nunes.
#

# Compiler used
CXX = g++
# Libs that are used to compile the game
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
# Flag used by the compiler
CXXFLAGS = -Wall -Wextra -O3 -std=c++11
# Flag used to generate a lower optimized version
CXXFLAGS_D = -Wall -Wextra -O1 -std=c++11
# Name of the executable
EXEC = PongGame
# Build directories
RELEASE_BUILD = out/linux/release-build
DEBUG_BUILD = out/linux/debug-build
OBJ_DIR = obj
SOURCEDIR = src

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
OBJECTS := $(notdir $(OBJECTS))
OBJECTS := $(addprefix $(RELEASE_BUILD)/$(OBJ_DIR)/, $(OBJECTS))

OBJECTS_D = $(OBJECTS)
# Without the line below, OBJECTS_D looks like out/debug-build/obj/out/rele...
OBJECTS_D := $(notdir $(OBJECTS_D))
OBJECTS_D := $(addprefix $(DEBUG_BUILD)/$(OBJ_DIR)/, $(OBJECTS_D))

all:
	\mkdir -p $(RELEASE_BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SOURCES) $(LIBS)
	\mv -f *.o $(RELEASE_BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(LIBS)
	\mv -f PongGame $(RELEASE_BUILD)/

release:
	\mkdir -p $(RELEASE_BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SOURCES) $(LIBS)
	\mv -f *.o $(RELEASE_BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(LIBS)
	\mv -f PongGame $(RELEASE_BUILD)/

debug:
	\mkdir -p $(DEBUG_BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS_D) -c $(SOURCES) $(LIBS)
	\mv -f *.o $(DEBUG_BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS_D) -o $(EXEC) $(OBJECTS_D) $(LIBS)
	\mv -f PongGame $(DEBUG_BUILD)/

clean:
	rm -f $(wildcard $(RELEASE_BUILD)/$(OBJ_DIR)/*.o)
	rm -f $(wildcard $(DEBUG_BUILD)/$(OBJ_DIR)/*.o)
