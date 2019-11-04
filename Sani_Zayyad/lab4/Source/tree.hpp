
#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include <memory>
#include <iostream>


struct Node
{
    Node() :data(int()),left(nullptr), right(nullptr){}
    
    int data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

class MyBinaryTree
{
public:
    explicit MyBinaryTree();
    ~MyBinaryTree() = default;
    
    std::shared_ptr<Node> rootPointer;
    
    bool startTree(std::string const& inputString);
    bool construcTree(std::string const& inputString,std::shared_ptr<Node>& rootPointer);
    std::string subString(std::string const& indexString, size_t* stringIndexPointer);
    bool isCorrectStr(std::string const& str);
    bool isBalanceBracket(std::string const& str);


};


#endif /* tree_hpp */
