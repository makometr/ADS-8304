#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H

#include<memory>
#include"node.h"

template <typename T>
class DynamicStack
{
public:
    typedef std::shared_ptr<DynamicStack> DynamicStackP;

private:
    typename Node<T>::NodeP head_ = nullptr;
    typename Node<T>::NodeP tail_ = nullptr;
    int elementsCount_ = 0;

public:
    DynamicStack() = default;
    DynamicStack(std::initializer_list<T> init);

    void push(T data);
    void push(DynamicStack stack);

    void pushBack(T data);
    void pushBack(DynamicStack stack);

    T pop();
    T onTop();

    size_t size();
    bool isEmpty();
    void clear();
};

template <typename T>
DynamicStack<T>::DynamicStack(std::initializer_list<T> init)
{
    for(auto value = init.begin(); value != init.end(); value++)
    {
        pushBack(*value);
    }
}

template <typename T>
void DynamicStack<T>::push(T data)
{
    typename Node<T>::NodeP newNode(new Node<T>);
    newNode->setData(data);

    if(head_ == nullptr)
    {
        head_ = newNode;
        tail_ = newNode;
    }
    else
    {
        newNode->setNext(head_);
        head_->setPrev(newNode);
        head_ = newNode;
    }

    elementsCount_ += 1;
}

template <typename T>
void DynamicStack<T>::push(DynamicStack stack)
{
    typename Node<T>::NodeP buf = stack.tail_;
    while(buf != nullptr)
    {
        T dataBuf = buf->data();

        push(dataBuf);

        buf = buf->prev();
    }
}

template <typename T>
void DynamicStack<T>::pushBack(T data)
{
    typename Node<T>::NodeP newNode(new Node<T>);
    newNode->setData(data);

    if(head_ == nullptr)
    {
        head_ = newNode;
        tail_ = newNode;
    }
    else
    {
        newNode->setPrev(tail_);
        tail_->setNext(newNode);
        tail_ = newNode;
    }

    elementsCount_ += 1;
}

template <typename T>
void DynamicStack<T>::pushBack(DynamicStack stack)
{
    typename Node<T>::NodeP buf = stack.head_;
    while(buf != nullptr)
    {
        T dataBuf = buf->data();

        pushBack(dataBuf);

        buf = buf->next();
    }
}

template <typename T>
T DynamicStack<T>::pop()
{

    typename Node<T>::NodeP buf  = head_;

    head_ = buf->next();

    buf->setNext(nullptr);

    elementsCount_ -= 1;

    if(head_ == nullptr)
    {
        tail_ = nullptr;
    }

    return buf->data();
}

template <typename T>
T DynamicStack<T>::onTop()
{
    return head_->data();
}

template <typename T>
bool DynamicStack<T>::isEmpty()
{
    return (elementsCount_ == 0);
}

template <typename T>
void DynamicStack<T>::clear()
{
    head_ = nullptr;
    tail_ = nullptr;
    elementsCount_ = 0;
}

template <typename T>
size_t DynamicStack<T>::size()
{
    return elementsCount_;
}

#endif // DYNAMICSTACK_H
