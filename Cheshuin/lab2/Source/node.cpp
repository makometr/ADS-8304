#include "node.h"
#include "list.h"
#include "atom.h"

void Node::setNext(Node* node)
{
    next_ = node;
}

Node* Node::next()
{
    return next_;
}

void Node::setPrev(Node* node)
{
    prev_ = node;
}

Node* Node::prev()
{
    return prev_;
}

void Node::setData(Data* data)
{
    data_ = data;
}

Data* Node::data()
{
    return data_;
}
