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
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
    
    Expression<double> expression(line);
    if(DEBUG)
        cout << expression.represent() << endl;
    if(expression.isCorrect())
    {
        cout << "\"" << line << "\"" << endl;
        cout << "The given expression \x1b[1mis\x1b[0m correct." << endl;
    }
    else
    {
        cout << "\"" << line << "\"" << endl;
        cout << "The given expression is \x1b[1mnot\x1b[0m correct." << endl;
        cout << expression.getErrors();
    }
}
