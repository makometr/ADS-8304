#include <iostream>
#include <fstream>
#include "MyList.h"

void create_new_list(MyList::MyListP inp_list, std::list<char>* new_list, int depth);
void print_list(std::list<char> list);

int main(int argc, char* argv[]) {
    std::string inpStr;
    if(argc == 1){
    	std::cout<<"Enter a hierarchical list: ";
    	std::cin>>inpStr;
    }
    else{
	std::string fileName = argv[1];
        //result += "Read text from file " + fileName + "\n";

        std::ifstream inputFile(fileName, std::ios::in);
        //inpStr = readText(inputFile);
	getline(inputFile, inpStr);
        inputFile.close();
	}

    //создание спискa, проверка на корректность
    MyList::MyListP List(new MyList);

    if (MyList::buildList(List, inpStr)) {
        std::cout << "The line is correct, the hierarchical list is created"<<std::endl;
    }
    else {
        std::cout<< "The string is incorrect!"<<std::endl;
        std::cerr<<"The input is not correct."<<std::endl;
        return 0;
    }

    std::cout<< "__ Read list__:"<<std::endl;
    std::cout << "List: " << List<<std::endl;
    std::list<char> new_list;
    new_list = {};
    create_new_list(List, &new_list, 0);
    std::cout<<"New list: ";
    print_list(new_list);
    return 0;
}

void create_new_list(MyList::MyListP inp_list, std::list<char>* new_list, int depth){
    depth++;
    if(inp_list->isNull())
        return;
    while(!inp_list->isNull()){
        if(inp_list->getHead()->getIsAtom()){
            new_list->push_back(inp_list->getHead()->getAtom());
            inp_list = inp_list->getTail();
        }
        else {
            create_new_list(inp_list->getHead(), new_list, depth);
            inp_list = inp_list->getTail();
        }
    }
}

void print_list(std::list<char> list){
    /*auto begin = list.begin();
    auto end = list.end();*/
    std::cout<<"(";
    for(auto i = list.begin(); i != list.end(); i++){
        std::cout <<*i;
    }
    std::cout <<")"<<std::endl;
}
