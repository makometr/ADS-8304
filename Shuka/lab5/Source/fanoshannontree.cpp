#include "fanoshannontree.h"


FanoShannonTree::FanoShannonTree(const Symbol &data) : EncodeTree(data) { }


void FanoShannonTree::createEncodeTree(const std::string &message)
{
    /*
     * Функция, для создания бинарного дерева кодирования, принимает на вход
     * текст.
     *
     * 1) Создаются словарь и массив символов. В словарь заносится частота
     * встречаемости каждого символа в тексте.
     * В массив заносятся уникальные символы.
     *
     * 2) Массив сортируется по убыванию "веса" символов.
     *
     * 3) Случай, когда текст содержит один символ обрабатывается отдельно.
     *
     * 4) Если в тексте больше 1 символа, вызывается фунция создания дерева,
     * которая создает поддеревья из подмассивов.
    */

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
    /*
     * Функция, для создания бинарного дерева кодирования, принимает на вход
     * словарь символов, отсортированный по убыванию массив, левый и правый индекс в массиве,
     * сумму "весов" символов.
     *
     * 1) Если левый индекс больше либо равен правому - возвращает nullptr.
     *
     * 2) Если между левым и правым индексами один элемент - создаем лист.
     *
     * 3) В ином случае разделяем массив на деревья, примерно равные по весу,
     * рекурсивно создаем левое и правое поддеревья.
    */

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

    this->concat(sum, leftTree, rightTree);
    leftTree->setParent(this);
    rightTree->setParent(this);
}


size_t FanoShannonTree::getMiddle(std::map<char, size_t> &symbolMap,
                                  std::vector<char> &symbolVector,
                                  size_t left, size_t sum, size_t &leftSum,
                                  size_t &rightSum)
{
    /*
     * Функция получения середины массива символов, принимает на вход
     * словарь символов, отсортированный по не возрастанию массив, левый индекс в массиве,
     * ссылки на сумму весов слева и справа от середины, возвращает индекс середины.
    */

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
