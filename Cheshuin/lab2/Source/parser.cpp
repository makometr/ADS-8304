#include "parser.h"

List* Parser::parse(std::istream& stream)
{
    char buffer = '\0';
    List* parsedList = new List();

    while(stream.peek() != EOF)
    {
        stream.get(buffer);

        if(buffer == '(')
        {
            parsedList->pushBack(parse(stream));
        }
        else if(buffer == ')')
        {
            break;
        }
        else if(buffer == ' ');
        else
        {
            stream.unget();

            parsedList->pushBack(readAtom(stream));
        }
    }

    return parsedList;
}

Atom* Parser::readAtom(std::istream& stream)
{
    char buffer = ' ';
    std::string* atomValue = new std::string();

    while(stream.peek() != EOF)
    {
        stream.get(buffer);

        if(buffer == '(' ||
           buffer == ')')
        {
            stream.unget();
            break;
        }
        else if(isspace(buffer))
        {
            break;
        }
        else
        {
            (*atomValue) += buffer;
        }
    }

    Atom* atom = new Atom(atomValue);
    return atom;
}
