#include <iostream>
#include <string>

#include "expression.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    std::string line;
    if(argc >= 2)
    {
        for(int i = 1; i < argc; i++)
            line += std::string(argv[i]) + " ";
    }
    else
    {
        cout << "Enter an expression:" << endl;
        cin >> line;
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
    cout << endl;
}
