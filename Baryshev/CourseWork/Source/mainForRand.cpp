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
	foutViz.open("ResultVizualize.txt", std::ios::app);
	std::ofstream foutRoots;
	foutRoots.open("ResultRoots.txt", std::ios::app);
	std::ofstream foutHeights;
	foutHeights.open("ResultHeights.txt", std::ios::app);
	std::ofstream foutTimeFind;
	foutTimeFind.open("ResultTimeFind.txt", std::ios::app);
	std::ifstream fenter("Tests/TestDataRandom.txt");
	std::string Expr;
	int* arrayNum = new int[200];
	int stop, start, find;
	
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
		find = arrayNum[rand()%arrayNumber];
		start = clock();
		Find(h, find);
		stop = clock();
		foutTimeFind << (stop - start)/1000.0 << " ";
		displayBT(h, 1, foutViz);
		foutViz << " Will find: " << find << ";" << std::endl;
		destroy(h);
	}

	delete arrayNum;
	fenter.close();
	foutRoots.close();
	foutViz.close();
	foutHeights.close();
	foutTimeFind.close();
	return 0;
}



