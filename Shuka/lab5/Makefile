all: lab5.exe

lab5.exe: main.o encodetree.o fanoshannontree.o
	g++ main.o encodetree.o fanoshannontree.o -o lab5.exe

main.o: ./Source/main.cpp
	g++ -c -Wall ./Source/main.cpp

encodetree.o: ./Source/encodetree.cpp
	g++ -c -Wall ./Source/encodetree.cpp

fanoshannontree.o: ./Source/fanoshannontree.cpp
	g++ -c -Wall ./Source/fanoshannontree.cpp

clean:
	rm -rf *.o
