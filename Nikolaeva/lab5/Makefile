all: lab5.exe

lab5.exe: main.o
	g++ main.o -o lab5.exe -g

main.o: ./Source/main.cpp
	g++ -c ./Source/main.cpp -g

clean:
	rm -rf *.o
