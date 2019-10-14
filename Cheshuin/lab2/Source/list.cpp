#include "list.h"

List::List()
{
    this->setDataType(DataType::LIST);
}

void List::pushBack(Data::DataP data)
{
    Node::NodeP newNode(new Node);
    newNode->setData(data);

    if(head_ == nullptr)
    {
        head_ = newNode;
        tail_ = newNode;
    }
    else
    {
        tail_->setNext(newNode);
        newNode->setPrev(tail_);
        tail_ = newNode;
    }
}

Node::NodeP List::begin()
{
    return head_;
}

Node::NodeP List::end()
{
    return tail_;
}

std::string List::toString()
{
    std::string outString;
    Node::NodeP curNode = head_;
    List::ListP curList = nullptr;
    Atom::AtomP curAtom = nullptr;

    if(isEmpty())
    {
        return "empty expr";
    }

    while(curNode != nullptr)
    {
        if(curNode->data()->dataType() == DataType::ATOM)
        {
            curAtom = std::static_pointer_cast<Atom>(curNode->data());
            outString += curAtom->value();
        }
        else if(curNode->data()->dataType() == DataType::LIST)
        {
            curList = std::static_pointer_cast<List>(curNode->data());
            outString += '(' + curList->toString() + ')';
        }

        if(curNode->next() != nullptr)
        {
            outString += " ";
        }

        curNode = curNode->next();
    }

    return outString;
}

Data::DataP List::pullHead()
{
    DataP data = head_->data();
    Node::NodeP buf = head_->next();

    head_->setData(nullptr);

    head_ = buf;

    return data;
}

bool List::isEmpty()
{
    return head_ == nullptr;
}
