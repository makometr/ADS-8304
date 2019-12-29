#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <queue>


#include "encodetree.h"



class HuffmanTree : public EncodeTree
{
public:
    HuffmanTree() = default;

    HuffmanTree (const Symbol& data);

    ~HuffmanTree() = default;

    HuffmanTree (const HuffmanTree& tree) = default;

    HuffmanTree& operator= (const HuffmanTree& tree) = default;

    HuffmanTree (const HuffmanTree&& tree) = delete;

    HuffmanTree& operator= (const HuffmanTree&& tree) = delete;

    class CompareHuffmanTree
    {
    public:
        bool operator() (HuffmanTree* first, HuffmanTree* second);
    };

private:
    void createEncodeTree (const std::string& text);

    void createEncodeTree (std::map<char, size_t>& charactersAndWeights,  std::vector<char> &symbolVector);

    HuffmanTree* copyNode() const;
};

#endif // HUFFMANTREE_H
