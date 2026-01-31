# Compiler
CC = gcc

# Target executable
TARGET = raycasting

# Source files (تمام فایل‌های .c داخل src/)
SRC = $(wildcard src/*.c)

# Raylib paths
RAYLIB_PATH = raylib
INCLUDES = -I"$(RAYLIB_PATH)/include"
LIBS = -L"$(RAYLIB_PATH)/lib" -lraylib

# System-dependent settings
ifeq ($(OS),Windows_NT)
    SYS_LIBS = -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
    EXE_EXT = .exe
else
    SYS_LIBS = -lm -ldl -lpthread -lGL -lGLU -lX11
    RM = rm -f
    EXE_EXT =
endif

# Compile flags
CFLAGS = -Wall -Wextra -std=c11

# Default target
all: "$(TARGET)$(EXE_EXT)"

# Build rule
"$(TARGET)$(EXE_EXT)": $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o "$(TARGET)$(EXE_EXT)" $(LIBS) $(SYS_LIBS)

# Run the program
run: "$(TARGET)$(EXE_EXT)"
ifeq ($(OS),Windows_NT)
	"./$(TARGET)$(EXE_EXT)"
else
	./"$(TARGET)$(EXE_EXT)"
endif

# Clean build
clean:
	$(RM) "$(TARGET)$(EXE_EXT)"


