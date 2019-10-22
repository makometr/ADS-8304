#ifndef stack_hpp
#define stack_hpp

#include <string>
#include <iostream>

// A stack element consisting of an expression and the priority of that expression.
// check makeInfix function in main.cpp to see the definition of priorities for every operator.
typedef std::pair<std::string, int> Data;

class Stack{
public:
    Stack(size_t max_size);
    
    Stack(const Stack &stack) = delete;
    Stack& operator=(const Stack&) = delete;

    ~Stack();
    
    //methods for working with stack
    void push(const Data elem);
    Data pop();
    Data top() const;
    size_t size() const;
    bool isEmpty() const;

private:
    Data* stackData;
    std::size_t stackSize;
    
};

#endif /* stack_hpp */
