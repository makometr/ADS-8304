#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<istream>
#include<string>
#include "list.h"
#include "atom.h"

class Parser
{
private:

public:
    Parser() = default;

    List* parse(std::istream& stream);
    Atom* readAtom(std::istream& stream);
};

#endif // PARSER_H
