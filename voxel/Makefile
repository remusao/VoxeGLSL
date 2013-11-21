CXX=g++
CXXFLAGS=-std=c++11 -march=native -Ofast -Wall -Wextra -pedantic
LINKAGE=$(shell pkg-config --cflags --libs glfw3) $(shell pkg-config --cflags --libs glew)

SRC=main.cc voxelEngine.cc shader.cc
BINARY=lie

.PHONY: lie

all: lie

lie:
	${CXX} ${CXXFLAGS} -o ${BINARY} ${SRC} ${LINKAGE}
