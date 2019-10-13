#ifndef LIST_H
#define LIST_H

#include "data.h"
#include "node.h"
#include "atom.h"

class List: public Data
{
private:
    Node* head_  = nullptr;
    Node* tail_  = nullptr;
public:
    List();

    void pushBack(Data* data);
    void pushBack(List* list);
    void pushBack(Atom* atom);
    Data* pullHead();
    bool isEmpty();

    Node* begin();
    Node* end();

    std::string toString();
};

#endif // LIST_H
