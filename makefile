# Define variables for directory paths and compiler flags
ASST_DIR=./assets
SRC_DIR=./source
INCLUDE_DIR=./include

CXXFLAGS=-I$(INCLUDE_DIR) -o2 -flto -ffunction-sections -fdata-sections -os
LDFLAGS+=-s -flto -Wl,--gc-sections

# Define variables for source and header files
SRCS=$(shell find $(SRC_DIR) -name "*.cpp" -o -name "*.c")
HEADERS=$(shell find $(INCLUDE_DIR) -name "*.hpp" -o -name "*.h")
ASSTS=$(shell find $(ASST_DIR) -name "*.cpp" -o -name "*.c" -name "*.hpp" -o -name "*.h")

# Define the main target
all: CPPExecute;

# Define the Test target
CPPExecute: $(ASSTS) $(SRCS) $(HEADERS)
	g++ $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o CPPExecute
	strip CPPExecute

# Define the clean target
clean:
	rm -f CPPExecute