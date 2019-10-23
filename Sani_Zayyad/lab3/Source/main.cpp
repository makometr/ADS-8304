#include "stack.hpp"
#include <iostream>
#include <fstream>
#include <string>

void ReadFromFile(const std::string &filename);
std::string getInfix(const std::string &input);
Data makeInfix(const char &sign, const Data &firstArg, const Data &secondArg);
bool isAlpha(const char ch);
bool isDigit(const char ch);
bool isOperator(const char ch);


void ReadFromFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        int count = 0;
        while (!file.eof())
        {
            count++;
            std::string input;
            getline(file, input);
            std::cout << "test #" << count << " \"" + input + "\""<< "\n";
            std::string output = getInfix(input);
            std::cout<< "---->  FINAL EXPRESSION : "<< output <<"\n\n";
        }
    }
    else
    {
        std::cout << "File not opened"<<"\n";
    }
}

std::string getInfix(const std::string &postfixExpression){
    Stack stack;
    
    for (auto i = postfixExpression.cbegin(); i < postfixExpression.cend(); ++i) {
       char elem = *i;
        if(elem == ' '){
            continue;
        }
        // If the scanned character is an operand (number||alpahabet),
        // push it to the stack.
       else if (isAlpha(elem) || isDigit(elem)) {
            std::string tmpStr;
            while (elem != ' ' && i != postfixExpression.cend()) {
               if (!isDigit(elem) && !isAlpha(elem)) {
                    std::cout<< "Error: wrong data!";
                   return "";
               }
               tmpStr += elem;
               ++i;
               elem = *i;
           }
            stack.push(Data(tmpStr, 0));
        }
       // If the scanned character is an operator, pop two
        // elements from stack apply the operator
        else if (isOperator(elem)) {
            Data firstArg;
            Data secondArg;

            if (!stack.isEmpty()) {
                secondArg = stack.top();
                stack.pop();
            }
            else {
                std::cout << "Error: stack is empty!";
                return "";
            }

            if (!stack.isEmpty()) {
                firstArg = stack.top();
                stack.pop();
            }
            else {
                std::cout << "Error: stack is empty!";
                return "";
            }
           
            //applying the operator
            Data infix = makeInfix(elem, firstArg, secondArg);
            //then pushing it to stack
            stack.push(infix);
            std::cout << "Result of expression placed in stack :" << infix.first.c_str()<< "\n";
        }
        else {
            std::cout<< "Incorrect symbol in string!";
            return "";
        }
    }

    // There must be a single element
    // in stack now which is the required infix.
    if (stack.size() == 1) {
        std:: string tmpStr = stack.top().first;
        stack.pop();
        return tmpStr;
    }
    else {
        std::cout << "Error: string is incorrect!";
        return "";
    }

}
Data makeInfix(const char &sign, const Data &firstArg, const Data &secondArg)
{
    std::string tmpStr;

    int expressionPriority = 0;
     //defining the priority for each sign(operator) according to PEDMAS
    //exponent > multiplication > adittion and subtraction
    if (sign == '+' || sign == '-') {
        expressionPriority = 1;
    } else if (sign == '*') {
        expressionPriority = 2;
    } else if (sign == '^') {
        expressionPriority = 3;
    }

    if (firstArg.second != 0 && firstArg.second < expressionPriority) {
        tmpStr += '(';
        tmpStr += firstArg.first;
        tmpStr += ')';
    } else {
        tmpStr += firstArg.first;
    }
    
    tmpStr += sign;

    if (secondArg.second != 0 && secondArg.second < expressionPriority) {
        tmpStr += '(';
        tmpStr += secondArg.first;
        tmpStr += ')';
    } else {
        tmpStr += secondArg.first;
    }
    
    Data tmp(tmpStr,expressionPriority);
    
    return tmp;
}

//check if element is an operand (in this case Alphabets)
bool isAlpha(const char ch)
{
    return ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z'));
}
//check if element is an operand (in this case numbers)
bool isDigit(const char ch)
{
    return (ch >= '0' && ch <= '9');
}

//check if element is an operator
bool isOperator(const char ch)
{
    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '^');
}






int main()
{
    std::cout << "> Choose your input" << "\n";
    std::cout << "> 0 - from console" << "\n";
    std::cout << "> 1 - from file default file -(default test file is located along the path : test3.txt)" << "\n";
    std::cout << "> Any other number to Exit!" <<"\n";

    int command = 0;
    std::cin >> command;
    std::cin.ignore();

    switch (command)
    {
        case 0:
        {
            std::cout << "> Enter expression: ";
            std::string input,output;
            std::getline(std::cin, input);
            output = getInfix(input);
            std::cout<< "---->   FINAL EXPRESSION : "<< output <<"\n\n";
            break;
        }
    case 1:
        {
            std::cout << "> FilePath: ";
            std::string filePath;
            std::cin >> filePath;
            ReadFromFile(filePath);
            break;
        }
    default:
            std::cout << "GOODBYE!";
    }
    return 0;
}

