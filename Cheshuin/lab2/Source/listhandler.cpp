#include "listhandler.h"

bool ListHandler::isValid(List& list)
{     
    if(list.isEmpty())
    {
        return false;
    }

    Node::NodeP buf = list.begin();
    AtomType exprType = AtomType::UNKNOWN;

    // Проверка 1 аргумента
    if(buf->data()->dataType() == DataType::ATOM)
    {
        Atom::AtomP arg1 = std::static_pointer_cast<Atom>(buf->data());

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
        List::ListP arg1 = std::static_pointer_cast<List>(buf->data());

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
        Atom::AtomP arg2 = std::static_pointer_cast<Atom>(buf->data());

        if(isArgument(*arg2) == false)
        {
            return false;
        }

    }
    else
    {
        List::ListP arg2 = std::static_pointer_cast<List>(buf->data());

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
        Atom::AtomP oper = std::static_pointer_cast<Atom>(buf->data());

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

List::ListP ListHandler::simplify(List& list)
{
    if(isValid(list))
    {
        if(list.begin()->next() == nullptr)
        {
            if(list.begin()->data()->dataType() == DataType::LIST)
            {
                List::ListP buf = std::static_pointer_cast<List>(list.begin()->data());

                List::ListP newList = simplify(*buf);

                std::cout << list.toString() << " - is simplified to - ";
                std::cout << newList->toString() <<std::endl;
                return newList;
            }
            else
            {

                List::ListP newList(new List());

                Atom::AtomP buf = std::static_pointer_cast<Atom>(list.begin()->data());
                Atom::AtomP newAtom(new Atom(*buf));

                newList->pushBack(newAtom);

                std::cout << list.toString() << " - is simplified to - ";
                std::cout << newList->toString() << std::endl;
                return newList;
            }
        }

        Atom::AtomP buf = std::static_pointer_cast<Atom>(list.end()->data());

        if(buf->type() == AtomType::OPERATOR)
        {
            std::string operStr = buf->value();
            Data::DataP arg1 = list.begin()->data();
            Data::DataP arg2 = list.begin()->next()->data();

            List::ListP newList = simplifyOper(operStr, arg1, arg2);

            std::cout << list.toString() << " - is simplified to - ";
            std::cout << newList->toString() <<std::endl;
            return newList;
        }
        else
        {
            Atom::AtomP func = std::static_pointer_cast<Atom>(list.begin()->data());
            std::string funcStr = func->value();
            Data::DataP arg = list.begin()->next()->data();

            List::ListP newList = simplifyFunc(funcStr, arg);

            std::cout << list.toString() << " - is simplified to - ";
            std::cout << newList->toString() << std::endl;
            return newList;
        }
    }
    else
    {
        std::cout << list.toString() << " - not simplified because incorrect. ";

        return std::make_shared<List>(list);
    }
}

List::ListP ListHandler::simplifyFunc(std::string& func, Data::DataP arg)
{
    List::ListP list(new List());
    Data::DataP newArg = nullptr;
    //упрощение аргумента
    if(arg->dataType() == DataType::LIST)
    {
        List::ListP argExpr = std::static_pointer_cast<List>(arg);
        List::ListP simplifyedArgExpr = simplify(*argExpr);

        if(simplifyedArgExpr->begin()->next() == nullptr)
        {
            newArg = simplifyedArgExpr->pullHead();
        }
        else
        {
            newArg = simplifyedArgExpr;
        }
    }
    else
    {
        newArg = arg;
    }

    if(newArg->dataType() == DataType::ATOM)
    {
        Atom::AtomP argAtom = std::static_pointer_cast<Atom>(newArg);
        //упрощения sin
        if(func == "sin")
        {
            if(argAtom->value() == "PI" || argAtom->value() == "0")
            {
                Atom::AtomP newArgAtom(new Atom("0"));
                list->pushBack(newArgAtom);
            }
            else
            {
                Atom::AtomP newFuncAtom(new Atom(func));
                Atom::AtomP newArgAtom(new Atom(*argAtom));
                list->pushBack(newFuncAtom);
                list->pushBack(newArgAtom);
            }
        }
        //упрощения cos
        else
        {
            if(argAtom->value() == "PI")
            {
                Atom::AtomP newArgAtom(new Atom("-1"));
                list->pushBack(newArgAtom);
            }
            else if(argAtom->value() == "0")
            {
                Atom::AtomP newArgAtom(new Atom("1"));
                list->pushBack(newArgAtom);
            }
            else
            {
                Atom::AtomP newFuncAtom(new Atom(func));
                Atom::AtomP newArgAtom(new Atom(*argAtom));
                list->pushBack(newFuncAtom);
                list->pushBack(newArgAtom);
            }
        }
    }
    else
    {
        Atom::AtomP newFuncAtom(new Atom(func));

        list->pushBack(newFuncAtom);
        list->pushBack(newArg);
    }

    return list;
}

List::ListP ListHandler::simplifyOper(std::string& oper, Data::DataP arg1, Data::DataP arg2)
{
    List::ListP list(new List());
    Data::DataP newArg1 = nullptr;
    Data::DataP newArg2 = nullptr;

    bool isNewArg1Simple = false;
    bool isNewArg2Simple = false;
    bool isAlreadySimplified = false;
    //упрощение 1 аргумента
    if(arg1->dataType() == DataType::LIST)
    {
        List::ListP arg1Expr = std::static_pointer_cast<List>(arg1);
        List::ListP simplifyedArg1Expr = simplify(*arg1Expr);

        if(simplifyedArg1Expr->begin()->next() == nullptr)
        {
            newArg1 = simplifyedArg1Expr->pullHead();
        }
        else
        {
            newArg1 = simplifyedArg1Expr;
        }
    }
    else
    {
        newArg1 = arg1;
    }
    //упрощение 2 аргумента
    if(arg2->dataType() == DataType::LIST)
    {
        List::ListP arg2Expr = std::static_pointer_cast<List>(arg2);
        List::ListP simplifyedArg2Expr = simplify(*arg2Expr);

        if(simplifyedArg2Expr->begin()->next() == nullptr)
        {
            newArg2 = simplifyedArg2Expr->pullHead();
        }
        else
        {
            newArg2 = simplifyedArg2Expr;
        }
    }
    else
    {
        newArg2 = arg2;
    }

    if(newArg1->dataType() == DataType::ATOM)
    {
        isNewArg1Simple = true;
    }
    if(newArg2->dataType() == DataType::ATOM)
    {
        isNewArg2Simple = true;
    }
    //упрощение текущей операции
    if(oper == "*")
    {
        if(isNewArg1Simple)
        {
            Atom::AtomP buf = std::static_pointer_cast<Atom>(newArg1);
            if(buf->value() == "0")
            {
                Atom::AtomP newAtom(new Atom("0"));
                list->pushBack(newAtom);

                isAlreadySimplified = true;
            }
            else if(buf->value() == "1")
            {
                list->pushBack(newArg2);

                isAlreadySimplified = true;
            }
        }
        if(isNewArg2Simple && isAlreadySimplified == false)
        {
            Atom::AtomP buf = std::static_pointer_cast<Atom>(newArg2);
            if(buf->value() == "0")
            {
                Atom::AtomP newAtom(new Atom("0"));
                list->pushBack(newAtom);

                isAlreadySimplified = true;
            }
            else if(buf->value() == "1")
            {
                list->pushBack(newArg1);

                isAlreadySimplified = true;
            }
        }
        if(isAlreadySimplified == false)
        {
            Atom::AtomP newOperAtom(new Atom(oper));

            list->pushBack(newArg1);
            list->pushBack(newArg2);
            list->pushBack(newOperAtom);
        }
    }
    else if(oper == "+" || oper == "-")
    {
        if(isNewArg1Simple)
        {
            Atom::AtomP buf = std::static_pointer_cast<Atom>(newArg1);
            if (oper == "-" && isNewArg2Simple)
            {
                Atom::AtomP buf2 = std::static_pointer_cast<Atom>(newArg2);
                if(buf->value() == buf2->value())
                {
                    Atom::AtomP newAtom(new Atom("0"));
                    list->pushBack(newAtom);

                    isAlreadySimplified = true;
                }
            }
            else if(oper == "+" && buf->value() == "0")
            {
                list->pushBack(newArg2);
                isAlreadySimplified = true;
            }
        }
        if(isNewArg2Simple && isAlreadySimplified == false)
        {
            Atom::AtomP buf = std::static_pointer_cast<Atom>(newArg2);
            if(buf->value() == "0")
            {
                list->pushBack(newArg1);
                isAlreadySimplified = true;
            }
        }
        if(isAlreadySimplified == false)
        {
            Atom::AtomP newOperAtom(new Atom(oper));

            list->pushBack(newArg1);
            list->pushBack(newArg2);
            list->pushBack(newOperAtom);
        }
    }

    return list;
}
