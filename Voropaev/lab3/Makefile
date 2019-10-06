main.cpp: main.o queue.o
	g++ -Wall main.o queue.o -o lab3
main.o: Source/main.cpp Source/queue.h
	g++ -c Source/main.cpp
queue.o: Source/queue.cpp Source/queue.h
	g++ -c Source/queue.cpp
clean:
	rm -rf *.o
