#include "BinaryTree.h"

int main(int argc, char* argv[]) {
    int index1 = 0,
        index2 = 0,
        testCounter = 0;
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
        while(std::getline(inputFile, str1) && std::getline(inputFile, str2))
        {
            std::cout << std::endl << "Test №" << ++testCounter << std::endl;
            std::cout << "First string:" << std::endl;
            std::cout << str1 << std::endl;
            std::cout << "Second string:" << std::endl;
            std::cout << str2 << std::endl;
            BinaryForest<std::string> forest(str1.size(), str2.size());
            if (forest.makeBinaryForest(str1, str2, index1, index2)){
                forest.printBinaryForest();
                forest.forestComparison();
            }
            index1 = 0;
            index2 = 0;
        }
        return 0;
    }
    BinaryForest<std::string> forest(str1.size(), str2.size());
    if (forest.makeBinaryForest(str1, str2, index1, index2)){
        forest.printBinaryForest();
        forest.forestComparison();
    }
    return 0;
}