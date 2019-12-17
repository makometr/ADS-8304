#include "../Headers/encodetree.h"


EncodeTree::EncodeTree()
{
    this->parent_ = nullptr;
    this->left_ = nullptr;
    this->right_ = nullptr;
    this->data_ = nullptr;
}


EncodeTree::EncodeTree (const Symbol& data)
{
    /*
     * Constructor to create a leaf of a tree, accept the symbol
     * with his "weight".
    */

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


EncodeTree::EncodeTree (const EncodeTree& tree)
{
    this->left_ = tree.left_->copyNode();
    this->right_ = tree.right_->copyNode();

    left_->setParent(this);
    right_->setParent(this);

    this->data_ = new Symbol (*tree.data_);
}


EncodeTree& EncodeTree::operator= (const EncodeTree& tree)
{
    if (this == &tree) {
        return *this;
    }

    if  (left_ != nullptr) {
        delete left_;
    }

    if (right_ != nullptr) {
        delete right_;
    }

    if (data_ != nullptr) {
        delete data_;
    }

    this->left_ = tree.left_->copyNode();
    this->right_ = tree.right_->copyNode();

    left_->setParent (this);
    right_->setParent (this);

    this->data_ = new Symbol (*tree.data_);

    return *this;
}


const EncodeTree* EncodeTree::getLeft() const
{
    return left_;
}


const EncodeTree* EncodeTree::getRight() const
{
    return right_;
}


const EncodeTree* EncodeTree::getParent() const
{
    return parent_;
}


const Symbol* EncodeTree::getData() const
{
    return data_;
}


size_t EncodeTree::getHeight() const
{

    /*
     * Method for calculating tree height. Returns the height of the tree.
    */
    
    if (this->isEmptyNode()) {
        return 0;
    }

    size_t leftHeight = 0;
    if (this->left_ != nullptr) {
        leftHeight = this->left_->getHeight();
    }

    size_t rightHeight = 0;
    if (this->right_ != nullptr) {
        rightHeight = this->right_->getHeight();
    }

    return 1 + std::max (leftHeight, rightHeight);
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


void EncodeTree::setLeft (EncodeTree* left)
{
    left_ = left;
}


void EncodeTree::setRight (EncodeTree* right)
{
    right_ = right;
}


void EncodeTree::setParent (EncodeTree* parent)
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
    /*
     * The method for creating a tree node takes the
     * "weight" of subtrees, left and right subtrees.
    */

    if (data_ == nullptr) {
        data_ = new Symbol;
    }

    this->data_->weight_ = weight;
    this->left_ = left;
    this->right_ = right;
}


QString EncodeTree::encodeText (const QString& text)
{
    /*
     * The method for encoding text.
     * Accepts input text, returns encoded text.
    */

    if (text.size() == 0) {
        return "";
    }

    this->createEncodeTree (text);

    QString code;
    QString path;

    for (auto elem : text) {
        const EncodeTree* node = this->findSymbol (elem);

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

    return code;
}


const EncodeTree* EncodeTree::findSymbol (QChar data) const
{
    /*
     * The method for finding a character in a tree takes a pointer
     * to the root and a character, returns a pointer to the leaf
     * that contains that character, or if the character is not in
     * the tree, returns nullptr.
    */

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


void EncodeTree::printTree (QString& result, size_t depth) const
{
    /*
     * The method for writing a tree to a string. Accepts
     * a link to the result string and current depth.
     * Writes a tree to a string as a list.
    */

    if (this->isLeaf()) {
        for (size_t i = 0; i < depth; ++i){
            result += "-";
        }

        QChar data = this->data_->data_;
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


void EncodeTree::getCharactersCode (QMap<QString, QChar>& charactersCode,
                                    const QString& path) const
{
    /*
     * The method for obtaining character codes.
     * Accepts a dictionary of character codes and the current path in the
     * tree.
     * 1) If the tree node is empty, the method exits.
     * 2) If the current node is a leaf, writes a symbol with its code into
     * the dictionary.
     * 3) Otherwise, it is called recursively for the left and right subtrees.
    */

    if (this->isEmptyNode()) {
        return;
    }

    if (this->isLeaf()) {
        QChar data = this->data_->data_;
        charactersCode.insert (path, data);
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


QMap<QString, QChar> EncodeTree::getCharactersCode() const
{
    /*
     * The method for obtaining character codes., returns a
     * result map.
    */

    QMap<QString, QChar> charactersCode;

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


QString EncodeTree::printTree() const
{
    /*
     * The method for writing a tree to a string
     * in the form of a list.
    */

    QString result;

    printTree (result);

    return result;
}
