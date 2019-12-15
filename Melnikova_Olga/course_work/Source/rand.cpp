#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <ctime>
int main(int argc, char* argv[]){
	std::ofstream fout(argv[1]);
	long count = atoi(argv[2]);
	srand(time(0));
	int i = 0;
    while (i++ < count){
    	fout << rand() << std::endl;
    }

}

