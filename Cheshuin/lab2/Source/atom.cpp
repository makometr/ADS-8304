#include "atom.h"

Atom::Atom(std::string value)
{
    this->setDataType(DataType::ATOM);
    valueStr_ = value;

    if(value == "+" ||
       value == "-" ||
       value == "*")
    {
        type_ = AtomType::OPERATOR;
    }
    else if(value == "sin" ||
            value == "cos")
    {
        type_ = AtomType::FUNCTION;
    }
    else
    {
        bool isNumber = true;

        if(isdigit(value[0]) == 0 && value[0] != '-')
        {
            isNumber = false;
        }

        for(int i = 1; i < value.length(); i++)
        {
            if(isdigit(value[i]) == 0)
            {
                isNumber = false;
                break;
            }
        }

        if(isNumber || value == "PI")
        {
            type_ = AtomType::CONST_VALUE;
        }
        else
        {
            type_ = AtomType::VARIABLE;
        }
    }
}

Atom::Atom(const Atom& atom)
{
    setDataType(DataType::ATOM);
    valueStr_ = atom.valueStr_;
    type_ = atom.type_;
}

AtomType Atom::type()
{
    return type_;
}

std::string Atom::value()
{
    return valueStr_;
}
