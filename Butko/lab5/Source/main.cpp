#include <iostream>
#include <fstream>
#include <string>

#include "RBST.h"

int readFromFile(const std::string& str)
{
    std::string str1;
    int element;
    std::cout << "For file: " << str << std::endl;
    std::ifstream inputFile(str);
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
    RandomBinarySearchTree<int> Tree;
    while (inputFile >> element)
        Tree.searchAndInsertElement(element);
    std::cout << "Do you want to add some elements? (y/n)" << std::endl;
    while(getchar() != 'n')
    {
        std::cout << "Input element:" << std::endl;
        std::cin >> element;
        Tree.searchAndInsertElement(element);
        getchar();
        std::cout << "Do you want to add some elements? (y/n)" << std::endl;
    }
    Tree.printTree(0);
    inputFile.close();
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::string str;
        std::cout << "Input file path:" << std::endl;
        std::getline(std::cin, str);
        readFromFile(str);
    }
    else readFromFile(argv[1]);
    return 0;
}