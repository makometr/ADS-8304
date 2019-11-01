#ifndef FANOSHANNONTREE_H
#define FANOSHANNONTREE_H

#include "encodetree.h"


class FanoShannonTree : public EncodeTree
{
    /*
     * The class that implements the Fano-Shannon coding algorithm
     * using a binary coding tree.
    */

public:
    explicit FanoShannonTree() = default;

    explicit FanoShannonTree (const Symbol& data);

    virtual ~FanoShannonTree() = default;

    FanoShannonTree (const FanoShannonTree& tree) = default;

    FanoShannonTree& operator= (const FanoShannonTree& tree) = default;

    FanoShannonTree (const FanoShannonTree&& tree) = delete;

    FanoShannonTree& operator= (const FanoShannonTree&& tree) = delete;

protected:
    virtual void createEncodeTree (const QString& text);

    virtual void createEncodeTree (QMap<QChar, size_t>& charactersAndWeights,
                                   QVector<QChar>& characters,
                                   size_t leftIndex, size_t rightIndex,
                                   size_t sum);

    static size_t getMiddleIndex (QMap<QChar, size_t>& symbolMap,
                                  QVector<QChar>& symbolVector,
                                  size_t leftIndex, size_t sum,
                                  size_t& leftSum, size_t& rightSum);

    virtual FanoShannonTree* copyNode() const;
};

#endif // FANOSHANNONTREE_H
