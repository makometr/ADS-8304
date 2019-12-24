#ifndef ENCODETREE_H
#define ENCODETREE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>


struct Symbol
{
    char data_;
    size_t weight_;

    Symbol(char data = 0, size_t weight = 0) :
        data_(data), weight_(weight) { }
};


class EncodeTree
{
public:
    EncodeTree();

    EncodeTree(const Symbol& data);

    virtual ~EncodeTree();

    const EncodeTree* getLeft() const;

    const EncodeTree* getRight() const;

    const EncodeTree* getParent() const;

    const Symbol* getData() const;

    void concatenateTrees (size_t weight, EncodeTree* left, EncodeTree* right);

    void setLeft(EncodeTree* left);

    void setRight(EncodeTree* right);

    void setParent(EncodeTree* parent);

    void setData(const Symbol& data);

    void concat(size_t weight, EncodeTree* left, EncodeTree* right);

    bool isEmptyNode() const;

    bool isLeaf() const;

    std::map<std::string, char> getCharactersCode() const;

    std::string encode(const std::string& message);

    void printTree(std::string& result, size_t level = 0) const;

    std::string createCodeSymbols(const std::string& message) const;

protected:
    virtual void createEncodeTree(const std::string& message) = 0;

    const EncodeTree* findSymbol(char data) const;


    void getCharactersCode (std::map<std::string, char>& charactersCode,
                            const std::string& path) const;


private:
    Symbol* data_;
    EncodeTree* parent_;
    EncodeTree* left_;
    EncodeTree* right_;
};


#endif // ENCODETREE_H
