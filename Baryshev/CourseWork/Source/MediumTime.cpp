#include <iostream>
#include <fstream>
#include <cstdlib>

int main(){
	std::ifstream fileTime;
	fileTime.open("ResultTimeFind.txt");
	float buf;
	float array[3000];
	float medium = 0;
	int counter = 0;
	
	while(fileTime >> buf){
	 	array[counter] = buf;
		medium = medium + array[counter];
		counter++;
	}
	medium =  medium/counter;
	
	std::cout << " Medium time for find one elem(for an average of " << counter << " data) is: " << medium << std::endl;
	
	fileTime.close();
	return 0;
}



