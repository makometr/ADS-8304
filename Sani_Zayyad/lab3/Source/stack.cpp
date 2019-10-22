#include "stack.hpp"

Stack::Stack(size_t maxSize)
{
    stackData = new Data[maxSize];
    stackSize = 0;
}

Stack::~Stack()
{
     delete [] stackData;
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
        return stackData[stackSize -1];
    }
    else {
        std::cout << "Error. Stack is empty";
        return Data("", 0);
    }
}

// removing or popping the top element in stack
Data Stack::pop()
{
    if (!isEmpty()){
         Data elem = stackData[--stackSize];
        return elem;
    }
    else {
        std::cout << "Error. Stack is empty";
        return Data("",0);
    }
   
}

//adding element in stack
void Stack::push(const Data elem)
{
    stackData[stackSize] = elem;
    stackSize++;
}
