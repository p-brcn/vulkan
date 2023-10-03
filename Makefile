# Project Title

CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# Directories
SRC_DIR := src
SHADER_DIR := shaders
OUT_DIR := $(SHADER_DIR)/spv

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
HEADER_FILES := $(wildcard $(SRC_DIR)/*.hpp)

# Shader files
VERT_SHADER := $(wildcard $(SHADER_DIR)/*.vert)
FRAG_SHADER := $(wildcard $(SHADER_DIR)/*.frag)
VERT_SPV := $(patsubst $(SHADER_DIR)/%.vert,$(OUT_DIR)/%.vert.spv,$(VERT_SHADER))
FRAG_SPV := $(patsubst $(SHADER_DIR)/%.frag,$(OUT_DIR)/%.frag.spv,$(FRAG_SHADER))

# Executable
EXECUTABLE := VulkanTest

$(EXECUTABLE): $(SRC_FILES) $(HEADER_FILES) $(VERT_SPV) $(FRAG_SPV)
	g++ $(CFLAGS) -o $(EXECUTABLE) $(SRC_FILES) $(LDFLAGS)

.PHONY: all test clean shaders

all: $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

$(OUT_DIR)/%.vert.spv: $(SHADER_DIR)/%.vert
	mkdir -p $(OUT_DIR)
	glslc $< -o $@

$(OUT_DIR)/%.frag.spv: $(SHADER_DIR)/%.frag
	mkdir -p $(OUT_DIR)
	glslc $< -o $@

shaders: $(VERT_SPV) $(FRAG_SPV)

clean:
	rm -f $(EXECUTABLE) $(VERT_SPV) $(FRAG_SPV)
