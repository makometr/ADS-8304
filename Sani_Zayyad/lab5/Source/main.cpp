#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "avl.hpp"


void ReadFromFile(AVLtree<int> &avlTree, const std::string &filename,const std::string &test);
void insert(AVLtree<int> &avlTree,int const &n);
void deleteKey(AVLtree<int> &avlTree,int const &n);
void utility(AVLtree<int> &avlTree, std::string const &message,int type);


void insert(AVLtree<int> &avlTree,int const &n){
      std::cout << "Inserted Succesfully " << n << std::endl;
      avlTree.insert(n);
}
void deleteKey(AVLtree<int> &avlTree,int const &n){
    bool found;
    avlTree.searchElem(n, avlTree.root,found);
    if(found){
        std::cout<<"Элемент, который вы искали есть в дереве!"<<std::endl;
        std::cout << "Deleted Succesfully " << n << std::endl;
        avlTree.deleteKey(n);
    }else{
        std::cout<<"Простите, но такого элемента нет"<<std::endl;
    }
}

void utility(AVLtree<int> &avlTree, std::string const &message,int type){
    do {
        std::cout<<"\n::::Enter Number to" << message << "Node (or non-number to exit!)::::\n";
        int n;
        std::cin>>n;
        // if the user enters anything that is not integer we break the loop
        if(std::cin.fail()){
            // helps in clearing the error flags which are set when std::cin fails to interpret the input.
            std::cin.clear();
            // helps in clearing the stream of input in the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        };
        
        if(type == 1)
            insert(avlTree, n);
        else
            deleteKey(avlTree, n);
        
        avlTree.printBaracketNotation();
    } while (true);
}

std::vector<int> split(const std::string& line) {
    std::istringstream is(line);
    return std::vector<int>(std::istream_iterator<int>(is), std::istream_iterator<int>());
}

void ReadFromFile(const std::string &initialTree,const std::string &test)
{
    std::ifstream file(initialTree);
    std::ifstream file2(test);
    std::vector<int> deleteTest;
    
    if(file2.is_open()){
        std::string input;
        while (!file2.eof()) input.push_back(file2.get());
         deleteTest = split(input);
    }else{
        std::cout << "Files not opened!"<<"\n";
        return;
    }
    

    if (file.is_open())
    {
        int count = 0;

        while (!file.eof())
        {
            AVLtree<int> avlTree;
            
            std::string input;
            getline(file, input);
            std::cout<< "Your input: "<< input << "\n";
            std::vector<int> treeInput = split(input);
            for(int i : treeInput){
                   avlTree.insert(i);
            }
            avlTree.printBaracketNotation();

            std::cout<< "\n:::Delete "<< deleteTest[count] << " if it exists\n";
            deleteKey(avlTree, deleteTest[count]);
            avlTree.printBaracketNotation();

            std::cout<< "----------------------------------------------\n";

            count++;
        }
    }
    else
        std::cout << "Files not opened!"<<"\n";
}
        

int main()
{
       AVLtree<int> avlTree;
        int command;
        
        do{
            std::cout<<"\n\n\t\t::::AVL TREE APP::::"<<std::endl;
            std::cout<<"::::1 Enter Number to insert Node"<<std::endl;
            std::cout<<"::::2 Delete Number if it exists in tree --(Main Task)"<<std::endl;
            std::cout<<"::::3 Read from File"<<std::endl;
            std::cout<<"::::0 Exit"<<std::endl;

            std::cout<<"\nChoose Option and Click Enter: ";
            std::cin >> command;
            switch(command)
                    {
                        case 1:
                         {
                            std::string  message = " add ";
                            utility(avlTree, message, 1);
                            break;
                         }
                        case 2:
                           {
                                std::string  message = " delete ";
                                utility(avlTree, message, 2);
                                break;
                            }
                        case 3:
                            {
                                std::string filePath ;
                                std::string filePath2;
                                
                                std::cout << "> Tree FilePath: ";
                                std::cin >> filePath;
                                
                                std::cout << "> Test FilePath: ";
                                std::cin >> filePath2;

                                ReadFromFile(filePath,filePath2);
                                break;
                            }
                        default:
                            std::cout<<"Sorry! wrong input"<<std::endl;
                            break;
                    }
            }while(command != 0);

        
        return 0;

}
