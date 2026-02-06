SRCS=$(wildcard src/*.cpp)
NAME=bin/solitaire

CXXFLAGS := -Iinclude

all: 
	g++ -Og $(CXXFLAGS) $(SRCS) -o $(NAME)
release:
	g++ -Ofast $(CXXFLAGS) $(SRCS) -static -o $(NAME)