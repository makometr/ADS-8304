#include <iostream>
#include <string>
#include <fstream>
#include "fanoshannontree.h"


using std::cout;
using std::cin;
using std::cerr;


std::string readText(std::istream& in);

std::string readText(std::ifstream& in);


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 3) {
        std::string text;
        std::string result;

        if (argc == 2) {
            std::string fileName = argv[1];
            result += "Read text from file " + fileName + "\n";

            std::ifstream inputFile(fileName, std::ios::in);
            text = readText(inputFile);
            inputFile.close();
        }
        else {
            cout << "Enter text: ";
            text = readText(cin);
        }

        result += "Input text:\n" + text + "\n\n";

        FanoShannonTree tree;
        result += tree.encode(text) + "\n\n\n";

        cout << result;

        std::ofstream resultFile("result.txt", std::ios::app);
        resultFile << result;
        resultFile.close();
    }
    else {
        cerr << "Error: incorect console's arguments\n";
    }

    cout << "End programm\n";
    return 0;
}


std::string readText(std::istream& in) {
    std::string result;
    std::string oneLineStr;
    while (getline(in, oneLineStr)) {
        result += oneLineStr;
        result += "\n";
    }
    result = result.substr(0, result.size() - 1);

    return result;
}


std::string readText(std::ifstream& in) {
    if (!in.is_open()) {
        cerr << "Error: incorrect file name!\n";
        return "";
    }

    std::string result;
    std::string oneLineStr;
    while (getline(in, oneLineStr)) {
        result += oneLineStr;
        result += "\n";
    }
    result = result.substr(0, result.size() - 1);

    return result;
}
