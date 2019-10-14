#include "node.h"
#include "list.h"
#include "atom.h"

void Node::setNext(NodeP node)
{
    next_ = node;
}

Node::NodeP Node::next()
{
    return next_;
}

void Node::setPrev(NodeP node)
{
    prev_ = node;
}

Node::NodeP Node::prev()
{
    return Node::NodeP(prev_);
}

void Node::setData(Data::DataP data)
{
    data_ = data;
}

Data::DataP Node::data()
{
    return data_;
}
