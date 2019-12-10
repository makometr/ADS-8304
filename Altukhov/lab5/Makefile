all: main.o HashTable.o
	g++ -Wall -Werror main.o HashTable.o -o lab5

main.o: Source/main.cpp
	g++ -c -Wall -Werror Source/main.cpp

queue.o: Source/HashTable.cpp
	g++ -c -Wall -Werror Source/HashTable.cpp