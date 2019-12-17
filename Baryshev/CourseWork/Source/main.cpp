#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "SecondaryFunctions.h"
#include "BinTreeSearch.h"

int main(){
	srand(time(0));
	int arrayNumber = 0;
	std::ofstream foutViz;
	foutViz.open("ResultVizualizeWorst.txt", std::ios::app);
	std::ofstream foutRoots;
	foutRoots.open("ResultRootsWorst.txt", std::ios::app);
	std::ofstream foutHeights;
	foutHeights.open("ResultHeightsWorst.txt", std::ios::app);
	std::ifstream fenter("Tests/TestDataWorst.txt");
	std::string Expr;
	int* arrayNum = new int[200];
	
	while(std::getline(fenter, Expr)){
		BinSearchTree h = NULL;
		arrayNumber = getNumbers(arrayNum, Expr);
		for(int i = 0; i < arrayNumber; i++){
			h = Insert(h, arrayNum[i]);
		}
		foutRoots << h->key << " ";
		foutHeights << hBT(h) << " ";
		foutViz << "________________________________" << std::endl;
		foutViz << "Was introduce: " << std::endl;
		displayBT(h, 1, foutViz);
		destroy(h);
	}

	delete arrayNum;
	fenter.close();
	foutRoots.close();
	foutViz.close();
	foutHeights.close();
	return 0;
}



