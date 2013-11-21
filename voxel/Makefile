CXX=g++
CXXFLAGS=-std=c++11 -march=native -Ofast -Wall -Wextra -pedantic
LINKAGE=$(shell pkg-config --cflags --libs sfml-graphics) $(shell pkg-config --cflags --libs glew)

SRC=main.cc voxelEngine.cc shader.cc camera.cc
BINARY=lie

.PHONY: lie

all: lie

lie:
	${CXX} ${CXXFLAGS} -o ${BINARY} ${SRC} ${LINKAGE}
