#ifndef stack_hpp
#define stack_hpp

#include <string>
#include <iostream>

// A stack element consisting of an expression and the priority of that expression.
// check makeInfix function in main.cpp to see the definition of priorities for every operator.
typedef std::pair<std::string, int> Data;

class Stack{
public:
    Stack();
    
    Stack(const Stack &stack) = delete;
    Stack& operator=(const Stack&) = delete;

    ~Stack();
    
    //methods for working with stack
    void push(const Data elem);
    Data pop();
    Data top() const;
    size_t size() const;
    bool isEmpty() const;
    Data* resize(Data*& stackdata, size_t defaultsize, size_t new_size);
    
private:
    Data* stackData;
    size_t stackSize;
    size_t defaultSize;
    
};

#endif /* stack_hpp */
