#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <cstdio>
#include <fstream>

template <typename T>
class BinaryTree
{
public:
	T value;
    std::unique_ptr<BinaryTree<T>> leftLeaf;
    std::unique_ptr<BinaryTree<T>> rightLeaf;

    int makeFromString(std::string str)
    {
        if ((str.length() == 0) || (str[0] == '#'))
        {
            value = NULL;
            return 0;
        }
        if ((str[0] == '(') || (str[0] == ')')){
        	std::cout<<"Неправильная запись дерева" << std::endl;
        	exit(1);
        }

        value = str[0];

        std::string leftStr = "", rightStr = "";

        if (str.length() > 1)
        {
            if (str[1] != '('){
		    	std::cout<<"Неправильная запись дерева" << std::endl;
		    	exit(1);
		    }
            int leftStart = 2;
            int leftEnd;
            int rightStart;
            int rightEnd;

            leftEnd = getEndPos(str, leftStart);
            leftStr = str.substr(leftStart, leftEnd - leftStart + 1);

            rightStart = leftEnd + 1;
            //if (str.Length() > rightStart)
            if (str[rightStart] == ')')
                rightEnd = rightStart - 1;
            else
                rightEnd = getEndPos(str, rightStart);
            rightStr = str.substr(rightStart, rightEnd - rightStart + 1);
        }
        // a(b(c)e(#h))
        // 012345678901

        leftLeaf = std::make_unique<BinaryTree<char>>();
        rightLeaf = std::make_unique<BinaryTree<char>>();

        leftLeaf->makeFromString(leftStr);
        rightLeaf->makeFromString(rightStr);
    }
    
    bool isResemlanceWith(std::unique_ptr<BinaryTree<T>>& secondTree)
    {
        bool result = false;
        if (secondTree != NULL)
        {
            if ( (secondTree->leftLeaf  == NULL) == (leftLeaf  == NULL) &&
                 (secondTree->rightLeaf == NULL) == (rightLeaf == NULL)    ){
                result = true;
                if (leftLeaf != NULL)
                    result = leftLeaf->isResemlanceWith(secondTree->leftLeaf);
                if (rightLeaf != NULL)
                    result &= rightLeaf->isResemlanceWith(secondTree->rightLeaf);
            }
		}
		return result;
    }

    bool isMirrorResemlanceWith(std::unique_ptr<BinaryTree>& secondTree)
    {
        bool result = false;
        if (secondTree != NULL)
        {
            if ( (secondTree->leftLeaf  == NULL) == (rightLeaf  == NULL) &&
                 (secondTree->rightLeaf == NULL) == (leftLeaf   == NULL)    ){
                result = true;
                if (leftLeaf != NULL)
                    result = leftLeaf->isMirrorResemlanceWith(secondTree->rightLeaf);
                if (rightLeaf != NULL)
                    result &= rightLeaf->isMirrorResemlanceWith(secondTree->leftLeaf);
            }
		}
		return result;
 	}

    bool isEqualWith(std::unique_ptr<BinaryTree>& secondTree)
    {
        bool result = false;
        if (secondTree != NULL)
        {
            if ( (secondTree->leftLeaf  == NULL) == (leftLeaf  == NULL) &&
                 (secondTree->rightLeaf == NULL) == (rightLeaf == NULL) &&
                 (secondTree->value == value)                              ){
                result = true;
                if (leftLeaf != NULL)
                    result = leftLeaf->isEqualWith(secondTree->leftLeaf);
                if (rightLeaf != NULL)
                    result &= rightLeaf->isEqualWith(secondTree->rightLeaf);
            }
		}
		return result;
    }

    bool isSymmetryWith(std::unique_ptr<BinaryTree>& secondTree)
    {
        bool result = false;
        if (secondTree != NULL)
        {
            if ( (secondTree->leftLeaf  == NULL) == (rightLeaf  == NULL) &&
                 (secondTree->rightLeaf == NULL) == (leftLeaf   == NULL) &&
                 (secondTree->value == value)                              ){
                result = true;
                if (leftLeaf != NULL)
                    result = leftLeaf->isSymmetryWith(secondTree->rightLeaf);
                if (rightLeaf != NULL)
                    result &= rightLeaf->isSymmetryWith(secondTree->leftLeaf);
            }
		}
		return result;
    }

    ~BinaryTree() = default;
    
private:

    int getEndPos(std::string str, int startPos)
    {
        int endPos;
        if (str[startPos + 1] == '(')
        {
            endPos = startPos + 2;
            int brackets = 1;
            while ((brackets > 0) && (endPos < str.length()))
            {
                if (str[endPos] == '(') brackets++;
                if (str[endPos] == ')') brackets--;
                endPos++;
            }
            if (brackets > 0) {
		    	std::cout<<"Неправильная запись дерева" << std::endl;
		    	exit(1);
		    } // неправильная строка
            endPos--;
        }
        else
            endPos = startPos;
        return endPos;
    }
};
