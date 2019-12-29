#include "hierarchicallist.h"
#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char *argv[]) {
    std::string listStr;
    int choice;
    HierarchicalList::ListPointer list(new HierarchicalList);
    char oldElem, newElem, testnum;

    while (true) {
        std::cout << "What type of test?" << std::endl;
        std::cout << "1.FROM FILE" << std::endl;
        std::cout << "2.FROM CONSOLE" << std::endl;
        std::cin >> choice;
        
          switch (choice){
              case 1:{
                  std::cout << " FROM FILE " << std::endl;
                  std::cout << "Number of test?\n";
                  std::cin >> testnum;
                  std::string FileName = "./Tests/test";
                  FileName += testnum;
                  FileName += ".txt";
                  std::ifstream inputFile(FileName, std::ios::in);
                  if(inputFile.is_open()){
                  inputFile >> listStr >> oldElem >> newElem;
                  std::cout << "oldElement:" << oldElem << "\nnewElement:" << newElem << "\n";
                  HierarchicalList::buildList(list, listStr);

   
                      if (oldElem != newElem) {
                        HierarchicalList::swapElements(list, oldElem, newElem);
                        std::cout << "List after swap:" << list << "\n";
                      }
                      else {
                        std::cout << "Elements are equal. List hadn't changed\n";
                      }
                  }
                  inputFile.close();
                  break;
              }
                  
            case 2:
              std::cout << "Enter list: ";
              std::cin >> listStr;
              std::cout << "List : " << listStr << "\n";


              if (HierarchicalList::buildList(list, listStr)) {

                std::cout << "Enter old element:";
                std::cin >> oldElem;

                std::cout << "Enter new element:";
                std::cin >> newElem;


              if (oldElem != newElem) {
                HierarchicalList::swapElements(list, oldElem, newElem);
                std::cout << "List after swap:" << list << "\n";
              }
              else {
                std::cout << "Elements are equal. List hadn't changed\n";
              }
          
        }
              default:
                  break;
       
      }
        
    }
    return 0;
}

