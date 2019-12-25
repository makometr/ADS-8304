#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "avl.hpp"

int chooseType();
void fromRandom(const int &level,std::ofstream &output);
void fromFile(const std::string &filePath, std::ofstream &output);
void utilityAddRemove(AVLtree &avlTree, std::ofstream &output, std::vector<int> const& vec, int const& type);
void makeAVL(AVLtree &avlTree, std::istream &file, std::ofstream &output, int const& type);


int chooseType() {
    std::cout << "Choose the difficulty\n";
    std::cout << "1: Easy -  to insert 5 elements and remove 1 \n";
    std::cout << "2: Medium - to insert 10 element and remove 3\n";
    std::cout << "3: Hard - to insert 15 element and remove 5\n";
    int type;
    std::cin >> type;

    if ((type < 1) || (type > 3)) {
        std::cout << "You entered incorrect type\n";
        return 0;
    }
    return type;
}

void fromRandom(const int &level, std::ofstream &output){
    int array_insert_size;
    int array_delete_size;
    
    if(level == 1){
        array_insert_size = 5;
        array_delete_size = 1;
    }else if(level == 2){
        array_insert_size = 10;
        array_delete_size = 3;
    }else{
        array_insert_size = 15;
        array_delete_size = 5;
    }
    srand((unsigned)time(NULL));
    
    for (int i = 0; i < 5; i++){
        AVLtree avlTree;
        std::vector<int> inputElem;
        std::vector<int> deleteElem;
        for (int i = 0; i < array_insert_size; i++){
                int elem = rand() % 100 + 1;
                inputElem.push_back(elem);
        }
        for (int i = 0; i < array_delete_size; i++){
                int elem = rand() % array_insert_size;
                deleteElem.push_back(inputElem.at(elem));
        }
        std::cout << "-----Test " << i + 1 << "-----\n";
        output << "-----Test " << i + 1 << "-----\n";
        utilityAddRemove(avlTree, output, inputElem, 1);
        utilityAddRemove(avlTree, output, deleteElem, 2);
        std::cout <<"----------------------------------------------------------------\n";
        output <<"----------------------------------------------------------------\n";
        avlTree.deleteTree(avlTree.root);
    }
    
}

void fromFile(const std::string &filePath, std::ofstream &output){
    std::ifstream file(filePath);

    if (file.is_open()) {
        std::cout << "Reading from file:" << "\n";

        int count = 1;

        while (!file.eof()) {
               std::cout << "-----Test " << count << "-----\n";
               output << "-----Test " << count << "-----\n";
               AVLtree avlTree;
               makeAVL(avlTree,file,output,3);
               count++;
               std::cout <<"----------------------------------------------------------------\n";
               output <<"----------------------------------------------------------------\n";
        }
    } else  std::cout << "File not opened";

}

void utilityAddRemove(AVLtree &avlTree, std::ofstream &output, std::vector<int> const& vec, int const& type){
    if(type == 1){
         std::cout<<":Insert: ";
         output<<":Insert: ";
         for (auto i = vec.begin(); i != vec.end(); ++i){
             avlTree.root =  avlTree.insert(avlTree.root, *i);
             std::cout<< *i << " ";
             output<< *i << " ";

         }
    }else{
        std::cout<<"\n:Delete: ";
        output<<"\n:Delete: ";
        for (auto i = vec.begin(); i != vec.end(); ++i){
            avlTree.root =  avlTree.remove(avlTree.root, *i);
            std::cout<< *i << " ";
            output<< *i << " ";
        }
    }
    avlTree.printBaracketNotation(output);
}

void makeAVL(AVLtree &avlTree, std::istream &file, std::ofstream &output, int const& type){
    int array_insert_size;
    int array_delete_size;
    std::vector<int> inputElem;
    std::vector<int> deleteElem;

    if(type == 1){
        int difficulty = chooseType();
        if(difficulty != 0)
            fromRandom(difficulty,output);
        
    }else if (type == 2){
        std::cout<< "How many element to insert ? : ";
        std::cin >> array_insert_size;
        for (int i = 0; i < array_insert_size; ++i) {
            int elem;
            std::cin >> elem;
            inputElem.push_back(elem);
        }
        std::cout<< "How many element to delete ? : ";
        std::cin >> array_delete_size;
        
        for (int i = 0; i < array_delete_size; ++i) {
            int elem;
            std::cin >> elem;
            deleteElem.push_back(elem);
        }
        
    }else{
           file >> array_insert_size;
           for (int i = 0; i < array_insert_size; ++i) {
               int elem;
               file >> elem;
               inputElem.push_back(elem);
           }

           file >> array_delete_size;
           for (int i = 0; i < array_delete_size; ++i) {
               int elem;
               file >> elem;
               deleteElem.push_back(elem);
           }
    }
   
    if(type!=1){
        utilityAddRemove(avlTree, output, inputElem, 1);
        utilityAddRemove(avlTree, output, deleteElem, 2);
        avlTree.deleteTree(avlTree.root);
    }
}

int main(){
    int command;
    std::string ouputfile;
    std::cout << "> Test FilePath: ";
    std::cin >> ouputfile;
//    ouputfile = "/Users/sanizayyad/Documents/Sani_Zayyad/CourseWork/Test/output.txt";
    std::ofstream output(ouputfile, std::ios_base::app);

    do{
        std::cout<<"\n\n\t\t::::AVL TREE APP::::"<<std::endl;
        std::cout<<"::::1 Generate AVL from Random Numbers"<<std::endl;
        std::cout<<"::::2 AVL from User"<<std::endl;
        std::cout<<"::::3 AVL from Test File "<<std::endl;
        std::cout<<"::::0 Exit"<<std::endl;

        std::cout<<"\nChoose Option and Click Enter: ";
        std::cin >> command;
        AVLtree avlTree;
        
        switch(command)
                {
                    case 0:
                        break;
                    case 1:
                           makeAVL(avlTree, std::cin,output, 1);
                           break;
                    case 2:
                           makeAVL(avlTree, std::cin,output, 2);
                            break;
                    case 3:
                        {
                            std::string filePath ;
                            std::cout << "> Test FilePath: ";
                            std::cin >> filePath;
//                            filePath = "/Users/sanizayyad/Documents/Sani_Zayyad/CourseWork/Test/test.txt";
                            fromFile(filePath,output);
                            break;
                        }
                    default:
                        std::cout<<"Sorry! wrong input"<<std::endl;
                        break;
                }
        }while(command != 0);


    return 0;
}
