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
        ROUND_OPEN, //открывающая круглая скобка
        QUAD_OPEN, //открывающая квадратная скобка
        FIGURE_OPEN, //открывающая фигурная скобка
        ROUND_CLOSE, //закрывающая круглая скобка
        QUAD_CLOSE, //закрывающая квадратная скобка
        FIGURE_CLOSE, //закрывающая фигурная скобка
        ELEMENT,
        TEXT
    };

    DynamicStack<Types> rulesTable[6] = {{CHARACTER},
                                    {ELEMENT, TEXT},
                                    {ROUND_OPEN, TEXT, ROUND_CLOSE},
                                    {QUAD_OPEN, TEXT, QUAD_CLOSE},
                                    {FIGURE_OPEN, TEXT, FIGURE_CLOSE},
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
