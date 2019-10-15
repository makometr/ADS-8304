#include "stack.h"

Stack::Stack(QObject *parent) : QObject(parent)
{
    sizeStack = 0;
}


size_t Stack::size() const
{
    return sizeStack;
}


bool Stack::isEmpty() const
{
    return size() == 0;
}


Data Stack::top() const
{
    if (!isEmpty()) {
        return stack.back();
    }
    else {
        qDebug() << "Error. Stack is empty";
        return Data("", optype::null);
    }
}


void Stack::pop()
{
    if (!isEmpty()){
        stack.pop_back();
        sizeStack -= 1;
    }
    else {
        qDebug() << "Error. Stack is empty";
    }
}


void Stack::push(const Data elem)
{
    stack.push_back(elem);
    sizeStack += 1;
}
