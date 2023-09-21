# Project Title

CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# Directories
SRC_DIR := src
SHADER_DIR := shaders

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
HEADER_FILES := $(wildcard $(SRC_DIR)/*.hpp)

# Shader files
VERT_SHADER := $(wildcard $(SHADER_DIR)/*.vert)
FRAG_SHADER := $(wildcard $(SHADER_DIR)/*.frag)

# Executable
EXECUTABLE := VulkanTest

$(EXECUTABLE): $(SRC_FILES) $(HEADER_FILES) $(VERT_SHADER) $(FRAG_SHADER)
	g++ $(CFLAGS) -o $(EXECUTABLE) $(SRC_FILES) $(LDFLAGS)

.PHONY: all test clean shaders

all: $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

shaders: $(VERT_SHADER:.vert=.vert.spv) $(FRAG_SHADER:.frag=.frag.spv)

%.vert.spv: %.vert
	glslc $< -o $@

%.frag.spv: %.frag
	glslc $< -o $@

clean:
	rm -f $(EXECUTABLE) $(SHADER_DIR)/*.spv
