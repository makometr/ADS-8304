#include "listhandler.h"

bool ListHandler::isValid(List& list)
{     
    if(list.isEmpty())
    {
        return false;
    }

    Node* buf = list.begin();
    AtomType exprType = AtomType::UNKNOWN;

    // Проверка 1 аргумента
    if(buf->data()->dataType() == DataType::ATOM)
    {
        Atom* arg1 = static_cast<Atom*>(buf->data());

        if(isArgument(*arg1))
        {
            exprType = AtomType::OPERATOR;
        }
        else if(arg1->type() == AtomType::FUNCTION)
        {
            exprType = AtomType::FUNCTION;
        }
        else
        {
            return false;
        }
    }
    else
    {
        List* arg1 = static_cast<List*>(buf->data());

        if(isValid(*arg1))
        {
            exprType = AtomType::OPERATOR;
        }
        else
        {
            return false;
        }
    }

    // Проверка 2 аргумента
    buf = buf->next();

    if(buf == nullptr)
    {
        if(exprType == AtomType::FUNCTION)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    if(buf->data()->dataType() == DataType::ATOM)
    {
        Atom* arg2 = static_cast<Atom*>(buf->data());

        if(isArgument(*arg2) == false)
        {
            return false;
        }

    }
    else
    {
        List* arg2 = static_cast<List*>(buf->data());

        if(isValid(*arg2) == false)
        {
            return false;
        }
    }

    // Проверка оператора
    buf = buf->next();

    if(buf == nullptr)
    {
        if(exprType == AtomType::FUNCTION)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if(buf->data()->dataType() == DataType::ATOM)
    {
        Atom* oper = static_cast<Atom*>(buf->data());

        if(oper->type() != AtomType::OPERATOR)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    //проверка законченности
    buf = buf->next();

    if(buf != nullptr)
    {
        return false;
    }

    return true;
}

bool ListHandler::isArgument(Atom& atom)
{
    return (atom.type() == AtomType::VARIABLE ||
            atom.type() == AtomType::CONST_VALUE);
}

List* ListHandler::simplify(List& list)
{
    if(isValid(list))
    {
        if(list.begin()->next() == nullptr)
        {
            if(list.begin()->data()->dataType() == DataType::LIST)
            {
                List* buf = static_cast<List*>(list.begin()->data());

                List* newList = simplify(*buf);

                std::cout << list.toString() << " - is simplified to - ";
                std::cout << newList->toString() <<std::endl;
                return newList;
            }
            else
            {

                List* newList = new List();

                Atom* buf = static_cast<Atom*>(list.begin()->data());
                Atom* newAtom = new Atom(*buf);

                newList->pushBack(newAtom);

                std::cout << list.toString() << " - is simplified to - ";
                std::cout << newList->toString() <<std::endl;
                return newList;
            }
        }

        Atom* buf = static_cast<Atom*>(list.end()->data());

        if(buf->type() == AtomType::OPERATOR)
        {
            std::string* operStr = buf->value();
            Data* arg1 = list.begin()->data();
            Data* arg2 = list.begin()->next()->data();

            List* newList = simplifyOper(operStr, arg1, arg2);

            std::cout << list.toString() << " - is simplified to - ";
            std::cout << newList->toString() <<std::endl;
            return newList;
        }
        else
        {
            Atom* func = static_cast<Atom*>(list.begin()->data());
            std::string* funcStr = func->value();
            Data* arg = list.begin()->next()->data();

            List* newList = simplifyFunc(funcStr, arg);

            std::cout << list.toString() << " - is simplified to - ";
            std::cout << newList->toString() << std::endl;
            return newList;
        }
    }
    else
    {
        std::cout << list.toString() << " - not simplified because incorrect. ";

        return &list;
    }
}

List* ListHandler::simplifyFunc(std::string* func, Data* arg)
{
    List* list = new List();
    //упрощение аргумента
    if(arg->dataType() == DataType::LIST)
    {
        List* argExpr = static_cast<List*>(arg);
        List* simplifyedArgExpr = simplify(*argExpr);

        if(simplifyedArgExpr->begin()->next() == nullptr)
        {
            Data* newArg = simplifyedArgExpr->pullHead();
            delete  simplifyedArgExpr;

            if(newArg->dataType() == DataType::LIST)
            {
                Atom* newFuncAtom = new Atom(func);

                list->pushBack(newFuncAtom);
                list->pushBack(newArg);
            }
            else
            {
               arg = newArg;
            }
        }
    }

    if(arg->dataType() == DataType::ATOM)
    {
        Atom* argAtom = static_cast<Atom*>(arg);
        //упрощения sin
        if(*func == "sin")
        {
            if(*argAtom->value() == "PI" || *argAtom->value() == "0")
            {
                std::string* argStr = new std::string("0");
                Atom* newArgAtom = new Atom(argStr);
                list->pushBack(newArgAtom);
            }
            else
            {
                Atom* newFuncAtom = new Atom(func);
                Atom* newArgAtom = new Atom(argAtom->value());
                list->pushBack(newFuncAtom);
                list->pushBack(newArgAtom);
            }
        }
        //упрощения cos
        else
        {
            if(*argAtom->value() == "PI")
            {
                std::string* argStr = new std::string("-1");
                Atom* newArgAtom = new Atom(argStr);
                list->pushBack(newArgAtom);
            }
            else if(*argAtom->value() == "0")
            {
                std::string* argStr = new std::string("1");
                Atom* newArgAtom = new Atom(argStr);
                list->pushBack(newArgAtom);
            }
            else
            {
                std::string* newFunc = new std::string(*func);
                Atom* newFuncAtom = new Atom(newFunc);
                Atom* newArgAtom = new Atom(*argAtom);
                list->pushBack(newFuncAtom);
                list->pushBack(newArgAtom);
            }
        }
    }
    else
    {
        std::string* newFunc = new std::string(*func);
        Atom* newFuncAtom = new Atom(newFunc);

        list->pushBack(newFuncAtom);
        list->pushBack(arg);
    }

    return list;
}

List* ListHandler::simplifyOper(std::string* oper, Data* arg1, Data* arg2)
{
    List* list = new List();

    bool isArg1Simple = false;
    bool isArg2Simple = false;
    bool isAlreadySimplified = false;
    //упрощение 1 аргумента
    if(arg1->dataType() == DataType::LIST)
    {
        List* arg1Expr = static_cast<List*>(arg1);
        List* simplifyedArg1Expr = simplify(*arg1Expr);

        if(simplifyedArg1Expr->begin()->next() == nullptr)
        {
            Data* newArg1 = simplifyedArg1Expr->pullHead();
            delete  simplifyedArg1Expr;

            arg1 = newArg1;
        }
        else
        {
            arg1 = simplifyedArg1Expr;
        }
    }
    //упрощение 2 аргумента
    if(arg2->dataType() == DataType::LIST)
    {
        List* arg2Expr = static_cast<List*>(arg2);
        List* simplifyedArg2Expr = simplify(*arg2Expr);

        if(simplifyedArg2Expr->begin()->next() == nullptr)
        {
            Data* newArg2 = simplifyedArg2Expr->pullHead();
            delete  simplifyedArg2Expr;

            arg2 = newArg2;
        }
        else
        {
            arg2 = simplifyedArg2Expr;
        }
    }

    if(arg1->dataType() == DataType::ATOM)
    {
        isArg1Simple = true;
    }
    if(arg2->dataType() == DataType::ATOM)
    {
        isArg2Simple = true;
    }
    //упрощение текущей операции
    if(*oper == "*")
    {
        if(isArg1Simple)
        {
            Atom* buf = static_cast<Atom*>(arg1);
            if(*buf->value() == "0")
            {
                std::string* atomValue = new std::string("0");
                Atom* newAtom = new Atom(atomValue);
                list->pushBack(newAtom);

                isAlreadySimplified = true;
            }
            else if(*buf->value() == "1")
            {
                list->pushBack(arg2);

                isAlreadySimplified = true;
            }
        }
        if(isArg2Simple && isAlreadySimplified == false)
        {
            Atom* buf = static_cast<Atom*>(arg2);
            if(*buf->value() == "0")
            {
                std::string* atomValue = new std::string("0");
                Atom* newAtom = new Atom(atomValue);
                list->pushBack(newAtom);

                isAlreadySimplified = true;
            }
            else if(*buf->value() == "1")
            {
                list->pushBack(arg1);

                isAlreadySimplified = true;
            }
        }
        if(isAlreadySimplified == false)
        {
            std::string* newOper = new std::string(*oper);
            Atom* newOperAtom = new Atom(newOper);

            list->pushBack(arg1);
            list->pushBack(arg2);
            list->pushBack(newOperAtom);
        }
    }
    else if(*oper == "+" || *oper == "-")
    {
        if(isArg1Simple)
        {
            Atom* buf = static_cast<Atom*>(arg1);
            if (*oper == "-" && isArg2Simple)
            {
                Atom* buf2 = static_cast<Atom*>(arg2);
                if(*buf->value() == *buf2->value())
                {
                    std::string* atomValue = new std::string("0");
                    Atom* newAtom = new Atom(atomValue);
                    list->pushBack(newAtom);

                    isAlreadySimplified = true;
                }
            }
        }
        if(isArg2Simple && isAlreadySimplified == false)
        {
            Atom* buf = static_cast<Atom*>(arg2);
            if(*buf->value() == "0")
            {
                list->pushBack(arg1);
                isAlreadySimplified = true;
            }
        }
        if(isAlreadySimplified == false)
        {
            std::string* newOper = new std::string(*oper);
            Atom* newOperAtom = new Atom(newOper);

            list->pushBack(arg1);
            list->pushBack(arg2);
            list->pushBack(newOperAtom);
        }
    }

    return list;
}
