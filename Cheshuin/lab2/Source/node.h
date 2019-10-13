#ifndef NODE_H
#define NODE_H

#include "data.h"

class Node
{
private:
    Node* prev_ = nullptr;
    Node* next_ = nullptr;
    Data* data_ = nullptr;
public:
    Node() = default;

    void setNext(Node* node);
    Node* next();

    void setPrev(Node* node);
    Node* prev();

    void setData(Data* data);
    Data* data();
};

#endif // NODE_H
