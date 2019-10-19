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

    List::ListP parse(std::istream& stream);
    Atom::AtomP readAtom(std::istream& stream);
};

#endif // PARSER_H
