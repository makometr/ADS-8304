all: cw.exe

cw.exe: main.o huffmantree.o fanoshannontree.o encodetree.o decode.o
	g++ main.o huffmantree.o fanoshannontree.o encodetree.o decode.o -o cw.exe -g

main.o: ./Source/main.cpp
	g++ -c ./Source/main.cpp -g

huffmantree.o: ./Source/huffmantree.cpp ./Source/huffmantree.h
	g++ -c ./Source/huffmantree.cpp

fanoshannontree.o: ./Source/fanoshannontree.cpp ./Source/fanoshannontree.h
	g++ -c ./Source/fanoshannontree.cpp

encodetree.o: ./Source/encodetree.cpp ./Source/encodetree.h
	g++ -c ./Source/encodetree.cpp

decode.o: ./Source/decode.cpp ./Source/decode.h
	g++ -c ./Source/decode.cpp
clean:
	rm -rf *.o
	rm result.txt
