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
class RandomBinaryTree
{
public:
    T value;
    unsigned int count = 0;
    std::unique_ptr<RandomBinaryTree<T>> leftTree;
    std::unique_ptr<RandomBinaryTree<T>> rightTree;

    void makeFromVector(std::vector<T>& vect, std::unique_ptr<RandomBinaryTree<T>>& tree){
        T info;
        int i = 0;
        while(i<vect.size()){
            info = vect[i];
            i++;
            SearchAndInsert(info, tree);
        }
    }

    void makeFromFile(std::ifstream& fin, std::unique_ptr<RandomBinaryTree<T>>& tree){
        T info;
        while(fin >> info){
            SearchAndInsert(info, tree);
        }
    }
    void SearchAndInsert(T& info, std::unique_ptr<RandomBinaryTree<T>>& tree){
        if((tree->count) == 0 ) {
            tree->value = info;
            tree->count = 1;
        }else if ( info < tree->value ) {
            if (!tree->leftTree) tree->leftTree = std::make_unique<RandomBinaryTree<T>>();
            SearchAndInsert(info, tree->leftTree);
        }else if(info>(tree->value)){
            if (!tree->rightTree) tree->rightTree = std::make_unique<RandomBinaryTree<T>>();
            SearchAndInsert(info, tree->rightTree);
        }else (tree->count)++;
    }

    void WriteToFile(std::ofstream& fout, std::unique_ptr<RandomBinaryTree<T>>& tree) {
        if (tree->leftTree) WriteToFile(fout, tree->leftTree);
        fout << tree->value << std::endl;
        if (tree->rightTree) WriteToFile(fout, tree->rightTree);
    }
    void WriteToVector(std::vector<T> & vect, std::unique_ptr<RandomBinaryTree<T>>& tree) {
        if (tree->leftTree) WriteToVector(vect, tree->leftTree);
        vect.push_back(tree->value);
        if (tree->rightTree) WriteToVector(vect, tree->rightTree);
    }

    int Search(T& info, long& steps, std::unique_ptr<RandomBinaryTree<T>>& tree){
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

    long GetDepth(std::unique_ptr<RandomBinaryTree<T>>& tree)
    {
        long l, r;
        if (tree->leftTree)  l = GetDepth(tree->leftTree);  else l = 0;
        if (tree->rightTree) r = GetDepth(tree->rightTree); else r = 0;
        if (l > r) return l+1; else return r+1;
     }
};
