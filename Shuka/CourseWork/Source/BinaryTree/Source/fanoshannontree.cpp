#include "../Headers/fanoshannontree.h"


FanoShannonTree::FanoShannonTree (const Symbol& data) : EncodeTree (data) { }


void FanoShannonTree::createEncodeTree (const QString& text)
{
    /*
     * The method for creating a binary coding tree that accepts text.
     * 1) A dictionary of character codes and an array of characters
     * are created. Unique characters are entered into the array.
     * 2) The array is sorted in descending order of the "weight"
     * of the characters.
     * 3) The case when the text contains one character
     * processed separately.
     * 4) If the text has more than 1 character, the method of creating a
     * tree is called, which creates subtrees from subarrays.
    */

    QMap<QChar, size_t> charactersAndWeights;
    QVector<QChar> characters;

    for (auto elem : text) {
        if (charactersAndWeights.count (elem) == 0) {
            charactersAndWeights.insert (elem, 1);
            characters.push_back (elem);
        }
        else {
            charactersAndWeights[elem] += 1;
        }
    }

    std::sort (characters.begin(), characters.end(),
               [&charactersAndWeights] (QChar first, QChar second) {
        return charactersAndWeights[first] > charactersAndWeights[second]; });

    if (characters.size() == 1) {
        QChar data = characters[0];
        Symbol symbol (data, 1);

        FanoShannonTree* leftTree = new FanoShannonTree (symbol);
        leftTree->setParent (this);
        this->setLeft (leftTree);
        this->setData (Symbol (0, 1));
    }
    else {
        createEncodeTree (charactersAndWeights, characters, 0,
                          static_cast <size_t> (characters.size()),
                          static_cast <size_t> (text.size()));
    }
}


void FanoShannonTree::createEncodeTree (QMap<QChar, size_t>& charactersAndWeights,
                                        QVector<QChar>& characters,
                                        size_t leftIndex, size_t rightIndex,
                                        size_t sum)
{
    /*
     * The method for creating a binary coding tree,
     * takes a dictionary of characters, an array of characters
     * sorted in descending order, the left and right index in
     * the array, and the sum of the "weights" of the characters.
     * 1) If the left index is greater than or equal to the right, nullptr
     * is returned.
     * 2) If there is one element between the left and right indexes,
     * a leaf is created.
     * 3) Otherwise, the array is split into trees of approximately equal
     * weight, and the left and right subtrees are created recursively.
    */

    if (leftIndex >= rightIndex) {
        return;
    }

    if (rightIndex == leftIndex + 1) {
        QChar data = characters[static_cast <long> (leftIndex)];
        Symbol symbol (data, charactersAndWeights[data]);
        this->setData (symbol);
    }
    else {
        size_t leftSum = 0;
        size_t rightSum = 0;
        size_t middle = getMiddleIndex (charactersAndWeights, characters,
                                        leftIndex, sum, leftSum, rightSum);

        FanoShannonTree* leftTree = new FanoShannonTree;
        leftTree->createEncodeTree (charactersAndWeights, characters,
                                    leftIndex, middle + 1, leftSum);

        FanoShannonTree* rightTree = new FanoShannonTree;
        rightTree->createEncodeTree (charactersAndWeights, characters,
                                     middle + 1, rightIndex, rightSum);

        leftTree->setParent (this);
        rightTree->setParent (this);

        this->concatenateTrees (sum, leftTree, rightTree);
    }
}


size_t FanoShannonTree::getMiddleIndex (QMap<QChar, size_t>& charactersAndWeights,
                                        QVector<QChar>& characters,
                                        size_t leftIndex, size_t sum,
                                        size_t &leftSum, size_t &rightSum)
{
    /*
     * The function of getting the middle of an array of characters takes a
     * dictionary of characters, sorted by non-increasing array, the left
     * index in the array, links to the sum of the weights to the left and
     * right of the middle, returns the middle index.
    */

    size_t middle = leftIndex;

    leftSum = charactersAndWeights[characters[static_cast <long> (middle)]];
    rightSum = sum - leftSum;

    long delta = static_cast <long> (leftSum) - static_cast <long> (rightSum);

    while (delta + static_cast <long> (charactersAndWeights[
                                       characters[
                                       static_cast <long> (middle)+1]])< 0) {
        ++middle;

        QChar data = characters[static_cast <long> (middle)];

        leftSum += charactersAndWeights[data];
        rightSum -= charactersAndWeights[data];

        delta = static_cast <long> (leftSum) - static_cast <long> (rightSum);
    }

    return middle;
}


FanoShannonTree* FanoShannonTree::copyNode() const
{
    FanoShannonTree* node = new FanoShannonTree;

    node->setData(*(new Symbol(*this->getData())));
    if (this->getLeft() == nullptr && this->getRight() == nullptr) {
        return node;
    }

    FanoShannonTree* left = nullptr;
    if (this->getLeft() != nullptr) {
        EncodeTree* leftTmp = const_cast <EncodeTree *> (this->getLeft());
        left = dynamic_cast <FanoShannonTree *> (leftTmp);
    }

    FanoShannonTree* right = nullptr;
    if (this->getRight() != nullptr) {
        EncodeTree* rightTmp = const_cast<EncodeTree *>(this->getRight());
        left = dynamic_cast <FanoShannonTree *> (rightTmp);
    }

    left->setParent (node);
    right->setParent (node);

    node->setLeft (left);
    node->setRight (right);

    return node;
}
