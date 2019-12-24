#include "fanoshannontree.h"


FanoShannonTree::FanoShannonTree(const Symbol &data) : EncodeTree(data) { }


void FanoShannonTree::createEncodeTree(const std::string &message)
{
    std::map<char, size_t> symbolMap;
    std::vector<char> symbolVector;
    for (auto elem : message) {
        if (symbolMap.count(elem) == 0) {
            symbolMap.insert(std::make_pair(elem, 1));
            symbolVector.push_back(elem);
        }
        else {
            symbolMap[elem] += 1;
        }
    }

    std::sort(symbolVector.begin(), symbolVector.end(),
              [&symbolMap] (char first, char second) {
        return symbolMap[first] > symbolMap[second]; });

    if (symbolVector.size() == 1) {
        char data = symbolVector[0];
        Symbol symbol(data, symbolMap[data]);
        FanoShannonTree* leftTree = new FanoShannonTree(symbol);
        this->setLeft(leftTree);
        this->setData(Symbol(0, symbolMap[data]));
        leftTree->setParent(this);
    }

    return createEncodeTree(symbolMap, symbolVector, 0,
                            symbolVector.size(), message.length());
}


void FanoShannonTree::createEncodeTree(std::map<char, size_t> &symbolMap,
                                       std::vector<char> &symbolVector,
                                       size_t left, size_t right, size_t sum)
{
    if (left >= right) {
        return;
    }
    if (right == left + 1) {
        char data = symbolVector[left];
        Symbol symbol(data, symbolMap[data]);
        this->setData(symbol);
        return;
    }

    size_t leftSum = 0;
    size_t rightSum = 0;
    size_t middle = getMiddle(symbolMap, symbolVector, left, sum, leftSum, rightSum);

    FanoShannonTree* leftTree = new FanoShannonTree();
    leftTree->createEncodeTree(symbolMap, symbolVector, left,
                               middle + 1, leftSum);

    FanoShannonTree* rightTree = new FanoShannonTree();
    rightTree->createEncodeTree(symbolMap, symbolVector, middle + 1,
                                right, rightSum);

    this->concatenateTrees(sum, leftTree, rightTree);
    leftTree->setParent(this);
    rightTree->setParent(this);
}


size_t FanoShannonTree::getMiddle(std::map<char, size_t> &symbolMap,
                                  std::vector<char> &symbolVector,
                                  size_t left, size_t sum, size_t &leftSum,
                                  size_t &rightSum)
{
    size_t middle = left;

    leftSum = symbolMap[symbolVector[middle]];
    rightSum = sum - leftSum;

    long delta = static_cast<long>(leftSum) - static_cast<long>(rightSum);

    while (delta + static_cast<long>(symbolMap[symbolVector[middle+1]]) < 0) {
        ++middle;
        char data = symbolVector[middle];
        leftSum += symbolMap[data];
        rightSum -= symbolMap[data];
        delta = static_cast<long>(leftSum) - static_cast<long>(rightSum);
    }
    return middle;
}
