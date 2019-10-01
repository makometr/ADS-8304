#include "Stack.h"

#include <iostream>
#include <fstream>

void reverseFunction(std::ifstream& file, std::ofstream& newFile, Stack& aStack)
{
    std::string line;
    while (getline(file, line))
    {
        aStack.push('\n');
        for (char i : line)
            aStack.push(i);
        while (!aStack.isEmpty())
            newFile << aStack.pop();
        aStack.pop();
    }
}

int main()
{
    Stack aStack;
    std::string fileName, newFileName;
    std::cout << "Enter test-file location:" << std::endl;
    std::cin >> fileName;
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        std::cout << "error: file is not open" << std::endl;
        return 0;
    }
    std::cout << "Enter where to save results (location with <name>.txt): " << std::endl;
    std::cin >> newFileName;
    std::ofstream newFile(newFileName);
    if (!newFile.is_open())
    {
        std::cout << "error: file is not open" << std::endl;
        return 0;
    }
    reverseFunction(file, newFile, aStack);
    return 0;
}