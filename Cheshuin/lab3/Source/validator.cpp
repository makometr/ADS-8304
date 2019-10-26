#include "validator.h"

Validator::Types Validator::typeOf(char character)
{
    if(character == '(')
    {
        return ROBRACKET;
    }
    if(character == '[')
    {
        return QOBRACKET;
    }
    if(character == '{')
    {
        return FOBRACKET;
    }
    if(character == ')')
    {
        return RCBRACKET;
    }
    if(character == ']')
    {
        return QCBRACKET;
    }
    if(character == '}')
    {
        return FCBRACKET;
    }

    return CHARACTER;
}

int Validator::check(std::istream& stream)
{
    int position = 1;
    char nextChar = 0;

    stack.clear();
    stack.push(TEXT);

    for(; stream.peek() != EOF;)
    {
        if(stack.isEmpty())
        {
            std::cout << "Incorrect syntax - excess characters." << std::endl;

            return position;
        }

        nextChar = static_cast<char>(stream.peek());

        Types expectedType = stack.onTop();
        Types realType = typeOf(nextChar);

        if(expectedType == realType)
        {
            stream.get();
            stack.pop();

            position += 1;
        }
        else
        {
            int syntaxRule = syntaxTable[expectedType][realType];
            if(syntaxRule != -1)
            {
                stack.pop();
                stack.push(rulesTable[syntaxRule]);

                std::cout << "Used syntax rule number - " << syntaxRule << std::endl;
            }
            else
            {
                std::cout << "Incorrect syntax - syntax rule not founded." << std::endl;

                return position;
            }
        }
    }


    if(!stack.isEmpty())
    {
        if(stack.size() > 1 || stack.onTop() != TEXT)
        {
            std::cout << "Incorrect syntax - early end of string." << std::endl;

            return position;
        }
    }

    return VALID;
}
