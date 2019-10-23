all: lab5.exe

lab5.exe: main.o encodetree.o fanoshannontree.o
	g++ -Wall -Werror main.o encodetree.o fanoshannontree.o -o lab5.exe

main.o: ./Source/main.cpp
	g++ -c -Wall -Werror ./Source/main.cpp

encodetree.o: ./Source/encodetree.cpp ./Source/encodetree.h
	g++ -c -Wall -Werror ./Source/encodetree.cpp

fanoshannontree.o: ./Source/fanoshannontree.cpp ./Source/fanoshannontree.h
	g++ -c -Wall -Werror ./Source/fanoshannontree.cpp

clean:
	rm -rf *.o
