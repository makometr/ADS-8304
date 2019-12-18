#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

int main(){
	srand(time(0));
	std::ofstream file;
	file.open("Tests/TestDataRandom.txt", std::ios::app);
	for(int i = 0; i < 200; i++){
		for(int i = 0; i < 5 + rand()%15; i++){
			file << rand()%100 << " "; 
		}
		file << std::endl;
	}
	
	file.close();
	return 0;
}



