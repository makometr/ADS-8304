#include "stack.h"

Stack::Stack()
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


Data Stack::pop()
{
    if (!isEmpty()){
        Data elem = stack. back();
        stack.pop_back();
        sizeStack -= 1;
        return elem;
    }
    else {
        qDebug() << "Error. Stack is empty";
        return Data("", optype::null);
    }
}


void Stack::push(const Data elem)
{
    stack.push_back(elem);
    sizeStack += 1;
}
