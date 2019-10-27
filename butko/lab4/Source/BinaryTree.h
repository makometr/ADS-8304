#pragma once

#include <iostream>
#include <string>
#include <array>
#include <fstream>

template <typename T>
class BinaryTree
{
public:
    struct Element
    {
        T value;
        size_t leftElementIndex,
               rightElementIndex;
    };
    Element** array;

    explicit BinaryTree(int size)
    {
        maxSize_ = size;
        array = new Element* [size];
        for (int i = 0; i < size; i++)
            array[i] = new Element;
    }

    void setElementValue(T value, int index)
    {
        array[index]->value = value;
    }

    void setLeftIndex(int currentIndex, int leftIndex = -1)
    {
        array[currentIndex]->leftElementIndex = leftIndex;
    }

    void setRightIndex(int currentIndex, int rightIndex = -1)
    {
        array[currentIndex]->rightElementIndex = rightIndex;
    }

    bool makeBinaryTree(int& index, const std::string& str)
    {
        int currentIndex = counter_;
        if (str[index] != '(')
        {
            std::cout<<"ERROR: incorrect string"<<std::endl;
            return false;
        }
        std::string tmpStr;
        while(str[++index] != '(' && str[index] != ')' && str[index] != '#' && index != str.size())
            tmpStr += str[index];
        if (tmpStr.empty() && str[index] == '(')
        {
            std::cout<<"ERROR: incorrect string"<<std::endl;
            return false;
        }
        setElementValue(tmpStr, currentIndex);
        if (str[index] ==')')
        {
            setLeftIndex(currentIndex);
            setRightIndex(currentIndex);
            ++index;
            return true;
        }
        if (str[index] == '#' && str[index + 1] != '(')
        {
            std::cout<<"ERROR: incorrect string"<<std::endl;
            return false;
        }
        else if (str[index] == '#')
        {
            setLeftIndex(currentIndex);
            ++index;
        }
        else if(str[index] == '(')
        {
            if(counter_ + 1 == maxSize_) resize();
            setLeftIndex(currentIndex, ++counter_);
            if(!makeBinaryTree(index, str)) return false;
        }
        if(str[index] == ')')
        {
            setRightIndex(currentIndex);
            ++index;
            return true;
        }
        else if(str[index] == '(')
        {
            if(counter_ + 1 == maxSize_) resize();
            setRightIndex(currentIndex, ++counter_);
            if(!makeBinaryTree(index, str)) return false;
        }
        else {
            std::cout << "ERROR: incorrect string" << std::endl;
            return false;
        }
        ++index;
        if(str[index] == ' ')
        {
            std::cout << "ERROR: incorrect string" << std::endl;
            return false;
        }
        return true;
    }

    void resize()
    {
        auto** tmpArray = new Element* [maxSize_*2];
        for (int i = 0; i < counter_; ++i)
            tmpArray[i] = array[i];
        maxSize_ = maxSize_*2;
        for (int i = 1 + counter_; i < maxSize_; ++i)
            tmpArray[i] = new Element;
        delete[] array;
        array = tmpArray;
    }

    void print(Element* root, int I = 0)
    {
        if (root->rightElementIndex != -1)
        {
            print(array[root->rightElementIndex], 1+I);
        }
        for (int i = 0; i < I; i++)
            std::cout << "    ";
        std::cout << root->value << std::endl;
        if (root->leftElementIndex != -1)
        {
            print(array[root->leftElementIndex], 1+I);
        }
    }

    ~BinaryTree()
    {
        for (int i = 0; i < maxSize_; ++i)
            delete(array[i]);
        delete[] array;
    }
private:
    int counter_ = 0;
    int maxSize_ = 20;
};

template <typename T>
class BinaryForest
{
public:
    BinaryTree<T> tree1;
    BinaryTree<T> tree2;
    bool isDirectResemblance = true;
    bool isDirectEquality = true;
    bool isMirrorResemblance = true;
    bool isMirrorEquality = true;

    BinaryForest(int size1, int size2) : tree1(size1), tree2(size2){}

    bool makeBinaryForest(const std::string &str1,const std::string &str2, int& index1, int& index2)
    {
        return !(!tree1.makeBinaryTree(index1, str1) || !tree2.makeBinaryTree(index2, str2));
    }

    void printBinaryForest()
    {
        std::cout << "_______________" << std::endl;
        std::cout << "Binary Tree №1 :" << std::endl;
        std::cout << "_______________" << std::endl;
        tree1.print(tree1.array[0]);
        std::cout << "_______________" << std::endl;
        std::cout << "Binary Tree №2 :" << std::endl;
        std::cout << "_______________" << std::endl;
        tree2.print(tree2.array[0]);
        std::cout << "_______________" << std::endl;
    }

    void forestComparison()
    {
        forestDirectComparison(tree1.array[0], tree2.array[0]);
        forestMirrorComparison(tree1.array[0], tree2.array[0]);
        std::cout << std::endl << "Binary trees:" << std::endl;
        if (isDirectResemblance) std::cout << "similar;" << std::endl;
        else std::cout << "not similar;" << std::endl;
        if (isDirectEquality) std::cout << "equal;" << std::endl;
        else std::cout << "not equal;" << std::endl;
        if (isMirrorResemblance) std::cout << "mirror similar;" << std::endl;
        else std::cout << "not mirror similar;" << std::endl;
        if (isMirrorEquality) std::cout << "mirror equal." << std::endl;
        else std::cout << "not mirror equal." << std::endl;
    }

    void forestDirectComparison(typename BinaryTree<T>::Element *root1, typename BinaryTree<T>::Element* root2)
    {
        if (root1->value != root2->value)
            isDirectEquality = false;

        if (root1->rightElementIndex != -1 && root2->rightElementIndex != -1)
            forestDirectComparison(tree1.array[root1->rightElementIndex], tree2.array[root2->rightElementIndex]);
        else if (root1->rightElementIndex != -1 || root2->rightElementIndex != -1)
        {
            isDirectEquality = false;
            isDirectResemblance = false;
        }

        if (root1->leftElementIndex != -1 && root2->leftElementIndex != -1)
            forestDirectComparison(tree1.array[root1->leftElementIndex], tree2.array[root2->leftElementIndex]);
        else if (root1->leftElementIndex != -1 || root2->leftElementIndex != -1)
        {
            isDirectEquality = false;
            isDirectResemblance = false;
        }
    }

    void forestMirrorComparison(typename BinaryTree<T>::Element *root1, typename BinaryTree<T>::Element* root2)
    {
        if (root1->value != root2->value)
            isMirrorEquality = false;

        if (root1->rightElementIndex != -1 && root2->leftElementIndex != -1)
            forestMirrorComparison(tree1.array[root1->rightElementIndex], tree2.array[root2->leftElementIndex]);
        else if (root1->rightElementIndex != -1 || root2->leftElementIndex != -1)
        {
            isMirrorEquality = false;
            isMirrorResemblance = false;
        }

        if (root1->leftElementIndex != -1 && root2->rightElementIndex != -1)
            forestMirrorComparison(tree1.array[root1->leftElementIndex], tree2.array[root2->rightElementIndex]);
        else if (root1->leftElementIndex != -1 || root2->rightElementIndex != -1)
        {
            isMirrorEquality = false;
            isMirrorResemblance = false;
        }
    }

    ~BinaryForest() = default;
};
