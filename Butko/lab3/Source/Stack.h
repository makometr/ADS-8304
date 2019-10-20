#pragma once

class Stack
{
public:
    Stack() : top(nullptr)
    {
    }
    void push(char element)
    {
        auto* tmp = new Node;
        tmp->element = element;
        tmp->prev = top;
        top = tmp;
    }
    bool isEmpty()
    {
        return top == nullptr;
    }
    char pop()
    {
        if (isEmpty()) return 0;
        char element = top->element;
        auto* tmp = top;
        top = top->prev;
        delete tmp;
        return element;
    }
    ~Stack()
    {
        while (top)
        {
            auto* tmp = top;
            top = top->prev;
            delete tmp;
        }
    }
private:
    struct Node
    {
        char element;
        Node* prev;
    };
    Node* top;
};
