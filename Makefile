CC = gcc
TARGET = raycasting
SRC = raycasting.c

RAYLIB_PATH = raylib
INCLUDES = -I"$(RAYLIB_PATH)/include"
LIBS = -L"$(RAYLIB_PATH)/lib" -lraylib

ifeq ($(OS),Windows_NT)
    SYS_LIBS = -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
    EXE_EXT = .exe
else
    SYS_LIBS = -lm -ldl -lpthread -lGL -lGLU -lX11
    RM = rm -f
    EXE_EXT =
endif

CFLAGS = -Wall -Wextra -std=c11

all: "$(TARGET)$(EXE_EXT)"

"$(TARGET)$(EXE_EXT)": $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o "$(TARGET)$(EXE_EXT)" $(LIBS) $(SYS_LIBS)

run: "$(TARGET)$(EXE_EXT)"
ifeq ($(OS),Windows_NT)
	"./$(TARGET)$(EXE_EXT)"
else
	./"$(TARGET)$(EXE_EXT)"
endif

clean:
	$(RM) "$(TARGET)$(EXE_EXT)"

