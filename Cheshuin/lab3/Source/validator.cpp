#include "validator.h"

Validator::Types Validator::typeOf(char character)
{
    if(character == '(')
    {
        return ROUND_OPEN;
    }
    if(character == '[')
    {
        return QUAD_OPEN;
    }
    if(character == '{')
    {
        return FIGURE_OPEN;
    }
    if(character == ')')
    {
        return ROUND_CLOSE;
    }
    if(character == ']')
    {
        return QUAD_CLOSE;
    }
    if(character == '}')
    {
        return FIGURE_CLOSE;
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
            std::cout << "-------------------------------------------" << std::endl;

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
                std::cout << "-------------------------------------------" << std::endl;

                return position;
            }
        }
    }


    if(!stack.isEmpty())
    {
        if(stack.size() > 1 || stack.onTop() != TEXT)
        {
            std::cout << "Incorrect syntax - early end of string." << std::endl;
            std::cout << "-------------------------------------------" << std::endl;

            return position;
        }
    }

    std::cout << "-------------------------------------------" << std::endl;
    return VALID;
}
