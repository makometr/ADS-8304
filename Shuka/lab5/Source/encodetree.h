#ifndef ENCODETREE_H
#define ENCODETREE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>


struct Symbol
{
    /*
     * Структура для хранения символа и его 'веса'
    */

    char data_;
    size_t weight_;

    Symbol(char data = 0, size_t weight = 0) :
        data_(data), weight_(weight) { }
};


class EncodeTree
{
    /*
     * Базовый абстрактный класс дерева, реализующий методы для работы с
     * бинарным деревом кодирования. Экземпляр класса является узлом дерева.
    */

public:
    EncodeTree();

    EncodeTree(const Symbol& data);

    virtual ~EncodeTree();

    const EncodeTree* getLeft() const;

    const EncodeTree* getRight() const;

    const EncodeTree* getParent() const;

    const Symbol& getData() const;

    void setLeft(EncodeTree* left);

    void setRight(EncodeTree* right);

    void setParent(EncodeTree* parent);

    void setData(Symbol data);

    void concat(size_t weight, EncodeTree* left, EncodeTree* right);

    std::string encode(const std::string& message);

protected:
    virtual void createEncodeTree(const std::string& message) = 0;

    virtual void createEncodeTree(std::map<char, size_t>& symbolMap,
                                  std::vector<char>& symbolVector,
                                  size_t left, size_t right, size_t sum) = 0;

    const EncodeTree* findSymbol(char data) const;

    void printTree(std::string& result, size_t level = 0) const;

    std::string createCodeSymbols(const std::string& message) const;

private:
    Symbol data_;
    EncodeTree* parent_;
    EncodeTree* left_;
    EncodeTree* right_;
};


#endif // ENCODETREE_H
