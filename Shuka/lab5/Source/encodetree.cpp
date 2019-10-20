#include "encodetree.h"


EncodeTree::EncodeTree()
{
    parent_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
}


EncodeTree::EncodeTree(const Symbol& data)
{
    /*
     * Конструктор создания листа дерева, принимает на вход символ
     * с его "весом".
    */

    this->data_ = data;
}


EncodeTree::~EncodeTree()
{
    if (left_ != nullptr)
        delete left_;

    if (right_ != nullptr)
        delete right_;
}


const EncodeTree *EncodeTree::getLeft() const
{
    return left_;
}


const EncodeTree *EncodeTree::getRight() const
{
    return right_;
}


const EncodeTree *EncodeTree::getParent() const
{
    return parent_;
}


const Symbol& EncodeTree::getData() const
{
    return data_;
}


void EncodeTree::setLeft(EncodeTree *left)
{
    left_ = left;
}


void EncodeTree::setRight(EncodeTree *right)
{
    right_ = right;
}


void EncodeTree::setParent(EncodeTree *parent)
{
    parent_ = parent;
}


void EncodeTree::setData(Symbol data)
{
    data_ = data;
}


void EncodeTree::concat(size_t weight, EncodeTree* left, EncodeTree* right)
{
    /*
     * Метод создания узла дерева, принимает на вход "вес"
     * поддеревьев, левое и правое поддеревья.
    */

    this->data_.weight_ = weight;
    this->left_ = left;
    this->right_ = right;
}


std::string EncodeTree::encode(const std::string &message)
{
    /*
     * Функция кодирования текста.
     * Принимает на вход текст, возвращает строку-результат,
     * содержащую закодированный текст, коды символов, представление дерева.
    */

    this->createEncodeTree(message);

    std::string code;
    std::string path;

    for (auto elem : message) {
        const EncodeTree* node = this->findSymbol(elem);

        while (node->parent_ != nullptr) {
            if (node->parent_->left_ == node) {
                path = "0" + path;
            }
            else {
                path = "1" + path;
            }
            node = node->parent_;
        }
        code += path;
        path.clear();
    }

    std::string res = "Encoded text:\n";
    res += code;

    res += "\nCharacter codes:\n";
    res += this->createCodeSymbols(message);

    std::string resTree = "\nBinary coding tree: \n";
    this->printTree(resTree);
    res += resTree;
    return res;
}


const EncodeTree *EncodeTree::findSymbol(char data) const
{
    /*
     * Функция поиска символа в дереве, принимает указатель на корень и символ,
     * возвращает указатель на лист, который содержит этот символ, либо если
     * символ отсутствует в дереве - nullptr.
    */

    if (this->left_ == nullptr && this->right_ == nullptr) {
        if (this->data_.data_ == data) {
            return this;
        }
    }
    if (this->left_ != nullptr) {
        const EncodeTree* buffer = this->left_->findSymbol(data);
        if (buffer != nullptr) {
            return buffer;
        }
    }
    if (this->right_ != nullptr) {
        const EncodeTree* buffer = this->right_->findSymbol(data);
        if (buffer != nullptr) {
            return buffer;
        }
    }
    return nullptr;
}


void EncodeTree::printTree(std::string &result, size_t level) const
{
    /*
     * Функция записи дерева в строку. Принимает на вход ссылку на
     * строку-результат и уровень в дереве.
     *
     * Записывает дерево в строку ввиде уступчатого списка.
    */

    if (this->right_ == nullptr && this->left_ == nullptr){
        for (size_t i = 0; i < level; ++i){
            result += "-";
        }

        if (this->data_.data_ == ' ') {
            result += "space";
        }
        else if (this->data_.data_ == '\n') {
            result += "\\n";
        }
        else if (this->data_.data_ == '\t') {
            result += "tabulation";
        }
        else {
            result.push_back(this->data_.data_);
        }

        result.push_back('\n');
    }
    if (this->left_){
        this->left_->printTree(result, level + 1);
    }
    if (this->right_){
        this->right_->printTree(result, level + 1);
    }
}


std::string EncodeTree::createCodeSymbols(const std::string &message) const
{
    /*
     * Функция определения кодов символов по дереву кодирования, текст и
     * возвращает строку-результат.
     *
     * 1) Создается массив уникальных символов. Алгоритм работает за O(n*m), где n -
     * текста, m - количество уникальных символов. т.к char может содержать не более 2^8
     * символов, можно считать, что алгоритм работает за O(n)
     *
     * 2) В строку результат записывается код символа, который сохраняется в
     * переменной path при проходе по дереву
    */

    std::vector<char> symbolVector;

    std::string path;
    std::string res;

    for (auto elem : message){
        if (find(symbolVector.begin(), symbolVector.end(), elem) == symbolVector.end() )
            symbolVector.push_back(elem);
    }

    for (size_t i = 0; i < symbolVector.size(); ++i){
        // Переходим в ту часть дерева, где находится нужный символ
        const EncodeTree* node = this->findSymbol(symbolVector[i]);
        // При подъеме от листа к корню если переходим влево - то
        // добавляем в массив 0, если вправо - 1
        while (node->parent_ != nullptr) {
            if (node->parent_->left_ == node) {
                path = "0" + path;
            }
            else {
                path = "1" + path;
            }

            node = node->parent_;
        }

        if (symbolVector[i] == '\n') {
            res += "\\n";
        }
        else if (symbolVector[i] == ' ') {
            res += "space";
        }
        else if (symbolVector[i] == '\t') {
            res += "tabulation";
        }
        else {
            res.push_back(symbolVector[i]);
        }

        res += "  -->  " + path + "\n";
        path.clear();
    }

    return res;
}
