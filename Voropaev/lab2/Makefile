main.cpp: main.o krm.o
	g++ -std=c++17 -Wall main.o krm.o -o lab2
main.o: Source/main.cpp Source/krm.h
	g++ -std=c++17 -c Source/main.cpp
krm.o: Source/krm.cpp Source/krm.h
	g++ -std=c++17 -c Source/krm.cpp
clean:
	rm -rf *.o
