#ifndef LISTHANDLER_H
#define LISTHANDLER_H

#include <iostream>
#include <map>
#include <string>
#include "list.h"
#include "atom.h"

class ListHandler
{
private:
    bool isArgument(Atom& atom);
    List* simplifyFunc(std::string* func, Data* arg);
    List* simplifyOper(std::string* oper, Data* arg1, Data* arg2);
public:
    ListHandler() = default;
    bool isValid(List& list);
    List* simplify(List& list);
};

#endif // LISTHANDLER_H
