all: main.o tree.o
	g++ main.o tree.o -std=c++17 -o lab4
main.o: Source/main.cpp Source/tree.hpp
	g++ -c Source/main.cpp -std=c++17
tree.o: Source/tree.cpp Source/tree.hpp
	g++ -c Source/tree.cpp -std=c++17
