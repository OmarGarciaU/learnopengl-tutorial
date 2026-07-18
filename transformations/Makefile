APP_NAME = Enigma
BUILD_DIR = ./bin
CPP_FILES = ./src/main.cpp 
C_FILES = ./src/include/glad/glad.c
# Replace this with the actual path to the GLFW library file
BINARY = ./src/include/GLFW/libs/libglfw.3.dylib

# Combine includes and linkers
APP_FLAGS = -g -std=c++17 -I./src/include/GLFW -I./src/include -I./src/include/glad -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -L./src/include/GLFW/libs -lglad -lglfw3

build:
	clang++ -arch arm64 $(CPP_FILES) $(C_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_FLAGS)

.PHONY: clean

clean:
	rm -f $(BUILD_DIR)/$(APP_NAME)

