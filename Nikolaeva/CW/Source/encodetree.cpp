#include "encodetree.h"


EncodeTree::EncodeTree()
{
    this->parent_ = nullptr;
    this->left_ = nullptr;
    this->right_ = nullptr;
    this->data_ = nullptr;
}


EncodeTree::EncodeTree (const Symbol& data)
{
    this->data_ = new Symbol (data);
    this->parent_ = nullptr;
    this->left_ = nullptr;
    this->right_ = nullptr;
}


EncodeTree::~EncodeTree()
{
    if (left_ != nullptr) {
        delete left_;
    }

    if (right_ != nullptr) {
        delete right_;
    }

    if (data_ != nullptr) {
        delete data_;
    }
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




const Symbol* EncodeTree::getData() const
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


void EncodeTree::setData (const Symbol& data)
{
    if (data_ == nullptr) {
        data_ = new Symbol;
    }

    *data_ = data;
}



void EncodeTree::concatenateTrees (size_t weight, EncodeTree* left,
                                   EncodeTree* right)
{
    if (data_ == nullptr) {
        data_ = new Symbol;
    }

    this->data_->weight_ = weight;
    this->left_ = left;
    this->right_ = right;
}


std::string EncodeTree::encode(const std::string &message)
{
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

    std::string res;
    res += code;

    return res;
}

const EncodeTree* EncodeTree::findSymbol (char data) const
{
    if (this->isLeaf()) {
        if (this->data_->data_ == data) {
            return this;
        }
    }

    if (this->left_ != nullptr) {
        const EncodeTree* buffer = this->left_->findSymbol (data);
        if (buffer != nullptr) {
            return buffer;
        }
    }

    if (this->right_ != nullptr) {
        const EncodeTree* buffer = this->right_->findSymbol (data);
        if (buffer != nullptr) {
            return buffer;
        }
    }

    return nullptr;
}

void EncodeTree::printTree (std::string& result, size_t depth) const
{
    if (this->isLeaf()) {
        for (size_t i = 0; i < depth; ++i){
            result += "-";
        }

        char data = this->data_->data_;
        if (data == ' ') {
            result += "space";
        }
        else if (data == '\n') {
            result += "\\n";
        }
        else if (data == '\t') {
            result += "tab";
        }
        else {
            result += data;
        }

        result += "\n";
    }
    else {
        depth += 1;

        if (this->left_ != nullptr) {
            this->left_->printTree (result, depth);
        }

        if (this->right_ != nullptr) {
            this->right_->printTree (result, depth);
        }
    }
}



std::string EncodeTree::createCodeSymbols(const std::string &message) const
{
    std::vector<char> symbolVector;

    std::string path;
    std::string res;

    for (auto elem : message){
        if (find(symbolVector.begin(), symbolVector.end(), elem) == symbolVector.end() )
            symbolVector.push_back(elem);
    }

    for (size_t i = 0; i < symbolVector.size(); ++i){
         const EncodeTree* node = this->findSymbol(symbolVector[i]);
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

bool EncodeTree::isEmptyNode() const
{
    return (this->data_ == nullptr &&
            this->left_ == nullptr &&
            this->right_ == nullptr);
}


bool EncodeTree::isLeaf() const
{
    return this->left_ == nullptr && this->right_ == nullptr;
}

void EncodeTree::getCharactersCode (std::map<std::string, char>& charactersCode,
                                    const std::string& path) const
{

    if (this->isEmptyNode()) {
        return;
    }

    if (this->isLeaf()) {
        char data = this->data_->data_;
        charactersCode.insert(std::make_pair(path, data));
    }
    else {
        if (this->left_ != nullptr) {
            this->left_->getCharactersCode (charactersCode, path + "0");
        }
        if (this->right_ != nullptr) {
            this->right_->getCharactersCode (charactersCode, path + "1");
        }
    }
}

std::map<std::string, char> EncodeTree::getCharactersCode() const
{
    std::map<std::string, char> charactersCode;

    if (this->isEmptyNode()) {
        return charactersCode;
    }

    if (this->left_ != nullptr) {
        this->left_->getCharactersCode (charactersCode, "0");
    }
    if (this->right_ != nullptr) {
        this->right_->getCharactersCode (charactersCode, "1");
    }

    return charactersCode;
}


