#include <iostream>
#include "tree.hpp"
#include <stdio.h>
#include <fstream>

void defineTree(const std::string &input);
void ReadFromFile(const std::string &filename);
bool isPyramid(std::shared_ptr<Node> root);

void ReadFromFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        int count = 0;
        while (!file.eof())
        {
            count++;
            std::string input;
            getline(file, input);
            std::cout << "test #" << count << " \"" + input + "\""<< "\n";
            defineTree(input);
        }
    }
    else
    {
        std::cout << "File not opened!"<<"\n";
    }
}

bool isBST(std::shared_ptr<Node> root, std::shared_ptr<Node> l=nullptr, std::shared_ptr<Node> r=nullptr)
{
    // Base condition
    if (root == nullptr)
        return true;
  
    // if left node exist then check it has
    // correct data or not i.e. left node's data
    // should be less than root's data
    if (l != nullptr && root->data <= l->data)
        return false;
  
    // if right node exist then check it has
    // correct data or not i.e. right node's data
    // should be greater than root's data
    if (r != nullptr && root->data >= r->data)
        return false;
  
    // check recursively for every node.
    return isBST(root->left, l, root) && isBST(root->right, root, r);
}

bool isPyramid(std::shared_ptr<Node> root) 
{
    /* left_data is left child data and
       right_data is for right child data*/
    int left_data = 0, right_data = 0;
      
    /* If node is NULL or it's a leaf node
    then return true */
    if(root == nullptr || (root->left == nullptr && root->right == nullptr))
        return true;
    else
    {
        /* If left child is not present then 0
        is used as data of left child */
        if(root->left != nullptr)
            left_data = root->left->data;
      
        /* If right child is not present then 0
        is used as data of right child */
        if(root->right != nullptr)
            right_data = root->right->data;
      
        /* if the node and both of its children
        satisfy the pyramid return true else false*/
        int childrenMax = left_data > right_data ? left_data : right_data;
        if((root->data > childrenMax) && isPyramid(root->left) && isPyramid(root->right))
            return true;
        else
            return false;
    }
}
  

void defineTree(const std::string &input){
    MyBinaryTree tree;
    
    if(tree.startTree(input)){
        std::cout<<"String is correct :)\n";
        if (isBST(tree.rootPointer))
               std::cout << "-->This is a Binary Search Tree"<<"\n\n";

           else if(isPyramid(tree.rootPointer))
               std::cout << "-->This is Pyramid"<<"\n\n";
           
           else
               std::cout << "-->None of the above :(\n"<<"\n\n";
    }else{
        std::cout<<"FIX! the above errors and run again!\n\n";
    }
}

int main() {
    std::cout << "> Choose your input option" << "\n";
    std::cout << "> 0 - from console" << "\n";
    std::cout << "> 1 - from file default file -(default test file is located along the path : test4.txt)" << "\n";
    std::cout << "> Any other number to Exit!" <<"\n";

    int command = 0;
    std::cin >> command;
    std::cin.ignore();

    switch (command)
    {
        case 0:
        {
            std::cout << "> Enter binary tree: ";
            std::string input;
            std::getline(std::cin, input);
            defineTree(input);
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
            std::cout << "GOODBYE!\n";
    }
    
    return 0;
}
