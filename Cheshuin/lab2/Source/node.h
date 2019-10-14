#ifndef NODE_H
#define NODE_H

#include "data.h"
#include <memory>


class Node
{
public:
    typedef std::shared_ptr<Node> NodeP;
    typedef std::weak_ptr<Node> NodeWP;

    Node() = default;

    void setNext(NodeP node);
    NodeP next();

    void setPrev(NodeP node);
    NodeP prev();

    void setData(Data::DataP data);
    Data::DataP data();
private:
    NodeWP prev_;
    NodeP next_ = nullptr;
    Data::DataP data_ = nullptr;
};

#endif // NODE_H
