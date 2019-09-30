#include <fstream>
#include "iostream"
#include "lab2.h"

int main(int argc, char* argv[]) {
    std::stringstream str;
    str << argv[1];
    lisp lst = new s_expr;
    read_lisp(lst, str);
    std::cout << str.str();
    if (argv[1][0] == '(')
        std::cout << std::endl << "dip: " << dip(lst) << std::endl << std::endl;
    else
        std::cout << std::endl << "Неверный синтаксис, список должен начинаться с открывающей скобки!" << std::endl << std::endl;
    destroy(lst);
    return 0;
}