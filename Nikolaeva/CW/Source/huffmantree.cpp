#include "huffmantree.h"


HuffmanTree::HuffmanTree (const Symbol& data) : EncodeTree (data) { }


void HuffmanTree::createEncodeTree (const std::string& text)
{
    std::map<char, size_t> charactersAndWeights;
    std::vector<char> symbolVector;
    for (auto elem : text) {
        if (charactersAndWeights.count (elem) == 0) {
            charactersAndWeights.insert (std::make_pair(elem, 1));
            symbolVector.push_back(elem);
        }
        else {
            charactersAndWeights[elem] += 1;
        }
    }

    if (charactersAndWeights.size() == 1) {
        char data = text[0];
        Symbol symbol (data, 1);

        HuffmanTree* leftTree = new HuffmanTree (symbol);
        leftTree->setParent (this);
        this->setLeft (leftTree);
        this->setData (Symbol (0, 1));
    }
    else {
        createEncodeTree(charactersAndWeights, symbolVector);
    }
}



void HuffmanTree::createEncodeTree (std::map<char, size_t>& charactersAndWeights,  std::vector<char> &symbolVector)
{
    std::priority_queue<HuffmanTree*, std::vector<HuffmanTree*>,
            HuffmanTree::CompareHuffmanTree> nodes;

    for (auto elem : symbolVector) {
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

        HuffmanTree* node = new HuffmanTree();
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
    HuffmanTree* node = new HuffmanTree();

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
