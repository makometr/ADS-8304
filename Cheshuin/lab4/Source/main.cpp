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
        if(isSearchTree(bt))
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
            bt->toParent();

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
        else
        {
            bt->setValue(stoi(buf));
        }
    }

    return bt;
}

bool isSearchTree(VBinaryTree<int>* bt)
{

    bool isSearch = true;
    int base = bt->current();

    std::queue<int> nodes;
    nodes.push(base);

    while(!nodes.empty() && isSearch == true)
    {
        bt->toPos(nodes.front());
        nodes.pop();

        int value = bt->getValue();

        if(bt->left() != -1){
            bt->toLeft();
            if(!bt->isEmpty())
            {
                nodes.push(bt->current());

                if(bt->getValue() > value)
                {
                    isSearch = false;
                    break;
                }
            }
            bt->toParent();
        }

        if(bt->right() != -1)
        {
            bt->toRight();
            if(!bt->isEmpty())
            {
                nodes.push(bt->current());

                if(bt->getValue() <= value)
                {
                    isSearch = false;
                    break;
                }
            }
        }
    }

    bt->toPos(base);

    return isSearch;
}

bool isPyramid(VBinaryTree<int>* bt)
{
    bool isPyramid = true;
    int base = bt->current();

    std::queue<int> nodes;
    nodes.push(base);

    while(!nodes.empty() && isPyramid == true)
    {
        bt->toPos(nodes.front());
        nodes.pop();

        int value = bt->getValue();

        if(bt->left() != -1){
            bt->toLeft();
            if(!bt->isEmpty())
            {
                nodes.push(bt->current());

                if(bt->getValue() > value)
                {
                    isPyramid = false;
                    break;
                }
            }
            bt->toParent();
        }

        if(bt->right() != -1)
        {
            bt->toRight();
            if(!bt->isEmpty())
            {
                nodes.push(bt->current());

                if(bt->getValue() > value)
                {
                    isPyramid = false;
                    break;
                }
            }
        }
    }

    bt->toPos(base);

    return isPyramid;
}
