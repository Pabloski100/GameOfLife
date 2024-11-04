# Define the directory for source files
SRC_DIR = src

# Define the directory for object files
OBJ_DIR = obj

# List of source files
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/gamegui.cpp \
          $(SRC_DIR)/game.cpp \
          $(SRC_DIR)/presets.cpp \
          $(SRC_DIR)/utils.cpp

# List of object files (corresponding to source files)
OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/gamegui.o \
          $(OBJ_DIR)/game.o \
          $(OBJ_DIR)/presets.o \
          $(OBJ_DIR)/utils.o

# Target executable
TARGET = main

# Compiler and flags
CXX = g++
CXXFLAGS = -O2 -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -larmadillo

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean object files
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
