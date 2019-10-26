#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <iostream>
#include "dynamicstack.h"

class Validator
{
private:
    enum Types // не enum class для удобства работы с таблицей валидации
    {
        CHARACTER,
        ROBRACKET, //открывающая круглая скобка
        QOBRACKET, //открывающая квадратная скобка
        FOBRACKET, //открывающая фигурная скобка
        RCBRACKET, //закрывающая круглая скобка
        QCBRACKET, //закрывающая квадратная скобка
        FCBRACKET, //закрывающая фигурная скобка
        ELEMENT,
        TEXT
    };

    DynamicStack<Types> rulesTable[6] = {{CHARACTER},
                                    {ELEMENT, TEXT},
                                    {ROBRACKET, TEXT, RCBRACKET},
                                    {QOBRACKET, TEXT, QCBRACKET},
                                    {FOBRACKET, TEXT, FCBRACKET},
                                    {}};

    int syntaxTable[9][9] = {{-1, -1, -1, -1, -1, -1, -1, -1, -1},
                             {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                             {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                             {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                             {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                             {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                             {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                             { 0,  2,  3,  4, -1, -1, -1, -1, -1},
                             { 1,  1,  1,  1,  5,  5,  5,  1, -1}};

    DynamicStack<Types> stack = {};

public:
    const static int VALID = -1;

private:
    Types typeOf(char elem);

public:
    Validator() = default;
    int check(std::istream& stream);
};

#endif // VALIDATOR_H
