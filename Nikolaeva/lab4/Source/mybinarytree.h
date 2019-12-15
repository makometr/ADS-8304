#ifndef MYBINARYTREE_H
#define MYBINARYTREE_H

#include <iostream>
#include <ostream>
#include <memory>


template <class T>
class BinaryTree
{
public:
    typedef std::shared_ptr<BinaryTree<T>> BinaryTreeP;

    explicit BinaryTree() = default;
    explicit BinaryTree(const T& data);
    ~BinaryTree() = default;

    BinaryTreeP getLeft() const;
    BinaryTreeP getRight() const;
    const T& getData() const;

    static BinaryTreeP createCharTree(const std::string& expression) = delete;

    static size_t getEndIndexSubTree(const std::string& str, size_t indexEnd);

    bool elemIsExist(const T& elem) const;
    size_t numberOfElem(const T& elem) const;
    int minDepthToElem(const T& elem, size_t depth = 0);

private:
    BinaryTreeP leftTree_;
    BinaryTreeP rightTree_;
    T data_;
};


template<class T>
BinaryTree<T>::BinaryTree(const T &data)
{
    data_ = data;
}


template<class T>
typename BinaryTree<T>::BinaryTreeP BinaryTree<T>::getLeft() const
{
    return this->leftTree_;
}


template<class T>
typename BinaryTree<T>::BinaryTreeP BinaryTree<T>::getRight() const
{
    return this->rightTree_;
}


template<class T>
const T &BinaryTree<T>::getData() const
{
    return this->data_;
}


template<>
typename BinaryTree<char>::BinaryTreeP
BinaryTree<char>::createCharTree(const std::string& str)
{
    BinaryTreeP tree = std::make_shared<BinaryTree<char>>();

    char elem = 0;
    size_t indexStart = 1;

    while (str[indexStart] != '(' && str[indexStart] != ')') {
        if (str[indexStart] != ' ' && str[indexStart] != '(' && str[indexStart] != ')') {
            elem = str[indexStart];
            tree->data_ = elem;
        }
        indexStart++;;
    }

    if (str[indexStart] == ')') {
        return tree;
    }

    size_t indexEnd = indexStart + 1;
    indexEnd = getEndIndexSubTree(str, indexEnd);
    BinaryTreeP leftTree = createCharTree(str.substr(indexStart, indexEnd - indexStart));
    tree->leftTree_ = leftTree;

    indexStart = indexEnd;
    while (str[indexStart] != '(' && str[indexStart] != ')') {
        indexStart++;
    }

    if (str[indexStart] == ')') {
        return tree;
    }

    indexEnd = indexStart + 1;
    indexEnd = getEndIndexSubTree(str, indexEnd);
    BinaryTreeP rightTree = createCharTree(str.substr(indexStart, indexEnd - indexStart));
    tree->rightTree_ = rightTree;

    return tree;
}


template<class T>
size_t BinaryTree<T>::getEndIndexSubTree(const std::string &str, size_t indexEnd)
{
    /*
     * Метод возвращает индекс в строке конца поддерева
    */

    size_t openB = 1;
    size_t closeB = 0;
    while (openB != closeB) {
        if (str[indexEnd] == '(') {
            openB++;
        }
        else if (str[indexEnd] == ')') {
            closeB++;
        }
        indexEnd++;
    }
    return indexEnd;
}


template<class T>
bool BinaryTree<T>::elemIsExist(const T& elem) const
{
    if (this->getData() == elem)
        return true;

    bool isExist = false;
    if (this->getLeft() != nullptr) {
        isExist = isExist || this->getLeft()->elemIsExist(elem);
    }

    if (this->getRight() != nullptr) {
        isExist = isExist || this->getRight()->elemIsExist(elem);
    }

    return isExist;
}


template<class T>
size_t BinaryTree<T>::numberOfElem(const T& elem) const
{
    size_t count = 0;
    if (this->getData() == elem) {
        count += 1;
    }

    if (this->getLeft() != nullptr) {
        count += this->getLeft()->numberOfElem(elem);
    }

    if (this->getRight() != nullptr){
        count += this->getRight()->numberOfElem(elem);
    }

    return count;
}

template<class T>
int BinaryTree<T>::minDepthToElem(const T &elem, size_t depth)
{
    if (this->getData() == elem){
        return static_cast<int>(depth);
    }

    int leftMinDepth = -1;
    int rightMinDepth = -1;

    if (this->getLeft() != nullptr) {
        leftMinDepth = this->getLeft()->minDepthToElem(elem, depth + 1);
    }

    if (this->getRight() != nullptr){
        rightMinDepth = this->getRight()->minDepthToElem(elem, depth + 1);
    }

    if (leftMinDepth != -1 && rightMinDepth != -1)
        return std::min(leftMinDepth, rightMinDepth);
    else if (leftMinDepth == -1)
        return rightMinDepth;
    else
        return leftMinDepth;

}


#endif // MYBINARYTREE_H
