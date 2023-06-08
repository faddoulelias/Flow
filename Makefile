.PHONY = all clean run

# Compiler
CXX := g++
CFLAGS := -Wall -g -std=c++17
SDLFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf

# Directories
BUILD  := ./build
OBJECT := ./build/obj
SOURCE := ./src
HEADER := ./src/headers

# Files
SRCS := $(wildcard $(SOURCE)/*.cpp)
OBJS := $(patsubst $(SOURCE)/%.cpp, $(OBJECT)/%.o, $(SRCS))
EXEC := $(BUILD)/Flow

# Makefile commands
all : $(EXEC)

run:$(EXEC)
	$(EXEC) $(ARGS)

$(EXEC) : $(OBJS)
	$(CXX) $(CFLAGS) -o $(EXEC) $(OBJS) $(SDLFLAGS)

$(OBJECT)/%.o : $(SOURCE)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $^ $(SDLFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)
