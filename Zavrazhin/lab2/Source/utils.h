#ifndef LAB2_UTILS_H_
#define LAB2_UTILS_H_

#include <string>
#include <sstream>

namespace lab2
{   
    // enum class OperationType is used to encode arithmetic operations
    enum class OperationType {ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION};
    
    // lab2::to_string is similar to std::to_string, but is overloaded for two
    // additional types: std::string and lab2::OperationType
    std::string to_string(const std::string& string)
    {
        return string;
    }
    
    std::string to_string(lab2::OperationType operationType)
    {
        if(operationType == lab2::OperationType::ADDITION)
            return "+";
        if(operationType == lab2::OperationType::SUBTRACTION)
            return "-";
        if(operationType == lab2::OperationType::MULTIPLICATION)
            return "*";
        if(operationType == lab2::OperationType::DIVISION)
            return "/";
        return "?";
    }
    
    template<class T>
    std::string to_string(T value)
    {
        return std::to_string(value);
    }
    
    // lab2::stoT converts a string into a numeric type
    // its name resembles the functions std::stoi, std::stol, std::stod, etc
    // this is necessary to convert a string to a numeric type specified as a 
    // template parameter
    template<class T>
    short stoT(const std::string& str)
    {
        T result;
        std::istringstream stream(str);
        stream >> result;
        return result;
    }
}

#endif  // LAB2_UTILS_H_
