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
        std::string key_;
        ValueT value_;
    };

    int size_ = 10;
    int elementsCount_ = 0;
    std::list<pair>* array_ = nullptr;

    unsigned hash(const std::string& key) const;
    void resize(int size);

public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable& table);
    void operator=(const HashTable& table);

    void insert(std::string key, ValueT value);
    ValueT get(const std::string& key) const;
    void remove(const std::string& key);
    bool search(const std::string& key) const;
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
void HashTable<ValueT>::insert(std::string key, ValueT value)
{
    if(elementsCount_ >= size_)
    {
        resize(size_ * 2);
    }

    elementsCount_ += 1;

    unsigned hash_ = hash(key);

    pair newPair{key, value};
    array_[hash_].push_back(newPair);
}

template<typename ValueT>
ValueT HashTable<ValueT>::get(const std::string& key) const
{
     unsigned hash_ = hash(key);

     std::list<pair>& valueList = array_[hash_];

     for(auto iter = valueList.begin(); iter != valueList.end(); iter++)
     {
         if((*iter).key_ == key)
         {
             return (*iter).value_;
         }
     }

     std::cout << "Can't find key: " << key << std::endl;
     throw "Key doesn't exist";
}

template<typename ValueT>
void HashTable<ValueT>::remove(const std::string& key)
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
bool HashTable<ValueT>::search(const std::string& key) const
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
unsigned HashTable<ValueT>::hash(const std::string& key) const
{
    unsigned hashKey = 0;

    for(unsigned i = 0; i < key.size(); i++)
    {
        hashKey += (hashKey << 8 ) + static_cast<unsigned>(key[i]);
        hashKey = hashKey % size_;
    }

    return hashKey;
}

template<typename ValueT>
void HashTable<ValueT>::resize(int size)
{
    int oldSize = size_;
    size_ = size;
    std::list<pair>* newArray = new std::list<pair>[size_];

    for(int i = 0; i < oldSize; i++)
    {
        for(auto iter = array_[i].begin(); iter != array_[i].end(); iter++)
        {
            unsigned hash_ = hash((*iter).key_);

            pair newPair{(*iter).key_, (*iter).value_};
            newArray[hash_].push_back(newPair);
        }
    }
    delete[] array_;
    array_ = newArray;
}

template<typename ValueT>
std::string HashTable<ValueT>::toStr() const
{
    std::stringstream out;
    for (int i = 0; i < size_; i++)
    {
        out << "Hash - " << i << std::endl;
        for(auto iter = array_[i].begin(); iter != array_[i].end(); iter++)
        {
            out << "----[" << (*iter).key_ << " - " + (*iter).value_ << "]" << std::endl;
        }
    }

    return out.str();
}
#endif // HASHTABLE_H
