#include <iostream>
#include <fstream>

struct numberRoot{
	int counter = 0;
	int array[3000];
};

typedef struct numberRoot numberRoot;

int main(){
	std::ifstream fileRoots;
	std::ifstream fileHeights;
	std::ofstream forGraphics;
	std::ofstream forMediumGraphic;
	fileRoots.open("ResultRootsWorst.txt");
	fileHeights.open("ResultHeightsWorst.txt");
	forGraphics.open("DataForGraphics.txt", std::ios_base::out | std::ios_base::trunc);
	int bufRoots;
	numberRoot RootsWorst[10];
	
	while(fileRoots >> bufRoots){
		fileHeights >> RootsWorst[bufRoots-1].array[RootsWorst[bufRoots-1].counter];
		RootsWorst[bufRoots-1].counter++;
//		std::cout << "Height is: " << RootsWorst[bufRoots-1].array[RootsWorst[bufRoots-1].counter - 1] << "; Root is:" << bufRoots << "; Counter is: " << RootsWorst[bufRoots-1].counter << ";" << std::endl;
	}
	
	std::cout << "root distribution: " << std::endl;
	int max = 0;
	int min = 100000;
	int IndexMin, IndexMax, sum;
	sum = 0;
	
	for(int i = 0; i < 10; i++){
		std::cout << "Quantity roots with value \'" << i + 1 << "\' is: " << RootsWorst[i].counter << std::endl;
		forGraphics << "(" << -(i + 1) << ";" << RootsWorst[i].counter << ")";
		if(RootsWorst[i].counter > max){
			max = RootsWorst[i].counter;
			IndexMax = i + 1;
		}
		if(RootsWorst[i].counter < min){
			min = RootsWorst[i].counter;
			IndexMin = i + 1;
		}
		sum = sum + RootsWorst[i].counter;
	}
	
	std::cout << "Least probable root meets over " << min << "; It is \'" << IndexMin << "\'" << std::endl;
	std::cout << "Most probable root meets over " << max << "; It is \'" << IndexMax << "\'" << std::endl;
	std::cout << "The program has been run " << sum << " times" << std::endl;
	
	float mediumValue = 0;
	max = 0;
	min = 100000;
	int WorstCounter = 0;
	int BestCounter = 0;
	
	for(int i = 0; i < 10; i++){
		if(RootsWorst[i].counter == 0){
			continue;
		}
		for(int j = 0; j < RootsWorst[i].counter; j++){
			mediumValue = mediumValue + (float)RootsWorst[i].array[j];
			if(RootsWorst[i].array[j] > max){
				max = RootsWorst[i].array[j];
				WorstCounter = 1;
			}
			else if(RootsWorst[i].array[j] == max){
				WorstCounter++;
			}
			if(RootsWorst[i].array[j] < min){
				min = RootsWorst[i].array[j];
				BestCounter = 1;
			}
			else if(RootsWorst[i].array[j] == min){
				BestCounter++;
			}
		}
		mediumValue = mediumValue/(float)RootsWorst[i].counter;
		std::cout << "Medium value of Height for " << i + 1 << " is: " << mediumValue << "; max height is: " << max << "; min height is: " << min << ";" << std::endl;
		std::cout << "Quantity of the WORST cases: " << WorstCounter << "; probability of this cases for root: " << (float)WorstCounter/RootsWorst[i].counter << std::endl;
		std::cout << "Quantity of the BEST cases: " << BestCounter << "; probability of this cases for root: " << (float)BestCounter/RootsWorst[i].counter << std::endl << std::endl;
		mediumValue = 0;
		min = 100000;
		max = 0;
		BestCounter = 0;
		WorstCounter = 0;
	}

	fileHeights.close();
	fileRoots.close();
	forGraphics.close();
	return 0;
}



