#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include "btree.h"


void createTree(std::string lkp, std::string lpk, char node, std::vector<char>& klp, bTree &BinTree)
{
	bTree leftSubTree = Create();
	bTree rightSubTree = Create();

	klp.push_back(node);
	if (lpk.length() < 2){
		BinTree = new Node;
		BinTree->root = node;
		return;
	}

	int index = lkp.find(node);
	
	std::string leftlkp = lkp.substr(0, index);
	std::string leftlpk = lpk.substr(0, index);
	std::string rightlkp = lkp.substr(index + 1);
	lpk = lpk.erase(lpk.length()-1, 1);
	std::string rightlpk = lpk.substr(index);

	
	
	if (index!= 0){


			createTree(leftlkp, leftlpk, leftlpk[leftlpk.size() - 1], klp, leftSubTree);
	
	}


	createTree(rightlkp, rightlpk, rightlpk[rightlpk.size() - 1], klp, rightSubTree);

	
	BinTree = consBT(node, leftSubTree, rightSubTree);
	return;
}
void readFromFile(std::ifstream &file){
		
		int count;
		std::string lkp;
		std::string lpk;

		std::vector<char> klp;
		

		if(!file.is_open()){
  	  		std::cout<<"Неверный путь к файлу\n";
	    		return;
    		}
		std::string str;
		while (std::getline(file,str)){
			if (str[0] == ' ') continue;
			else{
				if(count == 0) {lkp = str; count++;continue;}
				else if(count == 1){lpk = str; count++; continue;}
				else{
				count = 0;
	
				bTree MyBinTree;
				createTree(lkp, lpk, lpk[lpk.size() - 1], klp, MyBinTree);			
				
				std::cout << " Узлы дерева в порядке ЛКП:" << lkp << std::endl;
				std::cout << " Узлы дерева в порядке ЛПК:" << lpk << std::endl;
				std::cout << " Узлы дерева в порядке КЛП: ";

				for ( auto i: klp)
					std::cout << i;

				std::cout << std::endl;
				klp.clear();
				lkp.clear();
				lpk.clear();

				std::cout << " Изображение БД:" << std::endl;
				displayBT (MyBinTree,1);
				destroy(MyBinTree);
				}
			}
		}
}

int main(int argc, char* argv[]){
	
	

	if (argc == 2) {
		std::ifstream file(argv[1]);
		readFromFile(file);
	
	}else{
	
	std::string lkp;
	std::string lpk;

	std::cout << " Введите последовательность узлов в порядке ЛКП:";
	getline(std::cin, lkp);
	std::cout << "\n Введите последовательность узлов в порядке ЛПК:";
	getline(std::cin, lpk);

	std::vector<char> klp;
	
	bTree MyBinTree;

	createTree(lkp, lpk, lpk[lpk.size() - 1], klp, MyBinTree);

	std::cout << " Узлы дерева в порядке КЛП:" << std::endl;

	for ( auto i: klp)
		std::cout << ' ' << i;
	std::cout << std::endl;

	std::cout << " Изображение БД:" << std::endl;
	displayBT (MyBinTree,1);
	destroy(MyBinTree);
	
	}return 0;
}
