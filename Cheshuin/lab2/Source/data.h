#ifndef DATA_H
#define DATA_H

#include <memory>
#include "types.h"

class Data
{
private:
    DataType dataType_ = DataType::UNKNOWN;
protected:
    void setDataType(DataType type);
public:
    typedef std::shared_ptr<Data> DataP;
    Data() = default;
    DataType dataType();
};

#endif // DATA_H
