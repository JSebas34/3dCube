# Detect OS
UNAME_S := $(shell uname -s)

# Compiler flags
CXXFLAGS = -std=c++17 -g
INCLUDES = -Iinclude -Iinclude/glad_$(UNAME_S) -Iinclude/KHR
LDFLAGS = -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -ldl

# Default source and output
SRC = src/glad_4.1.c
OUTPUT = $(basename $(file))

# OS-specific settings
ifeq ($(UNAME_S), Darwin)
    SRC = src/glad_4.1.c
    OUTPUT = $(basename $(file))
else ifeq ($(OS), Windows_NT)
    SRC = src/glad_4.6.c
    OUTPUT = $(basename $(file)).exe
else
    OUTPUT = $(basename $(file))
endif

# Ensure file is passed
ifeq ($(file),)
    $(error "Usage: make build file=yourfile.cpp")
endif

# Build rule
build:
	g++ $(CXXFLAGS) $(file) $(SRC) -o $(OUTPUT) $(INCLUDES) $(LDFLAGS)
