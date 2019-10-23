#include "stack.hpp"

Stack::Stack()
{
    defaultSize = 5;
    stackSize = 0;
    stackData = new Data[defaultSize];
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

Data* Stack::resize(Data*& stackdata, size_t defaultsize, size_t new_size){
    Data* new_stackData = new Data[new_size];
    
    for (size_t i = 0; i < defaultsize; i++)
        new_stackData[i] = stackData[i];
    delete[] stackdata;
//    std::cout<<"resizing.....\n";
    
    return new_stackData;
}

//adding element in stack
void Stack::push(const Data elem)
{
    stackSize++;
    if (stackSize >= defaultSize) {
        size_t increment = 5;
        stackData = resize(stackData, defaultSize, defaultSize + increment);
        defaultSize += increment;
    }
    stackData[stackSize - 1] = elem;
    
}
