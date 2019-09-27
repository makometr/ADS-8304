#include <fstream>
#include "iostream"
#include "lab2.h"

static std::ifstream in("/home/mukhamux/CLionProjects/algoritms/lab2/tests.txt");
int main(int argc, char* argv[]) {
    std::stringstream str;
    str << argv[1];
    lisp lst = new s_expr;
    read_lisp(lst, str);
    std::cout << str.str();
    std::cout << " dip: " << dip(lst) << std::endl;
    destroy(lst);
    return 0;
}