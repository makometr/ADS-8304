#include "../Headers/huffmantree.h"


HuffmanTree::HuffmanTree (const Symbol& data) : EncodeTree (data) { }


void HuffmanTree::createEncodeTree (const QString& text)
{
    /*
     * The method for creating a binary coding tree that accepts text.
     * 1) A dictionary of character codes is creating.
     * 2) The case when the text contains one character
     * processed separately.
     * 3) If the text has more than 1 character, the method of creating a
     * tree is called, which creates subtrees.
    */

    QMap<QChar, size_t> charactersAndWeights;

    for (auto elem : text) {
        if (charactersAndWeights.count (elem) == 0) {
            charactersAndWeights.insert (elem, 1);
        }
        else {
            charactersAndWeights[elem] += 1;
        }
    }

    if (charactersAndWeights.size() == 1) {
        QChar data = text[0];
        Symbol symbol (data, 1);

        HuffmanTree* leftTree = new HuffmanTree (symbol);
        leftTree->setParent (this);
        this->setLeft (leftTree);
        this->setData (Symbol (0, 1));
    }
    else {
        createEncodeTree (charactersAndWeights);
    }
}


void HuffmanTree::createEncodeTree (QMap<QChar, size_t>& charactersAndWeights)
{
    /*
     * Method for creating a coding tree. Accepts a dictionary
     * of characters and their "weights".
     * 1) A priority queue is created from the dictionary.
     * 2) As long as there are at least 3 elements in the queue,
     * two elements with the smallest "weight" are extracted from the
     * queue and merged into a tree node. The tree node is queued.
     * 3) When 2 items remain in the queue, they are retrieved and
     * merged into a summary tree.
    */

    std::priority_queue<HuffmanTree*, std::vector<HuffmanTree*>,
            HuffmanTree::CompareHuffmanTree> nodes;

    for (auto elem : charactersAndWeights.keys()) {
        size_t weight = charactersAndWeights[elem];
        nodes.push (new HuffmanTree (Symbol (elem, weight)));
    }


    HuffmanTree* leftTree = nullptr;
    HuffmanTree* rightTree = nullptr;

    while (nodes.size() > 2) {
        leftTree = nodes.top();
        nodes.pop();

        rightTree = nodes.top();
        nodes.pop();

        HuffmanTree* node = new HuffmanTree;
        node->concatenateTrees(leftTree->getData()->weight_ +
                               rightTree->getData()->weight_,
                               leftTree, rightTree);

        leftTree->setParent (node);
        rightTree->setParent (node);

        nodes.push (node);
    }

    leftTree = nodes.top();
    nodes.pop();

    rightTree = nodes.top();
    nodes.pop();

    this->concatenateTrees (leftTree->getData()->weight_ +
                            rightTree->getData()->weight_,
                            leftTree, rightTree);

    leftTree->setParent (this);
    rightTree->setParent (this);
}


HuffmanTree* HuffmanTree::copyNode() const
{
    HuffmanTree* node = new HuffmanTree;

    node->setData(*(new Symbol(*this->getData())));
    if (this->getLeft() == nullptr && this->getRight() == nullptr) {
        return node;
    }

    HuffmanTree* left = nullptr;
    if (this->getLeft() != nullptr) {
        EncodeTree* leftTmp = const_cast<EncodeTree *>(this->getLeft());
        left = dynamic_cast<HuffmanTree *>(leftTmp);
    }

    HuffmanTree* right = nullptr;
    if (this->getRight() != nullptr) {
        EncodeTree* rightTmp = const_cast<EncodeTree *>(this->getRight());
        left = dynamic_cast<HuffmanTree *>(rightTmp);
    }

    left->setParent (node);
    right->setParent (node);

    node->setLeft (left);
    node->setRight (right);

    return node;
}


bool HuffmanTree::CompareHuffmanTree::operator()(HuffmanTree *first, HuffmanTree *second)
{
    return first->getData()->weight_ > second->getData()->weight_;
}
