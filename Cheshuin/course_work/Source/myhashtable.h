#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<list>
#include<iostream>
#include <sstream>

template<typename ValueT>
class HashTable
{
private:
    struct pair
    {
        long long int key_;
        ValueT value_;
    };

    int size_ = 8;
    int elementsCount_ = 0;
    std::list<pair>* array_ = nullptr;

    unsigned hash(const long long int& key) const;
    void resize(int size);

public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable& table);
    void operator=(const HashTable& table);

    void insert(long long int key, ValueT value);
    ValueT get(const long long int& key) const;
    void remove(const long long int& key);
    bool search(const long long int& key) const;
    void clear();
    std::string toStr() const;
};

template<typename ValueT>
HashTable<ValueT>::HashTable()
{
    array_ = new std::list<pair>[size_];
}

template<typename ValueT>
HashTable<ValueT>::~HashTable()
{
    delete[] array_;
}

template<typename ValueT>
HashTable<ValueT>::HashTable(const HashTable& table)
{
    this->size_ = table.size_;
    for(int i = 0; i < size_; i++)
    {
        array_[i] = table.array_[i];
    }
}

template<typename ValueT>
void HashTable<ValueT>::operator=(const HashTable& table)
{
    this->size_ = table.size_;
    for(int i = 0; i < size_; i++)
    {
        array_[i] = table.array_[i];
    }
}

template<typename ValueT>
void HashTable<ValueT>::insert(long long int key, ValueT value)
{
    if(elementsCount_ >= size_)
    {
        resize(size_ * 2);
    }

    elementsCount_ += 1;

    unsigned hash_ = hash(key);

    std::list<pair>& valueList = array_[hash_];

    for(auto& elem : valueList)
    {
        if(elem.key_ == key)
        {
            elem.value_ = value;
            return;
        }
    }

    pair newPair{key, value};

    array_[hash_].push_back(newPair);
}

template<typename ValueT>
ValueT HashTable<ValueT>::get(const long long int& key) const
{
     unsigned hash_ = hash(key);

     std::list<pair>& valueList = array_[hash_];

     for(auto& elem : valueList)
     {
         if(elem.key_ == key)
         {
             return elem.value_;
         }
     }

     std::cout << "Can't find key: " << key << std::endl;
     throw "Key doesn't exist";
}

template<typename ValueT>
void HashTable<ValueT>::remove(const long long int& key)
{
    elementsCount_ -= 1;
    unsigned hash_ = hash(key);

    std::list<pair>& valueList = array_[hash_];

    for(auto iter = valueList.begin(); iter != valueList.end(); iter++)
    {
        if((*iter).key_ == key)
        {
            valueList.erase(iter);

            return;
        }
    }

    std::cout << "Can't find key: " << key << std::endl;
    throw "Key doesn't exist";
}

template<typename ValueT>
bool HashTable<ValueT>::search(const long long int& key) const
{
    unsigned hash_ = hash(key);

    std::list<pair>& valueList = array_[hash_];

    for(auto iter = valueList.begin(); iter != valueList.end(); iter++)
    {
        if((*iter).key_ == key)
        {
            return true;
        }
    }

    return false;
}

template<typename ValueT>
unsigned HashTable<ValueT>::hash(const long long int& key) const
{
    unsigned basicHash = abs(key) % size_;

    return basicHash;
}

template<typename ValueT>
void HashTable<ValueT>::resize(int size)
{
    int oldSize = size_;
    size_ = size;
    std::list<pair>* newArray = new std::list<pair>[size_];

    for(int i = 0; i < oldSize; i++)
    {
        for(auto& elem : array_[i])
        {
            unsigned hash_ = hash(elem.key_);

            pair newPair{elem.key_, elem.value_};
            newArray[hash_].push_back(newPair);
        }
    }
    delete[] array_;
    array_ = newArray;
}

template<typename ValueT>
std::string HashTable<ValueT>::toStr() const
{
    std::stringstream out("");
    for (int i = 0; i < size_; i++)
    {
        out << "Hash - " << i << std::endl;
        for(auto& elem : array_[i])
        {
            out << "----[" << elem.key_ << " - " << elem.value_ << "]" << std::endl;
        }
    }

    return out.str();
}

template<typename ValueT>
void HashTable<ValueT>::clear()
{
    size_ = 8;
    elementsCount_ = 0;

    delete[] array_;

    array_ = new std::list<pair>[size_];
}
#endif // HASHTABLE_H
