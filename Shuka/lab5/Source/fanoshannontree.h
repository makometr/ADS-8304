#ifndef FANOSHANNONTREE_H
#define FANOSHANNONTREE_H

#include "encodetree.h"


class FanoShannonTree : public EncodeTree
{
    /*
     * Класс, реализующий алгоритм кодирования Фано-
     * Шеннона с помощью бинарного дерева кодирования.
    */

public:
    FanoShannonTree() = default;
    FanoShannonTree(const Symbol& data);
    ~FanoShannonTree() = default;

private:
    void createEncodeTree(const std::string& message);

    void createEncodeTree(std::map<char, size_t>& symbolMap,
                          std::vector<char>& symbolVector,
                          size_t left, size_t right, size_t sum);

    static size_t getMiddle(std::map<char, size_t>& symbolMap,
                            std::vector<char>& symbolVector,
                            size_t left, size_t sum, size_t& leftSum,
                            size_t& rightSum);
};

#endif // FANOSHANNONTREE_H
