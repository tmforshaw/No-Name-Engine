
# This is messy as fuck and it's mostly because I have to include glad.c but also because I am bad with Makefiles

PROJECTNAME = NoNameEngine

CC = g++
CFLAGS = -std=c++2a
LINKFLAGS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

BUILDDIR := bin
OBJDIR := lib
SRCDIR := src
DEPENDDIR := dependencies

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJS += $(OBJDIR)/glad.o

# Build the project
.PHONY: build
build: $(OBJS) $(BUILDDIR)/$(PROJECTNAME).bin
	@echo !-- Built $(PROJECTNAME).bin --!

# Create the necessary folders
.PHONY: setup
setup:
	@echo !-- Setting Up Environment --!
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(OBJDIR)

# Remove unneeded files
.PHONY: clean
clean:
	@echo !-- Cleaning Folders --!
	@rm -rf $(BUILDDIR)/*
	@rm -rf $(OBJDIR)/*

# Compile the individual cpp files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo !-- Compiling $^ --!
	@mkdir -p $(@D)
	@$(CC) -c $^ -o $@ $(CFLAGS)

# Compile the individual c files
$(OBJDIR)/%.o: $(DEPENDDIR)/%.c
	@echo !-- Compiling $^ --!
	@$(CC) -c $^ -o $@ $(CFLAGS)

# Link the files together
$(BUILDDIR)/$(PROJECTNAME).bin: $(OBJS)
	@echo !-- Linking $^ --!
	@$(CC) -o $@ $^ $(LINKFLAGS)

# Run the project as an executable
.PHONY: run
run: build
	@echo !-- Running --!
	@./$(BUILDDIR)/$(PROJECTNAME).bin