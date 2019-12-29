all: lab4.exe

lab4.exe: main.o
	g++ -Wall -Werror main.o -o lab4.exe

main.o: ./Source/main.cpp ./Source/mybinarytree.h
	g++ -c -Wall -Werror ./Source/main.cpp

clean:
	rm -rf *.o
