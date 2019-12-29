#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <cstdio>
#include <fstream>
// если элем удалить
template <typename T>
class BinaryTree
{
public:
    T value;
    unsigned int count = 0;
    std::unique_ptr<BinaryTree<T>> leftTree;
    std::unique_ptr<BinaryTree<T>> rightTree;

    void makeFromFile(std::ifstream& fin, std::unique_ptr<BinaryTree<T>>& tree){
        T info;
        while(fin >> info){
            SearchAndInsert(info, tree);
        }
    }
    void SearchAndInsert(T& info, std::unique_ptr<BinaryTree<T>>& tree){
        if((tree->count) == 0 ) {
            tree->value = info;
            tree->count = 1;
        }else if ( info < tree->value ) {
            if (!tree->leftTree) tree->leftTree = std::make_unique<BinaryTree<T>>();
            SearchAndInsert(info, tree->leftTree);
        }else if(info>(tree->value)){
            if (!tree->rightTree) tree->rightTree = std::make_unique<BinaryTree<T>>();
            SearchAndInsert(info, tree->rightTree);
        }else (tree->count)++;
    }

    void WriteToFile(std::ofstream& fout, std::unique_ptr<BinaryTree<T>>& tree) {
        if (tree->leftTree) WriteToFile(fout, tree->leftTree);
        fout << tree->value << std::endl;
        if (tree->rightTree) WriteToFile(fout, tree->rightTree);
    }

    T GetAndDeleteMinValue(std::unique_ptr<BinaryTree<T>>& tree, unsigned int & count) {
        if (tree->leftTree) {
            return GetAndDeleteMinValue(tree->leftTree, count);
        }
        else {
            T result = tree->value;
            count = tree->count;
            if (tree->rightTree)
                tree->value = GetAndDeleteMinValue(tree->rightTree, tree->count);
            else
                tree = NULL;
            return result;
        }        
    }

    T GetAndDeleteMaxValue(std::unique_ptr<BinaryTree<T>>& tree, unsigned int & count) {
        if (tree->rightTree) {
            return GetAndDeleteMaxValue(tree->rightTree, count);
        }
        else {
            T result = tree->value;
            count = tree->count;
            if (tree->leftTree)
                tree->value = GetAndDeleteMaxValue(tree->leftTree, tree->count);
            else
                tree = NULL;
            return result;
        }
    }


    int SearchAndDelete(int& count, T& info, std::unique_ptr<BinaryTree<T>>& tree){
        if (tree->value != info) {
            if(info < tree->value) {
                if(tree->leftTree != NULL) {
                	count++;
                    return SearchAndDelete(count, info, tree->leftTree);
                }
                else return -1;
            } else {
                if(tree->rightTree != NULL) {
                	count++;
                    return SearchAndDelete(count, info, tree->rightTree);
                }
                else return -1;
            }
        }else{
            if (tree->rightTree) {
                tree->value = GetAndDeleteMinValue(tree->rightTree, tree->count);
            }
            else if (tree->leftTree) {
                tree->value = GetAndDeleteMaxValue(tree->leftTree, tree->count);
            }
            else {
            	if(count == 0){
            		tree->value = 0;
            		tree->count = 0;
            	}else{
                	tree = NULL;
                }
            }
            return 1;
        }
    }
};
