#include <iostream>
#include <string>
#include <queue>
#include"ioManager.h"
#include"vbinarytree.h"

VBinaryTree<int>* parse(std::istream& input);
bool isSearchTree(VBinaryTree<int>* bt);
bool isPyramid(VBinaryTree<int>* bt);

int main(int argc, char** argv)
{
    IoManager ioManager(argc, argv);
    std::string result;

    std::istream* stream = ioManager.nextStream();
    while(stream != nullptr)
    {
        std::getline(*stream, result);
        stream->seekg(0);

        VBinaryTree<int>* bt = parse(*stream);
		if(bt == nullptr)
		{
			result += " | invalid input";
			
			ioManager.writeLine(result);

			delete stream;
			stream = ioManager.nextStream();
			
			continue;
		}
        else if(isSearchTree(bt))
        {
            result += " | search tree";
        }
        else if(isPyramid(bt))
        {
            result += " | pyramid";
        }
        else
        {
            result += " | simple binary tree";
        }
		
		delete bt;

        ioManager.writeLine(result);

        delete stream;
        stream = ioManager.nextStream();
    }

    return 0;
}

VBinaryTree<int>* parse(std::istream& input)
{
    VBinaryTree<int>* bt = new VBinaryTree<int>();

    while(input.peek() != EOF)
    {
        std::string buf;
        input >> buf;

        if(buf == "(")
        {
            if(bt->left() == -1)
            {
                bt->addLeft();
                bt->toLeft();
            }
            else
            {
                bt->addRight();
                bt->toRight();
            }
        }
        else if (buf == ")")
        {
            bt->toParent();
        }
        else if(buf == "^")
        {
            if(bt->left() == -1)
            {
                bt->addLeft();
                bt->toLeft();
            }
            else
            {
                bt->addRight();
                bt->toRight();
            }
			
			bt->toParent();
        }
        else
        {
			try
			{
				bt->setValue(stoi(buf));
			}
			catch(...)
			{
				delete bt;
				
				return nullptr;
			}
        }
    }

    return bt;
}

bool isSearchTree(VBinaryTree<int>* bt)
{
    std::cout << "Checking on search tree." << std::endl;

    bool isSearch = true;
    int base = bt->current();

    std::queue<int> nodes;
    nodes.push(base);

    while(!nodes.empty() && isSearch == true)
    {
        bt->toPos(nodes.front());
        nodes.pop();

        int value = bt->getValue();

        std::cout << "Cur node value - " << value  << std::endl;

        if(bt->left() != -1){
            bt->toLeft();
            if(!bt->isEmpty())
            {
                nodes.push(bt->current());

                if(bt->getValue() > value)
                {
                    std::cout << "Left node is bigger! - FAIL" << std::endl;
                    isSearch = false;
                    break;
                }
                std::cout << "Left node lesser or equal! - OK" << std::endl;
            }
            else
            {
                std::cout << "Left node is empty! - OK" << std::endl;
            }
            bt->toParent();
        }
        else
        {
            std::cout << "Left node is not exist! - OK" << std::endl;
        }

        if(bt->right() != -1)
        {
            bt->toRight();
            if(!bt->isEmpty())
            {
                nodes.push(bt->current());

                if(bt->getValue() <= value)
                {
                    std::cout << "Right node is lesser or equal! - FAIL" << std::endl;
                    isSearch = false;
                    break;
                }
                std::cout << "Right node bigger! - OK" << std::endl;
            }
            else
            {
                std::cout << "Right node is empty! - OK" << std::endl;
            }
        }
        else
        {
            std::cout << "Right node is not exist! - OK" << std::endl;
        }

        std::cout << "----------------------step----------------------" << std::endl;
    }

    bt->toPos(base);

    return isSearch;
}

bool isPyramid(VBinaryTree<int>* bt)
{
    std::cout << "Checking on pyramid." << std::endl;

    bool isPyramid = true;
    int base = bt->current();

    std::queue<int> nodes;
    nodes.push(base);

    while(!nodes.empty() && isPyramid == true)
    {
        bt->toPos(nodes.front());
        nodes.pop();

        int value = bt->getValue();

        std::cout << "Cur node value - " << value  << std::endl;

        if(bt->left() != -1){
            bt->toLeft();
            if(!bt->isEmpty())
            {
                nodes.push(bt->current());

                if(bt->getValue() > value)
                {
                    std::cout << "Left node is bigger! - FAIL" << std::endl;
                    isPyramid = false;
                    break;
                }
                std::cout << "Left node lesser or equal! - OK" << std::endl;
            }
            else
            {
                std::cout << "Left node is empty! - OK" << std::endl;
            }
            bt->toParent();
        }
        else
        {
            std::cout << "Left node is not exist! - OK" << std::endl;
        }

        if(bt->right() != -1)
        {
            bt->toRight();
            if(!bt->isEmpty())
            {
                nodes.push(bt->current());

                if(bt->getValue() > value)
                {
                    std::cout << "Right node is bigger! - FAIL" << std::endl;
                    isPyramid = false;
                    break;
                }
                std::cout << "Right node lesser or equal! - OK" << std::endl;
            }
            else
            {
                std::cout << "Right node is empty! - OK" << std::endl;
            }
        }
        else
        {
            std::cout << "Right node is not exist! - OK" << std::endl;
        }

        std::cout << "----------------------step----------------------" << std::endl;
    }

    bt->toPos(base);

    return isPyramid;
}
