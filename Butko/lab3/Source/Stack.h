#pragma once


class Stack
{
public:
    Stack():top(nullptr) {}
    void push(char element)
    {
        auto* tmp = new node_;
        tmp->element_ = element;
        tmp->prev_ = top;
        top = tmp;
    }
    bool isEmpty()
    {
        return top == nullptr;
    }
    char pop()
    {
        if (isEmpty()) return  -1;
        char element = top->element_;
        auto* tmp = top;
        top = top->prev_;
        delete tmp;
        return element;
    }
    ~Stack()
    {
        while (top)
        {
            auto* tmp = top;
            top = top->prev_;
            delete tmp;
        }
    }

private:
    struct node_
    {
        char element_;
        node_* prev_;
    };
    node_* top;
};
