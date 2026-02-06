SRCS=$(wildcard src/*.cpp)
NAME=solitaire

CXXFLAGS := -Iinclude

all: 
	g++ -Og $(CXXFLAGS) $(SRCS) -o $(NAME)
release:
	g++ -Ofast $(CXXFLAGS) $(SRCS) -static -o $(NAME)