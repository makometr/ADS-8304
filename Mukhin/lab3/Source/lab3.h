#ifndef LAB3
#define LAB3
#include <cstdlib>
template <class type>
class Stack{
    private:
        type* st;
        size_t len;
    public:
        Stack(size_t max_size);
        ~Stack();
        void push(type elem);
        type pop();
        bool isEmpty();
};
#endif
