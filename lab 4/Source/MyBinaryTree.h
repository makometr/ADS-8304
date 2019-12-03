//
// Created by Dan on 26.11.2019.
//

#ifndef MYBINARYTREE_H
#define MYBINARYTREE_H

#include <iostream>
#include <ostream>
#include <memory>


constexpr size_t SIZE = 500;

template <class T>
class MyBinaryTree
{
    /* РљР»Р°СЃСЃ-СЂРµР°Р»РёР·Р°С†РёСЏ Р±РёРЅР°СЂРЅРѕРіРѕ РґРµСЂРµРІР° РЅР° РјР°СЃСЃРёРІРµ.
     * РЎРѕРґРµСЂР¶РёС‚ РјР°СЃСЃРёРІ СЌР»РµРјРµРЅС‚РѕРІ РґРµСЂРµРІР° Рё СЂР°Р·РјРµСЂ РґРµСЂРµРІР°.
    */

public:
#pragma pack(2)
    //РЎС‚СЂСѓРєС‚СѓСЂР° СЌР»РµРјРµРЅС‚Р° РґРµСЂРµРІР°
    struct Node
    {
        int leftElem;
        int rightElem;
        bool isNull;
        T data;
    };
    typedef std::shared_ptr<Node> NodeP;
#pragma pack()

protected:
    NodeP binTree[SIZE];
    size_t size;

public:
    explicit MyBinaryTree();
    ~MyBinaryTree() = default;
    void clearTree();

    MyBinaryTree& operator=(const MyBinaryTree& tree) = delete;
    //MyBinaryTree(const MyBinaryTree&) = delete;

    //Getters-РјРµС‚РѕРґС‹
    bool isNull(size_t index) const;
    int getLeft(size_t index) const;
    int getRight(size_t index) const;
    size_t getSize() const;
    const T& getElem(size_t index) const;

    //РњРµС‚РѕРґС‹ РґР»СЏ СЂРµС€РµРЅРёСЏ РїРѕРґР·Р°РґР°С‡. РЁР°Р±Р»РѕРЅ РјРµС‚РѕРґР° РґР»СЏ СЃРѕР·РґР°РЅРёСЏ РґРµСЂРµРІР° СЂРµР°Р»РёР·РѕРІР°РЅ С‚РѕР»СЊРєРѕ РґР»СЏ char
    size_t createCharTree(const std::string& expression) = delete;
    int minHeightToElem(const T& elem) const;
    bool isExistElem(const T& elem) const;
    size_t countElem(const T& elem) const;

    std::string toStdString() const;
    std::string toAssignmentList() const;

protected:
    //РјРµС‚РѕРґ РґР»СЏ СЃРѕР·РґР°РЅРёСЏ СЌР»РµРјРµРЅС‚Р°
    void createNode();
    //РјРµС‚РѕРґ РґР»СЏ РїСЂРµРѕР±СЂР°Р·РѕРІР°РЅРёСЏ СЌР»РµРјРµРЅС‚Р° Рє СЃС‚СЂРѕРєРµ
    void NodeToStdString(const MyBinaryTree* tree, NodeP subTree, std::string& str) const;
    //РјРµС‚РѕРґ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРЅРґРµРєСЃР° РІ СЃС‚СЂРѕРєРµ, РіРґРµ Р·Р°РєР°РЅС‡РёРІР°РµС‚СЃСЏ РїРѕРґРґРµСЂРµРІРѕ
    size_t getEndIndexSubTree(const std::string& str, size_t indexEnd) const;
    //РјРµС‚РѕРґ РґР»СЏ РїСЂРµРѕР±СЂР°Р·РѕРІР°РЅРёСЏ РґРµСЂРµРІР° Рє СѓСЃС‚СѓРїС‡Р°С‚РѕРјСѓ СЃРїРёСЃРєСѓ
    void _toAssignmentList(std::string& str, size_t index, size_t depth = 1) const;

    //РїСЂРёРІР°С‚РЅС‹Рµ РјРµС‚РѕРґС‹ РґР»СЏ РїРѕРґР·Р°РґР°С‡, РїСЂРёРЅРёРјР°СЋС‚ РЅР° РІС…РѕРґ РґРѕРї.РїР°СЂР°РјРµС‚СЂС‹
    int _minHeightToElem(const T& elem, size_t heght = 0,
                         size_t index = 0, size_t depth = 1) const;
    bool _isExistElem(const T& elem, size_t index = 0, size_t depth = 1) const;
    size_t _countElem(const T& elem, size_t index = 0, size_t depth = 1) const;
};


template<class T>
MyBinaryTree<T>::MyBinaryTree()
{
    /*
     * РЎРѕР·РґР°РЅРёРµ РїСѓСЃС‚РѕРіРѕ РґРµСЂРµРІР°
    */

    this->size = 0;
}


template<typename T>
void MyBinaryTree<T>::clearTree()
{
    /*
     * РџРѕР»РЅРѕРµ СѓРґР°Р»РµРЅРёРµ РґРµСЂРµРІР°
    */

    for (size_t i = 0; i < size; ++i) {
        binTree[i].reset();
    }
    size = 0;
}


template <class T>
void MyBinaryTree<T>::createNode()
{
    /*
     * РЎРѕР·РґР°РЅРёРµ СЌР»РµРјРµРЅС‚Р° РґРµСЂРµРІР°.
     * РњРµС‚РѕРґ РїСЂРёРІР°С‚РЅС‹Р№ С‚.Рє СЃРѕР·РґР°РЅРёРµ СЌР»РµРјРµРЅС‚РѕРІ РґРѕР»Р¶РЅРѕ РїСЂРѕРёСЃС…РѕРґРёС‚СЊ РїСЂРё СЃРѕР·РґР°РЅРёРё РґРµСЂРµРІР°,
     * РёР·-Р·Р° РѕСЃРѕР±РµРЅРЅРѕСЃС‚РµР№ СЂРµР°Р»РёР·Р°С†РёРё РЅР° РјР°СЃСЃРёРІРµ
    */

    NodeP tmp = NodeP(new Node);
    tmp->isNull = true;
    tmp->leftElem = -1;
    tmp->rightElem = -1;

    this->binTree[size] = tmp;
    size += 1;
}


template<typename T>
bool MyBinaryTree<T>::isNull(size_t index) const
{
    /*
     * РњРµС‚РѕРґ РІРѕР·РІСЂР°С‰Р°РµС‚ bool-Р·РЅР°С‡РµРЅРёРµ, СЏРІР»СЏРµС‚СЃСЏ Р»Рё СЌР»РµРјРµРЅС‚ РґРµСЂРµРІР° РЅСѓР»РµРІС‹Рј
    */

    if (index < size) {
        return binTree[index]->isNull;
    }
    else {
        return false;
    }
}


template<class T>
int MyBinaryTree<T>::getLeft(size_t index) const
{
    /*
     * РњРµС‚РѕРґ РІРѕР·РІСЂР°С‰Р°РµС‚ РёРЅРґРµРєСЃ Р»РµРІРѕРіРѕ РїРѕРґРґРµСЂРµРІР°
    */

    if (!this->isNull(index)) {
        return this->binTree[index]->leftElem;
    }
    else {
        return -1;
    }
}


template<class T>
int MyBinaryTree<T>::getRight(size_t index) const
{
    /*
     * РњРµС‚РѕРґ РІРѕР·РІСЂР°С‰Р°РµС‚ РёРЅРґРµРєСЃ РїСЂР°РІРѕРіРѕ РїРѕРґРґРµСЂРµРІР°
    */

    if (!this->isNull(index)) {
        return binTree[index]->rightElem;
    }
    else {
        return -1;
    }
}


template<class T>
size_t MyBinaryTree<T>::getSize() const
{
    /*
     * РњРµС‚РѕРґ РІРѕР·РІСЂР°С‰Р°РµС‚ СЂР°Р·РјРµСЂ РґРµСЂРµРІР°
     */

    return this->size;
}


template<class T>
const T& MyBinaryTree<T>::getElem(size_t index) const
{
    /*
     * РњРµС‚РѕРґ РІРѕР·РІСЂР°С‰Р°РµС‚ Р·РЅР°С‡РµРЅРёРµ СЌР»РµРјРµРЅС‚Р° РїРѕ РёРЅРґРµРєСЃСѓ
    */

    if (!this->isNull(index)) {
        return this->binTree[index]->data;
    }
    else {
        exit(1);
    }
}


template <> inline
size_t MyBinaryTree<char>::createCharTree(const std::string& str)
{
    /*
     * РњРµС‚РѕРґ СЃРѕР·РґР°РЅРёСЏ РґРµСЂРµРІР°. РЎС‚СЂРѕРєР° РґРѕР»Р¶РЅР° Р±С‹С‚СЊ РєРѕСЂСЂРµРєС‚РЅР°
     */

    size_t sizeRoot = this->size;
    this->createNode();
    char elem = 0;

    size_t indexStart = 1;
    while (str[indexStart] != '(' && str[indexStart] != ')') {
        if (str[indexStart] != ' ' && str[indexStart] != '(' && str[indexStart] != ')') {
            elem = str[indexStart];
            this->binTree[sizeRoot]->data = elem;
            this->binTree[sizeRoot]->isNull = false;
        }
        indexStart++;
    }

    if (str[indexStart] == ')') {
        return sizeRoot;
    }

    size_t indexEnd = indexStart + 1;
    indexEnd = getEndIndexSubTree(str, indexEnd);
    size_t leftTree = createCharTree(str.substr(indexStart, indexEnd - indexStart));
    this->binTree[sizeRoot]->leftElem = static_cast<int>(leftTree);

    indexStart = indexEnd;
    while (str[indexStart] != '(' && str[indexStart] != ')') {
        indexStart++;
    }

    if (str[indexStart] == ')') {
        return sizeRoot;
    }

    indexEnd = indexStart + 1;
    indexEnd = getEndIndexSubTree(str, indexEnd);
    size_t rightTree = createCharTree(str.substr(indexStart, indexEnd - indexStart));

    this->binTree[sizeRoot]->rightElem = static_cast<int>(rightTree);
    return sizeRoot;
}


template<class T>
size_t MyBinaryTree<T>::getEndIndexSubTree(const std::string &str, size_t indexEnd) const
{
    /*
     * РњРµС‚РѕРґ РІРѕР·РІСЂР°С‰Р°РµС‚ РёРЅРґРµРєСЃ РІ СЃС‚СЂРѕРєРµ РєРѕРЅС†Р° РїРѕРґРґРµСЂРµРІР°
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
void MyBinaryTree<T>::_toAssignmentList(std::string &str, size_t index, size_t depth) const
{
    for (size_t i = 0; i < depth; ++i) {
        str += " ";
    }
    str += getElem(index);
    str += "\n";

    if (getLeft(index) != -1) {
        _toAssignmentList(str, getLeft(index), depth + 1);
        if (getRight(index) != -1) {
            _toAssignmentList(str, getRight(index), depth + 1);
        }
    }
}


template<class T>
std::string MyBinaryTree<T>::toStdString() const
{
    /*
     * РњРµС‚РѕРґ РІРѕР·РІСЂР°С‰Р°РµС‚ РїСЂРµРґСЃС‚Р°РІР»РµРЅРёРµ Р±РёРЅР°СЂРЅРѕРіРѕ РґРµСЂРµРІР° РІ РІРёРґРµ СѓРїСЂРѕС‰РµРЅРЅРѕР№ СЃРєРѕР±РѕС‡РЅРѕР№ Р·Р°РїРёСЃРё
     * Р­Р»РµРјРµРЅС‚ РґРѕР»Р¶РµРЅ РёРјРµС‚СЊ РїРµСЂРµРіСЂСѓР·РєСѓ РѕРїСЂРµСЂР°С‚РѕСЂР° += std::string
    */

    if (size == 0)
        return "()";

    std::string tree;
    tree += "(";
    tree += this->binTree[0]->data;
    if (this->binTree[0]->leftElem != -1) {
        NodeToStdString(this, this->binTree[this->binTree[0]->leftElem], tree);
    }

    if (this->binTree[0]->rightElem != -1) {
        NodeToStdString(this, this->binTree[this->binTree[0]->rightElem], tree);
    }
    tree += ")";
    return tree;
}


template<class T>
std::string MyBinaryTree<T>::toAssignmentList() const
{
    if (size == 0) {
        return "(empty)";
    }

    std::string str;
    str += getElem(0);
    str += "\n";
    if (getLeft(0) != -1)
        _toAssignmentList(str, getLeft(0));
    if (getRight(0) != -1)
        _toAssignmentList(str, getRight(0));

    return str;
}


template<class T>
void MyBinaryTree<T>::NodeToStdString(const MyBinaryTree* tree, MyBinaryTree::NodeP subTree, std::string &str) const
{
    /*
     * РњРµС‚РѕРґР° Р·Р°РїРёСЃС‹РІР°РµС‚ РІ СЃС‚СЂРѕРєСѓ-СЂРµР·СѓР»СЊС‚Р°С‚ РїСЂРµРґСЃС‚Р°РІР»РµРЅРёРµ СЌР»РµРјРµРЅС‚Р° РґРµСЂРµРІР° РІ СѓРїСЂРѕС‰РµРЅРЅРѕР№
     * СЃРєРѕР±РѕС‡РЅРѕР№ Р·Р°РїРёСЃРё
    */

    if (!subTree->isNull) {
        str += "(";
        str += subTree->data;
        if (subTree->leftElem != -1) {
            NodeToStdString(tree, tree->binTree[subTree->leftElem], str);
        }

        if (subTree->rightElem != -1) {
            NodeToStdString(tree, tree->binTree[subTree->rightElem], str);
        }
        str += ')';
    }
    else {
        str += "()";
    }
}


template<class T>
bool MyBinaryTree<T>::isExistElem(const T& elem) const
{
    /*
     * РњРµС‚РѕРґ РґР»СЏ РѕРїСЂРµРґРµР»РµРЅРёСЏ СЃСѓС‰РµСЃС‚РІРѕРІР°РЅРёСЏ СЌР»РµРјРµРЅС‚Р° РІ РґРµСЂРµРІРµ, РІРѕР·РІСЂР°С‰Р°РµС‚ bool
    */

    if (size < 1) {
        return false;
    }
    else {
        return _isExistElem(elem);
    }
}


template<class T>
size_t MyBinaryTree<T>::countElem(const T &elem) const
{
    /*
    * РњРµС‚РѕРґ РґР»СЏ РїРѕРґСЃС‡РµС‚Р° РєРѕР»РёС‡РµСЃС‚РІР° РІС…РѕР¶РґРµРЅРёРµ СЌР»РµРјРµРЅС‚Р° РІ РґРµСЂРµРІРµ, РІРѕР·РІСЂР°С‰Р°РµС‚ size_t
   */

    if (size < 1) {
        return 0;
    }
    else {
        return _countElem(elem);
    }
}


template<typename T>
int MyBinaryTree<T>::minHeightToElem(const T &elem) const
{
    /*
     * РњРµС‚РѕРґ РґР»СЏ РѕРїСЂРµРґРµР»РµРЅРёСЏ РјРёРЅРёРјР°Р»СЊРЅРѕРіРѕ РїСѓС‚Рё РґРѕ
     * СЌР»РµРјРµРЅС‚Р° РІ РґРµСЂРµРІРµ, РІРѕР·РІСЂР°С‰Р°РµС‚ -1, РµСЃР»Рё СЌР»РµРјРµРЅС‚Р° РІ РґРµСЂРµРІРµ РЅРµС‚
    */
    if (size < 1) {
        return -1;
    }
    else {
        return _minHeightToElem(elem);
    }
}


template<typename T>
bool MyBinaryTree<T>::_isExistElem(const T &elem, size_t index, size_t depth) const
{
    std::string dbgStr;
    for (size_t i = 0; i < depth; ++i) {
        dbgStr += " ";
    }

    bool isLeftTreeExistElem = false;
    bool isRightTreeExistElem = false;
    if (this->isNull(index)) {
        return false;
    }
    else if (index < this->size) {
        if (this->getElem(index) == elem)
            return true;

        if (this->getLeft(index) != -1)
            isLeftTreeExistElem = this->_isExistElem(elem, this->getLeft(index), depth + 1);

        if(this->getRight(index) != -1)
            isRightTreeExistElem= this->_isExistElem(elem, this->getRight(index), depth + 1);

        return isLeftTreeExistElem || isRightTreeExistElem;
    }
    else {
        return false;
    }
}


template<typename T>
size_t MyBinaryTree<T>::_countElem(const T &elem, size_t index, size_t depth) const
{
    std::string dbgStr;
    for (size_t i = 0; i < depth; ++i) {
        dbgStr += " ";
    }

    size_t count = 0;
    if (this->isNull(index)) {
        return 0;
    }
    else if (index < this->size) {
        if (this->getElem(index) == elem)
            count += 1;

        if (this->getLeft(index) != -1)
            count += this->_countElem(elem, this->getLeft(index), depth + 1);

        if(this->getRight(index) != -1)
            count += this->_countElem(elem, this->getRight(index), depth + 1);

        return count;
    }
    else {
        return 0;
    }
}


template<typename T>
int MyBinaryTree<T>::_minHeightToElem(const T &elem, size_t height,
                                      size_t index, size_t depth) const
{
    std::string dbgStr;
    for (size_t i = 0; i < depth; ++i) {
        dbgStr += " ";
    }

    if (isNull(index)) {
        return -1;
    }
    if (binTree[index]->data == elem) {
        return static_cast<int>(height);
    }

    int leftIndex = binTree[index]->leftElem;
    int rightIndex = binTree[index]->rightElem;

    int minHeightLeft = -1;
    int minHeightRight = -1;

    if (leftIndex != -1) {
        minHeightLeft = _minHeightToElem(elem, height + 1, leftIndex, depth + 1);
    }

    if (rightIndex != -1) {
        minHeightRight = _minHeightToElem(elem, height + 1, rightIndex, depth + 1);
    }

    if (minHeightLeft == -1 && minHeightRight == -1) {
        return -1;
    }
    else if (minHeightLeft != -1 && minHeightRight == -1) {
        return minHeightLeft;
    }
    else if (minHeightRight != -1 && minHeightLeft == -1) {
        return minHeightRight;
    }
    else {
        return std::min(minHeightLeft, minHeightRight);
    }
}

#endif // MYBINARYTREE_H
