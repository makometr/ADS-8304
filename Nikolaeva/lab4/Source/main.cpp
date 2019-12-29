#include <iostream>
#include <string>
#include <fstream>
#include "mybinarytree.h"


using std::cout;
using std::cin;
using std::cerr;


std::string readStr(std::istream& in);
std::string readStr(std::ifstream& in);

bool isCorrectStr(const std::string& str);


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 3) {
        std::string expression;
        std::string result;
        std::string element;
        char elem;

        if (argc == 2) {
            std::string fileName = argv[1];
            std::ifstream inputFile (fileName, std::ios::in);
            if (!inputFile.is_open()) {
                cerr << "Error. I ncorrect file name!\n";
                return 0;
            }
            expression = readStr(inputFile);
            element = readStr(inputFile);
            inputFile.close();
        }
        else {
            cout << "Enter a tree:\n";
            expression = readStr(cin);

            cout << "Enter an element:\n";
            element = readStr(cin);
        }

        result += "Input expression:\n" + expression + "\nInput element:\n" + element + "\n";

        bool isCorrectInput = true;

        if (element.length() > 1){
            result += "Incorrect element\n";
            isCorrectInput = false;
        };

        if (!isCorrectStr(expression)) {
            result += "Incorrect expression\n";
            isCorrectInput = false;
        }

        if (isCorrectInput) {
            elem = *(element.c_str());

            BinaryTree<char>::BinaryTreeP tree = BinaryTree<char>::createCharTree(expression);

            if (tree->elemIsExist(elem)){
                result += "\nThe elemnt \"" + element + "\" exists in the tree.\n";
            }
            else {
                result += "\nThe elemnt \"" + element + "\" doesnt exist in the tree.\n";
            }

            size_t count = tree->numberOfElem(elem);
            result += "The number of elements \"" + element +
                    "\" is " + std::to_string(count) + "\n";

            int depth = tree->minDepthToElem(elem);
            result += "The length of the minimum path to the element \"" + element +
                    "\" is " + std::to_string(depth) + "\n";
        }

	result += "\n\n\n";
        cout << result;

        std::ofstream outputFile("result.txt", std::ios::app);
        outputFile << result;
        outputFile.close();
    }
    else {
        cerr << "Error: incorect console's arguments\n";
    }

    return 0;
}


std::string readStr(std::istream& in) {
    std::string result;
    std::string str;
    getline(in, str);
    result += str;
    result += "\n";

    result = result.substr(0, result.size() - 1);

    return result;
}

std::string readStr(std::ifstream& in) {
    std::string result;
    std::string str;
    getline(in, str);
    result += str;
    result += "\n";

    result = result.substr(0, result.size() - 1);

    return result;
}


bool isCorrectStr(const std::string &str)
{

    bool isElem = false;
    bool flagIsCorrect = true;
    if (str[0] != '(' || str[str.length() - 1] != ')') {
        cout << "This binary tree representation must begin and end with brackets\n";
        return false;
    }

    size_t indexStart;
    size_t numberOfBrackets = 0;
    for (indexStart = 1; indexStart < str.length() - 1; indexStart++) {
        if (str[indexStart] != ' ' && str[indexStart] != '(' && str[indexStart] != ')') {
            if (!isElem) {
                isElem = true;
            }
            else {
                cout << "Multiple items in a row without parentheses";
                return false;
            }
        }
        if (str[indexStart] == '(') {
            if (!isElem) {
                cout << "An item was not added to the node";
                return false;
            }
            numberOfBrackets++;
            if (numberOfBrackets > 2) {
                cout << "An item was not added to the node.";
                return false;
            }
            size_t indexEnd = indexStart;
            int openB = 1;
            int closeB = 0;
            while (openB > closeB) {
                indexEnd++;
                if (indexEnd >= str.length()) {
                    cout << "Incorrect enter string";
                    return false;
                }
                if (str[indexEnd] == '(') {
                    openB++;
                }
                else if (str[indexEnd] == ')') {
                    closeB++;
                }
            }
            flagIsCorrect = flagIsCorrect && isCorrectStr(str.substr(indexStart, indexEnd - indexStart+ 1));
            indexStart= indexEnd;
        }
    }
    if (str[indexStart] == ')') {
        if (!isElem) {
            cout << "An item was not added to the node";
            return false;
        }
        if (indexStart== str.length() - 1) {
            return flagIsCorrect;
        }
        else {
            cout << "Incorrect entering";
            return false;
        }
    }
    return false;
}

