#include "lab3.h"
#include <iostream>
#include <fstream>

template <class type>
Stack<type>::Stack(size_t max_size) {
    st = new type[max_size + 2];
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
void Reverse(Stack<type>& stack, std::ifstream& in, std::ofstream& out, char& s) {
    if (s != EOF) {
        if (s != '\n') {
            stack.push(s);
            in.get(s);
            if (!in.eof())
                Reverse(stack, in, out, s);
        }
        if (!stack.isEmpty()) {
            out.put(stack.pop());
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2], std::ios::app);
    int maxLen = 0;
    int countString = 0;
    std::string currentLine;
    while (getline(in, currentLine)) {
        countString++;
        if (currentLine.length() > maxLen)
            maxLen = currentLine.length();
    }
    in.clear();
    in.seekg(0, std::ios::beg);
    char s;
    for (int i = 0; i < countString; i++) {
        Stack<char> stack(maxLen);
        in.get(s);
        if (s != EOF) {
            Reverse(stack, in, out, s);
            out.put('\n');
        }
    }
    in.close();
    out.close();
    return 0;
}
