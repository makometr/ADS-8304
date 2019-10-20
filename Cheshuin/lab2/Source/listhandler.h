#ifndef LISTHANDLER_H
#define LISTHANDLER_H

#include <iostream>
#include <memory>
#include <map>
#include <string>
#include "list.h"
#include "atom.h"

class ListHandler
{
private:
    typedef std::shared_ptr<ListHandler> ListHandlerP;

    bool isArgument(Atom& atom);
    List::ListP simplifyFunc(std::string& func, Data::DataP arg);
    List::ListP simplifyOper(std::string& oper, Data::DataP arg1, Data::DataP arg2);
public:
    ListHandler() = default;
    bool isValid(List& list);
    List::ListP simplify(List& list);
};

#endif // LISTHANDLER_H
