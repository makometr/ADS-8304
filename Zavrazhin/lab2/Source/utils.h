#ifndef LAB2_UTILS_H_
#define LAB2_UTILS_H_

#include <string>

namespace lab2
{   
    // enum class OperationType is used to encode an arithmetic operation
    enum class OperationType {ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION};
    
    // lab2::to_string is similar to std::to_string, but is overloaded for two
    // additional types
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
    
    std::string to_string(auto value)
    {
        return std::to_string(value);
    }
    
    // lab2::stoT is a generalization of std::stoi, std::stol, ...
    // for a numeric type T
    template<class T>
    T stoT(std::string);
    template<>
    short stoT<short>(std::string str){return std::stoi(str);}
    template<>
    int stoT<int>(std::string str){return std::stoi(str);}
    template<>
    long stoT<long>(std::string str){return std::stol(str);}
    template<>
    long long stoT<long long>(std::string str){return std::stoll(str);}
    template<>
    unsigned short stoT<unsigned short>(std::string str){return std::stoi(str);}
    template<>
    unsigned int stoT<unsigned int>(std::string str){return std::stoul(str);}
    template<>
    unsigned long stoT<unsigned long>(std::string str){return std::stoul(str);}
    template<>
    unsigned long long stoT<unsigned long long>(std::string str){return std::stoull(str);}
    template<>
    float stoT<float>(std::string str){return std::stof(str);}
    template<>
    double stoT<double>(std::string str){return std::stod(str);}
    template<>
    long double stoT<long double>(std::string str){return std::stold(str);}
}

#endif  // LAB2_UTILS_H_
