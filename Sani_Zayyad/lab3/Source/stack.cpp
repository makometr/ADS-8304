#include "stack.hpp"

Stack::Stack()
{
    stackSize = 0;
}

//getting size of stack
size_t Stack::size() const
{
    return stackSize;
}

//checking if the stack is empty
bool Stack::isEmpty() const
{
    return size() == 0;
}

//getting the top element of the stack
Data Stack::top() const
{
    if (!isEmpty()) {
        return stackData.back();
    }
    else {
        std::cout << "Error. Stack is empty";
        return Data("", 0);
    }
}

// removing or popping the top element in stack
void Stack::pop()
{
    if (!isEmpty()){
        stackData.pop_back();
        stackSize -= 1;
    }
    else {
        std::cout << "Error. Stack is empty";
    }
}

//adding element in stack
void Stack::push(const Data elem)
{
    stackData.push_back(elem);
    stackSize += 1;
}
