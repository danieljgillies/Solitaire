SRCS=$(wildcard src/*.cpp)
NAME=solitaire

all: 
	g++ -Og $(SRCS) -o $(NAME)
release:
	g++ -Ofast $(SRCS) -static -o $(NAME)