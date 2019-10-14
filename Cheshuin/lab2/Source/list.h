#ifndef LIST_H
#define LIST_H

#include <memory>
#include "data.h"
#include "node.h"
#include "atom.h"

class List: public Data
{
private:
    Node::NodeP head_  = nullptr;
    Node::NodeP tail_  = nullptr;
public:
    typedef std::shared_ptr<List> ListP;

    List();

    void pushBack(Data::DataP data);
    Data::DataP pullHead();
    bool isEmpty();

    Node::NodeP begin();
    Node::NodeP end();

    std::string toString();
};

#endif // LIST_H
