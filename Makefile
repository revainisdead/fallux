.PHONY: all run build

EXE_NAME= fallux.exe
WORKING_DIR= $(shell pwd)
IRR_DIR= $(WORKING_DIR)/lib/irrlicht-1.8.4
IRR_LIB= $(IRR_DIR)/lib/
IRR_INCLUDE= $(IRR_DIR)/include/

all: build run

build:
	g++ $$(git ls-files -- "*.cpp") -I $(IRR_INCLUDE) -L $(IRR_LIB) -Wall -o $(EXE_NAME)

run:
	@./$(EXE_NAME)
