#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "BinTreeSearch.h"

int main(){
	
	srand(time(0));
	std::ofstream foutViz;
	foutViz.open("ResultVizualizeWorst.txt", std::ios_base::out | std::ios_base::trunc);
	std::ofstream foutRoots;
	foutRoots.open("ResultRootsWorst.txt", std::ios_base::out | std::ios_base::trunc);
	std::ofstream foutHeights;
	foutHeights.open("ResultHeightsWorst.txt", std::ios_base::out | std::ios_base::trunc);
	
	int arrayNum[10];
	for(int i = 10; i > 0; i--){
		arrayNum[10-i] = i;
	}

	for(int j = 0; j < 1332; j++){
		BinSearchTree h = NULL;
		for(int i = 0; i < 10; i++){
			h = Insert(h, arrayNum[i]);
		}
		foutRoots << h->key << " ";
		foutHeights << hBT(h) << " ";
		foutViz << "________________________________" << std::endl;
		foutViz << "Was introduce: " << std::endl;
		displayBT(h, 1, foutViz);
		destroy(h);
	}

	foutRoots.close();
	foutViz.close();
	foutHeights.close();
	
	return 0;
}



