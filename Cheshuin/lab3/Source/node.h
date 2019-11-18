#ifndef NODE_H
#define NODE_H

#include<memory>

template <typename T>
class Node
{
public:
    typedef std::shared_ptr<Node> NodeP;
    typedef std::weak_ptr<Node> NodeWP;
private:
    T data_;
    NodeWP prev_;
    NodeP next_ = nullptr;
public:
    Node() = default;

    void setData(T data);
    T data() const;

    void setPrev(NodeP node);
    NodeP prev();

    void setNext(NodeP node);
    NodeP next();
};

template<typename T>
void Node<T>::setData(T data)
{
    data_ = data;
}

template<typename T>
T Node<T>::data() const
{
    return data_;
}

template<typename T>
void Node<T>::setPrev(NodeP node)
{
    prev_ = node;
}

template<typename T>
typename Node<T>::NodeP Node<T>::prev()
{
    if(prev_.expired())
    {
        return nullptr;
    }
    else
    {
        return NodeP(prev_);
    }
}

template<typename T>
void Node<T>::setNext(NodeP node)
{
    next_ = node;
}

template<typename T>
typename Node<T>::NodeP Node<T>::next()
{
    return next_;
}

#endif // NODE_H
