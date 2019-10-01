#include <fstream>
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

template <class type>
Stack<type>::Stack(size_t max_size) {
    const int spare_memory = 2;
    st = new type[max_size + spare_memory];
    len = 0;
}

template <class type>
Stack<type>::~Stack() {
    delete [] st;
    st = nullptr;
}

template <class type>
void Stack<type>::push(type elem) {
    st[len] = elem;
    len++;
}

template <class type>
type Stack<type>::pop() {
    return st[--len];
}

template <class type>
bool Stack<type>::isEmpty() {
    return len == 0;
}

template <class type>
void Reverse(Stack<type>& stack, std::ifstream& in, std::ofstream& out, char& current_elem) {
    if (current_elem != EOF) {
        if (current_elem != '\n') {
            stack.push(current_elem);
            in.get(current_elem);
            if (!in.eof())
                Reverse(stack, in, out, current_elem);
        }
        if (!stack.isEmpty()) {
            out.put(stack.pop());
            return;
        }
    }
}
