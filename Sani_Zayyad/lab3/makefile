all: main.o stack.o
	g++ main.o stack.o -std=c++17 -o lab3
main.o: Source/main.cpp Source/stack.hpp
	g++ -c Source/main.cpp -std=c++17
stack.o: Source/stack.cpp Source/stack.hpp
	g++ -c Source/stack.cpp -std=c++17
