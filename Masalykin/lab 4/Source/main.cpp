#include <iostream>
#include <string>
#include <fstream>
#include "MyBinaryTree.h"

void print_tree(MyBinaryTree<char> tree, std::string space, int index);
void print_LPK(MyBinaryTree<char> tree, int index);
int check_str(std::string str);

int main(int argc, char* argv[]) {
    std::string inp_str;
    if(argc == 1){
        std::cout<<"No input file! Enter your tree with keyboard!"<<std::endl;
        std::cin>>inp_str;
    }else {
        std::ifstream file;
        file.open(argv[1]);
        if (!file.is_open()) {
            std::cout << "Can't open file" << std::endl;
            return 1;
        } else {
            getline(file, inp_str);
        }
    }
    if(!check_str(inp_str)){
        std::cout<<"INCORRECT STRING!!!!!"<<std::endl;
        return 1;
    }
    MyBinaryTree<char> MyTree;
    MyTree.createCharTree(inp_str);
    std::cout<<MyTree.toStdString()<<std::endl;

    std::cout<<"Your tree list form:"<<std::endl;
    std::string space = "\t";
    std::cout<<MyTree.getElem(0)<<std::endl;
    print_tree(MyTree, space, 0);
    std::cout<<"LPK:(";
    print_LPK(MyTree, 0);
    std::cout<<')'<<std::endl;

    return 0;
}

void print_tree(MyBinaryTree<char> MyTree, std::string space, int index){
    if(MyTree.getLeft(index) != -1) {
        std::cout << space << MyTree.getElem(MyTree.getLeft(index)) << std::endl;
        print_tree(MyTree, space + '\t', MyTree.getLeft(index));
    }
    if(MyTree.getRight(index) != -1) {
        std::cout << space << MyTree.getElem(MyTree.getRight(index)) << std::endl;
        print_tree(MyTree, space + '\t', MyTree.getRight(index));
    }
}


void print_LPK(MyBinaryTree<char> tree, int index){
    if(tree.getLeft(index) == -1 && tree.getRight(index) == -1){
        std::cout<<tree.getElem(index);
    }
    else if(tree.getLeft(index) != -1 && tree.getRight(index) == -1){
        std::cout<<'(';
        print_LPK(tree, tree.getLeft(index));
        std::cout<<')';
        std::cout<<tree.getElem(index);
    }
    else if(tree.getLeft(index) == -1 && tree.getRight(index) != -1){
        std::cout<<'(';
        print_LPK(tree, tree.getRight(index));
        std::cout<<')';
        std::cout<<tree.getElem(index);
    }
    else if(tree.getLeft(index) != -1 && tree.getRight(index) != -1){
        std::cout<<'(';
        print_LPK(tree, tree.getLeft(index));
        std::cout<<')';
        std::cout<<'(';
        print_LPK(tree, tree.getRight(index));
        std::cout<<')';
        std::cout<<tree.getElem(index);
    }
}

int check_str(std::string str){
    int br_cntr = 0;
    bool is_br = false;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == '(') {
            br_cntr++;
            is_br = true;
        }
        if(str[i] == ')') {
            br_cntr--;
            is_br = true;
        }
    }
    if(!is_br)
        return 0;
    if (br_cntr)
        return 0;
    else
        return 1;
}
