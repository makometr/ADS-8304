#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <queue>

#include "encodetree.h"


class HuffmanTree : public EncodeTree
{
    /*
     * The class that implements the Huffman coding algorithm
     * using a binary coding tree.
    */

public:
    explicit HuffmanTree() = default;

    explicit HuffmanTree (const Symbol& data);

    virtual ~HuffmanTree() = default;

    HuffmanTree (const HuffmanTree& tree) = default;

    HuffmanTree& operator= (const HuffmanTree& tree) = default;

    HuffmanTree (const HuffmanTree&& tree) = delete;

    HuffmanTree& operator= (const HuffmanTree&& tree) = delete;

    class CompareHuffmanTree
    {
    public:
        bool operator() (HuffmanTree* first, HuffmanTree* second);
    };

protected:
    virtual void createEncodeTree (const QString& text);

    virtual void createEncodeTree (QMap<QChar, size_t>& charactersAndWeights);

    virtual HuffmanTree* copyNode() const;
};

#endif // HUFFMANTREE_H
