#ifndef DATA_H
#define DATA_H

#include "types.h"

class Data
{
private:
    DataType dataType_ = DataType::UNKNOWN;
protected:
    void setDataType(DataType type);
public:
    Data() = default;
    DataType dataType();
};

#endif // DATA_H
