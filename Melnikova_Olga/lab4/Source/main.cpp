
#include "BinaryTree.h"

std::string getStringWithoutBrackets(std::string str)
{
    int i = 0;
    while (str[i] == ' ') i++;
    if (str[i] != '('){
    std::cout<<"Неправильная запись дерева" << std::endl;
        	exit(1);
    }
    i++;
    int br = 1;
    int symbolsCount = 0;
    while ((br > 0) && (i+symbolsCount < str.length()))
    {
        symbolsCount++;
        if (str[i+symbolsCount] == '(') br++;
        if (str[i+symbolsCount] == ')') br--;
    }
    if (br > 0){
    	std::cout<<"Неправильная запись дерева" << std::endl;
        exit(1);
    }
    return str.substr(i, symbolsCount);
}


int main(int argc, char* argv[]) {
    int testCounter = 0;
    std::string str1,
                str2;
    if(argc == 1)
    {
        std::cout << "Input first string:" << std::endl;
        std::getline(std::cin, str1);
        std::cout << "Input second string:" << std::endl;
        std::getline(std::cin, str2);
    }
    else
    {
        std::cout << "For file: " << argv[1] << std::endl;
        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open())
        {
            std::cout << "ERROR: file isn't open" << std::endl;
            return 0;
        }
        if (inputFile.eof())
        {
            std::cout << "ERROR: file is empty" << std::endl;
            return 0;
        }
        std::getline(inputFile, str1);
        std::getline(inputFile, str2);
    }

    std::unique_ptr<BinaryTree<char>> tree1(new BinaryTree<char>());
    std::unique_ptr<BinaryTree<char>> tree2(new BinaryTree<char>());
    tree1->makeFromString(getStringWithoutBrackets(str1));
    tree2->makeFromString(getStringWithoutBrackets(str2));
    std::cout << "Бинарные деревья: ";
    if(tree1->isResemlanceWith(tree2)){
        std::cout << "подобны, ";
    }else{
        std::cout << "не подобны, ";
    }
    if(tree1->isMirrorResemlanceWith(tree2)){
        std::cout << "зеркально подобны, ";
    }else{
        std::cout << "не зеркально подобны, ";
    }
    if(tree1->isEqualWith(tree2)){
        std::cout << "равны, ";
    }else{
        std::cout << "не равны, ";
    }
    if(tree1->isSymmetryWith(tree2)){
        std::cout << "симметричны." << std::endl;
    }else{
        std::cout << "не симметричны." << std::endl;
    }

    return 0;
}
