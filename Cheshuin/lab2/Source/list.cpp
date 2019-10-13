#include "list.h"

List::List()
{
    this->setDataType(DataType::LIST);
}

void List::pushBack(Data* data)
{
    if(data->dataType() == DataType::LIST)
    {
        List* list = static_cast<List*>(data);
        pushBack(list);
    }
    else if(data->dataType() == DataType::ATOM)
    {
        Atom* atom = static_cast<Atom*>(data);
        pushBack(atom);
    }
}

void List::pushBack(List* list)
{
    Node* newNode = new Node();
    newNode->setData(list);

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

void List::pushBack(Atom *atom)
{
    Node* newNode = new Node();
    newNode->setData(atom);

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

Node* List::begin()
{
    return head_;
}

Node* List::end()
{
    return tail_;
}

std::string List::toString()
{
    std::string outString;
    Node* curNode = head_;
    List* curList = nullptr;
    Atom* curAtom = nullptr;

    if(isEmpty())
    {
        return "empty expr";
    }

    while(curNode != nullptr)
    {
        if(curNode->data()->dataType() == DataType::ATOM)
        {
            curAtom = static_cast<Atom*>(curNode->data());
            outString += *(curAtom->value());
        }
        else if(curNode->data()->dataType() == DataType::LIST)
        {
            curList = static_cast<List*>(curNode->data());
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

Data* List::pullHead()
{
    Data* data = head_->data();
    Node* buf = head_->next();

    head_->setData(nullptr);
    delete  head_;
    head_ = buf;

    return data;
}

bool List::isEmpty()
{
    return head_ == nullptr;
}
