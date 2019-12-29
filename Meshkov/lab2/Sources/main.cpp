#include <iostream>
#include "expression.h"

int main() {
    Expression expr;

    std::string exprStr;
    std::cout << "Enter expression: ";
    getline(std::cin, exprStr);

    std::string::size_type after;
    expr.load(exprStr, &after);
    if (!expr.isEmpty()) {
        if (after != exprStr.length())
            std::cerr << "Warning: Extra characters at the end of the expression." << std::endl;

        std::string variable;
        std::cout << "Enter target variable: ";
        std::cin >> variable;

        try {
            expr.derive(variable);
            std::cout << "Derived: " << expr.toString() << std::endl;
        } catch (Expression::ComplexPowerException &) {
            std::cerr << "Error: Unsupported expression: Complex power." << std::endl;
        }
    } else {
        std::cerr << "Error: Wrong expression." << std::endl;
    }

    return 0;
}

