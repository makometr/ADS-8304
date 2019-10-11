#include "hierachy.h"
#include <iostream>
#include <unordered_set>
#include <list>
#include <fstream>

void toSet(std::unordered_set<char>& set, const HierarchicalList::ListPointer list);
void ReadFromFile(std::string filename);
void execute(std::string listStr);



void toSet(std::unordered_set<char>& set, const HierarchicalList::ListPointer list) {
    if (list != nullptr && !list->isNull()) {
        if (list->isAtom()) {
            set.insert(list->getAtom());
        }
        else {
            toSet(set, list->getNested());
            toSet(set, list->getNext());
        }
    }
}


void ReadFromFile(std::string filename)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::cout << "Reading from file:"<< "\n\n";
        int count = 0;
        while (!file.eof())
        {
            count++;
            std::string listStr;
            getline(file, listStr);
            std::cout << "test #" << count << " \"" + listStr + "\""<< "\n";
            execute(listStr);
        }
    }
    else
    {
        std::cout << "File not opened"<<"\n";
    }
}

void execute(std::string listStr){
    HierarchicalList::ListPointer list(new HierarchicalList);
    std::unordered_set<char> set;
    
    if (HierarchicalList::buildList(list, listStr)) {
        toSet(set, list);
        std::cout << "Число различных элементов в списке: " << set.size() << "\n";

        std::list<char> result;
        for (auto elem : set)
            result.push_front(elem);

        std::string resultStr;
        for (auto elem : result)
            resultStr += elem;
        std::cout << "Линейный список: (" << resultStr << ")\n\n";
    }

}



int main()
{
    std::cout << "> Choose your input" << "\n";
    std::cout << "> 0 - from console" << "\n";
    std::cout << "> 1 - from file default file -(default test file is located along the path : test2.txt)" << "\n";
    std::cout << "> Any other number to Exit!" <<"\n";

    int command = 0;
    std::cin >> command;

    switch (command)
    {
        case 0:
        {
        std::string input;
        std::cout << "> Enter List: ";
        std::cin>>input;
        execute(input);
        break;
        }
    case 1:
        {
        std::cout << "> FilePath: ";
        std::string filePath;
        std::cin >> filePath;
        ReadFromFile(filePath);
        break;
            
        }
    default:
        std::cout << "GOODBYE!";
    }
    return 0;
}
