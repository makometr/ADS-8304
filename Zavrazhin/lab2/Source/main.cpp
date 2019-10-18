#include <iostream>
#include <string>

#include "expression.h"

using std::cin;
using std::cout;
using std::endl;

using lab2::Expression;

int main(int argc, char* argv[])
{
    if(argc > 2)
    {
        cout << "Too many command line arguments were provided." << endl;
    }
    
    std::string line;
    if(argc == 2)
    {
            line += std::string(argv[1]);
    }
    else
    {
        cout << "Enter an expression:" << endl;
        std::getline(cin, line);
    }
    
    Expression<double> expression(line);
    cout << expression.represent() << endl;
    if(expression.isCorrect())
    {
        cout << "The given expression \x1b[1mis\x1b[0m correct." << endl;
    }
    else
    {
        cout << "The given expression is \x1b[1mnot\x1b[0m correct." << endl;
        cout << expression.getErrors();
    }
    cout << endl; // so consecutive calls would be distinct
}
