all: lab2

lab2: main.o hierarchicallist.o
	g++ -Wall -Werror main.o hierarchicallist.o -o lab2
hierarchicallist.o: Source/hierarchicallist.cpp
	g++ -c -Wall -Werror -std=c++11 Source/hierarchicallist.cpp 
main.o: Source/main.cpp
	g++ -c -Wall -Werror Source/main.cpp
clean:
	rm -rf *.o
