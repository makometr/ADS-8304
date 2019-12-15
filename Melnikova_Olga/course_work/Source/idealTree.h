#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <vector>
// если элем удалить
template <typename T>
class IdealBinaryTree
{
public:
    T value;
    std::unique_ptr<IdealBinaryTree<T>> leftTree;
    std::unique_ptr<IdealBinaryTree<T>> rightTree;

    void makeFromFile(std::ifstream& fin, std::unique_ptr<IdealBinaryTree<T>>& tree){
        T info;
        while(fin >> info){
            SearchAndInsert(info, tree);
        }
    }
    void makeFromVector(std::vector<T>& vect, std::unique_ptr<IdealBinaryTree<T>>& tree){
        makeFromVector(vect, 0, vect.size()-1, tree);
    }
    void makeFromVector(std::vector<T> & vect, unsigned int startPos, unsigned int endPos, std::unique_ptr<IdealBinaryTree<T>>& tree){
        unsigned int endPosLeft, startPosRight;
        endPosLeft = (endPos+startPos) / 2;
        startPosRight = endPosLeft + 2;

        if (startPos != endPos) {
            value = vect[endPosLeft + 1];

            if (!tree->leftTree) tree->leftTree = std::make_unique<IdealBinaryTree<T>>();
            makeFromVector(vect, startPos, endPosLeft, tree->leftTree);

            if (startPosRight <= endPos) {
                if (!tree->rightTree) tree->rightTree = std::make_unique<IdealBinaryTree<T>>();
                makeFromVector(vect, startPosRight, endPos, tree->rightTree);
            }
        }
        else {
            value = vect[endPosLeft];
        }
    }

    void WriteToFile(std::ofstream& fout, std::unique_ptr<IdealBinaryTree<T>>& tree) {
        if (tree->leftTree) WriteToFile(fout, tree->leftTree);
        fout << tree->value << std::endl;
        if (tree->rightTree) WriteToFile(fout, tree->rightTree);
    }

    int Search(T& info, long& steps, std::unique_ptr<IdealBinaryTree<T>>& tree){
        if (tree->value != info) {
            steps++;
            if(info < tree->value) {
                if(tree->leftTree != NULL) {
                    return Search(info, steps, tree->leftTree);
                }
                else return -1;
            } else {
                if(tree->rightTree != NULL) {
                    return Search(info, steps, tree->rightTree);
                }
                else return -1;
            }
        }else{
            return steps;
        }
    }

    long GetDepth(std::unique_ptr<IdealBinaryTree<T>>& tree)
    {
        long l, r;
        if (tree->leftTree)  l = GetDepth(tree->leftTree);  else l = 0;
        if (tree->rightTree) r = GetDepth(tree->rightTree); else r = 0;
        if (l > r) return l+1; else return r+1;
     }

};
