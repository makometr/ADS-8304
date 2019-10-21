#ifndef stack_hpp
#define stack_hpp

#include <vector>
#include <string>
//#include <memory>
#include <iostream>

// A stack element consisting of an expression and the priority of that expression.
// check makeInfix function in main.cpp to see the definition of priorities for every operator.
typedef std::pair<std::string, int> Data;

class Stack{
public:
    explicit Stack();
    ~Stack() =  default;
    
    //methods for working with stack
    void push(const Data elem);
    void pop();
    Data top() const;
    size_t size() const;
    bool isEmpty() const;

private:
    std::vector <Data> stackData;
    std::size_t stackSize;
    
};

#endif /* stack_hpp */
