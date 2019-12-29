#include <iostream>
#include <fstream>
#include "lab3.hpp"

int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2], std::ios::app);
    unsigned int max_len = 0;
    int count_string = 0;
    std::string current_line;
    while (getline(in, current_line)) {
        count_string++;
        if (current_line.length() > max_len)
            max_len = current_line.length();
    }
    in.clear();
    in.seekg(0, std::ios::beg);
    char current_elem = '1';
    for (int i = 0; i < count_string; i++) {
        Stack<char> stack(max_len);
        in.get(current_elem);
        if (current_elem != EOF) {
            Reverse(stack, in, out, current_elem);
            out.put('\n');
        }
    }
    in.close();
    out.close();
    return 0;
}
