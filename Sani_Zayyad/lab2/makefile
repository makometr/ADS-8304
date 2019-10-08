all: main.o hierarchy.o
	g++ main.o hierarchy.o -std=c++17 -o lab2
main.o: Source/main.cpp Source/hierachy.h
	g++ -c Source/main.cpp -std=c++17
hierachy.o: Source/hierachy.cpp Source/hierachy.h
	g++ -c Source/hierrachy.cpp -std=c++17
