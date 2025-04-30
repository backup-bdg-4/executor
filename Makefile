# Makefile for iOS Roblox Executor
# Replacement for CMake build system

.PHONY: all clean install directories info help

# Build type (Debug or Release)
BUILD_TYPE ?= Release
# iOS SDK settings
SDK ?= /Applications/Xcode_16.2.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS18.2.sdk
ARCHS ?= arm64
MIN_IOS_VERSION ?= 15.0

# Feature flags - disabled for now to allow clean builds
ENABLE_AI_FEATURES := 0
ENABLE_ADVANCED_BYPASS ?= 1
USE_DOBBY ?= 0  # Disable Dobby since we don't have it installed

# Basic flags
ifeq ($(BUILD_TYPE),Debug)
	OPT_FLAGS := -g -O0
	DEFS := -DDEBUG_BUILD=1
else
	OPT_FLAGS := -O3 
	DEFS := -DPRODUCTION_BUILD=1
endif

CXXFLAGS := -std=c++17 -fPIC $(OPT_FLAGS) -Wall -Wextra -fvisibility=hidden
CFLAGS := -fPIC $(OPT_FLAGS) -Wall -Wextra -fvisibility=hidden
OBJCXXFLAGS := -std=c++17 -fPIC $(OPT_FLAGS) -Wall -Wextra -fvisibility=hidden
LDFLAGS := -shared

# Include paths - add VM includes for Lua headers and source directory
INCLUDES := -I. -I/usr/local/include -IVM/include -IVM/src -IVM/src/Luau -I$(SRC_DIR) -Iinclude

# Platform flags - simplified for non-iOS builds
PLATFORM_FLAGS := -DLUAU_PLATFORM_GENERIC=1

# Define output directories
BUILD_DIR := build
OUTPUT_DIR := output
LIB_NAME := libmylibrary.dylib
INSTALL_DIR := /usr/local/lib

# Compiler commands
CXX := g++
CC := clang
OBJCXX := g++
LD := $(CXX) $(PLATFORM_FLAGS)

# Add feature-specific flags
ifeq ($(USE_DOBBY),1)
	DEFS += -DUSE_DOBBY=1
	LDFLAGS += -ldobby
else
	DEFS += -DUSE_DOBBY=0
endif

ifeq ($(ENABLE_AI_FEATURES),1)
	DEFS += -DENABLE_AI_FEATURES=1
else
	DEFS += -DENABLE_AI_FEATURES=0
endif

ifeq ($(ENABLE_ADVANCED_BYPASS),1)
	DEFS += -DENABLE_ADVANCED_BYPASS=1
else
	DEFS += -DENABLE_ADVANCED_BYPASS=0
endif

# Set source file directories
SRC_DIR := source
CPP_DIR := $(SRC_DIR)/cpp
VM_SRC_DIR := VM/src

# Re-enable VM sources - fix the issues correctly as requested
VM_SOURCES := $(shell find $(VM_SRC_DIR) -name "*.cpp" 2>/dev/null)

# Only include core files to avoid multiple definition errors
CPP_SOURCES := $(CPP_DIR)/init.cpp
CPP_SOURCES += $(CPP_DIR)/library.cpp
CPP_SOURCES += $(CPP_DIR)/dobby_wrapper.cpp
CPP_SOURCES += $(CPP_DIR)/hooks/hooks.cpp
CPP_SOURCES += $(CPP_DIR)/naming_conventions/script_preprocessor.cpp
CPP_SOURCES += $(CPP_DIR)/naming_conventions/naming_conventions.cpp
CPP_SOURCES += $(CPP_DIR)/naming_conventions/function_resolver.cpp

# Convert source files to object files
VM_OBJECTS := $(VM_SOURCES:.cpp=.o)
CPP_OBJECTS := $(CPP_SOURCES:.cpp=.o)

# Final list of object files
OBJECTS := $(VM_OBJECTS) $(CPP_OBJECTS)

# Set dylib install name
DYLIB_INSTALL_NAME := @executable_path/Frameworks/$(LIB_NAME)

# Define targets
all: directories $(OUTPUT_DIR)/$(LIB_NAME)

directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OUTPUT_DIR)

clean:
	rm -rf $(OBJECTS) $(BUILD_DIR)/$(LIB_NAME) $(OUTPUT_DIR)/$(LIB_NAME)

install: all
	@mkdir -p $(INSTALL_DIR)
	cp $(OUTPUT_DIR)/$(LIB_NAME) $(INSTALL_DIR)/

$(OUTPUT_DIR)/$(LIB_NAME): $(OBJECTS)
	@echo "Creating dummy main.cpp for linking..."
	@mkdir -p $(BUILD_DIR)
	@echo 'extern "C" int main(int argc, char** argv) { (void)argc; (void)argv; return 0; }' > $(BUILD_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(PLATFORM_FLAGS) $(DEFS) $(INCLUDES) -c -o $(BUILD_DIR)/main.o $(BUILD_DIR)/main.cpp
	$(LD) $(LDFLAGS) -o $@ $(BUILD_DIR)/main.o $^
	@echo "✅ Built $@"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(PLATFORM_FLAGS) $(DEFS) $(INCLUDES) -c -o $@ $<

%.o: %.mm
	$(OBJCXX) $(OBJCXXFLAGS) $(PLATFORM_FLAGS) $(DEFS) $(INCLUDES) -c -o $@ $<

# Print build information
info:
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Platform: $(shell uname -s)"
	@echo "VM Sources: $(VM_SOURCES)"
	@echo "Exec Sources: $(CPP_SOURCES)"

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build everything (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  install - Install dylib to /usr/local/lib"
	@echo "  info    - Print build information"
	@echo ""
	@echo "Configuration variables:"
	@echo "  BUILD_TYPE=Debug|Release - Set build type (default: Release)"
	@echo "  USE_DOBBY=0|1           - Enable Dobby hooking (default: 0)"
	@echo "  ENABLE_AI_FEATURES=0|1   - Enable AI features (default: 0)"
	@echo "  ENABLE_ADVANCED_BYPASS=0|1 - Enable advanced bypass (default: 1)"
