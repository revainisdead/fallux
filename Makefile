.PHONY: all run build

EXE_NAME= fallux.exe

build:
	g++ $(git ls-files -- "*.cpp") -Wall -o $(EXE_NAME)

run: build
	@./$(EXE_NAME)


all: run
