#ifndef TYPES_H
#define TYPES_H

enum class DataType
{
    ATOM,
    LIST,
    UNKNOWN
};

enum class AtomType
{
    CONST_VALUE,
    VARIABLE,
    OPERATOR,
    FUNCTION,
    UNKNOWN
};

#endif // TYPES_H
