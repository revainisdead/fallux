.PHONY: all run build

EXE_NAME= fallux.exe
WORKING_DIR= $(shell pwd)
#RELATIVE_WORKING_DIR= ${CUR_DIR}
IRR_DIR= $(WORKING_DIR)/lib/irrlicht-1.8.4
IRR_LIB= $(IRR_DIR)/lib/Linux
IRR_INCLUDE= $(IRR_DIR)/include

# Replace all backslashes with escaped backslashes.
#BUILD_WHITELIST= $(shell echo $(shell pwd)/lib/ | sed -e "s:/:\\\/:g")

# git ls-files prints relative paths, use those here for exclusion.
BUILD_WHITELIST= lib/

all: build run

build:
	g++ $$(git ls-files -- "*.cpp" | grep -v $(BUILD_WHITELIST)) -I$(IRR_INCLUDE) -L$(IRR_LIB) -lIrrlicht -lGLU -lGL -lX11 -lXxf86vm -Wall -o $(EXE_NAME)

run:
	@./$(EXE_NAME)
